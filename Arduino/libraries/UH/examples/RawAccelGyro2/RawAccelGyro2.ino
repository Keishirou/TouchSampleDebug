/*
 *  Example: RawAccelGyro2
 *  To print out raw accel and gyro values via Serial Connection(115200).
 *  The raw accel and gyro values are printed out on your serial monitor.
 *  2016.10.22 
 *  http://dev.unlimitedhand.com
 */

#include <UH.h>
UH uh;  // create uh object to control a uh

int accelRaw[3];
int gyroRaw[3];

///////////////////////////////////////////////////////////
//  SET UP
///////////////////////////////////////////////////////////
void setup(){
  Serial.begin(115200); // initialize serial communication:
  uh.setupAcceleGyro(); // initialize AcceleGyro
}

///////////////////////////////////////////////////////////
//  LOOP 
///////////////////////////////////////////////////////////
void loop(){
  uh.readRawAccelValues(accelRaw); // get the sensor values(Accel)
  uh.readRawGyroValues(gyroRaw);   // get the sensor values(Gyro)

  Serial.print("accel x: ");   Serial.print(accelRaw[0]); 
  Serial.print(", accel y: "); Serial.print(accelRaw[1]); 
  Serial.print(", accel z: "); Serial.println(accelRaw[2]); 

  Serial.print("gyro x: ");    Serial.print(gyroRaw[0]); 
  Serial.print(", gyro y: ");  Serial.print(gyroRaw[1]); 
  Serial.print(",gyro z: ");   Serial.println(gyroRaw[2]); 

  delay(1000);
}

///////////////////////////////////////////////////////////
//  SERIAL EVENT FUNCTION 
///////////////////////////////////////////////////////////
void serialEvent(){
  if(Serial.available()>0){
    if((char)Serial.read()==118){ // if you type 'v'      
      char sketch_name[] = "RawAccelGyro2__0043";//Patch to probe sketch version
      Serial.print("Version:");Serial.println(sketch_name);// retrun the version
    }
  }
}


