// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#ifndef _DEFINES_H
#define _DEFINES_H

#include <AP_HAL_Boards.h>

// Just so that it's completely clear...
#define ENABLED                 1
#define DISABLED                0

// this avoids a very common config error
#define ENABLE ENABLED
#define DISABLE DISABLED

// Flight modes
// ------------
#define YAW_HOLD                0       // heading hold at heading in nav_yaw but allow input from pilot
#define YAW_ACRO                1       // pilot controlled yaw using rate controller
#define YAW_LOOK_AT_NEXT_WP     2       // point towards next waypoint (no pilot input accepted)
#define YAW_LOOK_AT_LOCATION    3       // point towards a location held in yaw_look_at_WP (no pilot input accepted)
#define YAW_CIRCLE              4       // point towards a location held in yaw_look_at_WP (no pilot input accepted)
#define YAW_LOOK_AT_HOME    	5       // point towards home (no pilot input accepted)
#define YAW_LOOK_AT_HEADING    	6       // point towards a particular angle (not pilot input accepted)
#define YAW_LOOK_AHEAD			7		// WARNING!  CODE IN DEVELOPMENT NOT PROVEN

#define ROLL_PITCH_STABLE 		0
#define ROLL_PITCH_AUTO			1
#define ROLL_PITCH_FBW			2


// sonar - for use with CONFIG_SONAR_SOURCE
#define SONAR_SOURCE_ADC 1
#define SONAR_SOURCE_ANALOG_PIN 2

// CH 7 control
#define CH7_PWM_TRIGGER 1800    // pwm value above which the channel 7 option will be invoked
//#define CH6_PWM_TRIGGER_HIGH 1800
//#define CH6_PWM_TRIGGER_LOW 1200
#define CH6_PWM_TRIGGER 1500

#define CH7_DO_NOTHING      0
#define CH7_SET_HOVER       1       // deprecated
#define CH7_RTL             4
#define CH7_SAVE_TRIM       5
#define CH7_ADC_FILTER      6       // deprecated
#define CH7_SAVE_WP         7
#define CH7_MULTI_MODE      8
#define CH7_CAMERA_TRIGGER  9
#define CH7_SONAR           10      // allow enabling or disabling sonar in flight which helps avoid surface tracking when you are far above the ground



// Frame types
#define QUAD_FRAME 0
#define TRI_FRAME 1
#define HEXA_FRAME 2
#define Y6_FRAME 3
#define OCTA_FRAME 4
#define HELI_FRAME 5
#define OCTA_QUAD_FRAME 6

#define PLUS_FRAME 0
#define X_FRAME 1
#define V_FRAME 2

// LED output
#define NORMAL_LEDS 0
#define SAVE_TRIM_LEDS 1


// Internal defines, don't edit and expect things to work
// -------------------------------------------------------

#define TRUE 1
#define FALSE 0
#define ToRad(x) radians(x)	// *pi/180
#define ToDeg(x) degrees(x)	// *180/pi

#define DEBUG 0
#define LOITER_RANGE 60 // for calculating power outside of loiter radius

#define T6 1000000
#define T7 10000000

// GPS type codes - use the names, not the numbers
#define GPS_PROTOCOL_NONE       -1
#define GPS_PROTOCOL_NMEA       0
#define GPS_PROTOCOL_SIRF       1
#define GPS_PROTOCOL_UBLOX      2
#define GPS_PROTOCOL_IMU        3
#define GPS_PROTOCOL_MTK        4
#define GPS_PROTOCOL_HIL        5
#define GPS_PROTOCOL_MTK19      6
#define GPS_PROTOCOL_AUTO       7

// HIL enumerations
#define HIL_MODE_DISABLED               0
#define HIL_MODE_ATTITUDE               1
#define HIL_MODE_SENSORS                2

// Altitude status definitions
#define REACHED_ALT                     0
#define DESCENDING                      1
#define ASCENDING                       2

// Auto Pilot modes
// ----------------
#define STABILIZE 0                     //
#define FBW 1                      		//
#define AUTO 2                          //
#define GUIDED 3                        //
#define RTL 4                           //
#define CIRCLE 5                        //
#define NUM_MODES 6

// CH_6 Tuning
// -----------
#define CH6_NONE            0           // no tuning performed


// Commands - Note that APM now uses a subset of the MAVLink protocol
// commands.  See enum MAV_CMD in the GCS_Mavlink library
#define CMD_BLANK 0 // there is no command stored in the mem location
                    // requested
#define NO_COMMAND 0


// Navigation modes held in nav_mode variable
#define NAV_NONE        0
#define NAV_CIRCLE      1
#define NAV_LOITER      2
#define NAV_WP          3
#define NAV_AVOID_BACK  4
#define NAV_AVOID_TURN  5


// Yaw behaviours during missions - possible values for WP_YAW_BEHAVIOR parameter
#define WP_YAW_BEHAVIOR_NONE                          0   // auto pilot will never control yaw during missions or rtl (except for DO_CONDITIONAL_YAW command received)
#define WP_YAW_BEHAVIOR_LOOK_AT_NEXT_WP               1   // auto pilot will face next waypoint or home during rtl
#define WP_YAW_BEHAVIOR_LOOK_AT_NEXT_WP_EXCEPT_RTL    2   // auto pilot will face next waypoint except when doing RTL at which time it will stay in it's last
#define WP_YAW_BEHAVIOR_LOOK_AHEAD                    3   // auto pilot will look ahead during missions and rtl (primarily meant for traditional helicotpers)


// Waypoint options
#define MASK_OPTIONS_RELATIVE_ALT               1
#define WP_OPTION_ALT_CHANGE                    2
#define WP_OPTION_YAW                           4
#define WP_OPTION_ALT_REQUIRED                  8
#define WP_OPTION_RELATIVE                      16
//#define WP_OPTION_					32
//#define WP_OPTION_					64
#define WP_OPTION_NEXT_CMD                      128

// RTL state
#define RTL_STATE_START             0
#define RTL_STATE_INITIAL_CLIMB     1
#define RTL_STATE_RETURNING_HOME    2
#define RTL_STATE_LOITERING_AT_HOME 3
#define RTL_STATE_FINAL_DESCENT     4
#define RTL_STATE_LAND              5

//repeating events
#define RELAY_TOGGLE 5

//  GCS Message ID's
/// NOTE: to ensure we never block on sending MAVLink messages
/// please keep each MSG_ to a single MAVLink message. If need be
/// create new MSG_ IDs for additional messages on the same
/// stream
enum ap_message {
    MSG_HEARTBEAT,
    MSG_ATTITUDE,
    MSG_LOCATION,
    MSG_EXTENDED_STATUS1,
    MSG_EXTENDED_STATUS2,
    MSG_NAV_CONTROLLER_OUTPUT,
    MSG_CURRENT_WAYPOINT,
    MSG_VFR_HUD,
    MSG_RADIO_OUT,
    MSG_RADIO_IN,
    MSG_RAW_IMU1,
    MSG_RAW_IMU2,
    MSG_RAW_IMU3,
    MSG_GPS_RAW,
    MSG_SERVO_OUT,
    MSG_NEXT_WAYPOINT,
    MSG_NEXT_PARAM,
    MSG_STATUSTEXT,
    MSG_AHRS,
    MSG_SIMSTATE,
    MSG_HWSTATUS,
    MSG_RETRY_DEFERRED // this must be last
};

enum gcs_severity {
    SEVERITY_LOW=1,
    SEVERITY_MEDIUM,
    SEVERITY_HIGH,
    SEVERITY_CRITICAL
};

//  Logging parameters
#define TYPE_AIRSTART_MSG               0x00
#define TYPE_GROUNDSTART_MSG            0x01
#define LOG_ATTITUDE_MSG                0x01
#define LOG_MODE_MSG                    0x03
#define LOG_CONTROL_TUNING_MSG          0x04
#define LOG_NAV_TUNING_MSG              0x05
#define LOG_PERFORMANCE_MSG             0x06
#define LOG_CMD_MSG                     0x08
#define LOG_STARTUP_MSG                 0x0A
#define LOG_EVENT_MSG                   0x0D
#define LOG_COMPASS_MSG                 0x0F
#define LOG_DMP_MSG                     0x10
#define LOG_INAV_MSG                    0x11
#define LOG_CAMERA_MSG                  0x12
#define LOG_ERROR_MSG                   0x13
#define LOG_DATA_INT16_MSG              0x14
#define LOG_DATA_UINT16_MSG             0x15
#define LOG_DATA_INT32_MSG              0x16
#define LOG_DATA_UINT32_MSG             0x17
#define LOG_DATA_FLOAT_MSG              0x18
#define LOG_WPNAV_MSG                   0x19
#define LOG_INDEX_MSG                   0xF0
#define MAX_NUM_LOGS                    50

#define MASK_LOG_ATTITUDE_FAST          (1<<0)
#define MASK_LOG_ATTITUDE_MED           (1<<1)
#define MASK_LOG_GPS                    (1<<2)
#define MASK_LOG_PM                     (1<<3)
#define MASK_LOG_NTUN                   (1<<5)
#define MASK_LOG_MODE                   (1<<6)
#define MASK_LOG_IMU                    (1<<7)
#define MASK_LOG_CMD                    (1<<8)
#define MASK_LOG_COMPASS                (1<<13)
#define MASK_LOG_INAV                   (1<<14)
#define MASK_LOG_CAMERA                 (1<<15)

// DATA - event logging
#define DATA_MAVLINK_FLOAT              1
#define DATA_MAVLINK_INT32              2
#define DATA_MAVLINK_INT16              3
#define DATA_MAVLINK_INT8               4
#define DATA_FAST_LOOP                  5
#define DATA_MED_LOOP                   6
#define DATA_AP_STATE                   7
#define DATA_ARMED                      10
#define DATA_DISARMED                   11
#define DATA_LOST_GPS                   19
#define DATA_LOST_COMPASS               20
#define DATA_BEGIN_FLIP                 21
#define DATA_END_FLIP                   22
#define DATA_EXIT_FLIP                  23
#define DATA_FLIP_ABORTED               24
#define DATA_SET_HOME                   25
#define DATA_REACHED_ALT                28
#define DATA_ASCENDING                  29
#define DATA_DESCENDING                 30
#define DATA_RTL_REACHED_ALT            31

// battery monitoring macros
#define BATTERY_VOLTAGE(x) (x->voltage_average()*g.volt_div_ratio)
#define CURRENT_AMPS(x) (x->voltage_average()-CURR_AMPS_OFFSET)*g.curr_amp_per_volt

#define BATT_MONITOR_DISABLED               0
#define BATT_MONITOR_VOLTAGE_ONLY           3
#define BATT_MONITOR_VOLTAGE_AND_CURRENT    4

/* ************************************************************** */
/* Expansion PIN's that people can use for various things. */

// AN0 - 7 are located at edge of IMU PCB "above" pressure sensor and
// Expansion port
// AN0 - 5 are also located next to voltage dividers and sliding SW2 switch
// AN0 - 3 has 10kOhm resistor in serial, include 3.9kOhm to make it as
// voltage divider
// AN4 - 5 are direct GPIO pins from atmega1280 and they are the latest pins
// next to SW2 switch
// Look more ArduCopter Wiki for voltage dividers and other ports
#define AN0  54  // resistor, vdiv use, divider 1 closest to relay
#define AN1  55  // resistor, vdiv use, divider 2
#define AN2  56  // resistor, vdiv use, divider 3
#define AN3  57  // resistor, vdiv use, divider 4 closest to SW2
#define AN4  58  // direct GPIO pin, default as analog input, next to SW2
                 // switch
#define AN5  59  // direct GPIO pin, default as analog input, next to SW2
                 // switch
#define AN6  60  // direct GPIO pin, default as analog input, close to
                 // Pressure sensor, Expansion Ports
#define AN7  61  // direct GPIO pin, default as analog input, close to
                 // Pressure sensor, Expansion Ports

// AN8 - 15 are located at edge of IMU PCB "above" pressure sensor and
// Expansion port
// AN8 - 15 PINs are not connected anywhere, they are located as last 8 pins
// on edge of the board above Expansion Ports
// even pins (8,10,12,14) are at edge of board, Odd pins (9,11,13,15) are on
// inner row
#define AN8  62  // NC
#define AN9  63  // NC
#define AN10  64 // NC
#define AN11  65 // NC
#define AN12  66 // NC
#define AN13  67 // NC
#define AN14  68 // NC
#define AN15  69 // NC

#define RELAY_APM1_PIN 47
#define RELAY_APM2_PIN 13

#define PIEZO_PIN AN5           //Last pin on the back ADC connector

// RADIANS
#define RADX100 0.000174532925f
#define DEGX100 5729.57795f


// EEPROM addresses
#define EEPROM_MAX_ADDR         4096
// parameters get the first 1536 bytes of EEPROM, remainder is for waypoints
#define WP_START_BYTE 0x600 // where in memory home WP is stored + all other
                            // WP
#define WP_SIZE 15

#define MAX_WAYPOINTS  (WP_START_BYTE / WP_SIZE) - 1 // -
                                                                          // 1
                                                                          // to
                                                                          // be
                                                                          // safe

// mark a function as not to be inlined
#define NOINLINE __attribute__((noinline))

// IMU selection
#define CONFIG_IMU_OILPAN  1
#define CONFIG_IMU_MPU6000 2
#define CONFIG_IMU_SITL    3
#define CONFIG_IMU_PX4     4

#define AP_BARO_BMP085    1
#define AP_BARO_MS5611    2
#define AP_BARO_PX4       3

#define AP_BARO_MS5611_SPI 1
#define AP_BARO_MS5611_I2C 2

// Error message sub systems and error codes
#define ERROR_SUBSYSTEM_MAIN                1
#define ERROR_SUBSYSTEM_RADIO               2
#define ERROR_SUBSYSTEM_COMPASS             3
#define ERROR_SUBSYSTEM_FAILSAFE_BATT       6
#define ERROR_SUBSYSTEM_FAILSAFE_GPS        7
#define ERROR_SUBSYSTEM_FAILSAFE_GCS        8
// general error codes
#define ERROR_CODE_ERROR_RESOLVED           0
#define ERROR_CODE_FAILED_TO_INITIALISE     1
// subsystem specific error codes -- radio
#define ERROR_CODE_RADIO_LATE_FRAME         2
// subsystem specific error codes -- failsafe_thr, batt, gps
#define ERROR_CODE_FAILSAFE_RESOLVED        0
#define ERROR_CODE_FAILSAFE_OCCURRED        1


// balance
#define LEFT_MOT_CH 0
#define RIGHT_MOT_CH 1

//AN0 = sonar
#define LEFT_DIR  AN1  // resistor, vdiv use, divider 1 closest to relay
#define LEFT_DIR_C AN0
#define RIGHT_DIR  AN2  // resistor, vdiv use, divider 2
#define RIGHT_DIR_C AN3

#endif // _DEFINES_H


