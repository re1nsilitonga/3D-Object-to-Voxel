# Tucil2_13524090_13524093
# 3D to Voxel Converter

![Logo](cover.png)

## Deskripsi Program
Pernahkah kamu melihat sebuah benda dan membayangkan bagaimana bentuknya jika dibangun di dalam game Minecraft? Program ini melakukan hal yang persis sama secara otomatis!

Program ini berfungsi mengubah model 3D standar (yang permukaannya mulus dan terbuat dari segitiga) menjadi susunan balok-balok 3D. Proses pengubahan wujud menjadi balok-balok ini dikenal dengan istilah Voxelization.
Program ini mengimplementasikan voxelization model 3D berformat OBJ menggunakan pendekatan divide and conquer berbasis octree.

* **Voxel (Volumetric Pixel):** Jika gambar 2D di layar HP-mu tersusun dari titik-titik warna bernama *pixel*, maka bentuk 3D tersusun dari kubus-kubus bernama *voxel*. Secara sederhana, *voxel* adalah satu blok bangunan di Minecraft.
* **Octree & Divide and Conquer (Cara Cepat Membangun):** Untuk menemukan di mana balok harus diletakkan, program tidak mengecek seluruh dunia secara membabi buta. Ia menggunakan trik cerdas yang disebut *Octree* (Pohon beranak 8):
    1.  Program membuat satu **kotak raksasa** yang membungkus seluruh objek 3D.
    2.  Kotak raksasa itu kemudian **dibelah menjadi 8 kotak** yang lebih kecil.
    3.  Jika ada kotak yang ternyata kosong, kotak itu langsung dibuang.
    4.  Jika kotak tersebut menyentuh bagian dari objek 3D, kotak itu dibelah lagi menjadi 8. Begitu seterusnya sampai kotaknya mengecil seukuran blok Minecraft yang kita inginkan.

Secara umum, alur program adalah:
1. Membaca mesh segitiga dari file OBJ (vertex dan face).
2. Menentukan bounding box model.
3. Membangun octree secara rekursif sampai kedalaman maksimum.
4. Menentukan node yang merepresentasikan voxel valid.
5. Mengekspor hasil voxelization ke file OBJ baru.

## Requirement

Program ini membutuhkan:
1. Sistem operasi Linux, macOS, atau Windows.
2. Compiler C++ dengan dukungan C++17 (contoh: g++).
3. GNU Make (direkomendasikan).

Verifikasi tool:

```bash
g++ --version
make --version
```

## Cara Kompilasi

Program menggunakan makefile. Dari root project, jalankan:

```bash
make
```

Perintah tersebut akan:
1. Membuat folder bin jika belum ada.
2. Mengompilasi seluruh source di folder src.
3. Menghasilkan executable di:

```bash
bin/voxelizer.exe
```

Untuk membersihkan hasil build:

```bash
make clean
```

## Cara Menjalankan Program

Format perintah:

```bash
bin/voxelizer.exe <input.obj> <kedalamanMaks>
```

Keterangan parameter:
1. input.obj: path file OBJ input.
2. kedalamanMaks: kedalaman maksimum octree (bilangan bulat 1-20).

Contoh penggunaan:

```bash
bin/voxelizer.exe test/cow.obj 15
bin/voxelizer.exe test/pumpkin.obj 9
bin/voxelizer.exe test/teapot.obj 8
```

## Cara Menjalankan GUI (Viewer)

Program juga menyediakan viewer sederhana untuk melihat file OBJ secara interaktif.

Requirement tambahan untuk viewer:
1. Library SFML (graphics, window, system).
2. `pkg-config` untuk deteksi SFML saat build.

Contoh instalasi di Ubuntu/Debian:

```bash
sudo apt update
sudo apt install -y libsfml-dev pkg-config
```

Build viewer:

```bash
make viewer
```

Jika SFML terdeteksi, executable viewer akan dibuat di:

```bash
bin/viewer.exe
```

Cara menjalankan viewer:

```bash
bin/viewer.exe <file-obj>
```

Contoh:

```bash
bin/viewer.exe test/cube.obj
bin/viewer.exe test/cube-voxelized-4.obj
```

Kontrol pada viewer:
1. Klik dan drag mouse untuk rotasi objek.
2. Scroll mouse untuk zoom in atau zoom out.
3. Tutup jendela untuk keluar dari viewer.

Catatan:
1. `make` akan mencoba build `bin/voxelizer.exe` dan `bin/viewer.exe`.
2. Jika SFML belum terpasang, proses build viewer akan dilewati otomatis.
3. Viewer menerima path langsung, dan juga mencoba mencari file di folder `test/` jika path awal tidak ditemukan.

## Format Input yang Didukung

File input harus berformat OBJ dengan asumsi:
1. Face berupa segitiga (setiap baris f memiliki tepat 3 indeks).
2. Indeks face bernilai positif dan valid terhadap jumlah vertex.
3. Prefix selain v dan f dapat diabaikan oleh parser.

## Hasil Output

Program menghasilkan:
1. File OBJ hasil voxelization dengan pola nama:

```text
<nama-file-input>-voxelized-<tingkat kedalaman>.obj
```

2. Informasi statistik pada terminal, meliputi:
	- jumlah voxel
	- jumlah vertex dan face hasil output
	- statistik node octree
	- waktu proses

## Struktur Direktori

```text
Tucil2_13524090_13524093/
├── src/              # source code utama
├── bin/              # executable hasil kompilasi
├── test/             # data uji OBJ dan output
├── doc/              # laporan tugas kecil
├── makefile          # instruksi build dan clean
└── README.md
```

## Teknologi

1. Bahasa: C++17
2. Compiler: g++
3. Build Tool: GNU Make
4. Pendekatan: Octree-based voxelization (divide and conquer)

## Author

1. Nashiruddin Akram - 13524090
2. Reinsen Silitonga - 13524093

---

Tugas Kecil 2 - IF2211 Strategi Algoritma  
Semester Genap Tahun 2025/2026
