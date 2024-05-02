#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 35744
#define MAX_DATA_NUMBER 35744
#define MAX_NEW_COLUMNS 6
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
    FILE *file = fopen("dataset/smoke_detection_iot_equal.csv", "r");
    FILE *trainFile = fopen("dataset/train_smoke_detection_iot.csv", "w");
    FILE *testFile = fopen("dataset/test_smoke_detection_iot.csv", "w");

    if (file == NULL || trainFile == NULL || testFile == NULL)
    {
        perror("An error occurred while opening the file");
        return EXIT_FAILURE;
    }

    char row[MAX_LINE_LENGTH];
    float new_data[MAX_DATA_NUMBER][MAX_NEW_COLUMNS];
    int data_number = 0;

    fgets(row, sizeof(row), file);

    while (fgets(row, sizeof(row), file) && data_number < MAX_DATA_NUMBER)
    {
        int i = 0;
        char *token = strtok(row, ",");
        int new_index = 0;
        while (token != NULL && i < MAX_NEW_COLUMNS)
        {

            new_data[data_number][new_index] = atof(token);
            new_index++;

            token = strtok(NULL, ",");
            i++;
        }
        data_number++;
    }

    shuffle(new_data, data_number);

    int train_number = data_number * TRAIN_PERCENTAGE / 100;

    for (int k = 0; k < train_number; k++)
    {
        for (int j = 0; j < MAX_NEW_COLUMNS; j++)
        {
            fprintf(trainFile, "%f", new_data[k][j]);
            if (j < MAX_NEW_COLUMNS - 1)
            {
                fprintf(trainFile, " ");
            }
        }
        fprintf(trainFile, "\n");
    }

    for (int k = train_number; k < data_number; k++)
    {
        for (int j = 0; j < MAX_NEW_COLUMNS; j++)
        {
            fprintf(testFile, "%f", new_data[k][j]);
            if (j < MAX_NEW_COLUMNS - 1)
            {
                fprintf(testFile, " ");
            }
        }
        fprintf(testFile, "\n");
    }

    int value_label[2] = {0};
    for (int i = 0; i < data_number; i++)
    {
        if (new_data[i][MAX_NEW_COLUMNS - 1] == 0.000000 || new_data[i][MAX_NEW_COLUMNS - 1] == 1.000000)
        {
            value_label[(int)new_data[i][MAX_NEW_COLUMNS - 1]]++;
        }
    }
    printf("Label value number:\n");
    printf("Label 0: %d\n", value_label[0]);
    printf("Label 1: %d\n", value_label[1]);

    fclose(file);
    fclose(trainFile);
    fclose(testFile);

    return EXIT_SUCCESS;
}