#include "pca9685.h"
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

#define SERVO_PIN 15
#define LEFT 400 //ultrasonic sensor facing right
#define CENTER 280//ultrasonic sensor facing front
#define RIGHT 160 //ultrasonic sensor facing left
#define TRIG_PIN 28 
#define ECHO_PIN 29 
#define OBSTACLE 20
#define SHORT_DELAY 200
#define MID_DELAY  300
#define LONG_DELAY 400

int fd;


void setup(){
    pinMode(LEFT_SIDE_IN_1,OUTPUT);
    pinMode(LEFT_SIDE_IN_2,OUTPUT);
    pinMode(RIGHT_SIDE_IN_1,OUTPUT);
    pinMode(RIGHT_SIDE_IN_2,OUTPUT);
    pinMode(TRIG_PIN,OUTPUT);
    pinMode(ECHO_PIN,INPUT);

    digitalWrite(LEFT_SIDE_IN_1,LOW);
    digitalWrite(LEFT_SIDE_IN_2,LOW);
    digitalWrite(RIGHT_SIDE_IN_1,LOW);
    digitalWrite(RIGHT_SIDE_IN_2,LOW);
}


int getDistance() {
        //Send trig pulse
        digitalWrite(TRIG_PIN, HIGH);
        delayMicroseconds(20);
        digitalWrite(TRIG_PIN, LOW);
 
        //Wait for echo start
        while(digitalRead(ECHO_PIN) == LOW);
 
        //Wait for echo end
        long startTime = micros();
        while(digitalRead(ECHO_PIN) == HIGH);
        long travelTime = micros() - startTime;
 
        int distanceCm = travelTime / 58;
 		if (distanceCm==0) distanceCm=1000;
        return distanceCm;
}
int main(void)
{
    	if(wiringPiSetup()==-1){
        	printf("setup wiringPi failed!\n");
        	printf("please check your setup\n");
        	return -1;
    	}
	setup();
	
	
	printf("Lesson 3: Obstacle Avoiding\n");
	
	// Setup with pinbase 300 and i2c location 0x40
	int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
	if (fd < 0)
	{
		printf("Error in pca9685 setup\n");
		return fd;
	}

    	bool obstacleOnLeft;
    	bool obstacleInMiddle;
    	bool obstacleOnRight;


	while (1)
	{
		pca9685PWMWrite(fd, SERVO_PIN, 0, LEFT);
		delay(MID_DELAY);
        	obstacleOnLeft = getDistance()<OBSTACLE;
		
		pca9685PWMWrite(fd, SERVO_PIN, 0, CENTER);
		delay(MID_DELAY);
		obstacleInMiddle = getDistance()<OBSTACLE;
		
		pca9685PWMWrite(fd, SERVO_PIN, 0, RIGHT);
		delay(MID_DELAY);
        	obstacleOnRight = getDistance()<OBSTACLE;

        	if (!obstacleOnLeft && obstacleInMiddle && obstacleOnRight)
		{
			printf("%d - %d - %d Hard left\n", obstacleOnLeft, obstacleInMiddle, obstacleOnRight);
			leftTurn(fd, LOW_SPEED, HIGH_SPEED);
		        delay(MID_DELAY);  
		        stop(fd);
		        delay(SHORT_DELAY);	
		} 
        	else if (!obstacleOnLeft && !obstacleInMiddle && obstacleOnRight)
		{
            		printf("%d - %d - %d Slight left\n", obstacleOnLeft, obstacleInMiddle, obstacleOnRight);
			leftTurn(fd, LOW_SPEED, MID_SPEED);
            		delay(MID_DELAY);  
            		stop(fd);
            		delay(SHORT_DELAY);		
		}
		else if ((!obstacleOnLeft && !obstacleInMiddle && !obstacleOnRight) || (!obstacleOnLeft && obstacleInMiddle && !obstacleOnRight) )
		{
			printf("%d - %d - %d Forward\n", obstacleOnLeft, obstacleInMiddle, obstacleOnRight);
			go_advance(fd,MID_SPEED);
            		delay(MID_DELAY);  
			stop(fd);
            		delay(SHORT_DELAY);	
		} 
        	else if (obstacleOnLeft && !obstacleInMiddle && !obstacleOnRight)
		{	
			printf("%d - %d - %d Slight right\n", obstacleOnLeft, obstacleInMiddle, obstacleOnRight);
			rightTurn(fd, MID_SPEED, LOW_SPEED);
            		delay(MID_DELAY);  
            		stop(fd);
            		delay(SHORT_DELAY);
		}
        	else if (obstacleOnLeft && obstacleInMiddle && !obstacleOnRight)
		{
			printf("%d - %d - %d Hard right\n", obstacleOnLeft, obstacleInMiddle, obstacleOnRight);
			rightTurn(fd, HIGH_SPEED, LOW_SPEED);
            		delay(MID_DELAY);  
            		stop(fd);
            		delay(SHORT_DELAY);	
		}
        	else if (obstacleOnLeft && obstacleInMiddle && obstacleOnRight) 
		{
            		printf("%d - %d - %d Dead end, turning back\n", obstacleOnLeft, obstacleInMiddle, obstacleOnRight);
			reverse(fd, LOW_SPEED);
            		delay(LONG_DELAY);  
            		stop(fd);
            		delay(SHORT_DELAY);	
		} 
		else if (obstacleOnLeft && !obstacleInMiddle && obstacleOnRight)
		{
            		printf("%d - %d - %d Fork in the road\n", obstacleOnLeft, obstacleInMiddle, obstacleOnRight);

            		if (rand()%2==0)
            		{
                		printf("Turning hard right\n",val);
                		rightTurn(fd, HIGH_SPEED, LOW_SPEED);
            		}
            		else
            		{
                		printf("Turning hard left\n",val);
                		leftTurn(fd, LOW_SPEED, HIGH_SPEED);
            		}
		}
	}
	return 0;
}
