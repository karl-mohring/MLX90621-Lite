#include "Arduino.h"
#include "MLX90621.h"

int refresh_rate = 16;
MLX90621 sensor;

float temperatures[64];

void setup(){
    Serial.println("Starting MLX90621 thermopile sensor");
    sensor.initialize(refresh_rate);
}

void loop(){
    Serial.println("/n/nReading sensor...");
    sensor.print_temperatures(Serial);
    delay(500);
}
