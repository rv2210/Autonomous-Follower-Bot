//no functions were created in the code, to increase computation speed (no referencing and function calling)
#define ult1 5  //left ultrasonic trigger
#define ule1 4  //left ultrasonic echo
#define ult2 6  // center ultrasonic tigger
#define ule2 7  //center ultrasonic echo
#define ult3 12  //right ultrasonic trigger
#define ule3 13  //right ultrasonic echo
#define mleft 10 //left motor signal line
#define mright 9 //right motor signal line
#define hcrx 0   //bluetooth receive
#define hctx 1   //bluetooth transmit
#define buzz 3   //buzzer
int dr = 0;
int dl = 0;
int dc = 0;
int right=0;
int left=0;
int straight=0;
float angle=0;
int i=0;
float deg=3.3;    //in degrees 
float dist=0.41;  //in cms
float X=0;
float Y=0;
float XT=0;
float YT=0;
float path[2][4000]; //array to store the path taken
int r;
int c;
int l ;
char junk;
String inputString="";
String inputString1="";
char flag;
//----------------------------------------------------------------
void setup() {
  //initialization
  pinMode(ult1, OUTPUT);
  pinMode(ult2, OUTPUT);
  pinMode(ult3, OUTPUT);
  pinMode(ule1, INPUT);
  pinMode(ule2, INPUT);
  pinMode(ule3, INPUT);
  pinMode(mleft, OUTPUT);
  pinMode(mright, OUTPUT);
  pinMode(hctx, OUTPUT);
  pinMode(hcrx, INPUT);
  pinMode(buzz, OUTPUT);
  Serial.begin(9600);
}
//------------------------------------------------------------------

void loop() {
  flag='z';
  inputString="";
      //receive data from bluetooth
      if(Serial.available()){
  while(Serial.available())
    {
      char inChar = (char)Serial.read(); //read the input
      inputString += inChar;        //make a string of the characters coming on serial
    }
    //Serial.println(inputString);
    while (Serial.available() > 0)  
    { junk = Serial.read() ; }      // clear the serial buffer
    if(inputString == "f"){         //in case of 'f' start the autonomous following mode

  //------------------------------------------------------------------
 while(1)
 {
  //all sensor readings are taken at the same instant so all the further distance comparisons are more relevant
  //read distance from central ultrasonic sensor
  digitalWrite(ult2, LOW);
  delayMicroseconds(2);
  digitalWrite(ult2, HIGH);
  delayMicroseconds(10);
  digitalWrite(ult2, LOW);
  int duration1 = pulseIn(ule2, HIGH);
  dc = (duration1 * .0343) / 2;
  //------------------------------------------------------------------
  //read distance from central ultrasonic sensor
  digitalWrite(ult1, LOW);
  delayMicroseconds(2);
  digitalWrite(ult1, HIGH);
  delayMicroseconds(10);
  digitalWrite(ult1, LOW);
  int duration2 = pulseIn(ule1, HIGH);
  dl = (duration2 * .0343) / 2;
  //----------------------------------------------------------------
  //read distance from central ultrasonic sensor
  digitalWrite(ult3, LOW);
  delayMicroseconds(2);
  digitalWrite(ult3, HIGH);
  delayMicroseconds(10);
  digitalWrite(ult3, LOW);
   int duration3 = pulseIn(ule3, HIGH);
  dr = (duration3 * .0343) / 2;
 //-------------------------------------------------------------------
r= abs(dr); //eliminating negative values that might arise due to noise
c= abs(dc);
l= abs(dl);
if (c<r && c<l && c > 30 && c<120)  //if true, robot moves straight
{
  
      digitalWrite(mright, HIGH);
      delay(0.6);
      digitalWrite(mright, LOW);
      digitalWrite(mleft, HIGH);
      delay(2.4);
      digitalWrite(mleft, LOW);
      delay(3);
      //the path tracing algorithm is executed
      XT= XT - (dist*sin(angle*(3.14/180)));
      YT= YT + (dist*cos(angle*(3.14/180)));
      path [0][i]= XT;
      path[1][i]= YT;
      i++;
      //end of path tracing
      //plotting on smartphone 
      Serial.print("x");
      Serial.println(XT);
      Serial.print("y");
      Serial.println(YT);
      //end of plotting
  
}
else if (l<c && l<r && l<110) //if true, robot turns left
{
      digitalWrite(mright, HIGH);
      delay(0.6);
      digitalWrite(mright, LOW);
      digitalWrite(mleft, HIGH);
      delay(0.6);
      digitalWrite(mleft, LOW);
      delay(3);
      angle= angle + deg; //updating heading angle of bot
      
}
else if (r<c && r<l && r<110) //if true, robot turns right
{
      digitalWrite(mright, HIGH);
      delay(2.4);
      digitalWrite(mright, LOW);
      digitalWrite(mleft, HIGH);
      delay(2.4);
      digitalWrite(mleft, LOW);
      delay(3); 
      angle= angle - deg; //updating heading angle of bot
}
else
{
  if(c>120 && l>110 && r>110) //buzz if target is lost or unavailable
  {
  digitalWrite(buzz, HIGH);
  delay(1000);
  digitalWrite(buzz, LOW);
  }
}
if(Serial.available()) //checking if stop button is pressed
{
flag=(char)Serial.read(); 
junk=Serial.read();
if(flag == 'x'){ //x corresponds to the stop button
 return;
}
}
}
}
else if(inputString == "m"){ //m corresponds to manual mode operation
  while(1)
  {
  flag='z';  
  if(Serial.available())
  flag=(char)Serial.read(); 
  if(flag=='w')  //w corresponds to move straight in manual mode
  {   digitalWrite(mright, HIGH);
      delay(0.6);
      digitalWrite(mright, LOW);
      digitalWrite(mleft, HIGH);
      delay(2.4);
      digitalWrite(mleft, LOW);
      delay(3);
  }
  else if(flag=='a') //a corresponds to turn left in manual mode
  {
      digitalWrite(mright, HIGH);
      delay(0.6);
      digitalWrite(mright, LOW);
      digitalWrite(mleft, HIGH);
      delay(0.6);
      digitalWrite(mleft, LOW);
      delay(3);
  } 
   else if(flag=='d') //d corresponds to turn right in manual mode
   {
      digitalWrite(mright, HIGH);
      delay(2.4);
      digitalWrite(mright, LOW);
      digitalWrite(mleft, HIGH);
      delay(2.4);
      digitalWrite(mleft, LOW);
      delay(3);
   }
   else if(flag=='s') //s corresponds to move backwards in manual mode
   {
      digitalWrite(mright, HIGH);
      delay(2.4);
      digitalWrite(mright, LOW);
      digitalWrite(mleft, HIGH);
      delay(0.6);
      digitalWrite(mleft, LOW);
      delay(3);
   }
   else if(flag=='x') //to stop manual mode
   {
    return;
   }
   }
   }
  }
}
