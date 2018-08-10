/*
 *  Example: RawAccelGyro
 *  To print out raw accel and gyro values via Serial Connection(115200).
 *  The raw accel and gyro values are printed out on your serial monitor.
 *  2016.10.22 
 *  http://dev.unlimitedhand.com
 */
#include <UH.h>
UH uh;
int accelRaw[3];
int gyroRaw[3];

///////////////////////////////////////////////////////////
//  SET UP
///////////////////////////////////////////////////////////
void setup(){
  Serial.begin(115200);
  uh.setupAcceleGyro();
}

///////////////////////////////////////////////////////////
//  LOOP 
///////////////////////////////////////////////////////////
void loop(){
  uh.readRawAccelValues(accelRaw); // get the sensor values(Accel)
  uh.readRawGyroValues(gyroRaw);   // get the sensor values(Gyro)
  
  for(int i=0;i<3;i++){
    Serial.print("accel: "); Serial.print(accelRaw[i]);
    Serial.print(", gyro: ");Serial.println(gyroRaw[i]); 
  }
  delay(300);
}

///////////////////////////////////////////////////////////
//  SERIAL EVENT FUNCTION 
///////////////////////////////////////////////////////////
void serialEvent(){
  if(Serial.available()>0){
    if((char)Serial.read()==118){ // if you type 'v'      
      char sketch_name[] = "RawAccelGyro__0043";//Patch to probe sketch version
      Serial.print("Version:");Serial.println(sketch_name);// retrun the version
    }
  }
}
