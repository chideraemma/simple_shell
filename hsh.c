#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[], char *envp[])
{
	char buffer[BUFFER_SIZE];
	pid_t pid;
	(void)argc;
	(void)argv;
	while (1)
	{
		/*Display prompt and wait for user input*/
		printf("$ ");
		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
		{
			/*Handle end of file condition (Ctrl+D)*/
			printf("\n");
			break;
		}
		/*Remove trailing newline character*/
		buffer[strcspn(buffer, "\n")] = 0;
		/*Fork a child process to execute the command*/
		pid = fork();
		if (pid == 0)
		{
			/*Child process*/
			if (execve(buffer, argv, envp) == -1)
			{
				/*Handle error if executable cannot be found*/
				perror(buffer);
			}
			exit(EXIT_FAILURE);
		} else if (pid < 0)
		{
			/*Handle error if fork fails*/
			perror("fork");
		}
		else
		{
			/*Parent process*/
			wait(NULL);
		}
	}
	return (EXIT_SUCCESS);
}
