#ifndef TRIE_H
#define TRIE_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct trie {
  char *value;
  char ch;
  char check;
  struct trie *sibling;
  struct trie *child;
};

struct trie *trie_create();
int trie_fuzzy_matching(struct trie *root, char *key, char *check, int i,
                         int prs, int num);
int find(char *key, char *check, int k, int prs);
struct trie *trie_insert(struct trie *root, char *key, char *value);
void reset(struct trie *root);

#endif
