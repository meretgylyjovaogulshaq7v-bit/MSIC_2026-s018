
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <stdexcept>

using namespace std;

// ===============================
// CLASA METODA
// ===============================
class Metoda {
private:
    string nume;
    int complexitate;
    vector<string> atributeUtilizate;

public:
    Metoda(string n, int c = 1) {
        nume = n;
        complexitate = c;
    }

    string getNume() const {
        return nume;
    }

    int getComplexitate() const {
        return complexitate;
    }

    void adaugaAtribut(const string& atribut) {
        if (find(atributeUtilizate.begin(),
                 atributeUtilizate.end(), atribut)
            == atributeUtilizate.end()) {
            atributeUtilizate.push_back(atribut);
        }
    }

    const vector<string>& getAtribute() const {
        return atributeUtilizate;
    }
};

// ===============================
// CLASA PRINCIPALA OOP
// ===============================
class ClasaOOP {
private:
    string nume;
    string parinte;
    vector<Metoda> metode;
    vector<string> atribute;
    vector<string> dependente;

public:
    ClasaOOP(string n) {
        nume = n;
    }

    string getNume() const {
        return nume;
    }

    string getParinte() const {
        return parinte;
    }

    void setParinte(const string& p) {
        parinte = p;
    }

    void adaugaMetoda(const Metoda& m) {
        metode.push_back(m);
    }

    void adaugaAtribut(const string& a) {
        if (find(atribute.begin(), atribute.end(), a)
            == atribute.end()) {
            atribute.push_back(a);
        }
    }

    void adaugaDependenta(const string& d) {
        if (find(dependente.begin(), dependente.end(), d)
            == dependente.end()) {
            dependente.push_back(d);
        }
    }

    int calculeazaWMC() const {
        int total = 0;

        for (const auto& m : metode) {
            total += m.getComplexitate();
        }

        return total;
    }

    int calculeazaRFC() const {
        vector<string> raspunsuri;

        for (const auto& m : metode) {
            raspunsuri.push_back(m.getNume());
        }

        for (const auto& d : dependente) {
            if (find(raspunsuri.begin(), raspunsuri.end(), d)
                == raspunsuri.end()) {
                raspunsuri.push_back(d);
            }
        }

        return raspunsuri.size();
    }

    int calculeazaCBO() const {
        return dependente.size();
    }

    int calculeazaDIT(const vector<ClasaOOP>& clase) const {
        int adancime = 0;
        string parinteCurent = parinte;

        while (!parinteCurent.empty()) {
            adancime++;

            bool gasit = false;

            for (const auto& c : clase) {
                if (c.getNume() == parinteCurent) {
                    parinteCurent = c.getParinte();
                    gasit = true;
                    break;
                }
            }

            if (!gasit)
                break;

            if (adancime > (int)clase.size())
                break;
        }

        return adancime;
    }

    int calculeazaNOC(const vector<ClasaOOP>& clase) const {
        int total = 0;

        for (const auto& c : clase) {
            if (c.getParinte() == nume)
                total++;
        }

        return total;
    }

    double calculeazaLCOM() const {
        int n = metode.size();

        if (n < 2)
            return 0;

        int perechiNeconexe = 0;
        int perechiConexe = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                bool comun = false;

                for (const auto& a : metode[i].getAtribute()) {
                    const vector<string>& alteAtribute =
                        metode[j].getAtribute();

                    if (find(alteAtribute.begin(),
                             alteAtribute.end(), a)
                        != alteAtribute.end()) {
                        comun = true;
                        break;
                    }
                }

                if (comun)
                    perechiConexe++;
                else
                    perechiNeconexe++;
            }
        }

        return (perechiNeconexe > perechiConexe)
            ? perechiNeconexe - perechiConexe : 0;
    }

    void afisare(const vector<ClasaOOP>& clase) const {
        cout << "\n================================\n";
        cout << "CLASA: " << nume << endl;
        cout << "================================\n";

        cout << "Numar metode: " << metode.size() << endl;
        cout << "Numar atribute: " << atribute.size() << endl;
        cout << "Parinte: "
             << (parinte.empty() ? "Niciunul" : parinte)
             << endl;

        cout << "\nMETRICI OOP:\n";
        cout << "WMC: " << calculeazaWMC() << endl;
        cout << "DIT: " << calculeazaDIT(clase) << endl;
        cout << "NOC: " << calculeazaNOC(clase) << endl;
        cout << "CBO: " << calculeazaCBO() << endl;
        cout << "RFC: " << calculeazaRFC() << endl;
        cout << "LCOM: " << calculeazaLCOM() << endl;
    }
};

// ===============================
// FUNCTIE CAUTARE CLASA
// ===============================
int cautaClasa(const vector<ClasaOOP>& clase,
               const string& nume) {
    for (int i = 0; i < (int)clase.size(); i++) {
        if (clase[i].getNume() == nume)
            return i;
    }

    return -1;
}

// ===============================
// SALVARE REZULTATE
// ===============================
void salveazaRezultate(const vector<ClasaOOP>& clase) {
    ofstream fout("rezultate.txt");

    if (!fout)
        throw runtime_error("Eroare la deschiderea fisierului!");

    for (const auto& c : clase) {
        fout << "Clasa: " << c.getNume() << endl;
        fout << "Parinte: " << c.getParinte() << endl;
        fout << "WMC: " << c.calculeazaWMC() << endl;
        fout << "DIT: " << c.calculeazaDIT(clase) << endl;
        fout << "NOC: " << c.calculeazaNOC(clase) << endl;
        fout << "CBO: " << c.calculeazaCBO() << endl;
        fout << "RFC: " << c.calculeazaRFC() << endl;
        fout << "LCOM: " << c.calculeazaLCOM() << endl;
        fout << "---------------------------\n";
    }

    fout.close();

    cout << "\nRezultatele au fost salvate in rezultate.txt!\n";
}

// ===============================
// PROGRAM PRINCIPAL
// ===============================
int main() {
    vector<ClasaOOP> clase;
    int optiune;

    do {
        cout << "\n====================================\n";
        cout << "       SISTEM DE ANALIZA OOP\n";
        cout << "====================================\n";

        cout << "1. Adaugare clasa\n";
        cout << "2. Adaugare metoda\n";
        cout << "3. Adaugare atribut\n";
        cout << "4. Definire mostenire\n";
        cout << "5. Definire dependenta\n";
        cout << "6. Calculare metrici OOP\n";
        cout << "7. Afisare clase\n";
        cout << "8. Salvare rezultate\n";
        cout << "0. Iesire\n";

        cout << "\nAlegeti optiunea: ";

        if (!(cin >> optiune)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Introduceti o valoare numerica!\n";
            continue;
        }

        try {
            switch (optiune) {

            case 1: {
                string nume;

                cout << "Numele clasei: ";
                cin >> nume;

                if (cautaClasa(clase, nume) != -1)
                    throw invalid_argument("Clasa exista deja!");

                clase.push_back(ClasaOOP(nume));

                cout << "Clasa adaugata cu succes!\n";
                break;
            }

            case 2: {
                string numeClasa, numeMetoda;
                int complexitate;

                cout << "Numele clasei: ";
                cin >> numeClasa;

                int index = cautaClasa(clase, numeClasa);

                if (index == -1)
                    throw runtime_error("Clasa nu exista!");

                cout << "Numele metodei: ";
                cin >> numeMetoda;

                cout << "Complexitatea metodei: ";
                cin >> complexitate;

                if (complexitate < 1)
                    throw invalid_argument("Complexitate invalida!");

                clase[index].adaugaMetoda(
                    Metoda(numeMetoda, complexitate)
                );

                cout << "Metoda adaugata!\n";
                break;
            }

            case 3: {
                string numeClasa, atribut;

                cout << "Numele clasei: ";
                cin >> numeClasa;

                int index = cautaClasa(clase, numeClasa);

                if (index == -1)
                    throw runtime_error("Clasa nu exista!");

                cout << "Numele atributului: ";
                cin >> atribut;

                clase[index].adaugaAtribut(atribut);

                cout << "Atribut adaugat!\n";
                break;
            }

            case 4: {
                string copil, parinte;

                cout << "Clasa copil: ";
                cin >> copil;

                cout << "Clasa parinte: ";
                cin >> parinte;

                int iCopil = cautaClasa(clase, copil);
                int iParinte = cautaClasa(clase, parinte);

                if (iCopil == -1 || iParinte == -1)
                    throw runtime_error("Clasa inexistenta!");

                if (copil == parinte)
                    throw invalid_argument("Mostenire invalida!");

                if (!clase[iCopil].getParinte().empty())
                    throw invalid_argument("Clasa are deja un parinte!");

                string curent = parinte;

                while (!curent.empty()) {
                    if (curent == copil)
                        throw invalid_argument("Ciclu de mostenire!");

                    int index = cautaClasa(clase, curent);

                    if (index == -1)
                        break;

                    curent = clase[index].getParinte();
                }

                clase[iCopil].setParinte(parinte);

                cout << "Mostenire definita!\n";
                break;
            }

            case 5: {
                string sursa, destinatie;

                cout << "Clasa sursa: ";
                cin >> sursa;

                cout << "Clasa destinatie: ";
                cin >> destinatie;

                int index = cautaClasa(clase, sursa);

                if (index == -1 ||
                    cautaClasa(clase, destinatie) == -1)
                    throw runtime_error("Clasa inexistenta!");

                if (sursa == destinatie)
                    throw invalid_argument("Dependenta invalida!");

                clase[index].adaugaDependenta(destinatie);

                cout << "Dependenta adaugata!\n";
                break;
            }

            case 6: {
                if (clase.empty()) {
                    cout << "Nu exista clase!\n";
                    break;
                }

                for (const auto& c : clase)
                    c.afisare(clase);

                break;
            }

            case 7: {
                for (const auto& c : clase) {
                    cout << "\nClasa: " << c.getNume() << endl;
                    cout << "Metode: " << c.calculeazaWMC() << " WMC\n";
                }

                break;
            }

            case 8:
                salveazaRezultate(clase);
                break;

            case 0:
                cout << "Program inchis!\n";
                break;

            default:
                cout << "Optiune invalida!\n";
            }
        }
        catch (const exception& e) {
            cout << "Eroare: " << e.what() << endl;
        }

    } while (optiune != 0);

    return 0;
}
