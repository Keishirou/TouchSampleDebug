/*
 *  Example: VibrationMotor
 *  To output vibration via Serial Connection(115200).
 *  Your UnlimitedHand vibrates every 1000ms.
 *  2016.10.22 
 *  http://dev.unlimitedhand.com
 */
 
#include <UH.h>
UH uh;  // create uh object to control a uh

///////////////////////////////////////////////////////////
//  SET UP
///////////////////////////////////////////////////////////
void setup(){
  Serial.begin(115200);     // initialize serial communication:
  uh.setupVibrationMotor(); // initialize vibrationMotor
}

///////////////////////////////////////////////////////////
//  LOOP 
///////////////////////////////////////////////////////////
void loop(){
  uh.onVibrationMotor();   // turn the vibrationMotor on
  delay(1000);              // wait for a second
  uh.offVibrationMotor();    // turn the vibrationMotor off
  delay(1000);              // wait for a second
}

///////////////////////////////////////////////////////////
//  SERIAL EVENT FUNCTION 
///////////////////////////////////////////////////////////
void serialEvent(){
  if(Serial.available()>0){
    if((char)Serial.read()==118){ // if you type 'v'      
      char sketch_name[] = "VibrationMotor__0043";//Patch to probe sketch version
      Serial.print("Version:");Serial.println(sketch_name);// retrun the version
    }
  }
}

