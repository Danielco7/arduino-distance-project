const int trigPin = 13;
const int echoPin = 12;
const int buzzer = 11; // Passive buzzer
const int greenLED = 10;
const int yellowLED = 9;
const int redLED = 8;

long duration;
double distance;
double maxDistanceInches = 12; // Max range

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  digitalWrite(buzzer, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);

  Serial.begin(9600); // Start serial monitor
  Serial.println("Ultrasonic Sensor Initialized...");
}

void loop() {
  // Send trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read echo pulse duration
  duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout

  // Debugging: Print raw duration
  Serial.print("Duration: ");
  Serial.println(duration);

  // Convert to cm then to inches
  distance = duration * 0.034 / 2;
  distance = distance / 2.54;

  // Debugging: Print the calculated distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" inches");

  // LED & Buzzer logic
  if (distance > 0 && distance < maxDistanceInches) {
    digitalWrite(greenLED, HIGH);
    Serial.println("Green LED ON");
  } else {
    digitalWrite(greenLED, LOW);
  }

  if (distance > 0 && distance < (maxDistanceInches * 0.66)) {
    digitalWrite(yellowLED, HIGH);
    Serial.println("Yellow LED ON");
  } else {
    digitalWrite(yellowLED, LOW);
  }

  if (distance > 0 && distance < (maxDistanceInches * 0.33)) {
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzer, HIGH);
    Serial.println("Red LED ON - Buzzer ON");
  } else {
    digitalWrite(redLED, LOW);
    digitalWrite(buzzer, LOW);
  }

  delay(500); // Small delay to avoid spamming the serial monitor
}
