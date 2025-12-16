#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Bed {
    int is_occupied;
    char patient_name[50];
    int days_admitted;
};

struct Ward {
    char ward_name[50];
    int total_beds;
    struct Bed *beds;
};

int count_occupied_recursive(struct Ward *wards, int ward_index, int bed_index) {
    if (ward_index < 0) {
        return 0;
    }

    if (bed_index < 0) {
        return count_occupied_recursive(wards, ward_index - 1, wards[ward_index - 1].total_beds - 1);
    }

    int count = 0;

    if (wards[ward_index].beds[bed_index].is_occupied == 1) {
        count = 1;
    }

    return count + count_occupied_recursive(wards, ward_index, bed_index - 1);
}

void save_to_file(struct Ward *wards, int total_wards) {
    FILE *fp = fopen("hospital_data.txt", "w");
    if (fp == NULL) {
        printf("file error\n");
        return;
    }

    fprintf(fp, "%d\n", total_wards);
int i;
    for (i = 0; i < total_wards; i++) {
        fprintf(fp, "%s %d\n", wards[i].ward_name, wards[i].total_beds);
int j;
        for (j = 0; j < wards[i].total_beds; j++) {
            fprintf(fp, "%d %s %d\n",
                    wards[i].beds[j].is_occupied,
                    wards[i].beds[j].patient_name,
                    wards[i].beds[j].days_admitted);
        }
    }

    fclose(fp);
    printf("data saved to hospital_data.txt\n");
}

void load_from_file(struct Ward **wards, int *total_wards) {
    FILE *fp = fopen("hospital_data.txt", "r");
    if (fp == NULL) {
        printf("file not found, starting fresh...\n");
        return;
    }

    fscanf(fp, "%d", total_wards);

    *wards = (struct Ward *) malloc((*total_wards) * sizeof(struct Ward));
int i;
    for (i = 0; i < *total_wards; i++) {
        fscanf(fp, "%s %d", (*wards)[i].ward_name, &(*wards)[i].total_beds);

        (*wards)[i].beds =
            (struct Bed *) malloc((*wards)[i].total_beds * sizeof(struct Bed));
int j;
        for (j = 0; j < (*wards)[i].total_beds; j++) {
            fscanf(fp, "%d %s %d",
                   &(*wards)[i].beds[j].is_occupied,
                   (*wards)[i].beds[j].patient_name,
                   &(*wards)[i].beds[j].days_admitted);
        }
    }

    fclose(fp);
    printf("data loaded from file\n");
}

int main() {
    struct Ward *wards = NULL;
    int total_wards = 0;

    load_from_file(&wards, &total_wards);

    int choice;

    while (1) {
        printf("\n1. Add ward\n");
        printf("2. Mark bed occupied\n");
        printf("3. Free bed\n");
        printf("4. Count occupied beds\n");
        printf("5. Save data\n");
        printf("6. Exit\n");
        printf("enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            total_wards++;
            wards = (struct Ward *) realloc(wards, total_wards * sizeof(struct Ward));

            printf("enter ward name: ");
            scanf("%s", wards[total_wards - 1].ward_name);

            printf("enter total beds: ");
            scanf("%d", &wards[total_wards - 1].total_beds);

            wards[total_wards - 1].beds =
                (struct Bed *) malloc(wards[total_wards - 1].total_beds * sizeof(struct Bed));
int i;
            for ( i = 0; i < wards[total_wards - 1].total_beds; i++) {
                wards[total_wards - 1].beds[i].is_occupied = 0;
                strcpy(wards[total_wards - 1].beds[i].patient_name, "empty");
                wards[total_wards - 1].beds[i].days_admitted = 0;
            }

            printf("ward added\n");
        }

        else if (choice == 2) {
            int w, b;
            printf("enter ward index: ");
            scanf("%d", &w);
            printf("enter bed index: ");
            scanf("%d", &b);

            if (w < total_wards && b < wards[w].total_beds) {
                printf("enter patient name: ");
                scanf("%s", wards[w].beds[b].patient_name);

                printf("enter days admitted: ");
                scanf("%d", &wards[w].beds[b].days_admitted);

                wards[w].beds[b].is_occupied = 1;

                printf("bed marked occupied\n");
            }
        }

        else if (choice == 3) {
            int w, b;
            printf("enter ward index: ");
            scanf("%d", &w);
            printf("enter bed index: ");
            scanf("%d", &b);

            if (w < total_wards && b < wards[w].total_beds) {
                wards[w].beds[b].is_occupied = 0;
                strcpy(wards[w].beds[b].patient_name, "empty");
                wards[w].beds[b].days_admitted = 0;

                printf("bed freed\n");
            }
        }
        else if (choice == 4) {
            if (total_wards == 0) {
                printf("no wards yet\n");
            } else {
                int total = count_occupied_recursive(wards, total_wards - 1,
                                                     wards[total_wards - 1].total_beds - 1);
                printf("total occupied beds: %d\n", total);
            }
        }
        else if (choice == 5) {
            save_to_file(wards, total_wards);
        }

        else if (choice == 6) {
            save_to_file(wards, total_wards);
            break;
        }
    }
    int i;
    for ( i = 0; i < total_wards; i++) {
        free(wards[i].beds);
    }
    free(wards);
    return 0;
}

