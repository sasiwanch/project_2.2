#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int motorPin1 = 8;// Blue   - 28BYJ48 pin 1
int motorPin2 = 9;// Pink   - 28BYJ48 pin 2
int motorPin3 = 10;// Yellow - 28BYJ48 pin 3
int motorPin4 = 11;// Orange - 28BYJ48 pin 4
int motorSpeed = 3;//variable to set stepper speed
char val = '0';
int timeo = 0;
int x;
int floora = 1;
int futurefloor;
void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);

  lcd.begin();
  lcd.backlight();
  lcd.noCursor();
  lcd.noBlink();

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print((String("Floor : ") + String(floora)));
}
void loop(){
  
 if (digitalRead(7)==LOW || digitalRead(6)==LOW || digitalRead(5)==LOW )
  {
    val = Serial.read();
    if (digitalRead(7)==LOW){    
    futurefloor=1;
    }
    if (digitalRead(6)==LOW){
    futurefloor=2;
    } 
    if (digitalRead(5)==LOW){
    futurefloor=3;
    }     
    x = (futurefloor-floora)*1200;
    floora=futurefloor;
    Serial.println(x);
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print((String("Floor : ") + String(floora)));
    delay(500);
  }
  if (x>0){    
    timeo++;    
    counterclockwise();   
    if(timeo == x-1){
      delay(500);
      tone(3,440);
      delay(500);
      noTone(3);
    }
  }
  if (x<0){
    timeo--;
    clockwise();
    if(timeo == x+1){
      delay(500);
      tone(3,440);
      delay(500);
      noTone(3);
    }
  }             
  if (timeo == x){
  timeo = 0;
  x=0;
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  digitalWrite(13,LOW);
  digitalWrite(12,HIGH);
  }      
  Serial.println(timeo) ;
  
}
void counterclockwise (){
  // 1
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  // 2
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay (motorSpeed);
  // 3
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  // 4
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(motorSpeed);
}

void clockwise(){
 // 1
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(motorSpeed);
  // 2
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay (motorSpeed);
  // 3
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  // 4
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
}

