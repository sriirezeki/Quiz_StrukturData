#include <iostream>
#include <string>
using namespace std;

struct Mahasiswa {
    string nim;
    string nama;
    double nilai;
    Mahasiswa* next;
};

class DynamicArray {
private:
    double* data;
    int size;
    int capacity;

    void perbesar() {                       
        capacity *= 2;
        double* baru = new double[capacity];
        for (int i = 0; i < size; i++) baru[i] = data[i];
        delete[] data;
        data = baru;
    }

public:
    DynamicArray() : size(0), capacity(2) { data = new double[capacity]; }
    ~DynamicArray() { delete[] data; }

    void tambah(double v) {
        if (size == capacity) perbesar();
        data[size++] = v;
    }

    int getSize() const { return size; }

    void insertionSort() {
        for (int i = 1; i < size; i++) {
            double key = data[i];
            int j = i - 1;
            while (j >= 0 && data[j] > key) {
                data[j + 1] = data[j];
                j--;
            }
            data[j + 1] = key;
        }
    }

    int binarySearch(double target) const {
        int kiri = 0, kanan = size - 1;
        while (kiri <= kanan) {
            int tengah = kiri + (kanan - kiri) / 2;
            if (data[tengah] == target) return tengah;
            else if (data[tengah] < target) kiri = tengah + 1;
            else kanan = tengah - 1;
        }
        return -1;
    }

    void tampil() const {
        if (size == 0) { cout << "Belum ada nilai.\n"; return; }
        for (int i = 0; i < size; i++)
            cout << "Nilai ke " << i + 1 << ": " << data[i] << "\n";
    }
};

class DaftarMahasiswa {
private:
    Mahasiswa* head;
    Mahasiswa* tail;

public:
    DaftarMahasiswa() : head(NULL), tail(NULL) {}
    ~DaftarMahasiswa() {
        while (head != NULL) {
            Mahasiswa* hapus = head;
            head = head->next;
            delete hapus;
        }
    }

    void cetakMahasiswa(const Mahasiswa* m) const {
        cout << "Nim: " << m->nim << "\n";
        cout << "Nama: " << m->nama << "\n";
        cout << "Nilai: " << m->nilai << "\n\n";
    }

    Mahasiswa* cariNIM(const string& nim) const {
        for (Mahasiswa* cur = head; cur != NULL; cur = cur->next)
            if (cur->nim == nim) return cur;
        return NULL;
    }

    bool tambah(const string& nim, const string& nama, double nilai) {
        if (cariNIM(nim) != NULL) return false;     
        Mahasiswa* baru = new Mahasiswa{nim, nama, nilai, NULL};
        if (head == NULL) head = tail = baru;
        else { tail->next = baru; tail = baru; }
        return true;
    }

    void tampil() const {
        if (head == NULL) { cout << "Belum ada data mahasiswa.\n"; return; }
        for (Mahasiswa* cur = head; cur != NULL; cur = cur->next)
            cetakMahasiswa(cur);
    }

    void tampilByNilai(double nilai) const {
        for (Mahasiswa* cur = head; cur != NULL; cur = cur->next)
            if (cur->nilai == nilai) cetakMahasiswa(cur);
    }
};

double bacaNilai() {
    double n;
    while (true) {
        cout << "Nilai (0 sampai 100): ";
        if (cin >> n && n >= 0 && n <= 100) return n;
        cout << "Input tidak valid, ulangi.\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

void menuTambah(DaftarMahasiswa& daftar, DynamicArray& nilaiArr, bool& sudahUrut) {
    string nim, nama;
    cout << "NIM: ";
    cin >> nim;
    cin.ignore(1000, '\n');
    cout << "Nama: ";
    getline(cin, nama);
    double nilai = bacaNilai();

    if (daftar.tambah(nim, nama, nilai)) {
        nilaiArr.tambah(nilai);
        sudahUrut = false;
        cout << "Data berhasil ditambahkan.\n";
    } else {
        cout << "NIM sudah terdaftar, data ditolak.\n";
    }
}

void menuTampil(const DaftarMahasiswa& daftar, const DynamicArray& nilaiArr, bool sudahUrut) {
    cout << "Data Mahasiswa (Linked List):\n\n";
    daftar.tampil();
    cout << "Kumpulan Nilai (Dynamic Array) "
         << (sudahUrut ? "sudah diurutkan" : "belum diurutkan") << ":\n";
    nilaiArr.tampil();
}

void menuUrut(DynamicArray& nilaiArr, bool& sudahUrut) {
    if (nilaiArr.getSize() == 0) { cout << "Belum ada data.\n"; return; }
    cout << "Sebelum diurutkan:\n";
    nilaiArr.tampil();
    nilaiArr.insertionSort();
    sudahUrut = true;
    cout << "\nSetelah diurutkan:\n";
    nilaiArr.tampil();
}

void menuCariNIM(const DaftarMahasiswa& daftar) {
    string nim;
    cout << "Masukkan NIM yang dicari: ";
    cin >> nim;
    cout << "\n";
    Mahasiswa* hasil = daftar.cariNIM(nim);
    if (hasil != NULL) {
        cout << "Mahasiswa ditemukan:\n";
        daftar.cetakMahasiswa(hasil);
    } else {
        cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan.\n";
    }
}

void menuCariNilai(const DaftarMahasiswa& daftar, const DynamicArray& nilaiArr, bool sudahUrut) {
    if (nilaiArr.getSize() == 0) { cout << "Belum ada data.\n"; return; }
    if (!sudahUrut) { cout << "Nilai belum diurutkan. Jalankan menu 3 terlebih dahulu.\n"; return; }

    double target = bacaNilai();
    cout << "\n";
    int idx = nilaiArr.binarySearch(target);
    if (idx != -1) {
        cout << "Nilai " << target << " ditemukan pada indeks " << idx << ".\n";
        cout << "Mahasiswa dengan nilai tersebut:\n\n";
        daftar.tampilByNilai(target);
    } else {
        cout << "Nilai " << target << " tidak ditemukan.\n";
    }
}

void tampilMenu() {
    cout << "\nSISTEM PENGELOLAAN NILAI MAHASISWA\n";
    cout << "1. Tambah data mahasiswa\n";
    cout << "2. Tampilkan data mahasiswa dan kumpulan nilai\n";
    cout << "3. Urutkan nilai (Insertion Sort)\n";
    cout << "4. Cari mahasiswa berdasarkan NIM (Linear Search)\n";
    cout << "5. Cari nilai tertentu (Binary Search)\n";
    cout << "0. Keluar\n";
    cout << "Pilihan: ";
}

int main() {
    system("cls");
    DaftarMahasiswa daftar;
    DynamicArray nilaiArr;
    bool sudahUrut = false;
    int pilihan;

    do {
        tampilMenu();
        cin >> pilihan;
        cout << "\n";

        switch (pilihan) {
            case 1: menuTambah(daftar, nilaiArr, sudahUrut); break;
            case 2: menuTampil(daftar, nilaiArr, sudahUrut); break;
            case 3: menuUrut(nilaiArr, sudahUrut); break;
            case 4: menuCariNIM(daftar); break;
            case 5: menuCariNilai(daftar, nilaiArr, sudahUrut); break;
            case 0: break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    cout << "Program selesai.\n";
    return 0;
}