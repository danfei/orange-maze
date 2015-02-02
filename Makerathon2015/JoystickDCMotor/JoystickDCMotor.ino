#include <Makeblock.h>
#include <SoftwareSerial.h>
#include <Wire.h>


class SZDIYJoystick: public MeJoystick {
  public:
    SZDIYJoystick(uint8_t port): MeJoystick(port) {}
  
    int x;
    int y;
    
    void initRead() {
      x = this->readX();
      y = this->readY();
    }
    
    void readJoystick() {
 
      // read the both joystick axis values:
      int new_x = this->readX();  
      int new_y = this->readY(); 
    
      // print the results to the serial monitor:
      if (x != new_x || y != new_y) {
//        Serial.print("Joystick X = " );                       
//        Serial.print(new_x);   
//        
//        Serial.print("\t Joystick Y = " );                       
//        Serial.println(new_y);
        
        x = new_x;
        y = new_y;
      }
      
   }   
};


MeDCMotor motor(M1);
SZDIYJoystick joystick(PORT_8);
MeLimitSwitch limitSwitch(PORT_6);

void setup() {
  Serial.begin(9600);
  
  joystick.initRead();
  
}

void loop() {
  joystick.readJoystick();
  delay(10);
  
  if (limitSwitch.touched()) {
    motor.run(80);
    delay(1000);
    motor.stop();
  }
  
  int speedMotor = (joystick.y - 500) / 2;
  if (abs(speedMotor) < 50) {
    motor.stop();
  }
  else {
    motor.run(speedMotor);
  }
  
  Serial.print("speed=");
  Serial.print(speedMotor);
  Serial.print(" touch=");
  Serial.println(limitSwitch.touched() ? "on" : "off");
}


