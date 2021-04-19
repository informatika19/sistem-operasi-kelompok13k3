#include "../modul/text.h"
#include "../modul/fileIO.h"
#include "../modul/math.h"

void main () {
    char name[14], tempBuff[512], fileContent[512 * 16], currDir;
	int isSuccess, i;
	isSuccess = 0;
	
	interrupt(0x21, 0x02, tempBuff, 512, 0);
    currDir = tempBuff[0];
    for (i = 0; i < 14; i++) {
		name[i] = tempBuff[i + 1];
	}

	for (i = 0; i < 512 * 16; i++) {
		fileContent[i] = 0x0;
	}

	readFile(fileContent, name, &isSuccess, currDir);

	if (isSuccess == 1) {
		printString(fileContent);
		printString("\r\n\0");

	} else {
		printString("File tidak ditemukan\r\n\0");
	}
	
    interrupt(0x21, 0x06, "shell", 0x2000, &isSuccess);
}