#include <stdio.h>
#include <stdlib.h>

struct User {
    char user_name[50];
    int total_days;
    float *units;   
};

float compute_bill(float total_units) {
    float bill_amount = 0;

    if(total_units <= 100) {
        bill_amount = total_units * 5;       
    }
    else if(total_units <= 300) {
        bill_amount = (100 * 5) + ((total_units - 100) * 8);   
    }
    else {
        bill_amount = (100 * 5) + (200 * 8) + ((total_units - 300) * 12);  
    }

    return bill_amount;
}

int main() {

    struct User user;
    int choice;
    int i;
    float total_units = 0;
    float bill_amount = 0;
    float avg_units = 0;

    printf("enter user name: ");
    scanf("%s", user.user_name);

    printf("enter number of days you want to record: ");
    scanf("%d", &user.total_days);

    user.units = (float *) malloc(user.total_days * sizeof(float));

    for(i = 0; i < user.total_days; i++) {
        printf("enter units for day %d: ", i + 1);
        scanf("%f", &user.units[i]);
    }

    while(1) {
        printf("\n1. add more days\n");
        printf("2. calculate bill\n");
        printf("3. save summary to file\n");
        printf("4. exit\n");
        printf("enter choice: ");
        scanf("%d", &choice);

        if(choice == 1) {
            int extra_days;
            printf("how many more days you want to add: ");
            scanf("%d", &extra_days);

            user.units = (float *) realloc(user.units,
                        (user.total_days + extra_days) * sizeof(float));

            for(i = user.total_days; i < user.total_days + extra_days; i++) {
                printf("enter units for day %d: ", i + 1);
                scanf("%f", &user.units[i]);
            }

            user.total_days = user.total_days + extra_days;

            printf("days added successfully\n");
        }

        else if(choice == 2) {
            total_units = 0;

            for(i = 0; i < user.total_days; i++) {
                total_units = total_units + user.units[i];
            }

            bill_amount = compute_bill(total_units);
            avg_units = total_units / user.total_days;

            printf("\ntotal units consumed: %.2f\n", total_units);
            printf("bill amount: %.2f\n", bill_amount);
            printf("average per day units: %.2f\n", avg_units);
        }

        else if(choice == 3) {
            FILE *fp = fopen("bill_summary.txt", "w");

            if(fp == NULL) {
                printf("file error\n");
            } else {
                fprintf(fp, "Electricity Bill Summary\n");
                fprintf(fp, "-------------------------\n");
                fprintf(fp, "User name: %s\n", user.user_name);
                fprintf(fp, "Total days recorded: %d\n\n", user.total_days);

                total_units = 0;
                for(i = 0; i < user.total_days; i++) {
                    fprintf(fp, "Day %d: %.2f units\n", i + 1, user.units[i]);
                    total_units = total_units + user.units[i];
                }

                bill_amount = compute_bill(total_units);
                avg_units = total_units / user.total_days;

                fprintf(fp, "\nTotal units: %.2f\n", total_units);
                fprintf(fp, "Bill amount: %.2f\n", bill_amount);
                fprintf(fp, "Average units: %.2f\n", avg_units);

                fclose(fp);
                printf("summary saved to bill_summary.txt\n");
            }
        }

        else if(choice == 4) {
            break;
        }
    }

    free(user.units);

    return 0;
}

