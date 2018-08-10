/*
  Arduino sample code of UnlimitedHand 
  for Unity, UnrealEngine and Processing, 
  ver 0044
  
  This code is used with:
  Arduino IDE ver 1.6.9 - 1.6.12 to upload this code to UnlimitedHand,
  or an Unity Code "UH.cs" in UH_Unity004*.zip 
  or an Processing Code in PUnlimitedHand0027.zip ~ PUnlimitedHand003*.zip
  or an UnrealEngine Project in UH4UE00**.zip
  Please visit http://dev.UnlimitedHand.com
*/

#include <UH.h>
#define IR_LED 11 //Use pin11 for infrared LED

/////////////////////////////////
//      GROBAL VARIABLES       //
/////////////////////////////////
UH uh;
int PRValues[PR_CH_NUM];
int PRVARSum;    
int PRVARSumAVE;
int PRVARSumCount;
bool PRCalib;

int uPR[8];
int uPRSum[8];
int uPRAve[8];

int calibSectionWidth;     // Section width for Photo-Reflector addition
int calibSectionCount;     // Average calculation count in Section width

int FIRE_THRESHOLD = 120;  // Fire Threshold which compares with "PRVARSum"

//Infrared rays for Liquid Crystal Television
unsigned char data[6] = {0xAA, 0x5A, 0x8F, 0x12, 0x16, 0xD1};  //AQUOS
// unsigned char data[4] = {0x40, 0xBF, 0x12, 0xED};           // REGZA


/////////////////////////////////
//            SETUP            //
/////////////////////////////////
void setup(){
  pinMode(IR_LED,OUTPUT);
  Serial.begin(115200);
  uh.initPR();

  PRCalib = false;
  PRVARSum = 0;
  PRVARSumAVE = 0;
  PRVARSumCount = 0;
  calibSectionWidth = 1;
  calibSectionCount = 0;
}


/////////////////////////////////
//            LOOP             //
/////////////////////////////////
void loop(){
  uh.readPR(PRValues);         // Read the Photo-Refrector values
  SerialPrintPhotoReflector(); // Display Photo-Reflector values
  SerialPrintCountsFlag();     // Display count value and Flag 
  delay(1000);


  // During Calibration ...
  // Calculate Photo-Reflector average of the each channel in section width until 29 counts
  if (calibSectionCount<2 && calibSectionWidth<30) {
    startCalibrate();
    PRCalib = true;
  }
  // When Calibration Finished ...
  else {
    PRCalib = false;
    PRVARSum = 0;
    
    // Calculate mean deviation of the each channel
    for(int i=0; i<8; i++){
      PRVARSum += abs(PRValues [i] - uPRAve [i]);
    }
    
    PRVARSumAVE += PRVARSum;
    PRVARSumCount++;
    
    if(20 < PRVARSumCount){
      //Calculate variance of the each channel
      PRVARSumAVE = PRVARSumAVE/PRVARSumCount;
      PRVARSumCount = 0;
      FIRE_THRESHOLD = PRVARSumAVE + 20; //Set the Threshold based on variance
    }

    if( FIRE_THRESHOLD <= PRVARSum && PRVARSum <= (FIRE_THRESHOLD+100) ){
      sendIrAEHA(); //Flash the LED (for AQUOS)
    }
  }
  
}// LOOP




/////////////////////////////////
//  SEND INFRARED RADIATION    //
/////////////////////////////////
// For AQUOS Television
void sendIrAEHA() {
  // T=425us
  const int dataCount = sizeof data /sizeof data[0];
  irPulse( 3400, 1700 );                                                // Leader
  for (int i=0; i<dataCount; i++) {
    for (int j=0; j<8; j++) irPulse( 425, (data[i]>>j)%2 ? 1275:425 );  // Data
  }
  irPulse( 425, 68000 );                                                // wait
  irPulse( 3400, 1700 );                                                // Repeat
  for (int i=0; i<dataCount; i++) {
    for (int j=0; j<8; j++) irPulse( 425, (data[i]>>j)%2 ? 1275:425 );  // Data
  }
  irPulse( 425, 0 );  // Trailer
}


// For REGA Television
void sendIrNEC() {
  // T=562us
  const int dataCount = sizeof data / sizeof data[0];
  irPulse( 9000, 4500 );                                               // Leader
  for (int i=0; i<dataCount; i++) {
    for(int j=0; j<8; j++) irPulse( 562, (data[i]>>j)%2 ? 1687:562 );  // Data
  }
    irPulse( 562, 40000 );                                             // Trailer
}
  

/////////////////////////////////
//       FLASH THE LED         //
/////////////////////////////////
void irPulse(unsigned long lenH, unsigned long lenL){
  unsigned long irExp=micros()+lenH;
  while(irExp>micros()){        //Output pulse for lenH usec
    digitalWrite(IR_LED,HIGH);
    delayMicroseconds(5);
    digitalWrite(IR_LED,LOW);
    delayMicroseconds(9);
  }
  if (lenL > 16000 ){           // To avoid Arduino's delayMicroseconds limitation
    delay(lenL / 1000);
  } else {
    delayMicroseconds( lenL );  // for LenL usec
  }
}
  

