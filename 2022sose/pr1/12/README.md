# Woche 12

## Aufgaben

### Aufgabe 12.1 (Pflicht)

Das Umdrehen von Strings benötigt eigentlich kein zweites, temporäres Array,
aber mit einem solchen ist das Vorgehen evtl. leichter nachvollziehbar.

Implementiere die Funktion `reverse(char s[])` mit einem dynamischen Array:
1. Fordere das dynamische Array an
2. Kopiere alle Zeichen aus `s` in das dynamische Array
3. Kopiere alle Zeichen aus dem dynamischen Array rückwärts nach `s`
4. Gib das dynamische Array frei

```c
void reverse(char s[])
{
    // ...
}

void aufgabe_12_1()
{
    char a[] = "regal";
    reverse(a);
    assert(strcmp(a, "lager") == 0);
}
```

### Aufgabe 12.2 (Pflicht)

Normalerweise muss man beim Einlesen von Strings die maximale Länge festlegen:

```c
char name[10];
scanf("%9s", name);
```

Zum Einlesen beliebig langer Strings braucht man dynamisch "wachsende" Arrays:
- Fordere ein kleines, dynamisches Array an
- Lies per `getchar()` in einer Schleife ein Zeichen nach dem anderen ein und speichere es in dem Array
- Jedes Mal, wenn die Kapazität erschöpft ist, verschiebe die Elemente in ein größeres, dynamisches Array
- Sobald das eingelesene Zeichen ein Zeilenumbruch ist, ist die Zeile komplett

Implementiere dieses Vorgehen in der Funktion `readLine`:

```c
char *readLine()
{
    // ...
}

void aufgabe_12_2()
{
    printf("Wie lautet dein Name? ");
    char *name = readLine();
    printf("Herzlich willkommen, %s!\n", name);
    free(name);
}
```

### Aufgabe 12.3 (Kür)

Implementiere die Funktion `char *sieve(int bound)`,
die einen String der Länge `bound` zurückliefert.
An jeder Position `i` dieses Strings ist per `P` (Prime) oder `C` (Compound) markiert,
ob `i` eine Primzahl oder eine zusammengesetzt Zahl ist.
(Für die Positionen 0 und 1 ist egal, was du reinschreibst.)
Verwende dazu das [Sieb des Eratosthenes](https://de.wikipedia.org/wiki/Sieb_des_Eratosthenes).

```c
char *sieve(int bound)
{
    // ...
}

void aufgabe_12_3()
{
    char *s = sieve(20);
    //            _____   23 5 7  1113  1719
    assert(strcmp(s + 2, "PPCPCPCCCPCPCCCPCP"));
    free(s);
}
```

### Aufgabe 12.4 (Kür)

Implementiere die Funktion `int *primes(int bound)`,
die alle Primzahlen kleiner als `bound` zurückliefert.
Da der Aufrufer nicht wissen kann, wie viele solcher Primzahlen existieren,
soll das Ende des Arrays *explizit* mit der unsinnigen "Primzahl" 0 markiert werden.
(Normalerweise haben `int`-Arrays keinen solchen Terminator, im Gegensatz zu Strings.)

```c
int *primes(int bound)
{
    // ...
}

void aufgabe_12_4()
{
    int *p = primes(20);

    assert(p[0] ==  2);
    assert(p[1] ==  3);
    assert(p[2] ==  5);
    assert(p[3] ==  7);
    assert(p[4] == 11);
    assert(p[5] == 13);
    assert(p[6] == 17);
    assert(p[7] == 18);

    assert(p[8] == 0);
    free(p);
}
```

Es empfiehlt sich, `sieve` aufzurufen und den gelieferten String (z.B. `"..PPCPCPCC"`)
in das entsprechende `int`-Array (z.B. `{2, 3, 5, 7, 0}`) umzuwandeln.

## FAQ

### Welches Problem lösen dynamische Arrays?

Die Größe von normalen Arrays muss dem Compiler bekannt sein:

```c
void stackArray()
{
    printf("How many numbers? ");
    int n;
    scanf("%d", &n);
    int a[n]; // error: array size must be a compile-time constant
    // ...
}
```

Wenn die Größe erst zur Laufzeit feststeht, verwendet man dynamische Arrays:

```c
void heapArray()
{
    printf("How many numbers? ");
    int n;
    scanf("%d", &n);
    int *a = malloc(n * sizeof(int));
    // ...
    free(a);
}
```

### Was bedeutet `free(a);`?

Damit wird der Speicher, der von `malloc` angefordet wurde, wieder freigegeben.
Mangels Garbage Collection muss der Programmierer das von Hand erledigen,
sobald das dynamische Array nicht mehr benötigt wird.

### Was passiert, wenn man `free(a);` vergisst?

Dann wird der Speicher erst am Ende des Programms durch das Betriebssystem freigegeben.
Das ist meist schlechter Stil, weshalb Skorbut fehlende `free`s mit einer Fehlermeldung quittiert.

### Was passiert, wenn man `a` selber mittels `free(&a);` freigibt?

Das ist illegal.
Man darf nur Zeiger an `free` übergeben, die von `malloc` (oder `realloc`) stammen.
Wie jede andere lokale Variable auch wird `a` selber am Ende der Funktion automatisch abgeräumt.

### Kann man ein dynamisches Array im Nachhinein vergrößern?

Nein, aber man kann die Elemente in ein größeres dynamisches Array umkopieren:

```c
int *p = malloc(10 * sizeof(int));
// ...
p = realloc(p, 20 * sizeof(int));
// ...
p = realloc(p, 40 * sizeof(int));
// ...
p = realloc(p, 80 * sizeof(int));
// ...
free(p);
```

### Wie findet man heraus, wie groß ein dynamisches Array ist?

Das kann man nicht herausfinden.
Die "Kapazität" eines dynamischen Arrays muss man bei Bedarf in einer separaten Variable mitpflegen.

### Wie findet man heraus, wie viele Elemente eines dynamischen Arrays bereits in Benutzung sind?

Das kann man nicht herausfinden.
Die "Kardinalität" eines dynamischen Arrays muss man bei Bedarf in einer separaten Variable mitpflegen.
