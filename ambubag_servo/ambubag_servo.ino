#include <Servo.h>
int bpm ;
int potpin_speed = 0;
int potpin_angle = 1;
int potpin_inc = 2;
int min_angle = 50;
int val_speed;  
int val_angle;  
int val_inc;
int angle_pcnt;
 int steps;
 int loop_time;
Servo myservo;  

#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27,20,4);

int pos =10;   
void setup() {
  Serial.begin(9600);
  myservo.attach(8); 
  lcd.init(); 
  lcd.backlight();  
}






void loop() {

   val_speed = analogRead(potpin_speed);            
  val_speed = map(val_speed, 0, 1023, 1, 20); 
     val_angle = analogRead(potpin_angle);            
  val_angle = map(val_angle , 0, 1023,min_angle, 136);
  angle_pcnt = val_angle;
  angle_pcnt = map(angle_pcnt, 136, min_angle, 0, 100) ;
  steps = val_angle;
  steps = map(steps, 136, min_angle, 0, (136-min_angle));                                                                  
   val_inc = analogRead(potpin_inc);            
  val_inc = map(val_inc , 0, 1023, 1, 5); 
   
   
   loop_time = (val_speed*steps);
   int loop_time_ex = (val_speed*(round(steps/4))); 
   if(angle_pcnt>5){
   bpm = (60000/((loop_time+loop_time_ex)+2000));
   }
   if(angle_pcnt<5){
   bpm = 0;
   }
 Serial.print(" loop(s): ");
 Serial.print(loop_time);  
 Serial.print(" steps : ");
 Serial.print(steps);  
 Serial.print(" bpm : ");
 Serial.print(bpm);  
    Serial.print(" Speed: ");
  Serial.print(val_speed);
  Serial.print( " Angle: " );
  Serial.print(val_angle);
    Serial.print( " Percent: " );
  Serial.print(angle_pcnt);
  Serial.print( " Step: " );
  Serial.println(val_inc);
  lcdfnc(val_angle,angle_pcnt, val_speed, bpm);
  
  for (pos =val_angle;pos <= 136; pos += 4) {
    myservo.write(pos);              
    delay(val_speed);                      
  }
  delay(1000);
  for (pos = 136; pos >=val_angle;pos -= 1) { 
    myservo.write(pos);              
    delay(val_speed);                      
  }
delay(1000);
}



void lcdfnc(int angleS,int pcntS, int speedS, int bpmS){
 lcd.init();   
 lcd.backlight();
  lcd.setCursor(1,1);
 lcd.print("Squeeze (%): ");
  lcd.setCursor(1,2);
 lcd.print("BPM:  ");
  lcd.setCursor(14,1); 
 lcd.print(pcntS);
 lcd.setCursor(14,2);
   lcd.print(bpmS);

 
};
