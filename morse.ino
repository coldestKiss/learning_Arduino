#include <Morse.h>
 
Morse morse(13);
int incomingByte = 0;
 
void setup()
{
  Serial.begin(9600);
}

void loop(){
  if(Serial.available() > 0){
    incomingByte = Serial.read();
    switch(incomingByte){
      case 97:morse.dot();morse.dash();morse.c_space();break;
      case 98:morse.dash();morse.dot();morse.dot();morse.dot();morse.c_space();break;
      case 99:morse.dash();morse.dot();morse.dash();morse.dot();morse.c_space();break;
      case 100:morse.dash();morse.dot();morse.dot();morse.c_space();break;
      case 101:morse.dot();morse.c_space();break;
      case 102:morse.dot();morse.dot();morse.dash();morse.dot();morse.c_space();break;
      case 103:morse.dash();morse.dash();morse.dot();morse.c_space();break;
      case 104:morse.dot();morse.dot();morse.dot();morse.dot();morse.c_space();break;
      case 105:morse.dot();morse.dot();morse.c_space();break;
      case 106:morse.dot();morse.dash();morse.dash();morse.dash();morse.c_space();break;
      case 107:morse.dash();morse.dot();morse.dash();morse.c_space();break;
      case 108:morse.dot();morse.dash();morse.dot();morse.dot();morse.c_space();break;
      case 109:morse.dash();morse.dash();morse.c_space();break;
      case 110:morse.dash();morse.dot();morse.c_space();break;
      case 111:morse.dash();morse.dash();morse.dash();morse.c_space();break;
      case 112:morse.dot();morse.dash();morse.dash();morse.dot();morse.c_space();break;
      case 113:morse.dash();morse.dash();morse.dot();morse.dash();morse.c_space();break;
      case 114:morse.dot();morse.dash();morse.dot();morse.c_space();break;
      case 115:morse.dot();morse.dot();morse.dot();morse.c_space();break;
      case 116:morse.dash();morse.c_space();break;
      case 117:morse.dot();morse.dot();morse.dash();morse.c_space();break;
      case 118:morse.dot();morse.dot();morse.dot();morse.dash();morse.c_space();break;
      case 119:morse.dot();morse.dash();morse.dash();morse.c_space();break;
      case 120:morse.dash();morse.dot();morse.dot();morse.dash();morse.c_space();break;
      case 121:morse.dash();morse.dot();morse.dash();morse.dash();morse.c_space();break;
      case 122:morse.dash();morse.dash();morse.dot();morse.dot();morse.c_space();break;
      case 32:morse.w_space();
    }
  }
}
