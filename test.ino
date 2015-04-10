#include <Stepper.h>

//Pin of the laser to be blinked
const int laser = 13;

//Speed of the stepper motor
const int stepsPerRevolution = 200;

//Set the accuracy of the average
const int numberOfReads = 50;

//Offset determines the difference from the average and the read that
//must be reached in order for a note to be played
const int offset = 50;

//Stores the average of the initial numberOfReads reads
int avg = 0;

//stores the current read from the light sensor
int read = 0;

//Counter used in the initial startup
int i = 0;

//For determining if the program is in the state of the first three iterations
//Flipped to false after the first three iterations has finished
bool first = true;

//Initialize the stepper on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup(){
  myStepper.setSpeed(60);
  Serial.begin(9600);
  pinMode(laser, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop(){
  if(!first){
    digitalWrite(12, HIGH);
    delay(100);
    read = analogRead(A0);
    digitalWrite(12, LOW);

    Serial.print("Read:  ");
    Serial.print(read);
    Serial.print(" Average:  ");
    Serial.println(avg);

    //If there was a change of more than 50, blink the status LED to signify
    if((read - avg) > offset){
      digitalWrite(laser, HIGH);
    }
    else{
      digitalWrite(laser, LOW);
    }

    //In case something goes wrong, such as the amount of light in the room
    //changing, and a hard reset needs to be made to recalculate the initial
    //average.
    //if(digitalRead(A reset button)){
    //  first = true;
    //}
  }
  else{
    if(i == 0){
      delay(1000);
    }

    digitalWrite(12, HIGH);
    delay(100);
    avg += analogRead(A0);
    digitalWrite(12, LOW);

    i++;

    if(i == numberOfReads){
      avg /= numberOfReads;
      i = 0;
      first = false;
    }
  }
}

//  myStepper.step(stepsPerRevolution);
//  myStepper.step(stepsPerRevolution, laser);

//  for(int i = 0; i < 12; i++){
//    myStepper.step(2, laser);
//  }
//
//  for(int i = 0; i < 12; i++){
//    myStepper.step(-2, laser);
//  }
