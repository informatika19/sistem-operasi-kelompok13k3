void handleInterrupt21 (int AX, int BX, int CX, int DX);
void clear(char *buffer, int length); //Fungsi untuk mengisi buffer dengan 0
void executeProgram(char *filename, int segment, int *success);
void printLogo();
void printInMemory(char *string, int color, int x, int y);

int main() {
	int success;

	printLogo();
	makeInterrupt21();
	handleInterrupt21(0XFF06, "shell", 0x2000, &success);
	
	while (1);
}

void handleInterrupt21 (int AX, int BX, int CX, int DX) {
	char AL, AH;
	AL = (char) (AX);
	AH = (char) (AX >> 8);
	switch (AL) {
		case 0x00:
			printString(BX);
			break;
		case 0x01:
			readString(BX);
			break;
		case 0x02:
			readSector(BX, CX);
			break;
		case 0x03:
			writeSector(BX, CX);
			break;
		case 0x04:
			readFile(BX, CX, DX, AH);
			break;
		case 0x05:
			writeFile(BX, CX, DX, AH);
			break;
		case 0x06:
			executeProgram(BX, CX, DX);
			break;
		default:
			printString("Invalid interrupt");
	}
}

void clear(char *buffer, int length) {
	int i;
	for(i = 0; i < length; ++i){
		buffer[i] = 0x00;
	}
}

void executeProgram(char *filename, int segment, int *success) {
	char bufferFile[512 * 16];
	int i;
	
	clear(bufferFile, 512 * 16);
	readFile(&bufferFile, filename, success, 0xFF);
	if (*success) {
		for (i=0; i<512 * 16; i++) {
			putInMemory(segment, i, bufferFile[i]);
		}
		launchProgram(segment);
	} else {
		interrupt(0x21, 0, "File doesn't exist!", 0, 0);
	}
}

void printInMemory(char *string, int color, int x, int y){
	if (x >= 0 && x <= 80 && y >= 0 && y <= 25)
	{
		int i = 0;
		while (string[i] != '\0' && string[i] != '\n')
		{
			int offset = 0x8000 + ((80 * y) + x) * 2;
			putInMemory(0xB000, offset, string[i]);
			putInMemory(0xB000, offset + 1, color);
			i++;
			x++;
		}
	}
}

//Menampilkan logo ascii saat booting
void printLogo(){
	printInMemory("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *", 0xA, 0, 0);
	printInMemory("* ##           ##                                 ##     ##  ###  ##     ###  *", 0xA, 0, 1);
	printInMemory("*  #            #                                  #      #  #  #  #     #  # *", 0xA, 0, 2);
	printInMemory("*  #            #                                  #      #     #  #        # *", 0xA, 0, 3);
	printInMemory("*  # ###  ###   #   ####  ########  #####   ####   # ###  #   ##   # ###  ##  *", 0xA, 0, 4);
	printInMemory("*  # ##  #   #  #  ##  ##  #  #  #   #   # ##  ##  # ##   #     #  # ##     # *", 0xA, 0, 5);
	printInMemory("*  ##    #####  #  #    #  #  #  #   #   # #    #  ##     #     #  ##       # *", 0xA, 0, 6);
	printInMemory("*  # #   #      #  ##  ##  #  #  #   #   # ##  ##  # #    #  #  #  # #   #  # *", 0xA, 0, 7);
	printInMemory("*  # #   #      #  ##  ##  #  #  #   #   # ##  ##  # #    #  #  #  # #   #  # *", 0xA, 0, 8);
	printInMemory("* ### ##  #### ###  ####  #########  ####   ####  ### ## ### ###  ### ## ###  *", 0xA, 0, 9);
	printInMemory("*                                    #                                        *", 0xA, 0, 10);
	printInMemory("*                                   ###                                       *", 0xA, 0, 11);
	printInMemory("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *", 0xA, 0, 12);
}