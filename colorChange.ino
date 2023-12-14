#include "LSM6DS3.h"
#include "Wire.h"

//Create a instance of class LSM6DS3
LSM6DS3 myIMU(I2C_MODE, 0x6A);  //I2C device address 0x6A

#define CONVERT_G_TO_MS2 9.80665f
#define INTERVAL_MS 2 //500Hz
#define DEBOUNCE 500
#define LOW_TIME 20
#define HIGH_TIME 50
#define Z_AXIS_LEVEL 12


unsigned long tempo[2] = {0};

int sequence[4][3]={{LOW,HIGH,HIGH}, // Creation of the sequence of lighting of the 3 leds
                      {HIGH,LOW,HIGH},
                      {HIGH,HIGH,LOW},
                      {HIGH,HIGH,HIGH}};

bool state=false;
bool statePrec=false;
byte mode=0;

void setup() {
   pinMode(LED_BUILTIN, OUTPUT); //Configuration of the red led
   pinMode(LED_GREEN, OUTPUT); //Configuration of the green led
   pinMode(LED_BLUE, OUTPUT); //Configuration of the blue led

   Serial.begin(115200);
   while (!Serial)
     ;

   if (myIMU.begin() != 0) {
     Serial.println("Device error");
   } else {
     Serial.println("Device OK!");
   }
   digitalWrite(LED_BUILTIN, HIGH);
   digitalWrite(LED_GREEN, HIGH);
   digitalWrite(LED_BLUE, HIGH);
  }

void colorChange()
{
     digitalWrite(LED_BUILTIN,sequence[mode][0]);
     digitalWrite(LED_GREEN, sequence[mode][1]);
     digitalWrite(LED_BLUE, sequence[mode][2]);
     mode++;
     mode=mode%3;
     delay(DEBOUNCE);
}

void risingEdge(){
     unsigned long interval;
     if (state==true && statePrec==false){
         tempo[0]=tempo[1];//first double tap
         tempo[1]=millis();//second double tap
         interval=tempo[1]-tempo[0];
         if (interval>LOW_TIME && interval<HIGH_TIME){
             colorChange();
         }
     }

}

void loop() {
         float zAxis;
         zAxis=myIMU.readFloatAccelZ();
         //Serial.println(zAxis * CONVERT_G_TO_MS2, 4);

           if ((zAxis * CONVERT_G_TO_MS2) > Z_AXIS_LEVEL ) {
               state=true;
           }
           else{
               state=false;
           }
           risingEdge();
           statePrec=state;
           delay(INTERVAL_MS);
}
