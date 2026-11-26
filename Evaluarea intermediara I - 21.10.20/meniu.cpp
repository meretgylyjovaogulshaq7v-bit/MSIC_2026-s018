
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <stdexcept>

using namespace std;

class Meniu {
private:
    string nume;
    int pozitieX, pozitieY;
    vector<string> optiuni;

public:
    // Constructor
    Meniu(string n = "Meniu", int x = 0, int y = 0) {
        nume = n;
        pozitieX = x;
        pozitieY = y;
    }

    // Schimbarea numelui: meniu * "nume"
    Meniu operator*(const string& numeNou) const {
        Meniu copie = *this;
        copie.nume = numeNou;
        return copie;
    }

    // Adaugarea unei optiuni: meniu + "optiune"
    Meniu operator+(const string& optiune) const {
        if (optiune.empty())
            throw invalid_argument("Optiunea nu poate fi vida!");

        Meniu copie = *this;
        copie.optiuni.push_back(optiune);
        return copie;
    }

    // Sortare alfabetica: !meniu
    Meniu operator!() const {
        Meniu copie = *this;
        sort(copie.optiuni.begin(), copie.optiuni.end());
        return copie;
    }

    // Unirea a doua meniuri
    Meniu operator+(const Meniu& altMeniu) const {
        Meniu rezultat = *this;

        for (const auto& opt : altMeniu.optiuni) {
            rezultat.optiuni.push_back(opt);
        }

        return rezultat;
    }

    // Crearea unui submeniu cu primele n optiuni
    Meniu operator/(int n) const {
        if (n < 0 || n > (int)optiuni.size())
            throw out_of_range("Numar invalid de optiuni!");

        Meniu submeniu("Submeniu", pozitieX, pozitieY);

        for (int i = 0; i < n; i++) {
            submeniu.optiuni.push_back(optiuni[i]);
        }

        return submeniu;
    }

    // Clasa iterator
    class Iterator {
    private:
        vector<string>::const_iterator it;

    public:
        Iterator(vector<string>::const_iterator pozitie) {
            it = pozitie;
        }

        string operator*() const {
            return *it;
        }

        Iterator& operator++() {
            ++it;
            return *this;
        }

        bool operator!=(const Iterator& alt) const {
            return it != alt.it;
        }
    };

    Iterator begin() const {
        return Iterator(optiuni.begin());
    }

    Iterator end() const {
        return Iterator(optiuni.end());
    }

    // Salvare in fisier
    void salvare(const string& fisier) const {
        ofstream fout(fisier);

        if (!fout)
            throw runtime_error("Eroare la deschiderea fisierului!");

        fout << nume << endl;
        fout << pozitieX << " " << pozitieY << endl;
        fout << optiuni.size() << endl;

        for (const auto& opt : optiuni) {
            fout << opt << endl;
        }

        fout.close();
    }

    // Incarcare din fisier
    void incarcare(const string& fisier) {
        ifstream fin(fisier);

        if (!fin)
            throw runtime_error("Fisierul nu poate fi deschis!");

        string numeNou;
        int x, y;
        int nr;

        getline(fin, numeNou);

        if (!(fin >> x >> y >> nr) || nr < 0)
            throw runtime_error("Format invalid al fisierului!");

        fin.ignore();

        vector<string> optiuniNoi;

        for (int i = 0; i < nr; i++) {
            string opt;
            if (!getline(fin, opt))
                throw runtime_error("Date incomplete in fisier!");

            optiuniNoi.push_back(opt);
        }

        nume = numeNou;
        pozitieX = x;
        pozitieY = y;
        optiuni = optiuniNoi;

        fin.close();
    }

    // Afisarea meniului
    void afisare() const {
        cout << "\nMeniu: " << nume << endl;
        cout << "Pozitie: (" << pozitieX
             << ", " << pozitieY << ")" << endl;

        cout << "Optiuni:" << endl;

        for (size_t i = 0; i < optiuni.size(); i++) {
            cout << i + 1 << ". " << optiuni[i] << endl;
        }
    }
};

// Program principal
int main() {
    try {
        Meniu meniu("Meniu principal", 10, 20);

        meniu = meniu + "Adauga";
        meniu = meniu + "Sterge";
        meniu = meniu + "Modifica";
        meniu = meniu + "Afiseaza";

        cout << "MENIUL INITIAL:";
        meniu.afisare();

        // Schimbarea numelui
        Meniu meniuNou = meniu * "Aplicatia mea";

        cout << "\nMENIUL CU NUME NOU:";
        meniuNou.afisare();

        // Sortare
        Meniu meniuSortat = !meniu;

        cout << "\nMENIUL SORTAT:";
        meniuSortat.afisare();

        // Creare submeniu
        Meniu submeniu = meniu / 2;

        cout << "\nSUBMENIU:";
        submeniu.afisare();

        // Unirea meniurilor
        Meniu meniu2("Meniu secundar", 5, 5);
        meniu2 = meniu2 + "Iesire";
        meniu2 = meniu2 + "Ajutor";

        Meniu meniuUnificat = meniu + meniu2;

        cout << "\nMENIUL UNIT:";
        meniuUnificat.afisare();

        // Parcurgere cu iterator
        cout << "\nPARCURGERE CU ITERATOR:" << endl;

        for (Meniu::Iterator it = meniu.begin();
             it != meniu.end(); ++it) {
            cout << *it << endl;
        }

        // Salvare
        meniu.salvare("meniu.txt");
        cout << "\nMeniul a fost salvat!" << endl;

        // Incarcare
        Meniu meniuIncarcat;
        meniuIncarcat.incarcare("meniu.txt");

        cout << "\nMENIUL INCARCAT DIN FISIER:";
        meniuIncarcat.afisare();

    }
    catch (const exception& e) {
        cerr << "\nEroare: " << e.what() << endl;
    }

    return 0;
}
