#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


#define MAX_LENGTH 4096

struct CourseEntry {
  char name[MAX_LENGTH]; // 과목의 이름
  struct CourseEntry *prerequisites; // 선수 과목들
  int n_prerequisites; // 선수 과목의 수
  float difficulty; // 과목의 난이도
};

void rmvfirst(char* buf);
int main(int argc, char** argv)
{

	FILE *fp = NULL;
	
	struct CourseEntry ce[20];

	int i = 0;
	int n = 0;
	int N = 0;
	char* info[10];
	char buf[BUFSIZ];
	char sub1[BUFSIZ];
	char sub2[BUFSIZ];
	memset(sub1, 0x00, BUFSIZ);
	memset(sub2, 0x00, BUFSIZ);
	memset(buf, 0x00, BUFSIZ);
	fp = fopen("./in/database.csv", "r");

	if(fp != NULL)
	{

		while(!feof(fp))
		{

			fgets(buf, 1000, fp);
			char* newstrptr = (char*)malloc(sizeof(char)*(strlen(buf)+1));
			strcpy(newstrptr,buf);
			info[n] = newstrptr;
			n++;
		}	
	} 
	ce[i].prerequisites = malloc(sizeof(struct CourseEntry)*ce[i].n_prerequisites);


	// 문자열 파싱
	for(i; i < n-1; i++)
	{
		char *s1 = malloc(sizeof(char) *30);

		strcpy(s1, info[i]);

		printf("[%d] %s\n",i,info[i]);

		char* ptr = strtok(s1, ",");
		while(ptr != NULL)
		{
				if(N==0) // 과목이름
			{
				strcpy(ce[i].name, ptr);
			}
			else if(N == 1)	// 선수 과목의 수 
			{
				ce[i].n_prerequisites = atoi(ptr);
			}
			else if(N == 2)	// 선수 과목 1
			{
				rmvfirst(ptr);
	 			strcpy(sub1, ptr);
				ce[i].prerequisites = &ce[0];
			}	
			else	// 선수 과목 2
			{	
				rmvfirst(ptr);
				strcpy(sub2, ptr);			
				ce[i].prerequisites = &ce[1];
			}

			ptr = strtok(NULL, ",");
		 //	printf("ptr[%d] %s\n",i, ptr); 
			N++;
		}
			printf("sub1 =%s\nsub2 =%s\n", sub1, sub2);
		N = 0;
	}
	




for(int a = 0; a < i; a++)
	{
	

		printf("과목이름 : %s\n", ce[a].name);
		printf("과목 난이도 : %f\n", ce[a].difficulty);
		printf("선수 과목의 수 : %d\n", ce[a].n_prerequisites);

		for(int b = 0; b < ce[a].n_prerequisites; b++)
			printf("선수과목 %d : %s\n",b+1,ce[a].prerequisites[b].name);

		printf("\n\n");
	}

	fclose(fp);

  return 0;
}



void rmvfirst(char *buf)
{
	int i=0;
	for(i=1;buf[i];i++)
		buf[i-1] = buf[i];

	buf[i-1] = '\0';
}

/*
void set_CE(struct CourseEntry *ce)
{
	cd->difficulty = 5;
	ce[i].prerequisites = malloc(sizeof(struct CourseEntry));
}
*/


