void handleInterrupt21 (int AX, int BX, int CX, int DX);
void printString(char *string);
void readString(char *string);
void clear(char *buffer, int length); //Fungsi untuk mengisi buffer dengan 0

int main () {
  putInMemory(0xB000, 0x8000, 'H');
  putInMemory(0xB000, 0x8001, 0xD);
  putInMemory(0xB000, 0x8002, 'a');
  putInMemory(0xB000, 0x8003, 0xD);
  putInMemory(0xB000, 0x8004, 'i');
  putInMemory(0xB000, 0x8005, 0xD);

// printString test
  printString("print string\ntest");

  while (1);
}

void handleInterrupt21 (int AX, int BX, int CX, int DX){
  switch (AX) {
    case 0x0:
      printString(BX);
      break;
    case 0x1:
      readString(BX);
      break;
    default:
      printString("Invalid interrupt");
  }
}


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
void clear(char *buffer, int length) {
	//Mengisi seluruh elemen buffer dengan 0x00
	for(int i = 0; i < length; i++){
		buffer[i] = 0x00;
	}
}
