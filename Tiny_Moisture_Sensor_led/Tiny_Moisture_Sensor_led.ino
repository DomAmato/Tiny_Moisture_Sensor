#define POWER_PIN1      0              // ATtiny Pin 5
#define POWER_PIN2      4              // ATtiny Pin 3
#define LED_PIN         2              // ATtiny Pin 7
#define MOISTURE_SENSOR	3              // ATtiny Pin 2


//change this to your desired moisture level it may require some
//experimentation on your part to determine the optimal level
const int  MOISTURE_LEVEL = 250;

//our valriables and timer
int 	   val1, val2;
long       timer;

//check every 5 minutes 
const unsigned int DELAY_TIME = 300;

void setup(){
  timer = 0;

  pinMode(POWER_PIN1, OUTPUT);
  pinMode(POWER_PIN2, OUTPUT);
  pinMode(LED_PIN, OUTPUT);  
  pinMode(MOISTURE_SENSOR, INPUT);

  //here we do a quick setup and check. we dont want the sensor to corrode
  //so we will only be checking every once in awhile, also it is unlikely
  //that the soil will dry up in a matter of seconds or even minutes
  digitalWrite(POWER_PIN1, HIGH);
  digitalWrite(POWER_PIN2, LOW);
  val1 = analogRead(MOISTURE_SENSOR);
  delay(500);
  digitalWrite(POWER_PIN1, LOW);
  digitalWrite(POWER_PIN2, HIGH);
  val2 = 1023 - analogRead(MOISTURE_SENSOR);

  //turn things off 
  digitalWrite(POWER_PIN1, LOW);
  digitalWrite(POWER_PIN2, LOW);

  //set an inital state
  int avg = (val1 + val2) / 2;
  avg < MOISTURE_LEVEL ? digitalWrite(LED_PIN, HIGH) : digitalWrite(LED_PIN, LOW);
}

void readSensor(){

  digitalWrite(POWER_PIN1, HIGH);
  digitalWrite(POWER_PIN2, LOW);
  val1 = analogRead(MOISTURE_SENSOR);
  delay(500);
  digitalWrite(POWER_PIN1, LOW);
  digitalWrite(POWER_PIN2, HIGH);
  val2 = 1023 - analogRead(MOISTURE_SENSOR);

  //average things out
  int avg = (val1 + val2) / 2;

  //the more moist the soil the lower the resistance and thus higher the reading
  //a lower average means the soils dry
  avg < MOISTURE_LEVEL ? digitalWrite(LED_PIN, HIGH) : digitalWrite(LED_PIN, LOW);
}

void loop(){

  //only check when its time
  if(millis()-timer>1000*DELAY_TIME){
    readSensor();

    //set things back to low 
    digitalWrite(POWER_PIN1, LOW);
    digitalWrite(POWER_PIN2, LOW);

    //reset the timer
    timer = millis();
  }
}






