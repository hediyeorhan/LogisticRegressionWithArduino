#define led1 3
#define led2 4
#define buzzer 5

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(buzzer, OUTPUT);

}

int sensorDeger;

void loop() {
    sensorDeger = analogRead(A2);

    Serial.println(sensorDeger);

    if(sensorDeger > 800)
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

}
