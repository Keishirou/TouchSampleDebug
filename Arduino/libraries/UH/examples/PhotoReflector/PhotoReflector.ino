/*
 *  Example: PhotoReflector
 *  To print out PhotoReflector via Serial Connection(115200).
 *  The PhotoReflector's value is printed out on your serial monitor.
 *  2016.10.22 
 *  http://dev.unlimitedhand.com
 */
 
#include <UH.h>
UH uh;  // create uh object to control a uh

///////////////////////////////////////////////////////////
//  SET UP
///////////////////////////////////////////////////////////
void setup(){
  Serial.begin(115200); // initialize serial communication:
  uh.initPR();          // initialize PhotoReflectors
}

///////////////////////////////////////////////////////////
//  LOOP
///////////////////////////////////////////////////////////
void loop(){
  //print out a value of Photo-Reflector '5'
  Serial.println(uh.readPR(5));
  delay(300);
}

///////////////////////////////////////////////////////////
//  SERIAL EVENT FUNCTION 
///////////////////////////////////////////////////////////
void serialEvent(){
  if(Serial.available()>0){
    if((char)Serial.read()==118){ // if you type 'v'      
      char sketch_name[] = "PhotoReflector__0043";//Patch to probe sketch version
      Serial.print("Version:");Serial.println(sketch_name);// retrun the version
    }
  }
}

