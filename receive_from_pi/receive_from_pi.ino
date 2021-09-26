#include<SPI.h>
#include<RF24.h>
//#include <Servo.h>
#include "HCPCA9685.h"
#define  I2CAdd 0x40
HCPCA9685 HCPCA9685(I2CAdd);



RF24 radio(9,10);

void setup(void) {
  HCPCA9685.Init(SERVO_MODE);
  
while(!Serial);  
  Serial.begin(9600);

 radio.begin();
 radio.setPALevel(RF24_PA_MAX);
 radio.setChannel(0x77);
 radio.openWritingPipe(0xF0F0F0F0E1LL);
 
 const uint64_t pipe = 0xE8E8F0F0E1LL;  //0xE8E8F0F0E1LL
 radio.openReadingPipe(1,pipe);

 radio.enableDynamicPayloads();
 radio.powerUp();
 radio.startListening();
}

void loop(void) {
 unsigned int Pos;
// HCPCA9685.Sleep(false);
//
//           for(Pos = 10; Pos < 450; Pos++)
//            {
//              HCPCA9685.Servo(0, Pos);
//              HCPCA9685.Servo(1, Pos);
//              HCPCA9685.Servo(2, Pos);
//          
//              delay(40);
//            }
//            
//            for(Pos = 450; Pos >= 10; Pos--)
//            {
//              HCPCA9685.Servo(0, Pos);
//              HCPCA9685.Servo(1, Pos);
//              HCPCA9685.Servo(2, Pos);
//          
//              delay(40);
//            }
//            HCPCA9685.Sleep(true);

 char receivedMessage[32]={0}; 
 if (radio.available()){
  
  radio.read(receivedMessage, sizeof(receivedMessage));
  String stringMessage(receivedMessage);
  Serial.println(receivedMessage);
  Serial.println(stringMessage);

  if(stringMessage == "true" ){ //如果监测到motion，舵机转动
        Serial.println("Motion detected");
        HCPCA9685.Sleep(false);

           for(Pos = 10; Pos < 300; Pos++)
            {
              HCPCA9685.Servo(0, Pos);
              HCPCA9685.Servo(1, Pos);
              HCPCA9685.Servo(2, Pos);
          
              delay(1000);
            }
            
            for(Pos = 300; Pos >= 10; Pos--)
            {
              HCPCA9685.Servo(0, Pos);
              HCPCA9685.Servo(1, Pos);
              HCPCA9685.Servo(2, Pos);
          
              delay(1000);
            }
            HCPCA9685.Sleep(true);

       }
       
    else if (stringMessage == "fals" ){
        Serial.println("No motion");
   }

delay (1000);


}
}
