# Woche 8

## Aufgaben

### Aufgabe 8.1 Lottozahlen (abnahmepflichtig & klausurrelevant)

```c
unsigned int randState;

// Initialisiert den Zufallszahlengenerator
void srand(unsigned int seed)
{
    randState = seed;
}

// Generiert die nächste Zufallszahl
int rand()
{
    randState = randState * 214013 + 2531011;
    return randState / 65536;
}



void doppeltUndDreifach()
{
    srand(457);
    printf("Die Lottozahlen von morgen:");
    for (int i = 0; i < 6; ++i)
    {
        int zwischen0und48 = rand() % 49;
        int zwischen1und49 = zwischen0und48 + 1;
        printf(" %d", zwischen1und49);
    }
}
```

Obiges Programm schreibt folgendes auf die Konsole:

```
Die Lottozahlen von morgen: 12 21 12 42 42 42
```

Leider wurde die 12 doppelt und die 42 sogar dreifach gezogen.
Im echten Lotto darf jede Zahl aber nur einmal vorkommen!
Effektiv wurden also nur die ersten 3 Lottozahlen von 6 gezogen,
es fehlen noch 3 weitere:

```
Die Lottozahlen von morgen: 12 21 42 48 8 3
```

Wiederhole das Ziehen jeder Lottozahl, solange diese schonmal gezogen wurde:

| Versuch |  Erste | Zweite | Dritte | Vierte | Fünfte | Sechste |
| ------: | -----: | -----: | -----: | -----: | -----: | ------: |
|       1 | **12** | **21** |     12 |     42 |  **8** |   **3** |
|       2 |        |        | **42** |     42 |        |         |
|       3 |        |        |        |     12 |        |         |
|       4 |        |        |        | **48** |        |         |

Führe dazu das `do`/`while`-Muster in der Funktion `lotto6` fort:

```c
void lotto6(int a[6])
{
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
}

const int lotto_testDaten[] =
{
    457,   12, 21, 42, 48,  8,  3,
    6  ,   10, 34, 17, 49, 29, 42,
    338,   16, 39, 15,  5, 40, 35,
    48 ,   49, 16, 33, 38, 47, 36,
    492,   29, 38,  7, 28, 36, 24,
    111,   10, 13, 22, 49, 34,  2,
    98 ,   16, 42, 23,  5, 20, 37,
    64 ,    3, 29, 26, 43, 34, 28,
    803,   15, 28,  3, 35, 26, 48,
    96 ,   10, 30,  8, 38, 28, 35,
    92 ,   46,  9, 17, 28,  3, 32,
    75 ,   39, 15, 22, 46, 10, 14,
    70 ,   23, 13, 25,  9, 20, 34,
    110,    6,  9, 17, 32,  3, 26,
    300,   39,  6,  8, 26, 42, 48,
    47 ,   46, 11,  5, 31, 14, 10,
    607,   12, 48, 40, 43, 10, 49,
    
    -1
};

void lotto6_test()
{
    int lottozahlen[6];
    for (int i = 0; lotto_testDaten[i] != -1; i += 7)
    {
        srand(lotto_testDaten[i]);
        lotto6(lottozahlen);
        
        assert(lottozahlen[0] == lotto_testDaten[i + 1]);
        assert(lottozahlen[1] == lotto_testDaten[i + 2]);
        assert(lottozahlen[2] == lotto_testDaten[i + 3]);
        assert(lottozahlen[3] == lotto_testDaten[i + 4]);
        assert(lottozahlen[4] == lotto_testDaten[i + 5]);
        assert(lottozahlen[5] == lotto_testDaten[i + 6]);
    }
}
```

**Optional:** Vereinfache `lotto6` mit einer Hilfsfunktion für die `do`/`while`-Bedingung:

```c
// Prüft, ob die Zahl an der Position bereits links davon in den Zahlen auftaucht
bool istDuplikat(const int zahlen[], int position)
{
    // ...
}
```

### Aufgabe 8.2 Rechentrainer (abnahmepflichtig & klausurrelevant)

Schreibe eine Funktion `void rechentrainer()`, die sich zufällige Rechenaufgaben
(ganzzahlige Addition, Subtraktion, Multiplikation) ausdenkt.
Der Benutzer rechnet die Aufgabe im Kopf aus und tippt seinen Lösungsvorschlag ein.
Dieser wird dann mit dem korrekten Ergebnis verglichen:

```
Was ist 9 * 6 ? 45
Falsch! 9 * 6 = 54

Was ist 3 - 7 ? 4
Falsch! 3 - 7 = -4

Was ist 5 - 8 ? -3
Stimmt!

Was ist 1 + 8 ? 18
Falsch! 1 + 8 = 9

Was ist 9 - 7 ? 2
Stimmt!

Was ist 5 + 3 ? 8
Stimmt!
```

(Die Zahlen nach den Fragezeichen sind Tastatur-Eingaben.)

Ideen für **optional**e Erweiterungen:

- Beende das Rechentraining nach 10 Runden und bewerte die Leistung des Benutzers
- Oder passe den Schwierigkeitsgrad nach jeder Runde an die Leistung des Benutzers an
- Ganzzahlige Division (mit ganzzahligem Ergebnis!)

### Aufgabe 8.3 Lottoschein (klausurrelevant)

Zusätzlich zum `int[6]` Array verwenden wir jetzt ein `bool[50]` Array,
das sich für jede ziehbare Lottozahl von 1 bis 49 merkt, ob sie bereits gezogen wurde.
Dadurch vereinfacht sich die `do`/`while`-Bedingung auf einen einzigen Array-Zugriff!

```c
void lotto50(int a[6])
{
    bool gezogen[50] =
    {
        false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false,
    };
    
    // repeat (6)
    {
        do
        {
            // Ziehe eine Lottozahl
        }
        while ( /* Wurde diese Lottozahl schonmal gezogen? */ );
        
        // Vermerke die Lottozahl als erstmalig gezogen
    }
}

void lotto50_test()
{
    int lottozahlen[6];
    for (int i = 0; lotto_testDaten[i] != -1; i += 7)
    {
        srand(lotto_testDaten[i]);
        lotto50(lottozahlen);
        
        assert(lottozahlen[0] == lotto_testDaten[i + 1]);
        assert(lottozahlen[1] == lotto_testDaten[i + 2]);
        assert(lottozahlen[2] == lotto_testDaten[i + 3]);
        assert(lottozahlen[3] == lotto_testDaten[i + 4]);
        assert(lottozahlen[4] == lotto_testDaten[i + 5]);
        assert(lottozahlen[5] == lotto_testDaten[i + 6]);
    }
}
```

Der `repeat`-Schleifenrumpf dürfte dir aus Tic Tac Toe bekannt vorkommen:

- Frage den Spieler wiederholt nach einer Position, solange diese bereits belegt ist
- Vermerke diese Position anschließend als belegt

Statt `char[9]` (initial Leerzeichen) verwenden wir hier `bool[50]` (initial false).
Außerdem kommen die Positionen jetzt nicht mehr von der Tastatur,
sondern aus einem Zufallszahlen-Generator.
Aber *konzeptionell* ähneln sich beide Verfahren stark!

### Aufgabe 8.4 Typische `srand`-Fehler (klausurrelevant)

Folgende Funktionen verstoßen gegen die Empfehlung,
`srand(time(0))` *einmalig* zu Beginn der Programmausführung aufzurufen.
Probiere **auf maximaler Geschwindigkeit** aus,
zu welchem Fehlverhalten das führt, und erkläre es deinem Betreuer!

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

## FAQ

### Was sind Arrays?

- Ein Array `Typ name[anzahl];` besteht aus einer festen Anzahl von Variablen desselben Typs
- Diese Variablen sind von `name[0]` bis `name[anzahl-1]` durchnummeriert bzw. zugreifbar:

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

### Sind Strings ebenfalls Arrays?

Ja, Strings sind Arrays mit dem Typ `char` sowie 3 Sonderregeln:

1. String-Literale können direkt an Funktionen übergeben werden: `f("String-Literal")`
2. String-Literale können String-Variablen initialisieren: `char s[] = "String-Literal";`
3. Strings enden per Standard-Konvention mit dem unsichtbaren Zeichen `'\0'`

Weitere Unterschiede gibt es nicht.
Insbesondere funktioniert der Zugriff genau gleich: `a[i]` bzw. `s[i]`

### Woher weiß eine Funktion, wie groß ein übergebenes Array ist?

1. `void f(int a[6])`
   - Die Funktion kann nur mit einer festen Größe sinnvoll umgehen
   - Die `6` ist reine Dokumentation und wird *nicht* überprüft!
2. `void g(int b[], int n)`
   - Der Aufrufer muss die Größe als zusätzliches Argument `n` übergeben
   - Die Funktion vertraut dem Aufrufer, dass er keinen Blödsinn übergibt
3. `void h(int c[])`
   - Funktion und Aufrufer haben sich auf einen "Terminator"-Wert geeinigt
   - Beliebte Werte sind `-1` oder `-2147483648`
   - Jeder Wert, der niemals in den echten Nutzdaten vorkommen kann, ist geeignet
   - Einen Standard-Terminator (analog zu `'\0'` für Strings) gibt es für andere Arrays *nicht*!

### Wie funktionieren Zufallszahlen in [DOOM](https://de.wikipedia.org/wiki/Doom_(1993))?

Es sind einfach 256 vorbestimmte Zufallszahlen von 0 bis 255 in einem Array abgelegt,
und daraus werden von links nach rechts zyklisch Zufallszahlen gelesen:

```c
// unsigned char  sind Zahlen von 0 bis 255, siehe Woche 3

const unsigned char rndtable[256] =
{
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

Man beachte, dass manche Zufallszahlen mehrfach vorkommen, z.B. die 0 und die 2.
Andere Zufallszahlen fehlen dagegen logischerweise.

### Muss man alle Zufallszahlen unbedingt im Arbeitsspeicher ablegen?

Nein, alternativ kann man die nächste Zufallszahl erst bei Bedarf mit einem
[Linearen Kongruenzgenerator](https://en.wikipedia.org/wiki/Linear_congruential_generator) berechnen:

```c
unsigned char randState;

int rand()
{
    randState = randState * 85 + 1;
    return randState;    //  a   c
}
```

Die deterministisch berechnete Sequenz sieht für `a=85` und `c=1` wie folgt aus:

```
  1,  86, 143, 124,  45, 242,  91,  56, 153, 206, 103,  52,  69, 234, 179, 112,
 49,  70,  63, 236,  93, 226,  11, 168, 201, 190,  23, 164, 117, 218,  99, 224,
 97,  54, 239,  92, 141, 210, 187,  24, 249, 174, 199,  20, 165, 202,  19,  80,
145,  38, 159, 204, 189, 194, 107, 136,  41, 158, 119, 132, 213, 186, 195, 192,
193,  22,  79,  60, 237, 178,  27, 248,  89, 142,  39, 244,   5, 170, 115,  48,
241,   6, 255, 172,  29, 162, 203, 104, 137, 126, 215, 100,  53, 154,  35, 160,
 33, 246, 175,  28,  77, 146, 123, 216, 185, 110, 135, 212, 101, 138, 211,  16,
 81, 230,  95, 140, 125, 130,  43,  72, 233,  94,  55,  68, 149, 122, 131, 128,
129, 214,  15, 252, 173, 114, 219, 184,  25,  78, 231, 180, 197, 106,  51, 240,
177, 198, 191, 108, 221,  98, 139,  40,  73,  62, 151,  36, 245,  90, 227,  96,
225, 182, 111, 220,  13,  82,  59, 152, 121,  46,  71, 148,  37,  74, 147, 208,
 17, 166,  31,  76,  61,  66, 235,   8, 169,  30, 247,   4,  85,  58,  67,  64,
 65, 150, 207, 188, 109,  50, 155, 120, 217,  14, 167, 116, 133,  42, 243, 176,
113, 134, 127,  44, 157,  34,  75, 232,   9, 254,  87, 228, 181,  26, 163,  32,
161, 118,  47, 156, 205,  18, 251,  88,  57, 238,   7,  84, 229,  10,  83, 144,
209, 102, 223,  12, 253,   2, 171, 200, 105, 222, 183, 196,  21, 250,   3,   0,
```

Man beachte, dass jede Zufallszahl nun genau 1x vorkommt.
(Statt `a=85` und `c=1` kann man jedes `a=4k+1` und `c=2n+1` für einen vollen Zyklus verwenden.)

### Ein voller Zyklus der Länge 256 mit allen Zahlen von 0 bis 255 wirkt irgendwie nicht besonders zufällig...

Stimmt, deshalb schneidet `rand()` normalerweise die untere Hälfte vom Ergebnis ab:

```c
int rand()
{
    randState = randState * 85 + 1;
    return randState / 16;
}   //               ~~~~
```

```
  0,   5,   8,   7,   2,  15,   5,   3,   9,  12,   6,   3,   4,  14,  11,   7,
  3,   4,   3,  14,   5,  14,   0,  10,  12,  11,   1,  10,   7,  13,   6,  14,
  6,   3,  14,   5,   8,  13,  11,   1,  15,  10,  12,   1,  10,  12,   1,   5,
  9,   2,   9,  12,  11,  12,   6,   8,   2,   9,   7,   8,  13,  11,  12,  12,
 12,   1,   4,   3,  14,  11,   1,  15,   5,   8,   2,  15,   0,  10,   7,   3,
 15,   0,  15,  10,   1,  10,  12,   6,   8,   7,  13,   6,   3,   9,   2,  10,
  2,  15,  10,   1,   4,   9,   7,  13,  11,   6,   8,  13,   6,   8,  13,   1,
  5,  14,   5,   8,   7,   8,   2,   4,  14,   5,   3,   4,   9,   7,   8,   8,
  8,  13,   0,  15,  10,   7,  13,  11,   1,   4,  14,  11,  12,   6,   3,  15,
 11,  12,  11,   6,  13,   6,   8,   2,   4,   3,   9,   2,  15,   5,  14,   6,
 14,  11,   6,  13,   0,   5,   3,   9,   7,   2,   4,   9,   2,   4,   9,  13,
  1,  10,   1,   4,   3,   4,  14,   0,  10,   1,  15,   0,   5,   3,   4,   4,
  4,   9,  12,  11,   6,   3,   9,   7,  13,   0,  10,   7,   8,   2,  15,  11,
  7,   8,   7,   2,   9,   2,   4,  14,   0,  15,   5,  14,  11,   1,  10,   2,
 10,   7,   2,   9,  12,   1,  15,   5,   3,  14,   0,   5,  14,   0,   5,   9,
 13,   6,  13,   0,  15,   0,  10,  12,   6,  13,  11,  12,   1,  15,   0,   0,
```

### Aber jetzt hat man ja nur noch 16 verschiedene Zufallszahlen statt 256?

Wenn wir den Zustandsraum von 8 Bit auf 32 Bit erhöhen,
können wir halbwegs gute 16-Bit-Zufallszahlen von 0 bis 65535 generieren:

```c
// unsigned int  sind Zahlen von 0 bis 4294967295, siehe Woche 3

unsigned int randState;

// Generiert die nächste Zufallszahl
int rand()
{
    // https://en.wikipedia.org/wiki/Linear_congruential_generator#Parameters_in_common_use
    randState = randState * 214013 + 2531011;
    return randState / 65536;
}
```

Die entsprechende Tabelle mit 4294967296 Einträgen ersparen wir uns an dieser Stelle aus Platzgründen.

### Wieso bekomme ich bei jedem Programmstart dieselben Zufallszahlen?

Weil `randState` am Anfang `0` ist. Wenn wir `randState` stattdessen mit `time(0)` initialisieren,
fangen wir bei jedem Programmstart woanders in der langen Sequenz von 4 Milliarden Zufallszahlen an;
sofern wir das Programm nicht mehrfach pro Sekunde starten:

```c
// Initialisiert den Zufallszahlengenerator
void srand(unsigned int seed)
{
    if (randState != 0)
    {
        printf("https://stackoverflow.com/questions/7343833/srand-why-call-it-only-once\n");
    }
    randState = seed;
}

void dieLottozahlenVonMorgen()
{
    // srand(time(0)); sollte EINMALIG zu Beginn der Programmausführung aufgerufen werden
    srand(time(0));

    printf("Die Lottozahlen von morgen:");
    for (int i = 0; i < 6; ++i)
    {
        // rand() kann beliebig oft und beliebig schnell hintereinander aufgerufen werden
        printf(" %d", rand() % 49 + 1);
    }
}
```
