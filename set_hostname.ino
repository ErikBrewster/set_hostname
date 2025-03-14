/*
 * Circuits4you.com
 * Reading and Writing String to EEPROM Example Code
 * Oct 2018
 */
 
 // Based on https://circuits4you.com/2018/10/16/arduino-reading-and-writing-string-to-eeprom/

#include <EEPROM.h>

String deviceName = "ngarage";

void writeString(char add,String data);
String read_String(char add);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  EEPROM.begin(512);
  String data = deviceName;

  Serial.print("Writing Data:");
  Serial.println(data);

  writeString(0, data);  //Address 10 and String type data
  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  String recivedData;
  recivedData = read_String(0);
  Serial.print("Read Data:");
  Serial.println(recivedData);
  delay(10000);
}

void writeString(char add,String data)
{
  int _size = data.length();
  int i;
  for(i=0;i<_size;i++)
  {
    EEPROM.write(add+i,data[i]);
  }
  EEPROM.write(add+_size,'\0');   //Add termination null character for String Data
  EEPROM.commit();
}


String read_String(char add)
{
  int i;
  char data[100]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k=EEPROM.read(add);
  while(k != '\0' && len<500)   //Read until null character
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}
