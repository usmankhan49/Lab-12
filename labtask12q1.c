#include <stdio.h>
#include <stdlib.h>

int main() {

    int *hours_steps = NULL;
    int total_hours = 0;
    int capacity = 2;
    int i;

    hours_steps = (int *)malloc(capacity * sizeof(int));
    if (hours_steps == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    int choice = 1;

    while (choice == 1) {
        if (total_hours == capacity) {
            capacity = capacity * 2;
            hours_steps = (int *)realloc(hours_steps, capacity * sizeof(int));
            if (hours_steps == NULL) {
                printf("Reallocation failed\n");
                return 1;
            }
        }

        printf("Enter steps for hour %d: ", total_hours + 1);
        scanf("%d", (hours_steps + total_hours));
        total_hours++;

        printf("Add more hours? (1 = yes, 0 = no): ");
        scanf("%d", &choice);
    }

    int total_steps = 0;
    int max_steps = *(hours_steps);
    int threshold;
    int above_threshold = 0;

    for (i = 0; i < total_hours; i++) {
        total_steps = total_steps + *(hours_steps + i);

        if (*(hours_steps + i) > max_steps) {
            max_steps = *(hours_steps + i);
        }
    }

    printf("Enter step threshold: ");
    scanf("%d", &threshold);

    for (i = 0; i < total_hours; i++) {
        if (*(hours_steps + i) > threshold) {
            above_threshold++;
        }
    }

    FILE *fp = fopen("fitness_tracker.txt", "w");
    if (fp == NULL) {
        printf("File could not be opened\n");
        return 1;
    }

    fprintf(fp, "Fitness Tracker Data\n");
    fprintf(fp, "Total hours: %d\n", total_hours);
    fprintf(fp, "Total steps: %d\n", total_steps);
    fprintf(fp, "Maximum steps in an hour: %d\n", max_steps);
    fprintf(fp, "Hours above threshold: %d\n\n", above_threshold);

    for (i = 0; i < total_hours; i++) {
        fprintf(fp, "Hour %d: %d steps\n", i + 1, *(hours_steps + i));
    }

    fclose(fp);

    printf("\nAnalysis Complete\n");
    printf("Total steps: %d\n", total_steps);
    printf("Max steps in an hour: %d\n", max_steps);
    printf("Hours above threshold: %d\n", above_threshold);
    printf("Data saved in fitness_tracker.txt\n");

    free(hours_steps);
    return 0;
}

