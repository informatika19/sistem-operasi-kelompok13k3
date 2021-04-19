#include "folderIO.h"

void delDir(char entry) {
	char folderFiles[1024];
	int i;

	interrupt(0x21, 0x02, folderFiles, 257, 0);
	interrupt(0x21, 0x02, folderFiles + 512, 258, 0);

	//menghapus folder entry
	folderFiles[entry * 16] = 0x0;
	folderFiles[entry * 16 + 1] = '\0';

	//rewrite buffer ke sector
	interrupt(0x21, 0x03, &folderFiles, 257, 0);
	interrupt(0x21, 0x03, folderFiles + 512, 258, 0);

	for (i = 0; i < 64; i++) {
		if (folderFiles[i * 16] != 0xFF) {
			if (folderFiles[i * 16] == entry && folderFiles[i * 16 + 1] != '\0') {
	 			delFile(i);
	 		}
		}
	}

	for (i = 0; i < 64; i++) {
		if (folderFiles[i * 16] == entry && folderFiles[i * 16 + 1] == 0xFF) {
			delDir(i);
	 	}
	}
}