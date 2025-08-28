#include <Adafruit_SSD1306.h>
#include <Servo.h>

// OLED Display Definitions
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// RoboEyes Library
#include <FluxGarage_RoboEyes.h>
roboEyes roboEyes; // Create an instance of the roboEyes class

// Servo Definitions
Servo leftArmServo; // Create a servo object for the left arm
Servo rightArmServo; // Create a servo object for the right arm

#define LEFT_SERVO_PIN 9 // The pin for the left servo
#define RIGHT_SERVO_PIN 10 // The pin for the right servo

// Standard positions for the arms in degrees
int downPos = 40; // Arm position: down
int middlePos = 90; // Arm position: middle
int upPos = 140; // Arm position: up

// Animation Timers and Flags
// These variables are used to create a non-blocking sequence of events.
unsigned long eventTimer; // Stores the timestamp of the last event
bool event1Played = false; // Flag to ensure the first event plays only once
bool event2Played = false; // Flag for the second event
bool event3Played = false; // Flag for the third event

// Non-blocking servo movement variables
unsigned long lastServoUpdate = 0; // Stores the last time the servos were updated
const int servoInterval = 20; // Interval in milliseconds to update the servo position
int currentLeftPos; // The current position of the left servo
int currentRightPos; // The current position of the right servo
int targetLeftPos; // The target position for the left servo
int targetRightPos; // The target position for the right servo

void setup() {
// Initialize the OLED display
// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C or 0x3D
Serial.println(F("SSD1306 allocation failed"));
for(;;); // Don't proceed, loop forever
}

// Initialize the robo eyes
// Parameters: screen-width, screen-height, max framerate (60-100fps are good)
roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 100);
roboEyes.setPosition(DEFAULT); // Set the eye position to the middle center
roboEyes.close(); // Start with the eyes closed

// Initialize the servos
leftArmServo.attach(LEFT_SERVO_PIN);
rightArmServo.attach(RIGHT_SERVO_PIN);

// Define initial servo positions
currentLeftPos = downPos;
currentRightPos = downPos;
targetLeftPos = downPos;
targetRightPos = downPos;

leftArmServo.write(currentLeftPos);
rightArmServo.write(currentRightPos);

eventTimer = millis(); // Start the animation timer
} // end of setup

void loop() {
// This function must be called continuously to update the eye drawings
roboEyes.update();

// Non-blocking servo movement
// Checks if the specified servoInterval has passed since the last update
if (millis() - lastServoUpdate >= servoInterval) {
lastServoUpdate = millis(); // Reset the timer

// Move the left arm incrementally towards its target position
if (currentLeftPos < targetLeftPos) {
currentLeftPos++;
leftArmServo.write(currentLeftPos);
} else if (currentLeftPos > targetLeftPos) {
currentLeftPos--;
leftArmServo.write(currentLeftPos);
}

// Move the right arm incrementally towards its target position
if (currentRightPos < targetRightPos) {
currentRightPos++;
rightArmServo.write(currentRightPos);
} else if (currentRightPos > targetRightPos) {
currentRightPos--;
rightArmServo.write(currentRightPos);
}
}

// --- Looped Animation Sequence ---
// This section handles a sequence of timed events for the eyes and arms.
// Each event is triggered after a certain amount of time has passed and
// a flag ensures it only happens once.

// Event 1: After 2 seconds, open the eyes and move arms to the middle
if(millis() >= eventTimer + 2000 && event1Played == false){
event1Played = true;
roboEyes.open();
targetLeftPos = middlePos;
targetRightPos = middlePos;
}

// Event 2: After 4 seconds, set the mood to happy, start a laugh animation,
// and move the arms up.
if(millis() >= eventTimer + 4000 && event2Played == false){
event2Played = true;
roboEyes.setMood(HAPPY);
roboEyes.anim_laugh();
targetLeftPos = upPos;
targetRightPos = upPos;
}

// Event 3: After 6 seconds, set the mood to tired and move the arms down.
if(millis() >= eventTimer + 6000 && event3Played == false){
event3Played = true;
roboEyes.setMood(TIRED);
targetLeftPos = downPos;
targetRightPos = downPos;
}

// Event 4: After 8 seconds, close the eyes, reset the mood, and restart the sequence.
if(millis() >= eventTimer + 8000){
roboEyes.close();
roboEyes.setMood(DEFAULT);
// Reset the timer and flags to restart the entire animation loop
eventTimer = millis();
event1Played = false;
event2Played = false;
event3Played = false;
}
// --- End of Looped Animation Sequence ---

} // end of main loop