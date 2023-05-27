#include <Arduino.h>
#include "local/data/Events/events.hpp"

//* Objects
EventHandler eventHandler;

//* Global variables
const int led1 = 4;

void setup() {
    pinMode(led1, OUTPUT);
    eventHandler.begin();
}

void loop() {
    eventHandler.loop();
}