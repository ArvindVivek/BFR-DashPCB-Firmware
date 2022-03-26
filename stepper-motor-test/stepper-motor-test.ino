void setup() {
  // put your setup code here, to run once:
  // nENBL: LOW
  // nSLEEP: HIGH
  // M0: LOW
  // M1: LOW
  // DIR: HIGH
  // STEP: PULSE LOW TO HIGH
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}
double timeDelay = 1;
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(8, LOW);
  delay(timeDelay);
  digitalWrite(8, HIGH);
  delay(timeDelay);
}
