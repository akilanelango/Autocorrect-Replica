# Autocorrect-Replica
This C program demonstrates an autocorrect functionality using a hash table and the Levenshtein distance algorithm. It reads a CSV file containing a dictionary of words, builds a hash table with the words, and then autocorrects user-inputted sentences by suggesting corrections for misspelled words based on the Levenshtein distance.

Features:
- Utilizes a hash table for efficient word lookup.
- Implements the Levenshtein distance algorithm to find the closest word to a misspelled word.
- Autocorrects user-inputted sentences by suggesting corrections for misspelled words.

How to use:
1. Compile the program using a C compiler (e.g., gcc).
2. Ensure that the CSV file "words.csv" containing the dictionary of words is present in the same directory as the executable.
3. Run the compiled program.
4. Enter a string for autocorrection when prompted.
