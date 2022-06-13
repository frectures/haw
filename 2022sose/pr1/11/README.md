# Woche 11

## Aufgaben

### Aufgabe 11.1 (Pflicht)

Hier sind zwei Funktionen zum Schreiben der Multiplikationstabelle und der Additionstabelle:

```c
void multiplicationTable(int n)
{
    for (int y = 1; y <= n; ++y)
    {
        for (int x = 1; x <= n; ++x)
        {
            printf("%4d", x * y);
        }
        putchar('\n');
    }
    putchar('\n');
}

void additionTable(int n)
{
    for (int y = 1; y <= n; ++y)
    {
        for (int x = 1; x <= n; ++x)
        {
            printf("%4d", x + y);
        }
        putchar('\n');
    }
    putchar('\n');
}

void aufgabe_11_1()
{
    multiplicationTable(10);
    additionTable(10);
}
```

Ersetzte `multiplicationTable` und `additionTable` durch eine einzige Funktion,
die Tabellen für *jede* mathematische Operation schreiben kann:

```c
void printTable(int n, int (*operation)(int, int))
{
    // ...
}

// ...

void aufgabe_11_1()
{
    printTable(10, /* ??? */); // Multiplikationstabelle
    printTable(10, /* ??? */); // Additionstabelle
}
```

### Aufgabe 11.2 (Pflicht)

In der FAQ wird ein `double`-Array mit `qsort` aufsteigend sortiert:

```c
int ascending(const void *v, const void *w)
{
    const double *p = v;
    const double *q = w;
    
    if (*p < *q) return -1;
    else return (*p > *q);
}

void qsort_ascending_test()
{
    double a[] = {19, 41, 23, 13, 11, 17, 37, 43, 31, 29};
    
    qsort(a, 10, sizeof(double), &ascending);
    
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

### Aufgabe 11.3 (Kür)

Sortiere ein String-Array mit `qsort` aufsteigend:

```c
typedef const char *string;

int string_compare(const void *v, const void *w)
{
    // ...
}

void aufgabe_11_3()
{
    string words[] = {
        "The", "only", "way", "to", "learn",
        "a", "new", "programming", "language",
        "is", "by", "writing", "programs", "in", "it",
    };
    qsort(words, 15, sizeof(string), &string_compare);
    for (int i = 0; i < 15; ++i)
    {
        puts(words[i]);
    }
}
```

### Aufgabe 11.4 (Kür)

Sortiere ein String-Array mit `qsort` ohne `typedef const char *string;`

## FAQ

### Wie funktioniert Insertionsort?

Angenommen, wir wollen folgende Zahlen aufsteigend sortieren:

```
19 41 23 13 11 17 37 43 31 29
```

Insertionsort schaut sich nacheinander Präfix-Listen der Länge 2 bis 10 an
und verschiebt die letzte Zahl (ganz rechts) an die richtige Stelle (nach links):

```
   __
19 41    nichts zu tun, da 41 >= 19
   ▔
      __
19 41 23
     \      23 < 41
19 23 41
   ▔
         __
19 23 41 13
  \  \  \      13 < 19
13 19 23 41
▔
            __
13 19 23 41 11
  \  \  \  \      11 < 13
11 13 19 23 41
▔
               __
11 13 19 23 41 17
        \  \  \     17 < 19
11 13 17 19 23 41
      ▔
                  __
11 13 17 19 23 41 37
                 \      37 < 41
11 13 17 19 23 37 41
               ▔
                     __
11 13 17 19 23 37 41 43    nichts zu tun, da 43 >= 41
                     ▔
                        __
11 13 17 19 23 37 41 43 31
                 \  \  \      31 < 37
11 13 17 19 23 31 37 41 43
               ▔
                           __
11 13 17 19 23 31 37 41 43 29
                 \  \  \  \      29 < 31
11 13 17 19 23 29 31 37 41 43
               ▔
```

### Wie implementiert man Insertionsort?

Es empfiehlt sich, das Verschieben der letzten Zahl in eine eigene Funktion auszulagern:

```c
/*
Moves the rightmost element *p into place

precondition:  a[0] .. p[-1] is sorted
postcondition: a[0] .. p[ 0] is sorted
*/
void insert(double *a, double *p)
{
    double elementToInsert = *p;
    while (a < p && elementToInsert < p[-1])
    {
        *p = p[-1];
        --p;
    }
    *p = elementToInsert;
}

void insert_test()
{
    double a[] = {11, 13,  19, 23, 41, 17};
    
    insert(a, a + 5);
    
    assert(a[0] == 11);
    assert(a[1] == 13);
    
    assert(a[2] == 17);
    assert(a[3] == 19);
    assert(a[4] == 23);
    assert(a[5] == 41);
}

void insertionsort(double a[], int size)
{
    for (int i = 1; i < size; ++i)
    {
        insert(a, a + i);
    }
}

void insertionsort_test()
{
    double a[] = {19, 41, 23, 13, 11, 17, 37, 43, 31, 29};
    
    insertionsort(a, 10);
    
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

### Wie dreht man die Sortierreihenfolge um?

Die Sortierreihenfolge ist aufgrund folgender Teilbedingung in der `while`-Schleife aufsteigend:

```c
elementToInsert < p[-1]
```

Für eine absteigende Sortierreihenfolge dreht man den Vergleich einfach um:

```c
elementToInsert > p[-1]
```

### Also muss man den kompletten Code kopieren, wenn man beide Sortierreihenfolgen braucht?

Nein, wir können die Vergleiche in Funktionen auslagern und über diese Funktionen abstrahieren:

```c
typedef enum { false, true } bool;

void insert(double *a, double *p, bool (*belongsLeft)(double, double))
{
    double elementToInsert = *p;
    while (a < p && belongsLeft(elementToInsert, p[-1]))
    {
        *p = p[-1];
        --p;
    }
    *p = elementToInsert;
}

void insertionsort(double a[], int size, bool (*belongsLeft)(double, double))
{
    for (int i = 1; i < size; ++i)
    {
        insert(a, a + i, belongsLeft);
    }
}

bool ascending(double x, double y)
{
    return x < y;
}

void insertionsort_ascending_test()
{
    double a[] = {19, 41, 23, 13, 11, 17, 37, 43, 31, 29};
    
    insertionsort(a, 10, &ascending);
    
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

bool descending(double x, double y)
{
    return x > y;
}

void insertionsort_descending_test()
{
    double a[] = {19, 41, 23, 13, 11, 17, 37, 43, 31, 29};
    
    insertionsort(a, 10, &descending);
    
    assert(a[0] == 43);
    assert(a[1] == 41);
    assert(a[2] == 37);
    assert(a[3] == 31);
    assert(a[4] == 29);
    assert(a[5] == 23);
    assert(a[6] == 19);
    assert(a[7] == 17);
    assert(a[8] == 13);
    assert(a[9] == 11);
}
```

### Was bedeutet `bool (*belongsLeft)(double, double)`?

- `belongsLeft` ist ein Zeiger auf eine Funktion, die zwei `double`s akzeptiert und einen `bool` liefert

### Wo ist der Funktionsrumpf von `belongsLeft`?

- `belongsLeft` ist keine Funktion und hat daher keinen Funktionsrumpf
- Die konkreten Rümpfe findest du in den typkompatiblen Funktionen `ascending` und `descending`,
welche mittels `&ascending` bzw. `&descending` an `insertionsort` übergeben werden

### Was ist der Unterschied zwischen `bool (*f)()` und `bool *g()`?

- `f` ist ein Zeiger auf eine Funktion, die keine Parameter akzeptiert und einen `bool` liefert
- `g` ist eine Funktion, die keine Parameter akzeptiert und einen Zeiger auf einen `bool` liefert

### Muss man für jeden Datentyp eine eigene Sortierfunktion schreiben?

Nein, in C gibt es bereits eine eingebaute Sortierfunktion namens `qsort` für alle Datentypen:

```c
qsort(void    *firstElement,
      unsigned numberOfElements,
      unsigned bytesPerElement,
      int    (*compare)(const void*, const void*))
```

Das folgende Beispiel sortiert ein `double`-Array aufsteigend:

```c
int ascending(const void *v, const void *w)
{
    const double *p = v;
    const double *q = w;
    
    if (*p < *q) return -1;
    else return (*p > *q);
}

void qsort_ascending_test()
{
    double a[] = {19, 41, 23, 13, 11, 17, 37, 43, 31, 29};
    
    qsort(a, 10, sizeof(double), &ascending);
    
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

### Was bedeutet `void *firstElement`?

- Ein `void*` ist eine rohe Speicheradresse ohne weitere Typinformation,
wie die Bytes beginnend bei dieser Speicheradresse zu interpretieren sind
- Ein `void*` kann mit jedem getypten Zeiger (z.B. `double*`) initialisiert werden,
die zusätzliche Typinformation (`double`) geht dabei verloren
- Für `qsort` ist das notwendig/nützlich, um Arrays beliebiger Datentypen sortieren zu können

### Welchen Sinn hat `int (*compare)(const void*, const void*)`?

- Damit vergleicht `qsort` 2 Elemente
- Die Bedeutung des Ergebnis-`int` kennen wir bereits von `strcmp`:
  - *irgendein* negativer Wert, falls das erste Element vor das zweite gehört
  - *irgendein* positiver Wert, falls das zweite Element vor das erste gehört
  - 0, falls beide Elemente im Sinne der Sortierreihenfolge als gleich angesehen werden
- In der konkreten Vergleichsfunktion müssen die beiden `const void*`
in Zeiger auf die tatsächlichen Elemente zurückkonvertiert werden,
um die Elemente miteinander vergleichen zu können.

### Warum `const void*` und nicht einfach `void*`?

- Der reine Vergleich zweier Elemente sollte die Elemente nicht verändern
- Je nach Ergebnis des Vergleichs wird `qsort` die Elemente anschließend verändern

### Welches Sortierverfahren benutzt `qsort`?

- Traditionell wurde `qsort` mit Quicksort implementiert (daher das `q` im Namen)
- Alternativ wird gerne eine Kombination aus Quicksort und Insertionsort verwendet
- In Skorbut ist `qsort` der Nachvollziehbarkeit halber mit Selectionsort implementiert
