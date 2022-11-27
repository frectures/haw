# Woche 9

📺 C Zeiger zum Zugriff auf Argumente des Aufrufers: https://www.youtube.com/watch?v=AgDmdlfKuKI

## Aufgaben

### Aufgabe 9.0 Vertauschen (abnahmepflichtig & klausurrelevant)

Erkläre deinem Betreuer alle 6 kommentierten Zeilen:

```c
void swap(int* p, int* q) // 1
{
    int z;                // 2

    z  = *p;              // 3
    *p = *q;              // 4
    *q = z;               // 5
}

void swap_test()
{
    int a = 2;
    int b = 1;

    swap(&a, &b);         // 6

    assert(a == 1);
    assert(b == 2);
}
```

### Aufgabe 9.1 Sortieren (abnahmepflichtig & klausurrelevant)

Implementiere die Funktion `sort2`:

```c
void sort2(int* p, int* q)
{
    // ...
}

void sort2_permutation_test(int a, int b)
{
    sort2(&a, &b);

    assert(a == 1);
    assert(b == 2);
}

void sort2_test()
{
    sort2_permutation_test(1, 2);
    sort2_permutation_test(2, 1);
}
```

### Aufgabe 9.2 Sortieren (abnahmepflichtig & klausurrelevant)

Implementiere die Funktion `sort3`:

```c
void sort3(int* p, int* q, int* r)
{
    // ...
}

void sort3_permutation_test(int a, int b, int c)
{
    sort3(&a, &b, &c);

    assert(a == 1);
    assert(b == 2);
    assert(c == 3);
}

void sort3_test()
{
    sort3_permutation_test(1, 2, 3);
    sort3_permutation_test(1, 3, 2);
    sort3_permutation_test(2, 1, 3);
    sort3_permutation_test(2, 3, 1);
    sort3_permutation_test(3, 1, 2);
    sort3_permutation_test(3, 2, 1);
}
```

### Aufgabe 9.3 Ungültige Operatoren (klausurrelevant)

In Aufgabe 5.2 haben wir eine Funktion `ausrechnen` extrahiert:

```c
double ausrechnen(double links, char operator, double rechts)
```

Diese Funktion konnte bisher nicht sinnvoll auf ungültige Operatoren reagieren,
weil wir den Fehlerfall nicht in einem speziellen Rückgabewert wie `-1` kodieren konnten;
bei einer mathematischen Operation kann *jeder* `double` herauskommen!

Deshalb wollen wir die Funktion so umbauen,
dass sie statt dem mathematischen Ergebnis einen Wahrheitswert zurückliefert,
der Auskunft darüber gibt, ob der Operator einer der 4 gültigen ist.
Falls ja, speichert sie das mathematische Ergebnis über einen zusätzlichen Parameter:

```c
bool ausrechnen(double links, char operator, double rechts, double* result)
{                                                          ///////////////
    // ...
}

void ausrechnen_test()
{
    double ergebnis;

    // Gültige Operatoren

    assert(ausrechnen(1.5, '+', 2.5, &ergebnis) == true);
    assert(ergebnis ==  4);

    assert(ausrechnen(10 , '-', 1  , &ergebnis) == true);
    assert(ergebnis ==  9);

    assert(ausrechnen( 6 , '*', 7  , &ergebnis) == true);
    assert(ergebnis == 42);

    assert(ausrechnen(22 , '/', 7  , &ergebnis) == true);
    assert(ergebnis ==  3.142857142857143);

    // Ungültige Operatoren

    assert(ausrechnen(42 , '%', 6  , &ergebnis) == false);
    assert(ergebnis ==  3.142857142857143); // unangetastet

    assert(ausrechnen( 2 , '^', 8  , &ergebnis) == false);
    assert(ergebnis ==  3.142857142857143); // unangetastet
}
```

### Aufgabe 9.4 Quadratische Gleichungen (klausurrelevant)

In Aufgabe 3.4 haben wir die Anzahl Lösungen einer quadratische Gleichungen bestimmt.
Die Lösungen selber haben wir nicht berechnet, weil wir noch nicht wussten,
wie man zusätzliche Ergebnisse (bis zu 2 Nullstellen) aus einer Funktion zurückliefern kann.

Implementiere die Funktion `loeseQuadratischeGleichung`.
Ihr `int`-Ergebnis ist die Anzahl der Nullstellen (0, 1 oder 2).
Die Nullstellen selber werden indirekt befüllt
über `x1` (falls mindestens 1 Nullstelle) und `x2` (falls 2 Nullstellen).

Zum Wurzelziehen kannst du heute einfach `pow(radikand, 0.5)` verwenden.
Allgemein berechnet `pow(basis, exponent)` nämlich: basis<sup>exponent</sup>

```c
int loeseQuadratischeGleichung(double a, double b, double c, double* x1, double* x2)
{                                                           ///////////////////////
    double p = b / a;
    double q = c / a;
    // ... https://de.wikipedia.org/wiki/Quadratische_Gleichung#L%C3%B6sungsformel_f%C3%BCr_die_Normalform_(p-q-Formel)
}

void loeseQuadratischeGleichung_test()
{
    double erste  = 123;
    double zweite = 123;

    assert(loeseQuadratischeGleichung(2, 3, 5, &erste, &zweite) == 0);
    assert(erste  == 123); // unangetastet
    assert(zweite == 123); // unangetastet

    assert(loeseQuadratischeGleichung(1, 0, 0, &erste, &zweite) == 1);
    assert(erste  == 0.0);
    assert(zweite == 123); // unangetastet

    assert(loeseQuadratischeGleichung(2, 3, -5, &erste, &zweite) == 2);
    assert(erste  == 1.0);
    assert(zweite == -2.5);
}
```

## FAQ

### Was sind *Wertparameter*?

Beim Aufruf einer Funktionen wird ein Argument in den entsprechenden Parameter kopiert:

```c
void negiere(int x)
{
    x = -x; // negiert Parameter x, aber nicht Argument a
}

void negiere_test()
{
    int a = 42;
    negiere(a); // kopiere a nach x
    assert(a == 42);
}
```

Änderungen eines Parameters wie `parameter = neuerWert;` ändern niemals das Argument:

```
  +-----+
x | -42 |
  +-----+

  +-----+
a |  42 |
  +-----+
```

**Alle Parameter in C sind Wertparameter.**

### Was sind *Referenzparameter*?

Innerhalb einer Funktion sind Parameter und Argument dieselbe Variable.
Manche Programmiersprachen unterstützen Referenzparameter,
Microsoft C# zum Beispiel mit dem Schlüsselwort `ref`.
**In C gibt es keine Referenzparameter**, aber man kann sie mit Zeigern simulieren:

```c
void negiere(int* p) // p ist ein Zeiger auf eine int-Variable
{
    *p = -*p; // a = -a;
}

void negiere_test()
{
    int a = 42;
    negiere(&a); // p ist &a, *p ist a
    assert(a == -42);
}
```

Hier wird der Zeiger `&a` in den Wertparameter `p` kopiert.
Da `p` somit auf `a` zeigt, wirken sich Änderungen von `*p` auf `a` aus.
Mit anderen Worten: `a` und `*p` sind *dieselbe* Variable:

```
  +-----+
p | &a  |
  +--|--+
     v
  +-----+
a | -42 | *p
  +-----+
```

Änderungen des Parameters `p` selber (`p = ...`) wären für den Aufrufer aber nach wie vor unbemerkbar.

### Was bedeutet das Sternchen?

In Deklarationen hat das Sternchen eine andere Bedeutung als in Rechnungen:

- `int* p;`
  - Deklaration
  - `p` soll ein Zeiger sein, der auf `int`-Variablen zeigen kann
- `*p = -*p`
  - Dereferenzierung
  - Schreibe in die gezeigte Variable ihren negierten Wert rein

### Was bedeutet das Brezel?

Der Ausdruck `&a` ist ein Zeiger auf die Variable `a`.
Im Gegensatz zum Sternchen taucht das Brezel *nicht* in Deklaration auf.

In Woche 5 ist uns das Brezel zum ersten Mal begegnet:

```c
double a;
scanf("%lf", &a);
```

Hier übergeben wir mit `&a` einen Zeiger auf `a` an `scanf`,
damit `scanf` indirekten Zugriff auf die Variable `a` hat.
Ohne das Brezel würden wir den aktuellen Wert von `a` übergeben,
aber `scanf` interessiert sich gar nicht für den aktuellen Wert von `a`,
und außerdem steht in `a` auch noch gar kein sinnvoller Wert drin.

### Braucht man zum Negieren unbedingt Zeiger?

Nein, dafür ist eine Funktion mit Ergebnis eigentlich sinnvoller:

```c
int negiere(int x)
{
    return -x;
}

void negiere_test()
{
    int a = 42;
    int b = negiere(a);

    assert(a ==  42);
    assert(b == -42);
}
```

### Was ist ein sinnvolles Minimal-Beispiel für Zeiger?

Eine Funktion zum Vertauschen zweier Variablen geht nicht ohne Zeiger:

```c
void swap_fail(int x, int y)
{
    int z;

    z = x;
    x = y; // ändert Parameter x, aber nicht Argument a
    y = z; // ändert Parameter y, aber nicht Argument b
}

void swap_fail_test()
{
    int a = 2;
    int b = 1;

    swap_fail(a, b);

    assert(a == 2);
    assert(b == 1);
}


void swap(int* p, int* q)
{
    int z;

    z  = *p;
    *p = *q;
    *q = z;
}

void swap_test()
{
    int a = 2;
    int b = 1;

    swap(&a, &b);

    assert(a == 1);
    assert(b == 2);
}
```
