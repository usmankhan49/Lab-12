#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* gate_attendance = NULL;
int gate_count = 0;

void add_gate(int count) {
    int* temp = realloc(gate_attendance, (gate_count + count) * sizeof(int));
    if (!temp) {
        printf("Memory allocation failed!\n");
        return;
    }
    gate_attendance = temp;
    int i;
    for (i = gate_count; i < gate_count + count; i++) {
        gate_attendance[i] = 0;
    }
    gate_count += count;
    printf("%d gate(s) added successfully.\n", count);
}

void record_attendance() {
    if (gate_count == 0) {
        printf("No gates available. Add gates first.\n");
        return;
    }
    int i;
    for (i = 0; i < gate_count; i++) {
        printf("Enter number of attendees at Gate %d: ", i+1);
        scanf("%d", &gate_attendance[i]);
    }
}

int total_attendance_recursive(int index) {
    if (index < 0) return 0;
    return gate_attendance[index] + total_attendance_recursive(index - 1);
}

int gate_with_highest_attendance() {
    if (gate_count == 0) return -1;
    int max_index = 0, i;
    for (i = 1; i < gate_count; i++) {
        if (gate_attendance[i] > gate_attendance[max_index]) {
            max_index = i;
        }
    }
    return max_index;
}

void save_attendance() {
    FILE *fp = fopen("attendance.txt", "a");
    if (!fp) {
        printf("Cannot open file for writing!\n");
        return;
    }

    time_t now = time(NULL);
    fprintf(fp, "Attendance report at %s", ctime(&now));
    int i;
    for (i = 0; i < gate_count; i++) {
        fprintf(fp, "Gate %d: %d attendees\n", i+1, gate_attendance[i]);
    }
    fprintf(fp, "Total attendees: %d\n", total_attendance_recursive(gate_count-1));
    int max_gate = gate_with_highest_attendance();
    if (max_gate != -1) {
        fprintf(fp, "Gate with highest attendance: Gate %d (%d attendees)\n\n",
                max_gate+1, gate_attendance[max_gate]);
    }

    fclose(fp);
    printf("Attendance data saved to attendance.txt\n");
}

void free_memory() {
    if (gate_attendance) free(gate_attendance);
    gate_attendance = NULL;
    gate_count = 0;
}
int main() {
    int choice, count;

    while (1) {
        printf("\n==== Real-Time Event Attendance Counter ====\n");
        printf("1. Add Gate(s)\n");
        printf("2. Record Attendance\n");
        printf("3. Show Total Attendance\n");
        printf("4. Show Gate with Highest Attendance\n");
        printf("5. Save Attendance Report\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Enter number of gates to add: ");
            scanf("%d", &count);
            add_gate(count);
        }
        else if (choice == 2) {
            record_attendance();
        }
        else if (choice == 3) {
            int total = total_attendance_recursive(gate_count-1);
            printf("Total attendees so far: %d\n", total);
        }
        else if (choice == 4) {
            int max_gate = gate_with_highest_attendance();
            if (max_gate != -1) {
                printf("Gate with highest attendance: Gate %d (%d attendees)\n",
                       max_gate+1, gate_attendance[max_gate]);
            } else {
                printf("No gates added yet.\n");
            }
        }
        else if (choice == 5) {
            save_attendance();
        }
        else if (choice == 6) {
            save_attendance();
            free_memory();
            printf("Exiting program. Memory freed.\n");
            break;
        }
        else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

