#ifndef FILEIO_H
#define FILEIO_H

void writeFile(char *buffer, char *path, int *sectors, char parentIndex);
void readFile(char *buffer, char *path, int *result, char parentIndex);
void readSector(char *buffer, int sector); 
void writeSector(char *buffer, int sector); 

#endif
