#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manager.h"

#define FILENAME "passwords.dat"

void xor_encrypt(char *data, int len, const char *key) {
    int key_len = strlen(key);
    for (int i = 0; i < len; i++) {
        data[i] ^= key[i % key_len];
    }
}

int load_credentials(Credential creds[], int *count, const char *key) {
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) return 0;

    fread(count, sizeof(int), 1, fp);
    fread(creds, sizeof(Credential), *count, fp);

    for (int i = 0; i < *count; i++) {
        xor_encrypt((char *)&creds[i], sizeof(Credential), key);
    }

    fclose(fp);
    return 1;
}

void save_credentials(Credential creds[], int count, const char *key) {
    FILE *fp = fopen(FILENAME, "wb");
    if (!fp) {
        printf("Error saving data.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        xor_encrypt((char *)&creds[i], sizeof(Credential), key);
    }

    fwrite(&count, sizeof(int), 1, fp);
    fwrite(creds, sizeof(Credential), count, fp);
    fclose(fp);

    // Restore to normal for program use
    for (int i = 0; i < count; i++) {
        xor_encrypt((char *)&creds[i], sizeof(Credential), key);
    }
}

void add_credential(Credential creds[], int *count) {
    if (*count >= MAX_ENTRIES) {
        printf("Credential limit reached!\n");
        return;
    }

    printf("Enter site: ");
    scanf(" %[^\n]", creds[*count].site);
    printf("Enter username: ");
    scanf(" %[^\n]", creds[*count].username);
    printf("Enter password: ");
    scanf(" %[^\n]", creds[*count].password);

    (*count)++;
    printf("Credential added successfully.\n");
}

void view_credentials(Credential creds[], int count) {
    if (count == 0) {
        printf("No credentials saved.\n");
        return;
    }

    printf("\nStored Credentials:\n");
    for (int i = 0; i < count; i++) {
        printf("[%d] Site: %s | Username: %s | Password: %s\n",
            i + 1, creds[i].site, creds[i].username, creds[i].password);
    }
    printf("\n");
}

void delete_credential(Credential creds[], int *count) {
    int index;
    view_credentials(creds, *count);
    printf("Enter the number to delete: ");
    scanf("%d", &index);

    if (index < 1 || index > *count) {
        printf("Invalid index.\n");
        return;
    }

    for (int i = index - 1; i < *count - 1; i++) {
        creds[i] = creds[i + 1];
    }

    (*count)--;
    printf("Credential deleted.\n");
}

