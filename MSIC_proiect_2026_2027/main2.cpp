
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

// Clasa Menu
class Menu {
private:
    string name;
    int x, y;
    vector<string> options;

public:

    // Constructor implicit
    Menu() {
        name = "Menu";
        x = 0;
        y = 0;
    }

    // Constructor cu parametri
    Menu(string n, int posX, int posY) {
        name = n;
        x = posX;
        y = posY;
    }

    // Constructor de copiere
    Menu(const Menu& m) {
        name = m.name;
        x = m.x;
        y = m.y;
        options = m.options;
    }

    // Destructor
    ~Menu() {
    }

    // Operator * - schimba numele meniului
    Menu operator*(string newName) {
        Menu temp(*this);
        temp.name = newName;
        return temp;
    }

    // Operator + - adauga o optiune
    Menu operator+(string option) {
        Menu temp(*this);
        temp.options.push_back(option);
        return temp;
    }

    // Operator ! - sorteaza optiunile
    Menu operator!() {
        Menu temp(*this);

        sort(temp.options.begin(), temp.options.end());

        return temp;
    }

    // Operator + - uneste doua meniuri
    Menu operator+(const Menu& m) {
        Menu temp(*this);

        for (const auto& option : m.options) {
            temp.options.push_back(option);
        }

        return temp;
    }

    // Operator / - creeaza un submeniu
    Menu operator/(int n) {
        if (n < 0 || n > (int)options.size()) {
            throw out_of_range("Numar invalid!");
        }

        Menu temp(*this);

        temp.options.clear();

        for (int i = 0; i < n; i++) {
            temp.options.push_back(options[i]);
        }

        temp.name = name + " - Submeniu";

        return temp;
    }

    // Afisare meniu
    void display() const {
        cout << "\n";

        for (int i = 0; i < x; i++)
            cout << " ";

        cout << name << endl;

        for (int i = 0; i < y; i++)
            cout << " ";

        for (int i = 0; i < (int)options.size(); i++) {
            cout << i + 1 << ". " << options[i] << endl;

            for (int j = 0; j < y; j++)
                cout << " ";
        }
    }

    // Stergere meniu
    void removeMenu() {
        name = "";
        options.clear();

        cout << "Meniul a fost sters!\n";
    }

    // Numar de optiuni
    int getSize() const {
        return options.size();
    }
};

// Functia principala
int main() {
    try {

        // Creare meniu
        Menu m1("Meniul Principal", 2, 2);

        // Adaugare optiuni
        m1 = m1 + "Adauga student";
        m1 = m1 + "Sterge student";
        m1 = m1 + "Afiseaza studenti";
        m1 = m1 + "Iesire";

        cout << "MENIUL INITIAL:";
        m1.display();

        // Schimbare nume
        Menu m2 = m1 * "Meniul Nou";

        cout << "\nMENIUL CU NUME NOU:";
        m2.display();

        // Sortare alfabetica
        Menu m3 = !m1;

        cout << "\nMENIUL SORTAT:";
        m3.display();

        // Creare al doilea meniu
        Menu m4("Meniu Secundar", 2, 2);

        m4 = m4 + "Setari";
        m4 = m4 + "Ajutor";

        // Unire meniuri
        Menu m5 = m1 + m4;

        cout << "\nMENIUL UNIT:";
        m5.display();

        // Creare submeniu
        Menu sub = m1 / 2;

        cout << "\nSUBMENIU:";
        sub.display();

        // Stergere meniu
        // m2.removeMenu();

    }
    catch (exception& e) {
        cout << "Eroare: " << e.what() << endl;
    }

    return 0;
}
