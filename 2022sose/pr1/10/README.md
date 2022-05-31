# Woche 10

## Aufgaben

### Aufgabe 10.1 (Pflicht)

Implementiere die Funktion `countSpaces` zum Zählen von Leertasten **ohne** `s[i]` Syntax:

```c
int countSpaces(const char *s)
{
    // ...
}

void aufgabe_10_1()
{
    assert(countSpaces("") == 0);
    assert(countSpaces(" ") == 1);
    assert(countSpaces("  ") == 2);
    assert(countSpaces("hello world") == 1);
    assert(countSpaces("  to be or  not to be  ") == 10);
}
```

### Aufgabe 10.2 (Pflicht)

Implementiere die Funktion `removeSpaces` zum Entfernen von Leertasten **ohne** `s[i]` Syntax:

```c
void removeSpaces(char *s)
{
    // ...
}

void aufgabe_10_2()
{
    char a[] = "  If a woodchuck  could chuck wood  ";
    removeSpaces(a);
    assert(0 == strcmp(a, "Ifawoodchuckcouldchuckwood"));
}
```

### Aufgabe 10.3 (Kür)

Implementiere den `strcmp`-Klon `my_strcmp` zum Vergleichen von Strings. Das Ergebnis von `my_strcmp(a, b)` ist:
- 0, falls `a` gleich `b` ist
- *irgendeine* negative Zahl, falls `a` lexikographisch vor `b` liegt
- *irgendeine* positive Zahl, falls `a` lexikographisch nach `b` liegt

```c
int my_strcmp(const char *s, const char *t)
{
    // ...
}

void aufgabe_10_3()
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

### Aufgabe 10.4 (Kür)

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
char *z   = a; // z zeigt auf das erste Zeichen von a
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

Offensichtlich sehen Arrays und Zeiger im Speicher unterschiedlich aus.
Das begründet auch den unterschiedlichen Speicherverbrauch:

```c
assert(sizeof a != sizeof z);

assert(sizeof a == sizeof(char[6]));
assert(sizeof z == sizeof(char*));
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
b = z;
//  char*
//ø char[6]

b = a;
//  char[6]
//¤ char*
//ø char[6]
```

## Sind Array-Parameter eigentlich Zeiger-Parameter?

Ja, das ist eine **Sonderregel für Parameter** von Funktionen:

> ISO C90 §3.7.1 Function definitions, Semantics
>
> A declaration of a parameter as *array of type* shall be adjusted to *pointer to type*

```c
void funktion(char p[6], char q[], char *r)
{
    assert(sizeof p == sizeof(char*));
    assert(sizeof q == sizeof(char*));
    assert(sizeof r == sizeof(char*));
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
p |&a[0]|  |     |
  +-----+  |     |
           |     |
        +--|--+  |
      q |&a[0]|  |
        +-----+  |
                 |
              +--|--+
            r |&a[0]|
              +-----+
```

## Warum kann ich dann nicht `char x[];` für einen Zeiger schreiben?

Weil lokale Variablen keine Parameter sind.
Parameter befinden sich zwischen den runden Klammern im Funktionskopf:

```c
void funktion(char parameter[]) // char *parameter
{
    char lokal[]; // missing array size or initializer
}
```

## Wenn Array-Parameter eigentlich Zeiger-Parameter sind, wieso klappt `x[i]` dann trotzdem?

- Nützliche Lüge:
  - Der Zugriff `x[i]` funktioniert sowohl direkt auf Arrays als auch indirekt über Zeiger
- Technische Wahrheit:
  - Der Zugriff `x[i]` funktioniert *ausschließlich* über Zeiger
  - Wenn `x` ein Array ist, wird gemäß §3.2.2.1 ein Zeiger auf das erste Element bereitgestellt
  - Tatsächlich ist `x[i]` nur syntaktischer Zucker für `*(x + i)`

## Man kann mit Zeigern *rechnen*?!

Ja, das ist recht nützlich für die Iteration über Arrays:

```c
unsigned my_strlen(const char *p)
{
    const char *q = p;
    while (*q != '\0')
    {
        ++q; // Präfix-Inkrement
    }
    return q - p; // Differenz
}

void test_strlen()
{
    assert(0 == my_strlen(""));
    assert(1 == my_strlen("I"));
    assert(2 == my_strlen("we"));
    assert(3 == my_strlen("you"));
    assert(4 == my_strlen("they"));
}


void my_strcpy(char *dst, const char *src)
{
    while (*dst++ = *src++) {} // Postfix-Inkrement
}

void test_strcpy()
{
    char s[10];
    
    my_strcpy(s, "apfel");
    assert(0 == strcmp(s, "apfel"));
    
    my_strcpy(s + 5, "sine"); // Addition
    assert(0 == strcmp(s, "apfelsine"));
}


void my_strcat(char *dst, const char *src)
{
    my_strcpy(dst + strlen(dst), src); // Addition
}

void test_strcat()
{
    char s[10];
    
    my_strcpy(s, "apfel");
    assert(0 == strcmp(s, "apfel"));
    
    my_strcat(s, "sine");
    assert(0 == strcmp(s, "apfelsine"));
}
```
