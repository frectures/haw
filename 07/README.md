# Woche 7

## Aufgaben

### Aufgabe 7.1 Tic Tac Toe unentschieden (abnahmepflichtig & klausurrelevant)

Implementiere die Funktion `printBoard`, die mithilfe der Sonderzeichen `+-|`
eine visuell ansprechende Repräsentation des Spielfelds auf die Konsole schreibt:

```c
void printBoard(const char board[])
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
und diese anschließend mit seinem Zeichen besetzt:

```c
void humanMove(char board[], char player)
{
    // ...
}

void aufgabe_7_1()
{
    char board[] = "         ";
    assert(strlen(board) == 9);
    printBoard("012345678");

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
(Die Zahlen nach den Fragezeichen sind Tastatur-Eingaben.)

Ergänze das Programm, so dass alle 9 Positionen besetzt werden.
Gewinnen kann man in dieser Version noch nicht, das "Spiel" geht immer unentschieden aus.

Die Qualitätskontrolle findet 3 Probleme in deinem Programm, behebe zumindest das erste Problem:
1. Man kann bereits besetzte Position erneut besetzen, das verstößt gegen die Spielregeln
   - siehe [FAQ 1&2](#wie-fordere-ich-den-benutzer-bei-fachlich-inkorrekten-eingaben-erneut-auf)
2. Wenn man eine Position außerhalb der gültigen Grenzen eingibt (z.B. -1 oder 100), stürzt das Programm ab
3. Wenn man Zeichen eingibt, die keine Zahl darstellen, stürzt das Programm ab oder landet in einer Endlosschleife
   - siehe [FAQ 3&4](#was-mache-ich-wenn-der-benutzer-statt-einer-zahl-etwas-anderes-eingibt)

### Aufgabe 7.2 Tic Tac Toe gewinnbar (abnahmepflichtig & klausurrelevant)

Kopiere die Funktion `aufgabe_7_1` in eine neue Funktion `aufgabe_7_2`.

Implementiere die Funktion `wins`, die prüfen soll,
ob der Spieler 3 Zeichen in einer Reihe (horizontal, vertikal oder diagonal) hat:

```c
typedef enum { false, true } bool;

bool wins(const char board[], char player)
{
    // ...
}

void wins_test()
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
Weder der Verlierer noch der Gewinner dürfen weitere Positionen besetzen.
(Geheimtipp: Mit `return;` beendet man `void`-Funktionen.)
Endet das Spiel nach 9 Zügen ohne Sieger, soll `Unentschieden!` erscheinen.

### Aufgabe 7.3 Zufälliger Computergegner (klausurrelevant)

Kopiere die Funktion `aufgabe_7_2` in eine neue Funktion `aufgabe_7_3`.

Spieler `X` soll vom Computer gesteuert werden.
Schreibe dazu eine Funktion `dumbComputerMove`,
die einfach "zufällig" eine leere Position besetzt.
Mit `time(0) % 9` erhältst du eine "zufällige" Position von 0 bis 8.

Da `time(0)` nur einmal pro Sekunde eine neue (um 1 höhere) "Zufallszahl" liefert,
ist diese Funktion ungeeignet, falls man ständig neue "Zufallszahlen" braucht.
(Der Mensch könnte einfach absichtlich *n* Sekunden lang warten,
um eine "Zufallszahl" zu provozieren, die genau *n* höher ist als vorher.)
Nächste Woche werden wir bessere "Zufallszahlen"-Generatoren studieren!

### Aufgabe 7.4 Intelligenter Computergegner (klausurrelevant)

Kopiere die Funktion `aufgabe_7_3` in eine neue Funktion `aufgabe_7_4`.
Kopiere die Funktion `dumbComputerMove` in eine neue Funktion `smartComputerMove`.

Anstatt komplett "zufällig" zu agieren, soll der Computergegner folgende Prioritätenliste durchgehen:

1. Führt das Besetzen einer freien Position mit `X` zum Sieg des Computers? Dann wähle diese Position
2. Führt das Besetzen einer freien Position mit `O` zum Sieg des Menschen? Dann wähle diese Position
3. Wähle wie gehabt eine "zufällige" Position

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

## FAQ

### Wie fordere ich den Benutzer bei fachlich inkorrekten Eingaben erneut auf?

Hier ein Beispiel für die Eingabe von Zeichen, von denen nur 2 fachlich korrekt sind:

```c
char weinprobe()
{
    char wein;
    printf("Rot- oder Weisswein (r/w)? ");
    scanf(" %c", &wein);
    while (!(wein == 'r' || wein == 'w'))
    {
        printf("Rot- oder Weisswein (r/w)? ");
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
        printf("Rot- oder Weisswein (r/w)? ");
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
(In echten Umgebungen hat `zahl` den Wert, der zu dem Zeitpunkt im Arbeitsspeicher steht.)

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


void echo()
{
    int zahl = liesZahl("Bitte geben Sie eine Zahl ein: ");
    printf("Sie haben die Zahl %d eingegeben.\n", zahl);

    int zahl2 = liesZahl("Bitte geben Sie noch eine Zahl ein: ");
    printf("Sie haben noch eine Zahl %d eingegeben.\n", zahl2);
}
```
