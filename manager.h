#ifndef MANAGER_H
#define MANAGER_H

#define MAX_ENTRIES 100
#define MAX_LEN 100
#define MASTER_PASS "admin123" // Change this in real use

typedef struct {
    char site[MAX_LEN];
    char username[MAX_LEN];
    char password[MAX_LEN];
} Credential;

void xor_encrypt(char *data, int len, const char *key);
int load_credentials(Credential creds[], int *count, const char *key);
void save_credentials(Credential creds[], int count, const char *key);
void add_credential(Credential creds[], int *count);
void view_credentials(Credential creds[], int count);
void delete_credential(Credential creds[], int *count);

#endif

