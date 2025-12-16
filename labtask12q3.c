#include <stdio.h>
#include <stdlib.h>

int main() {

    float *temp_readings = NULL;
    int total_readings = 0;
    int capacity = 3;
    int choice = 1;
    int i;

    float highest_temp;
    float lowest_temp;
    float alert_limit;
    int alert_count = 0;

    temp_readings = (float *)malloc(capacity * sizeof(float));
    if (temp_readings == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter alert temperature threshold: ");
    scanf("%f", &alert_limit);

    while (choice == 1) {

        if (total_readings == capacity) {
            capacity = capacity + 3;
            temp_readings = (float *)realloc(temp_readings, capacity * sizeof(float));
            if (temp_readings == NULL) {
                printf("Reallocation failed\n");
                return 1;
            }
        }

        printf("Enter temperature reading: ");
        scanf("%f", &temp_readings[total_readings]);

        total_readings++;

        printf("Add more readings? (1 = yes, 0 = no): ");
        scanf("%d", &choice);
    }

    highest_temp = temp_readings[0];
    lowest_temp = temp_readings[0];

    for (i = 0; i < total_readings; i++) {

        if (temp_readings[i] > highest_temp)
            highest_temp = temp_readings[i];

        if (temp_readings[i] < lowest_temp)
            lowest_temp = temp_readings[i];

        if (temp_readings[i] > alert_limit)
            alert_count++;
    }

    FILE *fp = fopen("temperature_summary.txt", "w");
    if (fp == NULL) {
        printf("File open failed\n");
        return 1;
    }

    fprintf(fp, "Temperature Monitoring Report\n\n");
    fprintf(fp, "Total Readings: %d\n", total_readings);
    fprintf(fp, "Highest Temperature: %.2f\n", highest_temp);
    fprintf(fp, "Lowest Temperature: %.2f\n", lowest_temp);
    fprintf(fp, "Alert Threshold: %.2f\n", alert_limit);
    fprintf(fp, "Readings Above Alert: %d\n", alert_count);

    fclose(fp);

    printf("\nSummary saved to temperature_summary.txt\n");

    free(temp_readings);
    return 0;
}

