#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 62629
#define MAX_COLUMNS 16
#define MAX_DATA_NUMBER 62629
#define MAX_NEW_COLUMNS (MAX_COLUMNS - 10)
#define TRAIN_PERCENTAGE 80

void shuffle(float new_data[][MAX_NEW_COLUMNS], int data_number)
{
    srand(time(NULL));
    for (int i = data_number - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        float temp[MAX_NEW_COLUMNS];
        memcpy(temp, new_data[i], MAX_NEW_COLUMNS * sizeof(float));
        memcpy(new_data[i], new_data[j], MAX_NEW_COLUMNS * sizeof(float));
        memcpy(new_data[j], temp, MAX_NEW_COLUMNS * sizeof(float));
    }
}

int main()
{
    FILE *file = fopen("dataset/smoke_detection_iot.csv", "r");
    FILE *eq_data = fopen("dataset/smoke_detection_iot_equal.csv", "w");

    if (file == NULL || eq_data == NULL)
    {
        perror("An error occurred while opening the file");
        return EXIT_FAILURE;
    }

    char row[MAX_LINE_LENGTH];
    float new_data[MAX_DATA_NUMBER][MAX_NEW_COLUMNS];
    int data_number = 0;
    int value_label[2] = {0};

    fgets(row, sizeof(row), file);

    while (fgets(row, sizeof(row), file) && data_number < MAX_DATA_NUMBER)
    {
        int i = 0;
        char *token = strtok(row, ",");
        int new_index = 0;
        while (token != NULL && i < MAX_COLUMNS)
        {
            if (i != 0 && i != 1 && i != 4 && i != 5 && i != 9 && i != 10 && i != 11 && i != 12 && i != 13 && i != 14)
            {
                new_data[data_number][new_index] = atof(token);
                new_index++;
            }
            token = strtok(NULL, ",");
            i++;
        }

        if (new_index > 0)
        {
            int label = (int)new_data[data_number][new_index - 1];
            if (label == 0 || label == 1)
            {
                value_label[label]++;
            }
        }
        data_number++;
    }

    int min_label_count = value_label[0] < value_label[1] ? value_label[0] : value_label[1];
    shuffle(new_data, data_number);
    int label_0 = 0, label_1 = 0;

    for (int k = 0; k < data_number; k++)
    {
        int label = (int)new_data[k][MAX_NEW_COLUMNS - 1];
        if ((label == 0 && label_0 < min_label_count) || (label == 1 && label_1 < min_label_count))
        {
            for (int j = 0; j < MAX_NEW_COLUMNS; j++)
            {
                fprintf(eq_data, "%f", new_data[k][j]);
                if (j < MAX_NEW_COLUMNS - 1)
                {
                    fprintf(eq_data, ",");
                }
            }
            fprintf(eq_data, "\n");

            // Etiketi kontrol et ve ilgili sayacı güncelle
            if (label == 0)
            {
                label_0++;
            }
            else if (label == 1)
            {
                label_1++;
            }

            // Her iki etiket de min_label_count sayısına ulaştığında döngüyü sonlandır
            if (label_0 == min_label_count && label_1 == min_label_count)
            {
                break;
            }
        }
    }

    int label_count[2] = {0};
    for (int i = 0; i < data_number; i++)
    {
        if (new_data[i][MAX_NEW_COLUMNS - 1] == 0.000000 || new_data[i][MAX_NEW_COLUMNS - 1] == 1.000000)
        {
            label_count[(int)new_data[i][MAX_NEW_COLUMNS - 1]]++;
        }
    }
    printf("Label value number:\n");
    printf("Label 0: %d\n", label_count[0]);
    printf("Label 1: %d\n", label_count[1]);

    fclose(file);
    fclose(eq_data);

    return EXIT_SUCCESS;
}