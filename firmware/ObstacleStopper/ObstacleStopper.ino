/*
  Ultrasonic proximity-stop controller
  ------------------------------------
  Arduino-based, open-loop two-motor controller.
  Stops when distance is below 20 cm or the echo is missing.

  This is a reviewed reference implementation based on the repository's
  original 2024 sketch. Hardware behavior has NOT been revalidated.

  IMPORTANT: This is NOT autonomous obstacle avoidance and is NOT a
  safety-rated collision-prevention system.
*/

const uint8_t TRIG_PIN = 2;
const uint8_t ECHO_PIN = 3;

const uint8_t IN1_PIN = 4;
const uint8_t IN2_PIN = 5;
const uint8_t IN3_PIN = 6;
const uint8_t IN4_PIN = 7;

const uint8_t ENA_PIN = 11;
const uint8_t ENB_PIN = 10;

const float STOP_DISTANCE_CM = 20.0f;
const uint8_t MOTOR_PWM = 200;       // Range: 0..255
const unsigned long ECHO_TIMEOUT_US = 30000UL;
const unsigned long LOOP_DELAY_MS = 100UL;

void stopMotors() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, LOW);
}

void moveForward() {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  pinMode(ENA_PIN, OUTPUT);
  pinMode(ENB_PIN, OUTPUT);

  digitalWrite(TRIG_PIN, LOW);
  stopMotors();  // Start with motor direction inputs off.

  analogWrite(ENA_PIN, MOTOR_PWM);
  analogWrite(ENB_PIN, MOTOR_PWM);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  const unsigned long durationUs = pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT_US);

  if (durationUs == 0UL) {
    stopMotors();
    Serial.println(F("No echo: motors stopped"));
    delay(LOOP_DELAY_MS);
    return;
  }

  // Approximate speed of sound: 0.0343 cm/us. Round trip: divide by 2.
  const float distanceCm = (durationUs * 0.0343f) / 2.0f;
  Serial.print(F("Distance (cm): "));
  Serial.println(distanceCm, 1);

  if (distanceCm < STOP_DISTANCE_CM) {
    stopMotors();
  } else {
    moveForward();
  }

  delay(LOOP_DELAY_MS);
}
