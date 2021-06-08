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

  // all subsystems are working
  
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(9, HIGH);
  delay(1000);

  digitalWrite(10, LOW);  //payload 1 is not working
  delay(1000);
  
  digitalWrite(10, HIGH); 
  digitalWrite(9,LOW);  //payload 2 is not working
  delay(1000);
  
  digitalWrite(9. HIGH);
  digitalWrite(11, LOW);  //adcs is not working
  delay(1000);

  digitalWrite(11, HIGH);
  digitalWrite(13, LOW);  //comms is now working
  delay(1000);
  
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);  //eps is not working
  delay(1000);
}
