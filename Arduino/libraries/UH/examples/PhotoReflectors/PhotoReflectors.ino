/*
 *  Example: PhotoReflectors
 *  To print out PhotoReflectors via Serial Connection(115200).
 *  The PhotoReflectors' values are printed out on your serial monitor.
 *  2016.10.22 
 *  http://dev.unlimitedhand.com
 */
 
#include <UH.h>
UH uh;  // create uh object to control a uh

int PRValues[PR_CH_NUM];// channel number of PhotoReflectors

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
  uh.readPR(PRValues);
    for(int i = 0; i < PR_CH_NUM; i ++){
        Serial.print("CH"); Serial.print(i);Serial.print(":");
        Serial.print(PRValues[i]); Serial.print(" ");
     }
    Serial.println("");
    delay(300);
}

///////////////////////////////////////////////////////////
//  SERIAL EVENT FUNCTION 
///////////////////////////////////////////////////////////
void serialEvent(){
  if(Serial.available()>0){
    if((char)Serial.read()==118){ // if you type 'v'      
      char sketch_name[] = "PhotoReflectors__0043";//Patch to probe sketch version
      Serial.print("Version:");Serial.println(sketch_name);// retrun the version
    }
  }
}

