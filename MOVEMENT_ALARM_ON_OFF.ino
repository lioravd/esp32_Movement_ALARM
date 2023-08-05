/* LIOR AVADYAYEV
--------------------------------------------------------------------------------
This code implements a movement alarm via movement sesnor
To turn ON the alarm we will click on the button
the alarm will turn on the led and the buzzer anytime there will be a movement
to turn OFF the alarm we will click the button again
---------------------------------------------------------------------------------
*/
#define led 2               // Led pin
#define sensor 5            // Movement Sensor pin
#define button 4            // button pin
#define BUZZER_PIN 18       //buzzer pin

int move = 0;                 // movement variable
int Alarm_ON = 0;


void IRAM_ATTR isr() {      //This function Turn ON/OFF the alarm
    if (Alarm_ON){
      Serial.println("Alarm is OFF"); 
      digitalWrite(led, LOW); // turn LED OFF
      digitalWrite(BUZZER_PIN, LOW);   // turn Buzzer OFF
    }
    else
      Serial.println("Alarm is ON");    
    Alarm_ON = ~Alarm_ON;;
}

void setup() {
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
  pinMode(button, INPUT_PULLUP);    // initialize button as an input
  pinMode(BUZZER_PIN, OUTPUT);    // initialize buzzer as an output
  attachInterrupt(button, isr, FALLING);  //initialize interrupt
  Serial.begin(115200);        // initialize serial
}

void loop(){
 
  while(Alarm_ON){   //ONLY if ALARM TURNED ON
    move = digitalRead(sensor);   // read sensor value
    if (move == HIGH) {           // check if the sensor is HIGH
      digitalWrite(led, HIGH);   // turn LED ON
      digitalWrite(BUZZER_PIN, HIGH);   // turn BUZZER ON
      delay(20);                // delay 20 milliseconds  
      Serial.println("Motion detected!"); 
     
    } 
    else {
        digitalWrite(led, LOW); // turn LED OFF
        digitalWrite(BUZZER_PIN, LOW);   // turn BUZZER OFF
        Serial.println("Motion stopped!");
     
    }

  }
}
  