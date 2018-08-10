void SerialPrintPhotoReflector(){
  for(int i = 0; i < PR_CH_NUM; i ++){
    Serial.print("CH");
    Serial.print(i);
    Serial.print(":");
    Serial.print(PRValues[i]);
    Serial.print(", ");
  }
  Serial.println("");
}


void SerialPrintCountsFlag(){
  Serial.print("calibSectionWidth:");
  Serial.println(calibSectionWidth);
  Serial.print("calibSectionCount:");
  Serial.println(calibSectionCount);
  Serial.print("PRCalib Flag:");
  Serial.println(PRCalib);
  Serial.print("PRVARSum ");
  Serial.println(PRVARSum);
  Serial.print("FIRE_THRESHOLD ");
  Serial.println(FIRE_THRESHOLD);
  Serial.println("-----------------------");
}


void startCalibrate(){
 
  for (int i=0; i<8; i++) {
      uPRSum [i] += PRValues [i];                  // Sum of Photo-Reflector of each channel
      uPRAve [i] = uPRSum [i] / calibSectionWidth; // Average of Photo-Reflector of each channel
  }
  calibSectionWidth++;
  
  // When the section width is optional number (in this case it's 30),
  // Reset the sum value of Photo-Reflector in section width    
  if (30 == calibSectionWidth) {                 
    for (int i=0; i<8; i++) {
       uPRSum [i] = uPRAve [i];
    }
    calibSectionWidth = 1; // Reset the section width
    calibSectionCount++;   // Count the section width
   } 
}




