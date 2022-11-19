# Woche 8

📺 Wie funktionieren `rand` und `srand` intern? https://www.youtube.com/watch?v=0sEmOCO5CQM

## Aufgaben

### Aufgabe 8.1 `int[6]` (abnahmepflichtig & klausurrelevant)

```c
unsigned int random_state;

void srand(unsigned int seed)
{
    random_state = seed;
}

int rand()
{
    random_state = random_state * 214013 + 2531011;
    return random_state / 65536;
}

void vierfachGemoppelt()
{
    srand(607);

    printf("Die Lottozahlen von morgen:");
    for (int i = 0; i < 6; ++i)
    {   //            ~~ 0..48 ~~
        printf(" %d", rand() % 49 + 1);
    }   //            ~~~~ 1..49 ~~~~
}
```

Obiges Program schreibt folgendes auf die Konsole:

```
Die Lottozahlen von morgen: 12 48 12 12 40 12
```

Hier wird die 12 mehrfach gezogen, was der Realität widerspricht.
Stattdessen wollen wir doppelt gezogene Lottozahlen verwerfen:

```
Die Lottozahlen von morgen: 12 48 40 43 10 49
```

Dazu ziehen wir einfach jede Lottozahl wiederholt neu, solange sie bereits gezogen wurde:

| Versuch |  Erste | Zweite | Dritte | Vierte | Fünfte | Sechste |
| ------: | -----: | -----: | -----: | -----: | -----: | ------: |
|       1 | **12** | **48** |     12 |     12 | **10** |  **49** |
|       2 |        |        |     12 | **43** |        |         |
|       3 |        |        | **40** |        |        |         |

```c
void aufgabe_8_1()
{
    srand(607);

    int a[6];
    a[0] = rand() % 49 + 1;

    do
    {
        a[1] = rand() % 49 + 1;
    }
    while (a[1] == a[0]);

    do
    {
        a[2] = rand() % 49 + 1;
    }
    while (a[2] == a[0] || a[2] == a[1]);

    // ...

    printf("Die Lottozahlen von morgen:");

    // ...
}
```

Vervollständige den Code! Zum Testen bieten sich folgende `srand`-Werte an,
die zu Duplikaten an verschiedenen Stellen führen:

```
srand(  6): 10 10
srand(338): 16    16
srand( 48): 49       49
srand(492): 29          29
srand(111): 10             10
srand( 98):    42 42
srand( 64):    29    29
srand(803):    28       28
srand( 96):    30          30
srand( 92):       17 17
srand( 75):       22    22
srand( 70):       25       25
srand(110):          32 32
srand(300):          26    26
srand( 47):             14 14

srand(607): 12    12 12    12
srand(457): 12    12 42 42 42
```

Das war ziemlich viel Tipparbeit bzw. Fleißarbeit.
Falls du Lust dazu hast, kannst du den Code stark vereinfachen,
indem du eine Hilfsfunktion für die `do/while`-Bedingung schreibst:
`bool istDuplikat(const int zahlen[], int position)` soll prüfen,
ob die Zahl an der `position` bereits links davon in den `zahlen` auftaucht.

### Aufgabe 8.2 `bool[50]` (abnahmepflichtig & klausurrelevant)

Statt einem `int[6]` Array verwenden wir jetzt ein `bool[50]` Array,
das sich für jede Zahl merkt, ob sie bereits gezogen wurde.
Dadurch vereinfacht sich die `do/while`-Bedingung enorm,
weil wir unmittelbar prüfen können, ob die Zahl bereits gezogen wurde!

```c
void aufgabe_8_2()
{
    srand(607);

    bool gezogen[50];

    // Setze alle 50 Elemente auf false
    // (d.h. bisher wurde noch keine Zahl gezogen)

    // Wiederhole 6x
    //      Generiere wiederholt eine neue Zufallszahl,
    //      solange diese bereits gezogen wurde
    //
    //      Vermerke die Zufallszahl als gezogen
    //      und schreibe sie auf die Konsole
}
```

Das eingerückte Verfahren dürfte dir aus Tic Tac Toe bekannt vorkommen:
*Frage den Spieler wiederholt nach einer Position, solange diese bereits belegt ist.
Vermerke diese Position anschließend als belegt.*
Statt `char[9]` (initial Leerzeichen) verwenden wir hier `bool[50]` (initial false).
Außerdem kommen die Positionen jetzt nicht mehr von der Tastatur,
sondern aus einem Zufallszahlen-Generator.
Aber *konzeptionell* sind die Verfahren sehr ähnlich!

### Aufgabe 8.3 Typische `srand`-Fehler (klausurrelevant)

Die folgenden Programme verstoßen gegen die Empfehlung, `srand(time(0))` einmalig ganz am Anfang aufzurufen.
Probiere **auf maximaler Geschwindigkeit** aus, zu welchem Fehlverhalten das führt, und erkläre es deinem Betreuer!

```c
void srandMehrmals()
{
    printf("Die Lottozahlen von morgen:");
    for (int i = 0; i < 6; ++i)
    {
        srand(time(0));
        printf(" %d", rand() % 49 + 1);
    }
}

void srandVergessen()
{
    printf("Die Lottozahlen von morgen:");
    for (int i = 0; i < 6; ++i)
    {
        printf(" %d", rand() % 49 + 1);
    }
}
```

### Aufgabe 8.4 Statistik (klausurrelevant)

Schreibe eine Funktion `void aufgabe_8_4()`, die 490 Zufallszahlen zwischen 1 und 49 zieht und mitzählt,
welche Zufallszahl wie häufig vorkommt. Schreibe am Ende eine Statistik auf die Konsole.
Ohne `srand`-Initialisierung sollte dabei folgende Statistik rauskommen:

```
 1: 11x
 2: 11x
 3: 15x
 4: 7x
 5: 11x
 6: 9x
 7: 9x
 8: 14x
 9: 12x
10: 10x
...
47: 7x
48: 8x
49: 8x
```

## FAQ

### Was sind Arrays?

Ein Array ist eine Kette von Elementen desselben Typs, die hintereinander im Speicher liegen:

```c
void fibonacciArray()
{
    // Definition
    int fib[46];

    // Schreibzugriff
    fib[0] = 1;
    fib[1] = 1;

    for (int i = 2; i < 46; ++i)
    {
        fib[i] = fib[i - 2] + fib[i - 1];
    }

    for (int i = 0; i < 46; ++i)
    {
        // Lesezugriff
        printf("%d ", fib[i]);
    }
}
```

- *Definition:* `int fib[46];` definiert ein Array namens `fib` bestehend aus 46 `int`s
- *Zugriff:* `fib[i]` greift in dem Array `fib` an der Position `i` zu
  - Die 46 `int`s sind von `fib[0]` bis `fib[45]` durchnummeriert
  - Insbesondere existiert *kein* Element `fib[46]` aufgrund der `0`-basierten Indizierung!

### Sind Strings ebenfalls Arrays?

Ja, Strings sind Arrays mit dem Elementtyp `char` sowie 3 Sonderregeln:

1. String-Literale können direkt an Funktionen übergeben werden: `f("String-Literal")`
2. String-Literale können String-Variablen initialisieren: `char s[] = "String-Literal";`
3. Strings enden per Konvention mit dem speziellen Zeichen `'\0'` (NUL-Terminator, ASCII-Code 0)

Weitere Unterschiede gibt es nicht.
Insbesondere funktioniert der Element-Zugriff bei Strings und Arrays genau gleich: `a[i]`

### Sind konstante Arrays sinnvoll?

Konstante Arrays werden gerne als Ersatz für `switch/case/return`-Konstrukte verwendet:

```c
//                                     0   1   2        3   4   5   6   7   8   9   10  11  12
const double averageMonthLengths[] = { -1, 31, 28.2425, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

double averageMonthLength(int month)
{
    if (month < 1 || month > 12) return -1;
    return averageMonthLengths[month];
}

//                          C    D    E   F   G   H   I  J   K   L   M     N   O   P   Q   R   S   T   U   V  W   X
const int romanValues[] = { 100, 500, -1, -1, -1, -1, 1, -1, -1, 50, 1000, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, 10 };

int romanValue(char romanLetter)
{
    if (romanLetter < 'C' || romanLetter > 'X') return -1;
    return romanValues[romanLetter - 'C'];
}
```

### Wie funktionieren Zufallszahlen in [DOOM](https://de.wikipedia.org/wiki/Doom_(1993))?

Es sind einfach 256 vorbestimmte "Zufallszahlen" von 0 bis 255 in einem Array abgelegt,
und daraus werden von links nach rechts zyklisch "Zufallszahlen" gelesen:

```c
// unsigned char  sind Zahlen von 0 bis 255, siehe Woche 3

const unsigned char rndtable[256] = {
      0,   8, 109, 220, 222, 241, 149, 107,  75, 248, 254, 140,  16,  66,  74,  21,
    211,  47,  80, 242, 154,  27, 205, 128, 161,  89,  77,  36,  95, 110,  85,  48,
    212, 140, 211, 249,  22,  79, 200,  50,  28, 188,  52, 140, 202, 120,  68, 145,
     62,  70, 184, 190,  91, 197, 152, 224, 149, 104,  25, 178, 252, 182, 202, 182,
    141, 197,   4,  81, 181, 242, 145,  42,  39, 227, 156, 198, 225, 193, 219,  93,
    122, 175, 249,   0, 175, 143,  70, 239,  46, 246, 163,  53, 163, 109, 168, 135,
      2, 235,  25,  92,  20, 145, 138,  77,  69, 166,  78, 176, 173, 212, 166, 113,
     94, 161,  41,  50, 239,  49, 111, 164,  70,  60,   2,  37, 171,  75, 136, 156,
     11,  56,  42, 146, 138, 229,  73, 146,  77,  61,  98, 196, 135, 106,  63, 197,
    195,  86,  96, 203, 113, 101, 170, 247, 181, 113,  80, 250, 108,   7, 255, 237,
    129, 226,  79, 107, 112, 166, 103, 241,  24, 223, 239, 120, 198,  58,  60,  82,
    128,   3, 184,  66, 143, 224, 145, 224,  81, 206, 163,  45,  63,  90, 168, 114,
     59,  33, 159,  95,  28, 139, 123,  98, 125, 196,  15,  70, 194, 253,  54,  14,
    109, 226,  71,  17, 161,  93, 186,  87, 244, 138,  20,  52, 123, 251,  26,  36,
     17,  46,  52, 231, 232,  76,  31, 221,  84,  37, 216, 165, 212, 106, 197, 242,
     98,  43,  39, 175, 254, 145, 190,  84, 118, 222, 187, 136, 120, 163, 236, 249,
};

unsigned char rndindex;

int M_Random()
{
    ++rndindex;
    return rndtable[rndindex];
}
```

Man beachte, dass manche "Zufallszahlen" mehrfach vorkommen, z.B. die 0 und die 2.
Andere "Zufallszahlen" fehlen dagegen logischerweise.

### Muss man alle Zufallszahlen unbedingt im Arbeitsspeicher ablegen?

Nein, alternativ kann man jede "Zufallszahl" live mit einem [Linearen Kongruenzgenerator](https://en.wikipedia.org/wiki/Linear_congruential_generator) berechnen:

```c
unsigned char random_state;

int rand()
{
    random_state = random_state * 89 + 1;
    return random_state;       //  a   c
}
```

Die deterministisch berechnete Sequenz sieht für `a=89` und `c=1` wie folgt aus:

```
  1,  90,  75,  20, 245,  46, 255, 168, 105, 130,  51, 188,  93,  86, 231,  80,
209, 170,  27, 100, 197, 126, 207, 248,  57, 210,   3,  12,  45, 166, 183, 160,
161, 250, 235, 180, 149, 206, 159,  72,   9,  34, 211,  92, 253, 246, 135, 240,
113,  74, 187,   4, 101,  30, 111, 152, 217, 114, 163, 172, 205,  70,  87,  64,
 65, 154, 139,  84,  53, 110,  63, 232, 169, 194, 115, 252, 157, 150,  39, 144,
 17, 234,  91, 164,   5, 190,  15,  56, 121,  18,  67,  76, 109, 230, 247, 224,
225,  58,  43, 244, 213,  14, 223, 136,  73,  98,  19, 156,  61,  54, 199,  48,
177, 138, 251,  68, 165,  94, 175, 216,  25, 178, 227, 236,  13, 134, 151, 128,
129, 218, 203, 148, 117, 174, 127,  40, 233,   2, 179,  60, 221, 214, 103, 208,
 81,  42, 155, 228,  69, 254,  79, 120, 185,  82, 131, 140, 173,  38,  55,  32,
 33, 122, 107,  52,  21,  78,  31, 200, 137, 162,  83, 220, 125, 118,   7, 112,
241, 202,  59, 132, 229, 158, 239,  24,  89, 242,  35,  44,  77, 198, 215, 192,
193,  26,  11, 212, 181, 238, 191, 104,  41,  66, 243, 124,  29,  22, 167,  16,
145, 106, 219,  36, 133,  62, 143, 184, 249, 146, 195, 204, 237, 102, 119,  96,
 97, 186, 171, 116,  85, 142,  95,   8, 201, 226, 147,  28, 189, 182,  71, 176,
 49,  10, 123, 196,  37, 222,  47,  88, 153,  50,  99, 108, 141,   6,  23,   0,
```

Man beachte, dass jede "Zufallszahl" nun genau 1x vorkommt.
(Statt `a=89` und `c=1` kann man jedes `a=4k+1` und `c=2n+1` für einen vollen Zyklus verwenden.)

### Ein voller Zyklus der Länge 256 mit allen Zahlen von 0 bis 255 wirkt irgendwie nicht besonders zufällig...

Stimmt, deshalb schneidet `rand()` normalerweise die untere Hälfte vom Ergebnis ab:

```c
int rand()
{
    random_state = random_state * 89 + 1;
    return random_state / 16;
}   //                  ^^^^
```

Jetzt findet man z.B. erwartungskonform etwa einen Zwillingsnachbar pro Reihe:

```
 0,  5,  4,  1, 15,  2, 15, 10,  6,  8,  3, 11,  5,  5, 14,  5,
13, 10,  1,  6, 12,  7, 12, 15,  3, 13,  0,  0,  2, 10, 11, 10,
10, 15, 14, 11,  9, 12,  9,  4,  0,  2, 13,  5, 15, 15,  8, 15,
 7,  4, 11,  0,  6,  1,  6,  9, 13,  7, 10, 10, 12,  4,  5,  4,
 4,  9,  8,  5,  3,  6,  3, 14, 10, 12,  7, 15,  9,  9,  2,  9,
 1, 14,  5, 10,  0, 11,  0,  3,  7,  1,  4,  4,  6, 14, 15, 14,
14,  3,  2, 15, 13,  0, 13,  8,  4,  6,  1,  9,  3,  3, 12,  3,
11,  8, 15,  4, 10,  5, 10, 13,  1, 11, 14, 14,  0,  8,  9,  8,
 8, 13, 12,  9,  7, 10,  7,  2, 14,  0, 11,  3, 13, 13,  6, 13,
 5,  2,  9, 14,  4, 15,  4,  7, 11,  5,  8,  8, 10,  2,  3,  2,
 2,  7,  6,  3,  1,  4,  1, 12,  8, 10,  5, 13,  7,  7,  0,  7,
15, 12,  3,  8, 14,  9, 14,  1,  5, 15,  2,  2,  4, 12, 13, 12,
12,  1,  0, 13, 11, 14, 11,  6,  2,  4, 15,  7,  1,  1, 10,  1,
 9,  6, 13,  2,  8,  3,  8, 11, 15,  9, 12, 12, 14,  6,  7,  6,
 6, 11, 10,  7,  5,  8,  5,  0, 12, 14,  9,  1, 11, 11,  4, 11,
 3,  0,  7, 12,  2, 13,  2,  5,  9,  3,  6,  6,  8,  0,  1,  0,
```

### Aber jetzt hat man ja nur noch 16 verschiedene Zufallszahlen statt 256?

Wenn wir den Zustandsraum von 8 Bit auf 32 Bit erhöhen,
können wir halbwegs gute 16-Bit-"Zufallszahlen" von 0 bis 65535 generieren:

```c
// unsigned int  sind Zahlen von 0 bis 4294967295, siehe Woche 3

unsigned int random_state;

int rand()
{
    // https://en.wikipedia.org/wiki/Linear_congruential_generator#Parameters_in_common_use
    random_state = random_state * 214013 + 2531011;
    return random_state / 65536;
}
```

(Die entsprechende Tabelle mit 4294967296 Einträgen ersparen wir uns an dieser Stelle aus Platzgründen.)

### Wieso bekomme ich bei jedem Programmstart dieselben Zufallszahlen?

Weil `random_state` am Anfang `0` ist. Wenn wir `random_state` stattdessen mit `time(0)` initialisieren,
fangen wir bei jedem Programmstart woanders in der langen Sequenz von 4 Milliarden "Zufallszahlen" an;
sofern wir das Programm nicht mehrfach pro Sekunde starten:

```c
void srand(unsigned int seed)
{
    if (random_state != 0)
    {
        printf("https://stackoverflow.com/questions/7343833/srand-why-call-it-only-once\n");
    }
    random_state = seed;
}

void dieLottozahlenVonMorgen()
{
    // EINMALIGE (!!!) Initialisierung des Linearen Kongruenzgenerators ganz am Anfang
    srand(time(0));

    printf("Die Lottozahlen von morgen:");
    for (int i = 0; i < 6; ++i)
    {
        // rand() kann beliebig oft und beliebig schnell hintereinander aufgerufen werden
        printf(" %d", rand() % 49 + 1);
    }
}
```
