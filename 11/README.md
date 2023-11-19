# Woche 11

## Aufgaben

- Lösche die alte Datei `skorbut.jar`
- Lade [skorbut version 2023-12-16](https://raw.githubusercontent.com/fredoverflow/skorbut-release/master/skorbut.jar) runter

### Aufgabe 11.0 Sortierkriterium (abnahmepflichtig & klausurrelevant)

- Untersuche die Funktion `compareDoubleAscending`:
  - Welche möglichen Werte hat `(x > y)` ?
  - Welche möglichen Werte hat `(x < y)` ?
  - Welche möglichen Werte hat `(x > y) - (x < y)` ?
  - Wann liefert `compareDoubleAscending` welchen Wert?
- Welche Funktion interessiert sich überhaupt für das Ergebnis von `compareDoubleAscending`?

```c
int compareDoubleAscending(const void* v, const void* w)
{
    double x = *(const double*)v;
    double y = *(const double*)w;

    return (x > y) - (x < y);
}

void compareDoubleAscending_test()
{
    double a[10] = {2.718, 0.707, 3.14, 1079252848800.0, 1.618, 1.41, 1836.1526734311, 4.669, 0.618, 1.059};

    qsort(a, 10, sizeof(double), &compareDoubleAscending);

    assert(a[0] == 0.618);
    assert(a[1] == 0.707);
    assert(a[2] == 1.059);
    assert(a[3] == 1.41);
    assert(a[4] == 1.618);
    assert(a[5] == 2.718);
    assert(a[6] == 3.14);
    assert(a[7] == 4.669);
    assert(a[8] == 1836.1526734311);
    assert(a[9] == 1079252848800.0);
}
```

### Aufgabe 11.1 Shorts sortieren (abnahmepflichtig & klausurrelevant)

- Aufgabe 11.0 hat ein `double`-Array *aufsteigend* sortiert
  - Sortiere nun ein `short`-Array *absteigend*
- Um aus zwei `short`s einen `int` zu berechnen, ist `(x > y) - (x < y)` Overkill
  - Stattdessen reicht auch `x - y`, siehe `strcmp` (Woche 6, unterste FAQ, letztes `return`)
  - Warum klappt dieser Subtraktionstrick für `char` und `short`, aber *nicht* für `double` oder `int`?
    - **Tipp:** Welche möglichen Werte hat `x - y` für `char`, `short`, `double` und `int`?

### Aufgabe 11.2 Strings sortieren (abnahmepflichtig & klausurrelevant)

Sortiere das `string`-Array `words` mit `qsort` alphabetisch aufsteigend:

```c
typedef const char* string;

int compareStringAscending(const void* v, const void* w)
{
    // ...
}

void compareStringAscending_test()
{
    string words[15] =
    {
        "The", "only", "way", "to", "learn",
        "a", "new", "programming", "language",
        "is", "by", "writing", "programs", "in", "it",
    };

    qsort(words, 15, sizeof(string), &compareStringAscending);

    for (int i = 0; i < 15; ++i)
    {
        printf("%s ", words[i]);
    }

    assert(strcmp(words[ 0], "The") == 0); //     Großbuchstaben (65...90)
    assert(strcmp(words[ 1], "a") == 0);  // vor Kleinbuchstaben (97...122)
    assert(strcmp(words[ 2], "by") == 0);
    assert(strcmp(words[ 3], "in") == 0);
    assert(strcmp(words[ 4], "is") == 0);
    assert(strcmp(words[ 5], "it") == 0);
    assert(strcmp(words[ 6], "language") == 0);
    assert(strcmp(words[ 7], "learn") == 0);
    assert(strcmp(words[ 8], "new") == 0);
    assert(strcmp(words[ 9], "only") == 0);
    assert(strcmp(words[10], "programming") == 0);
    assert(strcmp(words[11], "programs") == 0);
    assert(strcmp(words[12], "to") == 0);
    assert(strcmp(words[13], "way") == 0);
    assert(strcmp(words[14], "writing") == 0);
}
```

### Aufgabe 11.3 kurz vor lang (klausurrelevant)

- Sortiere kurze Strings vor lange Strings
- und Strings gleicher Länge wiederum alphabetisch

### Aufgabe 11.4 (klausurrelevant)

- In den Aufgaben 7.3 und 7.4 wurde die Haupt-Spiel-Funktion `ticTacToe` 2x kopiert
- Die Kopien unterschieden sich vom Original nur im Aufruf des Spielzugs für Spieler 1:

| Haupt-Spiel-Funktion     | Aufruf Spieler 1  | Aufruf Spieler 2  |
| ------------------------ | ----------------- | ----------------- |
| `void ticTacToe()`       | `menschlicherZug` | `menschlicherZug` |
| `void ticTacToeLeicht()` | `zufaelligerZug`  | `menschlicherZug` |
| `void ticTacToeSchwer()` | `schlauerZug`     | `menschlicherZug` |

- Kopiere `void ticTacToe()` zum dritten Mal in eine neue Funktion:
  - `void ticTacToeFlexibel(void (* spielzug)(char spielfeld[9], char spieler))`
- Verwende den Parameter `spielzug` sinnvoll in der Funktion `ticTacToeFlexibel`
- Vereinfache die 3 Haupt-Spiel-Funktionen anschließend auf jeweils 1 Zeile Code

## FAQ

### Was bringen Funktionszeiger?

- Ein Funktionszeiger kann auf verschiedene Funktionen desselben Typs (Ergebnistyp + Parametertypen) zeigen
- Vergleiche die beiden Funktionen `printMultiplicationTable` und `printAdditionTable`:

```c
int times(int x, int y)
{
    return x * y;
}

int plus(int x, int y)
{
    return x + y;
}

void printMultiplicationTable(int n)
{
    for (int y = 1; y <= n; ++y)
    {
        for (int x = 1; x <= n; ++x)
        {
            printf("%4d", times(x, y));
        }                //////
        printf("\n");
    }
    printf("\n");
}

void printAdditionTable(int n)
{
    for (int y = 1; y <= n; ++y)
    {
        for (int x = 1; x <= n; ++x)
        {
            printf("%4d", plus(x, y));
        }                /////
        printf("\n");
    }
    printf("\n");
}
```

- `printMultiplicationTable` und `printAdditionTable` unterscheiden sich lediglich dadurch, ob sie `times` oder `plus` aufrufen
- Beide Funktionen `int times(int, int)` und `int plus(int, int)` haben denselben Typ `int (int, int)`
- Deshalb kann man mit einem Funktionszeiger-Parameter über die konkret aufgerufene Funktion abstrahieren:

```c
void printTable(int n, int (* operation)(int, int))
{
    for (int y = 1; y <= n; ++y)
    {
        for (int x = 1; x <= n; ++x)
        {
            printf("%4d", operation(x, y));
        }                //////////
        printf("\n");
    }
    printf("\n");
}

void printMultiplicationTable(int n)
{
    printTable(n, &times);
}                ///////

void printAdditionTable(int n)
{
    printTable(n, &plus);
}                //////
```

### Welche Parameter hat `qsort`?

```c
void qsort(void*    firstElement,
           unsigned numberOfElements,
           unsigned bytesPerElement,
           int   (* compare)(const void*, const void*))
```

### Was bedeutet `void* firstElement` ?

- Ein `void*` ist eine rohe Speicheradresse ohne weitere Typinformation,
was die Bytes beginnend bei dieser Speicheradresse bedeuten
- Ein `void*` kann mit jedem getypten Zeiger (z.B. `double*`) initialisiert werden,
die zusätzliche Typinformation (hier `double`) geht dabei verloren
- Für `qsort` ist das notwendig/nützlich, um Arrays *beliebiger* Element-Typen sortieren zu können

### Welchen Sinn hat `int (* compare)(const void*, const void*)` ?

- `qsort` kennt weder den Element-Typ noch die gewünschte Sortierreihenfolge
  - Daher muss `qsort` ständig `compare` zum Vergleichen zweier Elemente aufrufen
- Die Bedeutung des Ergebnis-`int` kennen wir bereits von `strcmp`:
  - *irgendein* negativer Wert, falls das erste Element vor das zweite gehört
  - *irgendein* positiver Wert, falls das zweite Element vor das erste gehört
  - 0, falls beide Elemente im Sinne der Sortierreihenfolge äquivalent sind

### Warum ist `(* compare)` eingeklammert?

- `int (* compare)(const void*, const void*)` ist ein *Zeiger* auf eine Funktion, die einen `int` liefert
- `int* compare(const void*, const void*)` wäre eine *Funktion*, die einen Zeiger auf einen `int` liefert

### Wieso `const void*` statt `void*`?

- Der reine *Vergleich* zweier Elemente muss die Elemente nur lesen, nicht verändern
- Je nach Ergebnis des Vergleichs vertauscht `qsort` ggf. die beiden Elemente

### Was bedeutet `*(const double*)v` ?

- `v` zeigt auf ein Element in dem zu sortierenden Array
  - Ein `const void*` weiß aber nicht, von welchem Typ dieses Element ist
  - Deshalb würde `*v` zum Zugriff auf das Element nicht funktionieren
- `(const double*)v` zeigt auf dasselbe Element wie `v` aber weiß, dass es ein `double` ist
- `*(const double*)v` ist dieses `double`-Element
- Formal ist `(neuerTyp)alterWert` eine *Typumwandlung*

### Wie könnte man `qsort` notfalls selber bauen?

[Quicksort](https://en.wikipedia.org/wiki/Quicksort)

```c
void qsort(void* base, unsigned count, unsigned size, int (* compare)(const void*, const void*))
{
    // Programming Pearls
    // 11.3 Better Quicksorts
    void* beyond = base + count * size;
    while (count >= 2)
    {
        memswap(base, base + rand() % count * size, size);
        void* p = base;
        void* q = beyond;
        while (true)
        {                                      ////////////////
            do p += size; while (p < beyond && compare(p, base) < 0);
            do q -= size; while (              compare(q, base) > 0);
            if (p > q) break;                  ////////////////
            memswap(p, q, size);
        }
        memswap(base, q, size);
        qsort(base, (q - base) / size, size, compare);
        base = q + size;
        count = (beyond - base) / size;
    }
}
```

### Geht das auch einfacher?

[Insertion Sort](https://en.wikipedia.org/wiki/Insertion_sort)

```c
void isort(void* base, unsigned count, unsigned size, int (* compare)(const void*, const void*))
{
    // Programming Pearls
    // 11.1 Insertion Sort
    void* beyond = base + count * size;

    for (void* p = base + size; p < beyond; p += size)
    {
        for (void* q = p; q > base && compare(q - size, q) > 0; q -= size)
        {                             ////////////////////
            memswap(q - size, q, size);
        }
    }
}
```
