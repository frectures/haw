# Woche 12

## Aufgaben

### Aufgabe 12.0 Diagnostics

- Skorbut hat links unten neben dem `console`-Tab ein `diagnostics`-Tab
- Ein Mausklick auf eine Diagnostic führt zur problematischen Stelle im Programm
- **In der Klausur führt *jede* Diagnostic zu Punktabzügen!**
- Behebe möglichst viele Diagnostics für die Wochen 3 bis 11

### Aufgabe 12.1 Sprachsortierung

Gegeben sei folgender Typ `struct Language` für Programmiersprachen:

```c
struct Language
{
    char name[8];
    int  year;
};
```

Schreibe zwei unabhängige Vergleichsfunktionen für Programmiersprachen:

```c
int compareYearAscending(const void* v, const void* w)
{
    // von alt nach jung
}

int compareNameAscending(const void* v, const void* w)
{
    // alphabetisch
}

void sortLanguages()
{
    struct Language languages[10] =
    {
        {"C", 1972},
        {"Go", 2012},
        {"C++", 1983},
        {"Rust", 2015},
        {"Java", 1996},
        {"Lisp", 1958},
        {"Kotlin", 2016},
        {"Scheme", 1975},
        {"Fortran", 1957},
        {"Clojure", 2009},
    };

    qsort(languages, 10, sizeof(struct Language), &compareYearAscending);

    for (int i = 0; i < 10; ++i)
    {
        printf("%s (%d)\n", languages[i].name, languages[i].year);
    }

    printf("====================\n");

    qsort(languages, 10, sizeof(struct Language), &compareNameAscending);

    for (int i = 0; i < 10; ++i)
    {
        printf("%s (%d)\n", languages[i].name, languages[i].year);
    }
}
```

### Aufgabe 12.2 Gemüse-Typ

In Aufgabe 10.1 waren *zwei Arrays* für das englische und deutsche Gemüse vorgegeben:

```c
const char englisch[18][12] =
{
    "asparagus",
    "cabbage",
    "cauliflower",
    ...
};

const char deutsch[18][12] =
{
    "Spargel",
    "Kohl",
    "Blumenkohl",
    ...
};
```

Mit einem neuen Gemüse-Typ lassen sich beide Arrays zu *einem einzigen* verschmelzen:

```c
struct Gemuese
{
    char englisch[12];
    char deutsch[12];
};

const struct Gemuese gemuese[18] =
{
    {"asparagus", "Spargel"},
    {"cabbage", "Kohl"},
    {"cauliflower", "Blumenkohl"},
    ...
};
```

Passe den restlichen Code von Blatt 10 auf diese neue Struktur an.

## FAQ

### Was ist ein `struct`?

- Ein `struct` fasst mehrere Typen zu einem neuen Typ zusammen
- Das ist nützlich, wenn mehrere Informationen zusammengehören, zum Beispiel Zähler und Nenner eines Bruchs:

```c
struct Bruch
{
    int zaehler;
    int nenner;
};

void multipliziere(      struct Bruch  kopie,
                   const struct Bruch* original,
                         struct Bruch* ergebnis)
{
    (*ergebnis).zaehler = kopie.zaehler * (*original).zaehler;
      ergebnis->nenner  = kopie.nenner  *   original->nenner;
}

void bruchrechnen()
{
    struct Bruch pi = {22, 7};
    struct Bruch anderthalb = {3, 2};
    struct Bruch produkt;

    multipliziere(pi, &anderthalb, &produkt);
    printf("%d/%d\n", produkt.zaehler, produkt.nenner);
}
```

### Ist `struct Bruch  kopie` oder `const struct Bruch* original` besser?

- Das kommt auf den Speicherbedarf des `struct`-Typen an
- Je größer der Speicherbedarf, desto sinnvoller ist die Vermeidung von Kopien

### Warum ist `(*ergebnis)` eingeklammert?

- `*ergebnis.zaehler` würde `*(ergebnis.zaehler)` bedeuten
  - aber `ergebnis` ist kein `Bruch`
  - und `zaehler` ist kein Zeiger

### Was ist der Unterschied zwischen `s.m` und `p->m`?

- `s.m` funktioniert nur für `struct`-Variablen
- `p->m` funktioniert nur für *Zeiger* auf `struct`-Variablen
- `p->m` verhält sich exakt wie `(*p).m`

### Muss man wirklich bei *jeder* Verwendung dieses nervige `struct` vor `Bruch` schreiben?!

Mit einem `typedef` kann man das theoretisch eliminieren.
Ausführliche Variante:

```c
struct Bruch
{
    int zaehler;
    int nenner;
};

typedef  struct Bruch  Bruch; // ab jetzt steht  Bruch  für  struct Bruch
```

Kompakte Variante:

```c
typedef struct
{
    int zaehler;
    int nenner;
} Bruch;
```

- Ob man `struct Bruch` tatsächlich per `typedef` abkürzen sollte, spaltet die C-Community
- In C++ ist das übrigens kein Thema, dort ist das `struct` vor `Bruch` grundsätzlich optional
