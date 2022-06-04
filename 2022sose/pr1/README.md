# PR1 Sommersemester 2022

## Laborprüfung

Laut Silke wurde die Laborprüfung am 22. Juli auf 12:00 Uhr verschoben.

### Welche Aufgabenblätter sind die prüfungsrelevantesten?

Blatt 6 und Blatt 10; Strings solltest du im Schlaf untersuchen und verändern können!

### Hinweise aus der echten Laborprüfung

- Bitte starten Sie Skorbut *nicht* mehrfach gleichzeitig!
  - Rechtsklick auf `skorbut.jar` gefolgt von Linksklick auf `Öffnen` startet Skorbut garantiert nur einmal
  - Dagegen wird ein Doppelklick zum Starten versehentlich gerne ein Dreifach- oder Vierfachklick
  - Mit Alt+Tab können Sie durch die geöffneten Anwendungen wechseln und so sicherstellen, dass Skorbut wirklich nur einmal läuft
- Zu jeder Aufgaben-Funktion `f` ist eine zugehörige Test-Funktion `void f_test()` abgedruckt
  - Diese Test-Funktionen dienen primär der präzisen Spezifikation der Aufgabe
  - Ob Sie diese Test-Funktionen komplett, teilweise oder gar nicht abtippen, ist Ihnen überlassen

**Beispiel:** Implementieren Sie die Funktion `hexValue`:

```c
int hexValue(char digit)
{
    // ...
}

void hexValue_test()
{
    assert(hexValue('0') ==  0);
    assert(hexValue('1') ==  1);
    assert(hexValue('2') ==  2);
    assert(hexValue('3') ==  3);
    assert(hexValue('4') ==  4);
    assert(hexValue('5') ==  5);
    assert(hexValue('6') ==  6);
    assert(hexValue('7') ==  7);
    assert(hexValue('8') ==  8);
    assert(hexValue('9') ==  9);
    
    assert(hexValue('a') == 10);
    assert(hexValue('b') == 11);
    assert(hexValue('c') == 12);
    assert(hexValue('d') == 13);
    assert(hexValue('e') == 14);
    assert(hexValue('f') == 15);
}
```

- Keine der Aufgaben-Funktionen soll auf die Konsole schreiben oder von der Konsole lesen
  - Wenn Sie `printf` oder `scanf` verwenden, sind Sie auf dem Holzweg!
- Jede Warnung in Skorbuts `diagnostics`-Reiter links unten führt zu Punktabzug
  - zum Beispiel unbenutzte Variablen, fehlende `return`-Anweisungen oder wirkungslose Anweisungen
  - Studieren Sie diese Warnungen aufmerksam!
  - Ein Mausklick auf die Warnung führt zur entsprechenden Stelle im Programm

### Muss ich den ASCII-Code auswendig lernen?

- `'a'` hat z.B. den ASCII-Code `97`
- Musst du das wissen, um `97` an einer passenden Stelle im Programm hinzuschreiben?
- Nein, schreib doch einfach `'a'` statt `97` hin, denn `'a'` *ist* `97`

### Was mache ich, wenn ich die `for`-Scheife vergesse?

Verwende stattdessen eine `while`-Schleife:

```c
int i = 0;
while (i < 10)
{
    printf("%d ist eine Ziffer\n", i);
    ++i;
}
```

Obige `while`-Schleife verhält sich bekanntlich wie folgende `for`-Schleife:

```c
for (int i = 0; i < 10; ++i)
{
    printf("%d ist eine Ziffer\n", i);
}
```

### Was mache ich, wenn ich die `strlen`-Funktion vergesse?

- Nutze die Autokorrektur von Skorbut:
  - `void help() { string; }`
  - undeclared symbol `string`, best matches: `strcmp`, `strlen`
- Falls du die Signatur von `strlen` vergessen hast:
  - `void help() { strlen; }`
  - Links oben auf `syntax tree` klicken
  - `help : void()` aufklappen
  - `strlen;` aufklappen
  - `strlen : unsigned int(const char*)` ist die Signatur
- Derselbe Trick klappt auch mit anderen Funktionen:
  - `void help() { allocate; sort; }`

## Anspruch

- Ein Vollzeitstudium hat 30 CP pro Semester
- PR1 beansprucht davon 6 CP, also ein Fünftel
- Pro Woche sollte demnach ein kompletter Tag in PR1 investiert werden:
  - 3 Stunden Vorlesung
  - 4 Stunden **Aufgaben zu Hause bearbeiten und (weitestgehend) lösen**
  - 1 Stunde Praktikum: Letzter Feinschliff der Lösungen, dann abnehmen lassen
    - Alle 3 Wochen findet ein 3-stündiges Praktikum statt

## Praktika

- **Vorbereitung:** Die Aufgaben wurden zu Hause 4 Stunden lang bearbeitet und (weitestgehend) gelöst
  - 1 Stunde pro Woche wäre viel zu knapp für die Bearbeitung, Lösung und Abnahme!
- Für die Abnahme der Aufgaben finden sich jeweils 2 Teilnehmer zu Pärchen zusammen
- Ein Betreuer lässt sich die Lösungen abwechselnd von beiden Teilnehmern erklären und stellt Rückfragen
- Sobald der Betreuer mit den Lösungen, Erklärungen und Antworten zufrieden ist, wird die Aufgabe als abgenommen abgehakt
- Falls Abnahmen innerhalb eines Regeltermins nicht erfolgen:
  - 3 Wochen später direkt am Anfang abnehmen lassen
  - Oder beim nächsten Termin von Gruppe 3 (nur halb ausgelastet) abnehmen lassen
- Die erfolgreiche Abnahme aller 12 Wochen ist Voraussetzung für die Zulassung zur Laborprüfung

### Gruppe 3

- April 20: Abnahme der Wochen 1, 2, 3
- Mai 11: Abnahme der Wochen 4, 5, 6
- Juni 1: Abnahme der Wochen 7, 8, 9
- Juni 22: Abnahme der Wochen 10, 11, 12

### Gruppe 1

- April 27: Abnahme der Wochen 1, 2, 3
- Mai 18: Abnahme der Wochen 4, 5, 6
- Juni 8: Abnahme der Wochen 7, 8, 9
- Juni 29: Abnahme der Wochen 10, 11, 12

### Gruppe 2

- Mai 4: Abnahme der Wochen 1, 2, 3
- Mai 25: Abnahme der Wochen 4, 5, 6
- Juni 15: Abnahme der Wochen 7, 8, 9
- Juli 6: Abnahme der Wochen 10, 11, 12

## Literatur

Anfängern empfehle ich das Buch "Grundkurs C" von Jürgen Wolf und René Krooß.
Das Buch behandelt den aktuellen Sprachstandard C18.
In PR1 werden wir uns auf ANSI C89 bzw. ISO C90 beschränken.
Diesen ausgereiften Standard kann man im Prinzip aus jedem C-Buch lernen, das in den letzten 3 Jahrzehnten verfasst wurde.

**Achtung:** C wird häufig mit C++ oder C# verwechselt bzw. in einen Topf geschmissen.
Das sind zwar historisch verwandte und interessante, aber komplett andere Programmiersprachen.
Aus einem C++ Buch oder C# Buch kann man C *nicht* lernen!
