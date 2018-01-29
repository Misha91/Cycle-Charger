
const int girkon_pin = 8;
const int relay_charge_pin = 12;
const int relay_battery_pin = 10;
const int ledPin =  13;      // the number of the LED pin

const int wheel_d = 400; // диаметр колеса

// the setup routine runs once when you press reset:
void setup() 
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  
  // configure pins
  pinMode(girkon_pin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(relay_charge_pin, OUTPUT);
  pinMode(relay_battery_pin, OUTPUT);
}

unsigned long this_time, last_time, spin_time, prev_time;
long cur_speed;
int girkon_state, last_state, flag;

// the loop routine runs over and over again forever:
void loop() 
{
  unsigned long currentMillis = millis();
  
  //Serial.print("millis = ");
  //Serial.println(currentMillis);
  
  // read the input pin:
  girkon_state = digitalRead(girkon_pin);
  // print out the state of the button:
  //Serial.print("buttonState = ");
  //Serial.println(buttonState);
  
  if (girkon_state == 1)
  {
    if (girkon_state != last_state)
    {
      last_time = this_time;
      this_time = millis();
      spin_time = this_time - last_time;
      cur_speed = (wheel_d * 3.14 / spin_time) * 3.6;
    
      //Serial.print("cur_speed = "); Serial.println(cur_speed);
    }
  }
  else
  {
    //Serial.println(millis() - this_time);
    // если более N sec нет изменений, ставим скорость 0
   if ((millis() - this_time >= 600))
   {
     cur_speed = 0; 
   }
  }
  
  // выводим скорость раз в 500мс
  if (millis() - prev_time >= 500)
  {
     Serial.print("cur_speed = ");
     Serial.println(cur_speed);
      
     prev_time = millis();
  }
  
  if (cur_speed >= 9)
  {
    digitalWrite(ledPin, HIGH);
    digitalWrite(relay_charge_pin, HIGH);
    digitalWrite(relay_battery_pin, HIGH);
    flag = 1;
  }
  
  if (flag)
  {
    if (cur_speed <=2 )
    {
     flag = 0;
     digitalWrite(ledPin, LOW);
     digitalWrite(relay_charge_pin, LOW);
     digitalWrite(relay_battery_pin, LOW); 
    } 
  }
  
 last_state = girkon_state;
  
  
  
  //digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  //delay(100);               // wait for a second
  //digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  //delay(1000);               // wait for a second
  

  //Serial.println("");
}



