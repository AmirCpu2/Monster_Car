
void setup() {
  // put your setup code here, to run once:
  
  /*--------------  initial Pins  --------------*/
  pinMode(2,OUTPUT);//Beep
  pinMode(3,OUTPUT);//LED Back "RED"
  pinMode(4,OUTPUT);//LED HeadLight LOW-Power
  pinMode(5,OUTPUT);//LED HeadLight HiGHT-Power
  pinMode(6,OUTPUT);//LED Front
  /*----------------  serialBigin ------------------*/
  Serial.begin(9600);
  delay(10);
  
}

/************************************
 * function Process commands Start
 ************************************/
 void processCommand() {
  if(!Serial.available()) { return; }
  
  String command = Serial.readString();
  
  switch(command[0])//LED Controller
  {
    case 'F'://front LED
    case 'f':
    
    if(command[1] == '1')
    {
      digitalWrite(6,HIGH);
    }
    else if(command[1] == '0')
    {
        digitalWrite(6,LOW);
    }
      
    break;
    
    case 'S'://LED Back "RED"
    case 's':
    if(command[1] == '1')
    {
      digitalWrite(3,HIGH);
    }
    else if(command[1] == '0')
    {
        digitalWrite(3,LOW);
    }
    
    break;
    
    case 'H'://LED HeadLight
    case 'h':
    if(command[1] == 2)//LED HeadLight HiGHT-Power
    {
      digitalWrite(5,HIGH);
      digitalWrite(4,LOW);
    }
    else if(command[1] == '1')//LED HeadLight LOW-Power
    {
        digitalWrite(5,LOW);
        digitalWrite(4,HIGH);
    }
    else if(command[1] == '0')//LED HeadLight OFF
    {
        digitalWrite(5,LOW);
        digitalWrite(4,LOW);
    }
    
    break;
    
    case 'B'://Beep
    case 'b':
    if(command[1] == '1')
    {
      digitalWrite(2,HIGH);
    }
    else if(command[1] == '0')
    {
        digitalWrite(2,LOW);
    }
    
    break;
    
    case 'W':
    case 'w':
    Serial.print("Status:\nPORT2=");
    Serial.println((digitalRead(2) > 0 ? 1 : 0 ) );
    Serial.print("PORT3=");
    Serial.println((digitalRead(3) > 0 ? 1 : 0 ) );
    Serial.print("PORT4=");
    Serial.println( (digitalRead(4) > 0 ? 1 : 0 ) );
    Serial.print("PORT5=");
    Serial.println( (digitalRead(5) > 0 ? 1 : 0 ) );
    Serial.print("PORT6=");
    Serial.println((digitalRead(6) > 0 ? 1 : 0 ) );
    
    
    break;
    default:
    Serial.println("Unknown command. Try these:");
    Serial.println(" F# - set LED Front [range 0..1]");
    Serial.println(" S# - set LED Stop [range 0..1]");
    Serial.println(" H# - set LED High light [range 0..2]");
    Serial.println(" B# - set Bazzer Voice [range 0..1]");
    Serial.println(" W - Who is (return status)");
    
  }//switch on command
  
}

/************************************
 * function Process commands Stop
 ************************************/
 
void loop() {
  // put your main code here, to run repeatedly:

  /*----------------  Check Serial  ------------------*/
  //if Command Resive => process commands Function run
  if(Serial.available())
  {
    processCommand();
    delay(100);
  }
}
