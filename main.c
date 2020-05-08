#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include "trie.h"

#define WordsCount 80369
char *Words[WordsCount];
char *UserWords[1000];
char *UserVol[1000];

int Read(char *IFILE)
{
	char word[100]= {' '};
	uint32_t CountWord = 0, CountSpace = 0;
	FILE* f;
	printf("\tOpen dictionary: %s\n", IFILE);
	if((f = fopen(IFILE, "r")) == NULL)
	{
		perror("fopen");
		exit(1);
	}
	printf("\tRead dictionary\n");
	register int inWord = 0;
	int c;
	int WLen = 0;
	while((c = getc(f)) != EOF)
	{
		if(isspace(c) || c == '\n')
		{
			inWord = 0;
			++CountSpace;
			if (WLen)
			{
				word[WLen] = '\0';
				Words[CountWord - 1] = (char*)malloc((WLen + 1) * sizeof(char));
				strcpy(Words[CountWord - 1], word);
			}
			WLen = 0;
		}
		else
		{
			word[WLen] = c;
			++WLen;
			if(inWord == 0)
			{
				inWord = 1;
				++CountWord;
			}
		}
	}
	printf("\tDictionary contain %d words.\n", CountWord);
	return CountWord;
}

void mitoa(int n, char s[])
{
	void reverse(char s[])
	{
		int i, j;
		char c; 
		for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
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

int main(int argc, char **argv)
{	
	int count = Read("dictionary.txt");
	struct trie *root;
	int i, req = -1, zz = 0;
	root = trie_insert(NULL, Words[0], "0");

	for (i = 1; i < WordsCount; i++)
	{
		char str[10];
		mitoa(i, str);
		root = trie_insert(root, Words[i], str);
	}
	
	while (1)
	{
		printf("\n\n\n\n===============================================\n");
			char buf[25];
			char check[25];
			printf(" Enter word to fuzzy matching: ");
			scanf("%24s", buf);
			trie_fuzzy_matching(root, buf, check, 0, 0);
			for(int i = 1; i < 6; i++)
				if(strlen(buf) > (i + 2) / 3)
					trie_fuzzy_matching(root, buf, check, 0, i);
			reset(root);
	}
	return 0;
}

