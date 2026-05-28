/*
Detect distance with Ultrasonic based on traffic light

Wire connection
HC-SR04 Pin	Arduino UNO	Notes
VCC	5 V	Must be 5 V (not 3.3 V)
GND	GND	Common ground with Arduino
TRIG	D9	Trigger output
ECHO	D10	Needs direct connection — not through a resistor divider if using Uno
LED_RED	D2 → 220 Ω → GND	
LED_YELLOW	D3 → 220 Ω → GND	
LED_GREEN	D4 → 220 Ω → GND	
*/

#define TRIG_PIN 9
#define ECHO_PIN 10

#define LED_RED    2
#define LED_YELLOW 3
#define LED_GREEN  4

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
}

void loop() {
  // Send trigger pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  float distance = duration * 0.0343 / 2;

  // Debug info
  Serial.print("Duration: ");
  Serial.print(duration);
  Serial.print(" us, Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Traffic light logic
  if (distance > 25 && distance < 400) {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
  } 
  else if (distance > 10 && distance <= 25) {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_RED, LOW);
  } 
  else if (distance <= 10 && distance > 0) {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, HIGH);
  } 
  else {
    // No reading or out of range
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
  }

  delay(500);
}
