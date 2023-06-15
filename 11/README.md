# Woche 11

## Aufgaben

### Aufgabe 11.0 Formelrechner (abnahmepflichtig & klausurrelevant)

```c
double strichrechnen(); // + -
double punktrechnen();  // *

double zahl_oder_klammern();
double zahl();          // 7
double klammern();      // ( ... )

const char* p;

double ausrechnen(const char* formel)
{
    p = formel;
    double ergebnis = strichrechnen();
    if (*p == '\0') return ergebnis;
}

void ausrechnen_test()
{
    assert(ausrechnen("1") == 1);
    assert(ausrechnen("1+2") == 3);
    assert(ausrechnen("1+2+3") == 6);
    assert(ausrechnen("3-2-1") == 0);
    assert(ausrechnen("2*3") == 6);
    assert(ausrechnen("2*3*7") == 42);
    assert(ausrechnen("2*3+4") == 10);
    assert(ausrechnen("2+3*4") == 14);
    assert(ausrechnen("2*3+4*5") == 26);
    assert(ausrechnen("2*(3+4)*5") == 70);
    assert(ausrechnen("2+3*4+5") == 19);
    assert(ausrechnen("(2+3)*(4+5)") == 45);
}

double strichrechnen()
{
    double ergebnis = punktrechnen();
    for (;;)
    {
        switch (*p)
        {
            case '+':
            ++p;
            ergebnis = ergebnis + punktrechnen();
            break;
            
            case '-':
            ++p;
            ergebnis = ergebnis - punktrechnen();
            break;
            
            default:
            return ergebnis;
        }
    }
}

double punktrechnen()
{
    double ergebnis = zahl_oder_klammern();
    while (*p == '*')
    {
        ++p;
        ergebnis = ergebnis * zahl_oder_klammern();
    }
    return ergebnis;
}

double zahl_oder_klammern()
{
    switch (*p)
    {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        return zahl();
        
        case '(':
        return klammern();
    }
}

double zahl()
{
    return *p++ - '0';
}

double klammern()
{
    ++p;
    double ergebnis = strichrechnen();
    if (*p == ')')
    {
        ++p;
        return ergebnis;
    }
}


void getline(char* buffer, int size)
{
    char* last = buffer + (size - 1);
    char x;
    while (buffer < last && (x = getchar()) != '\n')
    {
        *buffer++ = x;
    }
    *buffer = '\0';
}

void formelrechner()
{
    // Definiere eine Variable für die Eingabezeile
    // Endlosschleife:
    //     Fordere den Benutzer zur Eingabe auf
    //     Lies eine Zeile vom Benutzer ein
    //     Rechne die eingegebene Formel aus
    //     Schreibe das ausgerechnete Ergebnis auf die Konsole
}
```

Implementiere obige Funktion `formelrechner` gemäß der enthaltenen Kommentare:

```
? 2+3
5.000000

? 2*3
6.000000

? (2+3)*(4+5)
45.000000

?
```

(Die Formeln hinter den Fragezeichen `?` sind Tastatur-Eingaben des Benutzers.)

### Aufgabe 11.1 Leertasten entfernen (abnahmepflichtig & klausurrelevant)

Implementiere die Funktion `entferneLeertasten` zum Entfernen von Leertasten:

```c
void entferneLeertasten(char* s)
{
    // ...
}

void entferneLeertasten_test()
{
    char fox[] = "The quick   brown  fox";
    entferneLeertasten(fox);
    assert(strcmp(fox, "Thequickbrownfox") == 0);
    
    char dog[] = "   jumps over  the lazy dog   ";
    entferneLeertasten(dog);
    assert(strcmp(dog, "jumpsoverthelazydog") == 0);
}
```

Rufe `entferneLeertasten` in `formelrechner` auf, damit der Benutzer auch Leertasten eingeben darf:

```
? 2 + 3
5.000000

? 2 * 3
6.000000

? (2 + 3) * (4 + 5)
45.000000

?
```

**SPOILER** Folgendes Gerüst hat sich in der Vergangenheit als hilfreich erwiesen:

```c
ibvq ragsrearYrregnfgra(pune* fpuervore)
{
    sbe (pbafg pune* yrfre = fpuervore; *yrfre; ++yrfre)
    {
        // ...
    }
}
```

### Aufgabe 11.2 Division (abnahmepflichtig & klausurrelevant)

Baue Division als zusätzlichen Operator ein:

```c
    assert(ausrechnen("1/2+3") == 3.5);
    assert(ausrechnen("2+3/4") == 2.75);
```

Soll Division stärker binden als Multiplikation oder gleich stark,
d.h. soll `2*3/4*5` als `(2*3)/(4*5)` interpretiert werden oder als `((2*3)/4)*5` ?

### Aufgabe 11.3 Mehrstellige Zahlen (klausurrelevant)

Baue die Funktion `zahl` so um, dass auch mehrstellige Zahlen wie `12345` funktionieren:

```c
    assert(ausrechnen("12345") == 12345);
    assert(ausrechnen("123+45") == 168);
    assert(ausrechnen("12*34") == 408);
```

**Tipp:** `12345 = ((((1) * 10 + 2) * 10 + 3) * 10 + 4) * 10 + 5`

### Aufgabe 11.4 Negation (klausurrelevant)

Baue Negation als zusätzlichen Operator ein:

```c
    assert(ausrechnen("-3") == -3);
    assert(ausrechnen("-(1+2)") == -3);
    assert(ausrechnen("-1+-2") == -3);
```

## FAQ

### Was bedeutet `for (;;)` ?

Alle drei Bestandteile des `for`-Schleifenkopfs sind optional:

```c
for (Initialisieren; Schleifenbedingung; Zählen)
```

Wenn die Schleifenbedingung fehlt, ist sie *wahr*, d.h. `for (;;)` ist eine Endlosschleife.

### Wie unterscheiden sich `++p` (*Präfix*) und `p++` (*Postfix*)?

Das wurde bereits in Woche 4 besprochen, hier nochmal eine alternative Sichtweise:

- Im Arbeitsspeicher haben `++p` und `p++` dieselbe *Wirkung*:
  - Beide erhöhen `p` um 1
- Aber das *Ergebnis* (im Kontext einer größeren Rechnung, zum Beispiel `*p++`) ist unterschiedlich:
  - `++p` hat den *neuen* Wert von `p`
  - `p++` hat den *alten* Wert von `p`

> ISO C90 §3.3.3.1 Prefix increment
>
> - The value of the operand of the prefix `++` operator is incremented
> - The result is the new value of the operand after incrementation

> ISO C90 §3.3.2.4 Postfix increment
>
> - The result of the postfix `++` operator is the value of the operand
> - After the result is obtained, the value of the operand is incremented

### Und was bedeutet `*p++` dann konkret?

- Das *Ergebnis* von `*p++` ist die gezeigte Variable `*p`
- Die anschließende *Wirkung* ist die Erhöhung von `p` um 1

### Wie würde man `zahl` und `getline` ohne Postfix-Inkrement implementieren?

```c
double zahl()
{
    // mit
    return *p++ - '0';
    
    // ohne
    int ergebnis = *p - '0';
    p += 1;
    return ergebnis;
}


void getline(char* buffer, int size)
{
    // ...
        // mit
        *buffer++ = x;
        
        // ohne
        *buffer = x;
        buffer += 1;
    // ...
}
```

### Was bedeutet `double funktion();` ohne Rumpf?

Die Funktion wird nur *deklariert* aber nicht *definiert*.
Eine passende Definition muss weiter unten im Programm erfolgen.

### Wann braucht man Funktions-Deklarationen?

Normalerweise kann man nur Funktionen aufrufen, die oberhalb der Aufrufstelle definiert sind:

```c
void f()
{
    //...
    g(); // error: must declare function before use
}

void g()
{
    //...
}
```

Mit einer Funktions-Deklaration kann man diese Beschränkung aufheben:

```c
void g(); //////
             //
void f()    //
{          //
    //... //
    g(); // okay
}

void g()
{
    //...
}
```

### Kann man Funktions-Deklarationen durch geeignete Sortierung der Funktions-Definitionen umgehen?

Offenbar funktioniert das normalerweise, denn bisher haben wir Funktions-Deklarationen ja nie benötigt:

```c
void g() //////////
{               //
    //...      //
}             //
             //
void f()    //
{          //
    //... //
    g(); // okay
}
```

### Wann ist eine Funktions-Deklaration zwingend erforderlich?

Wenn mehrere Funktionen sich gegenseitig aufrufen:

```c
void g(); //////
             //
void f() // // /////
{          //    //
    //... //    //
    g(); //    //
}             //
             //
void g()    //
{          //
    //... //
    f(); //
}
```

### Sind Funktions-Deklarationen nur ein Notbehelf für solche Reihenfolge-Probleme?

Nein. Manche Programmierer finden es zum Beispiel grundsätzlich übersichtlicher,
erst alle Funktion zu deklarieren und dann alle Funktionen zu definieren.

Außerdem sind Funktions-Deklarationen spätestens dann unerlässlich,
wenn man große Programme auf mehrere Dateien aufteilt (Stichwort: *Header-Dateien*),
aber das wird im Rahmen von PR1 nicht behandelt.
