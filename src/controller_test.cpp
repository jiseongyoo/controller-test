/*
 *	Title: DC Motor controller test on Beaglebone Black
 *	Author: Jiseong Yoo @ Colorado School of Mines
 *
 *	Description:
 *	 This program controls 4 DC motor or uses GPIO pins in Beaglebone Black.
 *	 User can select test mode, PWM or GPIO.
 */

#include <ros/ros.h>
// #include <joint_trajectory_controller/hardware_interface_adapter.h>
#include "controller_test/cPWM.h"
#include "controller_test/eqep.h"
#include "controller_test/GPIOConst.h"
#include "controller_test/GPIOManager.h"
#include <iostream>
#include <unistd.h>

//  Motor0 running test; standby = Pin8_15, dirA = Pin8_9, dirB = Pin8_14, enable = Pin8_28, PWM = Pin8_13
#define MOTOR_STBY "P8_15"
#define MOTOR_ENABLE  "P8_28"

#define MOTOR_3_PWM   "P9_14"
#define MOTOR_3_DIR1  "P9_12"
#define MOTOR_3_DIR2  "P9_11"

#define MOTOR_2_PWM   "P9_16"
#define MOTOR_2_DIR1  "P9_17"
#define MOTOR_2_DIR2  "P9_18"

#define MOTOR_1_PWM   "P9_19"
#define MOTOR_1_DIR1  "P9_18"
#define MOTOR_1_DIR2  "P9_17"

#define MOTOR_0_PWM   "P8_13"
#define MOTOR_0_DIR1  "P8_14"
#define MOTOR_0_DIR2  "P8_9"

#define TIME_ns (1)
#define TIME_us (1000)
#define TIME_ms (1000000)
#define TIME_s  (1000000000)

struct JointState { double joint1;};
using namespace std;

int main(int argc, char **argv)
{
  // Test option, m:Motor, p:PWM, g:GPIO
  char option;
  bool quite = false;
  string aux;
  int pin, motor;
  float pwm_duty_cycle;
  GPIO::GPIOManager* gp=NULL;
  cPWM::cPWM* a;
  
  
  while(!quite){
    cout << "select test option (m:Motor, p:PWM, g:GPIO, q:Quite): ";
    cin >> option;
    
    switch (option){
      case 'm':
        cout << "Hello test" << endl;
        cout << "Motor number (0~3): ";
        cin >>motor;
        cout << "PWM duty cycle (-1 ~ 1): ";
        cin >>pwm_duty_cycle;

        gp = GPIO::GPIOManager::getInstance();
        // Motor standby set
        pin = GPIO::GPIOConst::getInstance()->getGpioByKey(MOTOR_STBY);
        gp->setDirection(pin, GPIO::OUTPUT);
        gp->setValue(pin, GPIO::HIGH);
        cout << "MOTOR0 Standby : High" << endl;
        
        // Motor enable set
        pin = GPIO::GPIOConst::getInstance()->getGpioByKey(MOTOR_ENABLE);
        gp->setDirection(pin, GPIO::OUTPUT);
        gp->setValue(pin, GPIO::HIGH);
        cout << "MOTOR0 Enable : High" << endl;
        
        switch (motor){
          case 0:
            // Motor0 direction set
            aux = MOTOR_0_PWM;
            if (pwm_duty_cycle >= 0){ // CCW
              pin = GPIO::GPIOConst::getInstance()->getGpioByKey(MOTOR_0_DIR1);
              gp->setDirection(pin, GPIO::OUTPUT);
              gp->setValue(pin, GPIO::LOW);
              cout <<"MOTOR0_DIR1: Low"<<endl;
              pin = GPIO::GPIOConst::getInstance()->getGpioByKey(MOTOR_0_DIR2);
              gp->setDirection(pin, GPIO::OUTPUT);
              gp->setValue(pin, GPIO::HIGH);
              cout <<"MOTOR0_DIR2: High"<<endl;
            }else{  // CW
              pin = GPIO::GPIOConst::getInstance()->getGpioByKey(MOTOR_0_DIR1);
              gp->setDirection(pin, GPIO::OUTPUT);
              gp->setValue(pin, GPIO::HIGH);
              cout <<"MOTOR0_DIR1: High"<<endl;
              pin = GPIO::GPIOConst::getInstance()->getGpioByKey(MOTOR_0_DIR2);
              gp->setDirection(pin, GPIO::OUTPUT);
              gp->setValue(pin, GPIO::LOW);
              cout <<"MOTOR0_DIR2: Low"<<endl;
            }
            break;
          case 1:
            // Motor1 direction set
            aux = MOTOR_1_PWM;
            if (pwm_duty_cycle >= 0){ // CCW
              pin = GPIO::GPIOConst::getInstance()->getGpioByKey(MOTOR_1_DIR1);
              gp->setDirection(pin, GPIO::OUTPUT);
              gp->setValue(pin, GPIO::LOW);
              cout <<"MOTOR1_DIR1: Low"<<endl;
              pin = GPIO::GPIOConst::getInstance()->getGpioByKey(MOTOR_1_DIR2);
              gp->setDirection(pin, GPIO::OUTPUT);
              gp->setValue(pin, GPIO::HIGH);
              cout <<"MOTOR1_DIR2: High"<<endl;
            }else{  // CW
              pin = GPIO::GPIOConst::getInstance()->getGpioByKey(MOTOR_1_DIR1);
              gp->setDirection(pin, GPIO::OUTPUT);
              gp->setValue(pin, GPIO::HIGH);
              cout <<"MOTOR1_DIR1: High"<<endl;
              pin = GPIO::GPIOConst::getInstance()->getGpioByKey(MOTOR_1_DIR2);
              gp->setDirection(pin, GPIO::OUTPUT);
              gp->setValue(pin, GPIO::LOW);
              cout <<"MOTOR1_DIR2: Low"<<endl;
            }
            break;
          case 2:
            // Motor2 direction set
            aux = MOTOR_2_PWM;
            if (pwm_duty_cycle >= 0){ // CCW
              pin = GPIO::GPIOConst::getInstance()->getGpioByKey(MOTOR_2_DIR1);
              gp->setDirection(pin, GPIO::OUTPUT);
              gp->setValue(pin, GPIO::LOW);
              cout <<"MOTOR2_DIR1: Low"<<endl;
              pin = GPIO::GPIOConst::getInstance()->getGpioByKey(MOTOR_2_DIR2);
              gp->setDirection(pin, GPIO::OUTPUT);
              gp->setValue(pin, GPIO::HIGH);
              cout <<"MOTOR2_DIR2: High"<<endl;
            }else{  // CW
              pin = GPIO::GPIOConst::getInstance()->getGpioByKey(MOTOR_2_DIR1);
              gp->setDirection(pin, GPIO::OUTPUT);
              gp->setValue(pin, GPIO::HIGH);
              cout <<"MOTOR2_DIR1: High"<<endl;
              pin = GPIO::GPIOConst::getInstance()->getGpioByKey(MOTOR_2_DIR2);
              gp->setDirection(pin, GPIO::OUTPUT);
              gp->setValue(pin, GPIO::LOW);
              cout <<"MOTOR2_DIR2: Low"<<endl;
            }
            break;
          case 3:
            // Motor3 direction set
            aux = MOTOR_3_PWM;
            if (pwm_duty_cycle >= 0){ // CCW
              pin = GPIO::GPIOConst::getInstance()->getGpioByKey(MOTOR_3_DIR1);
              gp->setDirection(pin, GPIO::OUTPUT);
              gp->setValue(pin, GPIO::LOW);
              cout <<"MOTOR3_DIR1: Low"<<endl;
              pin = GPIO::GPIOConst::getInstance()->getGpioByKey(MOTOR_3_DIR2);
              gp->setDirection(pin, GPIO::OUTPUT);
              gp->setValue(pin, GPIO::HIGH);
              cout <<"MOTOR3_DIR2: High"<<endl;
            }else{  // CW
              pin = GPIO::GPIOConst::getInstance()->getGpioByKey(MOTOR_3_DIR1);
              gp->setDirection(pin, GPIO::OUTPUT);
              gp->setValue(pin, GPIO::HIGH);
              cout <<"MOTOR3_DIR1: High"<<endl;
              pin = GPIO::GPIOConst::getInstance()->getGpioByKey(MOTOR_3_DIR2);
              gp->setDirection(pin, GPIO::OUTPUT);
              gp->setValue(pin, GPIO::LOW);
              cout <<"MOTOR3_DIR2: Low"<<endl;
            }
            break;
          default:
            cout <<"Wrong motor number"<<endl;
            break;
        }
        
        // Motor PWM set
        a = new cPWM::cPWM(aux);

        a->Period(1*TIME_ms);
        a->Duty_cycle(abs(pwm_duty_cycle)*TIME_ms);
        a->Polarity(1);
        
        cout << aux << " PWM enable" << endl;
        a->Enable();
        usleep(5*TIME_s);
        cout << aux << " PWM disable" << endl;
        a->Disable();
        
        delete a;
        
        break;
        
      case 'g':
        //  GPIO test
        cout << "Hello GPIO test" << endl;
        cout << "Put GPIO pin ";
        cin >> aux;
        
        gp = GPIO::GPIOManager::getInstance();
        pin = GPIO::GPIOConst::getInstance()->getGpioByKey(aux.c_str());
        gp->setDirection(pin, GPIO::OUTPUT);
        
        cout << aux << " High" << endl;
        gp->setValue(pin, GPIO::HIGH);
        sleep(2);
        cout << aux << " Low" << endl;
        gp->setValue(pin, GPIO::LOW);
        sleep(2);
        
        gp->~GPIOManager();
        cout <<"Test ends"<<endl;
        break;
      
      case 'p':
        //  PWM test
        cout << "Hello PWM Test" << endl;
        cout << "Put PWM pin ";
        cin >> aux;
        
        a = new cPWM::cPWM(aux);

        a->Period(1000000000);	// 200000ns = 200us = 0.2ms = 5000hz
        a->Duty_cycle(500000000);	// 50% duty cycle
        a->Polarity(1);
        
        cout << aux << " PWM enable" << endl;
        a->Enable();
        usleep(10000000);
        cout << aux << " PWM disable" << endl;
        a->Disable();
        
        delete a;
        cout <<"Test ends"<< endl;
        break;
        
      case 'q':
        cout <<"Quite the test"<<endl;
        quite = true;
        break;
        
      default:
        cout <<"Wrong test option"<<endl;
        break;
	  }
	}
  
  
  eQEP eqep2b("eqep2b", eQEP::eQEP_Mode_Absolute);
    
  // Set the unit time period to 100,000,000 ns, or 0.1 seconds
  eqep2b.set_period(100000000L);

  // Query back the period
  std::cout << "[eQEP2b] Period = " << eqep2b.get_period() << " ns" << std::endl;

  // Read position indefintely
  while(1)
  {
  std::cout << "[eQEP2b] Position = " << eqep2b.get_position() << std::endl;
  }
  
  return 0;
}
