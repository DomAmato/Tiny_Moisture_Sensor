#include <TinyWireS.h>

//this needs to change for each sensor
#define I2C_SLAVE_ADDR  0x01            // i2c slave address 

#define POWER_PIN1      4              // ATtiny Pin 3
#define POWER_PIN2      1              // ATtiny Pin 6
#define MOISTURE_SENSOR	3              // ATtiny Pin 2
boolean isOn;
boolean polarity;

//change this to your desired moisture level it may require some
//experimentation on your part to determine the optimal level
const int  MOISTURE_LEVEL = 250;

//our valriables and timer
int 	   val1, val2;
long     timer;

//check every 5 minutes 
const unsigned int DELAY_TIME = 300;

void setup(){
  timer = 0;
  polarity = true;
  
  pinMode(POWER_PIN1, OUTPUT);
  pinMode(POWER_PIN2, OUTPUT);             
  pinMode(MOISTURE_SENSOR, INPUT);

  TinyWireS.begin(I2C_SLAVE_ADDR);      // init I2C Slave mode

  TinyWireS.onRequest(requestEvent);  //the function associated with a read request

  //here we do a quick setup and check. we dont want the sensor to corrode
  //so we will only be checking every once in awhile, also it is unlikely
  //that the soil will dry up in a matter of seconds or even minutes
  digitalWrite(POWER_PIN1, HIGH);
  digitalWrite(POWER_PIN2, LOW);
  val1 = analogRead(MOISTURE_SENSOR);
  digitalWrite(POWER_PIN1, LOW);
  digitalWrite(POWER_PIN2, HIGH);
  val2 = 1023 - analogRead(MOISTURE_SENSOR);

  //turn things off 
  digitalWrite(POWER_PIN1, LOW);
  digitalWrite(POWER_PIN2, LOW);
  
  //set an inital state
  int avg = (val1 + val2) / 2;
  isOn = avg < MOISTURE_LEVEL ?  true : false;
}

//the i2c request handle
void requestEvent()
{  
  //we are just sending if it needs water or not
  TinyWireS.send(isOn);
}

void readSensor(){

  //which direction are we reading
  polarity ? val1 = analogRead(MOISTURE_SENSOR) : val2 = 1023 - analogRead(MOISTURE_SENSOR);

  //average things out
  int avg = (val1 + val2) / 2;

  //the more moist the soil the lower the resistance and thus higher the reading
  //a lower average means the soils dry
  isOn = avg < MOISTURE_LEVEL ?  true : false;
}

void loop(){

  //only check when its time
  if(millis()-timer>1000*DELAY_TIME){
    //which direction are we checking
    if(polarity){
      digitalWrite(POWER_PIN1, HIGH);
      digitalWrite(POWER_PIN2, LOW);
    }
    else{
      digitalWrite(POWER_PIN1, LOW);
      digitalWrite(POWER_PIN2, HIGH);
    }
    readSensor();
    polarity = !polarity;

    //set things back to low 
    digitalWrite(POWER_PIN1, LOW);
    digitalWrite(POWER_PIN2, LOW);
    
    //reset the timer
    timer = millis();
  }
  
  TinyWireS_stop_check();
}





