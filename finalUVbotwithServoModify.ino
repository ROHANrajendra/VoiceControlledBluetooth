#include<SoftwareSerial.h>
#include<Servo.h>
SoftwareSerial BTSerial(0,1);
Servo myServo;
int Ultrasound();
String phrase;
long duration;
int dist;
const int trig = 8;
const int echo = 9;
const int distance = 30; //distance below the sensor identifies the object as an obstacle 

void setup() {

  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  Serial.begin(9600);
  BTSerial.begin(9600);
  myServo.attach(7); //attaching the servo to digital pin 7
  myServo.write(90); //orienting the servo to default position

}

void loop() {

  while(BTSerial.available())
  {
    delay(10);
    char ch = BTSerial.read();
    if(ch == '#')
    { 
      break;
    }
    
    phrase += ch; 
  }

  if(phrase.length()>0)
  {
    if(phrase == "*go")
      forward();

    if(phrase == "*back")
      backward();

    if(phrase == "*stop")
      Stop();

    if(phrase == "*left")
      left();

    if(phrase == "*right")
      right();

    if(phrase == "*rotate")
      rotate(); 

    if(phrase == "*avoid")
    {   
      while(!BTSerial.available())
        avoid();   
    }   
    phrase = "";  
  }
  
}

void forward()
{ int Ultrasound();
  myServo.write(90);
  if(Ultrasound() >= distance)
  {
    analogWrite(6,255);
    analogWrite(5,0);
    analogWrite(11,0);
    analogWrite(10,255);
    delay(1500); //delay of 3 seconds for bot to move 30cm
    Stop();
    
  }
  else 
  {
    Stop();
    myServo.write(0);
    delay(500);
    myServo.write(180);
    delay(500);
    myServo.write(0);
    delay(500);
    myServo.write(180);
    delay(500);
    myServo.write(90);
  } 
}
 
void backward()
{  int Ultrasound();
  analogWrite(6,255);
  analogWrite(5,0);
  analogWrite(11,255);
  analogWrite(10,0); 
  delay(1200); //delay for 180 degree rotation
  Stop();
  if(Ultrasound() >= distance)
  {
    analogWrite(6,255);
    analogWrite(5,0);
    analogWrite(11,0);
    analogWrite(10,255);
    delay(1500); //delay of 3 seconds
    Stop();
   
  }
  else 
  {
    Stop();
    myServo.write(0);
    delay(500);
    myServo.write(180);
    delay(500);
    myServo.write(0);
    delay(500);
    myServo.write(180);
    delay(500);
    myServo.write(90);
  } 
  
}

void Stop() 
{
  analogWrite(6,0);
  analogWrite(5,0);
  analogWrite(11,0);
  analogWrite(10,0); 
}


void left() 
{ int Ultrasound();
  myServo.write(180); //turning the ultrasonic sensor to the left
  delay(500);
  
  if(Ultrasound() >= distance)
  {
    analogWrite(6,0);
    analogWrite(5,0);
    analogWrite(11,0);
    analogWrite(10,255); 
    delay(1500); //delay for 3 seconds
    forward();
  }
  else
  {
    Stop();
    myServo.write(0);
    delay(500);
    myServo.write(180);
    delay(500);
    myServo.write(0);
    delay(500);
    myServo.write(180);
    delay(500);
    myServo.write(90);
  } 
        
  delay(500);
  myServo.write(90);
  
}

void right() 
{ int Ultrasound();
  myServo.write(0); //to turn the ultrasonic sensor right
  delay(500);
  
  if(Ultrasound() >= distance)
  {
    analogWrite(6,255);
    analogWrite(5,0);
    analogWrite(11,0);
    analogWrite(10,0); 
    delay(1500); //delay of 3 seconds
    forward();
  }
  else
  {
    Stop();
    myServo.write(0);
    delay(500);
    myServo.write(180);
    delay(500);
    myServo.write(0);
    delay(500);
    myServo.write(180);
    delay(500);
    myServo.write(90);
  } 
    
  delay(500);
  myServo.write(90);
  
}

void rotate() 
{
  analogWrite(6,255);
  analogWrite(5,0);
  analogWrite(11,255);
  analogWrite(10,0); 
}

void rightturn()
{
    analogWrite(6,255);
    analogWrite(5,0);
    analogWrite(11,0);
    analogWrite(10,0);
    delay(1000);
}


void leftturn()
{
    analogWrite(6,0);
    analogWrite(5,0);
    analogWrite(11,0);
    analogWrite(10,255); 
    delay(1000);
}

void go()
{
  while(Ultrasound() >= distance){
    analogWrite(6,255);
    analogWrite(5,0);
    analogWrite(11,0);
    analogWrite(10,255);
  }
  Stop();  
}


void avoid()
{
  //go();  
  int Ultrasound();
  myServo.write(90);
  delay(1000);
  
  int span = Ultrasound();  

  if (span <= distance){

    Stop(); 

    char turn = check(); //Decide which direction to turn.

    switch (turn){

      case 'l':

        leftturn();

        break;

      case 'r':

        rightturn();

        break;

      case 's':

        go();

        break;
    }
  }

  else
    go();
         
}

char check()
{ int Ultrasound();
  int leftcheck, centercheck, rightcheck;
  char choice;

  myServo.write(180);  //Look left
  delay(1000);
  leftcheck = Ultrasound();

  myServo.write(0);  //Look right
  delay(1000);
  rightcheck = Ultrasound();


  myServo.write(90);   //Look straight
  delay(1000);
  centercheck = Ultrasound();

    if (leftcheck>rightcheck && leftcheck>centercheck)
      choice = 'l';
      
    else if (rightcheck>leftcheck && rightcheck>centercheck)
      choice = 'r';
      
    else
      choice = 's';

  return choice;
}



int Ultrasound()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);  //sending a 10 microsecond trigger pulse to the obstacle 
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH); //calculates the time taken by trigger pulse to reach echo pin 
  dist = duration*0.034/2; //distance between sensor and obstacle in cm
  Serial.print("Distance: ");  //prints the distance on serial monitor 
  Serial.println(dist);

  return dist;
}
  


