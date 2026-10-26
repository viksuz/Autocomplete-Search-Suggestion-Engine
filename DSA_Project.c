#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
};

struct TrieNode* createNode() {
    struct TrieNode *newNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    newNode->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

void insert(struct TrieNode *root, const char *word) {
    struct TrieNode *curr = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) {
            curr->children[index] = createNode();
        }
        curr = curr->children[index];
    }
    curr->isEndOfWord = true;
}

void printSuggestions(struct TrieNode *curr, char *prefixBuffer, int length) {
    if (curr == NULL) return;

    if (curr->isEndOfWord) {
        prefixBuffer[length] = '\0';
        printf(" -> %s\n", prefixBuffer);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (curr->children[i] != NULL) {
            prefixBuffer[length] = 'a' + i;
            printSuggestions(curr->children[i], prefixBuffer, length + 1);
        }
    }
}

void autocomplete(struct TrieNode *root, const char *prefix) {
    struct TrieNode *curr = root;
    char buffer[100];
    int length = 0;

    for (int i = 0; prefix[i] != '\0'; i++) {
        int index = prefix[i] - 'a';
        if (curr->children[index] == NULL) {
            printf("No suggestions found for prefix '%s'.\n", prefix);
            return;
        }
        buffer[length++] = prefix[i];
        curr = curr->children[index];
    }

    printf("Suggestions for '%s':\n", prefix);
    printSuggestions(curr, buffer, length);
}

int main() {
    struct TrieNode *root = createNode();
    int n;

    printf("How many words do you want to add to the dictionary? ");
    scanf("%d", &n);

    printf("Enter %d lowercase words:\n", n);
    for (int i = 0; i < n; i++) {
        char word[100];
        scanf("%s", word);
        insert(root, word);
    }

    char prefix[100];
    printf("\nEnter a prefix to search for: ");
    scanf("%s", prefix);

    autocomplete(root, prefix);

    return 0;
}
