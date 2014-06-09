
#ifndef __AP_HAL_LINUX_RCOUTPUT_H__
#define __AP_HAL_LINUX_RCOUTPUT_H__

#include <AP_HAL_Linux.h>
#define PRUSS_SHAREDRAM_BASE     0x4a310000
#define MAX_PWMS                 12
#define PWM_CMD_MAGIC            0xf00fbaaf
#define PWM_REPLY_MAGIC          0xbaaff00f
#define TICK_PER_US              200
#define TICK_PER_S               200000000
#define PWM_CMD_CONFIG	         0	/* full configuration in one go */
#define PWM_CMD_ENABLE	         1	/* enable a pwm */
#define PWM_CMD_DISABLE	         2	/* disable a pwm */
#define PWM_CMD_MODIFY	         3	/* modify a pwm */
#define PWM_CMD_SET	         4	/* set a pwm output explicitly */
#define PWM_CMD_CLR	         5	/* clr a pwm output explicitly */
#define PWM_CMD_TEST	         6	/* various crap */

class Linux::LinuxRCOutput : public AP_HAL::RCOutput {
    void     init(void* machtnichts);
    void     set_freq(uint32_t chmask, uint16_t freq_hz);
    uint16_t get_freq(uint8_t ch);
    void     enable_ch(uint8_t ch);
    void     disable_ch(uint8_t ch);
    void     write(uint8_t ch, uint16_t period_us);
    void     write(uint8_t ch, uint16_t* period_us, uint8_t len);
    uint16_t read(uint8_t ch);
    void     read(uint16_t* period_us, uint8_t len);

private:
    uint32_t period[MAX_PWMS];
    uint32_t pwm_hi[MAX_PWMS];
    struct pwm_multi_config {
       uint32_t enmask;        /* enable mask */
       uint32_t offmsk;        /* state when pwm is off */
       uint32_t hilo[MAX_PWMS][2];
    };

    struct pwm_cmd {
       uint32_t magic;
       uint8_t cmd;
       uint8_t pwm_nr; /* in case it is required */
       uint8_t pad[2];
       union {
          struct pwm_multi_config cfg;
          uint32_t hilo[2];
       }u;
    };

    struct pwm_cmd *sharedMem_cmd;

};

#endif // __AP_HAL_LINUX_RCOUTPUT_H__
