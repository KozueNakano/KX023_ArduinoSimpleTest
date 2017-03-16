#include <Wire.h>
union data {
  int16_t data16;
  byte  byteStr[2];//{*DATAL,*DATAH}
};
union data xData;
union data yData;
union data zData;

const int sendorDeviceAddress = 0x1F;
const int regAddressXOUTL = 0x06;
const int regAddressYOUTL = 0x08;
const int regAddressZOUTL = 0x0A;


void setup() {
  Serial.begin(9600);


  //KX023debice initialize
  Wire.begin();
  //stunbymode fullPower GLange2g
  Wire.beginTransmission(sendorDeviceAddress);
  Wire.write(0x18);
  Wire.write(0x40);
  Wire.endTransmission();
  //outPutDataLate 50Hz
  Wire.beginTransmission(sendorDeviceAddress);
  Wire.write(0x1B);
  Wire.write(0x02);
  Wire.endTransmission();
  //sensor WakeUp
  Wire.beginTransmission(sendorDeviceAddress);
  Wire.write(0x18);
  Wire.write(0xC0);
  Wire.endTransmission();

}

void loop() {

  //readXout
  Wire.beginTransmission(sendorDeviceAddress);
  Wire.write(regAddressXOUTL);
  Wire.endTransmission();
  Wire.requestFrom(sendorDeviceAddress, 2);
  xData.byteStr[0] = Wire.read();
  xData.byteStr[1] = Wire.read();
  
  //readYout
  Wire.beginTransmission(sendorDeviceAddress);
  Wire.write(regAddressYOUTL);
  Wire.endTransmission();
  Wire.requestFrom(sendorDeviceAddress, 2);
  yData.byteStr[0] = Wire.read();
  yData.byteStr[1] = Wire.read();
  
  //readZout
  Wire.beginTransmission(sendorDeviceAddress);
  Wire.write(regAddressZOUTL);
  Wire.endTransmission();
  Wire.requestFrom(sendorDeviceAddress, 2);
  zData.byteStr[0] = Wire.read();
  zData.byteStr[1] = Wire.read();

  Serial.print("xdata:");
  Serial.print(xData.data16, DEC); 
  Serial.print(",");
  Serial.print("ydata:");
  Serial.print(yData.data16, DEC); 
  Serial.print(",");
  Serial.print("zdata:");
  Serial.println(zData.data16, DEC); 
  delay(200);

}
