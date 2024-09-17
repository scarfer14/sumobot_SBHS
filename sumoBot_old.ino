//SUMOBOT MAIN PROGRAM

// Motor Pins L298n Motor driver
int in1 = 6;
int in2 = 7;
int in3 = 5;
int in4 = 4;

int ena = 9; //pwm
int enb = 3; //pwm

// Ir Sensor pins
int ir_left = 10;
int ir_right = 11;

int white = 0;
int black = 1;

// Distance  Sensor pins
int dist_left = A1;
int dist_right = A2;

int dist_range_left = 150;
int dist_range_right = 150;

int dist_left_val;
int dist_right_val;

//Ultrasonic Module pins
int trig_right = 8;
int echo_right = 2;
float ultra_val_right;
float ultra_range_right = 0.31;

//int trig_left = 13;
//int echo_left = 12;
//float ultra_val_left;
//float ultra_range_left = 0.31;



//Motor Code
void forward(int speed_left, int speed_right){
  analogWrite(ena, speed_right);
  analogWrite(enb, speed_left);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void backward(int speed_left, int speed_right){
  analogWrite(ena, speed_right);
  analogWrite(enb, speed_left);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void left(int speed_left, int speed_right){
  analogWrite(ena, speed_right);
  analogWrite(enb, speed_left);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void right(int speed_left, int speed_right){
  analogWrite(ena, speed_right);
  analogWrite(enb, speed_left);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stop_motor(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void search_speed(){ //need to calibrate
  forward(130,150);
  delay(1);
}

void turn_right(){ //need to calibrate
  stop_motor();
  delay(5);

  right(230,255);
  delay(100);

  left(230,255);
  delay(10);
}

void turn_left(){ //need to calibrate
  stop_motor();
  delay(5);

  left(230,255);
  delay(150);

  right(230,255);
  delay(10);
}

void semi_right(){ //need to calibrate
  right(230,255);
  delay(10);
}

void semi_left(){ //need to calibrate
  left(230,255);
  delay(10);
}

void edge_back(){ //need to calibrate
  backward(230,255);
  delay(300);

  stop_motor();
  delay(10);
  forward(230,255);
  delay(10);
}


//IR code
void ir_prog(){
  if((digitalRead(ir_left) == white) && (digitalRead(ir_right) == white)){ //both WHITE
    edge_back();

    turn_right();

    forward(230,255);
    delay(1);

    //Serial.println("BOTH IR WHITE");
  }

  if((digitalRead(ir_left) == white) && (digitalRead(ir_right) == black)){ //left WHITE
    edge_back();

    turn_right();

    forward(230,255);
    delay(1);

    //Serial.println("LEFT IR WHITE");
  }

  if((digitalRead(ir_left) == black) && (digitalRead(ir_right) == white)){ //right WHITE
    edge_back();

    turn_left();

    forward(230,255);
    delay(1);

    //Serial.println("RIGHT IR WHITE");
  }

  if((digitalRead(ir_left) == black) && (digitalRead(ir_right) == black)){ //both BLACK (SAFE AREA)
     search_speed();

     //Serial.println("SEARCHING...");
   }

}


//Distance code
void distance_prog(){
  dist_left_val = analogRead(dist_left);
  dist_right_val = analogRead(dist_right);

  if(dist_left_val > dist_range_left){
    turn_left();

    forward(230,255);
    delay(1);

    //Serial.print("Left Distance: ");
    //Serial.println(dist_left_val);
  }

  if(dist_right_val > dist_range_right){
    turn_right();

    forward(230,255);
    delay(1);

    //Serial.print("Right Distance: ");
    //Serial.println(dist_right_val);
  }
}


//Utrasonic code
void ultrasonic_prog(){
  digitalWrite(trig_right,LOW);
  delayMicroseconds(5);
  digitalWrite(trig_right,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_right,LOW);
  ultra_val_right = pulseIn(echo_right,HIGH);
  ultra_val_right = ultra_val_right*0.0001657;


  if(ultra_val_right > ultra_range_right){
    ir_prog();
    distance_prog();
  }

  if(ultra_val_right < ultra_range_right){
    Serial.print("RIGHT: ");
    Serial.println(ultra_val_right);

    forward(230,255);
    delay(10);
  }
}


void setup()
{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);

  pinMode(ir_left, INPUT);
  pinMode(ir_right, INPUT);

  pinMode(dist_left, INPUT);
  pinMode(dist_right, INPUT);

  pinMode(trig_right,OUTPUT);
  pinMode(echo_right,INPUT);
  //pinMode(trig_left,OUTPUT);
  //pinMode(echo_left,INPUT);

  Serial.begin(9600);

  delay(3500); //Adjust for the 5 seconds delay
}

void loop()
{
  ultrasonic_prog();
}