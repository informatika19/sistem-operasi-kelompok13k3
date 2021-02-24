# MILESTONE 1
## Cara kerja interrupt di sistem operasi
## Cara kerja kode di kernel.asm
Sistem operasi ini memiliki file assembly yang bernama kernel.asm. Fungsi dari kernel.asm ini sebagai deklarasi dan implementasi fungsi putInMemory, interrupt, makeInterrupt21, dan handleInterrupt. Fungsi-fungsi ini akan dipanggil (digunakan) di kernel.c. Berikut ini kegunaan dari masing-masing fungsi tersebut.
- ```void putInMemory (int segment, int address, char character)```
Fungsi ini menulis sebuah karakter pada segment memori dengan offset tertentu.
- ```int interrupt (int number, int AX, int BX, int CX, int DX)```
Fungsi ini memanggil sebuah interrupt dengan nomor tertentu dan juga meneruskan parameter AX, BX, CX, DX berukuran 16-bit ke interrupt tersebut.
- ```void makeInterrupt21()```
Fungsi ini mempersiapkan tabel interrupt vector untuk memanggil kode Anda jika interrupt 0x21 terpanggil 
- ```void handleInterrupt21 (int AX, int BX, int CX, int DX)```
Fungsi ini dipanggil saat terjadi interrupt nomor 0x21. Implementasi interrupt 0x21 pada kernel dilakukan di sini
