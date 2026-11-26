Varianta B – Dezvoltarea unui proiect
Titlul proiectului

Sistem de Calcul al Metricilor OOP în C++

1. Introducere

Scopul acestui proiect este dezvoltarea unei aplicații în limbajul C++ care permite gestionarea claselor și calcularea principalelor metrici orientate pe obiecte (OOP).

Aplicația utilizează concepte fundamentale ale programării orientate pe obiecte, precum încapsularea, clasele, obiectele, metodele, atributele și moștenirea.

2. Tehnologii utilizate
Limbaj de programare: C++
Standard: C++11
Compilator: GCC (g++)
Biblioteci: iostream, vector, string, fstream, algorithm
Mediu de dezvoltare: Visual Studio Code
3. Structura aplicației

Aplicația este organizată în următoarele componente:

Clasa Metoda – gestionează metodele și complexitatea acestora.
Clasa ClasaOOP – gestionează clasele, atributele, metodele și relațiile de moștenire.
Funcția cautaClasa() – identifică o clasă după nume.
Funcția salveazaRezultate() – salvează rezultatele în fișier.
Funcția main() – gestionează meniul interactiv al aplicației.
4. Metrici OOP implementate

Aplicația calculează următoarele metrici:

WMC (Weighted Methods per Class) – măsoară complexitatea totală a metodelor unei clase.
DIT (Depth of Inheritance Tree) – măsoară adâncimea ierarhiei de moștenire.
NOC (Number of Children) – numără clasele derivate direct.
CBO (Coupling Between Objects) – măsoară numărul dependențelor directe dintre clase.
RFC (Response For a Class) – estimează numărul metodelor care pot răspunde la un mesaj adresat clasei.
LCOM (Lack of Cohesion of Methods) – măsoară lipsa de coeziune dintre metodele unei clase.
5. Implementarea

Codul sursă este scris în fișierul main.cpp, utilizând clase, metode, vectori și funcții pentru gestionarea informațiilor și calcularea metricilor.

Aplicația include și tratarea excepțiilor pentru gestionarea situațiilor de eroare.

6. Compilare și executare
bash
g++ -std=c++11 -o metrici.exe main.cpp
metrici.exe
