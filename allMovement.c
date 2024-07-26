#include "pca9685.h"
#include <wiringPi.h>
#include "allMovement.h"
#include <stdio.h>
#include <stdlib.h>

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
