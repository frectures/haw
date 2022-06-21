# Altklausur 2015

## Einordnung

### Klausurrelevante Themen

2015 gab es nur 5 C-Vorlesungen statt 10, daher fielen einige Themen unter den Tisch:
- Binär/Hexadezimal/Oktal
- Zeiger
- Sortieren
- Dynamische Arrays

Entsprechend findet man unten keine alten Aufgaben aus 2015 zu diesen Themen,
aber 2022 sind diese Themen definitiv klausurrelevant!

### Arten von Aufgaben

2015 gab es noch 3 Arten von Aufgaben:
1. Karel-Aufgaben
2. Text-Aufgaben
3. Programmier-Aufgaben in C

2022 gibt es nur noch Programmier-Aufgaben in C!

## Aufgaben

### Aufgabe A 2015

Schreiben Sie eine Funktion `void rotate_clockwise(int matrix[9])`,
welche eine 3x3 Matrix um 90 Grad im Uhrzeigersinn dreht:
```c
void rotateClockwise(int matrix[9])
{
    // ...
}

void rotateClockwise_test()
{
    int m[] = {
        90, 56, 27,
        89, 68, 98,
        17, 52, 22,
    };
    rotate_clockwise(m);

    assert(m[0] == 17);
    assert(m[1] == 89);
    assert(m[2] == 90);

    assert(m[3] == 52);
    assert(m[4] == 68);
    assert(m[5] == 56);

    assert(m[6] == 22);
    assert(m[7] == 98);
    assert(m[8] == 27);
}
```

### Aufgabe B 2015

Schreiben Sie eine Funktion `bool is_non_descending(int a[], int n)`.
Diese Funktion soll überprüfen, ob das übergebene Array `a` der Länge `n`
in nicht-absteigender Reihenfolge geordnet ist,
d.h. ob jede Zahl in dem Array mindestens so groß ist wie ihr linker Nachbar.

### Aufgabe C 2015

Header-Dateien der C-Standardbibliothek haben in C++ eine abweichende Namenskonvention:
``` 
"stdio.h"   // C   Norm: mit .h am Ende
"cstdio"    // C++ Norm: mit c am Anfang
```
Schreiben Sie eine Funktion `void convertHeaderName(char s[])`,
die Header-Datei-Namen der C-Norm in die entsprechende C++ Norm konvertiert:

```c
void convertHeaderName(char s[])
{
    // ...
}

void convertHeaderName_test()
{
    char a[] = "stdio.h";
    convertHeaderName(a);
    assert(strcmp(a, "cstdio") == 0);
}
```

### Aufgabe D 2015

Schreiben Sie eine Funktion `void count(char s[], int n[128])`,
welche die Häufigkeit der in der Zeichenkette `s` vorkommenden Buchstaben im Array `n` ablegt:

```c
void count(char s[], int n[128])
{
    // ...
}

void count_test()
{
    int vorkommen[128];
    count("erdbeere", vorkommen);
    assert(vorkommen['e'] == 4);
    assert(vorkommen['r'] == 2);
}
```

### Aufgabe E 2015

Schreiben Sie eine Funktion `bool anagrams(char a[], char b[])`.
Diese Funktion soll überprüfen, ob `a` ein Anagramm von `b` ist,
d.h. ob jeder Buchstabe genau so oft in `a` vorkommt wie in `b`.

Beispiele für Anagramme:
- atlas, salat
- eichel, leiche
- fernsehen, ehrensenf
- reifen, ferien
- schaden, schande
