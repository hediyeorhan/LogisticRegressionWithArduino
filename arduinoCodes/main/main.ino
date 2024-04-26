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

// Optimum ağırlık değerlerini tanımlayın
float weights[6] = { -131960.656250, 597871.125000, 30257.791016, -19310.861328, -37382.253906 };

// Sigmoid fonksiyonu
float sigmoid(float z) {
  return 1.0 / (1.0 + exp(-z));
}

void setup() {
  // Sensörlerinizin bağlantılarını yapın
  Serial.begin(9600);
  bme.begin();
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(buzzer, OUTPUT);
}
float temp, press, humidity, h2, ethanol;
void loop() {

  temp = bme.readTemperature();

  press = bme.readPressure() / 100.0F;

  humidity = bme.readHumidity();

  h2 = analogRead(A1);

  ethanol = analogRead(A2);

  float sensorData[6] = { temp, humidity, h2, ethanol, press };

  // Lojistik regresyon modelini uygulayın ve tahminleri yapın
  float prediction = 0;
  for (int j = 0; j < 5; j++) {
    Serial.println(sensorData[j]);
    prediction += sensorData[j] * weights[j];
  }
  float h = sigmoid(prediction);
  int predictionResult = h >= 0.5 ? 1 : 0;


  Serial.print("\nTahmin: ");
  Serial.println(predictionResult);

  if (predictionResult == 1) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
  } else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(buzzer, LOW);
  }

  // Bekleme süresi ekleyebilirsiniz
  delay(1000);
}
