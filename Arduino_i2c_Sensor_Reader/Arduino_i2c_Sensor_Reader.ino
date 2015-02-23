#include <Wire.h>

#define numSensors 5

//if your addresses are sequential you can just do this
//byte firstAddress = 0x01;

//if they aren't sequential lets use an array
//evidently it cant be a byte or a uint8_t
int addresses[numSensors] = {0x01, 0x02, 0x03, 0x04, 0x05};

const unsigned int DELAY_TIME = 300;

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  
  //lets wait for all the devices to get their initial readings and be setup
  delay(3000);
}

void loop()
{

  //if sequntial
  // for(int i = firstAddress, i < firstAddress+numSensors; i++){
  // Wire.requestFrom(i, 6);    // request 6 bytes from slave device #2
  for(int i = 0; i < numSensors; i++){
    Wire.requestFrom(addresses[i], 1);
    while(Wire.available())    // slave may send less than requested
    { 
      //responses are all unsigned so byte is better than char
      byte c = Wire.read(); // receive a byte
      Serial.print("Sensor ");
      Serial.print(addresses[i]);
      Serial.print(": ");
      Serial.print(c);         
    }
    Serial.println();
  }
  

  //no point in reading all the time since the sensors only
  //update every 5 minutes or whatever your delay time is
  delay(1000*DELAY_TIME);
}

