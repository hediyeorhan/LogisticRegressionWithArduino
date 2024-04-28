#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define MAX_COLUMNS 6
#define MAX_TRAIN_DATA_NUMBER 50103
#define LEARNING_RATE 0.05
#define EPOCHS 500
#define MAX_TEST_DATA_NUMBER 12526

float train_data[MAX_TRAIN_DATA_NUMBER][MAX_COLUMNS];
float test_data[MAX_TEST_DATA_NUMBER][MAX_COLUMNS];
int train_data_number = 0;
int test_data_number = 0;
float weights[MAX_COLUMNS-1] = {0}; 


void readTrainData(const char *filePath)
{
    FILE *file = fopen(filePath, "r");

    if (file == NULL)
    {
        perror("An error occurred while opening the file");
        exit(EXIT_FAILURE);
    }

    char row[MAX_TRAIN_DATA_NUMBER];
    char *token;
    int i;

    while (fgets(row, sizeof(row), file) && train_data_number < MAX_TRAIN_DATA_NUMBER)
    {
        i = 0;
        token = strtok(row, " ");
        while (token != NULL && i < MAX_COLUMNS)
        {
            train_data[train_data_number][i] = atof(token);
            token = strtok(NULL, " ");
            i++;
        }
        train_data_number++;
    }

    fclose(file);
}

void readTestData(const char *filePath)
{
    FILE *file = fopen(filePath, "r");

    if (file == NULL)
    {
        perror("An error occurred while opening the file");
        exit(EXIT_FAILURE);
    }

    char satir[MAX_TEST_DATA_NUMBER];
    char *token;
    int i;

    while (fgets(satir, sizeof(satir), file) && test_data_number < MAX_TEST_DATA_NUMBER)
    {
        i = 0;
        token = strtok(satir, " ");
        while (token != NULL && i < MAX_COLUMNS)
        {
            test_data[test_data_number][i] = atof(token);
            token = strtok(NULL, " ");
            i++;
        }
        test_data_number++;
    }

    fclose(file);
}

void initializeWeights()
{
    srand(time(NULL));
    for (int i = 0; i < MAX_COLUMNS - 1; i++)
    {
        weights[i] = ((float)rand() / RAND_MAX) - 0.5;
    }
}

float sigmoid(float z)
{
    return 1.0 / (1.0 + exp(-z));
}

float calculateTrainAcc(int epoch)
{
    int true_pred = 0;
    for (int i = 0; i < train_data_number; i++)
    {
        float prediction = 0;
        for (int j = 0; j < MAX_COLUMNS - 1; j++)
        {
            prediction += train_data[i][j] * weights[j];
        }
        float h = sigmoid(prediction);
        int tahmin = h >= 0.5 ? 1.000000 : 0.000000; 

        if (tahmin == train_data[i][MAX_COLUMNS - 1])
        {
            true_pred++;
        }
    }

    float acc = (float)true_pred / train_data_number * 100;
    printf("%d. Epoch Accuracy : %.2f%%\n", epoch, acc);
    return acc;
}

void trainLogReg()
{
    float max_acc = 0;
    float acc = 0;
    float mse = 0;
    float min_mse = HUGE_VALF;
    int max_epoch = 0;
    float max_weights[MAX_COLUMNS-1] = {0};

    initializeWeights();

    for (int epoch = 0; epoch < EPOCHS; epoch++)
    {
        for (int i = 0; i < train_data_number; i++)
        {
            float prediction = 0;
            for (int j = 0; j < MAX_COLUMNS - 1; j++)
            {
                prediction += train_data[i][j] * weights[j];
            }
            float h = sigmoid(prediction);
            float error = train_data[i][MAX_COLUMNS - 1] - h;

            for (int j = 0; j < MAX_COLUMNS - 1; j++)
            {
                weights[j] += LEARNING_RATE * error * train_data[i][j];
            }
        }
 
        float total_squared_error = 0;
        for (int i = 0; i < train_data_number; i++)
        {
            float prediction = 0;
            for (int j = 0; j < MAX_COLUMNS - 1; j++)
            {
                prediction += train_data[i][j] * weights[j];
            }
            float h = sigmoid(prediction);
            float squared_error = pow(train_data[i][MAX_COLUMNS - 1] - h, 2); // Kare hata hesabı
            total_squared_error += squared_error; // Toplam kare hataya ekleniyor.
        }
        
        mse = total_squared_error / train_data_number;

        acc = calculateTrainAcc(epoch);
        mse = total_squared_error / train_data_number;
        if(acc > max_acc)
        {
            max_acc = acc;
            max_epoch = epoch;
            min_mse = mse;
            memcpy(max_weights, weights, sizeof(weights));
        }
    }

    FILE *file = fopen("TrainResults.txt", "w");
    if (file == NULL)
    {
        perror("An error occurred while creating the file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Min Loss : %.6f\n", min_mse);
    fprintf(file, "Max Epoch : %d\n", max_epoch);
    fprintf(file, "Max Accuracy : %.2f%%\n", max_acc);
    fprintf(file, "Max Weights : \n");
    for (int j = 0; j < MAX_COLUMNS - 1; j++)
    {
        fprintf(file, "W%d: %.6f\n", j + 1, max_weights[j]);
    }

    fclose(file);
        
}

void test()
{
    int true_pred = 0;
    int false_pred = 0;
    int true_positive = 0;
    int false_negative = 0;
    int true_negative = 0;
    int false_positive = 0;
    float total_squared_error = 0;
    
    for (int i = 0; i < test_data_number; i++)
    {
        float prediction = 0;
        for (int j = 0; j < MAX_COLUMNS - 1; j++)
        {
            prediction += test_data[i][j] * weights[j];
        }
        float h = sigmoid(prediction);
        float squared_error = pow(test_data[i][MAX_COLUMNS - 1] - h, 2); // Kare hata hesabı
        total_squared_error += squared_error; // Toplam kare hataya ekleniyor.
        int pred = h >= 0.5 ? 1 : 0;
        
        if (pred == test_data[i][MAX_COLUMNS - 1])
        {
            true_pred++;
            if (pred == 1)
                true_positive++;
            else
                true_negative++;
        }
        else
        {
            false_pred++;
            if (pred == 1)
                false_positive++;
            else
                false_negative++;
        }
    }
    
    float accuracy = (float)true_pred / (true_pred + false_pred) * 100;
    float precision = (float)true_positive / (true_positive + false_positive);
    float recall = (float)true_positive / (true_positive + false_negative);
    float f1_score = 2 * (precision * recall) / (precision + recall);
    float mse = total_squared_error / test_data_number;
        
    FILE *file = fopen("TestResults.txt", "w");
    if (file == NULL)
    {
        perror("An error occurred while creating the file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "Test Accuracy : %.2f%%\n", accuracy);
    fprintf(file, "True Prediction Number : %d\n", true_pred);
    fprintf(file, "Precision: %.2f\n", precision);
    fprintf(file, "Recall: %.2f\n", recall);
    fprintf(file, "F1 Score: %.2f\n", f1_score);
    fprintf(file, "MSE: %.6f\n", mse);
    fprintf(file, "\n\n");
    fprintf(file, "\t\tConfusion Matrix:\n\n");
    fprintf(file, "%20s %10s %10s\n", " ", "Predicted 0", "Predicted 1");
    fprintf(file, "%20s %10d %10d\n", "Actual 0", true_negative, false_positive);
    fprintf(file, "%20s %10d %10d\n", "Actual 1", false_negative, true_positive);

    fclose(file);
}

int main()
{
    const char *filePathTrain = "dataset/train_smoke_detection_iot.csv";
    readTrainData(filePathTrain);

    const char *filePathTest = "dataset/test_smoke_detection_iot.csv";
    readTestData(filePathTest);

    trainLogReg();
    
    test();

    return EXIT_SUCCESS;
}