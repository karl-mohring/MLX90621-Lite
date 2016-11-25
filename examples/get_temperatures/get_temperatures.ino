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
    sensor.get_temperatures(temperatures);

    for(int y=0;y<64;y+=16){ //go through all the rows
        Serial.print('[');
        for(int x=0;x<16;x++){ //go through all the columns
            Serial.print(temperatures[y+x], 2);

            if (x < 15) {
                Serial.print(", ");
        }
        Serial.println(']');
    }

    delay(500);
}
