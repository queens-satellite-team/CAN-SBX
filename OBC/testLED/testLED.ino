void setup() {
  // put your setup code here, to run once:
 pinMode(13, OUTPUT); //comms
 pinMode(12, OUTPUT); //eps
 pinMode(11, OUTPUT);  //adcs
 pinMode(10, OUTPUT);   //p1
 pinMode(9, OUTPUT);  //p2
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH);
  delay(1000);
  
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  delay(1000);
  
  digitalWrite(12, LOW);
  digitalWrite(11, HIGH);
  delay(1000);

  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  delay(1000);
  
  digitalWrite(10, LOW);
  digitalWrite(9, HIGH);
  delay(1000);
}
