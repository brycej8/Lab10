#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Trie{
    struct Trie *children[26];
    int count;

};

void insert(struct Trie **ppTrie, char *word)
{
    struct Trie* trie = *ppTrie;
    if (!trie) {
        trie = (struct Trie*) calloc(1, sizeof(struct Trie));
        *ppTrie = trie;
    }
    for (int i = 0; word[i] != '\0'; i++) {
        char c = word[i];
        if (c >= 'a' && c <= 'z') {
            c -= 'a';
            if (!trie->children[c]) {
                trie->children[c] = (struct Trie*) calloc(1, sizeof(struct Trie));
            }
            trie = trie->children[c];
        }
    }
    trie->count++;
}

int numberOfOccurances(struct Trie *pTrie, char *word)
{
    for (int i = 0; word[i] != '\0'; i++)
    {
        char letter = word[i];
        if (letter <= 'z' && letter >= 'a')
        {
            letter = letter - 'a';
            pTrie = pTrie->children[letter];

            if (!pTrie)
                return 0;
            
        }
    }

    return pTrie->count;
}

struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (!pTrie)
        return NULL;

    for (int i=0; i<26; i++)
    {
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }

    free(pTrie);
    return NULL;
}

int main(void)
{
    //read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure
    struct Trie *trie;

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    for (int i=0;i<5;i++)
    {
        insert(&trie, pWords[i]);
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);

    if (trie != NULL)
        printf("There is an error in this program\n");

    return 0;
}