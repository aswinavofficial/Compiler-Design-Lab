#include <stdio.h>
#include <string.h>
#include <ctype.h>
char keywords[][15] = {"void", "main", "int", "char", "do", "while", "for", "else", "long", "continue", "return", "double", "if", "default", "switch"};
char operators[] = "*+-/%=";
char seperators[] = "(){},;.";
int num_k = 15;
int isOperator(char ch)
{
	int i;
	for (i = 0; i < strlen(operators); i++)
	{
		if (ch == operators[i])
			return 1;
	}
	return 0;
}
int isSeperator(char ch)
{
	int i;
	for (i = 0; i < strlen(seperators); i++)
	{
		if (ch == seperators[i])
			return 1;
	}
	return 0;
}

int isKeyWord(char *ch)
{
	int i;
	for (i = 0; i < num_k; i++)
	{
		if (strcmp(ch, keywords[i]) == 0)
			return 1;
	}
	return 0;
}

void main()
{
	FILE *input, *token;
	input = fopen("input.c", "r");
	token = fopen("token.txt", "w");
	char ch, tempd[10], temps[10];
	int d, s;
	ch = fgetc(input);

	while (ch != EOF)
	{
		if (isdigit(ch))
		{
			d = 0;
			tempd[d++] = ch;
			ch = fgetc(input);
			while (isdigit(ch))
			{
				tempd[d++] = ch;
				ch = fgetc(input);
			}
			tempd[d] = '\0';
			fprintf(token, "%s\t<%s>\tNumber\n", tempd, tempd);
		}
		if (isalnum(ch))
		{
			char t[20], j = 0;
			t[j++] = ch;
			ch = fgetc(input);
			while (isalnum(ch))
			{
				t[j++] = ch;
				ch = fgetc(input);
			}
			if (ch == ' ' || ch == '\n' || isSeperator(ch) || isOperator(ch))
			{
				t[j++] = '\0';
			}

			if (isKeyWord(t) == 1)
			{
				fprintf(token, "%s\t<%s>\tKeyword\n", t, t);
			}
			else
			{
				fprintf(token, "%s\t<%s>\tIdentifier\n", t, t);
			}
		}
		if (isOperator(ch) == 1)
		{
			fprintf(token, "%c\t<%c>\tOperator\n", ch, ch);
		}

		if (isSeperator(ch) == 1)
		{
			fprintf(token, "%c\t<%c>\tSeperator\n", ch, ch);
		}

		ch = fgetc(input);
	}
	fclose(input);
	fclose(token);
	token = fopen("token.txt", "r");
	printf("\nLexemes\tTokens\t\n");
	char out1[30], out2[30], out3[30];
	fscanf(token, "%s%s%s", out1, out2, out3);
	while (!feof(token))
	{
		printf("%s\t%s\t%s\n", out1, out2, out3);
		fscanf(token, "%s%s%s", out1, out2, out3);
	}
}
