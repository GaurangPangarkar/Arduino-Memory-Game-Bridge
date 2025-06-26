int numLeds = 4;
int buttonPins[] = {2, 4, 6, 8};
int ledPins[] = {3, 5, 7, 9};

const int PATTERN_LENGTH = 4; // Let's fix it at 4 for now, for simplicity

// This array (list) will store the secret pattern the Arduino generates
int gamePattern[PATTERN_LENGTH];

int currentGuessIndex = 0; // Starts at 0 (the first step of the pattern)

// For simple debouncing (ignoring rapid presses)
long lastButtonPressTime = 0;
const long DEBOUNCE_DELAY = 550; // A bit longer delay for simpler debouncing

void setup() {
  Serial.begin(9600); // Initialize standard Serial communication with the computer
  
  for (int i = 0; i < numLeds; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    pinMode(ledPins[i], OUTPUT);
  }
  randomSeed(analogRead(A0));

  // Generate the first (and only) pattern for this simple game
  generateNewPattern();
  delay(1000); 
  Serial.println("Game Ready!");
  delay(3000);
  Serial.println("Watch pattern.");
  delay(5000);
  displayPattern();

  Serial.println("Now your turn!");
  delay(3000);
  Serial.println("Watch pattern.");
  delay(3000);
}

void loop() {
  if (currentGuessIndex < PATTERN_LENGTH) { // If there are still more steps to guess
    // Loop through each possible button (Button 0, Button 1, Button 2, Button 3)
    for (int i = 0; i < numLeds; i++) {
      int buttonState = digitalRead(buttonPins[i]); // Read if button 'i' is pressed

      if (buttonState == LOW && (millis() - lastButtonPressTime > DEBOUNCE_DELAY)) {
        lastButtonPressTime = millis(); // Remember the time this button was pressed

        digitalWrite(ledPins[i], HIGH);
        delay(100);
        digitalWrite(ledPins[i], LOW);

        if (i == gamePattern[currentGuessIndex]) { // Is YOUR pressed button 'i' the same as the Arduino's secret button at this step?
          Serial.println("Correct!");
          currentGuessIndex++; // Move to the next step in the pattern

          // Check if the entire pattern has been guessed correctly
          if (currentGuessIndex == PATTERN_LENGTH) {
            Serial.println("YOU WON!");
            allLedsOn();  // Turn all LEDs on for a win signal
            delay(4000);
            allLedsOff();
            
            currentGuessIndex = 0; // Reset the guess index for the new pattern
            generateNewPattern();  // Create a brand new 4-LED pattern
            delay(5000);           // Pause before showing the new pattern
            displayPattern();      // Show the new pattern
            allLedsOff();          // Make sure LEDs are off after display
            Serial.println("Now your turn!");
            delay(5000);
          }
        } else { // You pressed the WRONG button
          Serial.println("WRONG!");
          delay(2000);
          Serial.println("Watch pattern.");
          allLedsBlink(); // Blink all LEDs for a lose signal
          delay(2000);
          allLedsOff();
          Serial.println("Game finished.");
          delay(3000);
          Serial.println("Reset Arduino");
          delay(5000);
          while (true); // Stop the game loop here (optional, you could restart or just end)
        }
      }
    }
  }
}

void generateNewPattern() {
  Serial.println("Generating");
  delay(1000);
  Serial.println("New pattern.");
  for (int i = 0; i < PATTERN_LENGTH; i++) {
    // Pick a random LED (0, 1, 2, or 3 for 4 LEDs)
    gamePattern[i] = random(numLeds);
  }
}

// This function (recipe) knows how to light up the LEDs to show the current pattern
void displayPattern() {
  Serial.println("Display Pattern");
  for (int i = 0; i < PATTERN_LENGTH; i++) {
    int ledToLight = gamePattern[i];       // Get which LED to light up from our pattern list
    digitalWrite(ledPins[ledToLight], HIGH); // Turn that LED ON
    delay(600); // Keep it on for a bit longer so it's easier to see
    digitalWrite(ledPins[ledToLight], LOW);  // Turn that LED OFF
    delay(300); // Pause briefly before the next LED
  }
  Serial.println("Pattern");
  delay(2000);
  Serial.println("displayed");
  delay(2000);
}

// Helper function: Turn all LEDs ON
void allLedsOn() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
}

// Helper function: Turn all LEDs OFF
void allLedsOff() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

// Helper function: Blink all LEDs
void allLedsBlink() {
  for (int j = 0; j < 3; j++) { // Blink 3 times
    allLedsOn();
    delay(200);
    allLedsOff();
    delay(200);
  }
}