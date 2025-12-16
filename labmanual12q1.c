#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Order {
    char item_name[50];
    int quantity;
    float unit_price;
    char customer_name[50];
};

int main() {
    struct Order *orders = NULL;
    int total_orders = 0;
    int choice;
    float total_revenue = 0;

    FILE *file_ptr;

    while (1) {
        printf("\nDo you want to add a new order? (1 = yes, 0 = no): ");
        scanf("%d", &choice);

        if (choice == 0) {
            break;
        }

        total_orders++;

        orders = (struct Order *) realloc(orders, total_orders * sizeof(struct Order));
        if (orders == NULL) {
            printf("memory allocation failed\n");
            return 1;
        }

        printf("enter item name: ");
        scanf("%s", orders[total_orders - 1].item_name);

        printf("enter quantity: ");
        scanf("%d", &orders[total_orders - 1].quantity);

        printf("enter unit price: ");
        scanf("%f", &orders[total_orders - 1].unit_price);

        printf("enter customer name: ");
        scanf("%s", orders[total_orders - 1].customer_name);

        total_revenue = total_revenue + (orders[total_orders - 1].quantity * orders[total_orders - 1].unit_price);
    }

    file_ptr = fopen("orders_receipt.txt", "w");
    if (file_ptr == NULL) {
        printf("file not created\n");
        free(orders);
        return 1;
    }
    fprintf(file_ptr, "==== DAILY FOOD ORDERS RECEIPT ====\n\n");
    int i;
    for (i = 0; i < total_orders; i++) {
        fprintf(file_ptr, "Order %d\n", i + 1);
        fprintf(file_ptr, "Item: %s\n", orders[i].item_name);
        fprintf(file_ptr, "Quantity: %d\n", orders[i].quantity);
        fprintf(file_ptr, "Unit Price: %.2f\n", orders[i].unit_price);
        fprintf(file_ptr, "Customer: %s\n", orders[i].customer_name);
        fprintf(file_ptr, "Subtotal: %.2f\n\n",
                orders[i].quantity * orders[i].unit_price);
    }
    fprintf(file_ptr, "-------------------------------------\n");
    fprintf(file_ptr, "Total Revenue: %.2f\n", total_revenue);

    fclose(file_ptr);
    printf("\nOrders saved to orders_receipt.txt\n");
    printf("Total revenue: %.2f\n", total_revenue);
    free(orders);

    return 0;
}

