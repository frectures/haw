typedef enum { false, true } bool;



// AUFGABE A (2 Punkte)
// Summiert die ersten n UNGERADEN Zahlen

// EXERCISE A (2 points)
// Sums the first n ODD numbers

int oddSum(int n)
{
    // ...
}

void oddSum_test()
{
    assert(oddSum(1) == 1);
    assert(oddSum(2) == 1+3);
    assert(oddSum(3) == 1+3+5);
    assert(oddSum(4) == 1+3+5+7);
    assert(oddSum(5) == 1+3+5+7+9);
    assert(oddSum(6) == 1+3+5+7+9+11);
    assert(oddSum(7) == 1+3+5+7+9+11+13);
    assert(oddSum(8) == 1+3+5+7+9+11+13+15);
    assert(oddSum(9) == 1+3+5+7+9+11+13+15+17);
    assert(oddSum(0) == 0);
}



// AUFGABE B (3 Punkte)
// Konvertiert die Anzeige einer digitalen Uhr in die Anzahl Sekunden seit Mitternacht
// (Es ist KEINE Fehlerbehandlung für ungültige Eingaben erforderlich)

// EXERCISE B (3 points)
// Converts the display of a digital clock to the number of seconds since midnight
// (Error handling for ill-formed inputs is NOT necessary)

int secondsSinceMidnight(const char clock[])
{
    // ...
}

void secondsSinceMidnight_test()
{
    assert(secondsSinceMidnight("00:00:07") == 7);
    assert(secondsSinceMidnight("00:00:59") == 59);
    assert(secondsSinceMidnight("00:01:00") == 60);
    assert(secondsSinceMidnight("03:25:45") == 12345);
    assert(secondsSinceMidnight("12:34:56") == 45296);
    assert(secondsSinceMidnight("23:55:58") == 86158);
}



// AUFGABE C (3 Punkte)
// Verschlüsselt alle Buchstaben im String durch Rotation um 1 im Alphabet

// EXERCISE C (3 points)
// Encrypts all letters in the string through rotation by 1 in the alphabet

void rotate1(char s[])
{
    // ...
}

void rotate1_test()
{
    char pangram[] =       "Franz jagt im komplett verwahrlosten Taxi quer durch Bayern";
    rotate1(pangram);
    assert(strcmp(pangram, "Gsboa kbhu jn lpnqmfuu wfsxbismptufo Ubyj rvfs evsdi Cbzfso") == 0);
    
    char fullCycle[] = "aA";
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    rotate1(fullCycle);
    assert(strcmp(fullCycle, "aA") == 0);
}



// AUFGABE D (2 Punkte)
// Berechnet den Durchschnitt der übergebenen Zahlen

// EXERCISE D (2 points)
// Computes the average of the given numbers

double average(const int numbers[], int count)
{
    // ...
}

void average_test()
{
    const int pi[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3};
    
    assert(average(pi, 16) == 5);
    
    assert(average(pi, 4) == 2.25);
}



// AUFGABE E (3 Punkte)
// Findet die kleinste Zahl und die größte Zahl

// EXERCISE E (3 points)
// Finds the smallest number and the largest number

void minmax(const int numbers[], int count, int* min, int* max)
{
    // ...
}

void minmax_test()
{
    const int pi[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3};
    int minimum;
    int maximum;
    
    minmax(pi, 16, &minimum, &maximum);
    assert(minimum == 1);
    assert(maximum == 9);
    
    minmax(pi, 5, &minimum, &maximum);
    assert(minimum == 1);
    assert(maximum == 5);
    
    minmax(pi+6, 6, &minimum, &maximum);
    assert(minimum == 2);
    assert(maximum == 8);
}



// AUFGABE F (2 Punkte)
// Fängt der erste String mit dem zweiten String an?

// EXERCISE F (2 points)
// Does the first string start with the second string?

bool isPrefix(const char string[], const char prefix[])
{
    // ...
}

void isPrefix_test()
{
    assert(   isPrefix("Apfelsine", "Apfel"));
    assert(   isPrefix("Mandarine", "Mandarin"));
    
    assert( ! isPrefix("Engel", "Angel"));
    assert( ! isPrefix("Orang Utan", "Orange"));
    
    assert(   isPrefix("Z", "Z"));
    assert(   isPrefix("Z", ""));
    assert(   isPrefix("", ""));
    
    assert( ! isPrefix("", "Z"));
}



// AUFGABE G (2 Punkte)
// Findet das erste Vorkommen des zweiten Strings im ersten String

// EXERCISE G (2 points)
// Finds the first occurrence of the second string within the first string

int findSubstring(const char string[], const char substring[])
{
    // ...
}

void findSubstring_test()
{
    assert(findSubstring("Quastenflosser", "ast") == 2);
    assert(findSubstring("Quastenflosser", "flosse") == 7);
    
    assert(findSubstring("Buchstabe", "B") == 0);
    assert(findSubstring("Buchstabe", "e") == 8);
    
    assert(findSubstring("abc", "z") == -1);
    assert(findSubstring("egal", "") == 0);
    
    assert(findSubstring("Meineid", "ei") == 1);
    assert(findSubstring("Meineid", "ein") == 1);
    assert(findSubstring("Meineid", "eid") == 4);
}



// AUFGABE H (3 Punkte)
// Bestimmt, ob jede öffnende Klammer weiter rechts einen schließenden Partner hat
// (Jeder String besteht garantiert nur aus Klammern; andere Zeichen brauchen nicht behandelt werden)

// EXERCISE H (3 points)
// Determines whether every opening parenthesis has a closing partner further right
// (Every string is guaranteed to consist only of parentheses; other characters need not be handled)

bool isBalanced(const char parens[])
{
    // ...
}

void isBalanced_test()
{
    assert(   isBalanced("((()))"));
    assert(   isBalanced("()()()"));
    assert(   isBalanced(""));
    
    assert( ! isBalanced("("));
    assert( ! isBalanced(")"));
    
    assert( ! isBalanced("(("));
    assert(   isBalanced("()"));
    assert( ! isBalanced(")("));
    assert( ! isBalanced("))"));
    
    assert( ! isBalanced("((("));
    assert( ! isBalanced("(()"));
    assert( ! isBalanced("()("));
    assert( ! isBalanced("())"));
    assert( ! isBalanced(")(("));
    assert( ! isBalanced(")()"));
    assert( ! isBalanced("))("));
    assert( ! isBalanced(")))"));
    
    assert( ! isBalanced("(((("));
    assert( ! isBalanced("((()"));
    assert( ! isBalanced("(()("));
    assert(   isBalanced("(())"));
    assert( ! isBalanced("()(("));
    assert(   isBalanced("()()"));
    assert( ! isBalanced("())("));
    assert( ! isBalanced("()))"));
    assert( ! isBalanced(")((("));
    assert( ! isBalanced(")(()"));
    assert( ! isBalanced(")()("));
    assert( ! isBalanced(")())"));
    assert( ! isBalanced("))(("));
    assert( ! isBalanced("))()"));
    assert( ! isBalanced(")))("));
    assert( ! isBalanced("))))"));
}
