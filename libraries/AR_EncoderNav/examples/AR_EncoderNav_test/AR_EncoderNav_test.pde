// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: t -*-

#include <AP_Common.h>
#include <AP_Progmem.h>
#include <AP_Math.h>            // ArduPilot Mega Vector/Matrix math Library
#include <AP_Param.h>
#include <AP_HAL.h>
#include <AP_HAL_AVR.h>

#include <AP_GPS.h>             // ArduPilot GPS library
#include <AP_ADC.h>             // ArduPilot Mega Analog to Digital Converter Library
#include <AP_Baro.h>            // ArduPilot Mega Barometer Library
#include <Filter.h>
#include <AP_Compass.h>         // ArduPilot Mega Magnetometer Library
#include <AP_Declination.h>
#include <AP_InertialSensor.h>  // ArduPilot Mega Inertial Sensor (accel & gyro) Library
#include <AP_AHRS.h>
#include <AP_Airspeed.h>
#include <AC_PID.h>             // PID library
#include <APM_PI.h>             // PID library
#include <AP_Buffer.h>          // ArduPilot general purpose FIFO buffer

#include <AR_EncoderNav.h>
const AP_HAL::HAL& hal = AP_HAL_BOARD_DRIVER;

#if CONFIG_HAL_BOARD == HAL_BOARD_APM2

#define A_LED_PIN 27
#define C_LED_PIN 25
AP_InertialSensor_MPU6000 ins;
AP_Baro_MS5611 baro(&AP_Baro_MS5611::spi);

#else

#define A_LED_PIN 37
#define C_LED_PIN 35
AP_ADC_ADS7844 adc;
AP_InertialSensor_Oilpan ins(&adc);
AP_Baro_BMP085 baro;
#endif

GPS *gps;
AP_GPS_Auto auto_gps(&gps);

AP_Compass_HMC5843 compass;
AP_AHRS_DCM ahrs(&ins, gps);

AR_EncoderNav encoder_nav(&ahrs, &gps);

uint32_t last_update;

static void flash_leds(bool on) {
    hal.gpio->write(A_LED_PIN, on);
    hal.gpio->write(C_LED_PIN, ~on);
}

void setup(void)
{
    hal.console->println_P(PSTR("AR_encoder_nav test startup..."));
    hal.gpio->pinMode(A_LED_PIN, GPIO_OUTPUT);
    hal.gpio->pinMode(C_LED_PIN, GPIO_OUTPUT);

    gps = &auto_gps;
    gps->init(hal.uartB, GPS::GPS_ENGINE_AIRBORNE_2G);

    ins.init(AP_InertialSensor::COLD_START,
			 AP_InertialSensor::RATE_100HZ,
			 flash_leds);

    ahrs.set_compass(&compass);

    last_update = hal.scheduler->millis();

    encoder_nav.init();
    encoder_nav.set_velocity(0,0);
    encoder_nav.set_current_position(0,0);
}

void loop(void)
{
    hal.scheduler->delay(20);
    gps->update();
    ahrs.update();
    uint32_t currtime = hal.scheduler->millis();
    float dt = (currtime - last_update) / 1000.0f;
    last_update = currtime;
    encoder_nav.update(dt);

    float dx =  encoder_nav.get_latitude_diff();
    float dy =  encoder_nav.get_longitude_diff();
    float velx =  encoder_nav.get_latitude_velocity();
    float vely =  encoder_nav.get_longitude_velocity();

    hal.console->printf_P(
            PSTR("inertial nav pos: (%f,%f) velocity: (%f, %f)\r\n"),
            dx, dy, velx, vely);
}

AP_HAL_MAIN();
