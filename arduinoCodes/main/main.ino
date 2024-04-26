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
float weights[5] = { -131960.656250, 597871.125000, 30257.791016, -19310.861328, -37382.253906 };
float temp, press, humidity, h2, ethanol;
float sensorData[5];
int timer = 0;
int predictionResult;
float h;

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

  cli();

  // Timer1 kesmesi ayarlanıyor
  TCNT1 = 0;
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 15624;  // Bir saniye çalışması için gerekli zaman kesmesi frekansı
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  sei();
}

ISR(TIMER1_COMPA_vect) {
  timer++;
  if (timer == 180) {
    float prediction = 0;
    for (int j = 0; j < 5; j++) {
      Serial.println(sensorData[j]);
      prediction += sensorData[j] * weights[j];
    }
    h = sigmoid(prediction);
    predictionResult = h >= 0.5 ? 1 : 0;

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
    timer = 0;
  }
}

void loop() {
  temp = bme.readTemperature();

  press = bme.readPressure() / 100.0F;

  humidity = bme.readHumidity();

  h2 = analogRead(A1);

  ethanol = analogRead(A2);

  sensorData[0] = temp;
  sensorData[1] = humidity;
  sensorData[2] = h2;
  sensorData[3] = ethanol;
  sensorData[4] = press;
}
