# Woche 9

## Aufgaben

### Aufgabe 9.0 Vertauschen (Pflicht)

Erkläre deinem Betreuer die `swap`-Funktion am Ende der FAQ.

### Aufgabe 9.1 Sortieren (Pflicht)

Implementiere die Funktion `sort2`:

```c
void sort2(int *p, int *q)
{
    // ...
}

void test_sort2_permutation(int i, int j)
{
    sort2(&i, &j);

    assert(i == 1);
    assert(j == 2);
}

void test_sort2()
{
    test_sort2_permutation(1, 2);
    test_sort2_permutation(2, 1);
}
```

### Aufgabe 9.2 Sortieren (Pflicht)

Implementiere die Funktion `sort3`:

```c
void sort3(int *p, int *q, int *r)
{
    // ...
}

void test_sort3_permutation(int i, int j, int k)
{
    sort3(&i, &j, &k);

    assert(i == 1);
    assert(j == 2);
    assert(k == 3);
}

void test_sort3()
{
    test_sort3_permutation(1, 2, 3);
    test_sort3_permutation(1, 3, 2);
    test_sort3_permutation(2, 1, 3);
    test_sort3_permutation(2, 3, 1);
    test_sort3_permutation(3, 1, 2);
    test_sort3_permutation(3, 2, 1);
}
```

### Aufgabe 9.3 Datum komprimieren (Kür)

Wenn man eine Große Menge von "Datümern" (Plural von Datum) möglichst platzsparend repräsentieren möchte,
bietet sich z.B. folgendes 16-Bit-Format an:

```
yyyyyyyMMMMddddd
```

- 7 Bits für das Jahr ab 1900 (0..127)
- 4 Bits für den Monat (1..12)
- 5 Bits für den Tag (1..31)

`1010110010011010` repräsentiert z.B. den 26. April 1986:

- `1010110` = 86
- `0100` = 4
- `11010` = 26

Manche der möglichen Bitkombinationen sind sinnlose Datümer;
zum Beispiel repräsentiert `1000000111100000` den 00.15.1964,
aber darum kümmern wir uns heute nicht.

Die Funktion `encodeDate` konvertiert Jahr, Monat und Tag in dieses platzsparende Format.
Implementiere die Funktion `decodeDate` für den umgekehrten Weg:

```c
typedef unsigned short yyyyyyyMMMMddddd;

yyyyyyyMMMMddddd encodeDate(int year, int month, int day)
{
    return (year - 1900) << 9 | month << 5 | day;
}

void decodeDate(yyyyyyyMMMMddddd date, int *year, int *month, int *day)
{
    // ...
}

void aufgabe_9_3()
{
    yyyyyyyMMMMddddd chernobyl = encodeDate(1986, 4, 26);
    
    int year;
    int month;
    int day;
    decodeDate(chernobyl, &year, &month, &day);
    
    assert(year == 1986);
    assert(month == 4);
    assert(day == 26);
}
```

## Aufgabe 9.4 Quadratische Gleichungen (Kür)

In Aufgabe 3.4 haben wir bereits quadratische Gleichungen gelöst.
Heute wollen wir die Berechnung in eine eigene Funktion auslagern,
um sie von der Benutzer-Interaktion (`printf` und `scanf`) zu trennen.
Dies ermöglicht das automatisierte Testen der Berechnung mittels `assert`.

Implementiere die Funktion `loeseQuadratischeGleichung`.
Ihr `int`-Ergebnis ist die Anzahl der Nullstellen (0, 1 oder 2).
Die Nullstellen selber werden indirekt befüllt
über `px1` (falls mindestens 1 Nullstelle) und `px2` (falls 2 Nullstellen).

Zum Wurzelziehen kannst du heute einfach `pow(x, 0.5)` verwenden.

```c
int loeseQuadratischeGleichung(double a, double b, double c,
                               double *px1, double *px2)
{
    double p = b / a;
    double q = c / a;
    // ... https://de.wikipedia.org/wiki/Quadratische_Gleichung#L%C3%B6sungsformel_f%C3%BCr_die_Normalform_(p-q-Formel)
}

void aufgabe_9_4()
{
    double x1 = 123;
    double x2 = 123;
    
    assert(0 == loeseQuadratischeGleichung(2, 3, 5, &x1, &x2));
    assert(x1 == 123); // unangetastet
    assert(x2 == 123); // unangetastet
    
    assert(1 == loeseQuadratischeGleichung(1, 0, 0, &x1, &x2));
    assert(x1 == 0.0);
    assert(x2 == 123); // unangetastet
    
    assert(2 == loeseQuadratischeGleichung(2, 3, -5, &x1, &x2));
    assert(x1 == 1.0);
    assert(x2 == -2.5);
}
```

## FAQ

### Was sind *Wertparameter*?

Beim Aufruf einer Funktionen wird ein Argument in den entsprechenden Parameter kopiert:

```c
void negiere(int x)
{
    x = -x; // negiert Parameter x, aber nicht Argument i
}

void test_negiere()
{
    int i = 42;
    negiere(i); // kopiere i nach x
    assert(i == 42);
}
```

Änderungen eines Parameters wie `parameter = neuerWert;` ändern niemals das Argument:

```
  +-----+
i |  42 |
  +-----+

  +-----+
x | -42 |
  +-----+
```

**Alle Parameter in C sind Wertparameter.**

### Was sind *Referenzparameter*?

Innerhalb einer Funktion sind Parameter und Argument dieselbe Variable.
C# unterstützt Referenzparameter z.B. über das Schlüsselwort `ref`.
**In C gibt es keine Referenzparameter**, aber man kann sie mit Zeigern simulieren:

```c
void negiere(int *p) // p ist ein Zeiger auf eine int-Variable
{
    *p = -*p; // i = -i;
}

void test_negiere()
{
    int i = 42;
    negiere(&i); // p ist &i, *p ist i
    assert(i == -42);
}
```

Hier wird der Zeiger `&i` in den Wertparameter `p` kopiert.
Da `p` somit auf `i` zeigt, wirken sich Änderungen von `*p` auf `i` aus:

```
  +-----+
i | -42 | *p
  +-----+
     ^
  +--|--+
p | &i  |
  +-----+
```

Änderungen des Parameters `p` selber wären für den Aufrufer aber nach wie vor unbemerkbar.

### Was bedeutet das Sternchen?

In Deklarationen hat das Sternchen eine andere Bedeutung als in Rechnungen:

- `int *p;`
  - Deklaration
  - `p` soll ein Zeiger sein, der auf `int`-Variablen zeigen kann
- `*p = -*p`
  - Dereferenzierung
  - Schreibe in die gezeigte Variable ihren negierten Wert rein

C-Veteranen erklären sich die Syntax `int *p;` wie folgt:
nach der Deklaration `int *p;` ist der Ausdruck `*p` vom Typ `int`.

Dass die Deklaration einer Variable syntaktisch ihre spätere Verwendung widerspiegelt,
schätzt der Vater von C++ als gescheitertes Experiment ein:

> **Bjarne Stroustrup:** I consider the *C declarator syntax* an experiment that failed.
> Nevertheless, I adopted it for C++.
>
> The alternatives and improvements I considered at the time would not have improved matters.
> I rate it as a minor problem.

### Was bedeutet das Brezel?

Der Ausdruck `&i` ist ein Zeiger auf die Variable `i`.
Im Gegensatz zum Sternchen taucht das Brezel *nicht* in Deklaration auf.

In Woche 3 ist uns das Brezel zum ersten Mal begegnet:

```c
double a;
scanf("%lf", &a);
```

Hier übergeben wir mit `&a` einen Zeiger auf `a` an `scanf`,
damit `scanf` indirekten Zugriff auf die Variable `a` hat.
Ohne das Brezel würden wir den aktuellen Wert von `a` übergeben,
aber `scanf` interessiert sich gar nicht für den aktuellen Wert von `a`,
und außerdem steht in `a` auch noch gar kein sinnvoller Wert drin.

### Woran weist `int *p = &i;` zu?

An die neu deklarierte Variable `p`,
denn `int *p = &i;` ist nur eine kompakte Schreibweise für:

```c
int *p;
     p = &i;
```

Insbesondere weist `int *p = &i;` *nicht* an `*p` zu,
auch wenn das auf den ersten Blick so aussehen mag.
Das Typsystem würde das auch gar nicht erlauben,
denn `*p` ist ein `int`, während `&i` ein `int*` ist.

### Braucht man zum Negieren unbedingt Zeiger?

Nein, dafür ist eine Funktion mit Ergebnis eigentlich sinnvoller:

```c
int negiere(int x)
{
    return -x;
}

void test_negiere()
{
    int i = 42;
    int j = negiere(i);

    assert(i ==  42);
    assert(j == -42);
}
```

### Was ist ein sinnvolles Minimal-Beispiel für Zeiger?

Eine Funktion zum Vertauschen zweier Variablen geht nicht ohne Zeiger:

```c
void swap_fail(int x, int y)
{
    int z;

    z = x;
    x = y; // ändert Parameter x, aber nicht Argument i
    y = z; // ändert Parameter y, aber nicht Argument j
}

void test_swap_fail()
{
    int i = 2;
    int j = 1;

    swap_fail(i, j);

    assert(i == 2);
    assert(j == 1);
}


void swap(int *p, int *q)
{
    int z;

    z  = *p;
    *p = *q;
    *q = z;
}

void test_swap()
{
    int i = 2;
    int j = 1;

    swap(&i, &j);

    assert(i == 1);
    assert(j == 2);
}
```

### Das Sternchen in Deklarationen verwirrt mich?!

Wie wäre es mit einem neuen Namen für den Typ "Zeiger auf int"?

```c
typedef int *int_ptr;

void swap(int_ptr p, int_ptr q)
{
    int z;

    z  = *p;
    *p = *q;
    *q = z;
}
```
