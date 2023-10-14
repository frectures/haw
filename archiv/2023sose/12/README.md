# Woche 12

## Aufgaben

### Aufgabe 12.1 Fehlerbehandlung (abnahmepflichtig & klausurrelevant)

Wahrscheinlich sind dir letzte Woche links unten 3 Diagnostics aufgefallen:

1. function `ausrechnen` does not return a result on all code paths
2. function `zahl_oder_klammern` does not return a result on all code paths
3. function `klammern` does not return a result on all code paths

Alle drei Funktionen liefern nur ein Ergebnis zurück, sofern die Formel fehlerfrei ist.
Ansonsten stürzt Skorbut mit der Fehlermeldung `missing return statement` ab.
Außerhalb von Skorbut würden die 3 Funktionen zufälligen Speichermüll zurückliefern 😱

In Aufgabe 9.2 haben wir gelernt, wie Funktionen mit potenziell fehlerhaften Eingaben umgehen:
Anstatt das eigentliche Ergebnis zurückzuliefern, liefern sie einen Wahrheitswert zurück
und befüllen ggf. das eigentliche Ergebnis über einen zusätzlichen Zeigerparameter:

```c
bool ausrechnen(const char* formel, double* result);
bool strichrechnen(double* result);
bool punktrechnen(double* result);
bool zahl_oder_klammern(double* result);
bool zahl(double* result);
bool klammern(double* result);
```

Nimm diese Änderungen vor und reagiere an *allen* Aufrufstellen sinnvoll auf den `bool`;
Die Funktion `formelrechner` soll bei fehlerhaften Formeln eine Fehlermeldung anzeigen.
(Beim Anpassen der Tests kannst du dich an Aufgabe 9.2 `ausrechnen_test` orientieren;
oder du kommentierst die Tests vorübergehend aus, bis alles andere wieder läuft.)

**SPOILER 1** Die angepasste Funktion `ausrechnen` könnte z.B. wie folgt aussehen:

```c
obby nhferpuara(pbafg pune* sbezry, qbhoyr* erfhyg)
{
    c = sbezry;

    // Fpurvgreg orervgf qnf Fgevpuerpuara?
    // Qnaa fpurvgreg qnf Nhferpuara rorasnyyf:
    vs (fgevpuerpuara(erfhyg) == snyfr) erghea snyfr;

    // Jheqr qvr trfnzgr Sbezry xbzcyrgg xbafhzvreg?
    erghea *c == 0;
}
```

Bovtr Snyyhagrefpurvqhat mvrug fvpu fb äuayvpu nhpu qhepu nyyr naqrera Shaxgvbara:
Fbonyq qvr nhstrehsrar Shaxgvba fpurvgreg, fpurvgreg qre Nhsehsre rorasnyyf.

**SPOILER 2** In `strichrechnen` und `punktrechnen` kann man das reingereichte `result`
nicht einfach für *beide* Operanden (links und rechts vom Operator) verwenden,
weil qre mjrvgr Bcrenaq fbafg qra refgra Bcrenaq üorefpuervora jüeqr,
oribe qre Bcrengbe qvr orvqra Bcrenaqra zvgrvanaqre ireerpuara xnaa.
Süe qra mjrvgra Bcrenaq zhff zna nyfb rvar rvtrar Inevnoyr qrsvavrera!

### Aufgabe 12.2 Hallo C

- Besuche https://godbolt.org im Browser
- Wähle C als Sprache
- Tippe im linken Bereich der Webseite folgendes Programm ab:

```c
#include <stdio.h>  // für printf

int main()
{
    printf("Hallo C\n");
    return 0;
}
```

- Im rechten Bereich der Webseite sollte `Hallo C` erscheinen
- Wie unterscheidet sich obiges Programm optisch von deinen bisherigen Skorbut-Programmen?

**Optional** für macOS- oder Linux-Nutzer:

- Speichere obiges Programm in einer Datei namens `hallo.c` in deinem Benutzerverzeichnis ab
- Starte ein Terminal
- Kompiliere das Programm mittels `cc hallo.c`
- Starte das Programm mittels `./a.out`

### Aufgabe 12.3 Hallo C++

- Besuche https://godbolt.org im Browser
- Wähle C++ als Sprache
- Tippe im linken Bereich der Webseite folgendes Programm ab:

```cpp
#include <iostream>  // für std::cout

int main()
{
    std::cout << "Hallo C++\n";
}
```

- Im rechten Bereich der Webseite sollte `Hallo C++` erscheinen
- Wie unterscheidet sich obiges Programm optisch von 12.2 Hallo C?

### Aufgabe 12.4 Formelrechner C++

Die bisherige Realisierung des Formelrechners in C demonstriert mehrere Schwächen der Sprache:

1. Die Fehlerbehandlung mittels `bool` und `double*` ist nervig und invasiv;
selbst `strichrechnen` und `punktrechnen` mussten angepasst werden,
um Fehler aus `zahl_oder_klammern` zu propagieren
2. Die wechselseitige Rekursion erfordert zwingend Funktions-Deklarationen
3. Die Variable `const char* p` könnte versehentlich überall verwendet werden
4. Die Hauptfunktion `ausrechnen` ruft eine handvoll Hilfsfunktionen auf,
die versehentlich überall aufgerufen werden könnten

Die erste Schwäche löst C++ mit *Ausnahmen* (engl. *exceptions*), die letzten drei mit *Klassen*.
Die Punkte 3 und 4 (Kapselung) mögen im ersten Semester paranoid wirken,
spielen aber für langlebige, wartbare Software eine wichtige Rolle!

Füge folgendes Programm auf https://godbolt.org ein
und ergänze deine Erweiterungen des Formelrechners von letzter Woche:

```cpp
#include <iostream>   // für std::cout
#include <stdexcept>  // für std::invalid_argument
#include <string>     // für std::string

class Formelrechner
{
    const char* p;

    double strichrechnen()
    {
        double ergebnis = punktrechnen();
        for (;;)
        {
            switch (*p)
            {
                case '+':
                ++p;
                ergebnis = ergebnis + punktrechnen();
                break;

                case '-':
                ++p;
                ergebnis = ergebnis - punktrechnen();
                break;

                default:
                return ergebnis;
            }
        }
    }

    double punktrechnen()
    {
        double ergebnis = zahl_oder_klammern();
        while (*p == '*')
        {
            ++p;
            ergebnis = ergebnis * zahl_oder_klammern();
        }
        return ergebnis;
    }

    double zahl_oder_klammern()
    {
        switch (*p)
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            return zahl();

            case '(':
            return klammern();

            default:
            throw std::invalid_argument("erwarte Zahl oder ( statt " + std::string{*p});
        }
    }

    double zahl()
    {
        return *p++ - '0';
    }

    double klammern()
    {
        ++p;
        double ergebnis = strichrechnen();
        if (*p == ')')
        {
            ++p;
            return ergebnis;
        }
        throw std::invalid_argument("erwarte ) statt " + std::string{*p});
    }

public:

    double ausrechnen(const char* formel)
    {
        p = formel;
        double ergebnis = strichrechnen();
        if (*p == '\0') return ergebnis;
        throw std::invalid_argument("unverarbeitete Eingabe " + std::string(p) + " nach " + std::string(formel, p));
    }
};

void rechnen(const char* formel)
{
    Formelrechner rechner;
    try
    {
        double ergebnis = rechner.ausrechnen(formel);
        std::cout << formel << " = " << ergebnis << "\n";
    }
    catch (std::invalid_argument fehler)
    {
        std::cout << formel << ": " << fehler.what() << "\n";
    }
}

int main()
{
    rechnen("1");
    rechnen("1+2");
    rechnen("1+2+3");
    rechnen("3-2-1");
    rechnen("2*3");
    rechnen("2*3*7");
    rechnen("2*3+4");
    rechnen("2+3*4");
    rechnen("2*3+4*5");
    rechnen("2*(3+4)*5");
    rechnen("2+3*4+5");
    rechnen("(2+3)*(4+5)");
    std::cout << "\n";
    rechnen("1+a");
    rechnen("(1+2");
    rechnen("1+2a");
}
```

## FAQ

### Was bedeutet `#include <stdio.h>` ?

- In Skorbut sind Standard-Funktionen wie `printf` und `scanf` einfach so magisch vorhanden
- Außerhalb von Skorbut muss man `#include <stdio.h>` schreiben, um `printf` und `scanf` nutzen zu können
- In der Datei `stdio.h` befinden sich u.a. Funktions-Deklarationen für `printf` und `scanf`
- `stdio` steht für "`st`an`d`ard `i`nput/`o`utput", und die Dateiendung `.h` für "`h`eader"

### Auf welche Header-Dateien verteilen sich die magischen Funktionen von Skorbut?

- `<stdio.h>`
  - printf
  - scanf
  - puts
  - putchar
  - getchar
- `<string.h>`
  - strlen
  - strcmp
- `<stdlib.h>`
  - malloc
  - free
  - realloc
  - qsort
  - bsearch
- `<math.h>`
  - pow
- `<time.h>`
  - time

### Was hat es mit der `main`-Funktion auf sich?

- Die Programm-Ausführung startet in der `main`-Funktion
- In Skorbut kann man jede `void funktion()` starten
  - Außerhalb von Skorbut geht das *nicht*!

### Warum liefert die `main`-Funktion einen `int`?

- Damit signalisiert die `main`-Funktion dem Betriebssystem, ob das Programm normal beendet wurde (`0`) oder nicht (irgendein anderer Wert)
- Das ist primär beim Ausführen mehrerer Programme hintereinander relevant:
  - `C:\Users\fred> a.exe && b.exe && c.exe`
  - Wenn `a.exe` 0 liefert, wird `b.exe` ausgeführt
  - Wenn `b.exe` 0 liefert, wird `c.exe` ausgeführt
  - Liefert ein Programm einen anderen Wert als `0`, werden die folgenden Programme nicht mehr ausgeführt

### Warum fehlt in 12.3 Hallo C++ das `return 0;` am Ende von `main`?

- Das ist eine Spezialregel von C++
- Wenn das `return 0;` am Ende von `main` fehlt, wird implizit `0` zurückgegeben
  - Für andere Funktionen als `main` gilt diese Spezialregel *nicht*!

### Ist C++ klausurrelevant?

Nein.

![](bjarne.jpg)
