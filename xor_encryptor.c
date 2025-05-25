#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <termios.h>
#include <stdbool.h>

#ifndef STDIN_FILENO
#define STDIN_FILENO 0
#endif

void crypt_file(char filename[], char key[]);
void view_encrypted_file(char filename[], char key[]);
char* generate_key(int key_length);


int main(int argc, char *argv[]) {
    srand(time(NULL));
    struct termios original,noecho;
    tcgetattr(STDIN_FILENO,&original);
    noecho = original;
    noecho.c_lflag = noecho.c_lflag ^ ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &noecho);
    
    if (argc < 3) {
        fprintf(stderr, "Not enough arguments.\n");
        return 1;
    } else if (argc > 3) {
        fprintf(stderr, "Too many arguments.\n");
        return 1;
    }

    printf("XOR TXT Encryptor\n");

    if (strcmp(argv[2], "-er") == 0) {
        printf("Encrypting the file: %s\n", argv[1]);
        printf("Enter your key length: ");
        int key_length;
        scanf("%d", &key_length);
        getchar();
        char *key = generate_key(key_length);
        printf("Generated key: %s\n", key);
        crypt_file(argv[1], key);
        printf("Encryption complete. Output saved to output.txt\n");
        free(key);
    }

    if (strcmp(argv[2], "-ek") == 0) {
        printf("Encrypting the file: %s\n", argv[1]);
        printf("Enter your key length: ");
        int key_length;
        scanf("%d", &key_length);
        getchar();
        printf("Enter your key\n");
        char key[key_length + 1];
        fgets(key, key_length + 1, stdin);
        key[strcspn(key, "\n")] = '\0';
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        crypt_file(argv[1], key);
        printf("Encryption complete. Output saved to output.txt\n");
    }

    if (strcmp(argv[2], "-d") == 0) {
        printf("Decrypting the file: %s\n", argv[1]);
        printf("Enter your key length: ");
        int key_length;
        scanf("%d", &key_length);
        getchar();
        printf("Enter your key\n");
        char key[key_length + 1];
        fgets(key, key_length + 1, stdin);
        key[strcspn(key, "\n")] = '\0';
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        crypt_file(argv[1], key);
        printf("Decryption complete. Output saved to output.txt\n");
    }

    if (strcmp(argv[2], "-v") == 0) {
        printf("Viewing the file: %s\n", argv[1]);
        printf("Enter your key length: ");
        int key_length;
        scanf("%d", &key_length);
        getchar();
        printf("Enter your key\n");
        char key[key_length + 1];
        fgets(key, key_length + 1, stdin);
        key[strcspn(key, "\n")] = '\0';
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        view_encrypted_file(argv[1], key);
    }
    
    tcsetattr(STDIN_FILENO, TCSANOW, &original);
    return 0;
}

void crypt_file(char filename[], char key[]) {
    FILE *original_fp = fopen(filename, "r");
    if (original_fp == NULL) {
        fprintf(stderr, "File not found: %s\n", filename);
        exit(1);
    }

    FILE *updated_fp = fopen("output.txt", "w");
    if (updated_fp == NULL) {
        fprintf(stderr, "Could not create output.txt\n");
        fclose(original_fp);
        exit(1);
    }

    char c;
    int i = 0;
    int key_len = strlen(key);

    while ((c = fgetc(original_fp)) != EOF) {
        fputc(c ^ key[i], updated_fp);
        i = (i + 1) % key_len;
    }

    fclose(updated_fp);
    fclose(original_fp);
}

void view_encrypted_file(char filename[], char key[]) {
    FILE *original_fp = fopen(filename, "r");
    if (original_fp == NULL) {
        fprintf(stderr, "File not found: %s\n", filename);
        exit(1);
    }

    char c;
    int i = 0;
    int key_len = strlen(key);

    while ((c = fgetc(original_fp)) != EOF) {
        printf("%c", c ^ key[i]);
        i = (i + 1) % key_len;
    }

    printf("\n");
    fclose(original_fp);
}

char* generate_key(int key_length) {
    char *key = malloc((key_length + 1) * sizeof(char));
    if (key == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }

    for (int i = 0; i < key_length; i++) {
        key[i] = 33 + rand() % 94;
    }
    key[key_length] = '\0';

    return key;
}
