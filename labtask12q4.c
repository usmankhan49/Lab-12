#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct checkout_log {
    char book_title[100];
    int member_id;
    int checkout_day;
    int due_day;
    int return_due_days;
};

int main() {

    struct checkout_log *logs = NULL;
    int total_logs = 0;
    int capacity = 2;
    int choice = 1;

    logs = (struct checkout_log *)malloc(capacity * sizeof(struct checkout_log));
    if (logs == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    while (choice == 1) {

        if (total_logs == capacity) {
            capacity = capacity + 2;
            logs = (struct checkout_log *)realloc(logs, capacity * sizeof(struct checkout_log));
            if (logs == NULL) {
                printf("Reallocation failed\n");
                return 1;
            }
        }

        printf("Enter book title: ");
        getchar();
        fgets(logs[total_logs].book_title, 100, stdin);
        logs[total_logs].book_title[strcspn(logs[total_logs].book_title, "\n")] = '\0';

        printf("Enter member ID: ");
        scanf("%d", &logs[total_logs].member_id);

        printf("Enter checkout day (day number): ");
        scanf("%d", &logs[total_logs].checkout_day);

        printf("Enter return due days: ");
        scanf("%d", &logs[total_logs].return_due_days);

        logs[total_logs].due_day =
            logs[total_logs].checkout_day +
            logs[total_logs].return_due_days;

        total_logs++;

        printf("Add another checkout? (1 = yes, 0 = no): ");
        scanf("%d", &choice);
    }

    FILE *fp = fopen("checkout_logs.csv", "a");
    if (fp == NULL) {
        printf("File open failed\n");
        return 1;
    }

    fprintf(fp, "Book Title,Member ID,Checkout Day,Due Day\n");
    int i;
    for ( i = 0; i < total_logs; i++) {
        fprintf(fp, "%s,%d,%d,%d\n",
            logs[i].book_title,
            logs[i].member_id,
            logs[i].checkout_day,
            logs[i].due_day
        );
    }

    fclose(fp);

    printf("\nCheckout logs saved to checkout_logs.csv\n");

    free(logs);
    return 0;
}

