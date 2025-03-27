#include <Arduino.h>
#include "M5Atom.h"
//#include "Unit_Encoder.h"
//#include <M5Atom.h>
//#include "StepperDriver.h"
#include "FastLED.h"

/* ====== minimumStepper =======================================
 *  Bare minimum to get a stepper with step/dir driver turning
 */
#include <MobaTools.h>
// Stepper connections - Please adapt to your own needs.
int en_pin = 22; // enable pin
const byte stepPin = 19;
const byte dirPin = 23;

const int stepsPerRev = 200*32;    // Steps per revolution - 1/32 microstepping

MoToStepper stepper1( stepsPerRev, STEPDIR );  // create a stepper instance

void setup() {
  pinMode(en_pin, OUTPUT);
  pinMode(26, INPUT_PULLUP); // Optical fork for Y axis
  pinMode(32, INPUT_PULLUP); // Signal from X axis MCU  
  digitalWrite(en_pin, LOW); // enable driver
  stepper1.attach( stepPin, dirPin );
  stepper1.setSpeed( 600 );              // 30 rev/min (if stepsPerRev is set correctly)
  stepper1.setRampLen( stepsPerRev / 4); // Ramp length is 1/2 revolution
  //stepper1.rotate(1);                    // start turning, 1=vorward, -1=backwards                    
  //delay(10000);
  //stepper1.stop();                       // stop turning
  //stepper1.rotate(0);                    // stop turning
  //delay(2000);
  //stepper1.doSteps( stepsPerRev *4);        // do one revolution
  //delay(10000);
  //stepper1.doSteps( -stepsPerRev );

  //delay(20000);
  //digitalWrite(en_pin, HIGH); // disable driver


}

void loop() {

// --------------------------------******* X AXIS ********--------------------------------
  /* if(digitalRead(26) == HIGH){ // if the XY-stage is already in or beyond the home position (the optical fork is blocked = HIGH)
    stepper1.rotate(-1); //  start turning backwards, 1=vorward, -1=backwards
    while (digitalRead(26) == HIGH){ } // keep moving until the optical fork is not blocked anymore
      delay(100); // wait for 1 second and let the stage move a bit more away from home position
      stepper1.stop(); // stop turning
      delay(1000); // wait for 1 second
      //stepper1.rotate(1); //  start turning forwards toward home position
    }

  if(digitalRead(26) == LOW){
    stepper1.rotate(1); //  start turning forwards toward home position
    while (digitalRead(26) == LOW){ } // keep moving until the optical fork is blocked
  //if(digitalRead(32) == HIGH){ 
    stepper1.stop();
    delay(3000); // wait for 5 seconds
    //digitalWrite(en_pin, HIGH); // disable driver
  } */

  while (digitalRead(26) == HIGH){ } // Wait until signal from X axis MCU goes LOW (X axis is in home position) 

// --------------------------------******* Y AXIS ********--------------------------------
  if(digitalRead(32) == LOW){ // if the XY-stage is already in or beyond the home position (the optical fork is not blocked = LOW)
    stepper1.rotate(-1); //  start turning backwards, 1=vorward, -1=backwards
    while (digitalRead(32) == LOW){ } // keep moving until the optical fork is not blocked anymore
      delay(100); // wait for 1 second and let the stage move a bit more away from home position
      stepper1.stop(); // stop turning
      delay(1000); // wait for 1 second
      //stepper1.rotate(1); //  start turning forwards toward home position
    }

  if(digitalRead(32) == HIGH){
    stepper1.rotate(1); //  start turning forwards toward home position
    while (digitalRead(32) == HIGH){ } // keep moving until the optical fork is not blocked
  //if(digitalRead(32) == HIGH){ 
    stepper1.stop();
    digitalWrite(en_pin, HIGH); // disable driver and release tourqe on the motor
    while (1){} // wait forever
    //digitalWrite(en_pin, HIGH); // disable driver
  }
}