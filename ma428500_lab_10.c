#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//void insert(struct Trie **ppTrie, char *word);
//int numberOfOccurances(struct Trie *pTrie, char *word);
//struct Trie *deallocateTrie(struct Trie *pTrie);

typedef struct TrieNode
{
    int count;
    struct TrieNode* children[26];
    
}Trie;

Trie* createTrieNode()
{
    Trie* newNode = (Trie*)malloc(sizeof(Trie));
    newNode->count = 0;

    for (int i = 0; i < 26; i++)
    {
        newNode->children[i] = NULL;
    }

    return newNode;
}

void insert(Trie** ppTrie, char* word)
{
    Trie* pTrie = *ppTrie;

    if (pTrie == NULL)
    {
        pTrie = createTrieNode();
        *ppTrie = pTrie;
    }
    for (int i = 0; word[i] != '\0'; i++)
    {
        char c = word[i];

        if (!pTrie->children[c - 'a'])
        {
            pTrie->children[c - 'a'] = createTrieNode();
        }
        pTrie = pTrie->children[c - 'a'];
    }
    pTrie->count++;
}

int numberOfOccurances(Trie* pTrie, char* word) {
    if (pTrie == NULL)
        return 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        char c = word[i];
        if (!pTrie->children[c - 'a']) {
            return 0;
        }
        pTrie = pTrie->children[c - 'a'];
    }
    return pTrie->count;
}

Trie* deallocateTrie(Trie* pTrie)
{
    if (pTrie == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < 26; i++)
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
    Trie* trie = NULL;

    char* pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    for (int i = 0; i < 5; i++)
    {
        insert(&trie, pWords[i]);
        printf("%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }

    trie = deallocateTrie(trie);

    if(trie != NULL)
        printf("There is an error in this program\n");

    return 0;

}