
//Set up libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);
#include <Servo.h>     // Attaching a Library!!
Servo myservo;  // create servo object to control a servo



void setup() {
  
   Serial.begin(9600);

   //Blank LCD screen
   lcd.init();               // initialize the lcd 
   lcd.backlight();

   //Intialize pins
   //Analog pins
   pinMode(A0,INPUT);        //light sensor
   myservo.attach(A1);       //servo
   pinMode(A2,INPUT);        //potentiometer
   pinMode(A3,INPUT);        //x of joystick
   pinMode(A4,INPUT);        //y of joystick
   pinMode(A5,INPUT_PULLUP); //z of joystick
   
   //Digital pins
   pinMode(2, INPUT_PULLUP); //button 1
   pinMode(3, OUTPUT);       //led blue
   pinMode(4, OUTPUT);       //led green
   pinMode(5, OUTPUT);       //led red
   pinMode(6, OUTPUT);       //ultrasonic trig
   pinMode(7, INPUT);        //ultrasonic echo
   pinMode(8, OUTPUT);       //thunder
   pinMode(9, OUTPUT);       //lightning 1
   pinMode(10, OUTPUT);      //lightning 2
   pinMode(11, OUTPUT);      //lightning 3
   pinMode(12, OUTPUT);      //lightning 4
   
}

//Intialize variables
int xVal; 
int yVal; 
int zVal;
int xP; 
int yP; 
int zP;
int val;


   
void loop (){
  
   //More intializing variables
   long duration, inch=10;

   //Show story/instructions on LCD screen
   lcd.setCursor(0,0);
   lcd.print("Press the button"); 
   lcd.setCursor(0,1);
   lcd.print("to continue.");

   //Wait until the button is pushed
   while(digitalRead(2)==HIGH){
       //RGB LED flashes lights
       digitalWrite(3, HIGH);
       digitalWrite(4, LOW);
       digitalWrite(5, LOW);
       delay(150);
       digitalWrite(3, LOW);
       digitalWrite(4, HIGH);
       digitalWrite(5, LOW);
       delay(250);
       digitalWrite(3, LOW);
       digitalWrite(4, LOW);
       digitalWrite(5, HIGH);
       delay(150);
   }

   //RGB LED stops flashing
   digitalWrite(3, HIGH);
   digitalWrite(4, HIGH);
   digitalWrite(5, HIGH);

   //Next part of story/instructions
   //Will repeat throughout code
   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("\"Where are we?\"");
   
   //Wait for button push
   //Will repeat throughout code
   while(digitalRead(2)==HIGH){}
   
   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("\"Not where, ");
   lcd.setCursor(0,1);
   lcd.print("Marty. When.\"");
   

   while(digitalRead(2)==HIGH){}

   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("Marty & the Doc");
   lcd.setCursor(0,1);
   lcd.print("were in 1955.");
   

   while(digitalRead(2)==HIGH){}

   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("\"Seeing yourself");
   lcd.setCursor(0,1);
   lcd.print("can kill you.\"");
   

   while(digitalRead(2)==HIGH){}

   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("\"What about my");
   lcd.setCursor(0,1);
   lcd.print("parents?\"");
   

   while(digitalRead(2)==HIGH){}

   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("\"I suppose...");
   lcd.setCursor(5,1);
   lcd.print("Why?\"");
   

   while(digitalRead(2)==HIGH){}

   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("\"There's my mom\"");
   

   while(digitalRead(2)==HIGH){}

   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("\"HIDE!\"");
   

   while(digitalRead(2)==HIGH){}

   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("Turn the knob to");
   lcd.setCursor(0,1);
   lcd.print("move to hide");
   
   //Wait for ultrasonic sensor to be less than 1 inch
   //(reading where Marty & Doc are moving with servo)
   while(inch>1) {

      //Read ultrasonic sensor
      digitalWrite(6, LOW);
      delayMicroseconds(2);
      digitalWrite(6, HIGH);
      delayMicroseconds(5);
      digitalWrite(6, LOW);
      duration = pulseIn(7, HIGH);
      inch=duration/74/2;
      
      //Moves Marty & Doc with servo
      //Based on the potentiometer
      val = analogRead(A2);                // reads the value of the pot (0 to 1023)
      val = map(val, 0, 1023, 0, 180);     // scale it for servo (0 to 180) 
      Serial.println(val);                 // prints value to serial monitor
      myservo.write(val);                 // sends PWM value out to servo
   }

   //Goes back to tell the story
   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("\"Phew. That was");
   lcd.setCursor(0,1);
   lcd.print("close.\"");

   while(digitalRead(2)==HIGH){}

   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("\"Too close. Be");
   lcd.setCursor(0,1);
   lcd.print("careful, Marty.\"");

   while(digitalRead(2)==HIGH){}

   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("\"We have to get");
   lcd.setCursor(0,1);
   lcd.print("back home. Now.\"");

   while(digitalRead(2)==HIGH){}

   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("\"We need");
   lcd.setCursor(0,1);
   lcd.print("electricity.\"");

   while(digitalRead(2)==HIGH){}

   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("\"The lightning");
   lcd.setCursor(0,1);
   lcd.print("from the storm!\"");

   while(digitalRead(2)==HIGH){}

   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("\"Make it strike");
   lcd.setCursor(0,1);
   lcd.print("the clock tower\"");

   while(digitalRead(2)==HIGH){}

   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("\"Oh no!");
   lcd.setCursor(0,1);
   lcd.print("A guard!\"");

   while(digitalRead(2)==HIGH){}

   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("Turn off the");
   lcd.setCursor(0,1);
   lcd.print("lights to hide");

   //Wait for lights to turn off
   //Or just light sensor to sense dark
   while(analogRead(A0)>200) {}

   //Continue story
   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("\"We're safe!\"");

   while(digitalRead(2)==HIGH){}

   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("\"Now, lightning");
   lcd.setCursor(0,1);
   lcd.print("needs to move.\"");

   while(digitalRead(2)==HIGH){}

   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("\"It needs to be");
   lcd.setCursor(0,1);
   lcd.print("powerful, too.\"");

   while(digitalRead(2)==HIGH){}

   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("\"So, the thunder");
   lcd.setCursor(0,1);
   lcd.print("should be loud.\"");

   while(digitalRead(2)==HIGH){}

   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("Move a joystick");
   lcd.setCursor(0,1);
   lcd.print("to control storm");

   //Make sure everything is turned off
   noTone(8);
   digitalWrite(9, LOW);
   digitalWrite(12, LOW);
   digitalWrite(11, LOW);
   digitalWrite(10, LOW);

    //Read & map joystick
    xVal=analogRead(A3);
    yVal=analogRead(A4);
    zVal=digitalRead(A5);
    xP=map(xVal,0,1023,0,100);
    yP=map(yVal,0,1023,0,100);
    zP=(1-zVal)*100;
   
   //Create a loop that won't break
   while(analogRead(A0)>2){

      //Read & map joystick in loop
      xVal=analogRead(A3);
      yVal=analogRead(A4);
      zVal=digitalRead(A5);
      xP=map(xVal,0,1023,0,100);
      yP=map(yVal,0,1023,0,100);
      zP=(1-zVal)*100;

      //Intialize variable used to check if position is correct
      //Reset every loop
      int check=0;

      //Move lightning (LED) based on X of joystick  
      if (xP>85){
        digitalWrite(12, HIGH);
        digitalWrite(11, LOW);
        digitalWrite(10, LOW);
        digitalWrite(9, LOW);
      }
     else if (xP>45){
        digitalWrite(11, HIGH);
        digitalWrite(12, LOW);
        digitalWrite(10, LOW);
        digitalWrite(9, LOW);
     }
     else if (xP>20){
        digitalWrite(10, HIGH);
        digitalWrite(12, LOW);
        digitalWrite(11, LOW);
        digitalWrite(9, LOW);
        
        //Check varible increased because it is in correct X position
        check=1;
     }
    else{
        digitalWrite(9, HIGH);
        digitalWrite(12, LOW);
        digitalWrite(11, LOW);
        digitalWrite(10, LOW);
     }

    //Changing thunder (tone) based on joystick Y position
    if (yP>85){
        tone((8), 100);

        //Check varible increased because it is in correct Y position
        check=check+1;
    }
    else if (yP>45){
        tone((8), 200);
    }
    else if (yP>20){
        tone((8), 300);
    }
    else{
         tone((8), 400);
    }

    //If both positions are correct, then check will equal 2
    if (check==2){
      //Leaves loop if check equals 2
      break;
    }
   }

   //Continue story
   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("\"It worked!\"");
   
    //Lightning strikes (all LEDS and buzzer on)
    tone((8), 100);
    digitalWrite(9, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    
   //Story continues. Waits for button push
   while(digitalRead(2)==HIGH){}

   lcd.init();
   lcd.setCursor(0,0);
   lcd.print("\"Let's go!\"");

   //Turns off thunder and lightning (buzzer and LED)
   noTone(8);
   digitalWrite(9, LOW);
   digitalWrite(12, LOW);
   digitalWrite(11, LOW);
   digitalWrite(10, LOW);

   //Wait for button push
   while(digitalRead(2)==HIGH){
    
       //Flash RGB LED
       digitalWrite(3, HIGH);
       digitalWrite(4, LOW);
       digitalWrite(5, LOW);
       delay(150);
       digitalWrite(3, LOW);
       digitalWrite(4, HIGH);
       digitalWrite(5, LOW);
       delay(250);
       digitalWrite(3, LOW);
       digitalWrite(4, LOW);
       digitalWrite(5, HIGH);
       delay(150);
   }


   //Ends story
   lcd.init();
   lcd.setCursor(6,0);
   lcd.print("THE");
   lcd.setCursor(6,1);
   lcd.print("END");

   //Turn off RGB LED
   digitalWrite(3, HIGH);
   digitalWrite(4, HIGH);
   digitalWrite(5, HIGH);

   //Wait for button push to restart the story
   while(digitalRead(2)==HIGH){}
   
   }
   
