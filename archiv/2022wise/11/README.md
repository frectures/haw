# Woche 11

## Aufgaben

### Aufgabe 11.1 (abnahmepflichtig & klausurrelevant)

In der FAQ wird ein `double`-Array mit `qsort` *aufsteigend* sortiert:

```c
int compareDoubleAscending(const void* v, const void* w)
{
    const double* p = v;
    const double* q = w;
    
    if (*p < *q) return -1;
    else return (*p > *q);
}

void aufgabe_11_1()
{
    double a[10] = {19, 41, 23, 13, 11, 17, 37, 43, 31, 29};
    
    qsort(a, 10, sizeof(double), &compareDoubleAscending);
    
    assert(a[0] == 11);
    assert(a[1] == 13);
    assert(a[2] == 17);
    assert(a[3] == 19);
    assert(a[4] == 23);
    assert(a[5] == 29);
    assert(a[6] == 31);
    assert(a[7] == 37);
    assert(a[8] == 41);
    assert(a[9] == 43);
}
```

Sortiere ein `short`-Array mit `qsort` *absteigend*.

### Aufgabe 11.2 (abnahmepflichtig & klausurrelevant)

Sortiere ein String-Array mit `qsort` alphabetisch aufsteigend,
also [lexikographisch](https://de.wikipedia.org/wiki/Lexikographische_Ordnung):

```c
typedef const char* string;

int compareStringAscending(const void* v, const void* w)
{
    // ...
}

void aufgabe_11_2()
{
    string words[15] = {
        "The", "only", "way", "to", "learn",
        "a", "new", "programming", "language",
        "is", "by", "writing", "programs", "in", "it",
    };

    qsort(words, 15, sizeof(string), &compareStringAscending);

    assert(strcmp(words[0], "The") == 0); // Großbuchstaben    (65...90)
    assert(strcmp(words[1], "a") == 0); // vor Kleinbuchstaben (97...122)

    for (int i = 0; i < 15; ++i)
    {
        printf("%s ", words[i]);
    }
}
```

### Aufgabe 11.3 (klausurrelevant)

Sortiere ein String-Array mit `qsort`.
Dabei sollen kurze Strings vor langen Strings einsortiert werden,
und Strings gleicher Länge wiederum lexikographisch.

### Aufgabe 11.4 (klausurrelevant)

Ignoriere die Groß- und Kleinschreibung für die lexikographische Sortierung,
d.h. `"The"` sollte zwischen `"programs"` und `"to"` einsortiert werden.
Passe dazu deine Funktion `my_strcmp` von letzter Woche entsprechend an.

## FAQ

### Was bringen Funktionszeiger?

Ein Funktionszeiger kann auf verschiedene Funktionen derselben *Signatur*
(selbe Parametertypen und selber Ergebnistyp) zeigen.

Vergleiche die beiden Funktionen `printMultiplicationTable` und `printAdditionTable`:

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
        }   ///////////// ^^^^^ //////
        putchar('\n');
    }
    putchar('\n');
}

void printAdditionTable(int n)
{
    for (int y = 1; y <= n; ++y)
    {
        for (int x = 1; x <= n; ++x)
        {
            printf("%4d", plus(x, y));
        }   ///////////// ^^^^ //////
        putchar('\n');
    }
    putchar('\n');
}

void printBothTables()
{
    printMultiplicationTable(10);
    printAdditionTable(10);
}
```

Die beiden Funktionen `printMultiplicationTable` und `printAdditionTable`
unterscheiden sich lediglich dadurch, ob sie `times` oder `plus` aufrufen.
Da beide Funktionen `times` und `plus` dieselbe Signatur `int(int, int)` haben,
kann man über die konkrete aufgerufene Funktion mit einem Funktionszeiger-Parameter abstrahieren:

```c
void printTable(int n, int (* operation)(int, int))
{
    for (int y = 1; y <= n; ++y)
    {
        for (int x = 1; x <= n; ++x)
        {
            printf("%4d", operation(x, y));
        }   ///////////// ^^^^^^^^^ //////
        putchar('\n');
    }
    putchar('\n');
}

void printBothTables()
{
    printTable(10, &times);
    printTable(10, &plus);
}   ////////////// ^^^^^
```

### Wie benutzt man die eingebaute Sortierfunktion `qsort`?

Das folgende Beispiel sortiert ein `double`-Array aufsteigend:

```c
int compareDoubleAscending(const void* v, const void* w)
{
    const double* p = v;
    const double* q = w;
    
    if (*p < *q) return -1;
    else return (*p > *q);
}

void compareDoubleAscending_test()
{
    double a[10] = {19, 41, 23, 13, 11, 17, 37, 43, 31, 29};
    
    qsort(a, 10, sizeof(double), &compareDoubleAscending);
    
    assert(a[0] == 11);
    assert(a[1] == 13);
    assert(a[2] == 17);
    assert(a[3] == 19);
    assert(a[4] == 23);
    assert(a[5] == 29);
    assert(a[6] == 31);
    assert(a[7] == 37);
    assert(a[8] == 41);
    assert(a[9] == 43);
}
```

### Was ist die Signatur von `qsort`?

```c
void qsort(void*    firstElement,
           unsigned numberOfElements,
           unsigned bytesPerElement,
           int   (* compare)(const void*, const void*))
```

### Was bedeutet `void* firstElement`?

- Ein `void*` ist eine rohe Speicheradresse ohne weitere Typinformation,
wie die Bytes beginnend bei dieser Speicheradresse zu interpretieren sind
- Ein `void*` kann mit jedem getypten Zeiger (z.B. `double*`) initialisiert werden,
die zusätzliche Typinformation (`double`) geht dabei verloren
- Für `qsort` ist das notwendig/nützlich, um Arrays *beliebiger* Elementtypen sortieren zu können

### Welchen Sinn hat `int (* compare)(const void*, const void*)`?

- Damit vergleicht `qsort` 2 Elemente
- Die Bedeutung des Ergebnis-`int` kennen wir bereits von `strcmp`:
  - *irgendein* negativer Wert, falls das erste Element vor das zweite gehört
  - *irgendein* positiver Wert, falls das zweite Element vor das erste gehört
  - 0, falls beide Elemente im Sinne der Sortierreihenfolge äquivalent sind
- In konkreten Vergleichsfunktionen müssen die beiden `const void*`
wieder in Zeiger auf die tatsächlichen Elemente zurückkonvertiert werden,
um die Elemente miteinander vergleichen zu können

### Warum ist `(* compare)` eingeklammert?

- `int (* compare)(const void*, const void*)` ist ein *Zeiger* auf eine Funktion, die einen `int` liefert
- `int* compare(const void*, const void*)` wäre eine *Funktion*, die einen Zeiger auf einen `int` liefert

### Warum `const void*` und nicht einfach `void*`?

- Der reine *Vergleich* zweier Elemente muss die Elemente nur lesen, nicht verändern
- Je nach *Ergebnis* des Vergleichs wird `qsort` die Elemente anschließend vertauschen

### Welches Sortierverfahren benutzt `qsort`?

- Traditionell wurde `qsort` mit Quicksort implementiert (daher das `q` im Namen)
- Alternativ wird gerne eine Kombination aus Quicksort und Insertionsort verwendet
- In Skorbut ist `qsort` der Nachvollziehbarkeit halber mit Selectionsort implementiert
