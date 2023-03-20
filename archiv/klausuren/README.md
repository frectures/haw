# Klausurhinweise

### Wie wird die Klausur konkret ablaufen?

Ihr sitzt an einem Labor-Rechner (ohne Internet-Zugang) und programmiert C in Skorbut.

### Wie kann man sich die Aufgaben vorstellen?

Ganz ähnlich wie in den letzten 10 Wochen: Pro Aufgabe eine leere Funktion,
die ihr implementieren sollt, mit kurzer Beschreibung sowie zugehörigem Test.

### Wenn alle Test-Assertions durchlaufen, kriege ich dann die volle Punktzahl?

Nein! So mancher Schlaumeier transformiert die Test-Assertions stumpf in `if`/`return`-Pärchen:

```c
// AUFGABE B (2 Punkte)
// Summiert die ASCII-Codes aller Zeichen

// EXERCISE B (2 points)
// Sums the ASCII codes of all characters

int hashSum(const char* s)
{
    if (s[0] == '\0') return 0;

    if (s[0] == 'A' && s[1] == '\0') return 65;

    if (s[0] == 'B' && s[1] == 'C' && s[2] == '\0') return 'B'+'C';

    if (s[0] == 'D' && s[1] == 'E' && s[2] == 'F' && s[3] == '\0') return 'D'+'E'+'F';
}

void hashSum_test()
{
    assert(hashSum("") == 0);
    assert(hashSum("A") == 65);
    assert(hashSum("BC") == 'B'+'C');
    assert(hashSum("DEF") == 'D'+'E'+'F');
}
```

Dafür gibt es 0 Punkte *trotz* 100% durchgelaufener Test-Assertions.
Die Tests sollen euch beim Finden von Bugs helfen und sind *keine* erschöpfende Spezifikation;
diese befindet sich als Kommentar über dem Funktionskopf:

> Summiert die ASCII-Codes aller Zeichen

Das muss für *alle* Strings funktionieren und nicht bloß für die getesteten Beispiele!

### Sollen die Funktionen mit dem Benutzer interagieren?

Nein, auf gar keinen Fall!
Wenn ihr `printf` oder `scanf` verwendet, seid ihr auf dem Holzweg!

Alle benötigten Informationen kommen über Funktions-Parameter hinein,
und das Ergebnis wird entweder per `return`-Anweisung zurückgeliefert 
oder mittels Zeiger-Parameter in Variablen des Aufrufers geschrieben.

### Welche Wochen sind die klausurrelevantesten?

Woche 6 und Woche 10; Strings solltet ihr im Schlaf untersuchen und verändern können!

### Wird während der Klausur das Skript zur Verfügung gestellt?

Ja, eine große PDF-Datei mit allen FAQs der Wochen 3 bis 12 wird auf dem Desktop liegen.

### Dürfen wir eigene Notizen zur Klausur mitbringen?

Ihr dürft 1 DIN-A4-Blatt (beidseitig) **!!! HANDSCHRIFTLICH !!!** beschrieben mitbringen.

(Erfahrungsgemäß bringt das aufgrund der vollständig zur Verfügung gestellten FAQs aber wenig.)
