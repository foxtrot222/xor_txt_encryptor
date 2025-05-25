#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <termios.h>
#include <stdbool.h>

#ifndef STDIN_FILENO
#define STDIN_FILENO 0
#endif

void crypt_file(char filename[], char key);
void view_encrypted_file(char filename[], char key);
char crypt_key(char key[]);
const char* generate_key();
void noecho(bool i);

int main( int argc, char *argv[] ) {
 
  srand(time(NULL));
  
  if ( argc < 3 ) {
    fprintf(stderr, "Not enough arguments.\n");
    return 1;
  }
  else if ( argc > 3 ) {
    fprintf(stderr, "Too many arguments.\n");
    return 1;
  }
  else {
    printf("XOR TXT Encryptor\n");
    if ( strcmp(argv[2],"-er") == 0 ) {
      printf("Encrypting the file : %s\n", argv[1]);
      const char *key = generate_key();
      printf("Your Key is %s\n", key);
      crypt_file(argv[1], crypt_key((char*)(key)));
      printf("Encryption complete. Output saved to output.txt\n");
    }
    
    if ( strcmp(argv[2], "-ek") == 0 ) {
      printf("Encrypting the file : %s\n", argv[1]);
      printf("Enter your key\n");
      noecho(true);
      char key[128];
      noecho(false);
      crypt_file(argv[1], crypt_key(key));
      printf("Encryption complete. Output saved to output.txt\n");
    }
    
    if ( strcmp(argv[2], "-d") == 0 ) {
      printf("Decrypting the file : %s\n", argv[1]);
      printf("Enter your key\n");
      noecho(true);
      char key[128];
      noecho(false);
      
      crypt_file(argv[1], crypt_key(key));
      printf("Decryption complete. Output saved to output.txt\n");
    }
    
    if ( strcmp(argv[2], "-v") == 0 ) {
      printf("Viewng the file : %s\n", argv[1]);
      printf("Enter your key\n");
      noecho(true);
      char key[128];
      noecho(false);
      view_encrypted_file(argv[1], crypt_key(key));
    }
    
  }
  printf("Done.\n");
  return 0;
}

char crypt_key(char key[]) {
  char c = '0';
  for (int i = 0 ; key[i] != '\0' ; i++ ) {
    c = c ^ key[i];
  }
  return c;
}

void crypt_file(char filename[], char key) {
  
  FILE *original_fp;
  original_fp = fopen(filename, "r");
  if ( original_fp == NULL ) {
   fprintf(stderr, "File not found.\n");
   exit(1); 
  }
  FILE *updated_fp;
  updated_fp = fopen("output.txt", "w");
  char c;
  while ( (c = fgetc(original_fp)) != EOF ) {
    fputc(c ^ key, updated_fp);
  }
  fclose(updated_fp);
  fclose(original_fp);
}

void view_encrypted_file(char filename[], char key) {
  FILE *original_fp;
  original_fp = fopen(filename, "r");
  
  if ( original_fp == NULL ) {
   fprintf(stderr, "File not found.\n");
   exit(1); 
  }
  
  char c;
  while ( (c = fgetc(original_fp)) != EOF)  {
    printf("%c", c ^ key);
  }
  fclose(original_fp);
}

const char* generate_key() {
  static char key[12];
  key[11] = '\0';
  for ( int i = 0 ; i < 11 ; i++ ) {
    key[i] = 33 + rand() % 94;
  }
  char *pkey = key;
  return pkey;
}

void noecho(bool i) {
  struct termios original, noecho;
  tcgetattr(STDIN_FILENO,&original);
  noecho = original;
  noecho.c_lflag = noecho.c_lflag ^ ECHO;
  if (i) {
     tcsetattr(STDIN_FILENO, TCSANOW, &noecho);
  }
  else {
    tcsetattr(STDIN_FILENO, TCSANOW, &original);
  }
}
