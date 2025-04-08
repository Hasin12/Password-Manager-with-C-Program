#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "manager.h"

int main() {
    Credential creds[MAX_ENTRIES];
    int count = 0;
    char input_pass[100];

    printf("=== Password Manager ===\n");
    printf("Enter master password: ");
    scanf("%s", input_pass);

    if (strcmp(input_pass, MASTER_PASS) != 0) {
        printf("Access Denied!\n");
        return 0;
    }

    load_credentials(creds, &count, MASTER_PASS);

    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Credential\n");
        printf("2. View Credentials\n");
        printf("3. Delete Credential\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_credential(creds, &count);
                save_credentials(creds, count, MASTER_PASS);
                break;
            case 2:
                view_credentials(creds, count);
                break;
            case 3:
                delete_credential(creds, &count);
                save_credentials(creds, count, MASTER_PASS);
                break;
            case 4:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
