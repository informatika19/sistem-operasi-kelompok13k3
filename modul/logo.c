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