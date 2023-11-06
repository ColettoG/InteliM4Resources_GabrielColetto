// Start Simon Game

/* Define pin numbers for LEDs, buttons and speaker: */
const uint8_t buttonPins[] = {16, 2, 17, 5};
const uint8_t ledPins[] = {27, 26, 25, 33};

const int buzzerPin = 32; // Pin that the buzzer is conected

const int resetButton = 34;

#define MAX_GAME_LENGTH 100

/* Global variables - store the game state */
uint8_t gameSequence[MAX_GAME_LENGTH] = {0};
uint8_t gameIndex = 0;

void setup() {
  Serial.begin(9600);

  for (byte i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT);
  }

  pinMode(buzzerPin, OUTPUT);
  pinMode(resetButton, INPUT);

  // The following line primes the random number generator.
  // It assumes pin 4 is floating (disconnected):
  randomSeed(analogRead(16));
}

/* 
The buzzer play in a frequency and duration especific
*/
void playTone(unsigned int frequency, unsigned long duration) {
  tone(buzzerPin, frequency);
  delay(duration);
  noTone(buzzerPin);
}

/**
   Lights the given LED
*/
void lightLedAndPlayTone(byte ledIndex) {
  digitalWrite(ledPins[ledIndex], HIGH);
  playTone(1000, 500);
  digitalWrite(ledPins[ledIndex], LOW);
}


/**
   Plays the current sequence of notes that the user has to repeat
*/
void playSequence() {
  for (int i = 0; i < gameIndex; i++) {
    byte currentLed = gameSequence[i];
    lightLedAndPlayTone(currentLed);
    delay(200);
  }
}

/**
    Waits until the user pressed one of the buttons,
    and returns the index of that button
*/
byte readButtons() {
  while (true) {
    for (byte i = 0; i < 4; i++) {
      byte buttonPin = buttonPins[i];
      if (digitalRead(buttonPin) == HIGH) {
        return i;
      }
    }
    if (digitalRead(resetButton) == HIGH) {
      return -1;
    }
    
    delay(1);
  }
}

/**
   Get the user's input and compare it with the expected sequence.
*/
bool checkUserSequence() {
  for (int i = 0; i < gameIndex; i++) {
    byte expectedButton = gameSequence[i];
    byte actualButton = readButtons();
    lightLedAndPlayTone(actualButton);
    if (expectedButton != actualButton) {
      return false;
    }
  }

  return true;
}

/**
  Play the game over sequence, and report the game score
*/
void gameOver() {
  Serial.print("Game over! your score: ");
  playTone(2000, 2000);
  Serial.println(gameIndex - 1);
  gameIndex = 0;
  delay(200);
  
}

void loop() {

  // Add a random color to the end of the sequence
  gameSequence[gameIndex] = random(0, 4);
  gameIndex++;
  if (gameIndex >= MAX_GAME_LENGTH) {
    gameIndex = MAX_GAME_LENGTH - 1;
  }

  playSequence();
  if (!checkUserSequence()) {
    gameOver();
  }

  delay(300);
}
