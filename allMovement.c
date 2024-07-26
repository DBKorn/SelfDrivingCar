#include "pca9685.h"
#include <wiringPi.h>
#include "allMovement.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * wiringPi C library use different GPIO pin number system from BCM pin numberwhich are often used by Python, 
 * you can lookup BCM/wPi/Physical pin relation by following Linux command : gpio readall
 */
const int enableA = 0;  //left motor speed pin ENA connect to PCA9685 port 0
const int enableB = 1;  //right motor speed pin ENB connect to PCA9685 port 1
const int leftSideIn1 = 4;  //Left motor leftSideIn1 connect to wPi pin# 4 (Physical 16,BCM GPIO 23)
const int leftSideIn2 = 5;  //Left motor leftSideIn2 connect to wPi pin# 5 (Physical 18,BCM GPIO 24)
const int rightSideIn3 = 2;  //right motor rightSideIn3 connect to wPi pin# 2 (Physical 13,BCM GPIO 27)
const int rightSideIn4 = 3;  //right motor rightSideIn4 connect to wPi pin# 3 (Physical 15,BCM GPIO 22)
const int SPEED = 2000;

// initialize  leftSideIn1, leftSideIn2, rightSideIn3, rightSideIn4 
void setup(){
 pinMode(leftSideIn1,OUTPUT);
 pinMode(leftSideIn2,OUTPUT);
 pinMode(rightSideIn3,OUTPUT);
 pinMode(rightSideIn4,OUTPUT);
 
 digitalWrite(leftSideIn1,LOW);
 digitalWrite(leftSideIn2,LOW);
 digitalWrite(rightSideIn3,LOW);
 digitalWrite(rightSideIn4,LOW);
}
void reverse(int fd,int speed){
    digitalWrite(leftSideIn1,HIGH);
    digitalWrite(leftSideIn2,LOW);
    digitalWrite(rightSideIn3,HIGH);
    digitalWrite(rightSideIn4,LOW); 
    pca9685PWMWrite(fd, enableA, 0, speed);
    pca9685PWMWrite(fd, enableb, 0, speed);
}
void forward(int fd,int speed){
    digitalWrite(leftSideIn1,LOW);
    digitalWrite(leftSideIn2,HIGH);
    digitalWrite(rightSideIn3,LOW);
    digitalWrite(rightSideIn4,HIGH); 
    pca9685PWMWrite(fd, enableA, 0, speed);
    pca9685PWMWrite(fd, enableB, 0, speed);
}

void rightTurn(int fd,int left_speed,int right_speed){
    digitalWrite(leftSideIn1,LOW);
    digitalWrite(leftSideIn2,HIGH);
    digitalWrite(rightSideIn3,HIGH);
    digitalWrite(rightSideIn4,LOW); 
    pca9685PWMWrite(fd, ENA, 0, left_speed);
    pca9685PWMWrite(fd, ENB, 0, right_speed);

}
void leftTurn(int fd,int left_speed,int right_speed){
    digitalWrite(leftSideIn1,HIGH);
    digitalWrite(leftSideIn2,LOW);
    digitalWrite(rightSideIn3,LOW);
    digitalWrite(rightSideIn4,HIGH); 
    pca9685PWMWrite(fd, ENA, 0, left_speed);
    pca9685PWMWrite(fd, ENB, 0, right_speed);
}
void rotateClockwise(int fd,int speed){
    digitalWrite(leftSideIn1,LOW);
    digitalWrite(leftSideIn2,HIGH);
    digitalWrite(rightSideIn3,HIGH);
    digitalWrite(rightSideIn4,LOW); 
    pca9685PWMWrite(fd, enableA, 0, speed);
    pca9685PWMWrite(fd, enableB, 0, speed);
}
void rotateCounterclockwise(int fd,int speed){
    digitalWrite(leftSideIn1,HIGH);
    digitalWrite(leftSideIn2,LOW);
    digitalWrite(rightSideIn3,LOW);
    digitalWrite(rightSideIn4,HIGH); 
    pca9685PWMWrite(fd, enableA, 0, speed);
    pca9685PWMWrite(fd, enableB, 0, speed);
}
void stop(int fd){
    digitalWrite(leftSideIn1,LOW);
    digitalWrite(leftSideIn2,LOW);
    digitalWrite(rightSideIn3,LOW);
    digitalWrite(rightSideIn4,LOW); 
    pca9685PWMWrite(fd, ENA, 0, 0);
    pca9685PWMWrite(fd, ENB, 0, 0);
}
