# sistem-operasi-kelompok13k3

## Cara menjalankan sistem operasi
- Buat disk image `system.img`, `files.img`, `map.img`, dan `sectors.img` (Jalankan file `createimg.sh`)
```
chmod +x createimg.sh
./createimg.sh
```
- Ubah state `map.img` menjadi seperti berikut ini
```
00000000   FF FF FF FF  FF FF FF FF  FF FF FF FF  FF FF FF FF  FF 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  ................................
00000020   00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  ................................
00000040   00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  ................................
00000060   00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  ................................
00000080   00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  ................................
000000A0   00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  ................................
000000C0   00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  ................................
000000E0   00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  ................................
00000100   00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  ................................
```
- Jalankan file `run.sh`
```
chmod +x run.sh
./run.sh
```
## Aplikasi utilitas
### mkdir (utilitas untuk membuat direktori baru) 
Command mkdir
```
mkdir new_directory
```
### rm (utilitas untuk menghapus file atau folder)
Command rm file
```
rm file_name
```
Command rm folder
```
rm folder_name
```
### cat (utilitas untuk mencetak isi file)
Command cat
```
cat file_name
```
## Author
- [Febriawan Ghally Ar Rahman (13519111)](https://github.com/ghallyy)
- [Mgs. Tabrani (13519122)](https://github.com/mgstabrani)
- [Muhammad Rifky Muthahhari (13519123)](https://github.com/rifkymuth)