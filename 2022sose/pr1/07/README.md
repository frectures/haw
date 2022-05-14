# Woche 7

## Aufgaben

### Aufgabe 7.1 Tic Tac Toe unentschieden (Pflicht)

Implementiere die Funktion `printBoard` gemäß folgendem Beispiel:

```c
void printBoard(const char board[9])
{
    // ...
}

void aufgabe_7_1()
{   //         oben   unten
    //          ___   ___
    printBoard("XO XXOOXO");
}
```

```
 X | O |   
---+---+---
 X | X | O 
---+---+---
 O | X | O 
```

Implementiere die Funktion `humanMove`, die den Spieler nach einer leeren Position fragt
und diese anschließend mit seinem Zeichen besetzt. Beispiel:

```c
void humanMove(char board[9], char player)
{
    // ...
}

void aufgabe_7_1()
{
    char board[] = "         ";
    assert(strlen(board) == 9);
    
    printBoard(board);
    humanMove(board, 'X');
    printBoard(board);
    humanMove(board, 'O');
    printBoard(board);
}
```

```
   |   |   
---+---+---
   |   |   
---+---+---
   |   |   

X? 4

   |   |   
---+---+---
   | X |   
---+---+---
   |   |   

O? 4
O? 4
O? 4
O? 123
O? -1
O? 5

   |   |   
---+---+---
   | X | O 
---+---+---
   |   |   
```
(Die Zahlen nach den Fragezeichen sind Tastatur-Eingaben.)

Ergänze das Programm, so dass alle 9 Positionen besetzt werden.
Gewinnen kann man in dieser Version noch nicht, das "Spiel" geht immer unentschieden aus.

### Aufgabe 7.2 Tic Tac Toe gewinnbar (Pflicht)

Kopiere die Funktion `aufgabe_7_1` in eine neue Funktion `aufgabe_7_2`.

Implementiere die Funktion `wins`, die prüfen soll,
ob der Spieler 3 Zeichen in einer Reihe (horizontal, vertikal oder diagonal) hat:

```c
typedef enum { false, true } bool;

bool wins(const char board[9], char player)
{
    // ...
}

void test_wins()
{
    assert( wins("XXX      ", 'X'));
    assert(!wins(" XXX     ", 'X'));
    assert(!wins("  XXX    ", 'X'));
    assert( wins("   XXX   ", 'X'));
    assert(!wins("    XXX  ", 'X'));
    assert(!wins("     XXX ", 'X'));
    assert( wins("      XXX", 'X'));

    assert( wins("X  X  X  ", 'X'));
    assert( wins(" X  X  X ", 'X'));
    assert( wins("  X  X  X", 'X'));

    assert( wins("X   X   X", 'X'));
    assert( wins("  X X X  ", 'X'));
}
```

Integriere `wins` sinnvoll in `aufgabe_7_2`, so dass man gewinnen kann. Beispiel:

```
   |   |   
---+---+---
   |   |   
---+---+---
   |   |   

X? 0

 X |   |   
---+---+---
   |   |   
---+---+---
   |   |   

O? 8

 X |   |   
---+---+---
   |   |   
---+---+---
   |   | O 

X? 1

 X | X |   
---+---+---
   |   |   
---+---+---
   |   | O 

O? 7

 X | X |   
---+---+---
   |   |   
---+---+---
   | O | O 

X? 2

 X | X | X 
---+---+---
   |   |   
---+---+---
   | O | O 

X hat gewonnen!
```
(Die Zahlen nach den Fragezeichen sind Tastatur-Eingaben.)

Wenn ein Spieler gewonnen hat, ist das Spiel vorbei.
Weder der Verlierer noch der Gewinner dürfen weitere Positionen besetzen.
Endet das Spiel nach 9 Zügen ohne Sieger, soll `Unentschieden!` erscheinen.

### Aufgabe 7.3 Zufälliger Computergegner (Kür)

Kopiere die Funktion `aufgabe_7_2` in eine neue Funktion `aufgabe_7_3`.

Spieler `X` soll vom Computer gesteuert werden.
Schreibe dazu eine Funktion `dumbComputerMove`, 
die einfach zufällig eine leere Position besetzt.

Da `time(0)` nur einmal pro Sekunde eine neue (um 1 höhere) "Zufallszahl" liefert,
ist diese Funktion ungeeignet, falls man ständig neue "Zufallszahlen" braucht.
(Der Mensch könnte einfach absichtlich *n* Sekunden lang warten,
um eine "Zufallszahl" zu provozieren, die genau *n* höher ist als vorher.)
Stattdessen rufen wir `time(0)` nur noch einmalig am Anfang der `main`-Funktion auf,
um einen *Linearen Kongruenzgenerator* zu initialisieren:

```c
unsigned random_state;

void srand(unsigned seed)
{
    if (random_state != 0)
    {
        printf("https://stackoverflow.com/questions/7343833/srand-why-call-it-only-once\n");
    }
    random_state = seed;
}

int rand()
{
    // https://en.wikipedia.org/wiki/Linear_congruential_generator#Parameters_in_common_use
    random_state = random_state * 214013 + 2531011;
    return random_state / 65536;
}

int main()
{
    // EINMALIGE (!!!) Initialisierung des Linearen Kongruenzgenerators
    srand(time(0));

    // rand() kann beliebig oft und beliebig schnell hintereinander aufgerufen werden
    printf("3 Lottozahlen: %d, %d, %d\n", rand() % 49, rand() % 49, rand() % 49);
    
    aufgabe_7_3();
    
    return 0;
}
```

Wie verhält sich der Computergegner, wenn du `srand(time(0));` auskommentierst bzw. löschst?

### Aufgabe 7.4 Intelligenter Computergegner (Kür)

Kopiere die Funktion `aufgabe_7_3` in eine neue Funktion `aufgabe_7_4`.
Kopiere die Funktion `dumbComputerMove` in eine neue Funktion `smartComputerMove`.

Anstatt komplett zufällig zu agieren, soll der Computergegner folgende Prioritätenliste durchgehen:

1. Führt das Besetzen einer freien Position mit `X` zum Sieg des Computers? Dann wähle diese Position
2. Führt das Besetzen einer freien Position mit `O` zum Sieg des Menschen? Dann wähle diese Position
3. Wähle wie gehabt eine zufällige Position

```c
void test_smartComputerMove()
{
    char gewinnbar[] = "OO XX    ";
    smartComputerMove(gewinnbar, 'X');
    assert(0 == strcmp("OO XXX   ", gewinnbar));
    
    char verlierbar[]= "OO  X   X";
    smartComputerMove(verlierbar, 'X');
    assert(0 == strcmp("OOX X   X", verlierbar));
}
```

## FAQ

### Wie fordere ich den Benutzer bei fachlich sinnlosen Eingaben erneut auf?

Hier ein Beispiel für Zeichen, von denen nur 2 fachlich sinnvoll sind:

```c
char nochEinmal()
{
    char entscheidung;
    printf("Noch einmal spielen (j/n)? ");
    scanf(" %c", &entscheidung);
    while (!(entscheidung == 'j' || entscheidung == 'n'))
    {
        printf("Noch einmal spielen (j/n)? ");
        scanf(" %c", &entscheidung);
    }
    return entscheidung;
}
```

Mit De-Morgan können wir die Negation in die Klammern reinziehen:

```c
    while (!(entscheidung == 'j' || entscheidung == 'n'))
    while (  entscheidung != 'j' && entscheidung != 'n' )
```

### Geht das auch ohne doppelte Verwendung von `printf` und `scanf` im Programm?

Ja, und zwar mit der `do`/`while`-Schleife, die sonst eher selten zum Einsatz kommt:

```c
char nochEinmal()
{
    char entscheidung;
    do
    {
        printf("Noch einmal spielen (j/n)? ");
        scanf(" %c", &entscheidung);
    } while (entscheidung != 'j' && entscheidung != 'n');
    return entscheidung;
}
```

- Die `while`-Schleife prüft die Schleifenbedingung, bevor der Schleifenrumpf das erste Mal ausgeführt wird
  - Der Schleifenrumpf wird evtl. gar nicht ausgeführt
- Die `do`/`while`-Schleife führt den Schleifenrumpf aus, bevor die Schleifenbedigung das erste Mal geprüft wird
  - Der Schleifenrumpf wird mindestens 1x ausgeführt

### Was mache ich, wenn der Benutzer statt einer Zahl etwas anderes eingibt?

Hier ist das Problem:

```c
void echo()
{
    int zahl;
    printf("Bitte geben Sie eine Zahl ein: ");
    scanf("%d", &zahl);
    printf("Sie haben die Zahl %d eingegeben.\n", zahl);
}
```

Falls der Benutzer statt `123` z.B. `abc` eingibt, wird Skorbut beim zweiten `printf` abstürzen,
weil `scanf` keine Zahl im Eingabestrom vorfindet und `zahl` daher nicht befüllt.
(In echten Umgebungen hat `zahl` den Wert, der zu dem Zeitpunkt zufällig im Speicher steht.)

`scanf` liefert als Ergebnis die Anzahl erfolgreich befüllter Variablen.
Falls die Anzahl 0 ist, hat der Benutzer statt einer Zahl etwas anderes eingegeben.
Bevor wir `scanf` erneut aufrufen, sollten wir alle Zeichen bis zum nächsten Zeilenumbruch konsumieren:

```c
void echo()
{
    int zahl;
    printf("Bitte geben Sie eine Zahl ein: ");
    while (scanf("%d", &zahl) == 0)
    {
        while (getchar() != '\n')
        {
        }
        printf("Bitte geben Sie eine Zahl ein: ");
    }
    printf("Sie haben die Zahl %d eingegeben.\n", zahl);
}
```

### Muss ich diesen komplizierten Code jedes Mal hinschreiben, wenn ich eine Zahl einlesen will?!

Natürlich nicht, komplizierter Code gehört in eigene Funktionen:

```c
void konsumiereZeilenrest()
{
    while (getchar() != '\n')
    {
    }
}

int liesZahl(const char prompt[])
{
    int zahl;
    printf("%s", prompt);
    while (scanf("%d", &zahl) == 0)
    {
        konsumiereZeilenrest();
        printf("%s", prompt);
    }
    return zahl;
}

void addition()
{
    int x = liesZahl("x? ");
    int y = liesZahl("y? ");
    printf("%d + %d = %d\n", x, y, x + y);
}
```
