#include <stdio.h>

void crypt(char filename[], char key);

int main() {
  
  return 0;
}

void crypt(char filename[], char key) {
  FILE *original_fp;
  original_fp = fopen(filename, "r");
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
