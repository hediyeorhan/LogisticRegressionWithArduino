#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define led1 3
#define led2 4
#define buzzer 5

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

Adafruit_BME280 bme;

int sensorDegerq3, sensorDegerq8;

void setup() {
  Serial.begin(9600);
  bme.begin(); 
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(buzzer, OUTPUT);

}

void loop() {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" °C");

    Serial.print("Pressure = ");
    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    sensorDegerq3 = analogRead(A1);
    Serial.print("H2 = ");
    Serial.println(sensorDegerq3);

    sensorDegerq8 = analogRead(A2);
    Serial.print("Ethanol = ");
    Serial.println(sensorDegerq3);

    // test etmek icin

    if(sensorDegerq3 > 900)
    {
      digitalWrite(buzzer, HIGH);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
    }
    else
    {
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
    }


    Serial.println();

}
