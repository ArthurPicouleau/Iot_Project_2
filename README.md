# IOT Project : Dimitrios Primpas, Arthur Picouleau

Our project is based on motion recognition and in particular on taking into account a double tap between the user's thumb and index finger. To do this, we are using the accelerometer contained in the LSM6DS3 IMU, itself contained in the Seeed Xiao BLE nRF52840 Sense board.

To carry out this project, we decided to use the ArduinoIDE platform.
We coded 3 programs using the double tap functionality.

In order to run our codes, we first need to download the ```Seed Arduino LSM6DS3``` library.
To do this, go to ```Sketch``` > ```Include Library``` > ```Manage Libraries```.
This takes you to the Library Manager. Simply enter the name of the library: ```Seed Arduino LSM6DS3```. To run the code in the board you have to use the Upload button. 

In all our codes we have concentrated solely on the values given by the accelerometer on the Z axis. In fact, by wearing the card on the index finger like a ring and double-tapping between the thumb and index finger, we realised that only the Z component was greatly modified and allowed us to detect movement.

To detect double-tapping, we've developed a function called RisingEdge. The principle is based on rising edge detection. In our case, the rising edge we need to detect is when the Z-axis acceleration exceeds a limit that we've set beforehand. For the double tap to be effective, this limit must be exceeded twice within a certain time interval.

![Image1](/RisingEdge.png)
The graph shows a double tap at a sampling frequency of 500 Hz. 
In each of the 3 codes, to detect the double tap, ```t1-t0``` must be between 15 and 50 ms. In our codes ```t1``` and ```t0``` are called ```tempo[0]``` and ```tempo[1]```

When the code is uploaded to the card, wait a few seconds before starting to test the double tap or wait before thata LED is lit (red, green or blue). That means you can start experimenting.

# Code 1 : Control of a led

In this first program we control the red LED on the Seeed Xiao BLE nRF52840 Sense board. A double tap by the user turns the LED on and another turns it off.

# Code 2 : Changing the color

In this second program, we wanted to use the three LEDs on the board. To do this, we developed a program that allows the user to change the LED by double-tapping between his index finger and thumb.

# Code 3 : Control of the lighting up 
In the third program, we use the double tap to control how long the LED lights up. Each double tap increases the time when LED lights up.

## Part 4 : Demonstration video ##

[Demonstration video]
(https://youtu.be/pKcicKqbMaU)


