#include <Arduino.h>

#define LED_FREQUENCY_UP 12
#define LED_FREQUENCY_DOWN 11
#define LED_FREQUENCY_HIGH 10
#define LED_FREQUENCY_MEDIUM 9
#define LED_FREQUENCY_LOW 8
#define BUTTON_FREQUENCY_UP 7
#define BUTTON_FREQUENCY_DOWN 6
#define BUZZER 5

const long buzzerStrokeKeyDelayMs = 400;
unsigned long buttonFrequencyUpLastMillis = 0;
unsigned long buttonFrequencyDownLastMillis = 0;

const int buzzerFrequencyHigh = 1000;
const int buzzerFrequencyMedium = 500;
const int buzzerFrequencyVariation = 50;

int buzzerFrequency;

void setup() {
    pinMode(LED_FREQUENCY_UP, OUTPUT);
    pinMode(LED_FREQUENCY_DOWN, OUTPUT);
    pinMode(LED_FREQUENCY_HIGH, OUTPUT);
    pinMode(LED_FREQUENCY_MEDIUM, OUTPUT);
    pinMode(LED_FREQUENCY_LOW, OUTPUT);
    pinMode(BUTTON_FREQUENCY_UP, INPUT_PULLUP);
    pinMode(BUTTON_FREQUENCY_DOWN, INPUT_PULLUP);
    pinMode(BUZZER, OUTPUT);

    buzzerFrequency = 50;
}

void loop() {

    unsigned long currentMillis = millis();

    if (digitalRead(BUTTON_FREQUENCY_UP) == LOW) {
        if (currentMillis - buttonFrequencyUpLastMillis >= buzzerStrokeKeyDelayMs) {
            digitalWrite(LED_FREQUENCY_UP, HIGH);
            buzzerFrequency = buzzerFrequency + buzzerFrequencyVariation;
            buttonFrequencyUpLastMillis = currentMillis;
        }
    } else {
        digitalWrite(LED_FREQUENCY_UP, LOW);
    }

    if (digitalRead(BUTTON_FREQUENCY_DOWN) == LOW) {
        if (currentMillis - buttonFrequencyDownLastMillis >= buzzerStrokeKeyDelayMs) {
            digitalWrite(LED_FREQUENCY_DOWN, HIGH);
            buzzerFrequency = buzzerFrequency - buzzerFrequencyVariation;
            buttonFrequencyDownLastMillis = currentMillis;
        }
    } else {
        digitalWrite(LED_FREQUENCY_DOWN, LOW);
    }

    if (buzzerFrequency >= buzzerFrequencyHigh) {
        digitalWrite(LED_FREQUENCY_HIGH, HIGH);
        digitalWrite(LED_FREQUENCY_MEDIUM, HIGH);
        digitalWrite(LED_FREQUENCY_LOW, HIGH);
    } else if (buzzerFrequency >= buzzerFrequencyMedium) {
        digitalWrite(LED_FREQUENCY_HIGH, LOW);
        digitalWrite(LED_FREQUENCY_MEDIUM, HIGH);
        digitalWrite(LED_FREQUENCY_LOW, HIGH);
    } else {
        digitalWrite(LED_FREQUENCY_HIGH, LOW);
        digitalWrite(LED_FREQUENCY_MEDIUM, LOW);
        digitalWrite(LED_FREQUENCY_LOW, HIGH);
    }

    tone(BUZZER, buzzerFrequency);
    
}