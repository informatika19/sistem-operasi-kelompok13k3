#include <stdio.h>

void main(int argc, char* argv[]) {
  int i;

  if (argc < 2) {
    printf("Specify file name to load\n");
    return;
  }

  FILE* loadFil;
  loadFil = fopen(argv[1], "r");
  if (loadFil == 0) {
    printf("File not found\n");
    return;
  }

  FILE* floppy;
  floppy = fopen("system.img", "r+");
  if (floppy == 0) {
    printf("system.img not found\n");
    return;
  }

  char map[512];
  fseek(floppy, 512 * 0x100, SEEK_SET);
  for (i = 0; i < 512; i++) map[i] = fgetc(floppy);

  char dir[1024];
  fseek(floppy, 512 * 0x101, SEEK_SET);
  for (i = 0; i < 1024; i++) dir[i] = fgetc(floppy);

  char sector[512];
  fseek(floppy, 512 * 0x103, SEEK_SET);
  for (i = 0; i < 512; i++) sector[i] = fgetc(floppy);

  for (i = 0; i < 1024; i = i + 16)
    if (dir[i] == 0 && dir[i+1] == 0 && dir[i+2] == 0) break;
  if (i == 1024) {
    printf("Not enough room in directory\n");
    return;
  }
  int dirindex = i;

  for (i = 0; i < 14; i++) dir[dirindex + i + 2] = 0x00;
  for (i = 0; i < 14; i++) {
    if (argv[1][i] == 0) break;
    dir[dirindex + i + 2] = argv[1][i];
  }

  for (i = 0; i < 32; i++) {
    if (sector[i*16] == 0) break;
  }

  if (i == 32) {
    printf("No sector available\n");
    return;
  }

  int sectIndex = i;
  dir[dirindex] = 0xFF;
  dir[dirindex + 1] = sectIndex;

  int sectcount = 0;
  while (!feof(loadFil)) {
    if (sectcount == 20) {
      printf("Not enough space in directory entry for file\n");
      return;
    }

    for (i = 0; i < 256; i++)
      if (map[i] == 0) break;
    if (i == 256) {
      printf("Not enough room for file\n");
      return;
    }

    map[i] = 0xFF;
    sector[sectIndex * 16 + sectcount] = i;
    sectcount++;

    printf("Loaded %s to sector %d\n", argv[1], i);

    fseek(floppy, i * 512, SEEK_SET);
    for (i = 0; i < 512; i++) {
      if (feof(loadFil)) {
        fputc(0x0, floppy);
        break;
      } else {
        char c = fgetc(loadFil);
        fputc(c, floppy);
      }
    }
  }

  fseek(floppy, 512 * 0x100, SEEK_SET);
  for (i = 0; i < 512; i++) fputc(map[i], floppy);

  fseek(floppy, 512 * 0x101, SEEK_SET);
  for (i = 0; i < 1024; i++) fputc(dir[i], floppy);

  fseek(floppy, 512 * 0x103, SEEK_SET);
  for (i = 0; i < 512; i++) fputc(sector[i], floppy);

  fclose(floppy);
  fclose(loadFil);
}