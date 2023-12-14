// XIAO BLE Sense LSM6DS3 Accelerometer Raw Data

#include "LSM6DS3.h"
#include "Wire.h"

//Create a instance of class LSM6DS3
LSM6DS3 myIMU(I2C_MODE, 0x6A);  //I2C device address 0x6A

#define CONVERT_G_TO_MS2 9.80665f
#define INTERVAL_MS 2 //500Hz
#define DEBOUNCE 500
#define LOW_TIME 15
#define HIGH_TIME 50
#define Z_AXIS_LEVEL 12


bool ledState=false;

unsigned long tempo[2] = {0};

bool state=false;
bool statePrec=false;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); //Configuration of the red led
  Serial.begin(115200);
  while (!Serial)
    ;

  if (myIMU.begin() != 0) { // Initialisation of the acceleromter
    Serial.println("Device error");
  } else {
    Serial.println("Device OK!");
  }
  digitalWrite(LED_BUILTIN, HIGH); // Initialisation of the led in HIGH state
}


void flipFlop()
{
     if (ledState){
         ledState=false;
         digitalWrite(LED_BUILTIN, HIGH);
     }
     else{
         ledState=true;
         digitalWrite(LED_BUILTIN, LOW);
     }
     delay(DEBOUNCE);// We have created a delay to avoid taking into account the user's parasitic movements.
}


void risingEdge(){ // Detect a tap of the user
    unsigned long interval;
    if (state==true && statePrec==false){
        tempo[0]=tempo[1];//first double tap
        tempo[1]=millis();//second double ta
        interval=tempo[1]-tempo[0]; // We calculate the time interval between the two taps
        if (interval>LOW_TIME && interval<HIGH_TIME){ // Detect the double tap of the user
          Serial.println(interval);
          flipFlop();
        }
    }
}
void loop() {
        float zAxis;
        zAxis=myIMU.readFloatAccelZ(); // We recover the values give by the accelorometer on the z axis
          if ((zAxis * CONVERT_G_TO_MS2) > Z_AXIS_LEVEL ) { //Detection of the user's tap
              state=true;
          }
          else{
              state=false;
          }
          risingEdge();
          //Serial.println(state);
          statePrec=state;
          delay(INTERVAL_MS);
}
