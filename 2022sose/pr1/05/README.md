# Woche 5

## Aufgaben

### Aufgabe 5.1 Zahlenraten (Pflicht)

Schreibe eine Funktion `void aufgabe_5_1()` für das Spiel Zahlenraten.
Der Computer denkt sich dabei eine zufällige Zahl aus,
und der Mensch muss diese Zahl anschließend erraten.
Nach jedem Rateversuch antwortet der Computer wahrheitsgemäß, ob seine Zahl größer, kleiner oder gleich ist.
Falls sie gleich ist, wird das Spiel beendet.
Das ganze könnte z.B. wie folgt aussehen:
```
Ich habe mir eine Zahl zwischen 0 und 100 ausgedacht.
Welche Zahl mag es wohl sein?

10
Meine Zahl ist größer!

20
Meine Zahl ist kleiner!

12
Meine Zahl ist kleiner!

11
Herzlichen Glückwunsch, das ist meine Zahl!
```
(`10`, `20`, `12` und `11` sind Eingaben des Benutzers.)

Eine zeitabhängige "Zufallszahl" zwischen 0 und 100 kannst du mit `time(0) % 101` berechnen.

In Skorbut liefert `time(0)` die Anzahl Sekunden seit Mitternacht 1. Januar 1970.
Theoretisch könnte man statt `0` auch `&variable` schreiben (siehe `scanf`),
aber Skorbut unterstützt das noch nicht.

### Aufgabe 5.2 Rateversuche (Pflicht)

Kopiere die Funktion `void aufgabe_5_1()` in eine neue Funktion `void aufgabe_5_2()`.
Passe diese neue Funktion so an, dass der Spieler am Ende die Anzahl Rateversuche erfährt:
```
Herzlichen Glückwunsch, das ist meine Zahl!
Sie haben 4 Rateversuche gebraucht.
```

### Aufgabe 5.3 Rollentausch (Kür)

Diesmal denkt der Mensch sich eine Zahl aus, und der Computer errät sie:

```
Soso, Sie haben sich also eine Zahl zwischen 0 und 100 ausgedacht...

Ist es die 50? +

Ist es die 75? -

Ist es die 62? -

Ist es die 56? +

Ist es die 59? =

Geschafft, und das mit gerade mal 5 Rateversuchen!
```
(`+`, `-`, `-`, `+` und `=` sind Eingaben des Benutzers.)

Zum Einlesen eines Zeichens gibt es grundsätzlich 3 Möglichkeiten:
- `char x = getchar();`
- `scanf("%c", &y);`
- `scanf(" %c", &z);`

Die dritte Möglichkeit überspringt führende Leerzeichen/Zeilenumbrüche.

### Aufgabe 5.4 Oberlehrer (Kür)

Kopiere die Funktion `void aufgabe_5_2()` in eine neue Funktion `void aufgabe_5_4()`.
Bei unsinnigen Rateversuchen soll der Computer den Menschen behleren:
```
Ich habe mir eine Zahl zwischen 0 und 100 ausgedacht.
Welche Zahl mag es wohl sein?

10
Meine Zahl ist größer!

9
Sie wissen doch bereits, dass die Zahl mindestens 11 ist!

200
Sie wissen doch bereits, dass die Zahl höchstens 100 ist!
```
