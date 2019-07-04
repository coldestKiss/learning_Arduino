int income;

void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(6, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  if(Serial.available() > 0)
  {
    income = Serial.read() - '0';
    if((income&1)==1)
      digitalWrite(2, HIGH);
    if((income>>1)&1==1)
      digitalWrite(3, HIGH);
    if((income>>2)&1==1)
      digitalWrite(4, HIGH);
    if((income>>3)&1==1)
      digitalWrite(5, HIGH);
    
    digitalWrite(6, HIGH);
    delay(1000);
  }  
}
