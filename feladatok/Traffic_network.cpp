#include <iostream>
#include <vector>
#include  <queue>

using namespace std;

struct Heap_min_rendez {
    bool operator()(const pair<unsigned,unsigned>& a, const pair<unsigned,unsigned>& b) { // Comparator a heap min-be rendezeshez
        return a.second > b.second;
    }
};

void dijkstra(unsigned kiindulo_cs, vector<unsigned>& tavolsagok, vector<vector<pair<unsigned, unsigned>>>& graf) {
    priority_queue<pair<unsigned,unsigned>, vector<pair<unsigned,unsigned>>, Heap_min_rendez> elerheto_csucs_tav; // vektorban eltarolt heap min-be rendezve => moho

    tavolsagok[kiindulo_cs] = 0;
    elerheto_csucs_tav.push({kiindulo_cs, 0});

    while (!elerheto_csucs_tav.empty()) {
        unsigned tav = elerheto_csucs_tav.top().second; // feldolgozom a legkozelebbi csucsot
        unsigned cs = elerheto_csucs_tav.top().first;

        elerheto_csucs_tav.pop();

        if (tav <= tavolsagok[cs]) {
            for (auto szomszed_par: graf[cs]) { // grafon vegig megyek a szomszedos csucsokon (ahova vezet út)
                unsigned szomszed_cs = szomszed_par.first;
                unsigned szomszed_tav = szomszed_par.second;
                if (szomszed_tav + tav < tavolsagok[szomszed_cs]) { // ha a jelenlegi csucson haladva rövidebb a táv az adott csucshoz
                    tavolsagok[szomszed_cs] = szomszed_tav + tav;
                    elerheto_csucs_tav.push({szomszed_cs, tavolsagok[szomszed_cs]});
                }
            }
        }
    }

}

int main() {

    int grafok_szama;
    cin >> grafok_szama;

    for (unsigned i = 0; i < grafok_szama; i++) {
        unsigned csucsok_szama, egyiranyu_szama, ketiranyu_szama, kiindulo_cs, cel_cs;
        cin >> csucsok_szama >> egyiranyu_szama >> ketiranyu_szama >> kiindulo_cs >> cel_cs;

        cel_cs--; // 0 indexelesre hozom
        kiindulo_cs--;
        vector<vector<pair<unsigned, unsigned>>> graf(csucsok_szama); // adjecacny list megvalositas
        vector<vector<pair<unsigned, unsigned>>> graf_megf(csucsok_szama); // otlet: csak 2 dijsktra algoritmu futattása is eleg

        for (unsigned m = 0; m < egyiranyu_szama; ++m) { // egyirányu elek beolvasasa
            unsigned k_cs,c_cs,hossz;
            cin >> k_cs >> c_cs >> hossz;
            k_cs--;
            c_cs--;
            graf[k_cs].push_back(make_pair(c_cs, hossz));
            graf_megf[c_cs].push_back(make_pair(k_cs, hossz));
        }

        const unsigned INF = 2147400000; // alapbol egy nagy szammal toltom fel a tavolsagokat
        vector<unsigned> tavolsagok(csucsok_szama, INF);

        dijkstra(kiindulo_cs,tavolsagok,graf); // tavolsagok feltoltve

        vector<unsigned> tavolsagok_vissza(csucsok_szama, INF);

        dijkstra(cel_cs,tavolsagok_vissza,graf_megf); // cel csucsbol tavolsagok feltoltve

        unsigned legroividebb = tavolsagok[cel_cs];

        for (unsigned k = 0; k < ketiranyu_szama; ++k) {
            unsigned k_cs,c_cs,hossz;
            cin >> k_cs >> c_cs >> hossz;
            k_cs--;
            c_cs--;
            unsigned egyikirany = tavolsagok[k_cs] + hossz + tavolsagok_vissza[c_cs]; // nem mindegy, hogy a ketiranyu ut melyik csucsan megyek at eloszor
            unsigned masikirany = tavolsagok[c_cs] + hossz + tavolsagok_vissza[k_cs];
            legroividebb = min(legroividebb,min(masikirany, egyikirany));

        }

        if (legroividebb < INF) {cout << legroividebb << endl;} // kiiratas
        else cout << -1 << endl;
    }


    return 0;
}

