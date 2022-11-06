# Woche 6

📺 Strings in 14 Minuten erklärt: https://www.youtube.com/watch?v=u3VnaChy2sY

## Aufgaben

### Aufgabe 6.1 Vokale (abnahmepflichtig & klausurrelevant)

Implementiere die Funktion `istVokal`, am einfachsten mit einem `switch`:

```c
typedef enum { false, true } bool;

bool istVokal(char zeichen)
{
    // ...
}

void istVokal_test()
{
    for (int i = 0; i < 10; ++i)
    {
        assert( istVokal("AEIOUaeiou"[i]));
    }
    for (int i = 0; i < 85; ++i)
    {
        assert(!istVokal(" !\"#$%&'()*+,-./0123456789:;<=>?@BCDFGHJKLMNPQRSTVWXYZ[\\]^_`bcdfghjklmnpqrstvwxyz{|}~"[i]));
    }   //                  ^^ Anführungszeichen                                  ^^ Backslash
}
```

Implementiere die Funktion `zaehleVokale`:

```c
int zaehleVokale(const char s[])
{
    // ...
}

void zaehleVokale_test()
{
    assert(zaehleVokale("Ananas") == 3);
    assert(zaehleVokale("Eimer") == 3);
    assert(zaehleVokale("Insel") == 2);
    assert(zaehleVokale("Oben") == 2);
    assert(zaehleVokale("Unten") == 2);
    assert(zaehleVokale("Polenta") == 3);
    assert(zaehleVokale("Schnee") == 2);
    assert(zaehleVokale("Veni Vidi Vici") == 6);
    assert(zaehleVokale("Pomodoro") == 4);
    assert(zaehleVokale("Kanu") == 2);
}
```

### Aufgabe 6.2 Datenschutz (abnahmepflichtig & klausurrelevant)

Implementiere die Funktion `zensiereZiffern`, die Ziffern durch Kreuze ersetzt:

```c
void zensiereZiffern(char s[])
{
    // ...
}

void zensiereZiffern_test()
{
    char a[] = "Meine PIN ist 1234, und meine Telefonnummer ist 0123 / 456 78 90";
    zensiereZiffern(a);
    assert(strcmp(a, "Meine PIN ist XXXX, und meine Telefonnummer ist XXXX / XXX XX XX") == 0);
}
```

### Aufgabe 6.3 Palindrom-Prüfer (klausurrelevant)

Die Funktion `istPalindrom` funktioniert bisher nur mit Strings der Länge 10,
weil die 5 Fallunterscheidungen mit den Zeichen an den Positionen von 0 bis 9 arbeiten:

```c
bool istPalindrom(const char s[])
{
    assert(strlen(s) == 10);

    if (s[0] != s[9]) return false;
    if (s[1] != s[8]) return false;
    if (s[2] != s[7]) return false;
    if (s[3] != s[6]) return false;
    if (s[4] != s[5]) return false;

    return true;
}

void istPalindrom_test()
{
    assert( istPalindrom("regallager"));
    assert(!istPalindrom("regallagen"));
    assert(!istPalindrom("regalnager"));
}
```

Ersetze zunächst die 5 `if`s durch 1 einziges `if` in einer `for`-Schleife, die 5 Mal schleift.
Wodurch müssen die konkreten Zahlenpaare in den 5 Bedingungen (`s[0] != s[9]` usw.) ersetzt werden?

Behebe anschließend die Einschränkung auf 10 Zeichen,
d.h. `istPalindrom` soll mit beliebig langen Strings zurechtkommen.
Denke dir weitere Testfälle mit anderen Längen als 10 aus!

### Aufgabe 6.4 Spiegeln (klausurrelevant)

Implementiere die Funktion `spiegele` zum Spiegeln eines Strings:

```c
void spiegele(char s[])
{
    // ...
}

void spiegele_test()
{
    char a[] = "regal";
    spiegele(a);
    assert(strcmp(a, "lager") == 0);
}
```

## FAQ

### Welchen Sinn hat `typedef enum { false, true } bool;`?

ANSI C89 bzw. ISO C90 hat keinen Datentyp für Wahrheitswerte.
Stattdessen wird die Zahl 0 als *falsch* interpretiert und alle anderen Zahlen als *wahr*:

```c
for (int i = -2; i <= 2; ++i)
{
    if (i)
    {
        printf("%d ist wahr\n", i);
        // -2 ist wahr
        // -1 ist wahr
        // 1 ist wahr
        // 2 ist wahr
    }
    else
    {
        printf("%d ist falsch\n", i);
        // 0 ist falsch
    }
}
```

Vergleichsoperatoren liefern immer 0 oder 1:

```c
assert((42 == 97) == 0);
assert((42 != 97) == 1);
```

Für die Lesbarkeit von Programmen sind Zahlen als Wahrheitswerte eher unschön:

```c
int istPrim(int zahl)
{
    if (zahl < 2)      return 0; // hier bedeutet 0 falsch
    if (zahl == 2)     return 1; // hier bedeutet 1 wahr
    if (zahl % 2 == 0) return 0; // hier bedeutet 0 falsch

    for (int teiler = 3; teiler * teiler <= zahl; teiler += 2)
    {
        if (zahl % teiler == 0) return 0; // hier bedeutet 0 falsch
    }
    return 1; // hier bedeutet 1 wahr
}
```

Wenn C89/C90 einen Datentyp für Wahrheitswerte hätte, könnte man stattdessen schreiben:

```c
bool istPrim(int zahl)
{
    if (zahl < 2)      return false;
    if (zahl == 2)     return true;
    if (zahl % 2 == 0) return false;
    
    for (int teiler = 3; teiler * teiler <= zahl; teiler += 2)
    {
        if (zahl % teiler == 0) return false;
    }
    return true;
}
```

Im Prinzip brauchen wir also nur folgende Abbildungen:

1. `bool` bedeutet `int`
2. `false` bedeutet `0`
3. `true` bedeutet `1`

Und genau das leistet `typedef enum { false, true } bool;` im Wesentlichen.

Die Bezeichnung `bool` (C99, C++, C#) bzw. `boolean` (Java, JavaScript) geht auf den englischen Mathematiker, Logiker und Philosophen *George Boole* (1815 - 1864) zurück.

![](Boole.jpg)

### Was ist der ASCII-Code?

ASCII steht für "American Standard Code for Information Interchange".
ASCII legt für 128 Zeichen fest, wie diese als 7-Bit-Zahl repräsentiert werden.
95 dieser Zeichen sind sichtbare Zeichen (inkl. Leerzeichen):

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

### Wo hast du diese Tabelle her?

Die kann man sich ganz einfach selber generieren:

```c
void asciiTable()
{
    for (int left = 32; left < 48; ++left)
    {
        for (int i = left; i < 127; i += 16)
        {
            printf("%c %3d    ", i, i);
        }
        printf("\n");
    }
}
```

### Was ist ein String?

Ein String ist eine Kette von Zeichen, die hintereinander im Speicher liegen.
Das Ende eines Strings wird mit dem speziellen Zeichen `'\0'` (NUL-Terminator, ASCII-Code 0) markiert:

    Position: 0 1 2 3 4 5
     Zeichen: H a l l o \0

Der NUL-Terminator `'\0'` ist in String-Literalen wie `"Hallo"` bereits implizit enthalten.

```c
void spielerei()
{
    //          012345
    char s[] = "switch";
    
    printf("%d Zeichen\n", strlen(s)); // 6 Zeichen
    
    printf("%c%c%c%c%c\n", s[3], s[2], s[0], s[4], s[5]); // tisch
    
    printf("Nintendo %s\n", s); // Nintendo switch
    
    s[0] += 1;
    printf("%s Streaming\n", s); // twitch Streaming
    
    s[4] = '\0';
    printf("%s\n", s); // twit
}
```

### Wie übergebe ich einen String an eine *lesende* Funktion?

Mit dem Parametertyp `const char[]`:

```c
bool istFrage(const char s[])
{
    int laenge = strlen(s);
    int letztePosition = laenge - 1;
    char letztesZeichen = s[letztePosition];
    return letztesZeichen == '?';
}

void istFrage_test()
{
    assert( istFrage("Wie geht's?"));
    assert(!istFrage("Passt schon."));
}
```

Dabei stellt das `const` in `const char s[]` sicher, dass die Funktion auf `s` nur lesend zugreift.
Strings werden beim Aufruf von Funktionen nämlich *nicht* kopiert,
sondern die aufgerufene Funktion hat Zugriff auf den Original-String des Aufrufers!

### Wie übergebe ich einen String an eine (potenziell) *schreibende* Funktion?

Mit dem Parametertyp `char[]`, ohne `const`:

```c
void betone(char s[])
{
    int letztePosition = strlen(s) - 1;
    if (s[letztePosition] == '.')
    {
        s[letztePosition] = '!'; // würde mit const char s[] nicht funktionieren
    }
}

void betone_test()
{
    char satz[] = "Auf geht's.";
    assert(satz[10] == '.');

    betone(satz);
    assert(satz[10] == '!');
}
```

### Wie schleife ich über alle Zeichen eines Strings?

In Bedingungen wird der NUL-Terminator `'\0'` als *falsch* angesehen und alle anderen Zeichen als *wahr*.
Deshalb kann man beim Schleifen durch einen String das aktuelle Zeichen als Schleifenbedingung verwenden:

```c
void schleifeUeberAlleZeichen(const char s[])
{
    for (int i = 0; s[i]; ++i)
    {              ///// bricht die Schleife beim NUL-Terminator ab
        printf("Das Zeichen %c hat den Wert %d\n", s[i], s[i]);
    }
}
```

### Warum ist von der Schleifenbedingung `i < strlen(s)` abzuraten?

Weil jeder Aufruf von `strlen(s)` erneut alle Zeichen anfassen muss, um den NUL-Terminator zu finden:

```c
void punktabzug(const char s[])
{
    for (int i = 0; i < strlen(s); ++i)
    {              ////////////// Punktabzug
        printf("Das Zeichen %c hat den Wert %d\n", s[i], s[i]);
    }
}

int strlen(const char s[])
{
    int i;
    for (i = 0; s[i]; ++i)
    {
    }
    return i; // Position des NUL-Terminators entspricht Anzahl Nutzzeichen davor
}
```

- Bei einem String der Länge 100 müsste `for (int i = 0; i < strlen(s); ++i)` zum Beispiel 100 mal `strlen(s)` aufrufen
- Jeder dieser 100 Aufrufe von `strlen(s)` müsste erneut alle 100 Zeichen anfassen, um den NUL-Terminator zu finden
- Insgesamt würden also 100 * 100 = 10.000 Zeichen angefasst anstatt der eigentlich erforderlichen 100 Zeichen
  - (Formal spricht man von "Quadratischer Komplexität" anstatt "Linearer Komplexität")

### Wie benutze ich Strings mit `scanf` und `printf`?

```c
void gruesseNutzer()
{
    printf("Name? ");
    char name[16];
    scanf ( "%15s", name);

    printf("Hallo %s\n", name);
}
```

Dabei steht die `15` in `%15s` für die maximale Länge (exkl. NUL-Terminator `'\0'`).

### Wie vergleiche ich Strings?

```c
void zugang()
{
    printf("Passwort? ");
    char passwort[16];
    scanf("%15s", passwort);

    if (strcmp(passwort, "geheim") == 0)
    {                             ///// strcmp liefert 0 bei gleichen Zeichen
        printf("Willkommen im Club!\n");
    }
    else
    {
        printf("Falsches Passwort!\n");
    }
}
```

Dabei liefert `strcmp(a, b)`:
- 0, falls in `a` genau die gleichen Zeichen hintereinander stehen wie in `b`
- *irgendeine* negative Zahl, falls `a` lexikographisch vor `b` liegt
- *irgendeine* positive Zahl, falls `a` lexikographisch nach `b` liegt

```c
void strcmp_test()
{
    assert(strcmp("Apfel", "Apfel") == 0); // Apfel = Apfel
    assert(strcmp("Apfel", "Birne") <  0); // Apfel < Birne
    assert(strcmp("Birne", "Apfel") >  0); // Birne > Apfel
}
```

Die gewohnten Vergleichsoperatoren `a == b` bzw. `a != b` ignorieren die enthaltenen *Zeichen* und vergleichen stattdessen die *Speicheradressen* von `a` und `b`, was in der Praxis selten sinnvoll ist.

**Daumenregel:** Statt `a OPERATOR b` muss man `strcmp(a, b) OPERATOR 0` schreiben, um die Zeichen zu vergleichen.
