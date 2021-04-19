#include "text.h"

void printString(char *string) {
	int i = 0;
	while(string[i] != '\0'){
		interrupt(0x10, 0xE00 + string[i], 0, 0, 0);
		i++;
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