// AUFGABE A (3 Punkte)
// Transponiert eine 3x3 Matrix, d.h. spiegelt sie an ihrer \ Hauptdiagonale

// EXERCISE A (3 points)
// Transposes a 3x3 matrix, i.e. flips it over its \ main diagonal

void transpose(int matrix[9])
{
    // ...
}

void transpose_test()
{
    int m[] = {
        10, 20, 30,
        40, 50, 60,
        70, 80, 90,
    };
    transpose(m);
    
    assert(m[0] == 10);
    assert(m[1] == 40);
    assert(m[2] == 70);
    
    assert(m[3] == 20);
    assert(m[4] == 50);
    assert(m[5] == 80);
    
    assert(m[6] == 30);
    assert(m[7] == 60);
    assert(m[8] == 90);
}

// AUFGABE B (2 Punkte)
// Summiert die ASCII-Codes aller Zeichen

// EXERCISE B (2 points)
// Sums the ASCII codes of all characters

int hashSum(const char* s)
{
    // ...
}

void hashSum_test()
{
    assert(hashSum("") == 0);
    assert(hashSum("A") == 65);
    assert(hashSum("BC") == 'B'+'C');
    assert(hashSum("DEF") == 'D'+'E'+'F');
}

// AUFGABE C (2 Punkte)
// Summiert die ASCII-Codes aller Zeichen, gewichtet mit absteigenden 31er-Potenzen

// EXERCISE C (2 points)
// Sums the ASCII codes of all characters, weighted by descending powers of 31

int hashPolynom(const char* s)
{
    // ...
}

void hashPolynom_test()
{
    assert(hashPolynom("") == 0);
    assert(hashPolynom("A") == 65);
    assert(hashPolynom("BC") == 'B'*31+'C');
    assert(hashPolynom("DEF") == ('D'*31+'E')*31+'F');
}

// AUFGABE D (4 Punkte)
// (Die Top 3 sind bereits absteigend sortiert und müssen nicht erst sortiert werden!)
// Fügt den Score (sofern gut genug) an der korrekten Stelle in die Top 3 ein

// EXERCISE D (4 points)
// (The top 3 are already sorted in descending order, no need to sort them first!)
// Inserts the score (if good enough) at the correct place in the top 3

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

// AUFGABE E (4 Punkte)
// Zählt, wie viele Zeichen der beiden Strings am Anfang hintereinander gleich sind

// EXERCISE E (4 points)
// Counts how many consecutive characters of both strings are equal at the beginning

int commonPrefixLength(const char s[], const char t[])
{
    // ...
}

void commonPrefixLength_test()
{
    //                         _        _
    assert(commonPrefixLength("apfel", "abfall") == 1);
    //                         __       __
    assert(commonPrefixLength("apfel", "apple") == 2);
    
    assert(commonPrefixLength("apfel", "birne") == 0);
    
    assert(commonPrefixLength("apfel", "") == 0);
    
    assert(commonPrefixLength("", "birne") == 0);
    //                         _____    _____
    assert(commonPrefixLength("apfel", "apfelkuchen") == 5);
    //                         _____          _____
    assert(commonPrefixLength("apfelkuchen", "apfel") == 5);
    //                         _____    _____
    assert(commonPrefixLength("apfel", "apfel") == 5);
}



struct Person
{
    char  vorname[8];
    char nachname[8];
};

// Aufgabe F (2 Punkte)
// Vergleicht 2 Personen per Nachname; wenn die Nachnamen gleich sind, per Vorname

// Exercise F (2 points)
// Compares 2 persons by surname (nachname); if the surnames are equal, by forename (vorname)

int compareNachnameVorname(const void* v, const void* w)
{
    // ...
}

void compareNachnameVorname_test()
{
    struct Person a = { "Franz", "Meier" };
    struct Person b = { "Fritz", "Meier" };
    struct Person c = { "Franz", "Meyer" };
    struct Person d = { "Fritz", "Meyer" };
    
    assert(compareNachnameVorname(&a, &a) == 0);
    assert(compareNachnameVorname(&a, &b) <  0);
    assert(compareNachnameVorname(&a, &c) <  0);
    assert(compareNachnameVorname(&a, &d) <  0);
    
    assert(compareNachnameVorname(&b, &a) >  0);
    assert(compareNachnameVorname(&b, &b) == 0);
    assert(compareNachnameVorname(&b, &c) <  0);
    assert(compareNachnameVorname(&b, &d) <  0);
    
    assert(compareNachnameVorname(&c, &a) >  0);
    assert(compareNachnameVorname(&c, &b) >  0);
    assert(compareNachnameVorname(&c, &c) == 0);
    assert(compareNachnameVorname(&c, &d) <  0);
    
    assert(compareNachnameVorname(&d, &a) >  0);
    assert(compareNachnameVorname(&d, &b) >  0);
    assert(compareNachnameVorname(&d, &c) >  0);
    assert(compareNachnameVorname(&d, &d) == 0);
}

// Aufgabe G (3 Punkte)
// Teilt den Eingabe-String beim ersten Vorkommen von splitter in 2 Teile

// Exercise G (3 points)
// Splits the input string at the first occurrence of splitter in 2 parts

char* splitAtFirst(char splitter, char* s)
{
    // ...
}

void splitAtFirst_test()
{
    char a[] = "Wochenende. Laufen. Super!";
    char* p = splitAtFirst('.', a);
    assert(strcmp(a, "Wochenende") == 0);
    assert(strcmp(p, " Laufen. Super!") == 0);
    
    char b[] = "Wochenende. Laufen. Super!";
    char* q = splitAtFirst('!', b);
    assert(strcmp(b, "Wochenende. Laufen. Super") == 0);
    assert(strcmp(q, "") == 0);
    
    char c[] = "Wochenende. Laufen. Super!";
    char* r = splitAtFirst('?', c);
    assert(strcmp(c, "Wochenende. Laufen. Super!") == 0);
    assert(strcmp(r, "") == 0);
}
