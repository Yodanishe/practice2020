#include "trie.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

#define WordsCount 100000
char *Words[WordsCount];
char *UserWords[1000];
char *UserVol[1000];

int Read(char *IFILE) {
  char word[100] = {' '};
  uint32_t CountWord = 0, CountSpace = 0;
  FILE *f;
  printf("\tOpen dictionary: %s\n", IFILE);
  if ((f = fopen(IFILE, "r")) == NULL) {
    perror("fopen");
    exit(1);
  }
  printf("\tRead dictionary\n");
  register int inWord = 0;
  int c;
  int WLen = 0;
  while ((c = getc(f)) != EOF) {
    if (isspace(c) || c == '\n') {
      inWord = 0;
      ++CountSpace;
      if (WLen) {
        word[WLen] = '\0';
        Words[CountWord - 1] = (char *)malloc((WLen + 1) * sizeof(char));
        strcpy(Words[CountWord - 1], word);
      }
      WLen = 0;
    } else {
      word[WLen] = c;
      ++WLen;
      if (inWord == 0) {
        inWord = 1;
        ++CountWord;
      }
    }
  }
  printf("\tDictionary contain %d words.\n", CountWord);
  return CountWord;
}

void mitoa(int n, char s[]) {
  void reverse(char s[]) {
    int i, j;
    char c;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
      c = s[i];
      s[i] = s[j];
      s[j] = c;
    }
  }
  int i, sign;
  if ((sign = n) < 0)
    n = -n;
  i = 0;
  do {
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

int main() {
  int count = Read("dictionary.txt");
  int num = 0;
  struct trie *root;
  int i;
  root = trie_insert(NULL, Words[0], "0");

  for (i = 1; i < WordsCount - (WordsCount - count + 1); i++) {
    char str[20];
    mitoa(i, str);
    root = trie_insert(root, Words[i], str);
  }

  while (1) {
    printf("\n\n===============================================\n");
    char buf[25];
    char check[25];
    printf(" Enter word to fuzzy matching: ");
    scanf("%24s", buf);
    printf("\n");
    num = trie_fuzzy_matching(root, buf, check, 0, 0, num);
    for (int i = 1; i < 6; i++)
      num = trie_fuzzy_matching(root, buf, check, 0, i, num);
    if (num == 0)
      printf("\nYour request was not found");
    num = 0;
    reset(root);
  }
  return 0;
}
