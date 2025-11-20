#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Customer {
    int room;
    char name[50];
    char address[100];
    char phone[15];
    int days;
    float bill;
};

void addCustomer();
void viewCustomers();
void searchCustomer();
void updateCustomer();
void deleteCustomer();

int main() {
    int choice;

    while (1) {
        printf("\n===== HOTEL MANAGEMENT SYSTEM =====\n");
        printf("1. Add Customer\n");
        printf("2. View All Customers\n");
        printf("3. Search Customer\n");
        printf("4. Update Customer\n");
        printf("5. Delete Customer\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addCustomer(); break;
            case 2: viewCustomers(); break;
            case 3: searchCustomer(); break;
            case 4: updateCustomer(); break;
            case 5: deleteCustomer(); break;
            case 6: exit(0);
            default: printf("Invalid Choice! Try Again.\n");
        }
    }
}

// Add Customer
void addCustomer() {
    struct Customer c;
    FILE *fp = fopen("hotel.dat", "ab");

    printf("Enter Room Number: ");
    scanf("%d", &c.room);
    printf("Enter Name: ");
    getchar();
    gets(c.name);
    printf("Enter Address: ");
    gets(c.address);
    printf("Enter Phone: ");
    gets(c.phone);
    printf("Enter Number of Days: ");
    scanf("%d", &c.days);

    c.bill = c.days * 1500; // room rate = 1500 per day

    fwrite(&c, sizeof(c), 1, fp);
    fclose(fp);

    printf("Customer Added Successfully!\n");
}

// View All Customers
void viewCustomers() {
    struct Customer c;
    FILE *fp = fopen("hotel.dat", "rb");

    printf("\n===== CUSTOMER LIST =====\n");

    while (fread(&c, sizeof(c), 1, fp)) {
        printf("\nRoom: %d\nName: %s\nAddress: %s\nPhone: %s\nDays: %d\nBill: %.2f\n",
               c.room, c.name, c.address, c.phone, c.days, c.bill);
    }

    fclose(fp);
}

// Search Customer
void searchCustomer() {
    int room, found = 0;
    struct Customer c;
    FILE *fp = fopen("hotel.dat", "rb");

    printf("Enter Room Number to Search: ");
    scanf("%d", &room);

    while (fread(&c, sizeof(c), 1, fp)) {
        if (c.room == room) {
            printf("\nCustomer Found!\n");
            printf("Room: %d\nName: %s\nAddress: %s\nPhone: %s\nDays: %d\nBill: %.2f\n",
                   c.room, c.name, c.address, c.phone, c.days, c.bill);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Customer Not Found!\n");

    fclose(fp);
}

// Update Customer
void updateCustomer() {
    int room, found = 0;
    struct Customer c;
    FILE *fp = fopen("hotel.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    printf("Enter Room Number to Update: ");
    scanf("%d", &room);

    while (fread(&c, sizeof(c), 1, fp)) {
        if (c.room == room) {
            printf("Enter New Name: ");
            getchar();
            gets(c.name);
            printf("Enter New Address: ");
            gets(c.address);
            printf("Enter New Phone: ");
            gets(c.phone);
            printf("Enter New Days: ");
            scanf("%d", &c.days);

            c.bill = c.days * 1500;
            found = 1;
        }
        fwrite(&c, sizeof(c), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("hotel.dat");
    rename("temp.dat", "hotel.dat");

    if (found)
        printf("Customer Updated Successfully!\n");
    else
        printf("Customer Not Found!\n");
}

// Delete Customer
void deleteCustomer() {
    int room, found = 0;
    struct Customer c;
    FILE *fp = fopen("hotel.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    printf("Enter Room Number to Delete: ");
    scanf("%d", &room);

    while (fread(&c, sizeof(c), 1, fp)) {
        if (c.room == room) {
            found = 1;
            continue;
        }
        fwrite(&c, sizeof(c), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("hotel.dat");
    rename("temp.dat", "hotel.dat");

    if (found)
        printf("Customer Deleted Successfully!\n");
    else
        printf("Customer Not Found!\n");
}
