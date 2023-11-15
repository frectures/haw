# Woche 9

## Spickzettel

<table>
<tr>
<th>Programm</th>
<th>Arbeitsspeicher</th>
</tr>
<tr>
<td>

```c
int i;

int* p = &i;

*p = 123;

assert(i == 123);
```

</td>
<td>

```
  +-----+
i | 123 | *p
  +-----+
     ^
  +--|--+
p |  &i |
  +-----+
```

</td>
</tr>
</table>

| Typ    | Wertebereich                                            |
| ------ | ------------------------------------------------------- |
| `int`  | alle ganzen Zahlen zwischen -2147483648 und +2147483647 |
| `int*` | die (möglichen) Speicheradressen aller `int`-Variablen  |

## Kommunikation

| Schnipsel | Aussprache        | Erläuterung                                          |
| --------- | ----------------- | ---------------------------------------------------- |
| `int* p`  | int Zeiger `p`    | `p` ist eine Variable vom Typ: Zeiger auf int        |
| `&i`      | Adresse von `i`   | ¹ Zeiger auf die Variable `i`                        |
| `p = &i`  | `p` zeigt auf `i` | Zeiger auf `i` wird in der Variable `p` gespeichert  |
| `*p`      | (ver)folge `p`    | ² die Variable, auf die `p` zeigt                    |
| `*p`      | `i`               | sofern `p` zum Kommunikationszeitpunkt auf `i` zeigt |

> ¹ ANSI C89 §3.3.3.2 Address and indirection operators
>
> The result of the unary `&` (*address-of*) operator **is a pointer**
> to the variable designated by its operand.  
> If the operand has type “type”, the result has type “**pointer to type**”.

² Bitte `*p` *nicht* als “Zeiger p” aussprechen:
- `p` ist bereits ein Zeiger, nämlich ein `int*`
- `*p` ist *kein* Zeiger, sondern ein `int`, hier `i`

## Aufgaben

### Aufgabe 9.0 Vertauschen (abnahmepflichtig & klausurrelevant)

Erkläre deinem Betreuer anhand obiger Kommunikationstabelle die 6 kommentierten Zeilen:

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

### Aufgabe 9.1 Pärchen sortieren (abnahmepflichtig & klausurrelevant)

Implementiere die Funktion `sort2` zum aufsteigenden Sortieren der übergebenen Variablen:

```c
void sort2(int* p, int* q)
{
    // ...
}

void sort2_permutation_test(int a, int b,  int x, int y)
{
    sort2(&a, &b);
    
    assert(a == x);
    assert(b == y);
}

void sort2_test()
{
    srand(time(0));
    
    int a = 10 + rand() % 80;
    int b = a+1+ rand() % 10;
    assert(a < b);
    
    sort2_permutation_test(a, b,  a, b);
    sort2_permutation_test(b, a,  a, b);
    
    sort2_permutation_test(a, a,  a, a);
}
```

### Aufgabe 9.2 Ungültige Operatoren (abnahmepflichtig & klausurrelevant)

In Aufgabe 5.2 hatten wir eine Funktion `ausrechnen` extrahiert:

```c
double ausrechnen(double links, char operator, double rechts)
```

Diese Funktion konnte bisher nicht sinnvoll auf ungültige Operatoren reagieren,
weil wir den Fehlerfall nicht in einem speziellen Ergebnis wie `-1` kodieren konnten;
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

### Aufgabe 9.3 Tripel sortieren (klausurrelevant)

Implementiere die Funktion `sort3` zum aufsteigenden Sortieren der übergebenen Variablen:

```c
void sort3(int* p, int* q, int* r)
{
    // ...
}

void sort3_permutation_test(int a, int b, int c,  int x, int y, int z)
{
    sort3(&a, &b, &c);
    
    assert(a == x);
    assert(b == y);
    assert(c == z);
}

void sort3_test()
{
    srand(time(0));
    
    int a = 10 + rand() % 80;
    int b = a+1+ rand() %  5;
    int c = b+1+ rand() %  5;
    assert(a < b && b < c);
    
    sort3_permutation_test(a, b, c,  a, b, c);
    sort3_permutation_test(a, c, b,  a, b, c);
    sort3_permutation_test(b, a, c,  a, b, c);
    sort3_permutation_test(b, c, a,  a, b, c);
    sort3_permutation_test(c, a, b,  a, b, c);
    sort3_permutation_test(c, b, a,  a, b, c);
    
    sort3_permutation_test(a, a, a,  a, a, a);
    
    sort3_permutation_test(a, a, b,  a, a, b);
    sort3_permutation_test(a, b, a,  a, a, b);
    sort3_permutation_test(b, a, a,  a, a, b);
    
    sort3_permutation_test(a, b, b,  a, b, b);
    sort3_permutation_test(b, a, b,  a, b, b);
    sort3_permutation_test(b, b, a,  a, b, b);
}
```

### Aufgabe 9.4 Quadratische Gleichungen (klausurrelevant)

In Aufgabe 3.4 hatten wir die *Anzahl Lösungen* einer quadratische Gleichungen bestimmt.
Die *Lösungen selber* hatten wir nicht berechnet, weil wir noch nicht wussten,
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

Beim Aufruf einer Funktionen wird ein Argument in den entsprechenden Wertparameter *kopiert*:

```c
void negiere(int x)
{
    x = -x; // negiert Parameter x, aber nicht Argument a
}

void negiere_test()
{
    int a = 42;
    negiere(a); // kopiert Argument a in den Parameter x
    assert(a == 42);
}
```

Änderungen eines Wertparameters wie `parameter = neuerWert;` ändern niemals das Argument:

```
  +-----+
x | -42 |
  +-----+

  +-----+
a |  42 |
  +-----+
```

Alle Parameter in C sind Wertparameter.

### Was sind *Referenzparameter*?

- Innerhalb einer Funktion sind Referenzparameter und Argument *dieselbe* Variable
- Manche Programmiersprachen unterstützen Referenzparameter
  - Microsoft C# zum Beispiel mit dem Schlüsselwort `ref`
- In C gibt es keine Referenzparameter
  - aber man kann sie mit Zeigern simulieren:

```c
void negiere(int* p)
{
    *p = -*p;    // a = -a;
}

void negiere_test()
{
    int a = 42;
    negiere(&a); // p = &a
    assert(a == -42);
}
```

`*p` ist `*&a` ist `a`, d.h. `*p` und `a` sind *dieselbe* Variable:

```
  +-----+
p |  &a |
  +--|--+
     v
  +-----+
a | -42 | *p
  +-----+
```

### Was bedeutet das Sternchen?

In Deklarationen hat das Sternchen eine andere Bedeutung als in Rechnungen:

- `int* p`
  - `p` ist eine Variable vom Typ: Zeiger auf int
- `*p = -*p`
  - Schreibe in die gezeigte Variable ihren negierten Wert rein

### Was bedeutet das Brezel?

Der Zeiger `&a` ¹ zeigt auf die Variable `a`.
Im Gegensatz zum Sternchen taucht das Brezel *nicht* in Deklaration auf.

> ¹ ANSI C89 §3.3.3.2 Address and indirection operators
>
> The result of the unary `&` (*address-of*) operator **is a pointer**
> to the variable designated by its operand.  
> If the operand has type “type”, the result has type “**pointer to type**”.

In Woche 5 war uns das Brezel zum ersten Mal begegnet:

```c
double a;
scanf("%lf", &a);
```

Hier übergeben wir mit `&a` einen Zeiger auf `a` an `scanf`,
damit `scanf` indirekten Zugriff auf die Variable `a` hat.
Ohne das Brezel würden wir den aktuellen *Wert* von `a` übergeben,
aber `scanf` interessiert sich gar nicht für den aktuellen Wert von `a`,
und außerdem steht in `a` auch noch gar kein Wert drin.

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
