#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50
#define MAX_MEANING_LENGTH 200
#define FILENAME "dictionary.txt"

struct DictionaryEntry {
    char word[MAX_WORD_LENGTH];
    char meaning[MAX_MEANING_LENGTH];
};

void addWord(struct DictionaryEntry dictionary[], int *size) {
    char inputWord[MAX_WORD_LENGTH];
    char inputMeaning[MAX_MEANING_LENGTH];

    printf("Enter the word: ");
    scanf("%s", inputWord);

    printf("Enter the meaning: ");
    scanf(" %[^\n]", inputMeaning);

    if (*size < MAX_WORDS) {
        strcpy(dictionary[*size].word, inputWord);
        strcpy(dictionary[*size].meaning, inputMeaning);
        (*size)++;
        printf("Word added successfully!\n");

        // Update the file with the new entry
        FILE *file = fopen(FILENAME, "a");
        if (file != NULL) {
            fprintf(file, "%s|%s\n", inputWord, inputMeaning);
            fclose(file);
        }
    } else {
        printf("Dictionary is full. Cannot add more words.\n");
    }
}

void loadDictionaryFromFile(struct DictionaryEntry dictionary[], int *size) {
    FILE *file = fopen(FILENAME, "r");
    if (file != NULL) {
        while (fscanf(file, "%49[^|]|%199[^\n]\n", dictionary[*size].word, dictionary[*size].meaning) == 2) {
            (*size)++;
            if (*size >= MAX_WORDS) {
                break;
            }
        }
        fclose(file);
    }
}

void displayDictionary(const struct DictionaryEntry dictionary[], int size) {
    printf("Word\t\tMeaning\n");
    printf("==============================\n");
    for (int i = 0; i < size; i++) {
        printf("%s\t\t%s\n", dictionary[i].word, dictionary[i].meaning);
    }
}

const char* getMeaning(const struct DictionaryEntry dictionary[], int size, const char *word) {
    for (int i = 0; i < size; i++) {
        if (strcmp(dictionary[i].word, word) == 0) {
            return dictionary[i].meaning;
        }
    }
    return "Meaning not found.";
}

void removeWord(struct DictionaryEntry dictionary[], int *size, const char *word) {
    for (int i = 0; i < *size; i++) {
        if (strcmp(dictionary[i].word, word) == 0) {
            // Shift elements to the left to remove the word
            for (int j = i; j < *size - 1; j++) {
                strcpy(dictionary[j].word, dictionary[j + 1].word);
                strcpy(dictionary[j].meaning, dictionary[j + 1].meaning);
            }
            (*size)--;
            printf("Word removed successfully!\n");

            // Update the file after removing the entry
            FILE *file = fopen(FILENAME, "w");
            if (file != NULL) {
                for (int j = 0; j < *size; j++) {
                    fprintf(file, "%s|%s\n", dictionary[j].word, dictionary[j].meaning);
                }
                fclose(file);
            }
            return;
        }
    }
    printf("Word not found in the dictionary.\n");
}

void editWord(struct DictionaryEntry dictionary[], int size, const char *word) {
    for (int i = 0; i < size; i++) {
        if (strcmp(dictionary[i].word, word) == 0) {
            char newMeaning[MAX_MEANING_LENGTH];
            printf("Enter the new meaning for %s: ", word);
            scanf(" %[^\n]", newMeaning);
            strcpy(dictionary[i].meaning, newMeaning);
            printf("Meaning updated successfully!\n");

            // Update the file after editing the entry
            FILE *file = fopen(FILENAME, "w");
            if (file != NULL) {
                for (int j = 0; j < size; j++) {
                    fprintf(file, "%s|%s\n", dictionary[j].word, dictionary[j].meaning);
                }
                fclose(file);
            }
            return;
        }
    }
    printf("Word not found in the dictionary.\n");
}

int main() {
    struct DictionaryEntry dictionary[MAX_WORDS];
    int dictionarySize = 0;

    loadDictionaryFromFile(dictionary, &dictionarySize);

    int choice;
    char inputWord[MAX_WORD_LENGTH];

    do {
        printf("\nMenu:\n");
        printf("1. Add Word\n");
        printf("2. Search Meaning\n");
        printf("3. Display Dictionary\n");
        printf("4. Remove Word\n");
        printf("5. Edit Word\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addWord(dictionary, &dictionarySize);
                break;
            case 2:
                printf("Enter a word to get its meaning: ");
                scanf("%s", inputWord);
                printf("Meaning: %s\n", getMeaning(dictionary, dictionarySize, inputWord));
                break;
            case 3:
                displayDictionary(dictionary, dictionarySize);
                break;
            case 4:
                printf("Enter a word to remove: ");
                scanf("%s", inputWord);
                removeWord(dictionary, &dictionarySize, inputWord);
                break;
            case 5:
                printf("Enter a word to edit: ");
                scanf("%s", inputWord);
                editWord(dictionary, dictionarySize, inputWord);
                break;
            case 0:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 0);

    return 0;
}

