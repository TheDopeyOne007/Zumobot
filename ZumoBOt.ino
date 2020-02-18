int value1=0;
int value2=0;
int value=0;

const int AIA = 6;
const int AIB = 9;
const int BIA = 11;
const int BIB = 10;
byte speed = 255; 

// detects enemy
const int IR_TL = A4;
const int IR_TR = A5;
// detect line
const int IR_BL = A1;
const int IR_BR = A2;

int line_l=0;
int line_r=0;
int found=0;

void setup()
{
  pinMode(IR_TL, INPUT);
  pinMode(IR_TR, INPUT);
  pinMode(IR_BL, INPUT);//sense line L
  pinMode(IR_BR, INPUT);//sense line R when WHITE=1, when BLACK=0
  pinMode(AIA, OUTPUT);   
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT); 
  robotstop();
}

void robotstop()
{
    analogWrite(AIA,0);
    analogWrite(AIB,0); 
    analogWrite(BIA,0);
    analogWrite(BIB,0); 
}

void ir_find() //find opponent
{
  while (found==0)
  {
    analogWrite(AIA,speed);
    analogWrite(AIB,0); 
    analogWrite(BIA,0);
    analogWrite(BIB,speed); 
    value1=analogRead(IR_TL);
    value2=analogRead(IR_TR);
    delay(50);
   if ((value1>10)||(value2>10))
    {
    robotstop();
    delay(10);
    found=1;
    }
   line_l=digitalRead(IR_BL);
   line_r=digitalRead(IR_BR);  
   if ((line_l==HIGH)||(line_r==HIGH)) //if any sensor sense white line
    {
      robotstop();
      delay(10);
      found=1;
    }
  }
}


void fight() //When found opponent
{
  value1=analogRead(IR_TL); //double check opponent
  value2=analogRead(IR_TR); 
  delay(50);
  if ((value1>20)||(value2>20))
  {
        value=value1-value2;
        if (value<0)
        {
        analogWrite(AIA,speed);
        analogWrite(AIB,0); 
        analogWrite(BIA,speed);
        analogWrite(BIB,0); 
        }
        else
        {
        analogWrite(AIA,speed);
        analogWrite(AIB,0); 
        analogWrite(BIA,speed);
        analogWrite(BIB,0); 
         }
        delay(10);
        found=1;  
     }
    else 
    {
         found=0; 
    }
}

void sense_floor_black()
{
  line_l=digitalRead(IR_BL);
  line_r=digitalRead(IR_BR);  
  if ((line_l==LOW)&&(line_r==LOW))//all black
  {//ok, can find opponent / hit opponent
      if (found==0)//search
      {
        ir_find();
      }
      else//found
      {
        fight();
      }
    }
   else if ((line_l==HIGH)&&(line_r==HIGH))//ALL WHITE
   {
    analogWrite(AIA,0);
    analogWrite(AIB,speed); 
    analogWrite(BIA,0);
    analogWrite(BIB,speed);
    delay(500);
    robotstop();
   }
   else if (line_l==HIGH)//L=white, turn right
   {
    analogWrite(AIA,0);
    analogWrite(AIB,speed); 
    analogWrite(BIA,0);
    analogWrite(BIB,speed);
    delay(300);
    analogWrite(AIA,0);
    analogWrite(AIB,speed); 
    analogWrite(BIA,speed);
    analogWrite(BIB,0);
    delay(200);
    robotstop();
   }
   else 
   {
    analogWrite(AIA,0);
    analogWrite(AIB,speed); 
    analogWrite(BIA,0);
    analogWrite(BIB,speed);
    delay(300);
    analogWrite(AIA,speed);
    analogWrite(AIB,0); 
    analogWrite(BIA,0);
    analogWrite(BIB,speed);
    delay(200);
    robotstop();
   }
}

void loop() 
{
sense_floor_black();
}

void backward()
{
 analogWrite(AIA, 0);
 analogWrite(AIB, speed);
 analogWrite(BIA, 0);
 analogWrite(BIB, speed);
}
void forward()
{
 analogWrite(AIA, speed);
 analogWrite(AIB, 0);
 analogWrite(BIA, speed);
 analogWrite(BIB, 0);
}
