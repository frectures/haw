# Woche 7

## Aufgaben

### Aufgabe 7.1 Tic Tac Toe unentschieden (abnahmepflichtig & klausurrelevant)

```c
void printBoard(const char board[9])
{
    printf("%c%c%c\n%c%c%c\n%c%c%c\n",
        board[0], board[1], board[2],
        board[3], board[4], board[5],
        board[6], board[7], board[8]);
}

void ticTacToe()
{
    printBoard("O  XO XXO");
}
```

Obiges Programm schreibt folgendes auf die Konsole:

```
O  
XO 
XXO
```

Ändere die Funktion `printBoard`, so dass stattdessen folgendes auf der Konsole erscheint:

```
 O |   |   
---+---+---
 X | O |   
---+---+---
 X | X | O 
```

Vervollständige anschließend die Funktion `humanMove`, die den Spieler nach einer Position fragt
und diese dann mit seinem Zeichen besetzt:

```c
void humanMove(char board[9], char player)
{
    // Was muss auf die Konsole geschrieben werden, damit der aktuelle Spieler versteht,
    // dass er jetzt dran ist und etwas eingeben soll? Siehe Beispiel unter dem Programm!
    
    char input;
    scanf(" %c", &input);
    int position = input - '0';
    
    // Was muss sich im Arbeitsspeicher ändern, damit die Position besetzt ist?
    // Wie verändert man einen String ganz allgemein? Und konkret für unseren Fall:
    // - welcher String?
    // - welche Position?
    // - welches neue Zeichen?
}

void ticTacToe()
{
    // Veranschaulicht die möglichen Positionen
    printBoard("012345678");
    
    // Initialisierung mit geschweiften Klammern ist hier lesbarer als  "         "
    char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    // Außerdem spart man sich so den ausnahmsweise nicht benötigten NUL-Terminator
    
    humanMove(board, 'X');
    printBoard(board);
    
    humanMove(board, 'O');
    printBoard(board);
}
```

```
 0 | 1 | 2 
---+---+---
 3 | 4 | 5 
---+---+---
 6 | 7 | 8 

X? 4

   |   |   
---+---+---
   | X |   
---+---+---
   |   |   

O? 5

   |   |   
---+---+---
   | X | O 
---+---+---
   |   |   
```
(`4` und `5` sind Tastatur-Eingaben der Spieler.)

Erweitere das Programm von 2 Spielzügen auf 9 Spielzüge.<br>
Gewinnen kann man in dieser Version noch nicht, das "Spiel" geht immer unentschieden aus.

Die Qualitätskontrolle findet 2 Probleme in deinem Programm:
1. Wenn man ein Zeichen außerhalb von `0` bis `8` eingibt (z.B. `9` oder `/`), stürzt das Programm ab
2. Man kann bereits besetzte Position erneut besetzen, das verstößt gegen die Spielregeln

Beim Beheben beider Probleme helfen die
[FAQs 3&4](#wie-fordere-ich-den-benutzer-bei-fachlich-inkorrekten-eingaben-erneut-auf).

### Aufgabe 7.2 Tic Tac Toe gewinnbar (abnahmepflichtig & klausurrelevant)

Vervollständige die Funktion `has3in1row`, die prüfen soll,
ob der Spieler 3 Zeichen in einer Reihe (horizontal, vertikal oder diagonal) besetzt hat:

```c
//             0      1      int
typedef enum { false, true } bool;

bool has3in1row(const char board[9], char player)
{
    if ( /* obere    Zeile besetzt */ ) return true;
    if ( /* mittlere Zeile besetzt */ ) return true;
    if ( /* untere   Zeile besetzt */ ) return true;
    
    if ( /* linke   Spalte besetzt */ ) return true;
    // ...
    // ...
    
    // ...
    // ...
    
    return false;
}

void has3in1row_test()
{
    assert( has3in1row("XXX      ", 'X'));
    assert(!has3in1row(" OOO     ", 'O'));
    assert(!has3in1row("  XXX    ", 'X'));
    assert( has3in1row("   OOO   ", 'O'));
    assert(!has3in1row("    XXX  ", 'X'));
    assert(!has3in1row("     OOO ", 'O'));
    assert( has3in1row("      XXX", 'X'));

    assert( has3in1row("O  O  O  ", 'O'));
    assert( has3in1row(" X  X  X ", 'X'));
    assert( has3in1row("  O  O  O", 'O'));

    assert( has3in1row("X   X   X", 'X'));
    assert( has3in1row("  O O O  ", 'O'));
}
```

Rufe `has3in1row` an passenden Stellen in `ticTacToe` auf und reagiere sinnvoll auf das Ergebnis,
damit Gewinnsituationen das Spiel erfolgreich beenden. Beispiel:

```
 0 | 1 | 2 
---+---+---
 3 | 4 | 5 
---+---+---
 6 | 7 | 8 

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
Weder Verlierer noch Gewinner dürfen dann noch weitere Positionen besetzen.
**Tipp:** Mit `return;` beendet man eine `void`-Funktion.

Endet das Spiel nach 9 Zügen ohne Sieger, soll `Unentschieden!` erscheinen.

### Aufgabe 7.3 Zufälliger Computergegner (klausurrelevant)

Kopiere die Funktion `ticTacToe` in eine neue Funktion `ticTacToeRandom`.

Spieler `X` soll vom Computer gesteuert werden.
Schreibe dazu eine Funktion `randomComputerMove`,
die einfach zufällig eine freie Position besetzt.
Mit `time(0) % 9` erhältst du eine zufällige Position von 0 bis 8.

Da `time(0)` nur einmal pro Sekunde eine neue (um 1 höhere) Zufallszahl liefert,
ist diese Funktion ungeeignet, falls man ständig neue Zufallszahlen braucht.
(Der Mensch könnte einfach absichtlich *n* Sekunden lang warten,
um eine Zufallszahl zu provozieren, die genau *n* höher ist als vorher.)
Nächste Woche werden wir einen besseren Zufallszahlen-Generator kennenlernen!

### Aufgabe 7.4 Schlauer Computergegner (klausurrelevant)

Kopiere die Funktion `ticTacToeRandom` in eine neue Funktion `ticTacToeSmart`.

Schreibe eine Funktion `smartComputerMove`, die folgende Prioritätenliste durchgeht:

1. Führt das Besetzen einer freien Position mit `X` zum Sieg des Computers? Dann wähle diese Position
2. Führt das Besetzen einer freien Position mit `O` zum Sieg des Menschen? Dann wähle diese Position
3. Wähle wie gehabt eine zufällige Position

```c
void smartComputerMove_test()
{
    char gewinnbar[] = "OO XX    ";
    smartComputerMove(gewinnbar, 'X');
    assert(strcmp("OO XXX   ", gewinnbar) == 0);

    char verlierbar[]= "OO  X   X";
    smartComputerMove(verlierbar, 'X');
    assert(strcmp("OOX X   X", verlierbar) == 0);
}
```

**Tipp:** Beide "*Führt das Besetzen einer freien Position zum Sieg?*"-Fragen
können jeweils durch schlichtes Ausprobieren beantwortet werden:

1. Stein ablegen
2. `has3in1row` aufrufen
3. Stein ggf. wieder entfernen

## FAQ

### Welchen Sinn hat `typedef enum { false, true } bool;` ?

C89/C90 hat keinen Datentyp für Wahrheitswerte.
Stattdessen wird die Zahl 0 als *falsch* interpretiert und alle anderen Zahlen als *wahr*:

```c
void onlyZeroIsFalse()
{
    assert( -2147483648);
    // ...
    assert( -3);
    assert( -2);
    assert( -1);
    
    assert(! 0); // nur 0 ist falsch
    
    assert( +1);
    assert( +2);
    assert( +3);
    // ...
    assert( +2147483647);
}
```

Für die Lesbarkeit von Programmen sind Zahlen als Wahrheitswerte eher unschön:

```c
int istPrim(int zahl)
{
    if (zahl < 2) return 0; // falsch
    if (zahl == 2) return 1; // wahr
    if (zahl % 2 == 0) return 0; // falsch
    
    for (int teiler = 3; teiler * teiler <= zahl; teiler += 2)
    {
        if (zahl % teiler == 0) return 0; // falsch
    }
    return 1; // wahr
}
```

Wenn C89/C90 einen Datentyp für Wahrheitswerte hätte, könnte man stattdessen schreiben:

```c
bool istPrim(int zahl)
{
    if (zahl < 2) return false;
    if (zahl == 2) return true;
    if (zahl % 2 == 0) return false;
    
    for (int teiler = 3; teiler * teiler <= zahl; teiler += 2)
    {
        if (zahl % teiler == 0) return false;
    }
    return true;
}
```

Im Prinzip brauchen wir also nur folgende Abbildungen:

- `false` bedeutet `0`
- `true` bedeutet `1`
- `bool` bedeutet `int`

Und genau das leistet `typedef enum { false, true } bool;` im Wesentlichen.

Die Bezeichnung `bool` (C99, C++, C#) bzw. `boolean` (Java, JavaScript)
geht auf den englischen Mathematiker, Logiker und Philosophen
[George Boole](https://de.wikipedia.org/wiki/George_Boole) (1815 - 1864) zurück.

George Boole kam als erster Mensch auf die Idee, mit Wahrheitswerten zu *rechnen*;
nach ihm ist die [Boolesche *Algebra*](https://de.wikipedia.org/wiki/Boolesche_Algebra) benannt,
hier der Übersichtlichkeit halber mit ❌ falsch bzw. ✔️ wahr veranschaulicht: 

|     |     | nicht | und      | (inklusiv)<br>oder | exklusiv<br>oder |
| :-: | :-: | :---: | :------: | :--------: | :-----: |
| `a` | `b` | `!b`  | `a && b` | `a \|\| b` | `a ^ b` |
| ❌ | ❌ | ✔️ | ❌ | ❌ | ❌ |
| ❌ | ✔️ | ❌ | ❌ | ✔️ | ✔️ |
| ✔️ | ❌ | ✔️ | ❌ | ✔️ | ✔️ |
| ✔️ | ✔️ | ❌ | ✔️ | ✔️ | ❌ |

Eine solche Tabelle kann man auch programmatisch generieren:

```c
typedef enum { false, true } bool;

void boolescheAlgebra()
{
    printf("a b  !b && || ^\n---------------\n");
    for (bool a = false; a <= true; ++a)
    {
        for (bool b = false; b <= true; ++b)
        {
            printf("%d %d  %d  %d  %d  %d\n",
                a, b, !b, a && b, a || b, a ^ b);
        }
    }
}
```

```
a b  !b && || ^
---------------
0 0  1  0  0  0
0 1  0  0  1  1
1 0  1  0  1  1
1 1  0  1  1  0
```

### Wofür ist `enum` noch gut außer `bool`?

Enumerations (Aufzählungen) sind für *alle* aufzählbaren Konstanten gut:

```c
//             0       1        2          3         4       5         6        int
typedef enum { MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY } Weekday;

Weekday favorite = FRIDAY;
Weekday garfield = MONDAY;

//             0        1      2      3     4        5       6       7        8       int
typedef enum { MERCURY, VENUS, EARTH, MARS, JUPITER, SATURN, URANUS, NEPTUNE, PLUTO } Planet;

Planet controversial = PLUTO;

//         1      5      10      50      100      500      1000
enum { I = 1, V = 5, X = 10, L = 50, C = 100, D = 500, M = 1000 };

int year = M+M+X+X+I+I+I;
```

Wie das letzte Beispiel demonstriert,
lässt man das `typedef` ganz links und den Typnamen ganz rechts einfach weg,
wenn man keinen alternativen Typnamen benötigt;
Jahreszahlen sind nur *ein* möglicher Einsatzzweck römischer Ziffern!

### Wie fordere ich den Benutzer bei fachlich inkorrekten Eingaben erneut auf?

Hier ein Beispiel für die Eingabe von Zeichen, von denen nur 2 fachlich korrekt sind:

```c
char weinprobe()
{
    char wein;
    printf("Rot- oder Weißwein (r/w)? ");
    scanf(" %c", &wein);
    while (!(wein == 'r' || wein == 'w'))
    {
        printf("Rot- oder Weißwein (r/w)? ");
        scanf(" %c", &wein);
    }
    return wein;
}
```

Dank [Augustus De Morgan](https://de.wikipedia.org/wiki/De-morgansche_Gesetze) können wir die Negation in die Klammern reinziehen:

```c
    while (!(wein == 'r' || wein == 'w'))
    //     ~      ~~     ~~      ~~
    while (  wein != 'r' && wein != 'w' )
```

### Geht das auch ohne doppelte Verwendung von `printf` und `scanf` im Programm?

Ja, und zwar mit der `do`/`while`-Schleife, die sonst eher selten zum Einsatz kommt:

```c
char weinprobe()
{
    char wein;
    do
    {
        printf("Rot- oder Weißwein (r/w)? ");
        scanf(" %c", &wein);
    }
    while (wein != 'r' && wein != 'w');

    return wein;
}
```

- Die `while`-Schleife prüft die Schleifenbedingung, *bevor* der Schleifenrumpf das erste Mal ausgeführt wird
  - Der Schleifenrumpf wird *evtl. gar nicht* ausgeführt
- Die `do`/`while`-Schleife prüft die Schleifenbedingung, *nachdem* der Schleifenrumpf das erste Mal ausgeführt wurde
  - Der Schleifenrumpf wird *mindestens 1x* ausgeführt
