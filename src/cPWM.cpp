///  Simple C++ class wrapper for beaglebone PWM eHRPWM interface
//          Some of this code has been taken from https://github.com/clausqr/beaglebone-cpp-PWM

#include "controller_test/cPWM.h"
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>

namespace cPWM {

    /**
     * This class wraps the PWMss of the beaglebone,
     * but it accesses the PWMss by means of the sysfs interface,
     * so probably other systems are supported as well.
     * The sysfs filenames are defined in pwm.h.
     * The constructor just opens the sysfs files but doesn't write anything,
     * so in order to properly use the PWMss you need to follow all the steps
     * (frequency, period, polarity) before calling run.
     *
     * WARNING: PIN MUX AND CLOCK SETTINGS SHOULD BE DONE BEFORE USING THIS CLASS. 
     *
     * @param[pwm_name]	       name of the pins of the PWM (check /lib/firmware, e.g.: pwm_test_P9_16.10).
     * @return		a cPWM object
     *
     */

     
    cPWM::cPWM(std::string pin_number)
    {
        std::stringstream export_str;
        std::stringstream sysfsfile_pin_state;
        std::stringstream sysfsfile_pwmchip;
        std::string pwm_name, pwmchip;
        int exportNumber;

        std::stringstream sysfsfile_duty_cycle;
        std::stringstream sysfsfile_duty_cycle_percent;

        std::stringstream sysfsfile_period;
        std::stringstream sysfsfile_freq;

        std::stringstream sysfsfile_polarity;
        std::stringstream sysfsfile_enable;

        if (pin_number == "P9_14" || pin_number == "P8_36")
        {
                pwm_name = "pwm-3:0";
                pwmchip = "pwmchip3"; exportNumber = 0;
        }
	    else if (pin_number == "P9_16" || pin_number == "P8_34")
        {
                pwm_name = "pwm-3:1";
                pwmchip = "pwmchip3"; exportNumber = 1;
        }
        else if (pin_number == "P9_22" || pin_number == "P9_31")
        {
                pwm_name = "pwm-1:0"; 
                pwmchip = "pwmchip1"; exportNumber = 0;
        }
        else if (pin_number == "P9_21" || pin_number == "P9_29")
        {
                pwm_name = "pwm-1:1";
                pwmchip = "pwmchip1"; exportNumber = 1;
        }
        else if (pin_number == "P8_19" || pin_number == "P8_45")
        {
                pwm_name = "pwm-6:0";
                pwmchip = "pwmchip6"; exportNumber = 0;
        }
        else if (pin_number == "P8_13" || pin_number == "P8_46")
        {
                pwm_name = "pwm-6:1"; 
                pwmchip = "pwmchip6"; exportNumber = 1;
        }
        else
        {
                pwm_name = "";
                std::cout << "Wrong PWM pin name" << std::endl;
        }

        // export pwmchip
        export_str << "/sys/class/pwm/" << pwmchip << "/export";
        std::ofstream exportpwm(export_str.str().c_str());
        exportpwm << exportNumber;
        exportpwm.close();

        // set the paths for initializations
        sysfsfile_pin_state << SYSFS_EHRPWM_PIN_STATE << pin_number << "_pinmux/state";
        sysfsfile_pwmchip << SYSFS_EHRPWM_PREFIX << "/" << pwmchip;

        sysfsfile_duty_cycle << SYSFS_EHRPWM_PREFIX << "/" << pwmchip << "/" << pwm_name << "/" << SYSFS_EHRPWM_DUTY_CYCLE;
        sysfsfile_duty_cycle_percent << SYSFS_EHRPWM_PREFIX << "/" << pwmchip << "/" << pwm_name << "/" << SYSFS_EHRPWM_DUTY_CYCLE_PERCENT;

        sysfsfile_period << SYSFS_EHRPWM_PREFIX << "/" << pwmchip << "/" << pwm_name << "/" << SYSFS_EHRPWM_PERIOD;
        sysfsfile_freq << SYSFS_EHRPWM_PREFIX << "/" << pwmchip << "/" << pwm_name << "/" << SYSFS_EHRPWM_FREQ;

        sysfsfile_polarity << SYSFS_EHRPWM_PREFIX << "/" << pwmchip << "/" << pwm_name << "/" << SYSFS_EHRPWM_POLARITY;
        sysfsfile_enable << SYSFS_EHRPWM_PREFIX << "/" << pwmchip << "/" << pwm_name << "/" << SYSFS_EHRPWM_ENABLE;

        // perform the initializations using the private variables
        sysfsfid_pin_state.open(sysfsfile_pin_state.str().c_str());
        sysfsfid_pin_state << "pwm" << std::endl;
        
        sysfsfid_duty_cycle.open(sysfsfile_duty_cycle.str().c_str());
        sysfsfid_duty_cycle_percent.open(sysfsfile_duty_cycle_percent.str().c_str());

        sysfsfid_period.open(sysfsfile_period.str().c_str());
        sysfsfid_freq.open(sysfsfile_freq.str().c_str());

        sysfsfid_polarity.open(sysfsfile_polarity.str().c_str());
        sysfsfid_enable.open(sysfsfile_enable.str().c_str());
    }

    // Set the duty cycle for the PWMss
    // @param[in]	nanoseconds:	duty cycle time in nanoseconds 
    void cPWM::Duty_cycle(unsigned int nanoseconds)
    {
        if(nanoseconds > cPWM::period)
            throw std::out_of_range("Duty_ns: ");

        cPWM::duty_cycle = nanoseconds;
        sysfsfid_duty_cycle << nanoseconds << std::endl;
    }

    // Set the duty cycle of the PWMss
    // @param[in]	percent:	duty cycle time in percent
    void cPWM::Duty_cycle_percent(unsigned int percent)
    {
        if(percent > 100)
            throw std::out_of_range("Duty_percent: ");

        sysfsfid_duty_cycle_percent << percent << std::endl;
    }


    // Set the period for the PWMss
    // @param[in]	nanoseconds:	period time in nanoseconds
    void cPWM::Period(unsigned int nanoseconds)
    {
        cPWM::period  = nanoseconds;
        cPWM::freq_Hz = 1000000000 / nanoseconds;
        sysfsfid_period << nanoseconds << std::endl;
    }

    // Set the period for the PWMss
    // @param[in]	freq_Hz:	PWM frequency in Hz
    void cPWM::Freq(unsigned int freq_Hz)
    {
        cPWM::freq_Hz = freq_Hz;
        cPWM::period  = 1000000000 / freq_Hz;
        sysfsfid_freq << freq_Hz<< std::endl;
    }

    // Set the polarity for the PWMss
    // @param[in]	polarity  polarity
    void cPWM::Polarity(int polarity)
    {
        switch (polarity)
        {
            case 1:  sysfsfid_polarity << 1 << std::endl;
                     break;
            case 0:  sysfsfid_polarity << 0 << std::endl;
                     break;
        }
        cPWM::polarity = polarity;
    }

    // Set the PWM to run status
    void cPWM::Enable()
    {
        sysfsfid_enable << "1" << std::endl;
        cPWM::enable = 1;
    }

    // Stop the PWM
    void cPWM::Disable()
    {
        sysfsfid_enable << "0" << std::endl;
        cPWM::enable = 0;
    }

    // cPWM Destructor, stops the PWMss
    cPWM::~cPWM()
    {
        sysfsfid_enable << "0" << std::endl;
        sysfsfid_pin_state << "default" << std::endl;
        std::cout<< "PWM end" << std::endl;
    }

} /* namespace cPWM */
