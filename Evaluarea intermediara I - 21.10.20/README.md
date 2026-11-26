# Metrici software și ingineria calității

## Tema: Varianta B

**Dezvoltarea unui proiect:** stabilirea unui set de metrici (minim 10) care se
referă la proiectarea orientată pe obiecte și determinarea valorilor acestora.

## Proiectul măsurat

Proiectul 31: **Meniuri / Submeniuri** (C++), fișierul `mnn.cpp`.

Clasa `Meniu` are nume, poziție pe ecran și opțiuni cu identificatori numerici.
Are operatorii `*`, `+`, `!`, `+` (între 2 meniuri) și `/`, plus afișare/ștergere,
iterator (clasa interioară `Iterator`), salvare/încărcare din fișier și excepții.

## Cum am măsurat

- Am măsurat clasele `Meniu` și `Iterator` (clasă interioară în `Meniu`).
- Funcțiile `main` și `pornesteAnsi` nu sunt în clase, deci nu intră în metrici
  (doar în LOC și comentarii).
- Metricile sunt numărate manual din cod, apoi verificate cu comenzi simple.

## Setul de metrici (17)

| # | Metrica | Ce măsoară | Meniu | Iterator | Total |
|---|---|---|---|---|---|
| 1 | Număr de clase | câte clase are proiectul | - | - | **2** |
| 2 | NOA | număr de atribute | 7 | 2 | **9** |
| 3 | NOM | număr de metode | 19 | 5 | **24** |
| 4 | Operatori supraîncărcați | `=`, `*`, `+`, `+`, `!`, `/` în Meniu; `!=`, `++`, `*` în Iterator | 6 | 3 | **9** |
| 5 | DIT | adâncimea moștenirii | 0 | 0 | **0** |
| 6 | NOC | număr de clase copil | 0 | 0 | **0** |
| 7 | CBO | cuplaj între clase (fără STL) | 1 | 1 | **1** |
| 8 | WMC | suma complexităților metodelor | 38 | 5 | **43** |
| 9 | CC maxim | cea mai mare complexitate a unei metode | 4 | 1 | **4** |
| 10 | Imbricare maximă | cele mai multe `for`/`if` unul în altul | 3 | 0 | **3** |
| 11 | LCOM4 | lipsa de coeziune (1 = foarte bine) | 2 | 1 | - |
| 12 | AHF | atribute ascunse (private) | 100% | 100% | **100%** |
| 13 | MHF | metode ascunse (private) | 2/19 = 10,5% | 0/5 = 0% | **2/24 = 8,3%** |
| 14 | PF | metode virtuale (polimorfism) | 0 | 0 | **0** |
| 15 | LOC | linii de cod în `mnn.cpp` | - | - | **255** total, **229** nenule |
| 16 | Comentarii | linii cu comentarii / linii nenule | - | - | **49 / 229 = 21%** |
| 17 | Excepții | locuri cu `throw` (2 tipuri: `out_of_range`, `runtime_error`) | - | - | **4** |

## Formule folosite

- **WMC** = suma complexităților ciclomatice ale metodelor.
- **CC** (a unei metode) = 1 + număr de `if`, `for`, `while`, `&&`, `||`.
- **AHF** = atribute private / toate atributele.
- **MHF** = metode private / toate metodele.
- **CBO** = câte alte clase (scrise de noi) folosește clasa.
- **LCOM4** = număr de grupuri de metode care nu folosesc aceleași atribute.

## Anexă: calculul WMC

### Clasa Meniu (WMC = 38)

| Metoda | CC | De ce |
|---|---|---|
| `creste` | 2 | 1 `for` |
| `copiaza` | 2 | 1 `for` |
| `begin` | 1 | |
| `end` | 1 | |
| constructor implicit | 1 | |
| constructor de copiere | 1 | |
| destructor | 1 | |
| `operator=` | 2 | 1 `if` |
| `getNr` | 1 | |
| `getNume` | 1 | |
| `afiseaza` | 2 | 1 `for` |
| `sterge` | 2 | 1 `for` |
| `operator*` | 1 | |
| `operator+` (string) | 2 | 1 `if` |
| `operator!` | 4 | 2 `for` + 1 `if` |
| `operator+` (Meniu) | 3 | 1 `for` + 1 `if` |
| `operator/` | 4 | 1 `if` + 1 `||` + 1 `for` |
| `salveaza` | 3 | 1 `if` + 1 `for` |
| `incarca` | 4 | 2 `if` + 1 `for` |
| **Total** | **38** | 19 metode |

### Clasa Iterator (WMC = 5)

| Metoda | CC |
|---|---|
| constructor | 1 |
| `operator!=` | 1 |
| `operator++` | 1 |
| `operator*` | 1 |
| `idCurent` | 1 |
| **Total** | **5** |

## Concluzii

- Nu există moștenire (DIT = 0, NOC = 0), deci designul este simplu.
- Cuplajul este mic (CBO = 1): `Meniu` și `Iterator` depind doar una de alta.
- Toate atributele sunt private (AHF = 100%), deci încapsularea este bună.
- Complexitatea este mică: cea mai mare metodă are CC = 4.
- LCOM4 pentru `Meniu` este 2, pentru că `begin()` nu folosește direct niciun
  atribut (doar transmite `this`). Restul metodelor lucrează cu aceleași date,
  deci coeziunea este bună.
- Comentariile sunt aproximativ 21% din cod.

## Cum se rulează proiectul

```
g++ -std=c++11 -o meniu meniu.cpp
meniu.exe
```

Pe Linux / Mac:./meniu

find /c /v "" mnn.cpp
```

Pe Linux / Mac: `wc -l mnn.cpp`


