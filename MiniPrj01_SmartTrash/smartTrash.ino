#include <Servo.h>

//khai báo chân của cảm biến siêu âm
const int trigPin = 9;
const int echoPin = 10;

//khai báo chân của servo 
const int servoPin = 11;

//ngưỡng khoảng cách (cm)
const int acpDistance = 5;

long duration;
int distance;

Servo myServo; //tạo object servo

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myServo.attach(servoPin); //gán chân cho servo
  myServo.write(0); //góc ban đầu là 0

  Serial.begin(9600);
}

void loop() {
  //để tín hiệu ổn định, đặt về low trước khi set high
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10); //giữ trong khoảng 10 micro sec để gửi xung điện (cái này cảm biến yêu cầu)
  digitalWrite(trigPin, LOW);

  //đo thời gian sóng âm đi và về (thời gian pin ở mức HIGH)
  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  //in kc lên serial
  Serial.print("Distance: ");
  Serial.println(distance);

  if(distance <= acpDistance){
    myServo.write(105);
    delay(3000); //delay 5s
    myServo.write(0); //Đóng nắp
  }

  delay(100);
}
