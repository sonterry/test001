unsigned int count=0;
unsigned int count2=0;

const int motor1=2;
const int motor2=3;

const int trigPin1=12; 
const int echoPin1=13;
/*
const int trigPin2=10;
const int echoPin2=11;

const int trigPin3=8;
  const int echoPin3=9;
*/


int distance1=0;
int distance2=0;
//int distance3=0;


void setup() {
  Serial.begin(9600);
  pinMode(motor1, OUTPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  digitalWrite(trigPin1, LOW);
  /*
  pinMode(motor2, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  digitalWrite(trigPin2, LOW);
  */
  TCCR0A = 0; //TCCR0A initialize
  TCCR0B = 0; //TCCR0B initialize
  TCNT0 = 0;  //TCNT0 initialize
  OCR0A= 154; //Period: 10ms , Frequency: 100Hz
//  OCR0B= 154;
  TCCR0A |= (1<<WGM01);
  TCCR0B |= (1<<CS02) | (1<<CS00);
  TIMSK0 |= (1<<OCIE0A);
//  TIMSK0 |= (1 << OCIE0B) | (1<<OCIE0A);
  
  sei();
}
 
ISR(TIMER0_COMPA_vect){
  count++;
  
  if(count>13) // 100ms 마다 초기화
  {
    digitalWrite(trigPin1, LOW);
    distance1=pulseIn(echoPin1, HIGH)/58.2;
    if(distance1>250) distance1=250;
    Serial.print("sens1 : ");
    Serial.println(distance1);
    count=0;
    TCNT0=0;
    digitalWrite(trigPin1, HIGH);
  }
  
  if(distance1/13<count) digitalWrite(motor1, HIGH);
  else digitalWrite(motor1, LOW);
}
/*
ISR(TIMER0_COMPB_vect){
  count2++;
  
  if(count2>10) // 100ms 마다 초기화
  {
    digitalWrite(trigPin2, LOW);
    distance2=pulseIn(echoPin2, HIGH)/58.2;
    if(distance2>250) distance2=250;
    Serial.print("sens2 : ");
    Serial.println(distance2);
    count2=0;
    //TCNT0=0;
    digitalWrite(trigPin2, HIGH);
  }
  
  if(distance2/10<count2) digitalWrite(motor2, HIGH);
  else digitalWrite(motor2, LOW);
}
*/
void loop() {
  
}
