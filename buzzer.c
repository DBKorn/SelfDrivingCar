#include <wiringPi.h>
#include <stdio.h>

#define  buzzerPin    0	//define the buzzer pin number

void main(void)
{	
	printf("Program is starting ... \n");
	
	wiringPiSetup();	//Initialize wiringPi.
	
	pinMode(buzzerPin, OUTPUT);//Set the pin mode
	printf("Using pin%d\n",buzzerPin);	//Output information on terminal
	while(1){
		digitalWrite(buzzerPin, HIGH);  //Make GPIO output HIGH level
		printf("buzzer turned on >>>\n");		//Output information on terminal
		delay(1000);						//Wait for 1 second
		digitalWrite(buzzerPin, LOW);  //Make GPIO output LOW level
		printf("buzzer turned off <<<\n");		//Output information on terminal
		delay(1000);						//Wait for 1 second
	}
}

