#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_COLUMNS 7
#define MAX_VERI_SAYISI 1600
#define LEARNING_RATE 0.01
#define TOLERANCE 0.0001
#define EPOCHS 157
#define MAX_TEST_VERI_SAYISI 400

float train_veri[MAX_VERI_SAYISI][MAX_COLUMNS];
float test_veri[MAX_TEST_VERI_SAYISI][MAX_COLUMNS];
int veri_sayisi = 0;
int test_veri_sayisi = 0;
float weights[MAX_COLUMNS] = {0}; 

void veriOku(const char *dosyaYolu)
{
    FILE *dosya = fopen(dosyaYolu, "r");

    if (dosya == NULL)
    {
        perror("Dosya açılırken hata oluştu");
        exit(EXIT_FAILURE);
    }

    char satir[MAX_VERI_SAYISI];
    char *token;
    int i;

    while (fgets(satir, sizeof(satir), dosya) && veri_sayisi < MAX_VERI_SAYISI)
    {
        i = 0;
        token = strtok(satir, " ");
        while (token != NULL && i < MAX_COLUMNS)
        {
            train_veri[veri_sayisi][i] = atof(token);
            token = strtok(NULL, " ");
            i++;
        }
        veri_sayisi++;
    }

    fclose(dosya);
}

void veriTestOku(const char *dosyaYolu)
{
    FILE *dosya = fopen(dosyaYolu, "r");

    if (dosya == NULL)
    {
        perror("Dosya açılırken hata oluştu");
        exit(EXIT_FAILURE);
    }

    char satir[MAX_TEST_VERI_SAYISI];
    char *token;
    int i;

    while (fgets(satir, sizeof(satir), dosya) && test_veri_sayisi < MAX_TEST_VERI_SAYISI)
    {
        i = 0;
        token = strtok(satir, " ");
        while (token != NULL && i < MAX_COLUMNS)
        {
            test_veri[test_veri_sayisi][i] = atof(token);
            token = strtok(NULL, " ");
            i++;
        }
        test_veri_sayisi++;
    }

    fclose(dosya);
}


float sigmoid(float z)
{
    return 1.0 / (1.0 + exp(-z));
}

void egitim_dogrulugu_hesapla(int epoch)
{
    int dogru_tahmin = 0;
    for (int i = 0; i < veri_sayisi; i++)
    {
        float prediction = 0;
        for (int j = 0; j < MAX_COLUMNS - 1; j++)
        {
            prediction += train_veri[i][j] * weights[j];
        }
        float h = sigmoid(prediction);
        int tahmin = h >= 0.5 ? 1.000000 : 0.000000; 

        if (tahmin == train_veri[i][MAX_COLUMNS - 1])
        {
            dogru_tahmin++;
        }
    }

    float dogruluk = (float)dogru_tahmin / veri_sayisi * 100;
    printf("%d. Epoch sonu eğitim doğruluğu: %.2f%%\n", epoch, dogruluk);
}


void egit_lojistik_regresyon()
{
 
    for (int epoch = 0; epoch < EPOCHS; epoch++)
    {

        for (int i = 0; i < veri_sayisi; i++)
        {
            float prediction = 0;
            for (int j = 0; j < MAX_COLUMNS - 1; j++)
            {
                prediction += train_veri[i][j] * weights[j];
            }
            float h = sigmoid(prediction);
            float error = train_veri[i][MAX_COLUMNS - 1] - h;

            for (int j = 0; j < MAX_COLUMNS - 1; j++)
            {
                weights[j] += LEARNING_RATE * error * train_veri[i][j];
            }
        }
        
        // Hata toleransına ulaşıldığında eğitimi durdurma
        float total_error = 0;
        for (int i = 0; i < veri_sayisi; i++)
        {
            float prediction = 0;
            for (int j = 0; j < MAX_COLUMNS - 1; j++)
            {
                prediction += train_veri[i][j] * weights[j];
            }
            float h = sigmoid(prediction);
            total_error += fabs(train_veri[i][MAX_COLUMNS - 1] - h);
        }
        if (total_error < TOLERANCE)
        {
            printf("Hata toleransı %f'e ulaşıldı. Eğitim sona erdi.\n", TOLERANCE);
            break;
        }
        egitim_dogrulugu_hesapla(epoch);
    }

    // Eğitim sonucunda elde edilen ağırlıkları yazdırma
    printf("Eğitim tamamlandı. Elde edilen ağırlıklar:\n");
    for (int j = 0; j < MAX_COLUMNS - 1; j++)
    {
        printf("W%d: %.6f\n", j + 1, weights[j]);
    }
}


void test_et()
{
    int dogru_tahmin = 0;
    for (int i = 0; i < test_veri_sayisi; i++)
    {
        float prediction = 0;
        for (int j = 0; j < MAX_COLUMNS - 1; j++)
        {
            prediction += test_veri[i][j] * weights[j];
        }
        float h = sigmoid(prediction);
        int tahmin = h >= 0.5 ? 1.000000 : 0.000000; 
        if (tahmin == test_veri[i][MAX_COLUMNS - 1])
        {
            dogru_tahmin++;
        }
    }
    float accuracy = (float)dogru_tahmin / test_veri_sayisi * 100;
    printf("Test doğruluğu: %.2f%%\n", accuracy);
    printf("Doğru tahmin sayisi : %d\n", dogru_tahmin);
    printf("test veri sayisi : %d", test_veri_sayisi);
}
int main()
{
    const char *dosyaYolu = "datasets/train_smoke_detection_iot.csv";
    veriOku(dosyaYolu);

    const char *testDosyaYolu = "datasets/test_smoke_detection_iot.csv";
    veriTestOku(testDosyaYolu);

    egit_lojistik_regresyon();
    test_et();

    return EXIT_SUCCESS;
}
