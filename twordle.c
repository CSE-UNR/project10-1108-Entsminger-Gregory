/*Project 10 twordle.c
 Author Gregory Entsminger
 May 1, 2026

*/

#include <stdio.h>
#include <stdbool.h>

#define WORD_LEN 5
#define MAX_GUESSES 6

int strLen(char str[]);
void toLower(char str[]);
bool isLetter(char ch);
bool hasPunctuation(char str[]);
bool contains(char word[], char letter);
bool getWord(char mystery[]);
void getGuess(char guess[]);
bool sameWord(char first[], char second[]);
void copyString(char dest[], char src[]);
void clearPointer(char pointer[]);
void findMisplaced(char mystery[], char guess[], char pointer[]);
void findCorrect(char mystery[], char guess[]);
void displayBoard(char guesses[][WORD_LEN + 1], char pointers[][WORD_LEN + 1], int count);
void displayWinMessage(int guesses);

int main(void)
{
    char mystery[WORD_LEN + 1];
    char guess[100];
    char guesses[MAX_GUESSES][WORD_LEN + 1];
    char pointers[MAX_GUESSES][WORD_LEN + 1];

    int guessCount = 0;
    bool won = false;

    if (!getWord(mystery))
    {
        printf("Sorry, could not get today's word. Try again tomorrow.\n");
        return 1;
    }

    while (!won && guessCount < MAX_GUESSES)
    {
        if (guessCount == MAX_GUESSES - 1)
        {
            printf("FINAL GUESS : ");
        }
        else
        {
            printf("GUESS %d! Enter your guess: ", guessCount + 1);
        }

        getGuess(guess);
        toLower(guess);

        if (sameWord(mystery, guess))
        {
            findCorrect(mystery, guess);

            printf("================================\n");
            printf("        %s\n", guess);
            displayWinMessage(guessCount + 1);

            won = true;
        }
        else
        {
            copyString(guesses[guessCount], guess);
            clearPointer(pointers[guessCount]);

            findMisplaced(mystery, guesses[guessCount], pointers[guessCount]);
            findCorrect(mystery, guesses[guessCount]);

            guessCount++;
            displayBoard(guesses, pointers, guessCount);
        }
    }

    if (!won)
    {
        printf("You lost, better luck next time!\n");
    }

    return 0;
}

int strLen(char str[])
{
    int count = 0;

    while (str[count] != '\0')
    {
        count++;
    }

    return count;
}

bool isLetter(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

void toLower(char str[])
{
    int i;

    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] + 32;
        }
    }
}

bool hasPunctuation(char str[])
{
    int i;

    for (i = 0; str[i] != '\0'; i++)
    {
        if (!isLetter(str[i]))
        {
            return true;
        }
    }

    return false;
}

bool contains(char word[], char letter)
{
    int i;

    for (i = 0; word[i] != '\0'; i++)
    {
        if (word[i] == letter)
        {
            return true;
        }
    }

    return false;
}

bool getWord(char mystery[])
{
    FILE *file = fopen("mystery.txt", "r");

    if (file == NULL)
    {
        return false;
    }

    fscanf(file, "%5s", mystery);
    fclose(file);

    toLower(mystery);

    return true;
}

void getGuess(char guess[])

{
    scanf("%99s", guess);

    while (strLen(guess) != WORD_LEN || hasPunctuation(guess))
    {
        if (strLen(guess) != WORD_LEN)
        {
            printf("Your guess must be 5 letters long.\n");
        }
        else
        {
            printf("Your guess must contain only letters.\n");
        }

        printf("Please try again: ");
        scanf("%99s", guess);
    }
}

bool sameWord(char first[], char second[])
{
    int i;

    for (i = 0; first[i] != '\0' || second[i] != '\0'; i++)
    {
        if (first[i] != second[i])
        {
            return false;
        }
    }

    return true;
}

void copyString(char dest[], char src[])
{
    int i = 0;

    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
}

void clearPointer(char pointer[])
{
    int i;

    for (i = 0; i < WORD_LEN; i++)
    {
        pointer[i] = ' ';
    }

    pointer[WORD_LEN] = '\0';
}

void findMisplaced(char mystery[], char guess[], char pointer[])
{
    int i;
    int j;
    bool alreadyCorrect;

    for (i = 0; i < WORD_LEN; i++)
    {
        alreadyCorrect = false;

        for (j = 0; j < WORD_LEN; j++)
        {
            if (guess[i] == mystery[j] && guess[j] == mystery[j])
            {
                alreadyCorrect = true;
            }
        }

        if (guess[i] != mystery[i] && contains(mystery, guess[i]) && !alreadyCorrect)
        {
            pointer[i] = '^';
        }
    }
}

void findCorrect(char mystery[], char guess[])
{
    int i;

    for (i = 0; i < WORD_LEN; i++)
    {
        if (guess[i] == mystery[i] && guess[i] >= 'a' && guess[i] <= 'z')
        {
            guess[i] = guess[i] - 32;
        }
    }
}

void displayBoard(char guesses[][WORD_LEN + 1], char pointers[][WORD_LEN + 1], int count)
{
    int i;

    printf("================================\n");

    for (i = 0; i < count; i++)
    {
        printf("%s\n", guesses[i]);
        printf("%s\n", pointers[i]);
    }
}

void displayWinMessage(int guesses)
{
    if (guesses == 1)
    {
        printf("  You won in 1 guess!\n");
        printf("        GOATED!\n");
    }
    else if (guesses <= 3)
    {
        printf("  You won in %d guesses!\n", guesses);
        printf("        Amazing!\n");
    }
    else
    {
        printf("  You won in %d guesses!\n", guesses);
        printf("        Nice!\n");
    }
}
