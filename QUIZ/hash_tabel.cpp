
#include <iostream>
#include <string>
using namespace std;

const int UKURAN = 20;

enum Status {
    KOSONG,
    TERISI,
    DIHAPUS
};

struct Slot {
    long long key;
    string value;
    Status status;
};

class HashTable {
private:
    Slot tabel[UKURAN];

    int hash1(long long key) const {
        return key % UKURAN;
    }

    int hash2(long long key) const {
        return 19 - (key % 19);
    }

    int hitungIndex(long long key, int i) const {
        return (hash1(key) + i * hash2(key)) % UKURAN;
    }

    int cariIndex(long long key) const {
        for (int i = 0; i < UKURAN; i++) {
            int idx = hitungIndex(key, i);

            if (tabel[idx].status == KOSONG) {
                return -1;
            }

            if (tabel[idx].status == TERISI &&
                tabel[idx].key == key) {
                return idx;
            }
        }

        return -1;
    }

public:
    HashTable() {
        for (int i = 0; i < UKURAN; i++) {
            tabel[i].status = KOSONG;
        }
    }

    void insert(long long key, const string& nama) {
        int slotHapus = -1;

        for (int i = 0; i < UKURAN; i++) {
            int idx = hitungIndex(key, i);

            if (tabel[idx].status == TERISI) {
                if (tabel[idx].key == key) {
                    cout << "Gagal: NIM " << key
                         << " sudah terdaftar.\n";
                    return;
                }

                cout << "Collision pada index: " << idx
                     << "\nPercobaan ke-" << i << ".\n";
            }
            else if (tabel[idx].status == DIHAPUS) {
                if (slotHapus == -1) {
                    slotHapus = idx;
                }
            }
            else {
                int target = (slotHapus != -1)
                            ? slotHapus : idx;

                tabel[target] = {key, nama, TERISI};

                cout << "Insert berhasil!\n";
                cout << "NIM  : " << key << "\n";
                cout << "Nama : " << nama << "\n";
                cout << "Index: " << target << "\n";

                return;
            }
        }

        if (slotHapus != -1) {
            tabel[slotHapus] = {key, nama, TERISI};

            cout << "Insert berhasil!\n";
            cout << "NIM  : " << key << "\n";
            cout << "Nama : " << nama << "\n";
            cout << "Index: " << slotHapus << "\n";

            return;
        }

        cout << "Gagal: Tidak ditemukan slot yang tersedia "
             << "pada urutan probing.\n";
    }

    void search(long long key) const {
        int idx = cariIndex(key);

        if (idx != -1) {
            cout << "Data mahasiswa ditemukan!\n";
            cout << "Index: " << idx << "\n";
            cout << "NIM  : " << tabel[idx].key << "\n";
            cout << "Nama : " << tabel[idx].value << "\n";
        }
        else {
            cout << "NIM " << key
                 << " tidak ditemukan.\n";
        }
    }

    void remove(long long key) {
        int idx = cariIndex(key);

        if (idx != -1) {
            cout << "Data mahasiswa berhasil dihapus!\n";
            cout << "NIM  : " << tabel[idx].key << "\n";
            cout << "Nama : " << tabel[idx].value << "\n";
            cout << "Index: " << idx << "\n";

            tabel[idx].status = DIHAPUS;
        }
        else {
            cout << "NIM " << key
                 << " tidak ditemukan.\n";
            cout << "Tidak ada data yang dihapus.\n";
        }
    }

    void display() const {
        cout << "\nDATA HASH TABLE MAHASISWA\n";

        for (int i = 0; i < UKURAN; i++) {
            cout << "\nIndex " << i << "\n";

            if (tabel[i].status == TERISI) {
                cout << "Status : TERISI\n";
                cout << "NIM    : " << tabel[i].key << "\n";
                cout << "Nama   : " << tabel[i].value << "\n";
            }
            else if (tabel[i].status == DIHAPUS) {
                cout << "Status : DIHAPUS\n";
            }
            else {
                cout << "Status : KOSONG\n";
            }
        }
    }
};

void menuInsert(HashTable& ht) {
    long long nim;
    string nama;

    cout << "Masukkan NIM  : ";
    cin >> nim;

    cin.ignore(1000, '\n');

    cout << "Masukkan Nama : ";
    getline(cin, nama);

    cout << "\n";

    ht.insert(nim, nama);
}

void menuSearch(const HashTable& ht) {
    long long nim;

    cout << "Masukkan NIM yang dicari: ";
    cin >> nim;

    cout << "\n";

    ht.search(nim);
}

void menuRemove(HashTable& ht) {
    long long nim;

    cout << "Masukkan NIM yang dihapus: ";
    cin >> nim;

    cout << "\n";

    ht.remove(nim);
}

void menuDisplay(const HashTable& ht) {
    ht.display();
}

void menuDataUji(HashTable& ht) {
    long long nim[15] = {
        251401011, 251401014, 251401023,
        251401041, 251401083, 231301012,
        240102013, 221401088, 251401037,
        251401059, 241901089, 25110377,
        26111022, 23011062, 240311213
    };

    string nama[15] = {
        "Friska Fadilah",
        "Meisrik Wahyuni",
        "Bunga Lestari",
        "Baktiar Purba",
        "Sri Manalu",
        "Radit",
        "Ratu",
        "Citra",
        "Tulus",
        "Marcelina",
        "Grace",
        "Yana",
        "Kesya",
        "Chani",
        "Tere"
    };

    cout << "Memuat 15 data mahasiswa...\n\n";

    for (int i = 0; i < 15; i++) {
        cout << "Data ke-" << i + 1 << "\n";
        ht.insert(nim[i], nama[i]);
        cout << "\n";
    }

    cout << "Proses pemuatan data selesai.\n";
}

void tampilMenu() {
    cout << "\nSISTEM DATA MAHASISWA\n";
    cout << "MENGGUNAKAN HASH TABLE\n\n";

    cout << "1. Insert Data Mahasiswa\n";
    cout << "2. Search Data Mahasiswa\n";
    cout << "3. Remove Data Mahasiswa\n";
    cout << "4. Display Hash Table\n";
    cout << "5. Muat 15 Data Pengujian\n";
    cout << "0. Keluar\n";

    cout << "\nPilihan: ";
}

int main() {
    system("cls");
    HashTable ht;
    int pilihan;

    do {
        tampilMenu();
        cin >> pilihan;

        cout << "\n";

        switch (pilihan) {
            case 1:
                menuInsert(ht);
                break;

            case 2:
                menuSearch(ht);
                break;

            case 3:
                menuRemove(ht);
                break;

            case 4:
                menuDisplay(ht);
                break;

            case 5:
                menuDataUji(ht);
                break;

            case 0:
                cout << "Program selesai.\n";
                break;

            default:
                cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 0);

    return 0;
}
