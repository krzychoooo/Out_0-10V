#include <Arduino.h>

#include <Wire.h>
#include <MCP4725.h>
#include <Out_0-10V.h>

MCP4725 myDac(0x60);
Out_0_10V out_0_10V(&myDac);
#define NUMBER0V    58    //DAC value for Output = 0V
#define NUMBER10V   4058  //DAC value for Output = 10V

void setup(void) {
  Serial.begin(9600);
  Serial.setTimeout(4000UL);
  Serial.println("Hello!");
  Wire.begin(21, 22); 
  myDac.begin();
  out_0_10V.begin(NUMBER0V, NUMBER10V);

  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
    delay(10);
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);
  Serial.println("Start loop");
}

uint8_t terminalByte;
uint16_t dacValue = 0;
long miliVolt ;

void loop(void) {
  if (Serial.available() > 0) {
    // read the incoming byte:
    terminalByte = Serial.read();

    switch (terminalByte)
    {
    case '+':
      dacValue++;
      myDac.setValue(dacValue);
      break;
    
    case '-':
      dacValue--;
      myDac.setValue(dacValue);
      break;
    
    case 'u':
      Serial.println("Enter miliVolt number: ");
      while(!Serial.available()){
      }
      miliVolt = Serial.parseInt();
      Serial.print("miliVolt-> "); Serial.println(miliVolt);
      out_0_10V.setVoltage((uint16_t)miliVolt);
      break;

    default:
      break;
    }
    
    Serial.println(dacValue);
  }
  
  // myDac.setValue(dacValue);

}

