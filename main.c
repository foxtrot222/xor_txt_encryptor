#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void crypt_file(char filename[], char key[]);
void view_encypted_file(char filename[], char key[]);
char crypt_key(char key[]);
const char* generate_key();

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
    if ( strcmp(argv[2],"-er") == 0 ) {
      const char *key = generate_key();
      printf("Your Key is %s\n", key);
      crypt(argv[1], key);
    }
    if ( strcmp(argv[2], "-ek") == 0 ) {
      char key;
      printf("Enter your key\n");
      crypt(argv[1], crpyt_(key));
    }
    if ( strcmp(argv[2], "-d") == 0 ) {
      char key;
      printf("Enter your key\n");
      crypt(argv[1], crypt_(key));
    }
    if ( strcmp(argv[2], "-v") == 0 ) {
      char key;
      printf("Enter your key\n");
      crypt(argv[1], crypt_key(key)); 
    }
  }
  printf("\n");
  return 0;
}

void crypt_file(char filename[], char key[]) {
  
  FILE *original_fp;
  original_fp = fopen(filename, "r");
  if ( original_fp == NULL ) {
   fprintf(stderr, "File not found.\n");
   exit(1); 
  }
  FILE *updated_fp;
  updated_fp = fopen("output.txt", "w");
  char c;
  while ( !feof(original_fp) ) {
    c = fgetc(original_fp);
    fputc(c ^ crypt_key(key), updated_fp);
  }
  fclose(updated_fp);
  fclose(original_fp);
}

void decrypt_view(char filename[], char key[]) {
  FILE *original_fp;
  original_fp = fopen(filename, "r");
  
  if ( original_fp == NULL ) {
   fprintf(stderr, "File not found.\n");
   exit(1); 
  }
  
  char c;
  while ( !feof(original_fp) ) {
    c = fgetc(original_fp);
    printf("%c", c ^ crypt_key(key));
  }
  fclose(original_fp);
}

char crypt_key(char key[]) {
  char c = '0';
  for (int i = 0 ; key[i] != '\0' ; i++ ) {
    c = c ^ key[i];
  }
  return c;
}

const char* generate_key() {
  char key[12];
  key[11] = '\0';
  for ( int i = 0 ; i < 11 ; i++ ) {
    key[i] = (char)(rand() % 256);
  }
  char *pkey = key;
  return pkey;
}
