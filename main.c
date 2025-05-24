#include <stdio.h>
#include <stdlib.h>

void crypt(char filename[], char key);
void decrypt_view(char filename[], char key);

int main( int argc, char *argv[] ) {
  if ( argc < 3 ) {
    fprintf(stderr, "Not enough arguments.\n");
    return 1;
  }
  else if ( argc > 3 ) {
    fprintf(stderr, "Too many arguments.\n");
    return 1;
  }
  else {
    
  }
  return 0;
}

void crypt(char filename[], char key) {
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
    fputc(c ^ key, updated_fp);
  }
  fclose(updated_fp);
  fclose(original_fp);
}

void decrypt_view(char filename[], char key) {
  FILE *original_fp;
  original_fp = fopen(filename, "r");
  
  if ( original_fp == NULL ) {
   fprintf(stderr, "File not found.\n");
   exit(1); 
  }
  
  char c;
  while ( !feof(original_fp) ) {
    c = fgetc(original_fp);
    printf("%c", c ^ key);
  }
  fclose(original_fp);
}
