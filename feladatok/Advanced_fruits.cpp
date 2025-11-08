#include <iostream>
#include <vector>
#include <string>
using namespace std;

string olvaszto(const string &egyikszo, const string &masikszo) {
    int e_hossz = egyikszo.size();
    int m_hossz = masikszo.size();


    // A részmegoldásokat tároló mátrix létrehozása
    vector<vector<string>> reszeredmenyek(e_hossz + 1, vector<string>(m_hossz + 1, ""));


    for (int i = 0; i <= e_hossz; i++) {
        for (int j = 0; j <= m_hossz; j++) {
            if (i == 0 && j == 0)
                reszeredmenyek[i][j] = ""; // bal felső sarok
            else if (j == 0)
                reszeredmenyek[i][j] = egyikszo.substr(0, i); // eltárolom a az első sorban
            else if (i == 0)
                reszeredmenyek[i][j] = masikszo.substr(0, j); // illetve az első oszlopban a két szót felépítő subtringet
        }
    }

    //
    for (int i = 1; i <= e_hossz; i++) {
        for (int j = 1; j <= m_hossz; j++) {
            if (reszeredmenyek[i][0].back() == reszeredmenyek[0][j].back()) { // Összahasonlítom az aktuális substringek utolsó karakterét

                reszeredmenyek[i][j] = reszeredmenyek[i-1][j-1] + reszeredmenyek[i][0].back(); // ha a jó, akkor a diagonális elemhez kell csak hozzávenni az aktuális substring utolsó betűjét
            } else {
                string egyik = reszeredmenyek[i][j-1] + reszeredmenyek[0][j].back(); // ha nem, akkor a két ezelőtti részmegoldáshoz adom hozzá az utolsó karaktert
                string masik = reszeredmenyek[i-1][j] + reszeredmenyek[i][0].back();
                if (egyik.size() < masik.size()) // amelyik rövidebb, az nyer
                    reszeredmenyek[i][j] = egyik;
                else if (egyik.size() > masik.size())
                    reszeredmenyek[i][j] = masik;
                else
                    reszeredmenyek[i][j] = egyik;
            }
        }
    }

    /* a mátrix kinyomtatása
    for (int j = 0; j <= m_hossz; ++j) {
        cout << endl;
        for (int i = 0; i <= e_hossz; ++i) {
            cout << reszeredmenyek[i][j] << "\t";
        }
    }
    cout << endl;
    */

    return reszeredmenyek[e_hossz][m_hossz];
}

int main() {
    string egyikszo;
    string masikszo;

    while (cin >> egyikszo >> masikszo) cout << olvaszto(egyikszo, masikszo) << endl;

    return 0;
}