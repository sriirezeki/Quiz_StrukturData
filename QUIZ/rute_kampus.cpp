#include <iostream>
#include <climits>
#include <cctype>
using namespace std;

const int N = 6;                 
int graf[N][N];                  

void tambahSisi(int a, int b, int bobot) {   
    graf[a][b] = bobot;
    graf[b][a] = bobot;
}

void isiGraf() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) graf[i][j] = 0;

    tambahSisi(0, 1, 4);   // A B
    tambahSisi(0, 2, 2);   // A C
    tambahSisi(1, 2, 1);   // B C
    tambahSisi(1, 3, 5);   // B D
    tambahSisi(1, 4, 3);   // B E
    tambahSisi(2, 3, 8);   // C D
    tambahSisi(2, 4, 6);   // C E
    tambahSisi(3, 4, 2);   // D E
    tambahSisi(3, 5, 4);   // D F
    tambahSisi(4, 5, 3);   // E F
}

int bacaVertex(const char* pesan) {
    char c;
    while (true) {
        cout << pesan << " (A sampai F): ";
        cin >> c;
        c = toupper(c);
        if (c >= 'A' && c <= 'F') return c - 'A';
        cout << "Vertex tidak valid.\n";
    }
}

void cetakVertex(int urutan, int v) {
    cout << urutan << ". Vertex " << char('A' + v) << "\n";
}

void tampilGraf() {
    cout << "Hubungan antarlokasi (dari Adjacency Matrix):\n\n";
    for (int i = 0; i < N; i++) {
        cout << "Vertex " << char('A' + i) << " terhubung ke:\n";
        for (int j = 0; j < N; j++)
            if (graf[i][j] != 0)
                cout << "Vertex " << char('A' + j) << ", jarak " << graf[i][j] << "\n";
        cout << "\n";
    }
}

void bfs(int awal) {
    bool visited[N] = {false};
    int antrean[N], depan = 0, belakang = 0;

    visited[awal] = true;
    antrean[belakang++] = awal;

    cout << "Urutan penelusuran BFS dari vertex " << char('A' + awal) << ":\n";
    int urutan = 1;
    while (depan < belakang) {
        int u = antrean[depan++];
        cetakVertex(urutan++, u);
        for (int v = 0; v < N; v++) {
            if (graf[u][v] != 0 && !visited[v]) {
                visited[v] = true;
                antrean[belakang++] = v;
            }
        }
    }
}

void dfsRek(int u, bool visited[], int& urutan) {
    visited[u] = true;
    cetakVertex(urutan++, u);
    for (int v = 0; v < N; v++)
        if (graf[u][v] != 0 && !visited[v]) dfsRek(v, visited, urutan);
}

void dfs(int awal) {
    bool visited[N] = {false};
    int urutan = 1;
    cout << "Urutan penelusuran DFS dari vertex " << char('A' + awal) << ":\n";
    dfsRek(awal, visited, urutan);
}

void cetakRute(int prev[], int tujuan, int& urutan) {
    if (prev[tujuan] != -1) cetakRute(prev, prev[tujuan], urutan);
    cetakVertex(urutan++, tujuan);
}

void dijkstra(int awal, int tujuan) {
    int dist[N], prev[N];
    bool selesai[N];

    for (int i = 0; i < N; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
        selesai[i] = false;
    }
    dist[awal] = 0;

    for (int k = 0; k < N; k++) {
        int u = -1;                             
        for (int i = 0; i < N; i++)
            if (!selesai[i] && (u == -1 || dist[i] < dist[u])) u = i;

        if (u == -1 || dist[u] == INT_MAX) break;
        selesai[u] = true;

        for (int v = 0; v < N; v++) {
            if (graf[u][v] != 0 && !selesai[v] && dist[u] + graf[u][v] < dist[v]) {
                dist[v] = dist[u] + graf[u][v];
                prev[v] = u;
            }
        }
    }

    if (dist[tujuan] == INT_MAX) {
        cout << "Tidak ada rute dari " << char('A' + awal) << " ke " << char('A' + tujuan) << ".\n";
        return;
    }
    cout << "Rute terpendek dari " << char('A' + awal) << " ke " << char('A' + tujuan) << ":\n";
    int urutan = 1;
    cetakRute(prev, tujuan, urutan);
    cout << "Total jarak: " << dist[tujuan] << "\n";
}

void menuBFS() {
    int awal = bacaVertex("Vertex awal");
    cout << "\n";
    bfs(awal);
}

void menuDFS() {
    int awal = bacaVertex("Vertex awal");
    cout << "\n";
    dfs(awal);
}

void menuDijkstra() {
    int awal = bacaVertex("Vertex awal");
    int tujuan = bacaVertex("Vertex tujuan");
    cout << "\n";
    dijkstra(awal, tujuan);
}

void tampilMenu() {
    cout << "\nSISTEM PENCARIAN RUTE LINGKUNGAN KAMPUS\n";
    cout << "1. Tampilkan hubungan antarlokas\n";
    cout << "2. Telusuri graf dengan BFS\n";
    cout << "3. Telusuri graf dengan DFS\n";
    cout << "4. Cari rute terpendek\n";
    cout << "0. Keluar\n";
    cout << "Pilihan: ";
}

int main() {
    system("cls");
    isiGraf();
    int pilihan;

    do {
        tampilMenu();
        cin >> pilihan;
        cout << "\n";

        switch (pilihan) {
            case 1: tampilGraf(); break;
            case 2: menuBFS(); break;
            case 3: menuDFS(); break;
            case 4: menuDijkstra(); break;
            case 0: break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    cout << "Program selesai.\n";
    return 0;
}