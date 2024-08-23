#include "pca9685.h"
#include "allMovement.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

const int pinBase = 300;
const int hertz = 50;
int fd;
 
 //define L298N control pins using wPi
const int enableA = 0;  //left motor speed pin ENA connect to PCA9685 port 0
const int enableB = 1;  //right motor speed pin ENB connect to PCA9685 port 1
const int leftSideIn1 = 4;  
const int leftSideIn2 = 5;  
const int rightSideIn3 = 2; 
const int rightSideIn4 = 3;


//define infrared tracking sensor wPi pin#
const int leftSensor = 21;
const int middleSensor = 22; 
const int rightSensor = 23; 

// Max pulse length out of 4096
const int highSpeed = 3000;
const int midSpeed = 2000;
const int lowSpeed = 1000;
const int shortDelay = 100;
const int midDelay = 200;
const int longDelay = 300;

void setup(){
    
    pinMode(leftSideIn1,OUTPUT);
    pinMode(leftSideIn2,OUTPUT);
    pinMode(rightSideIn3,OUTPUT);
    pinMode(rightSideIn4,OUTPUT);
 
    pinMode(leftSensor,INPUT);
    pinMode(middleSensor,INPUT);
    pinMode(rightSensor,INPUT);

    digitalWrite(leftSideIn1,LOW);
    digitalWrite(leftSideIn2,LOW);
    digitalWrite(rightSideIn3,LOW);
    digitalWrite(rightSideIn4,LOW);
}

int main(void)
{
    if(wiringPiSetup()==-1){
        printf("setup wiringPi failed!\n");
        return -1;
    }
	setup();

	printf("Line Tracking\n");
 
	// Setup with pinbase 300 and i2c location 0x40
    fd = pca9685Setup(pinBase, 0x40, hertz);
	if (fd < 0)
	{
		printf("Error in setup\n");
		return fd;
	}
    
    int isLeft;
    int isMiddle;
    int isRight;

     while (1)
     {
	isLeft = !digitalRead(leftSensor);
        isMiddle = !digitalRead(middleSensor);
        isRight = !digitalRead(rightSensor);


        if (isLeft && !isMiddle && !isRight)
        {
            printf("%d-%d-%d hard left\n",isLeft, isMiddle, isRight);
            leftTurn(fd, lowSpeed, highSpeed);
        }
        else if (isLeft && isMiddle && !isRight)
        {
            printf("%d-%d-%d Slight left\n",isLeft, isMiddle, isRight);
            leftTurn(fd, lowSpeed, midSpeed);
        }
        else if ( (!isLeft && isMiddle && !isRight)  || (isLeft && isMiddle && isRight) )
        {
            printf("%d-%d-%d Straight ahead\n",isLeft, isMiddle, isRight);
            forward(fd,midSpeed);
        }
        else if (isLeft && !isMiddle && !isRight)
        {
            printf("%d-%d-%d Slight right\n",isLeft, isMiddle, isRight);
            rightTurn(fd, midSpeed, lowSpeed);
        }
        else if (!isLeft && !isMiddle && isRight)
        {
            printf("%d-%d-%d Hard right\n",isLeft, isMiddle, isRight);
            rightTurn(fd, highSpeed, lowSpeed);
        }
        else if (!isLeft && !isMiddle && !isRight)
        {
            printf("%d-%d-%d Reverse to attempt to correct course\n", isLeft, isMiddle, isRight);
            stop(fd);
            reverse(fd, lowSpeed);
        }
 
    }
 
	return 0;
}
