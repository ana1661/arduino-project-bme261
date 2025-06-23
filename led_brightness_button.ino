const int ledPin = 10;
const int buttonPin = 5;

int brightnessLevels[] = {0, 85, 150, 255};  // Off, Low, Medium, High
int level = 0;

bool lastButtonReading = HIGH;  // For raw input (debounce)
bool buttonState = HIGH;        // Stable state (debounced)
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // Using internal pull-up resistor
  analogWrite(ledPin, brightnessLevels[level]);  // Start at OFF

  Serial.begin(9600);  // Start serial communication
  Serial.println("Starting LED Brightness Controller");
}

void loop() {
  bool currentReading = digitalRead(buttonPin);
  Serial.print("Raw reading: ");
  Serial.print(currentReading);
  Serial.print(" | Debounced state: ");
  Serial.println(buttonState);

  // Debounce: reset the timer when a change in the button is detected
  if (currentReading != lastButtonReading) {
    lastDebounceTime = millis();  // Reset debounce timer
  }

  // Only proceed if the state is stable for long enough
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (currentReading != buttonState) {
      buttonState = currentReading;

      // On button press (LOW due to pull-up)
      if (brightnessLevels[level] == 255) {
      // Blink twice to indicate max brightness
        for (int i = 0; i < 2; i++) {
          digitalWrite(ledPin, LOW);
          delay(100);
          digitalWrite(ledPin, HIGH);
          delay(100);
        }
        analogWrite(ledPin, 255);  // Return to full brightness
      }

        Serial.print("Button Pressed! New brightness level: ");
        String label[] = {"Off", "Low", "Medium", "High"};
        Serial.print(" (");
        Serial.print(label[level]);
        Serial.println(")");
      }
    }
  }

  lastButtonReading = currentReading;
}
