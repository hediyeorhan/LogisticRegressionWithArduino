#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 2000
#define MAX_COLUMNS 16
#define MAX_VERI_SAYISI 2000
#define MAX_YENI_COLUMNS (MAX_COLUMNS - 9)
#define TRAIN_PERCENTAGE 80

void shuffle(float yeni_veri[][MAX_YENI_COLUMNS], int veri_sayisi)
{
    srand(time(NULL)); 
    for (int i = veri_sayisi - 1; i > 0; i--)
    {
        int j = rand() % (i + 1); 
        float temp[MAX_YENI_COLUMNS];
        memcpy(temp, yeni_veri[i], MAX_YENI_COLUMNS * sizeof(float));
        memcpy(yeni_veri[i], yeni_veri[j], MAX_YENI_COLUMNS * sizeof(float));
        memcpy(yeni_veri[j], temp, MAX_YENI_COLUMNS * sizeof(float));
    }
}

int main()
{
    FILE *dosya = fopen("datasets/smoke_detection_iot.csv", "r");
    FILE *train_dosya = fopen("datasets/train_smoke_detection_iot.csv", "w");
    FILE *test_dosya = fopen("datasets/test_smoke_detection_iot.csv", "w");

    if (dosya == NULL || train_dosya == NULL || test_dosya == NULL)
    {
        perror("Dosya açılırken hata oluştu");
        return EXIT_FAILURE;
    }

    char satir[MAX_LINE_LENGTH];
    float yeni_veri[MAX_VERI_SAYISI][MAX_YENI_COLUMNS];
    int veri_sayisi = 0;

    fgets(satir, sizeof(satir), dosya); 

    while (fgets(satir, sizeof(satir), dosya) && veri_sayisi < MAX_VERI_SAYISI)
    {
        int i = 0;
        char *token = strtok(satir, ",");
        int yeni_index = 0;
        while (token != NULL && i < MAX_COLUMNS)
        {
            if (i != 0 && i != 1 && i != 4 && i != 9 && i != 10 && i != 11 && i != 12 && i != 13 && i != 14)
            {
                yeni_veri[veri_sayisi][yeni_index] = atof(token);
                yeni_index++;
            }
            token = strtok(NULL, ",");
            i++;
        }
        veri_sayisi++;
    }

    shuffle(yeni_veri, veri_sayisi); 

    int train_sayisi = veri_sayisi * TRAIN_PERCENTAGE / 100;

  
    for (int k = 0; k < train_sayisi; k++)
    {
        for (int j = 0; j < MAX_YENI_COLUMNS; j++)
        {
            fprintf(train_dosya, "%f", yeni_veri[k][j]);
            if (j < MAX_YENI_COLUMNS - 1)
            {
                fprintf(train_dosya, " "); 
            }
        }
        fprintf(train_dosya, "\n"); 
    }

 
    for (int k = train_sayisi; k < veri_sayisi; k++)
    {
        for (int j = 0; j < MAX_YENI_COLUMNS; j++)
        {
            fprintf(test_dosya, "%f", yeni_veri[k][j]);
            if (j < MAX_YENI_COLUMNS - 1)
            {
                fprintf(test_dosya, " "); 
            }
        }
        fprintf(test_dosya, "\n"); 
    }

    int deger_sayisi[2] = {0};
    for (int i = 0; i < veri_sayisi; i++)
    {

        if (yeni_veri[i][6] == 0.000000 || yeni_veri[i][6] == 1.000000)
        {
            deger_sayisi[(int)yeni_veri[i][6]]++;
        }
    }
    printf("Label sütundaki değer sayısı:\n");
    printf("Label 0: %d\n", deger_sayisi[0]);
    printf("Label 1: %d\n", deger_sayisi[1]);

    fclose(dosya);
    fclose(train_dosya);
    fclose(test_dosya);

    return EXIT_SUCCESS;
}
