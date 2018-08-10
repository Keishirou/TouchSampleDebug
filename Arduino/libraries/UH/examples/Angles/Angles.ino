/*
 *  Example: Angles
 *  To print out angles via Serial Connection(115200).
 *  The angles are printed out on your serial monitor.
 *  2016.10.22 
 *  http://dev.unlimitedhand.com
 */
 
#include <UH.h>
UH uh;  // create uh object to control a uh

int accelRaw[3];
int gyroRaw[3];
int angleXYZ[3];

///////////////////////////////////////////////////////////
//  SET UP
///////////////////////////////////////////////////////////
void setup(){
  Serial.begin(115200);// initialize serial communication:
  
  uh.setupAcceleGyro();           // initialize AcceleGyro
  uh.readRawAccelValues(accelRaw);// get the sensor values
  uh.initAccelGyroKalman(micros(), accelRaw);// initialize Kalman  
}

///////////////////////////////////////////////////////////
//  LOOP 
///////////////////////////////////////////////////////////
void loop(){
  uh.readRawAccelValues(accelRaw);// get the sensor values(Accel)
  uh.readRawGyroValues(gyroRaw);  // get the sensor values(Gyro)
  uh.readAccelGyro_XYZ_Kalman(accelRaw,gyroRaw,angleXYZ);// calc the angles

  Serial.print("angle x: ");Serial.print(angleXYZ[0]); 
  Serial.print(", angle y: ");Serial.print(angleXYZ[1]); 
  Serial.print(", angle z: ");Serial.println(angleXYZ[2]); 
  delay(1000);
}

///////////////////////////////////////////////////////////
//  SERIAL EVENT FUNCTION 
///////////////////////////////////////////////////////////
void serialEvent(){
  if(Serial.available()>0){
    if((char)Serial.read()==118){ // if you type 'v'      
      char sketch_name[] = "Angles__0043";//Patch to probe sketch version
      Serial.print("Version:");Serial.println(sketch_name);// retrun the version
    }
  }
}

