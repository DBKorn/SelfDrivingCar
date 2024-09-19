#include "pca9685.h"
#include "ads7830.h"
#include <wiringPi.h>
#include "allMovement.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define PIN_BASE 300
#define HERTZ 50

#define ENABLE_A 0  //left motor speed pin ENABLE_A connect to PCA9685 port 0
#define ENABLE_B 1  //right motor speed pin ENABLE_B connect to PCA9685 port 1
#define LEFT_SIDE_IN_1 4  //Left motor leftSideIn1 connect to wPi pin# 4 
#define LEFT_SIDE_IN_2 5  //Left motor leftSideIn2 connect to wPi pin# 5
#define RIGHT_SIDE_IN_1 2  //right motor rightSideIn3 connect to wPi pin# 2 
#define RIGHT_SIDE_IN_2 3  //right motor rightSideIn4 connect to wPi pin# 3

#define LOW_SPEED 1000
#define MID_SPEED 2000
#define HIGH_SPEED 3000

//input pins on ads7830
#define LEFT_PHOTORESISTOR 0
#define RIGHT_PHOTORESISTOR 1

int fd;

int setup(){
    pinMode(LEFT_SIDE_IN_1,OUTPUT);
    pinMode(LEFT_SIDE_IN_2,OUTPUT);
    pinMode(RIGHT_SIDE_IN_1,OUTPUT);
    pinMode(RIGHT_SIDE_IN_2,OUTPUT);

    digitalWrite(LEFT_SIDE_IN_1,LOW);
    digitalWrite(LEFT_SIDE_IN_2,LOW);
    digitalWrite(RIGHT_SIDE_IN_1,LOW);
    digitalWrite(RIGHT_SIDE_IN_2,LOW);
    return 0;
}


float getVoltage(int channel){
    return (float) ads7830AnalogRead(channel)/255.0*3.3;
}

int main(){
  if(wiringPiSetup()==-1){
      printf("setup wiringPi failed!\n");
      printf("please check your setup\n");
      return -1;
  }
  // Setup with pinbase 300 and i2c location 0x40
	fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
	if (fd < 0)
	{
		printf("Error in pca9685 setup\n");
		return fd;
	}
	setup();


  float left;
  float right;

  while(true){
      left = getVoltage(LEFT_PHOTORESISTOR);
      right = getVoltage(RIGHT_PHOTORESISTOR);
      if (left <2.99 && right < 2.99)
      {
          forward(fd, MID_SPEED);
      }
      else if (abs(left-right)<.15)
      {
          stop(fd);
      }
      else if (left>3 || right>3)
      {
          if (left>right)
          {
              leftTurn(fd, LOW_SPEED, MID_SPEED);
          } 
          else if (left<right)
          {
              rightTurn(fd, MID_SPEED, LOW_SPEED);
          }
          else
          {
              forward(fd, HIGH_SPEED);
          }
        }
    }
}
