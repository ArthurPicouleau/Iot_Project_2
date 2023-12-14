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
#define MONOSTABLE_DELAY 100

bool ledState=false;
int time=MONOSTABLE_DELAY;
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



void Blink() // Increasing the time when the led is turning on
{
  digitalWrite(LED_BUILTIN, LOW);
  delay(time);//We increase the delay with each double tap
  digitalWrite(LED_BUILTIN, HIGH);
  delay(time);
  time=time+100;
  if (time>=1000){
    time=MONOSTABLE_DELAY;
  }
  delay(DEBOUNCE);// We have created a delay to avoid taking into account the user's parasitic movements.
}


void risingEdge(){ // Detect a tap of the user
    unsigned long interval;
    if (state==true && statePrec==false){
        tempo[0]=tempo[1];//first double tap
        tempo[1]=millis();// second double tap
        interval=tempo[1]-tempo[0]; // We calculate the time interval between the two taps
        if (interval>LOW_TIME && interval<HIGH_TIME){ // Detect the double tap of the user
          Serial.println(interval);
          Blink();
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
          statePrec=state;
          delay(INTERVAL_MS);
}
