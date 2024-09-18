//sumobot_demo

/*
  NOTE: you can change the pin assignment below
        as long as they match the crrect pinout
        diagram
*/

//Define pins

// L298N(Motor Driver)
int in1 = 8;
int in2 = 9;
int in3 = 12;
int in4 = 13;

int ena = 10;
int enb = 11;

// KY-033 (Line Tracking)
int leftLine = 2;
int rightLine = 3;

// HC - SR04 (Ultrasonic)
int trigger = 4;
int echo = 5;


// additional variable
int white = 0;
int black = 0;


long duration;
int distance;

//-----------------------------------------------------------------------------//

/*
  This part is for the functions of the bot
*/

//basic bot movement
void forward(int leftSpeed, int rightSpeed){

  analogWrite(enb, leftSpeed);
  analogWrite(ena, rightSpeed);

//change depending on polarity
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void backward(int leftSpeed, int rightSpeed){

  analogWrite(enb, leftSpeed);
  analogWrite(ena, rightSpeed);

//change depending on polarity
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void left(int leftSpeed, int rightSpeed){

  analogWrite(enb, leftSpeed);
  analogWrite(ena, rightSpeed);

//change depending on polarity
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void right(int leftSpeed, int rightSpeed){

  analogWrite(enb, leftSpeed);
  analogWrite(ena, rightSpeed);

//change depending on polarity
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stop(){
//change depending on polarity
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

//NOTE: the motor can be calibrated between 0 - 255
void lineDetection(){
  if((digitalRead(lineLeft) == white) && (digitalRead(lineRight) == white)){
    Serial.println("BOTH IR DETECTED");

    backward(100,115);
    delay(1);

    right(100,115);
    delay(700);

    forward(100,115);
    delay(1);
  }

  if((digitalRead(lineLeft) == white) && (digitalRead(lineRight) == black)){
    Serial.println("LEFT IR DETECTED");

    backward(100,115);
    delay(1);

    right(100,115);
    delay(700);

    forward(100,115);
    delay(1);
  }

  if((digitalRead(lineLeft) == black) && (digitalRead(lineRight) == white)){
    Serial.println("RIGHT IR DETECTED");

    backward(100,115);
    delay(1);

    left(100,115);
    delay(700);

    forward(100,115);
    delay(1);
  }

  if((digitalRead(lineLeft) == black) && (digitalRead(lineRight) == black)){
    Serial.println("SAFE AREA");

    forward(100,115);
    delay(1);
  }
}

void distanceDetection(){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);

  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 30){
    forward(240,255);
    delay(1);
  }

  if (distance > 30){
    lineDetection();
  }
}


void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);

  pinMode(leftLine, INPUT);
  pinMode(rightLine, INPUT);

  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  Serial.begin(9600);

  //can be change depending on how many seconds needed before the bot start
  delay(2500);
}

void loop() {
  distanceDetection();
}
