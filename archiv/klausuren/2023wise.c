typedef enum { false, true } bool;



// AUFGABE A (2 Punkte)
// Spiegelt eine 3x3 Matrix an ihrer Gegendiagonale: /

// EXERCISE A (2 points)
// Flips a 3x3 matrix over its antidiagonal: /

void flip(int matrix[9])
{
    // ...
}

void flip_test()
{
    int matrix[9] =
    {
        10, 20, 30,
        40, 50, 60,
        70, 80, 90,
    };
    
    flip(matrix);
    
    assert(matrix[0] == 90 && matrix[1] == 60 && matrix[2] == 30);
    assert(matrix[3] == 80 && matrix[4] == 50 && matrix[5] == 20);
    assert(matrix[6] == 70 && matrix[7] == 40 && matrix[8] == 10);
}



// AUFGABE B (3 Punkte)
// Zählt die Positionen, an denen Buchstaben stehen

// EXERCISE B (3 points)
// Counts the positions where letters are stored

int countLetters(const char* s)
{
    // ...
}

void countLetters_test()
{
    assert(countLetters("") == 0);
    assert(countLetters("HAL 9000") == 3);
    assert(countLetters("Jazz") == 4);
    assert(countLetters("a² + b² = c²") == 3);
    assert(countLetters("[_]") == 0);
    
    // Performance-Tipp: String-Tests laufen SEHR viel schneller durch,
    // wenn man die Ansicht links oben von "memory" auf "syntax tree" wechselt!
    
    // Performance tip: String tests will complete MUCH faster
    // when switching the top left view from "memory" to "syntax tree"!
    
    assert(countLetters("The quick brown fox jumps over the lazy dog.") == 35);
    assert(countLetters("Franz jagt im komplett verwahrlosten Taxi quer durch Bayern?") == 51);
    assert(countLetters("Ümläütë zählën NÏCHT!") == 11);
}



// AUFGABE C (3 Punkte)
// Konvertiert Sekunden seit Mitternacht (0..86399)
// in Stunden (0..23), Minuten (0..59) und Sekunden (0..59)

// EXERCISE C (3 points)
// Converts from seconds since midnight (0..86399)
// to hours (0..23), minutes (0..59) and seconds (0..59)

void convert(int secondsSinceMidnight, int* hours, int* minutes, int* seconds)
{
    // ...
}

void convert_test()
{
    int hours, minutes, seconds;
    
    convert(7, &hours, &minutes, &seconds);
    assert(hours == 0 && minutes == 0 && seconds == 7);
    
    convert(59, &hours, &minutes, &seconds);
    assert(hours == 0 && minutes == 0 && seconds == 59);
    
    convert(60, &hours, &minutes, &seconds);
    assert(hours == 0 && minutes == 1 && seconds == 0);
    
    convert(12345, &hours, &minutes, &seconds);
    assert(hours == 3 && minutes == 25 && seconds == 45);
    
    convert(45296, &hours, &minutes, &seconds);
    assert(hours == 12 && minutes == 34 && seconds == 56);
    
    convert(86158, &hours, &minutes, &seconds);
    assert(hours == 23 && minutes == 55 && seconds == 58);
}



// AUFGABE D (3 Punkte)
// Verschiebt jeden Kleinbuchstaben um 2 im Alphabet; andere Zeichen bleiben gleich!

// EXERCISE D (3 points)
// Moves every lower case letter by 2 in the alphabet; other characters remain unchanged!

//  VORHER abcdefghijklmnopqrstuvwxyz BEFORE
// NACHHER cdefghijklmnopqrstuvwxyzab AFTER

void rotate2(char* s)
{
    // ...
}

void rotate2_test()
{
    char a[] =       "banana";
    rotate2(a);
    assert(strcmp(a, "dcpcpc") == 0);
    
    char b[] =       "xylophonez";
    rotate2(b);
    assert(strcmp(b, "zanqrjqpgb") == 0);
    
    char c[] =       "The quick (brown) fox? Jumps over: The lazy dog!";
    rotate2(c);
    assert(strcmp(c, "Tjg swkem (dtqyp) hqz? Jworu qxgt: Tjg ncba fqi!") == 0);
}



// AUFGABE E (3 Punkte)
// Fügt den Score (sofern gut genug) an der korrekten Stelle in die Top 3 ein.
// Der Parameter topThree ist bereits absteigend sortiert und muss nicht erst sortiert werden!

// EXERCISE E (3 points)
// Inserts the score (if good enough) at the correct place in the top 3.
// The parameter topThree is already sorted in descending order, no need to sort it first!

void gameOver(int score, int topThree[3])
{
    // ...
}

void gameOver_test()
{
    int a[3] = { 300, 200, 100 };
    //       50 ist zu schlecht für die Top 3
    //       50 does not make it into the top 3
    gameOver(50, a);
    assert(a[0] == 300 && a[1] == 200 && a[2] == 100);
    
    int b[3] = { 300, 200, 100 };
    //       _____________^
    gameOver(150, b);
    assert(b[0] == 300 && b[1] == 200 && b[2] == 150);
    
    int c[3] = { 300, 200, 100 };
    //       ________^
    gameOver(250, c);
    assert(c[0] == 300 && c[1] == 250 && c[2] == 200);
    
    int d[3] = { 300, 200, 100 };
    //       ___^
    gameOver(350, d);
    assert(d[0] == 350 && d[1] == 300 && d[2] == 200);
}



// Grundlage für Aufgabe F (nur lesen und verstehen)
// Basis for exercise F (just read and understand)

int collatz(int x)
{
    if (x % 2 == 0)
    {
        return x / 2;
    }
    else
    {
        return 3 * x + 1;
    }
}

void collatz_test()
{   //             v
    assert(collatz(3) == 10                                     );
    //                    |
    assert(      collatz(10) == 5                               );
    //                          |
    assert(             collatz(5) == 16                        );
    //                                 |
    assert(                   collatz(16) == 8                  );
    //                                       |
    assert(                          collatz(8) == 4            );
    //                                             |
    assert(                                collatz(4) == 2      );
    //                                                   |
    assert(                                      collatz(2) == 1);
}   //                                                         ^

// AUFGABE F (3 Punkte)
// Bestimmt, wie häufig die Funktion collatz wiederholt aufgerufen werden muss, bis 1 rauskommt.
// (OBIGE Funktion collatz_test demonstriert zum Beispiel, dass collatz 7 Mal für n=3 aufgerufen werden muss.)

// Exercise F (3 points)
// Determines how often the function collatz must be called repeatedly to reach the value 1.
// (The function collatz_test ABOVE demonstrates how collatz must be called 7 times for n=3, for example.)

int countCollatzUntil1(int x)
{
    // ...
}

void countCollatzUntil1_test()
{
    assert(countCollatzUntil1(1) ==  0); // 1
    assert(countCollatzUntil1(2) ==  1); // 2 -> 1
    assert(countCollatzUntil1(3) ==  7); // 3 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
    assert(countCollatzUntil1(4) ==  2); // 4 -> 2 -> 1
    assert(countCollatzUntil1(5) ==  5); // 5 -> 16 -> 8 -> 4 -> 2 -> 1
    assert(countCollatzUntil1(6) ==  8); // 6 -> 3 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
    assert(countCollatzUntil1(7) == 16); // 7 -> 22 -> 11 -> 34 -> 17 -> 52 -> 26 -> 13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
    assert(countCollatzUntil1(8) ==  3); // 8 -> 4 -> 2 -> 1
    assert(countCollatzUntil1(9) == 19); // 9 -> 28 -> 14 -> 7 -> 22 -> 11 -> 34 -> 17 -> 52 -> 26 -> 13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
}


// AUFGABE G (3 Punkte)
// Vergleicht die übergebenen Strings anhand der enthaltenen Ganzzahlen.
// Die Strings enthalten ausschließlich Ziffern (von 0 bis 9), KEINE Buchstaben oder andere Zeichen.
// Führende Nullen kommen NICHT vor, d.h. jeder String startet garantiert mit einer Ziffer von 1 bis 9.

// EXERCISE G (3 points)
// Compares the given strings by the contained integers.
// The strings consist exclusively of digits (from 0 to 9), NO letters or other characters.
// Leading zeros do NOT occur, i.e. every string definitely starts with a digit from 1 to 9.

typedef const char* string;

int compareIntegerInString(const void* v, const void* w)
{
    // ...
}

void compareIntegerInString_test()
{
    string numbers[] = {"48", "20", "601", "1", "1384", "8", "261", "3185", "3", "113"};
    
    qsort(numbers, 10, sizeof(string), &compareIntegerInString);
    
    for (int i = 0; i < 10; ++i)
    {
        printf("%s ", numbers[i]);
    }
    
    assert(strcmp(numbers[0], "1") == 0);
    assert(strcmp(numbers[1], "3") == 0);
    assert(strcmp(numbers[2], "8") == 0);
    assert(strcmp(numbers[3], "20") == 0);
    assert(strcmp(numbers[4], "48") == 0);
    assert(strcmp(numbers[5], "113") == 0);
    assert(strcmp(numbers[6], "261") == 0);
    assert(strcmp(numbers[7], "601") == 0);
    assert(strcmp(numbers[8], "1384") == 0);
    assert(strcmp(numbers[9], "3185") == 0);
}
