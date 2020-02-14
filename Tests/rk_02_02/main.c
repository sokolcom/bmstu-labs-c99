#include <stdio.h>

#define ZERO 0
#define TWO 2
#define EOLN '\n'
#define SPACE ' '
#define WORD_LENGTH 10
#define LINE_LENGTH 4294967296  // 2^32
#define MAX_LINES 100

#define SUCCESS 0
#define FILE_NOT_FOUND -1
#define EMPTY_ERROR 1
#define VALUE_ERROR 2



void change_order(char *const line, const int length)
{
	char words[LINE_LENGTH / WORD_LENGTH][WORD_LENGTH];
	int words_len[LINE_LENGTH / WORD_LENGTH];
	char symbol;

	int i = ZERO;
	int j = ZERO;
	while (i < length)
	{
		if (symbol != SPACE)
		{
			int k = ZERO;
			while ((line[i] != SPACE) && (i < length))
			{
				words[j][k] = line[i];
				k++;
				i++;
			}
			words_len[j] = k;
			j++;
		}
		i++;
	}
	
	for (int i = ZERO; i < j / TWO; i++)
	{
		char temp[WORD_LENGTH];
		len_temp = words_len[i];
		for (int k = ZERO; k < len_temp; k++)
			temp[k] = words[i][k];

		for (int k = ZERO; k < words_len[j - i - ONE]; k++)
			words[i][k] = words[j - i - ONE][k];

		for (int k = ZERO; k < len_temp; k++)
			words[j - i - ONE] = temp[k];
	}
}


int invert_line(FILE* source, char line[][LINE_LENGTH], const int index)
{
	int length = ZERO;

	char symbol;
	fscanf(source, "%c", &symbol);
	while ((symbol != EOLN) || (symbol != EOF))
	{
		line[index][length] = symbol;
		length++;
		fscanf(source, "%c", &symbol);
	}
	
	cnahge_order(line[index], length);
	return SUCCESS;
}
	
	
int read_file(FILE* source, char text_matrix[][LINE_LENGTH])
{
	if (feof(source))
		return EMPTY_ERROR;
	
	int i = ZERO;
	while (!feof(source))
		if (invert_line(source, text_matrix, i) == VALUE_ERROR)
			return VALUE_ERROR;
		else
			i++;
		
	return SUCCESS;
}


int main()
{
	FILE* input_file = fopen("in.txt", "r");
	if (input_file) 
	{
		char text_matrix[MAX_LINES][LINE_LENGTH];
		int code = read_file(input_file, text_matrix);
		fclose(input_file);
		
		if (code == SUCCESS)
		{
			//FILE* input_file = fopen("in.txt", "w");
			//rewrite_file(input_file, text_matrix);
			//fclose(input_file);
		}
		
		return code;
	}
	else
	{
		printf("File not found!\n");
		return FILE_NOT_FOUND;
	}
}

