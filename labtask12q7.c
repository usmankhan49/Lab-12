#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Medicine {
    char medicine_name[100];
    int quantity_available;
    float unit_price;
};

struct Medicine *inventory = NULL;
int medicine_count = 0;

void add_medicine() {
    struct Medicine temp;

    printf("Enter Medicine Name: ");
    getchar();
    fgets(temp.medicine_name, sizeof(temp.medicine_name), stdin);
    temp.medicine_name[strcspn(temp.medicine_name, "\n")] = '\0';

    printf("Enter Quantity Available: ");
    scanf("%d", &temp.quantity_available);

    printf("Enter Unit Price: ");
    scanf("%f", &temp.unit_price);

    struct Medicine *new_arr = realloc(inventory, (medicine_count + 1) * sizeof(struct Medicine));
    if (!new_arr) {
        printf("Memory allocation failed!\n");
        return;
    }
    inventory = new_arr;
    inventory[medicine_count] = temp;
    medicine_count++;
    printf("Medicine added successfully.\n");
}

void remove_medicine() {
    if (medicine_count == 0) {
        printf("No medicines in inventory.\n");
        return;
    }

    char name[100];
    printf("Enter Medicine Name to remove: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    int found = -1, i;
    for (i = 0; i < medicine_count; i++) {
        if (strcmp(inventory[i].medicine_name, name) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Medicine not found.\n");
        return;
    }
    
    for (i = found; i < medicine_count - 1; i++) {
        inventory[i] = inventory[i + 1];
    }

    medicine_count--;
    if (medicine_count > 0) {
        struct Medicine *new_arr = realloc(inventory, medicine_count * sizeof(struct Medicine));
        if (new_arr) inventory = new_arr;
    } else {
        free(inventory);
        inventory = NULL;
    }

    printf("Medicine removed successfully.\n");
}

void display_inventory() {
    if (medicine_count == 0) {
        printf("Inventory is empty.\n");
        return;
    }
int i;
    printf("\nCurrent Inventory:\n");
    for ( i = 0; i < medicine_count; i++) {
        printf("%d. %s | Qty: %d | Price: %.2f\n",
               i + 1,
               inventory[i].medicine_name,
               inventory[i].quantity_available,
               inventory[i].unit_price);
    }
}

void compute_inventory_value() {
    float total = 0;
    printf("\nLow Stock Medicines (Qty < 5):\n");
    int low_found = 0;
int i;
    for (i = 0; i < medicine_count; i++) {
        total += inventory[i].quantity_available * inventory[i].unit_price;
        if (inventory[i].quantity_available < 5) {
            printf("- %s | Qty: %d\n", inventory[i].medicine_name, inventory[i].quantity_available);
            low_found = 1;
        }
    }

    if (!low_found) printf("None\n");
    printf("Total Inventory Value: %.2f\n", total);
}

void save_inventory() {
    FILE *fp = fopen("medicine_inventory.txt", "w");
    if (!fp) {
        printf("Cannot open file for writing.\n");
        return;
    }
int i;
    for ( i = 0; i < medicine_count; i++) {
        fprintf(fp, "%s,%d,%.2f\n",
                inventory[i].medicine_name,
                inventory[i].quantity_available,
                inventory[i].unit_price);
    }
    fclose(fp);
    printf("Inventory saved to medicine_inventory.txt\n");
}

void free_memory() {
    if (inventory) free(inventory);
    inventory = NULL;
    medicine_count = 0;
}

int main() {
    int choice;

    while (1) {
        printf("\n==== Medication Inventory Manager ====\n");
        printf("1. Add Medicine\n");
        printf("2. Remove Medicine\n");
        printf("3. Display Inventory\n");
        printf("4. Compute Inventory Value & Low-Stock Alerts\n");
        printf("5. Save & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) add_medicine();
        else if (choice == 2) remove_medicine();
        else if (choice == 3) display_inventory();
        else if (choice == 4) compute_inventory_value();
        else if (choice == 5) {
            save_inventory();
            free_memory();
            printf("Exiting program.\n");
            break;
        }
        else printf("Invalid choice. Try again.\n");
    }

    return 0;
}

