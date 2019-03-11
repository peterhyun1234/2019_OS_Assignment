#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


#define MAX_LENGTH 4096

struct CourseEntry {
  char name[MAX_LENGTH]; // 과목의 이름
  struct CourseEntry* prerequisites; // 선수 과목들
  int n_prerequisites; // 선수 과목의 수
  float difficulty; // 과목의 난이도
};

int main(int argc, char** argv)
{

	FILE *fp = NULL;
	
	struct CourseEntry ce[20];

	int i = 0;
	int n = 0;
	int N = 0;
	char* info[10];
	char buf[BUFSIZ];
	memset(buf, 0x00, BUFSIZ);
	fp = fopen(argv[1], "r");

	if(fp != NULL)
	{

		while(!feof(fp))
		{

			fgets(buf, 100, fp);
			char* newstrptr = (char*)malloc(sizeof(char)*(strlen(buf)+1));
			strcpy(newstrptr,buf);
			info[n] = newstrptr;
			n++;
		}	
	} 



/*
	
	// 문자열 파싱하는 부분(첫번째 방법)
	for(i; i < n-1; i++)
	{
		char* ptr = strtok(info[i], ",");
	
		while(ptr != NULL)
		{
			if(N==0) // 과목이름
			{
		//		strcpy(ce[i].name, ptr);
			}
			else if(N == 1)	// 과목 난이도
			{
		//		ce[i].difficulty = atof(ptr);
			}
			else if(N == 2)	// 선수 과목 1
			{
		//		strcpy(ce[i].prerequisites[0].name, ptr);
			}
			else	// 선수 과목 2
			{
		//		strcpy(ce[i].prerequisites[1].name, ptr);
			}

			if(N >= 2)
				ce[i].n_prerequisites = N - 1;
			else
				ce[i].n_prerequisites = 0;

			ptr = strtok(NULL, " ");
			N++;
		}

		N = 0;

	}
	
*/



	for(i; i < n-1; i++)
	{
		char *s1 = malloc(sizeof(char) *30);

		strcpy(s1, info[i]);

		char* ptr = strtok(s1, ",");
		while(ptr != NULL)
		{
				if(N==0) // 과목이름
			{
		//		strcpy(ce[i].name, ptr);
			}
			else if(N == 1)	// 과목 난이도
			{
		//		ce[i].difficulty = atof(ptr);
			}
			else if(N == 2)	// 선수 과목 1
			{
		//		strcpy(ce[i].prerequisites[0].name, ptr);
			}
			else	// 선수 과목 2
			{
		//		strcpy(ce[i].prerequisites[1].name, ptr);
			}

			if(N >= 2)
				ce[i].n_prerequisites = N - 1;
			else
				ce[i].n_prerequisites = 0;

			printf("%s\n", ptr);

			ptr = strtok(NULL, " ");
			N++;
			printf("N == %d\n",N);
		}
		N = 0;
	}
	





for(int a = 0; a < i; a++)
	{
	
		printf("과목이름 : %s\n", ce[a].name);
		printf("과목 난이도 : %f\n", ce[a].difficulty);
		printf("선수 과목의 수 : %d\n", ce[a].n_prerequisites);

		for(int b = 0; b < ce[a].n_prerequisites; b++)
			printf("선수과목 %d : %s\n ",b+1,ce[a].prerequisites[b].name);

		printf("\n\n");
	}


	fclose(fp);

  return 0;
}
