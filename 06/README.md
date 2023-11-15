# Woche 6

## Aufgaben

### Aufgabe 6.0 Verschlüsseln (abnahmepflichtig & klausurrelevant)

```c
void verschluesseln(char s[])
{
    for (int i = 0; s[i]; ++i)
    {
        if ('a' <= s[i] && s[i] <= 'm')
        {
            s[i] += 13;   
        }
        else if ('n' <= s[i] && s[i] <= 'z')
        {
            s[i] -= 13;
        }
    }
}

void verschluesseln_test()
{
    char name[] = "Brian Kernighan";

    verschluesseln(name);
    assert(strcmp(name, "Bevna Kreavtuna") == 0);

    verschluesseln(name);
    assert(strcmp(name, "Brian Kernighan") == 0);
}
```

Diskutiere mit deinem Betreuer folgende Fragen:

1. Wann beendet die Schleifenbedingung `s[i]` die Schleife?
2. Warum ist das `else` vor dem zweiten `if` zwingend erforderlich?
3. Was bedeutet `strcmp(name, "Bevna Kreavtuna") == 0` ?
4. Warum wurden `B` und `K` nicht verschlüsselt?
5. Warum ist eine separate `entschluesseln`-Funktion überflüssig?

### Aufgabe 6.1 Zeichensuche (abnahmepflichtig & klausurrelevant)

Implementiere die Funktion `findeZeichen`,
welche die Position des ersten Vorkommens von `c` in `s` liefert:

```c
int findeZeichen(const char s[], char c)
{
    // ...
}

void findeZeichen_test()
{
    assert(findeZeichen("C++", 'C') == 0);
    assert(findeZeichen("Scheme", 'e') == 3);
    assert(findeZeichen("Clojure", 'e') == 6);
    assert(findeZeichen("Clojure", 's') == -1);
}
```

Implementiere die Funktion `zaehleZeichen`,
welche die Anzahl Vorkommen von `c` in `s` liefert:

```c
int zaehleZeichen(const char s[], char c)
{
    // ...
}

void zaehleZeichen_test()
{
    assert(zaehleZeichen("Ananas", 'a') == 2);
    assert(zaehleZeichen("Bahamas", 'a') == 3);
    assert(zaehleZeichen("das", 's') == 1);
    assert(zaehleZeichen("dass", 's') == 2);
    assert(zaehleZeichen("Xylophon", 'f') == 0);
    assert(zaehleZeichen("Zitrone", 'Z') == 1);
}
```

### Aufgabe 6.2 Sokoban (abnahmepflichtig & klausurrelevant)

Jetzt wollen wir einen rudimentären [Sokoban](https://de.wikipedia.org/wiki/Sokoban)-Klon verstehen,
der unsere Funktionen `findeZeichen` und `zaehleZeichen` benutzt, um den Spieler `@`
in einer [Sokoban-Levelnotation](https://de.wikipedia.org/wiki/Sokoban#Levelnotation)
zu finden, die Level-Breite zu bestimmen und die Kisten `$` zu zählen:

```
  ####
###  ####
#     $ #
# #  #$ #
# . .#@ #
#########
```

| Zeichen | Bedeutung |
| ------: | --------- |
| `#`     | Wand      |
| `@`     | Spieler   |
| `$`     | normale Kiste |
| `.`     | Ziel für Kiste |
| `*`     | Kiste auf Ziel |
| `+`     | Spieler auf Kistenziel |

```c
int tastenRichtung(char taste, int vertikal)
{
    switch (taste)
    {
        case 'w': return -vertikal;
        case 'a': return -1;
        case 's': return +vertikal;
        case 'd': return +1;

        default: return 0;
    }
}

const char  vorher2[] = "@ |@.|+.|+ |";
const char nachher2[] = " @| +|.+|.@|";

void sokoban()
{
    // Spielzustand initialisieren

    char spielfeld[] = "  ####   \n###  ####\n#     $ #\n# #  #$ #\n# . .#@ #\n#########\n";

    int breite = findeZeichen(spielfeld, '\n') + 1;
    int spieler = findeZeichen(spielfeld, '@');
    int kisten = zaehleZeichen(spielfeld, '$');

    // Spielschleife    
    while (kisten > 0)
    {
        // Ausgabe
        printf("%s\n", spielfeld);

        // Eingabe
        char eingabe;
        scanf(" %c", &eingabe);

        // Spielzustand verändern

        int richtung = tastenRichtung(eingabe, breite);
        int a = spieler;
        int b = a + richtung;
        int c = b + richtung;

        if (spielfeld[a] == '@' && spielfeld[b] == '$' && spielfeld[c] == ' ')
        {
            spielfeld[a] =  ' ';   spielfeld[b] =  '@';   spielfeld[c] =  '$';

            spieler += richtung;
        }

        for (int i = 0; vorher2[i]; i += 3)
        {
            if (spielfeld[a] == vorher2[i] && spielfeld[b] == vorher2[i+1])
            {
                spielfeld[a] = nachher2[i];   spielfeld[b] = nachher2[i+1];

                spieler += richtung;
                break;
            }
        }
    }
}
```

- Kopiere obigen Code, stelle die Geschwindigkeit auf 0 und starte die `sokoban`-Funktion
- Um das Spiel möglichst verzögerungsfrei zu spielen, klicke nach dem Start einmalig auf `step return (F7)`
- Studiere die `sokoban`-Funktion und mache dich ggf. mit den Regeln von Sokoban vertraut
- Erkläre deinem Betreuer anschließend den Sinn dieser beiden Strings:

```c
const char  vorher2[] = "@ |@.|+.|+ |";
const char nachher2[] = " @| +|.+|.@|";
```

(Der optisch hilfreiche Senkrechtstrich `|` *nach* jeder Regel wird vom Code übersprungen.)

### Aufgabe 6.3 Schiebung (klausurrelevant)

- Bisher kann man Kisten nur auf leere Positionen schieben
- Ermögliche auch das Schieben von Kisten auf Zielpositionen
- Weitere fehlende Fälle werden dir wahrscheinlich beim Spielen auffallen
- Tausche das vorgegebene Spielfeld gerne gegen ein komplexeres aus!
- Falls du einen `index out of bounds`-Fehler bekommst, hast du wahrscheinlich den Senkrechtstrich `|` *nach* der letzten Regel vergessen!

### Aufgabe 6.4 Geschafft (klausurrelevant)

- Beende das Spiel mit einer Beglückwünschung, sobald alle Kisten auf Zielpositionen liegen
- Fällt dir eine schnellere Lösung ein, als nach jedem Zug `zaehleZeichen` erneut aufzurufen?
  - Nach welchen Zügen sollte sich die Variable `kisten` jeweils um wieviel ändern?
- Eine kleine Statistik (benötigte Spielzüge und verbrauchte Spielzeit) wäre nett

## FAQ

### Was ist der ASCII-Code?

- ASCII steht für "American Standard Code for Information Interchange"
- ASCII legt für 128 Zeichen fest, wie diese als 7-Bit-Zahl repräsentiert werden
- 95 dieser Zeichen sind sichtbare Zeichen (inkl. Leerzeichen):

```
   32    0  48    @  64    P  80    `  96    p 112
!  33    1  49    A  65    Q  81    a  97    q 113
"  34    2  50    B  66    R  82    b  98    r 114
#  35    3  51    C  67    S  83    c  99    s 115
$  36    4  52    D  68    T  84    d 100    t 116
%  37    5  53    E  69    U  85    e 101    u 117
&  38    6  54    F  70    V  86    f 102    v 118
'  39    7  55    G  71    W  87    g 103    w 119
(  40    8  56    H  72    X  88    h 104    x 120
)  41    9  57    I  73    Y  89    i 105    y 121
*  42    :  58    J  74    Z  90    j 106    z 122
+  43    ;  59    K  75    [  91    k 107    { 123
,  44    <  60    L  76    \  92    l 108    | 124
-  45    =  61    M  77    ]  93    m 109    } 125
.  46    >  62    N  78    ^  94    n 110    ~ 126
/  47    ?  63    O  79    _  95    o 111
```

Ein Beispiel für ein *un*sichtbares Zeichen ist der Zeilenumbruch `'\n'` mit dem ASCII-Code 10:

```c
assert('\n' == 10);
```

### Was ist ein String?

- Ein String ist eine Kette von Zeichen, die hintereinander im Speicher liegen
- Das Ende eines Strings wird mit dem unsichtbaren Zeichen `'\0'` (NUL-Terminator, ASCII-Code 0) markiert
- Der NUL-Terminator `'\0'` ist in String-Literalen wie `"Brian"` bereits implizit enthalten

```c
void spielerei()
{
    //          012345
    char s[] = "switch";
    //                \0

    printf("%d Zeichen\n", strlen(s)); // 6 Zeichen

    printf("%c%c%c%c%c\n", s[3], s[2], s[0], s[4], s[5]); // tisch

    printf("Nintendo %s\n", s); // Nintendo switch

    s[0] += 1;
    printf("%s Streaming\n", s); // twitch Streaming

    s[4] = '\0';
    printf("%s\n", s); // twit
}
```

### Wie übergibt man einen String an eine *lesende* Funktion?

Mit `const char[]` als Parametertyp:

```c
char letztesZeichen(const char s[])
{
    int laenge = strlen(s);
    return s[laenge-1];
}

void letztesZeichen_test()
{
    assert(letztesZeichen("Wie geht's?") == '?');
    assert(letztesZeichen("Passt schon.") == '.');
}
```

- Strings werden beim Aufruf von Funktionen *nicht* kopiert
- `const char s[]` erlaubt der Funktion ausschließlich *lesenden* Zugriff auf den Original-String
- Konkret hat `const` 2 Vorteile:
  1. Der Aufrufer kann sich darauf verlassen, dass die Funktion den übergebenen String nicht verändert
  2. Beim Implementieren der Funktion werden uns *versehentliche* Änderungen sofort angekreidet

### Wie übergibt man einen String an eine (potenziell) *schreibende* Funktion?

Mit `char[]` ohne `const` als Parametertyp:

```c
void loescheLetztesZeichen(char s[])
{
    int laenge = strlen(s);
    s[laenge-1] = '\0';   // wäre mit  const char s[]  nicht erlaubt!
}

void loescheLetztesZeichen_test()
{
    char a[] = "Nanu?!";
    loescheLetztesZeichen(a);
    assert(strcmp(a, "Nanu?") == 0);

    char b[] = "Kein Satz.";
    loescheLetztesZeichen(b);
    assert(strcmp(b, "Kein Satz") == 0);
}
```

### Wie schleift man über alle Zeichen eines Strings?

- In Bedingungen wird der NUL-Terminator `'\0'` als *falsch* angesehen und alle anderen Zeichen als *wahr*
- Deshalb kann man beim Schleifen durch einen String das aktuelle Zeichen als Schleifenbedingung verwenden:

```c
void schleifeUeberAlleZeichen(const char s[])
{
    for (int i = 0; s[i]; ++i)
    {              ///// bricht die Schleife beim NUL-Terminator ab
        printf("Das Zeichen %c hat den ASCII-Code %d\n", s[i], s[i]);
    }
}
```

### Wie benutzt man Strings mit `scanf` und `printf`?

```c
void gruesseNutzer()
{
    printf("Name? ");

    char name[20];         // 20 inkl. NUL-Terminator
    scanf ( "%19s", name); // 19 exkl. NUL-Terminator

    printf("Hallo %s\n", name);
}
```

### Wie vergleicht man Strings?

```c
void strcmp_test()
{
    char frucht[] = "Apfel";

    assert(strcmp(frucht, "Banane") < 0); // Apfel < Banane
    assert(strcmp(frucht, "Ananas") > 0); // Apfel > Ananas
    assert(strcmp(frucht, "Apfel") == 0); // Apfel = Apfel
}
```

Die eingebaute Funktion `strcmp(s, t)` liefert:
- 0, falls in `s` genau die gleichen Zeichen hintereinander stehen wie in `t`
- *irgendeine* negative Zahl, falls `s` lexikographisch vor `t` liegt
- *irgendeine* positive Zahl, falls `s` lexikographisch nach `t` liegt

### Wie könnte man `strcmp` notfalls selber bauen?

```c
int strcmp(const char s[], const char t[])
{
    int i;
    for (i = 0; s[i] == t[i]; ++i) // gemeinsames Präfix überspringen
    {
        if (s[i] == '\0') return 0; // alle Zeichen gleich
    }
    return s[i] - t[i]; // erster Unterschied an Position i
}
```
