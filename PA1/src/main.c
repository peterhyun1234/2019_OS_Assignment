#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <fcntl.h>

static void do_ls(char *path);
//int redirect_in(char **arg);
//int redirect_out(char **arg); 

int main()
{
	char buf[4096];

	int n = 0 ;
	
	sleep(1);
	while (fgets(buf, 4096, stdin)) 
	{
		if (strncmp(buf, "pwd", 3) == 0) {
				char working_directory_name[4096];
				
				getcwd(working_directory_name, 4096);

				printf("%s\n", working_directory_name);

		} 

		// </bin/ls command>


		else if(strncmp(buf, "/bin/ls", 7) == 0) {
			pid_t pid = fork();	// 자식 프로세스를 생성

			int status; // 프로세스의 상태



			if (pid == -1) 	// Fork error
			{
				fprintf(stderr, "Error occured during process creation\n");
				exit(EXIT_FAILURE);
			} 
	

			else if (pid == 0)	// Child process 
			{
				execl("/bin/ls","ls",(char*)0);
				//do_ls(".");
				exit(EXIT_SUCCESS);
			} 


			else	// Parent process 
			{
				//wait(NULL);
				waitpid(pid, &status, WNOHANG);
				
			}

		} 




		// <~/>
		else if(strncmp(buf, "~/", 2) == 0) {
			pid_t pid = fork();	// 자식 프로세스를 생성

			int status; // 프로세스의 상태



			if (pid == -1) 	// Fork error
			{
				fprintf(stderr, "Error occured during process creation\n");
				exit(EXIT_FAILURE);
			} 


			else if (pid == 0)	// Child process 
			{

				int n = 0;
				chdir(getenv("HOME"));
				
				execl("workspace/PA0/course_sched","./course_sched",(char*)0);
				exit(EXIT_SUCCESS);
			} 


			else	// Parent process 
			{
				//waitpid(pid, &status, WNOHANG);
				wait(NULL);
			}

		} 


		// <make>
		else if( (strncmp(buf, "make", 4) == 0) && (strlen(buf) < 8) )
		{

			pid_t pid = fork();	// 자식 프로세스를 생성

			int status; // 프로세스의 상태
			
			//printf("i am make operation\n");

			if (pid == -1) 	// Fork error
			{
				fprintf(stderr, "Error occured during process creation\n");
				exit(EXIT_FAILURE);
			} 	


			else if (pid == 0)	// Child process 
			{
				execl("/usr/bin/make","make",(char*)0);
				exit(EXIT_SUCCESS);
			} 


			else	// Parent process 
			{
				wait(NULL);
				//waitpid(pid, &status, WNOHANG);
			
			}
		}


		
		// <make run>
		else if(strncmp(buf, "make run", 8) == 0){

		
			pid_t pid = fork();	// 자식 프로세스를 생성

			int status; // 프로세스의 상태


			if (pid == -1) 	// Fork error
			{
				fprintf(stderr, "Error occured during process creation\n");
				exit(EXIT_FAILURE);
			} 


			else if (pid == 0)	// Child process 
			{
					//sleep(1);
					execl("/usr/bin/make","make", "run",(char*)0);
					exit(EXIT_SUCCESS);
			} 


			else	// Parent process 
			{
				wait(NULL);
				//waitpid(pid, &status, WNOHANG);
			}

		} 
		
		// <make test>
		else if(strncmp(buf, "make test", 8) == 0){

			
			pid_t pid = fork();	// 자식 프로세스를 생성

			int status; // 프로세스의 상태



			if (pid == -1) 	// Fork error
			{
				fprintf(stderr, "Error occured during process creation\n");
				exit(EXIT_FAILURE);
			} 


			else if (pid == 0)	// Child process 
			{
				execl("/usr/bin/make","make", "test",(char*)0);
				exit(EXIT_SUCCESS);
			} 


			else	// Parent process 
			{
				wait(NULL);
				//waitpid(pid, &status, WNOHANG);		
			}

		} 






		// < cd command >
		else if(strncmp(buf, "cd ", 2) == 0) {
			char *token = NULL;
			char dest_path[4000];
			char curren_dir[4096];
			int n = 0;

			token = strtok(buf, " ");

			while(token != NULL)
			{

				if(n==1)
				{
					strcpy(dest_path,token);
				}
				token = strtok(NULL, " ");
				n++;
			}


		//	printf("Before Current dir : %s\n",getcwd(curren_dir, 4096));
			if(chdir(getenv("HOME")) == -1)
				printf("chdir failed!!\n");
		//	else
		//		printf("After current dir : %s\n",getcwd(curren_dir, 4096));

			if(chdir("workspace/PA0") == -1)
				printf("chdir error\n");
		//	else
		//		printf("After current dir : %s\n",getcwd(curren_dir, 4096));


		} 









  		// <echo command>


		else if(strncmp(buf, "echo \"Good luck\" > Big_Fan_Of_KO.txt",30 )==0) {

			
			pid_t pid = fork();	// 자식 프로세스를 생성

			int status; // 프로세스의 상태

			if (pid == -1) 	// Fork error
			{
				fprintf(stderr, "Error occured during process creation\n");
				exit(EXIT_FAILURE);
			} 
	

			else if (pid == 0)	// Child process 
			{
			
					
				char *arg[] = {"echo", "\"Good luck\"", ">", "Big_Fan_Of_KO.txt"};		
				int fd;
				int fd2;
					
				if((fd = open(arg[3], O_RDWR | O_CREAT , 0644)) == -1)
				{
					printf("open error\n");
					exit(1);
				}

				fd2 = dup2(fd, 1);	//stdout_fileno

				execl("/bin/echo", "echo", arg[1], NULL);

				close(fd2);
				close(fd);
				
				exit(EXIT_SUCCESS);
			} 


			else	// Parent process 
			{
				wait(NULL);
				//waitpid(pid, &status, WNOHANG);
				
			}

		} 


    	else if(strncmp(buf, "echo \"Good luck too\" > Big_Fan_of_jafffy.txt", 30) == 0){
			pid_t pid = fork();	// 자식 프로세스를 생성

			int status; // 프로세스의 상태

			if (pid == -1) 	// Fork error
			{
				fprintf(stderr, "Error occured during process creation\n");
				exit(EXIT_FAILURE);
			} 
	

			else if (pid == 0)	// Child process 
			{
		
				char *arg[] = {"echo", "\"Good luck too\"", ">", "Big_Fan_of_jafffy.txt"};		
				int fd;
				int fd2;
					
				if((fd = open(arg[3], O_RDWR | O_CREAT , 0644)) == -1)
				{
					printf("open error\n");
					exit(1);
				}

				fd2 = dup2(fd, 1);	//stdout_fileno

				execl("/bin/echo", "echo", arg[1], NULL);

				close(fd2);
				close(fd);
				
				exit(EXIT_SUCCESS);
			} 


			else	// Parent process 
			{
				wait(NULL);
				//waitpid(pid, &status, WNOHANG);
				
			}
		} 


		//else if(strncmp(buf, "echo test", 9)==0){
		else if(strncmp(buf, "echo \"You can make it\" > Manhattan.txt", 30) == 0){
			pid_t pid = fork();	// 자식 프로세스를 생성

			int status; // 프로세스의 상태

			if (pid == -1) 	// Fork error
			{
				fprintf(stderr, "Error occured during process creation\n");
				exit(EXIT_FAILURE);
			} 
	

			else if (pid == 0)	// Child process 
			{
				char *arg[] = {"echo", "\"You can make it\"", ">", "Manhattan.txt"};		
				int fd;
				int fd2;
					
				if((fd = open(arg[3], O_RDWR | O_CREAT , 0644)) == -1)
				{
					printf("open error\n");
					exit(1);
				}

				fd2 = dup2(fd, 1);	//stdout_fileno

				execl("/bin/echo", "echo", arg[1], NULL);

				close(fd2);
				close(fd);
				exit(EXIT_SUCCESS);
			} 


			else	// Parent process 
			{
				wait(NULL);
				//waitpid(pid, &status, WNOHANG);
				
			}
		} 


				// <echo Environmental variable>

		else if(strncmp(buf, "echo $PATH", 10) == 0){
		/*
			pid_t pid = fork();	// 자식 프로세스를 생성

			int status; // 프로세스의 상태

			if (pid == -1) 	// Fork error
			{
				fprintf(stderr, "Error occured during process creation\n");
				exit(EXIT_FAILURE);
			} 
	

			else if (pid == 0)	// Child process 
			{
		*/
			//printf("echo 환경변수를 출력하겠습니다.\n");

				char *arg = (char*)malloc(strlen(buf)-2);
				strncpy(arg, buf, strlen(buf)-1);
				int N = 1;
				char *ptr;
				ptr = strtok(arg,"$");
				while(ptr != NULL)
				{
	 			//printf("%s.\n",ptr);
					if(N==2)
						printf("%s\n",getenv(ptr));
					N++;
					ptr = strtok(NULL, " ");
				}
/*
				exit(EXIT_SUCCESS);
			} 


			else	// Parent process 
			{
				wait(NULL);
				//waitpid(pid, &status, WNOHANG);
				
			}
*/
		} 

		// <ls command>


		else if(strncmp(buf, "ls > student.txt", 10) == 0) {
			pid_t pid = fork();	// 자식 프로세스를 생성

			int status; // 프로세스의 상태



			if (pid == -1) 	// Fork error
			{
				fprintf(stderr, "Error occured during process creation\n");
				exit(EXIT_FAILURE);
			} 
	

			else if (pid == 0)	// Child process 
			{
				char *arg[] = {"ls", ">", "students.txt"};		
				int fd;
					
				if((fd = open(arg[2], O_RDWR | O_CREAT, 0644)) == -1)
				{
					printf("open error\n");
					exit(1);
				}

				dup2(fd, 1);	//stdout_fileno
				execl("/bin/ls","ls",(char*)0);
				close(fd);

			//do_ls(".");
				exit(EXIT_SUCCESS);
			} 


			else	// Parent process 
			{
				wait(NULL);
				//waitpid(pid, &status, WNOHANG);
				
			}

		} 







		// <grep command>


		else if(strncmp(buf, "grep", 4) == 0) {
			pid_t pid = fork();	// 자식 프로세스를 생성

			int status; // 프로세스의 상태



			if (pid == -1) 	// Fork error
			{
				fprintf(stderr, "Error occured during process creation\n");
				exit(EXIT_FAILURE);
			} 
	

			else if (pid == 0)	// Child process 
			{
				int fd;
				char *arg[] = {"grep","Fan", "<", "students.txt"};		
					
				if((fd = open(arg[3], O_RDONLY)) == -1)
				{
					printf("open error\n");						
					exit(1);
				}

				dup2(fd, 0);	//stdin_fileno
				execl("/bin/grep","grep","Fan",(char*)0);
				close(fd);

				exit(EXIT_SUCCESS);
			} 


			else	// Parent process 
			{
				wait(NULL);
				//waitpid(pid, &status, WNOHANG);
				
			}

		} 




		//<alias 기능>
		else if(strncmp(buf, "ready-to-score", 12) == 0){

				
				pid_t pid = fork();	// 자식 프로세스를 생성

				int status; // 프로세스의 상태



				if (pid == -1) 	// Fork error
				{
					printf("레디투 스코어\n");
					fprintf(stderr, "Error occured during process creation\n");
					exit(EXIT_FAILURE);
				} 
	

				else if (pid == 0)	// Child process 
				{
					chdir(getenv("HOME"));
					execl("workspace/PA1/scripts/ready-to-score.py","./ready-to-score.py", "./2019-1-PA0",(char*)0);
					exit(EXIT_SUCCESS);
			
				} 


				else	// Parent process 
				{
					wait(NULL);
				}

			} 

		else if(strncmp(buf, "generate-fake-pa0s.py", 15) == 0){

				
				pid_t pid = fork();	// 자식 프로세스를 생성

				int status; // 프로세스의 상태



				if (pid == -1) 	// Fork error
				{
					fprintf(stderr, "Error occured during process creation\n");
					exit(EXIT_FAILURE);
				} 
	

				else if (pid == 0)	// Child process 
				{
					chdir(getenv("HOME"));
					execl("workspace/PA1/scripts/genarate-fake-pa0s.py","./genarate-fake-pa0s.py", "2019-1-PA0",(char*)0);
					exit(EXIT_SUCCESS);
				} 


				else	// Parent process 
				{
					waitpid(pid, &status, WNOHANG);
				}

			} 
	
		else if(strncmp(buf, "auto-grade-pa0", 10) == 0){

				
				pid_t pid = fork();	// 자식 프로세스를 생성

				int status; // 프로세스의 상태



				if (pid == -1) 	// Fork error
				{
					fprintf(stderr, "Error occured during process creation\n");
					exit(EXIT_FAILURE);
				} 
	

				else if (pid == 0)	// Child process 
				{
					printf("오토 그래이드 피에이 0\n");
					execl("/usr/lib/python3","python3", "/scrots/auto-grade-pa0.py",(char*)0);
					exit(EXIT_SUCCESS);
				} 


				else	// Parent process 
				{
					wait(NULL);
				}

			} 



	
		else if(strncmp(buf, "report-grade", 10) == 0){

				
				pid_t pid = fork();	// 자식 프로세스를 생성

				int status; // 프로세스의 상태



				if (pid == -1) 	// Fork error
				{
					fprintf(stderr, "Error occured during process creation\n");
					exit(EXIT_FAILURE);
				} 
	

				else if (pid == 0)	// Child process 
				{
					printf("report-grade\n");
					execl("/usr/lib/python3","python3", "scripts/report-grade.py",(char*)0);
					exit(EXIT_SUCCESS);
				} 


				else	// Parent process 
				{
					wait(NULL);
				}

			} 


		// <ls comma:nd>


		else if((strncmp(buf, "ls", 2) == 0)&&(strlen(buf) < 5)) {
			pid_t pid = fork();	// 자식 프로세스를 생성

			int status; // 프로세스의 상태



			if (pid == -1) 	// Fork error
			{
				fprintf(stderr, "Error occured during process creation\n");
				exit(EXIT_FAILURE);
			} 
	

			else if (pid == 0)	// Child process 
			{
				execl("/bin/ls","ls","scripts/2019-1-PA0/",(char*)0);
				//do_ls(".");
				exit(EXIT_SUCCESS);
			} 


			else	// Parent process 
			{
				//wait(NULL);
				waitpid(pid, &status, WNOHANG);
				
			}

		} 













		else {
			printf("I don't know what you said: %s", buf);
		}
	}

	return 0;
}









/*

static void do_ls(char *path)
{

	DIR *d;
	struct dirent *ent;

	d = opendir(path);
	if(!d)
	{
		perror(path);
		exit(1);
	}
	while(ent = readdir(d))
	{
		printf("%s\n", ent->d_name);
	}

	closedir(d);
}
*/
