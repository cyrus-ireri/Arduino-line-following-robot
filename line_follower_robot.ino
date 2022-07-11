//This code was developed by Cyrus Mwaniki
//Development date 23/10/2021
//Email cyrusmwaniki910@gmail.com
//******************************************
//Motor1 and motor2 are controlled by the L298N motor driver.
//3 Infrared based proximity sensors are used
const int motor1pin1 = 3;
const int motor1pin2 = 2;
const int motor2pin1 = 4;
const int motor2pin2 = 5;
const int motor1Speed = 11;
const int motor2Speed = 10;
const int sensor1Pin = 6;
const int sensor2Pin = 7;
const int sensor3Pin = 8;
unsigned char sensor1;
unsigned char sensor2;
unsigned char sensor3;
class sensor
{
  protected:
  void readSensors()
  {
    sensor1 = digitalRead(sensor1Pin);
    sensor2 = digitalRead(sensor2Pin);
    sensor3 = digitalRead(sensor3Pin);
  }
};
class motion:public sensor
{
  protected:
  void forward()
  {
    digitalWrite(motor1pin1,HIGH);
    digitalWrite(motor1pin2,LOW);
    digitalWrite(motor2pin1,HIGH);
    digitalWrite(motor2pin2,LOW);
  }
  void backward()
  {
    digitalWrite(motor1pin1,LOW);
    digitalWrite(motor1pin2,HIGH);
    digitalWrite(motor2pin1,LOW);
    digitalWrite(motor2pin2,HIGH);
  }
  void right()
  {
    digitalWrite(motor1pin1,HIGH);
    digitalWrite(motor1pin2,LOW);
    digitalWrite(motor2pin1,LOW);
    digitalWrite(motor2pin2,LOW);
  }
  void left()
  {
    digitalWrite(motor1pin1,LOW);
    digitalWrite(motor1pin2,LOW);
    digitalWrite(motor2pin1,HIGH);
    digitalWrite(motor2pin2,LOW);
  }
  void brake()
  {
    digitalWrite(motor1pin1,LOW);
    digitalWrite(motor1pin2,LOW);
    digitalWrite(motor2pin1,LOW);
    digitalWrite(motor2pin2,LOW);
  }
};
class manager:public motion
{
  public:
  void manage()
  {
    readSensors();
    if(sensor1 == LOW && sensor2 == LOW && sensor3 == LOW)
    {
      brake();
    }
    else if(sensor1 == LOW && sensor2 == HIGH && sensor3 == LOW)
    {
      forward();
    }
    else if(sensor1 == HIGH && sensor2 == HIGH && sensor3 == LOW)
    {
      left();
    }
    else if(sensor1 == LOW && sensor2 == HIGH && sensor3 == HIGH)
    {
      right();
    }
  }
};
class configuration
{
  public:
  void configure()
  {
    pinMode(motor1pin1,OUTPUT);
    pinMode(motor1pin2,OUTPUT);
    pinMode(motor2pin1,OUTPUT);
    pinMode(motor2pin2,OUTPUT);
    pinMode(sensor1Pin,INPUT);
    pinMode(sensor2Pin,INPUT);
    analogWrite(motor1Speed,150);
    analogWrite(motor2Speed,150);
  }
};
void setup()
{
  configuration robotConfig;
  robotConfig.configure();
}
void loop()
{
  manager taskmanager;
  taskmanager.manage();
}
