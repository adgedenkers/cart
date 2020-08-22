#include <Servo.h>

int cm = 0;
int inches = 0;
int power1 = 0;
int minimum = 0;
int power2 = 0;
int power3 = 0;
int powerMax = 0;
int servo_pin = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

Servo servo_9;

void setup()
{
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  servo_9.attach(9);

}

void loop()
{
  // set threshold distance to activate LEDs
  minimum = 110;
  power1 = 90;
  power2 = 70;
  power3 = 40;
  powerMax = 20;
  // measure the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(7, 6);
  Serial.println(cm);
  if (cm > minimum) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    servo_9.write(0);
    Serial.println("no power");
  }
  if (cm < minimum && cm >= power1) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    servo_9.write(30);
    Serial.println("power 1");
  }
  if (cm < power1 && cm >= power2) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    servo_9.write(60);
    Serial.println("power 2");
  }
  if (cm < power2 && cm >= power3) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    servo_9.write(90);
    Serial.println("power 3");
  }
  if (cm < power3 && cm >= powerMax) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    servo_9.write(110);
    Serial.println("max power");
  }
  delay(0); // Wait for 0 millisecond(s)
}
