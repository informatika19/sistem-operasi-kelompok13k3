void handleInterrupt21 (int AX, int BX, int CX, int DX);
void printString(char *string);
void readString(char *string);
void clear(char *buffer, int length); //Fungsi untuk mengisi buffer dengan 0
void printLogo();
void printInMemory(char *string, int color, int x, int y);

int main () {

	//variabel input saat readString
	char input[255];

	//Menampilkan logo saat booting
	printLogo();

	//Memulai
	printString("\nStarting my OS...");

	//Membaca string
	printString("What is your name: ");
	readString(input);

	//Selesai
	printString("\nNice to meet you :)");

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
		default: 
			printString("Invalid interrupt"); 
	} 
}


//Prosedur menampilkan string
void printString(char *string){
	int i = 0;
	int nl = 0;
	while (string[i] != '\0') {
		// jika ada newline agar print dilanjutkan dari kiri layar
		if (string[i] == '\n') {
			nl = 1;
			break;
		}
		interrupt(0x10, 0xE00 + string[i], 0, 0, 0);
		i = i+1;	
	}
	interrupt(0x10, 0xE00 + '\n', 0, 0, 0);
	interrupt(0x10, 0xE00 + '\r', 0, 0, 0);
	if(nl) {
		printString(&string[i+1]);
	}
}

//Prosedur baca string
void readString(char *string) {
	int i = 0;
	char c = 0;
	while (c != '\r')
	{
		c = interrupt(0x16, 0, 0, 0, 0);
		if (c == '\r')
		{
			string[i] = '\0';
		}
		else
		{
			if (c == '\b')
			{
				interrupt(0x10, 0xE00 + '\b', 0, 0, 0);
				interrupt(0x10, 0xE00 + '\0', 0, 0, 0);
				interrupt(0x10, 0xE00 + '\b', 0, 0, 0);
				if (i > 0)
				{
					string[i] = '\0';
					i = i - 1;
				}
			}
			else
			{
				string[i] = c;
				i = i + 1;
				interrupt(0x10, 0xE00 + c, 0, 0, 0);
			}
		}
	}
	interrupt(0x10, 0xE00 + '\n', 0, 0, 0);
	interrupt(0x10, 0xE00 + '\r', 0, 0, 0);
}

//Prosedur menghapus buffer dengan mengisi seluruh elemen buffer menjadi 0x00
void clear(char *buffer, int length) {
	//Mengisi seluruh elemen buffer dengan 0x00
	int i;
	for(i = 0; i < length; i++){
		buffer[i] = 0x00;
	}
}

//Menampilkan string ke dalam memory
void printInMemory(char *string, int color, int x, int y)
{
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
void printLogo()
{
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

// mod function
int mod(int a, int b) {
	while (a >= b) {
		a = a - b;
	}
	return a;
}

// div function
int div(int a, int b) {
	int count = 0;
	while (a >= b) {
		a = a - b;
		count = count + 1;
	}
	return count - 1;
}


void readSector(char *buffer, int sector) {
	interrupt(0x13, 0x201, buffer, 
	div(sector, 36) * 0x100 + mod(sector, 18) + 1, 
	mod(div(sector, 18), 2) * 0x100);
}


void writeSector(char *buffer, int sector) {
	interrupt(0x13, 0x301, buffer, 
	div(sector, 36) * 0x100 + mod(sector, 18) + 1, 
	mod(div(sector, 18), 2) * 0x100);
}
