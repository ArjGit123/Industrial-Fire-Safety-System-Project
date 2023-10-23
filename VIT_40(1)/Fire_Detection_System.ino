#include<LiquidCrystal.h>
#include<DHT.h>
#define DHTTYPE DHT11

#define TEMP 7     
#define MQ2 A1         
#define MQ136 A0 
#define Buzzer 11            
#define LED 12               
#define Gas_Thres 300
#define Temp_Thres 58        
#define FlamePin 10
float Temp;
float MQ2_Value;
float MQ136_Value;
int Flame = HIGH;

LiquidCrystal lcd(9, 8, 5, 4, 3, 2);
DHT dht(TEMP, DHTTYPE);

void setup() 
{
  pinMode(TEMP, INPUT);
  pinMode(MQ2, INPUT);
  pinMode(MQ136, INPUT);       
  pinMode(Buzzer, OUTPUT);     
  pinMode(LED, OUTPUT);        
  pinMode(FlamePin, INPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
  dht.begin();
}

int temperature() 
{
  Temp = dht.readTemperature();
  if (Temp > Temp_Thres) return 1;             //if smoke is detected
  else return 0;
  delay (50);                      
}
  
int mq2()
{
  MQ2_Value = analogRead(MQ2);           // reads the analog value from smoke sensor
  if ( MQ2_Value > Gas_Thres ) return 1;            //if smoke is detected
  else return 0;
  delay (50);                      
}


int mq136()
{
  MQ136_Value = analogRead(MQ136);           // reads the analog value from smoke sensor
  if ( MQ136_Value > Gas_Thres ) return 1;            //if smoke is detected
  else return 0;
  delay (50);                      
}


int flamesensor() 
{
  Flame = digitalRead(FlamePin);
  if (Flame == LOW) return 1;
  else return 0;
  delay(50);
}


void loop()
{
  int t = temperature();
  int g1 = mq2();
  int g2 = mq136();
  int f = flamesensor();
  if (t == 1 || g1 == 1 || g2 == 1 || f == 1)
  {
    digitalWrite(LED,HIGH);     // turns the LED on
    digitalWrite(Buzzer,HIGH);
    lcd.setCursor(2,0);          
    lcd.print("Fire Alert !!"); 
    lcd.setCursor(1,1);           
    lcd.print("Evacuate Place");
  }
  else
  {
    digitalWrite(LED, LOW);          //  turns the LED off
    digitalWrite(Buzzer,LOW); 
    lcd.clear();
  }
  delay(10);
} 
  
  

