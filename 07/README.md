# Woche 7

📺 https://www.youtube.com/watch?v=rdqXySFCvcQ

## Aufgaben

### Aufgabe 7.0 Hübsches Spielfeld (abnahmepflichtig & klausurrelevant)

```c
void zeigeSpielfeld(const char spielfeld[9])
{
    printf("%c%c%c\n%c%c%c\n%c%c%c\n",
        spielfeld[0], spielfeld[1], spielfeld[2],
        spielfeld[3], spielfeld[4], spielfeld[5],
        spielfeld[6], spielfeld[7], spielfeld[8]);
}

void ticTacToe()
{
    zeigeSpielfeld("O  XO XXO");
}
```

Obiges Programm schreibt ein optisch ernüchterndes Spielfeld auf die Konsole:

```
O  
XO 
XXO
```

Ändere die Funktion `zeigeSpielfeld`, so dass sie stattdessen Folgendes auf die Konsole schreibt:

```
 O |   |   
---+---+---
 X | O |   
---+---+---
 X | X | O 
```

### Aufgabe 7.1 Tic Tac Toe unentschieden (abnahmepflichtig & klausurrelevant)

Die ersten 2 Züge einer Partie Tic Tac Toe könnten wie folgt aussehen:

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

Vervollständige die Funktion `menschlicherZug`, die den Spieler nach einer Position fragt
und diese anschließend mit seinem Zeichen besetzt:

```c
void menschlicherZug(char spielfeld[9], char spieler)
{
    // Was muss auf die Konsole geschrieben werden, damit der aktuelle Spieler versteht,
    // dass er jetzt dran ist und etwas eingeben soll?
    printf(...);

    char eingabe;
    scanf(" %c", &eingabe);
    int position = eingabe - '0';

    // Was muss sich im Arbeitsspeicher ändern, damit die Position besetzt ist?
    // Wie verändert man einen String ganz allgemein? Und konkret für unseren Fall:
    // - welcher String?
    // - welche Position?
    // - welches neue Zeichen?
    ...
}

void ticTacToe()
{
    // Veranschaulicht die möglichen Positionen
    zeigeSpielfeld("012345678");
    
    // Initialisierung mit geschweiften Klammern ist hier lesbarer als  "         "
    char spielfeld[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    // Außerdem spart man sich so den ausnahmsweise nicht benötigten NUL-Terminator
    
    menschlicherZug(spielfeld, 'X');
    zeigeSpielfeld(spielfeld);
    
    menschlicherZug(spielfeld, 'O');
    zeigeSpielfeld(spielfeld);
}
```

- Erweitere das Programm anschließend von 2 auf 9 Spielzüge
  - Gewinnen kann man in dieser Version noch nicht, das "Spiel" geht immer unentschieden aus
- Die Qualitätskontrolle findet 2 Probleme in deinem Programm:
  1. Wenn man ein Zeichen außerhalb von `0` bis `8` eingibt (z.B. `9` oder `/`), stürzt das Programm ab
  2. Man kann bereits besetzte Position erneut besetzen, das verstößt gegen die Spielregeln
- Beim Beheben beider Probleme helfen die [FAQs](#faq)

### Aufgabe 7.2 Tic Tac Toe gewinnbar (abnahmepflichtig & klausurrelevant)

Vervollständige die Funktion `hatVolleReihe`, die prüfen soll,
ob der Spieler eine komplette Zeile, Spalte oder Diagonale voll hat:

```c
//             0      1      int
typedef enum { false, true } bool;

bool hatVolleReihe(const char spielfeld[9], char spieler)
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

void hatVolleReihe_test()
{
    assert(   hatVolleReihe("XXX      ", 'X') );
    assert( ! hatVolleReihe(" OOO     ", 'O') );
    assert( ! hatVolleReihe("  XXX    ", 'X') );
    assert(   hatVolleReihe("   OOO   ", 'O') );
    assert( ! hatVolleReihe("    XXX  ", 'X') );
    assert( ! hatVolleReihe("     OOO ", 'O') );
    assert(   hatVolleReihe("      XXX", 'X') );

    assert(   hatVolleReihe("O  O  O  ", 'O') );
    assert(   hatVolleReihe(" X  X  X ", 'X') );
    assert(   hatVolleReihe("  O  O  O", 'O') );

    assert(   hatVolleReihe("X   X   X", 'X') );
    assert(   hatVolleReihe("  O O O  ", 'O') );
}
```

Rufe `hatVolleReihe` an passenden Stellen in `ticTacToe` auf und reagiere sinnvoll auf das Ergebnis,
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

- Wenn ein Spieler gewonnen hat, ist das Spiel vorbei
  - Weder Verlierer noch Gewinner dürfen dann noch weitere Positionen besetzen
  - **Tipp:** Mit `return;` beendet man eine `void`-Funktion
- Endet das Spiel nach 9 Zügen ohne Sieger, soll `Unentschieden!` erscheinen

### Aufgabe 7.3 Zufälliger Computergegner (klausurrelevant)

- Kopiere die Funktion `ticTacToe` in eine neue Funktion `ticTacToeLeicht`
- Einer der Spieler soll vom Computer gesteuert werden und der andere Spieler vom Menschen
- Rufe für den Menschen weiterhin die bereits existerende Funktion `menschlicherZug` auf
- Rufe für den Computer eine neue Funktion `zufaelligerZug` auf, die irgendeine freie Position besetzt

### Aufgabe 7.4 Schlauer Computergegner (klausurrelevant)

- Kopiere die Funktion `ticTacToeLeicht` in eine neue Funktion `ticTacToeSchwer`
- Rufe für den Computer eine neue Funktion `schlauerZug` auf, die folgende Prioritätenliste durchgeht:
  1. Kann der Computer durch Besetzen einer freien Position gewinnen? Dann besetze diese Position
  1. Könnte der Mensch durch Besetzen einer freien Position gewinnen? Dann besetze diese Position
  3. Besetze ansonsten irgendeine freie Position

```c
void schlauerZug_test()
{
    char gewinnbar[] = "OO XX    ";
    schlauerZug(gewinnbar, 'X');
    assert(strcmp("OO XXX   ", gewinnbar) == 0);

    char verlierbar[]= "OO  X   X";
    schlauerZug(verlierbar, 'X');
    assert(strcmp("OOX X   X", verlierbar) == 0);
}
```

**Tipp:** Beide "*Kann jemand durch Besetzen einer freien Position gewinnen?*"-Fragen sind jeweils durch schlichtes Ausprobieren beantwortbar:
1. Stein ablegen
2. `hatVolleReihe` aufrufen
3. Stein ggf. wieder entfernen

## FAQ

### Wie fordert man den Benutzer bei fachlich inkorrekten Eingaben erneut auf?

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
    while (!(wein == 'r' || wein == 'w'));

    return wein;
}
```

| Schleife     | Prüfung der Schleifenbedingung | Anzahl Schleifendurchläufe |
| ------------ | ------------------------------ | -------------------------- |
| `while`      | vor dem Schleifenrumpf         | mindestens 0               |
| `do`/`while` | nach dem Schleifenrumpf        | mindestens 1               |

### Kann man `!(wein == 'r' || wein == 'w')` vereinfachen?

Dank [Augustus De Morgan](https://de.wikipedia.org/wiki/De-morgansche_Gesetze) kann man die Negation in die Klammern reinziehen:

```c
    while (!(wein == 'r' || wein == 'w'))
    //     ¦      ¦¦     ¦¦      ¦¦
    while (  wein != 'r' && wein != 'w' )
```

Man beachte, dass nicht nur `==` zu `!=` wird, sondern auch `||` zu `&&`

### Welchen Sinn hat `typedef enum { false, true } bool;` ?

- C89 hat keinen Datentyp für Wahrheitswerte
- Stattdessen wird die Zahl 0 als *falsch* interpretiert und alle anderen Zahlen als *wahr*
  - Die 6 Vergleichsoperatoren liefern immer 0 bzw. 1
- Häufig leidet darunter die Lesbarkeit von Programmen:

```c
int istPrim(int zahl)
{
    if (zahl < 2)      return 0; // falsch
    if (zahl == 2)     return 1; // wahr
    if (zahl % 2 == 0) return 0; // falsch

    for (int teiler = 3; teiler * teiler <= zahl; teiler += 2)
    {
        if (zahl % teiler == 0) return 0; // falsch
    }
    return 1; // wahr
}
```

Wenn C89 einen Datentyp für Wahrheitswerte hätte, könnte man stattdessen schreiben:

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

- `false` bedeutet `0`
- `true` bedeutet `1`
- `bool` bedeutet `int`

Und genau das leistet `typedef enum { false, true } bool;` im Wesentlichen.

Die Bezeichnung `bool` (C99, C++, C#) bzw. `boolean` (Java, JavaScript)
geht auf den englischen Mathematiker, Logiker und Philosophen
[George Boole](https://de.wikipedia.org/wiki/George_Boole) (1815 - 1864) zurück.
