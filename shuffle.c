#include <stdio.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <errno.h> 
#include <string.h> 
#include <fcntl.h> 
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
FILE *fp;
//char *tokenizer;
int f=0;
struct stat sa;
char *buffer;
int numberOfLines=0 ;
FILE *wp;
char *in = NULL;
char *out= NULL;
int value =0;



//Error handling for 3 arguments
if(argc!=5)
{
	fprintf(stderr,"Usage: shuffle -i inputfile -o outputfile\n");
	exit(1);
}

opterr=0;

while((value = getopt (argc, argv, "i:o:")) != -1)
{
  switch(value)
  {
	case 'i':
		in = strdup(optarg);
		break;
	case 'o':
		out = strdup(optarg);
		break;
	case '?':
		  fprintf(stderr,"Usage: shuffle -i inputfile -o outputfile\n");
		  exit(1);
	default:
		  fprintf(stderr,"Usage: shuffle -i inputfile -o outputfile\n");
		  exit(1);
   }	
}

	fp=fopen(in,"r");
	if(fp==NULL)
	{
		 fprintf(stderr,"Error: Cannot open file %s\n",argv[2]);
		 exit(1);
	}
wp = fopen(out,"w");
if(wp==NULL)
{
 fprintf(stderr,"Cannot open file for writing\n");
 exit(1);
}
f = fileno(fp);
fstat(f,&sa);
int fileSize = sa.st_size;
buffer = malloc(sizeof(char)*(sa.st_size));
if(buffer==NULL)
{
 fprintf(stderr,"File cannot be read");
 exit(1);
}
int temp =fread(buffer,sa.st_size,1,fp);

 if(temp<0)
 {
	fprintf(stderr,"File cannot be read");
	exit(1);
}

//printf("%s\n", buffer);

for(int i=0 ; i < sa.st_size ; i++)
  {
	if(buffer[i]=='\n')
	{
		numberOfLines++;
		//printf("%d\n",numberOfLines);
	}
  }	
//char *array[numberOfLines];

char **array = malloc(sizeof(char*)*(numberOfLines));

//fread(buffer,sa.st_size,1,fp);
//printf("%s\n", buffer);
//Reading the first token

/*
tokenizer = strtok(buffer,"\n");

int j = 0;
	while(tokenizer!=NULL)
	{
		if(j<numberOfLines)
		{
			array[j] = malloc(sizeof(char)*(strlen(tokenizer)+1));
			strcpy(array[j], tokenizer);
			tokenizer=strtok(NULL,"\n");
			j++;
		}
	}
*/

//char *ptr= malloc(sizeof(char)*512); 

//int b=0;
int e=0;
int store =0;
//int fileSize = sa.st_size;

	for(int i=0;i < fileSize ; i++)
	{
 		if(buffer[i]=='\n')
		{
			buffer[i] = '\0';
			array[store]= (buffer + (i-e));
			store++;
			e=0;
		}
		else
		{
		  e++;
		}
	}
//while(buffer!=NULL)

	/*
	for(int k=0; k<numberOfLines ; k++)
	{
		printf("%s\n",array[k]);
	}	
	*/

fclose(fp);
//int  even = 0;
//char *finalarray[numberOfLines];
/*
wp = fopen(out,"w");
if(wp==NULL)
{
 fprintf(stderr,"Cannot open file for writing\n");
}
*/
int beg = 0;
int end = numberOfLines-1;
	while(beg<=end)
	{
		if(beg==end)
		{
			fwrite(array[beg],strlen(array[beg]),1,wp);
			fwrite("\n",1,1,wp);
		}
		else
		{
			 fwrite(array[beg],strlen(array[beg]),1,wp);
			 fwrite("\n",1,1,wp);
			 fwrite(array[end],strlen(array[end]),1,wp);
			 fwrite("\n",1,1,wp);
		}
		
	 beg++;
	 end--;
	}	
	//fwrite("\n",1,1,wp);
	free(buffer);
	free(array);
			
	fclose(wp);
	
}




 
