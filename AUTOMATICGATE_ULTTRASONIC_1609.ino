//using ultrasonic sensor //unit testing 
const int trigpin = 13;//output
const int echopin =12;//input
const int relay1= 6;
const int relay2 = 5;
const int ir =4; 
const int open = 3; 
const int close =2; 
const int trigpin2 = 11;
const int echopin2 =10;
float distance;
float distance2;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("18092025");
pinMode(trigpin,OUTPUT);
pinMode(echopin,INPUT);
pinMode(trigpin2,OUTPUT);
pinMode(echopin2,INPUT);
pinMode(ir,INPUT);
pinMode(open,INPUT_PULLUP);
pinMode(close,INPUT_PULLUP);
pinMode(relay1,OUTPUT);
pinMode(relay2,OUTPUT);
}
void stop(){
  digitalWrite(relay1,LOW);
  digitalWrite(relay2,LOW);
}
void forward(){
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,LOW);
}
void backward(){
  digitalWrite(relay1,LOW);
  digitalWrite(relay2,HIGH);
}
enum State{
NEUTRAL,
OPENING,
CLOSING
};
State currentstate = NEUTRAL; 

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(trigpin,LOW);
digitalWrite(trigpin2,LOW);
delay(2);
digitalWrite(trigpin,HIGH);
delay(10);
digitalWrite(trigpin,LOW);

digitalWrite(trigpin2,LOW);
delay(2);
digitalWrite(trigpin2,HIGH);
delay(10);
digitalWrite(trigpin2,LOW);

unsigned long duration = pulseIn(echopin,HIGH);
unsigned long duration2 = pulseIn(echopin2,HIGH);

float distance = (0.034*duration)/2;
float distance2 = (0.034*duration2)/2;

if(distance<=5){
  Serial.println("warning!! obstacle detected");
}

if(distance2 <=5){
  Serial.println("warning!! obstacle detected 2");//ir replacement
}
switchstate();
}

void switchstate(){
  int openstate = digitalRead(open);
  int closestate = digitalRead(close);
  
  switch(currentstate){
    case NEUTRAL:
    stop();
    if(distance<5){
      Serial.println("motion detected at the front");
      currentstate=OPENING;
    }
    if(distance2 <5){
      Serial.println("motion detected on the gate path ");
      currentstate=OPENING;
    }
    if(distance>5&&distance2 >5){
      Serial.println("no motion detected");
      currentstate=CLOSING;
    }
    break;
    case OPENING:
    if(openstate==0||closestate==0){
      Serial.println("motor is in full position");
      //active low config
      currentstate =NEUTRAL;
    }
    if(distance>5&&distance2 >5){
      Serial.println("no motion detected");
      currentstate=CLOSING;
    }
    break;
    case CLOSING:
    if(openstate==0||closestate==0){
      Serial.println("motor is in full position");
      //active low config
      currentstate =NEUTRAL;
    }
     if(distance<5){
      Serial.println("motion detected at the front");
      currentstate=OPENING;
    }
    if(distance2 <5){
      Serial.println("motion detected on the gate path ");
      currentstate=OPENING;
    }
    break;
  }
}
