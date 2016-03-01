/*==========================================
            dictionary format:            
            	word:word
            	word:word
==========================================*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>          	

/* Error codes */
#define WRONG_ARGUMENTS				(-1)
#define CANNOT_OPEN_TARGET_FILE		(-2)
#define CANNOT_OPEN_DICT_FILE		(-3)
#define CANNOT_OPEN_TMP_FILE		(-4)
#define CANNOT_CLOSE_TARGET_FILE	(-5)
#define CANNOT_CLOSE_DICT_FILE		(-6)
#define CANNOT_CLOSE_TMP_FILE		(-7)
#define WRONG_DICT_FROMAT			(-8)
/* END OF error codes */

#define LONGEST_WORD				(44)
#define TRUE						(1)
#define FALSE						(0)
#define TMP_FILE_NAME				("temp.txt")


int findSyno(char * word,FILE * dict,char * target);

int main(int argc, char const *argv[])
{

	FILE * fp_target = NULL;
	FILE * fp_syn_dict = NULL;
	FILE * fp_tmp = NULL;
	int c;
	int rc = 0;
	int index = 0;
	char word[LONGEST_WORD];
	char syno[LONGEST_WORD];

	/* Check arguments count */
	if(3 != argc)
	{
		printf("Usage: synonym <target> <dict>");
		return WRONG_ARGUMENTS;
	}

	/* open files */
	fp_target = fopen(argv[1],"r+");
	if (NULL == fp_target)
	{
		printf("Could not open %s\n",argv[1]);
		return CANNOT_OPEN_TARGET_FILE;
	}

	fp_syn_dict = fopen(argv[2],"r");
	if (NULL == fp_syn_dict)
		{
		printf("Could not open %s\n",argv[2]);
		return CANNOT_OPEN_DICT_FILE;
		}

	fp_tmp = fopen(TMP_FILE_NAME,"w+");
	if (NULL == fp_tmp)
	{
		printf("Could not open %s\n",TMP_FILE_NAME);
		return CANNOT_OPEN_TMP_FILE;
	}

	/* replace with synonym */ 
	while((c=fgetc(fp_target)) != EOF)
	{
		if(isalpha(c))
		{
			word[index] = c;
			index++;	
		}
		else
		{
			/*we have a word!*/
			word[index] = '\0';
			index = 0;
			if(findSyno(word,fp_syn_dict,syno))
			{
				fprintf(fp_tmp,"%s%c",syno,c);
			}
			else
			{
				fprintf(fp_tmp,"%s%c",word,c);
			}
			
		}
	}

	/* we need to put the last word */
	word[index] = '\0';
	index = 0;
	printf("%s\n",word);

	if(findSyno(word,fp_syn_dict,syno))
	{
		fprintf(fp_tmp,"%s%c",syno);
	}
	else
	{
		fprintf(fp_tmp,"%s%c",word);
	}

	/* close opend files */

	if (0 != fclose(fp_tmp))
	{
		printf("Could not close %s\n",TMP_FILE_NAME);
		rc = CANNOT_CLOSE_TMP_FILE;
	}
	if (0 != fclose(fp_target))
	{
		printf("Could not close %s\n",argv[1]);
		rc = CANNOT_CLOSE_TMP_FILE;
	}
	if (0 != fclose(fp_syn_dict))
	{
		printf("Could not close %s\n",argv[2]);
		rc = CANNOT_CLOSE_TMP_FILE;
	}

	return rc;
}
/**
 *
 * function will get a word from a file
 * 
 */

int findSyno(char * word,FILE * dict,char * syno)
{
	int i = 0;
	char line[(LONGEST_WORD*2 )+ 1]; /* we read 2 words + space */
	char option1[LONGEST_WORD];
	char option2[LONGEST_WORD];
	fseek(dict,0,SEEK_SET);
	while(fgets(line,sizeof(line),dict) != NULL)
	{
		i = 0;
		while(line[i] != ':')
		{
			option1[i] = line[i];
			i++;
		}
		option1[i] = '\0';
		i++;

		while(line[i] != '\n' && line[i] != '\0')
		{
			option2[i-(strlen(option1)+1)] = line[i];
			i++;
		}
		option2[i-(strlen(option1)+1)] = '\0';
		if(strcmp(word,option1) == 0)
		{
			strcpy(syno,option2);
			return TRUE;
		}
		else if(strcmp(word,option2) == 0)
		{
			strcpy(syno,option1);
			return TRUE;
		}
	}
	return FALSE;
}