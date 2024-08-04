#include <Arduino.h>

// Define the pins for the ultrasonic sensor, LED, and buzzer
const int trigPin = 23;   // Trig pin of the ultrasonic sensor
const int echoPin = 22;   // Echo pin of the ultrasonic sensor
const int ledPin = 15;    // LED pin
const int buzzerPin = 4;  // Buzzer pinX 

// Define distance thresholds (in cm)
const int motionThreshold = 5;  // Distance change threshold to detect motion

void setup() {
  // Initialize the pins as input or output
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Initialize serial communication for debugging
  Serial.begin(115200);
}

void loop() {
  static long previousDistance = 50;
  long duration, distance;

  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, return the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Detect motion based on distance change
  if (abs(distance - previousDistance) > motionThreshold) {
    // Turn on the LED
    digitalWrite(ledPin, HIGH);
    // Turn on the buzzer
    digitalWrite(buzzerPin, HIGH);

    // Print a message to the serial monitor
    Serial.println("Motion detected!");
  } else {
    // Turn off the LED
    digitalWrite(ledPin, LOW);
    // Turn off the buzzer
    digitalWrite(buzzerPin, LOW);
  }

  // Update the previous distance
  previousDistance = distance;

  // Delay to avoid rapid toggling
  delay(100);
}
