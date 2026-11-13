#include <iostream>
#include <string>
using namespace std;

struct NodeAntrean {
    string nim, nama;
    NodeAntrean* next;
};

void cetakPeminjam(const string& nim, const string& nama) {
    cout << "Nim: " << nim << "\n";
    cout << "Nama: " << nama << "\n\n";
}

class Queue {
private:
    NodeAntrean* front;
    NodeAntrean* rear;
public:
    Queue() : front(NULL), rear(NULL) {}
    ~Queue() { while (!kosong()) { NodeAntrean tmp; dequeue(tmp); } }

    bool kosong() const { return front == NULL; }

    void enqueue(const string& nim, const string& nama) {
        NodeAntrean* baru = new NodeAntrean{nim, nama, NULL};
        if (rear == NULL) front = rear = baru;
        else { rear->next = baru; rear = baru; }
    }

    bool dequeue(NodeAntrean& hasil) {          
        if (kosong()) return false;
        NodeAntrean* hapus = front;
        hasil = *hapus;
        front = front->next;
        if (front == NULL) rear = NULL;
        delete hapus;
        return true;
    }

    void tampil() const {
        if (kosong()) { cout << "Antrean kosong.\n\n"; return; }
        int no = 1;
        for (NodeAntrean* c = front; c != NULL; c = c->next) {
            cout << "Antrean ke " << no++ << (c == front ? " (paling depan)" : "") << "\n";
            cetakPeminjam(c->nim, c->nama);
        }
    }
};

struct NodeRiwayat {
    string nama;
    int idBuku;
    NodeRiwayat* next;
};

class Stack {
private:
    NodeRiwayat* top;
public:
    Stack() : top(NULL) {}
    ~Stack() { while (top != NULL) pop(); }

    bool kosong() const { return top == NULL; }

    void push(const string& nama, int idBuku) {
        top = new NodeRiwayat{nama, idBuku, top};
    }

    bool pop() {                                
        if (kosong()) return false;
        NodeRiwayat* hapus = top;
        top = top->next;
        delete hapus;
        return true;
    }

    void tampil() const {
        if (kosong()) { cout << "Riwayat kosong.\n\n"; return; }
        int no = 1;
        for (NodeRiwayat* c = top; c != NULL; c = c->next) {
            cout << "Riwayat ke " << no++ << (c == top ? " (terbaru)" : "") << "\n";
            cout << "Nama: " << c->nama << "\n";
            cout << "ID buku: " << c->idBuku << "\n\n";
        }
    }
};

struct NodeBST {
    int id;
    NodeBST* kiri;
    NodeBST* kanan;
};

class BST {
private:
    NodeBST* root;

    NodeBST* sisip(NodeBST* node, int id, bool& berhasil) {
        if (node == NULL) { berhasil = true; return new NodeBST{id, NULL, NULL}; }
        if (id < node->id) node->kiri = sisip(node->kiri, id, berhasil);
        else if (id > node->id) node->kanan = sisip(node->kanan, id, berhasil);
        else berhasil = false;                  
        return node;
    }

    bool cari(NodeBST* node, int id) const {
        if (node == NULL) return false;
        if (id == node->id) return true;
        return id < node->id ? cari(node->kiri, id) : cari(node->kanan, id);
    }

    void preOrder(NodeBST* n) const {
        if (n == NULL) return;
        cout << n->id << "\n";
        preOrder(n->kiri);
        preOrder(n->kanan);
    }
    void inOrder(NodeBST* n) const {
        if (n == NULL) return;
        inOrder(n->kiri);
        cout << n->id << "\n";
        inOrder(n->kanan);
    }
    void postOrder(NodeBST* n) const {
        if (n == NULL) return;
        postOrder(n->kiri);
        postOrder(n->kanan);
        cout << n->id << "\n";
    }

    void hapusSemua(NodeBST* n) {
        if (n == NULL) return;
        hapusSemua(n->kiri);
        hapusSemua(n->kanan);
        delete n;
    }

public:
    BST() : root(NULL) {}
    ~BST() { hapusSemua(root); }

    bool tambah(int id) { bool ok = false; root = sisip(root, id, ok); return ok; }
    bool cari(int id) const { return cari(root, id); }

    void tampilTraversal() const {
        if (root == NULL) { cout << "BST kosong.\n\n"; return; }
        cout << "Traversal Pre-Order:\n";   preOrder(root);
        cout << "\nTraversal In-Order:\n";  inOrder(root);
        cout << "\nTraversal Post-Order:\n"; postOrder(root);
        cout << "\n";
    }
};

void menuEnqueue(Queue& antrean) {
    string nim, nama;
    cout << "NIM: "; cin >> nim;
    cin.ignore(1000, '\n');
    cout << "Nama: "; getline(cin, nama);
    antrean.enqueue(nim, nama);
    cout << nama << " masuk antrean.\n";
}

void menuDequeue(Queue& antrean, const BST& bst) {
    NodeAntrean peminjam;
    if (!antrean.dequeue(peminjam)) { cout << "Antrean kosong.\n"; return; }

    cout << "Peminjam yang diproses:\n";
    cetakPeminjam(peminjam.nim, peminjam.nama);

    int id;
    cout << "ID buku yang dipinjam: "; cin >> id;
    if (bst.cari(id))
        cout << peminjam.nama << " berhasil meminjam buku ID " << id << ".\n";
    else
        cout << "Buku ID " << id << " tidak ada di koleksi. "
             << peminjam.nama << " keluar dari antrean tanpa meminjam.\n";
}

void menuPush(Stack& riwayat, const BST& bst) {
    string nama;
    int id;
    cin.ignore(1000, '\n');
    cout << "Nama pengembali: "; getline(cin, nama);
    cout << "ID buku: "; cin >> id;
    if (bst.cari(id)) {
        riwayat.push(nama, id);
        cout << "Pengembalian dicatat di riwayat.\n";
    } else {
        cout << "ID buku tidak terdaftar di BST.\n";
    }
}

void menuPop(Stack& riwayat) {
    if (riwayat.pop()) cout << "Riwayat terakhir dihapus.\n";
    else cout << "Riwayat kosong.\n";
}

void menuTambahBuku(BST& bst) {
    int id;
    cout << "ID buku baru: "; cin >> id;
    if (bst.tambah(id)) cout << "ID " << id << " ditambahkan ke BST.\n";
    else cout << "ID " << id << " sudah ada.\n";
}

void menuCariBuku(const BST& bst) {
    int id;
    cout << "ID buku dicari: "; cin >> id;
    cout << "Buku ID " << id << (bst.cari(id) ? " ditemukan.\n" : " tidak ditemukan.\n");
}

void menuTraversal(const BST& bst) {
    bst.tampilTraversal();
}

void menuTampilSemua(const Queue& antrean, const Stack& riwayat, const BST& bst) {
    cout << "Proses Antrean Peminjaman (FIFO):\n\n";
    antrean.tampil();
    cout << "Riwayat Pengembalian (LIFO):\n\n";
    riwayat.tampil();
    cout << "Isi BST:\n\n";
    bst.tampilTraversal();
}

void tampilMenu() {
    cout << "\nSISTEM ANTREAN DAN PENGELOLAAN BUKU PERPUSTAKAAN\n";
    cout << "1. Tambah mahasiswa ke antrean\n";
    cout << "2. Proses peminjaman mahasiswa terdepan\n";
    cout << "3. Catat pengembalian buku\n";
    cout << "4. Hapus riwayat pengembalian terakhir\n";
    cout << "5. Tambah ID buku ke BST\n";
    cout << "6. Cari ID buku di BST\n";
    cout << "7. Tampilkan traversal BST\n";
    cout << "8. Tampilkan semua\n";
    cout << "0. Keluar\n";
    cout << "Pilihan: ";
}

int main() {
    system("cls");
    Queue antrean;
    Stack riwayat;
    BST bst;
    int pilihan;

    do {
        tampilMenu();
        cin >> pilihan;
        cout << "\n";

        switch (pilihan) {
            case 1: menuEnqueue(antrean); break;
            case 2: menuDequeue(antrean, bst); break;
            case 3: menuPush(riwayat, bst); break;
            case 4: menuPop(riwayat); break;
            case 5: menuTambahBuku(bst); break;
            case 6: menuCariBuku(bst); break;
            case 7: menuTraversal(bst); break;
            case 8: menuTampilSemua(antrean, riwayat, bst); break;
            case 0: break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    cout << "Program selesai.\n";
    return 0;
}