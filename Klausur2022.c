// AUFGABE A (2 Punkte)
// Dreht eine 3x3 Matrix um 90 Grad gegen den Uhrzeigersinn

// EXERCISE A (2 points)
// Rotates a 3x3 matrix by 90 degrees counterclockwise

void rotateCounterclockwise(int matrix[9])
{
    // ...
}

void rotateCounterclockwise_test()
{
    int m[] = {
        10, 20, 30,
        40, 50, 60,
        70, 80, 90,
    };
    rotateCounterclockwise(m);
    
    assert(m[0] == 30);
    assert(m[1] == 60);
    assert(m[2] == 90);
    
    assert(m[3] == 20);
    assert(m[4] == 50);
    assert(m[5] == 80);
    
    assert(m[6] == 10);
    assert(m[7] == 40);
    assert(m[8] == 70);
}



// AUFGABE B (3 Punkte)
// Zählt die Vokale (AEIOUaeiou) im String s

// EXERCISE B (3 points)
// Counts the vowels (AEIOUaeiou) in the string s

int countVowels(const char *s)
{
    // ...
}

void countVowels_test()
{
    assert(countVowels("") == 0);
    assert(countVowels("Super Mario Brothers") == 7);
    assert(countVowels("A man can dream") == 5);
    assert(countVowels("IOU 5 bucks") == 4);
    assert(countVowels("Ender Dragon") == 4);
}



// AUFGABE C (3 Punkte)
// Dreht den String s um

// EXERCISE C (3 points)
// Reverses the string s

void reverse(char s[])
{
    // ...
}

void reverse_test()
{
    char a[] = "regal";
    reverse(a);
    assert(strcmp(a, "lager") == 0);
    
    char b[] = "A man, a plan, a canal, panama";
    reverse(b);
    assert(strcmp(b, "amanap ,lanac a ,nalp a ,nam A") == 0);
    
    char c[] = "";
    reverse(c);
    assert(strcmp(c, "") == 0);
}



// AUFGABE D (4 Punkte)
// Konkateniert zwei Verzeichnisnamen.
// Es sollte egal sein, ob folder mit einem Strich ENDET
// oder subfolder mit einem Strich STARTET;
// Wenn concat fertig ist, soll genau 1 Strich zwischen ihnen stehen.

// EXERCISE D (4 points)
// Concatenates two folder names.
// It should not matter whether folder ENDS with a slash
// or subfolder STARTS with a slash;
// When concat is done, a total of 1 slash shall separate them.

void concat(char folder[], const char subfolder[])
{
    // ...
}

void concat_test()
{
    // no slashes
    char a[100] =    "/home/fred";
    concat(a,                   "karel");
    assert(strcmp(a, "/home/fred/karel") == 0);
    
    // trailing slash
    char b[100] =    "/home/fred/";
    concat(b,                   "karel");
    assert(strcmp(b, "/home/fred/karel") == 0);
    
    // leading slash
    char c[100] =    "/home/fred";
    concat(c,                  "/karel");
    assert(strcmp(c, "/home/fred/karel") == 0);
    
    // both slashes
    char d[100] =    "/home/fred/";
    concat(d,                  "/karel");
    assert(strcmp(d, "/home/fred/karel") == 0);
}



// AUFGABE E (2 Punkte)
// Kopiert alle Zeichen inklusive NUL-Terminator von source nach destination

// EXERCISE E (2 points)
// Copies all characters including the NUL-Terminator from source to destination

void strcpy(char *destination, const char *source)
{
    // ...
}

void strcpy_test()
{
    char a[20];
    strcpy(a, "Heidelbeeren");
    assert(strcmp(a, "Heidelbeeren") == 0);
}



// AUFGABE F (2 Punkte)
// Hängt alle Zeichen von source an destination dran

// EXERCISE F (2 points)
// Appends all characters from source to destination

void append(char *destination, const char *source)
{
    // ...
}

void append_test()
{
    char a[20];
    a[0] = '\0';
    append(a, "Heidel");
    append(a, "beeren");
    assert(strcmp(a, "Heidelbeeren") == 0);
}



// AUFGABE G (4 Punkte)
// Konvertiert einen Hexadezimal-String in einen Binär-String

// EXERCISE G (4 points)
// Converts a hexadecimal string to a binary string

void hexToBinary(const char *hex, char *bin)
{
    // ...
}

void hexToBinary_test()
{
    char bin[80];
    
    hexToBinary("0fab1e98", bin);
    assert(strcmp(bin, "0000 1111 1010 1011 0001 1110 1001 1000") == 0);
    
    hexToBinary("9a", bin);
    assert(strcmp(bin, "1001 1010") == 0);
    
    hexToBinary("20645e8abf1d379c", bin);
    assert(strcmp(bin, "0010 0000 0110 0100 0101 1110 1000 1010 1011 1111 0001 1101 0011 0111 1001 1100") == 0);
}

