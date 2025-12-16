#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char student_name[50];
    char roll_number[20];
    int seat_number;
};

int check_roll_recursive(char *roll, int i) {
    if (roll[i] == '\0')
        return 1;

    if ((roll[i] >= 'A' && roll[i] <= 'Z') ||
        (roll[i] >= 'a' && roll[i] <= 'z') ||
        (roll[i] >= '0' && roll[i] <= '9')) {
        return check_roll_recursive(roll, i + 1);
    }

    return 0;
}

int main() {

    struct Student *students = NULL;
    int total_students = 0;
    int capacity = 2;
    int choice = 1;
    int i;

    students = (struct Student *)malloc(capacity * sizeof(struct Student));
    if (students == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    while (choice == 1) {

        if (total_students == capacity) {
            capacity = capacity * 2;
            students = (struct Student *)realloc(students, capacity * sizeof(struct Student));
            if (students == NULL) {
                printf("Reallocation failed\n");
                return 1;
            }
        }

        printf("Enter student name: ");
        getchar();
        fgets(students[total_students].student_name, 50, stdin);
        students[total_students].student_name[strcspn(students[total_students].student_name, "\n")] = '\0';

        do {
            printf("Enter roll number (alphanumeric only): ");
            fgets(students[total_students].roll_number, 20, stdin);
            students[total_students].roll_number[strcspn(students[total_students].roll_number, "\n")] = '\0';

            if (check_roll_recursive(students[total_students].roll_number, 0) == 0) {
                printf("Invalid roll number. Try again.\n");
            }
        } while (check_roll_recursive(students[total_students].roll_number, 0) == 0);

        students[total_students].seat_number = total_students + 1;

        total_students++;

        printf("Add more students? (1 = yes, 0 = no): ");
        scanf("%d", &choice);
    }
    FILE *fp = fopen("seating.txt", "w");
    if (fp == NULL) {
        printf("File open failed\n");
        return 1;
    }
    fprintf(fp, "Exam Seating Plan\n\n");

    for (i = 0; i < total_students; i++) {
        fprintf(fp, "Seat %d | Name: %s | Roll: %s\n",
                students[i].seat_number,
                students[i].student_name,
                students[i].roll_number);
    }
    fclose(fp);

    printf("\nSeating plan saved to seating.txt\n");

    free(students);
    return 0;
}

