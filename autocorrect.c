/* Autocorrect Replica - Version 2
   Author - Akilan E 
   Description:
   This application demonstrates an autocorrect functionality using a hash table and the Levenshtein distance algorithm. 
   It reads a CSV file containing a dictionary of words, builds a hash table with the words, and then autocorrects 
   user-inputted sentences by suggesting corrections for misspelled words based on the Levenshtein distance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define DICTIONARY_SIZE 117821
#define MAX_WORD_LENGTH 50

// Define a structure for the nodes in the hash table
struct Node {
    char word[MAX_WORD_LENGTH];
    struct Node* next;
};

// Initialize the hash table
struct Node* hashtable[DICTIONARY_SIZE];

// Hash function to map a word to an index in the hash table
unsigned int hashFunction(const char* word) {
    unsigned int hash = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        hash = hash * 31 + word[i];
    }
    return hash % DICTIONARY_SIZE;
}

// Insert a word into the hash table
void insertWord(const char* word) {
    unsigned int index = hashFunction(word);

    // Create a new node for the word
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->word, word);
    newNode->next = NULL;

    // Insert the new node at the beginning of the linked list at the index
    newNode->next = hashtable[index];
    hashtable[index] = newNode;
}

// Search for a word in the hash table
int searchWord(const char* word) {
    unsigned int index = hashFunction(word);

    // Traverse the linked list at the index
    struct Node* current = hashtable[index];
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            return 1; // Word found
        }
        current = current->next;
    }

    return 0; // Word not found
}

// Calculate the minimum of three values
int min(int a, int b, int c) {
    return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
}

// Calculate Levenshtein distance between two words
int levenshteinDistance(const char* word1, const char* word2) {
    int len1 = strlen(word1);
    int len2 = strlen(word2);

    int dp[len1 + 1][len2 + 1];

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]);
            }
        }
    }

    return dp[len1][len2];
}

// Autocorrect function.
void autocorrect(const char* input) {
    // Split the input into words
    char* token = strtok((char*)input, " ");
    char autocorrectedSentence[500] = ""; // Initialize an empty string for autocorrected sentence

    while (token != NULL) {
        // Check if the word is in the dictionary
        if (!searchWord(token)) {
            printf("Autocorrecting: %s -> ", token);

            // Find the closest word in the dictionary based on Levenshtein distance
            int minDistance = INT_MAX;
            char closestWord[MAX_WORD_LENGTH] = "";

            // Traverse the dictionary
            for (int i = 0; i < DICTIONARY_SIZE; i++) {
                struct Node* current = hashtable[i];
                while (current != NULL) {
                    int distance = levenshteinDistance(token, current->word);
                    if (distance < minDistance) {
                        minDistance = distance;
                        strcpy(closestWord, current->word);
                    }
                    current = current->next;
                }
            }

            printf("%s\n", closestWord);

            // Append the corrected word to the autocorrected sentence
            strcat(autocorrectedSentence, closestWord);
        } else {
            // If the word is found in the dictionary, keep it as it is
            strcat(autocorrectedSentence, token);
        }

        // Add a space between words
        strcat(autocorrectedSentence, " ");

        // Move to the next word
        token = strtok(NULL, " ");
    }

    printf("Autocorrected sentence: %s\n", autocorrectedSentence);
}

int main() {
    // Open the CSV file for reading
    FILE* file = fopen("words.csv", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening the file.\n");
        return 1;
    }

    // Read words from the CSV file and insert them into the dictionary
    char line[MAX_WORD_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = 0; // Remove newline character
        insertWord(line);
    }

    // Close the CSV file
    fclose(file);

    // Get user input for the string to be autocorrected
    char inputString[500];
    printf("Enter a string for autocorrection: ");
    fgets(inputString, sizeof(inputString), stdin);

    // Remove newline character from the input
    inputString[strcspn(inputString, "\n")] = 0;

    // Autocorrect the user-inputted string
    autocorrect(inputString);

    return 0;
}
