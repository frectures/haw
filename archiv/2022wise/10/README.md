# Woche 10

📺 Mit Zeiger-Arithmetik durch Arrays wandern: https://www.youtube.com/watch?v=Q_DKC3Am-c8

## Aufgaben

### Aufgabe 10.1 Leertasten zählen (abnahmepflichtig & klausurrelevant)

Implementiere die Funktion `countSpaces` zum Zählen von Leertasten.<br>
Verwende dazu ausschließlich [Zeiger-Arithmetik](#man-kann-mit-zeigern-rechnen),
also insbesondere *keine* `s[i]`-Syntax und *keine* Index-Variable `i`!

```c
int countSpaces(const char* s)
{
    // ...
}

void countSpaces_test()
{
    assert(countSpaces("") == 0);
    assert(countSpaces(" ") == 1);
    assert(countSpaces("  ") == 2);
    assert(countSpaces("hello world") == 1);
    assert(countSpaces("  to be or  not to be  ") == 10);
}
```

### Aufgabe 10.2 Leertasten entfernen (abnahmepflichtig & klausurrelevant)

Implementiere die Funktion `removeSpaces` zum Entfernen von Leertasten.<br>
Verwende dazu ausschließlich [Zeiger-Arithmetik](#man-kann-mit-zeigern-rechnen),
also insbesondere *keine* `s[i]`-Syntax und *keine* Index-Variable `i`!

```c
void removeSpaces(char* s)
{
    // ...
}

void removeSpaces_test()
{
    char a[] = "  If a woodchuck  could chuck wood  ";
    removeSpaces(a);
    assert(strcmp(a, "Ifawoodchuckcouldchuckwood") == 0);
}
```

### Aufgabe 10.3 Strings vergleichen (klausurrelevant)

Implementiere den `strcmp`-Klon `my_strcmp` zum Vergleichen von Strings.
Genau wie `strcmp(a, b)` soll `my_strcmp(a, b)` folgendes liefern:
- 0, falls in `a` genau die gleichen Zeichen hintereinander stehen wie in `b`
- *irgendeine* negative Zahl, falls `a` lexikographisch vor `b` liegt
- *irgendeine* positive Zahl, falls `a` lexikographisch nach `b` liegt

Verwende dazu ausschließlich [Zeiger-Arithmetik](#man-kann-mit-zeigern-rechnen),
also insbesondere *keine* `s[i]`-Syntax und *keine* Index-Variable `i`!

```c
int my_strcmp(const char* s, const char* t)
{
    // ...
}

void my_strcmp_test()
{
    assert(my_strcmp("apple", "apple") == 0);
    assert(my_strcmp("apple", "pear") < 0);
    assert(my_strcmp("pear", "apple") > 0);

    assert(my_strcmp("apple", "ape") > 0);
    assert(my_strcmp("ape", "apple") < 0);

    assert(my_strcmp("apple", "apply") < 0);
    assert(my_strcmp("apply", "apple") > 0);

    assert(my_strcmp("apple", "applepie") < 0);
    assert(my_strcmp("applepie", "apple") > 0);

    assert(my_strcmp("", "") == 0);
    assert(my_strcmp("", "a") < 0);
    assert(my_strcmp("a", "") > 0);
}
```

### Aufgabe 10.4 Präfix vorspulen (klausurrelevant)

In `my_strcmp` hast du wahrscheinlich eine Schleife geschrieben,
um zum ersten unterschiedlichen Buchstabenpaar "vorzuspulen":

```
+-----+-----+-----+-----+-----+-----+
| 'a' | 'p' | 'p' | 'l' | 'e' | '\0'|
+-----+-----+-----+-----+-----+-----+
               ^
            +--|--+
          s |  |  |
            +-----+

            +-----+
          t |  |  |
            +--|--+
               v
+-----+-----+-----+-----+
| 'a' | 'p' | 'e' | '\0'|
+-----+-----+-----+-----+
```

Extrahiere diese Schleife in eine eigene Funktion.

## FAQ

### Sind Arrays eigentlich Zeiger?

**Nein**, aber Arrays werden bei ihrer Verwendung häufig in Zeiger konvertiert:

> ISO C90 §3.2.2.1
>
> Except when it is
> - the operand of the `sizeof` operator
> - or the unary `&` operator,
> - or is a character `string literal` used to initialize an array of character type,
>
> a variable that has type *array of type* is converted to an expression that has type *pointer to type*
> that points to the initial member of the array object and is not a variable.

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

### Sind Array-Parameter eigentlich Zeiger-Parameter?

Ja, das ist eine **Sonderregel für Parameter** von Funktionen:

> ISO C90 §3.7.1 Function definitions, Semantics
>
> A declaration of a parameter as *array of type* shall be adjusted to *pointer to type*

```c
void funktion(char s[6], char t[], char* u)
{
    assert(sizeof s == sizeof(char*));
    assert(sizeof t == sizeof(char*));
    assert(sizeof u == sizeof(char*));
}

void sonderregel()
{
    char a[] = "apfel";
    assert(sizeof a == sizeof(char[6]));
    funktion(a, a, a);
}
```

```
  +-----+-----+-----+-----+-----+-----+
a | 'a' | 'p' | 'f' | 'e' | 'l' | '\0'|
  +-----+-----+-----+-----+-----+-----+
   ^ ^ ^
   | | |
   | | +---------+
   | |           |
   | +-----+     |
   |       |     |
  +|----+  |     |
s |&a[0]|  |     |
  +-----+  |     |
           |     |
        +--|--+  |
      t |&a[0]|  |
        +-----+  |
                 |
              +--|--+
            u |&a[0]|
              +-----+
```

### Warum kann ich dann nicht `char x[];` für einen Zeiger schreiben?

Weil lokale Variablen keine Parameter sind.
Parameter befinden sich zwischen den runden Klammern im Funktionskopf:

```c
void funktion(char parameter[]) // char* parameter
{
    char lokal[]; // missing array size or initializer
}
```

### Wenn Array-Parameter eigentlich Zeiger-Parameter sind, wieso klappt `parameter[i]` dann trotzdem?

- Nützliche Lüge:
  - Der Zugriff `x[i]` funktioniert sowohl direkt auf Arrays als auch indirekt über Zeiger
- Technische Wahrheit:
  - Der Zugriff `x[i]` funktioniert *ausschließlich* über Zeiger
  - Wenn `x` ein Array ist, wird gemäß §3.2.2.1 ein Zeiger auf das erste Element bereitgestellt
  - Tatsächlich ist `x[i]` nur syntaktischer Zucker für `*(x + i)`

### Man kann mit Zeigern *rechnen*?!

Ja, das ist recht nützlich für die Iteration über Strings und andere Arrays:

```c
void zensiereZiffern(char* s)
{
                /// Zeiger-Inkrement
    for (; *s; ++s)
    {
        if (*s >= '0' && *s <= '9')
        {
            *s = 'X';
        }
    }
}

void zensiereZiffern_test()
{
    char a[] = "Meine PIN ist 1234, und meine Telefonnummer ist 0123 / 456 78 90";
    zensiereZiffern(a);
    assert(strcmp(a, "Meine PIN ist XXXX, und meine Telefonnummer ist XXXX / XXX XX XX") == 0);
}



int my_strlen(const char* s)
{
    const char* begin = s;

    for (; *s; ++s)
    {         /// Zeiger-Inkrement
    }
            ///////// Zeiger-Differenz
    return s - begin;
}

void my_strlen_test()
{
    assert(my_strlen("") == 0);
    assert(my_strlen("I") == 1);
    assert(my_strlen("we") == 2);
    assert(my_strlen("you") == 3);
    assert(my_strlen("they") == 4);
}
```
