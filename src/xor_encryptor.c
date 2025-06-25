/*
 * SPDX-FileCopyrightText: 2025 Tirth Kavathiya <tirthkavathiya@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <termios.h>

#ifndef STDIN_FILENO
#define STDIN_FILENO 0
#endif

struct termios original;
void crypt_file(char filename[], char key[]);
void view_encrypted_file(char filename[], char key[]);
char* generate_key(int key_length);
char* generate_random_key_from_user();
char* get_key_from_user();
void restore_terminal();

int main(int argc, char *argv[]) {
    srand(time(NULL));
    tcgetattr(STDIN_FILENO, &original);
    atexit(restore_terminal);
    struct termios noecho = original;
    noecho.c_lflag &= ~ECHO;
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
        char* key = generate_random_key_from_user();
        crypt_file(argv[1], key);
        printf("Encryption complete. Output saved to output.txt\n");
	free(key);
    }

    else if (strcmp(argv[2], "-ek") == 0) {
        printf("Encrypting the file: %s\n", argv[1]);
        char* key = get_key_from_user();
        crypt_file(argv[1], key);
        printf("Encryption complete. Output saved to output.txt\n");
	free(key);
    }

    else if (strcmp(argv[2], "-d") == 0) {
        printf("Decrypting the file: %s\n", argv[1]);
        char* key = get_key_from_user();
        crypt_file(argv[1], key);
        printf("Decryption complete. Output saved to output.txt\n");
	free(key);
    }

    else if (strcmp(argv[2], "-v") == 0) {
        printf("Viewing the file: %s\n", argv[1]);
        char* key = get_key_from_user();
        view_encrypted_file(argv[1], key);
	free(key);
    }

    else {
      fprintf(stderr, "Invalid arguments.\n");
      return 1;
    }

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

char* generate_random_key_from_user() {
  int key_length;
  
  printf("Enter your key length: ");
  if (scanf("%d", &key_length) != 1 || key_length <= 0) {
    fprintf(stderr, "Invalid key length.\n");
    exit(1);
  }
  getchar();

  char *key = generate_key(key_length);
  if (!key) {
    fprintf(stderr, "Key generation failed.\n");
    exit(1);
  }
  
  printf("Generated key: %s\n", key);
  return key;
}

char* get_key_from_user() {
    int key_length;

    printf("Enter your key length: ");
    if (scanf("%d", &key_length) != 1 || key_length <= 0) {
        fprintf(stderr, "Invalid key length.\n");
        exit(1);
    }
    getchar();

    printf("\nEnter your key: ");

    char *key = malloc((key_length + 1) * sizeof(char));
    if (!key) {
        fprintf(stderr, "Memory allocation failed for key.\n");
        exit(1);
    }

    if (!fgets(key, key_length + 1, stdin)) {
        fprintf(stderr, "Error reading key.\n");
        free(key);
        exit(1);
    }

    key[strcspn(key, "\n")] = '\0';

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("\n");

    return key;
}

void restore_terminal() {
  tcsetattr(STDIN_FILENO, TCSANOW, &original);
}
