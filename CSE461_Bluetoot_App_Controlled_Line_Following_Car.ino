//CSE461 Hands on Project
//Summer 2020

char dataIn = 'S';        //Character/Data coming from the phone.
char determinant; 
char det;

//Motor module
int EN_A = A1;
int EN_B = A2;

int IN1 = 2;
int IN2 = 3;
int IN3 = 4;
int IN4 = 5;

//IR Sensor Array
int OUT1 = 6;
int OUT2 = 7;
int OUT3 = 8;
int OUT4 = 9;
int OUT5 = 10;

int sout1;
int sout2;
int sout3;
int sout4;
int sout5;

//Mode changing switch
int sw = 11;
int ss;

//Mode LED
int led = 12;

void setup(){
  Serial.begin(9600); //bluetooth start
  
  pinMode(EN_A, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN_B, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(OUT1, INPUT);
  pinMode(OUT2, INPUT);
  pinMode(OUT3, INPUT);
  pinMode(OUT4, INPUT);
  pinMode(OUT5, INPUT); 
  
  pinMode(sw, INPUT);

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  delay(3000);
}

void loop(){

  ss = digitalRead(sw);
  while(ss == HIGH){
    digitalWrite(led, LOW);
    det = check();
    if(det == 'F') //forward
    {
        Serial.print(det);
        analogWrite(EN_A, 200);
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(EN_B, 200);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        det = check();
    }
    if(det == 'B') //back
    {
        Serial.print(det);
        analogWrite(EN_A, 200);
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        analogWrite(EN_B, 200);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        det = check();  
    }
    if(det == 'L') //left
    {
        Serial.print(det);
        analogWrite(EN_A, 200);
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(EN_B, 200);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        det = check();  
    }
    if(det == 'R') //right
    {
        Serial.print(det);
        analogWrite(EN_A, 200);
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        analogWrite(EN_B, 200);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        det = check();   
    }
    if(det == 'S') //stop
    {
        Serial.print(det);
        analogWrite(EN_A, 200);
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        analogWrite(EN_B, 200);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        det = check();   
    }
    ss = digitalRead(sw);
  }


  //======================================================
  while(ss==LOW){
    digitalWrite(led, HIGH);
    sout1 = digitalRead(OUT1);
    sout2 = digitalRead(OUT2);
    sout3 = digitalRead(OUT3);
    sout4 = digitalRead(OUT4);
    sout5 = digitalRead(OUT5);
    
    if(sout3==LOW && sout2==HIGH && sout4==HIGH) //forward
    {
        analogWrite(EN_A, 200);
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(EN_B, 200);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
    }
    if(sout2==LOW) //left
    {
        analogWrite(EN_A, 200);
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(EN_B, 200);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH); 
    }
    if(sout4==LOW) //right
    {
        analogWrite(EN_A, 200);
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        analogWrite(EN_B, 200);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);   
    }
    if(sout1==LOW && sout2==LOW && sout3==LOW && sout4==LOW && sout5==LOW) //stop
    {
        analogWrite(EN_A, 200);
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        analogWrite(EN_B, 200);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW); 
    }
    ss = digitalRead(sw);  
  }
}  
  
//===============================================================================================  
int check(){
  if (Serial.available() > 0){   //Check for data on the serial lines.   
    dataIn = Serial.read();      //Get the character sent by the phone and store it in 'dataIn'.
    
    if (dataIn == 'F'){     
      determinant = 'F';
    }  
    else if (dataIn == 'B'){ 
      determinant = 'B'; 
    }
    else if (dataIn == 'L'){ 
      determinant = 'L';
    }
    else if (dataIn == 'R'){ 
      determinant = 'R';
    } 
    else {
      determinant = 'S';
    }
  }
  return determinant;
}
