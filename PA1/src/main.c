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
	
	
	while (fgets(buf, 4096, stdin)) 
	{

		if (strncmp(buf, "pwd", 3) == 0) {
			pid_t pid = fork();	// 자식 프로세스를 생성

			int status; // 프로세스의 상태



			if (pid == -1) 	// Fork error
			{
				fprintf(stderr, "Error occured during process creation\n");
				exit(EXIT_FAILURE);
			} 
	

			else if (pid == 0)	// Child process 
			{
				char working_directory_name[4096];
				getcwd(working_directory_name, 4096);

				printf("%s\n", working_directory_name);

				exit(EXIT_SUCCESS);
			} 


			else	// Parent process 
			{
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
	 			if(chdir(getenv("HOME")) == -1)
						printf("chdir failed!!\n");
				else
					execl("/workspace/PA0/course_sched","./course_sched",(char*)0);
			} 


			else	// Parent process 
			{
				waitpid(pid, &status, WNOHANG);
				
			}

		} 



		// <make, make run, make test>
			else if(strncmp(buf, "make", 4) == 0) {
			
				
			// <make run>
				if(strncmp(buf, "make run", 8) == 0){

				
				pid_t pid = fork();	// 자식 프로세스를 생성

				int status; // 프로세스의 상태



				if (pid == -1) 	// Fork error
				{
					fprintf(stderr, "Error occured during process creation\n");
					exit(EXIT_FAILURE);
				} 
	

				else if (pid == 0)	// Child process 
				{
						execl("/usr/bin/make","make run",(char*)0);
				} 


				else	// Parent process 
				{
					waitpid(pid, &status, WNOHANG);
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
					execl("/user/bin/make","make test",(char*)0);
				} 


				else	// Parent process 
				{
					waitpid(pid, &status, WNOHANG);		
				}

			} 
				
				// <make>

			else
			{	
				pid_t pid = fork();	// 자식 프로세스를 생성

				int status; // 프로세스의 상태



				if (pid == -1) 	// Fork error
				{
					fprintf(stderr, "Error occured during process creation\n");
					exit(EXIT_FAILURE);
				} 	
	

				else if (pid == 0)	// Child process 
				{
						execl("/usr/bin/make","make",(char*)0);
				} 


				else	// Parent process 
				{
					waitpid(pid, &status, WNOHANG);
				
				}
			}
		}









		// < cd command >
		else if(strncmp(buf, "cd ", 2) == 0) {
			pid_t pid = fork();	// 자식 프로세스를 생성

			int status; // 프로세스의 상태



			if (pid == -1) 	// Fork error
			{
				fprintf(stderr, "Error occured during process creation\n");
				exit(EXIT_FAILURE);
			} 
	

			else if (pid == 0)	// Child process 
			{

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

				exit(EXIT_SUCCESS);
			} 


			else	// Parent process 
			{
				waitpid(pid, &status, WNOHANG);
				
			}

		} 









  		// <echo command>


		else if(strncmp(buf, "echo", 4) == 0) {
			pid_t pid = fork();	// 자식 프로세스를 생성

			int status; // 프로세스의 상태

			if (pid == -1) 	// Fork error
			{
				fprintf(stderr, "Error occured during process creation\n");
				exit(EXIT_FAILURE);
			} 
	

			else if (pid == 0)	// Child process 
			{
				
				//command parsing

				//echo1
				if(strncmp(buf, "echo \"Good luck\" > Big_Fan_Of_KO.txt",30 )==0)
				{
				//	printf("첫번째 문장입니다\n");
					char *arg[] = {"echo", "\"Good luck\"", ">", "Big_Fan_Of_KO.txt"};		
							int fd;
					
					if((fd = open(arg[3], O_RDWR | O_CREAT , 0644)) == -1)
					{
						printf("open error\n");
						exit(1);
					}

					dup2(fd, 1);	//stdout_fileno

					printf("%s",arg[1]);

					close(fd);

		}


				else if(strncmp(buf, "echo \"Good luck too\" > Big_Fan_of_jafffy.txt", 30) == 0)
				{	
					char *arg[] = {"echo", "\"Good luck too\"", ">", "Big_Fan_of_jafffy.txt"};		
								int fd;
					
					if((fd = open(arg[3], O_RDWR | O_CREAT, 0644)) == -1)
					{
						printf("open error\n");
						exit(1);
					}

					dup2(fd, 1);	//stdout_fileno

					printf("%s",arg[1]);

					close(fd);

	
				//	printf("두번쨰 문장입니다.\n");
				}



				else if(strncmp(buf, "echo \"You can make it\" > Manhattan.txt", 30) == 0)
				{
					char *arg[] = {"echo", "\"You can make it\"", ">", "Manhattan.txt"};		
					int fd;
					
					if((fd = open(arg[3], O_RDWR | O_CREAT, 0644)) == -1)
					{
						printf("open error\n");
						exit(1);
					}

					dup2(fd, 1);	//stdout_fileno

					printf("%s",arg[1]);

					close(fd);


				//	printf("세번째 문장입니다.\n");
				}

//				for(int a = 0; a < N; a++)
//					printf("명령어 파싱 순서 %d : %s.\n", a, arg[a]);

			





				// <echo Environmental variable>
/*
				else
				{
				
				}

*/

				
				
				exit(EXIT_SUCCESS);
			} 


			else	// Parent process 
			{
				waitpid(pid, &status, WNOHANG);
				
			}

		} 

     



























		// <ls command>


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
				waitpid(pid, &status, WNOHANG);
				
			}

		} 

		else {
			printf("I don't know what you said: %s", buf);
		}
	}

	return 0;
}











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

/*

int redirect_out_echo(char **arg)
{
	int a;
	int fd;

	for(a = 0; arg[a] != NULL; a++)
	{
		if(!strcmp(arg[a],">"))
		{
			break;
		}
	}

	if(arg[a])
	{
		if(!arg[a+1])
		{
			return -1;
		}
		else
		{
			if((fd = open(arg[a+1],O_RDWR|O_CREAT|S_IROTH, 0644)) == -1)
			{
				perrer(arg[a+1]);
				retrun -1;
			}
		}

		dup2(fd, STDOUT_FILENO);
		close(fd);
		arg[a] = NULL;
		arg[a+1] = NULL;
		for(a = a; arg[a]! = NULL; a++)
		{
			arg[a] = arg[a+2];
		}

		arg[a] = NULL;
	}
	return 0;
}

int redirect_in_echo(char ** arg)
{

	int a;
	int fd;
	
	for(a =0; arg[a] != NULL; a++)
	{
		if(!strcmp(arg[a],">"))
		{
			break;
		}
	}

	if(arg[a])
	{
		if(!arg[a+1])
		{
			return -1;
		}
		else
		{
			if((fd = open(arg[a+1],O_RDONLY)) == -1)
			{
				perrer(arg[a+1]);
				return -1;
			}
		}

		dup2(fd, STDIN_FILENO);
		close(fd);
		for(a = a; arg[a]! = NULL; a++)
		{
			arg[a] = arg[a+2];
		}

		arg[a] = NULL;
	}
	return 0;
}
*/
