# Woche 10

## Aufgaben

### Aufgabe 10.1 Wanderzeiger (abnahmepflichtig & klausurrelevant)

In Woche 6 hatten wir gelernt, über Strings zu schleifen:

```c
void schleifeUeberAlleZeichen(const char s[])
{
    for (int i = 0; s[i]; ++i)
    {
        printf("Das Zeichen %c hat den ASCII-Code %d\n", s[i], s[i]);
    }
}
```

Da der scheinbare Array-Funktionsparameter `(const char s[])`
in Wirklichkeit ein Zeiger-Funktionsparameter `(const char* s)` ist,
kann man sich die Schleifenvariable `i` auch schenken:

```c
void schleifeUeberAlleZeichen(const char* s)
{
    for (; *s; ++s)
    {
        printf("Das Zeichen %c hat den ASCII-Code %d\n", *s, *s);
    }
}
```

Nimm entsprechende Vereinfachungen für folgende 4 Funktionen aus Woche 6 vor:
- 6.0 `void verschluesseln(char s[])`
- 6.1 `int findeZeichen(const char s[], char c)`
  - Zeiger in Position konvertieren? siehe [vorletzte FAQ](#man-kann-mit-zeigern-rechnen)
- 6.1 `int zaehleZeichen(const char s[], char c)`
- FAQ `int strcmp(const char s[], const char t[])`

### Aufgabe 10.2 Gemüse-Quiz (abnahmepflichtig & klausurrelevant)

```c
const char englisch[18][12] =
{
    "asparagus",
    "cabbage",
    "cauliflower",
    "celery",
    "corn",
    "fennel",
    "garlic",
    "ginger",
    "kale",
    "lettuce",
    "nettles",
    "onion",
    "parsley",
    "parsnip",
    "peanut",
    "potato",
    "radish",
    "turnip",
};

const char deutsch[18][12] =
{
    "Spargel",
    "Kohl",
    "Blumenkohl",
    "Sellerie",
    "Mais",
    "Fenchel",
    "Knoblauch",
    "Ingwer",
    "Grünkohl",
    "Kopfsalat",
    "Brennnessel",
    "Zwiebel",
    "Petersilie",
    "Pastinake",
    "Erdnuss",
    "Kartoffel",
    "Radieschen",
    "Rübe",
};

void gemueseQuiz()
{
    srand(time(0));

    int index = rand() % 18;
    printf("Wie heißt %s auf Deutsch? ", englisch[index]);

    char eingabe[100];
    scanf("%99s", eingabe);

    if (strcmp(eingabe, deutsch[index]) == 0)
    {
        printf("Korrekt!\n");
    }
    else
    {
        printf("Leider falsch... %s heißt %s auf Deutsch!\n", englisch[index], deutsch[index]);
    }
}
```

- Obiges Gemüse-Quiz ist leider sehr penibel, was Groß- und Kleinschreibung angeht
  - “Fenchel” wird z.B. akzeptiert, aber “fenchel” nicht
- Ersetze `strcmp` durch eine neue Funktion `strcmpIgnoreCase`, die Groß- und Kleinschreibung ignoriert
  - Studiere dazu die Lage der Groß- und Kleinbuchstaben im ASCII-Code

### Aufgabe 10.3 Gemüse-Lexikon (abnahmepflichtig & klausurrelevant)

Schreibe eine neue Funktion `gemueseLexikon`, die eingegebene Wörter übersetzt:

```
Welches Wort möchten Sie übersetzen? corn
corn heißt Mais auf Deutsch.

Welches Wort möchten Sie übersetzen? Mais
Mais heißt corn auf Englisch.

Welches Wort möchten Sie übersetzen? Korn
Korn kenne ich nicht!
```

### Aufgabe 10.4 Quiz-Feinschliff (klausurrelevant)

- Das Gemüse-Quiz soll nicht nur 1 Gemüse abfragen, sondern 10 hintereinander
- Am Ende soll der Spieler eine Bewertung zwischen 0% und 100% erhalten
- Kein Gemüse soll doppelt abgefragt werden

## FAQ

### Sind Arrays eigentlich Zeiger?

**Nein**, aber Arrays werden bei ihrer Verwendung häufig in Zeiger *konvertiert*:

> ANSI C89 §3.2.2.1
>
> Except when it is
> - the operand of the `sizeof` operator
> - or the unary `&` operator,
> - or is a character `string literal` used to initialize an array of character type,
>
> a variable that has type “array of type” is converted to an expression that has type “pointer to type”
> that points to the initial member of the array and is not a variable.

Deshalb ist es zum Beispiel möglich, einen Zeiger mit einem Array zu initialisieren:

```c
char  a[] = "apfel";
char* z   = a; // z zeigt auf das erste Zeichen von a
```
```
  +-----+-----+-----+-----+-----+-----+
a | 'a' | 'p' | 'f' | 'e' | 'l' | '\0'|
  +-----+-----+-----+-----+-----+-----+
     ^
  +--|--+
z |&a[0]|
  +-----+
```

Zeiger können jederzeit auf andere Arrays umgebogen werden:

```c
char  b[] = "birne";
      z   = b;
```
```
  +-----+-----+-----+-----+-----+-----+
a | 'a' | 'p' | 'f' | 'e' | 'l' | '\0'|
  +-----+-----+-----+-----+-----+-----+

  +-----+
z |&b[0]|
  +--|--+
     v
  +-----+-----+-----+-----+-----+-----+
b | 'b' | 'i' | 'r' | 'n' | 'e' | '\0'|
  +-----+-----+-----+-----+-----+-----+
```

Arrays können dagegen niemals auf der linken Seite einer Zuweisung stehen:

```c
a = z;
 // char*
 //  cannot be converted to
 // char[6]

a = b;
 // char[6]
 //  cannot be converted to
 // char[6]
```

### Sind Array-Funktionsparameter eigentlich Zeiger-Funktionsparameter?

Ja, das ist eine **Sonderregel** für Funktionsparameter:

> ANSI C89 §3.7.1 **Function** definitions, Semantics
>
> A declaration of a **parameter** as “array of type” shall be adjusted to “pointer to type”

### Warum kann man dann nicht `char x[];` für einen Zeiger schreiben?

Weil lokale Variablen keine Funktionsparameter sind.
Funktionsparameter befinden sich zwischen den runden Klammern im Funktionskopf:

```c
void funktion(char parameter[]) // char* parameter
{
    char lokal[]; // missing array size or initializer
}
```

### Wenn Array-Funktionsparameter eigentlich Zeiger-Funktionsparameter sind, wieso klappt `parameter[i]` dann trotzdem?

- Nützliche Lüge:
  - Der Zugriff `x[i]` funktioniert sowohl direkt auf Arrays als auch indirekt über Zeiger
- Technische Wahrheit:
  - Der Zugriff `x[i]` funktioniert *ausschließlich* über Zeiger
  - Wenn `x` ein Array ist, wird gemäß §3.2.2.1 ein Zeiger auf das erste Element bereitgestellt
  - Tatsächlich ist `x[i]` nur syntaktischer Zucker für `*(x + i)`

### Man kann mit Zeigern *rechnen*?!

Ja, das ist recht nützlich für die Iteration über Strings und andere Arrays:

```c
int strlen(const char* s)
{
    const char* t = s;
    while (*t)
    {
        ++t;      // Zeiger-Inkrement
    }
    return t - s; // Zeiger-Differenz
}

void strlen_test()
{
    assert(strlen("") == 0);
    assert(strlen("I") == 1);
    assert(strlen("we") == 2);
    assert(strlen("you") == 3);
    assert(strlen("they") == 4);
}
```

### Was bedeutet `const` bei Zeigertypen?

Sowohl die gezeigte Variable `*p` als auch die Zeigervariable `p`
lassen sich mit `const` vor versehentlichen Änderungen schützen:

| West `const` Syntax | `*p = ...` | `p = ...` | East `const` Syntax |
| ------------------- | ---------- | --------- | ------------------- |
| `char*`             | ✔️         | ✔️       |                     |
| `const char*`       | ❌         | ✔️       | `char const*`       |
| `char* const`       | ✔️         | ❌       |                     |
| `const char* const` | ❌         | ❌       | `char const* const` |
