// Optimum ağırlık değerlerini tanımlayın
float weights[6] = {-2360.538330, -37.335854, -758.514526, 14005.946289, -9092.618164, -1559.964111};

// Sigmoid fonksiyonu
float sigmoid(float z) {
    return 1.0 / (1.0 + exp(-z));
}

void setup() {
    // Sensörlerinizin bağlantılarını yapın
    Serial.begin(9600);
}

void loop() {
    // Sensör verilerini okuyun
    float sensorData[6] = {24.520000, 56.669998, 400.000000, 12712.000000, 19744.000000, 939.843018};

    // Lojistik regresyon modelini uygulayın ve tahminleri yapın
    float prediction = 0;
    for (int j = 0; j < 6; j++) {
        prediction += sensorData[j] * weights[j];
    }
    float h = sigmoid(prediction);
    int predictionResult = h >= 0.5 ? 1 : 0;

    // Tahmin sonucunu işleyin veya görüntüleyin
    Serial.print("Tahmin: ");
    Serial.println(predictionResult);

    // Bekleme süresi ekleyebilirsiniz
    delay(1000);
}
