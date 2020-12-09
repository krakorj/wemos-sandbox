void setup() {
  // PIN setup
  pinMode(LED_BUILTIN, OUTPUT);

  // Serial port setup
  Serial.begin(115200);
}

void loop() {
  int i;

  for(i=0; i < 3; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);

    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
  
  delay(500);
  
  for(i=0; i < 2; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);

    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
} 
