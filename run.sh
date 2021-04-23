nasm bootloader.asm -o bootloader
dd if=bootloader of=system.img bs=512 count=1 conv=notrunc
dd if=map.img of=system.img bs=512 count=1 seek=256 conv=notrunc
dd if=files.img of=system.img bs=512 count=2 seek=257 conv=notrunc
dd if=sectors.img of=system.img bs=512 count=1 seek=259 conv=notrunc
bcc -ansi -c -o kernel.o kernel.c
bcc -ansi -c -o math.o modul/math.c
bcc -ansi -c -o text.o modul/text.c
bcc -ansi -c -o fileIO.o modul/fileIO.c
bcc -ansi -c -o folderIO.o modul/folderIO.c
bcc -ansi -c -o logo.o modul/logo.c
nasm -f as86 kernel.asm -o kernel_asm.o
ld86 -o kernel -d kernel.o kernel_asm.o math.o text.o fileIO.o folderIO.o logo.o
dd if=kernel of=system.img bs=512 conv=notrunc seek=1

# compile loadfile
gcc loadFile.c -o loadFile

# compile shell
bcc -ansi -c -o shell.o shell.c
nasm -f as86 lib.asm -o lib_asm.o
ld86 -o shell -d shell.o lib_asm.o
./loadFile shell

# compile cat
bcc -ansi -c bin/cat.c -o cat.o
ld86 -o cat -d cat.o lib_asm.o text.o fileIO.o math.o
./loadFile cat

# compile mkdir
bcc -ansi -c bin/mkdir.c -o mkdir.o
ld86 -o mkdir -d mkdir.o lib_asm.o
./loadFile mkdir

# compile rm
bcc -ansi -c bin/rm.c -o rm.o
ld86 -o rm -d rm.o lib_asm.o text.o fileIO.o folderIO.o math.o
./loadFile rm

#Loading file
cp files/13519111.txt 13519111.txt
cp files/13519122.txt 13519122.txt
cp files/13519123.txt 13519123.txt
./loadFile 13519111.txt 
./loadFile 13519122.txt
./loadFile 13519123.txt

# cleaning compiled files
rm bochsout.txt bootloader cat kernel loadFile mkdir shell rm *.o *.txt

# run bochs
echo c | bochs -f if2230.config