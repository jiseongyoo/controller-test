///     Some of this code has been taken from https://github.com/clausqr/beaglebone-cpp-PWM

#ifndef CPWM_H_
#define CPWM_H_

#include <fstream>
#include <sstream>


#define CAPEMGR_SLOT "--"
#define SYSFS_EHRPWM_PIN_STATE "/sys/devices/platform/ocp/ocp:"
#define SYSFS_EHRPWM_PREFIX "/sys/class/pwm"
#define SYSFS_EHRPWM_DUTY_CYCLE "duty_cycle"
#define SYSFS_EHRPWM_DUTY_CYCLE_PERCENT "duty_cycle_percent"
#define SYSFS_EHRPWM_PERIOD "period"
#define SYSFS_EHRPWM_FREQ "freq"
#define SYSFS_EHRPWM_POLARITY "polarity"
#define SYSFS_EHRPWM_ENABLE "enable"

namespace cPWM {

    class cPWM {

        public:
            enum Polarity
            {
                ActiveHigh,
                ActiveLow
            };

        private:
            int id;
            int duty_cycle;
            int period;
            int freq_Hz;
            //enum cPWM::Polarity polarity;
            int polarity;
            int enable;

            std::ofstream sysfsfid_pin_state;
            std::ofstream sysfsfid_pwmchip;

            std::ofstream sysfsfid_duty_cycle;
            std::ofstream sysfsfid_duty_cycle_percent;
            std::ofstream sysfsfid_period;
            std::ofstream sysfsfid_freq;

            std::ofstream sysfsfid_polarity;
            std::ofstream sysfsfid_enable;

        public:

            cPWM(std::string pin_number);
            virtual ~cPWM();

            void Duty_cycle(unsigned int nanoseconds);
            void Duty_cycle_percent(unsigned int percent);  //TODO: check if floats are possible

            void Period(unsigned int nanoseconds);
            void Freq(unsigned int freq_Hz);

            //void Polarity(cPWM::Polarity polarity);
            void Polarity(int polarity);
            void Enable();
            void Disable();
    };

} /* namespace cPWM */
#endif /* CPWM_H_ */
