# Woche 12

## Aufgaben

### Aufgabe 12.1 (abnahmepflichtig & klausurrelevant)

Gegeben sei folgender Typ `struct Language` für Programmiersprachen:

```c
struct Language
{
    char name[8];
    int year;
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
    // alphabetisch aufsteigend
}

void aufgabe_12_1()
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

    qsort(languages, 10, sizeof(struct Language), &compareNameAscending);
    for (int i = 0; i < 10; ++i)
    {
        printf("%s (%d)\n", languages[i].name, languages[i].year);
    }
}
```

### Aufgabe 12.2 (abnahmepflichtig & klausurrelevant)

Eine Person habe einen Vornamen, einen Nachnamen und ein Geburtsjahr.
Definiere einen passenden Typ `struct Person` und denke dir Beispiel-Personen aus.

Schreibe vier Vergleichsfunktionen für das Sortieren von Personen mittels `qsort`:
1. von jung nach alt
2. per Vorname
3. per Nachname
4. per Nachname, bei gleichen Nachnamen per Vorname

Deine Beispiel-Personen sollten natürlich auch gleiche Nachnamen enthalten,
um die vierte Vergleichsfunktion sinnvoll auszuprobieren!

### Aufgabe 12.3 (**klausurrelevant**)

In Skorbut gibt es links unten neben dem `console`-Tab ein `diagnostics`-Tab.
Darin werden Unschönheiten/Probleme in deinem Programm aufgelistet.
**In der Klausur führt *jede* Diagnostic zu Punktabzügen!**

Behebe möglichst viele dieser Diagnostics für die Wochen 3 bis 12.
Ein Mausklick auf eine Diagnostic führt zur entsprechenden Stelle im Programm.

## FAQ

### Was ist ein `struct`?

Ein `struct` fasst mehrere Typen zu einem neuen Typ zusammen.
Das ist nützlich, wenn mehrere Informationen zusammengehören,
zum Beispiel Zähler und Nenner eines Bruchs:

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

Das kommt auf den Speicherbedarf des `struct`-Typen an.
Je größer der Speicherbedarf ist, desto sinnvoller ist es,
Kopien zu vermeiden, aber eine scharfe Grenze gibt es nicht.

### Warum ist `(*ergebnis)` eingeklammert?

- `*ergebnis.zaehler` würde `*(ergebnis.zaehler)` bedeuten
  - aber `ergebnis` ist kein `Bruch`
  - und `zaehler` ist kein Zeiger

### Was ist der Unterschied zwischen `s.m` und `p->m`?

- `s.m` funktioniert nur für `struct`-Variablen
- `p->m` funktioniert nur für *Zeiger* auf `struct`-Variablen
- `p->m` verhält sich exakt wie `(*p).m`

### Muss man wirklich bei *jeder* Verwendung dieses nervige `struct` vor den `Bruch` schreiben?!

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

Die Frage, ob man das tatsächlich tun sollte, spaltet die C-Community; es gibt gute Argumente pro und kontra.

In C++ ist das übrigens keine Thema, dort ist das `struct` grundsätzlich optional.
