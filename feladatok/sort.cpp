
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Zoldseg {
    int x,y,z,w;
    bool rosszabb = false;
};

int INF = 2000000000;


/* túl sok memóriát foglal
struct Fenwick_fa2D {
    unsigned zoldsegek_szama;
    vector<vector<int>> adattarolo; // mindegyik index az lsb min-ét tartalmazza

    /*
     * 1 (01): LSB = 1
     * 2 (10): LSB = 1,2
     * 3 (11): LSB = 3
     * 4 (100): LSB = 1,2,3,4
     * 5 (101): LSB = 5
     */
/*
    Fenwick_fa2D(int zoldsegek_sz) : zoldsegek_szama(zoldsegek_sz), adattarolo(zoldsegek_sz+2, vector<int>(zoldsegek_sz+2, INF)) {}

    void frissit(int y, int z, int w) {
        for (unsigned i = y; i <= zoldsegek_szama; i += i & -i) { // indulunk az eredeti y, z pozícióból, ha min, akkor beaűllítjuk, eztán megyünk tovább
            for (unsigned j = z; j <= zoldsegek_szama; j += j & -j) {
                adattarolo[i][j] = min(adattarolo[i][j], w);
            }
        }
    }

    int lekerdez(int y, int z) {
        int minimum = INF;
        for (int i = y; i > 0; i -= i & -i) { // megnézi, hogy van-e olyan zöldség, ami dominűálta
            for (int j = z; j > 0; j -= j & -j) {
                minimum = min(adattarolo[i][j], minimum);
            }
        } return minimum;
    }

};
int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned zoldsegek_szama;
    cin >> zoldsegek_szama;
    vector<Zoldseg> zoldsegek;

    for (int i = 0; i < zoldsegek_szama; i++) {
        Zoldseg ujz;
        cin >> ujz.x >> ujz.y >> ujz.z >> ujz.w;
        zoldsegek.push_back(ujz);
    }

    // x-ek sorba rendezése
    sort(zoldsegek.begin(), zoldsegek.end(), [](const Zoldseg& a, const Zoldseg& b) {
        return a.x < b.x;
    });


    Fenwick_fa2D fa(zoldsegek_szama);
    int legjobbak = 0;

    for (unsigned i = 0; i < zoldsegek_szama; i++) {
        if (zoldsegek[i].w <= fa.lekerdez(zoldsegek[i].y, zoldsegek[i].z) ) {
            legjobbak++;
        }
        fa.frissit(zoldsegek[i].y, zoldsegek[i].z, zoldsegek[i].w);
    }

    cout << legjobbak << endl;

    return 0;

}
*/


struct Fenwick_fa {
    unsigned meret;
    vector<int> adattarolo; // mindegyik index az inetvalluma min-ét tartalmazza

    Fenwick_fa(int zoldsegek_sz) : meret(zoldsegek_sz), adattarolo(zoldsegek_sz+1, INF) {}

    void frissit(int z, int w) {
        for (unsigned i = z; i <= meret; i += i & -i) { // indulunk az eredeti z pozícióból, ha min, akkor beaűllítjuk, eztán megyünk tovább
            adattarolo[i] = min(adattarolo[i], w);
        }
    }

    int lekerdez(int z) {
        int minimum =INF;
        for (int i = z; i > 0; i -= i & -i) { // megnézi, hogy van-e olyan zöldség, ami dominűálta
                minimum = min(adattarolo[i], minimum);
        } return minimum;
    }

    void reset(int z) {
        for (int i = z; i <= meret; i += i & -i) {
            adattarolo[i] = INF;
        }
    }

};

bool comparatorX(Zoldseg a,Zoldseg b) {
    return a.x < b.x;
}

bool comparatorY(Zoldseg a,Zoldseg b) {
    return a.y < b.y;
}

void DevAndConc(vector<Zoldseg>& zoldsegek, int bal, int jobb, Fenwick_fa& fa) {

    if (bal == jobb) return; // ha a rekurziok aljara ertunk

    int kozep = bal + (jobb - bal) / 2;

    DevAndConc(zoldsegek, bal,kozep, fa);
    DevAndConc(zoldsegek,kozep+1,jobb,fa);

    // y rendezés (csak a felosztott reszekben)
    sort(zoldsegek.begin() + bal, zoldsegek.begin() + kozep +1,comparatorY);
    sort(zoldsegek.begin() + kozep +1 , zoldsegek.begin() + jobb +1,comparatorY);

    vector<int> frissitett;

    int b = bal;

    // Fenwick faban az  indexek z-k tehat rendezve jarjuk be
    for (int j = kozep +1; j <= jobb; ++j) {
        while (b <= kozep && zoldsegek[b].y < zoldsegek[j].y) {
            fa.frissit(zoldsegek[b].z,zoldsegek[b].w);
            frissitett.push_back(zoldsegek[b].z);
            ++b;
        }

        // w ellenorzese
        int min_w_gyoztes = fa.lekerdez(zoldsegek[j].z -1);

        if (zoldsegek[j].w > min_w_gyoztes) {
            zoldsegek[j].rosszabb = true;
        }

    }
    // reaeteljuk a fenwick fat
    for (int z : frissitett) {
        fa.reset(z);
    }

    inplace_merge(zoldsegek.begin() + bal, zoldsegek.begin() + kozep + 1, zoldsegek.begin() + jobb + 1, comparatorY);


}

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned zoldsegek_szama;
    cin >> zoldsegek_szama;
    vector<Zoldseg> zoldsegek;

    for (int i = 0; i < zoldsegek_szama; i++) {
        Zoldseg ujz;
        cin >> ujz.x >> ujz.y >> ujz.z >> ujz.w;
        zoldsegek.push_back(ujz);
    }

    // x-ek sorba rendezése
    sort(zoldsegek.begin(), zoldsegek.end(), comparatorX);


    Fenwick_fa fa(zoldsegek_szama);

    DevAndConc(zoldsegek,0,zoldsegek_szama -1,fa);

    int nem_rosszak = 0;
    for (int i = 0; i < zoldsegek_szama; ++i) {
        if (!zoldsegek[i].rosszabb) nem_rosszak++;
    }

    cout << nem_rosszak << endl;

    return 0;

}