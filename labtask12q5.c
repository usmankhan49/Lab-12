#include <stdio.h>
#include <stdlib.h>

struct rental {
    int customer_id;
    int rental_hours;
    int cost;
};

int main() {

    struct rental *rentals = NULL;
    int total_customers = 0;
    int size = 2;
    int choice = 1;

    int rate_per_hour = 500;
    int total_hours = 0;
    int max_hours = 0;

    rentals = (struct rental *)malloc(size * sizeof(struct rental));
    if (rentals == NULL) {
        printf("Memory not allocated\n");
        return 1;
    }

    while (choice == 1) {

        if (total_customers == size) {
            size = size + 2;
            rentals = (struct rental *)realloc(rentals, size * sizeof(struct rental));
            if (rentals == NULL) {
                printf("Reallocation failed\n");
                return 1;
            }
        }

        printf("Enter customer id: ");
        scanf("%d", &rentals[total_customers].customer_id);

        printf("Enter rental duration in hours: ");
        scanf("%d", &rentals[total_customers].rental_hours);

        rentals[total_customers].cost =
            rentals[total_customers].rental_hours * rate_per_hour;

        total_hours = total_hours + rentals[total_customers].rental_hours;

        if (rentals[total_customers].rental_hours > max_hours)
            max_hours = rentals[total_customers].rental_hours;

        total_customers++;

        printf("Add another rental? (1 = yes, 0 = no): ");
        scanf("%d", &choice);
    }

    FILE *fp = fopen("Rental_Invoices.txt", "w");
    if (fp == NULL) {
        printf("File error\n");
        return 1;
    }

    fprintf(fp, "Car Rental Invoices\n\n");
    int i;
    for (i = 0; i < total_customers; i++) {
        fprintf(fp, "Customer ID: %d\n", rentals[i].customer_id);
        fprintf(fp, "Rental Hours: %d\n", rentals[i].rental_hours);
        fprintf(fp, "Total Cost: %d\n\n", rentals[i].cost);
    }

    fprintf(fp, "Total Rental Hours Today: %d\n", total_hours);
    fprintf(fp, "Highest Rental Duration: %d\n", max_hours);

    fclose(fp);

    printf("\nInvoices written to Rental_Invoices.txt\n");

    free(rentals);
    return 0;
}

