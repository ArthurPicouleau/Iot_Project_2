# IOT Project : Dimitrios Primpas, Arthur Picouleau

Our project is based on motion recognition and in particular on taking into account a double tap between the user's thumb and index finger. To do this, we are using the accelerometer contained in the LSM6DS3 IMU, itself contained in the Seeed Xiao BLE nRF52840 Sense board.

To carry out this project, we decided to use the ArduinoIDE platform.
We coded 3 programs using the double tap functionality.

In order to run our codes, we first need to download the ```Seed Arduino LSM6DS3``` library.
To do this, go to ```Sketch``` > ```Include Library``` > ```Manage Libraries```.
This takes you to the Library Manager. Simply enter the name of the library: ```Seed Arduino LSM6DS3```. To run the code in the board you have to use the Upload button. 

In all our codes we have concentrated solely on the values given by the accelerometer on the Z axis. In fact, by wearing the card on the index finger like a ring and double-tapping between the thumb and index finger, we realised that only the Z component was greatly modified and allowed us to detect movement.

# Code 1 : Control of a led

In this first program we control the red LED on the Seeed Xiao BLE nRF52840 Sense board. A double tap by the user turns the LED on and another turns it off.

# Code 2 : Changing the color

In this second program, we wanted to use the three LEDs on the board. To do this, we developed a program that allows the user to change the LED by double-tapping between his index finger and thumb.

# Code 3 : Control of the blink 

In this third and final code, we decided to play with the flashing frequency of the red LED. Each double tap reduces the delay between the moment when the LED lights up and the moment when it goes out.

