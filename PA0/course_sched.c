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

int Find_subject_num(char* subject);
void rmvfirst(char* buf);
void sorting_1 (struct CourseEntry ce[], int order[]);
int main(int argc, char** argv)
{

	FILE *fp = NULL;
	
	struct CourseEntry ce[20];

	int i = 0;
	int n = 0;
	int k = 0;
	int N = 0;
	char* info[10];
	char* info2[10];
	char buf[BUFSIZ];
	char sub1[BUFSIZ];
	char sub2[BUFSIZ];
	memset(sub1, 0x00, BUFSIZ);
	memset(sub2, 0x00, BUFSIZ);
	memset(buf, 0x00, BUFSIZ);
	int Order[6] = {0,};
	fp = fopen("./in/database.csv", "r");


	if(fp == NULL)
	{
		return 0;
	}

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

//		printf("[%d] %s\n",i,info[i]);

		ce[i].difficulty = 5.0;

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
//			printf("sub1 =%s\nsub2 =%s\n", sub1, sub2);
		N = 0;
	}
	


// argv[1]에서 받아온 데이터 파싱
	FILE *fp2 = NULL;
	

	char buf2[BUFSIZ];
	memset(buf2, 0x00, BUFSIZ);
	fp2 = fopen(argv[1], "r");

	if(fp2 != NULL)
	{

		while(!feof(fp2))
		{

			fgets(buf2, 1000, fp2);
			char* newptr = (char*)malloc(sizeof(char)*(strlen(buf2)+1));
			strcpy(newptr,buf2);
			info2[k] = newptr;
			k++;
		}	
	} 


	// 문자열 파싱
	for(int I; I< k-1; I++)
	{
		char *s1 = malloc(sizeof(char) *30);
		int sub_num[2] = {0,};
		char dif[100];
		strcpy(s1, info2[I]);

		char* ptr = strtok(s1, ",");
		while(ptr != NULL)
		{
			if(N==0) // 과목 이름 받아서 과목 번호 찾기
			{
				sub_num[I] = Find_subject_num(ptr);
			}
			else if(N == 1)	// 과목 난이도 받고 과목에 배정
			{
				rmvfirst(ptr);
	 			strcpy(dif, ptr);
				ce[sub_num[I]].difficulty = atof(dif); 
			}


			
		//	printf("%s\n", ptr); 
			
			ptr = strtok(NULL, ",");
			N++;
		}
//			printf("sub1 =%s\nsub2 =%s\n", sub1, sub2);
		N = 0;
	}



	// 순서 초기화
	for(int u = 0; u < 6; u++)
	Order[u] = u;

	
	
	/*
	printf("Before first sorting : ");

	for(int c = 0; c < 6; c++)
	printf("%d ",Order[c]);
	printf("\n\n");

*/
	sorting_1(ce, Order);


/*

	printf("After first sorting : ");

	for(int a = 0; a < 6; a++)
	printf("%d ",Order[a]);
	printf("\n\n");


for(int a = 0; a < i; a++)
	{
	

		printf("과목이름 : %s\n", ce[a].name);
		printf("과목 난이도 : %f\n", ce[a].difficulty);
		printf("선수 과목의 수 : %d\n", ce[a].n_prerequisites);

		for(int b = 0; b < ce[a].n_prerequisites; b++)
			printf("선수과목 %d : %s\n",b+1,ce[a].prerequisites[b].name);

		printf("\n\n");
	}

	*/
	for(int a = 0; a < i; a++)
	{
		printf("%s\n",ce[Order[a]].name);
	}

	fclose(fp);
//	fclose(fp2);

  return 0;
}


void rmvfirst(char *buf)
{
	int i=0;
	for(i=1;buf[i];i++)
		buf[i-1] = buf[i];

	buf[i-1] = '\0';
}


int Find_subject_num(char* subject)
{

	for(int a = 0; a<5; a++)
	{
		if(strcmp(subject,"Computer Programming") == 0)
			return 0;
		else if(strcmp(subject, "Discrete Mathematics") == 0)
			return 1;
	   else if(strcmp(subject, "Digital Systems") == 0)
			return 2;
		else if(strcmp(subject, "Data Structures") == 0)
			return 3;
		else if(strcmp(subject, "Computer Architecture") == 0)
			return 4;
		else
			return 5;
	}

}

// 선수과목 0인 과목들 sorting
void sorting_1 (struct CourseEntry ce[], int order[])
{

	int temp = 0;

	int APB_order[6] = {2, 5, 4, 3, 1, 6}; // 각 과목의 알파벳 순서

	// 난이도 비교 sorting(Bubble Sorting)
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			if(ce[order[j]].difficulty < ce[order[j+1]].difficulty){
				temp = order[j];
				order[j] = order[j+1];
				order[j+1] = temp;
			}
		}
	}
	// 선수 과목 0이고  난이도가 같을 때 sorting
	for(int i=0; i<3; i++)
	{
		for(int j = 0; j<2; j++)
		{
			if((ce[order[j]].difficulty == ce[order[j+1]].difficulty)&&(APB_order[order[j]] > APB_order[order[j+1]]))	// 난이도 같고 알파벳 순서가 낮으면
			{
				temp = order[j];
				order[j] = order[j+1];
				order[j+1] = temp;
			}
		}
	}

}

