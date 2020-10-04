/*
  Serial to hid converter. Used when keywedge is needed for Linux systems.
  Joakim Ringstad
  Datalogic Sweden
  joakim.ringstad@datalogic.com

  Instructions
  Connect TX to CBX
  
  Connect Ground to signal ground CBX
*/

#include "Keyboard.h"

//Check full message arrived
bool firstCharFound = false;
int firstChar;

void setup() {
  // open the serial port:
  Serial1.begin(1200,SERIAL_8O2);
  // initialize control over the keyboard:
  Keyboard.begin();
  delay(3000);
}

void loop() {
   
  //IF Serial data is present
  if (Serial1.available() > 0) {
    int inChar = Serial1.read();

    //Convert + to -, keyboard language is wrong English to swedish
    char myChar = char(inChar); 
    if(myChar == 45){
      myChar = 47;
      }

    //Store first received character
    if(firstCharFound==false){
      firstChar = inChar;
      firstCharFound=true;
      }
    //IF header is <STX>
    if(firstChar==2){
      Keyboard.write(myChar);
      delay(15);  
      }
  }
  //IF Serial data not present
  else{
    Keyboard.flush();
  Serial1.flush();
  firstCharFound = false;
    }
  
  
}
