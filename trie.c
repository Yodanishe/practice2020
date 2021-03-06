#include "trie.h"

struct trie *trie_create() {
  struct trie *node;
  if ((node = malloc(sizeof(*node))) == NULL)
    return NULL;
  node->ch = '\0';
  node->check = 0;
  node->value = NULL;
  node->sibling = NULL;
  node->child = NULL;
  return node;
}

int trie_fuzzy_matching(struct trie *root, char *key, char *check, int i,
                        int prs, int num) {
  if (num > 15)
    if ((num > 25) || (prs < 4))
      if ((num > 30) || (prs < 6))
        return num;
  struct trie *node;
  for (node = root; node != NULL; node = node->sibling) {
    check[i] = node->ch;
    if ((node->value != NULL) && (node->check == 0)) {
      int j = find(key, check, i, prs);
      if (j == 1) {
        num++;
        node->check = 1;
        for (int k = i; k >= 0; k--)
          printf("%c", check[i - k]);
        printf("\n");
      }
    }
    if (node->child != NULL)
      num = trie_fuzzy_matching(node->child, key, check, i + 1, prs, num);
  }
  return num;
}

int find(char *key, char *check, int k, int prs) {
  int num = strlen(key);
  int buf = k + 1;
  int miss = 0;
  switch (prs) {
  case 0:
    if (buf - num == 0) {
      for (int i = 0; i < buf; i++) {
        *key = tolower(*key);
        *check = tolower(*check);
        if (*check == *key) {
          key++;
          check++;
          num--;
        }
      }
      if (num == 0) {
        return 1;
      } else {
        return 0;
      }
    }
    return 0;
  case 1:
    if (buf - num == 1) {
      for (int i = 0; i < buf; i++) {
        if (*check == *key) {
          key++;
          check++;
          num--;
        }
      }
      if (num == 0) {
        return 1;
      } else {
        return 0;
      }
    }
    return 0;
  case 2:
    if (buf - num == 2) {
      for (int i = 0; i < buf; i++) {
        if (*check == *key) {
          key++;
          check++;
          num--;
        }
      }
      if (num == 0) {
        return 1;
      } else {
        return 0;
      }
    }
    return 0;
  case 3:
    if (buf - num < 5) {
      for (int i = 0; i < buf; i++) {
        if (*check == *key) {
          key++;
          check++;
          num--;
        }
      }
      if (num == 0) {
        return 1;
      } else {
        return 0;
      }
    }
    return 0;
  case 4:
    if (buf - num == 0) {
      for (int j = num; j > 0; j--) {
        miss = 0;
        for (int i = 0; i < buf; i++) {
          if (*check == *key) {
            num--;
            break;
          }
          miss++;
          check++;
        }
        key++;
        for (int i = 0; i < miss; i++)
          check--;
      }
      if (num == 0) {
        return 1;
      } else {
        return 0;
      }
    } else
      return 0;
  case 5:
    if (buf - num == 0) {
      for (int j = num; j > 0; j--) {
        miss = 0;
        for (int i = 0; i < buf; i++) {
          if (*check == *key) {
            num--;
            break;
          }
          miss++;
          check++;
        }
        key++;
        for (int i = 0; i < miss; i++)
          check--;
      }
      if (num == 1) {
        return 1;
      } else {
        return 0;
      }
    } else
      return 0;
  }
}

struct trie *trie_insert(struct trie *root, char *key, char *value) {
  struct trie *node, *parent, *list;
  parent = NULL;
  list = root;
  for (; *key != '\0'; key++) {
    for (node = list; node != NULL; node = node->sibling) {
      if (node->ch == *key)
        break;
    }
    if (node == NULL) {
      node = trie_create();
      node->ch = *key;
      node->sibling = list;
      if (parent != NULL)
        parent->child = node;
      else
        root = node;
      list = NULL;
    } else {
      list = node->child;
    }
    parent = node;
  }
  if (node->value != NULL)
    free(node->value);
  node->value = strdup(value);
  return root;
}

void reset(struct trie *root) {
  struct trie *node;
  for (node = root; node != NULL; node = node->sibling) {
    node->check = 0;
    if (node->child != NULL)
      reset(node->child);
  }
}
