# Woche 8

📺 https://www.youtube.com/watch?v=0sEmOCO5CQM

## Aufgaben

### Aufgabe 8.1 Lottozahlen (abnahmepflichtig & klausurrelevant)

```c
unsigned int random; // Zahlen von 0 bis 4294967295, siehe Woche 3

// Initialisiert den Zufallszahlengenerator
void srand(unsigned int seed)
{
    if (random != 0)
    {
        printf("\nhttps://stackoverflow.com/questions/7343833/srand-why-call-it-only-once\n");
    }
    random = seed;
}

// Generiert die nächste Zufallszahl
int rand()
{
    random = 214013 * random + 2531011;

    return random / 65536;
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

        assert(lottozahlen[0] == lotto_testDaten[i+1]);
        assert(lottozahlen[1] == lotto_testDaten[i+2]);
        assert(lottozahlen[2] == lotto_testDaten[i+3]);
        assert(lottozahlen[3] == lotto_testDaten[i+4]);
        assert(lottozahlen[4] == lotto_testDaten[i+5]);
        assert(lottozahlen[5] == lotto_testDaten[i+6]);
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
- Ganzzahlige Division, mit ganzzahligem Ergebnis
- Verschiedene Schwierigkeitsgrade zur Auswahl

### Aufgabe 8.3 Lottoschein (klausurrelevant)

Zusätzlich zum `int[6]` Array empfiehlt sich ein `bool[50]` Array,
das sich für jede ziehbare Lottozahl von 1 bis 49 merkt, ob sie bereits gezogen wurde.
Dann vereinfacht sich die `do`/`while`-Bedingung nämlich auf einen einzigen Array-Zugriff.

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

        assert(lottozahlen[0] == lotto_testDaten[i+1]);
        assert(lottozahlen[1] == lotto_testDaten[i+2]);
        assert(lottozahlen[2] == lotto_testDaten[i+3]);
        assert(lottozahlen[3] == lotto_testDaten[i+4]);
        assert(lottozahlen[4] == lotto_testDaten[i+5]);
        assert(lottozahlen[5] == lotto_testDaten[i+6]);
    }
}
```

### Aufgabe 8.4 Typische `srand`-Fehler (klausurrelevant)

Folgende Funktionen verstoßen gegen die dringende Empfehlung,
`srand(time(0))` **EINMALIG** zu Beginn der Programmausführung aufzurufen.
Probiere **auf maximaler Geschwindigkeit** aus,
zu welchem Fehlverhalten das jeweils führt, und erkläre es deinem Betreuer!

```c
void srandMehrmals()
{
    printf("Die Lottozahlen von morgen:");
    for (int i = 0; i < 6; ++i)
    {
        srand(time(0)); // Upps!
        printf(" %d", rand() % 49 + 1);
    }
}

void srandVergessen()
{
    // Upps!
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
        fib[i] = fib[i-2] + fib[i-1];
    }

    for (int i = 0; i < 46; ++i)
    {
        // Lesezugriff
        printf("%d ", fib[i]);
    }
}
```

### Woher weiß eine Funktion, wie groß ein übergebenes Array ist?

1. `void f(int a[6])`
   - Die Funktion kann nur mit einer festen Größe sinnvoll umgehen
   - Die `6` ist reine Dokumentation und wird *nicht* überprüft!
2. `void g(int b[], int n)`
   - Der Aufrufer muss die Größe als zusätzliches Argument `n` übergeben
   - Die Funktion vertraut dem Aufrufer, dass er keinen Blödsinn übergibt!
3. `void h(int c[])`
   - Funktion und Aufrufer haben sich auf einen "Terminator"-Wert geeinigt, zum Beispiel `-1`
   - Einen Standard-Terminator (analog zu `'\0'` für Strings) gibt es für andere Arrays *nicht*!

### Wie generiert ein [Linearer Kongruenzgenerator](https://en.wikipedia.org/wiki/Linear_congruential_generator) Zufallszahlen?

```c
unsigned int random; // Zahlen von 0 bis 4294967295, siehe Woche 3

// Generiert die nächste Zufallszahl
int rand()
{
    // https://en.wikipedia.org/wiki/Linear_congruential_generator#Parameters_in_common_use
    random = 214013 * random + 2531011;

    return random / 65536; // verheimlicht dem Aufrufer die unteren 16 Bits
}
```

Die Variable `random` wird deterministisch und periodisch alle 4294967296 `unsigned int`-Werte durchlaufen,
in einer uns Menschen unvorhersehbaren und daher "zufällig" erscheinenden Reihenfolge:

```
         0
   2531011
 505908858
3539360597
 159719620
       ... 4294967286 Zufallszahlen später ...
 380547949
1040873596
2004624719
  59255510
2708534849
         0
   2531011
 505908858
       ...
```

### Wozu verheimlicht `rand()` dem Aufrufer die unteren 16 Bits?

Das *n*-te Bit hat eine Periodizität von 2<sup>*n*</sup>,
was insbesondere für `rand() % m` mit geradem `m` schnell auffallen würde:

```c
void kopfOderZahl()
{
    unsigned int r = 0;
    for (int i = 0; i < 10; ++i)
    {
        r = 214013 * r + 2531011;
        printf("%d ", r % 2); // 1 0 1 0 1 0 1 0 1 0
    }
}

void wuerfeln()
{
    unsigned int r = 0;
    for (int i = 0; i < 10; ++i)
    {                             // gerade
        r = 214013 * r + 2531011; // |   |   |   |   |
        printf("%d ", r % 6 + 1); // 2 1 6 5 2 1 6 3 4 1
    }                             //   |   |   |   |   |
}                                 // ungerade
```

### Wieso liefert `rand()` bei jedem Programmstart dieselben Zufallszahlen?

Weil `random` bei `0` anfängt. Damit `random` bei jedem Programmstart woanders anfängt,
initialisiert man `random` gerne auf die vergangenen Sekunden seit Mitternacht des 1. Januar 1970:

```c
void dieLottozahlenVonMorgen()
{
    random = time(0);

    printf("Die Lottozahlen von morgen:");
    for (int i = 0; i < 6; ++i)
    {
        printf(" %d", rand() % 49 + 1);
    }
}
```

In echten Systemen hat man keinen direkten Zugriff auf die Variable `random`,
stattdessen initialisiert man sie durch Aufruf der Funktion `srand`:

```c
// Initialisiert den Zufallszahlengenerator
void srand(unsigned int seed)
{
    if (random != 0)
    {
        printf("\nhttps://stackoverflow.com/questions/7343833/srand-why-call-it-only-once\n");
    }
    random = seed;
}

void dieLottozahlenVonMorgen()
{
    srand(time(0)); // sollte EINMALIG zu Beginn der Programmausführung aufgerufen werden

    printf("Die Lottozahlen von morgen:");
    for (int i = 0; i < 6; ++i)
    {
        // rand() kann beliebig oft und beliebig schnell hintereinander aufgerufen werden
        printf(" %d", rand() % 49 + 1);
    }
}
```
