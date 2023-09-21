int switch_pin = 2;
int analogInPin = 0xA0;
int inletValvePin = 6;
int exhaustValvePin = 7;
int pumpPin = 5;
int ledPin = 13;

//D7 is release valve
//D6 is input valve
//D2 is switch
//A0 is pressure sensor
//D5 is pump

int desiredValue = 296;
int tolerance = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(switch_pin, INPUT);
  pinMode(analogInPin, INPUT);

  pinMode(pumpPin, OUTPUT);
  pinMode(inletValvePin, OUTPUT);
  pinMode(exhaustValvePin, OUTPUT);
}

void loop() {
  analogWrite(pumpPin,0);
  // analogWrite(inletValvePin,0);
  // analogWrite(exhaustValvePin,0);
  int turn_on = digitalRead(switch_pin);
  int sensorValue = analogRead(analogInPin); 


  if ( turn_on == LOW) {
    digitalWrite(inletValvePin,LOW); // turn pressure valve HIGH
    analogWrite(pumpPin,0); // pump is off
    digitalWrite(exhaustValvePin,LOW); // turn exhaust valve HIGH
    // digitalWrite(ledPin,LOW); // LED off
    Serial.print("Pump OFF    ");
  }
  else{
    digitalWrite(inletValvePin,HIGH); // turn pressure valve HIGH
    digitalWrite(exhaustValvePin,LOW); // turn exhaust valve LOW
    // digitalWrite(ledPin,HIGH); // LED ON
    Serial.print("Pump ON    ");
      if (sensorValue <= desiredValue) {
        analogWrite(pumpPin,255); // Pump. (0 is off) and (255 is on)
        Serial.print("   pump high   "); 
      }
      else{
        if (sensorValue > (desiredValue + tolerance) ) {
          analogWrite(pumpPin,0); // reduce speed of pump
          Serial.print("  pump maintain   "); 
        }
      }
  }
  Serial.print("pressure: ");
  Serial.println(sensorValue);                         
  // digital value of pressure sensor voltage
  // voltage_mv =  (sensorValue * reference_voltage_mv) / ADCFULLSCALE;
 
  // pressure sensor voltage in mV
  // voltage_v = voltage_mv / 1000; 
                                     
  // output_pressure = ( ( (voltage_v - (0.10 * (reference_voltage_mv/1000) )) * (Pmax - Pmin) ) / (0.8 * (reference_voltage_mv/1000) ) ) + Pmin;
  delay(200);
}
