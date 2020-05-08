#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct trie {
	char *value;
	char ch;
	char check;
	struct trie *sibling;
	struct trie *child;
};

struct trie *trie_create();
void trie_fuzzy_matching(struct trie *root, char *key, char *check, int i, int prs);
int find(char *key, char *check, int k, int prs);
struct trie *trie_insert(struct trie *root, char *key, char *value);
void reset(struct trie *root);

#endif
