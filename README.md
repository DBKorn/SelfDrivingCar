# SelfDrivingCar
A self driving car with various modes, made with a raspberry pi. All files will be uploaded as I complete them, in whichever order I happen to do so

The modes are/will be:<br/>
  -Line tracking<br/>
  -Obstacle avoiding<br/>
  -Light tracking<br/>
  -Remote control<br/>
  
The allMovements.c file is a library for all the methods that control the car's movements (go forwrds turn right/left etc)<br/>

A L298N motor driver is used to control the speed and direction of the motors.<br/>

Line tracking mode: The car will follow a path marked by a line drawn the ground. It uses an infrared tracking sensor to keep track of the line. Input is read through GPIO pins and the car moves accordingly.<br/>

Obstacle avoiding mode: The car will drive freely until it runs into some obstacle and will avoid it. It uses a HC-SR04 ultrasonic module to measure how far away obstacles are. It sits atop a servo so it can rotate right and left to find an obstacle free path.<br/>

Light tracking mode: The car will follow the light shined by a flashlight or similar device. It must be placed in a darkened room for best results. It uses two photoresistors mounted on the front corners of the car. It measures the light, compares which side is brighter, and moves accordingly. The photoresistors are connected to an ADC7830 to read the exact voltage so we will know which side has the brighter light. <br/>
