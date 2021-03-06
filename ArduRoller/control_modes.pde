/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#define CONTROL_SWITCH_COUNTER  10  // 10 iterations at 100hz (i.e. 1/10th of a second) at a new switch position will cause flight mode change
static void read_control_switch()
{
    static uint8_t switch_counter = 0;

    uint8_t switchPosition = readSwitch();

    if (oldSwitchPosition != switchPosition) {
        switch_counter++;
        if(switch_counter >= CONTROL_SWITCH_COUNTER) {
            oldSwitchPosition       = switchPosition;
            switch_counter          = 0;
			set_mode(flight_modes[switchPosition]);
        }
    }else{
        // reset switch_counter if there's been no change
        // we don't want 10 intermittant blips causing a flight mode change
        switch_counter = 0;
    }
}

static uint8_t readSwitch(void){
    int16_t pulsewidth = g.rc_5.radio_in;   // default for Arducopter

    if (pulsewidth < 1231) return 0;
    if (pulsewidth < 1361) return 1;
    if (pulsewidth < 1491) return 2;
    if (pulsewidth < 1621) return 3;
    if (pulsewidth < 1750) return 4;        // Software Manual
    return 5;                               // Hardware Manual
}

static void reset_control_switch()
{
    oldSwitchPosition = -1;
    read_control_switch();
}

// read at 10 hz
// set this to your trainer switch
static void read_trim_switch()
{
    // return immediately if the CH7 switch has not changed position
    if (ap_system.CH7_flag == (g.rc_7.radio_in >= CH7_PWM_TRIGGER)) {
        return;
    }

    // set the ch7 flag
    ap_system.CH7_flag = (g.rc_7.radio_in >= CH7_PWM_TRIGGER);

    // multi-mode
    int8_t option;

    if(g.ch7_option == CH7_MULTI_MODE) {
        if (g.rc_6.radio_in < CH6_PWM_TRIGGER) {
            option = CH7_RTL;
        }else if (g.rc_6.radio_in >= CH6_PWM_TRIGGER) {
            option = CH7_SAVE_WP;
        }
    }else{
        option = g.ch7_option;
    }

    switch(option) {
        case CH7_RTL:
            if (ap_system.CH7_flag) {
                // engage RTL
                set_mode(RTL);
            }else{
                // disengage RTL to previous flight mode if we are currently in RTL
                if (control_mode == RTL) {
                    reset_control_switch();
                }
            }
            break;

        case CH7_SAVE_TRIM:
            break;

        case CH7_SAVE_WP:
            // save when CH7 switch is switched off
            if (ap_system.CH7_flag == false) {

                // if in auto mode, reset the mission
                if(control_mode == AUTO) {
                    CH7_wp_index = 0;
                    g.command_total.set_and_save(1);
                    set_mode(RTL);
                    return;
                }

                // increment index
                CH7_wp_index++;

                // set the next_WP (home is stored at 0)
                // max out at 100 since I think we need to stay under the EEPROM limit
                CH7_wp_index = constrain_int16(CH7_wp_index, 1, 100);

				// set our location ID to 16, MAV_CMD_NAV_WAYPOINT
				current_loc.id = MAV_CMD_NAV_WAYPOINT;

                // save command
                set_cmd_with_index(current_loc, CH7_wp_index);

                // Cause the CopterLEDs to blink twice to indicate saved waypoint
                copter_leds_nav_blink = 10;
            }
            break;

#if CAMERA == ENABLED
        case CH7_CAMERA_TRIGGER:
            if(ap_system.CH7_flag) {
                do_take_picture();
            }
            break;
#endif

        case CH7_SONAR:
            // enable or disable the sonar
            g.sonar_enabled = ap_system.CH7_flag;
            break;
    }
}

// save_trim - adds roll and pitch trims from the radio to ahrs
static void save_trim()
{
    // save roll and pitch trim
    float roll_trim = ToRad((float)g.rc_1.control_in/100.0f);
    float pitch_trim = ToRad((float)g.rc_2.control_in/100.0f);
    ahrs.add_trim(roll_trim, pitch_trim);
}

// auto_trim - slightly adjusts the ahrs.roll_trim and ahrs.pitch_trim towards the current stick positions
// meant to be called continuously while the pilot attempts to keep the copter level
static void auto_trim()
{
    if(auto_trim_counter > 0) {
        auto_trim_counter--;

        // flash the leds
        led_mode = SAVE_TRIM_LEDS;

        // calculate roll trim adjustment
        float roll_trim_adjustment = ToRad((float)g.rc_1.control_in / 4000.0f);

        // calculate pitch trim adjustment
        float pitch_trim_adjustment = ToRad((float)g.rc_2.control_in / 4000.0f);

        // make sure accelerometer values impact attitude quickly
        ahrs.set_fast_gains(true);

        // add trim to ahrs object
        // save to eeprom on last iteration
        ahrs.add_trim(roll_trim_adjustment, pitch_trim_adjustment, (auto_trim_counter == 0));

        // on last iteration restore leds and accel gains to normal
        if(auto_trim_counter == 0) {
            ahrs.set_fast_gains(false);
            led_mode = NORMAL_LEDS;
        }
    }
}

