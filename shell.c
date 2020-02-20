#include <stdio.h>
#include <sys/types.h>
#include<sys/stat.h>
#include <stdlib.h>  ////remove
#include <string.h>
#include <unistd.h>
#include<dirent.h>////DIR

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

int setpgid(pid_t pid, pid_t pgid);
struct dirent *readdir(DIR *dirp);
int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result);
void sighup() 
  
{ 
    signal(SIGHUP, sighup); /* reset signal */
    printf("CHILD: I have received a SIGHUP\n"); 
} 
int ch_p(char *line)
{
  int i,c=0;
  for(i=0;i<strlen(line);i++)
  {
    if(line[i]=='|')
    c++;
  }
  return c;
}
char **pipize(char *line)
{
  char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
        char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
        int i, tokenIndex = 0, tokenNo = 0;

        for(i =0; i < strlen(line); i++){

                char readChar = line[i];
                if(line[i-1] == '|')
                        continue;
                if (readChar == '|' || readChar == '\n' || readChar == '\t'){

                        token[tokenIndex] = '\0';
                        if (tokenIndex != 0){
                                tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
                                strcpy(tokens[tokenNo++], token);
                                tokenIndex = 0;
                        }
                } else {

                        token[tokenIndex++] = readChar;
                }
        }

        free(token);
        tokens[tokenNo] = NULL ;
        return tokens;
}
/* Splits the string by space and returns the array of tokens
*
*/
char **tokenize(char *line)
{
  char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
  char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
  int i, tokenIndex = 0, tokenNo = 0;

  for(i =0; i < strlen(line); i++){

    char readChar = line[i];

    if (readChar == ' ' || readChar == '\n' || readChar == '\t')
    {
      token[tokenIndex] = '\0';
      if (tokenIndex != 0)
      {
	   tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
	   strcpy(tokens[tokenNo++], token);
	   tokenIndex = 0; 
      }
    } 
    else
    {
      token[tokenIndex++] = readChar;
    }
  }
 
  free(token);
  tokens[tokenNo] = NULL ;
   return tokens;
}


int main(int argc, char* argv[])
 {
	char  line[MAX_INPUT_SIZE];            
	char  **tokens;              
	int i;
  char *execArgs[] = { "ls", "&", NULL };

	FILE* fp;
	if(argc == 2) 
    {
		fp = fopen(argv[1],"r");
		if(fp < 0) 
    {
			printf("File doesn't exists.");
			return -1;
		}
	}
    while(1) 
    {			
		/* BEGIN: TAKING INPUT */
		bzero(line, sizeof(line));
		if(argc == 2) { // batch mode
			if(fgets(line, sizeof(line), fp) == NULL) { // file reading finished
				break;	
			}
			line[strlen(line) - 1] = '\0';
		} else { // interactive mode
			printf("$ ");
			scanf("%[^\n]", line);
			getchar();
		}
		printf("Command entered: %s (remove this debug output later)\n", line);
		/* END: TAKING INPUT */

		line[strlen(line)] = '\n'; //terminate with new line
		tokens = tokenize(line);

    if(ch_p(line)!=0)
    {
      int i,g,j,n_p=ch_p(line),stat;
      tokens=pipize(line);
      char **str;
      int pipes[2*n_p];
      for(i=0;i<(2*n_p);i+=2)
      pipe(pipes+i);

      
      for(i=0;i<n_p+1;i++)
      {
        if(i==n_p)
        {
          int len=strlen(tokens[i]);
          tokens[i][len-1]=' ';
          strcat(tokens[i]," ");
        }
        str=tokenize(tokens[i]);
        if(fork()==0)
        {
          if(i==0)
          dup2(pipes[1],1);
          else if(i==n_p)
          dup2(pipes[(2*i)-2],0);
          else
          {
            dup2(pipes[g],0);
            dup2(pipes[g+3],1);
            g=g+2;
          }
          for(j=0;j<(2*n_p);j++)
            close(pipes[j]);

          if(execvp(str[0],str)<0)
          printf(" command not found\n");
        }
      }
      for(j=0;j<(2*n_p);j++)
      close(pipes[j]);

      for(i=0;i<n_p+1;i++)
      wait(&stat);

      continue;
  }
    //system("ls &");
       if(strcmp(tokens[0],"mkdir")==0)
       {
         int cor;
         cor=mkdir(tokens[1],S_IRUSR | S_IRGRP | S_IROTH | S_IXUSR | S_IXGRP | S_IXOTH);
         if(!cor)
         printf("director %s created....:D\n",tokens[1]);
         else 
         {printf("cannot create directory....:( \n");
            exit(1);
         }
         getch();
         system("dir/  \n");
         getch();
       }
       if(strcmp(tokens[0],"echo")==0)
       {
         printf("%s\n",tokens[1]);
       }
       if(strcmp(tokens[0],"rm")==0)
       {   
          if(remove(tokens[1])==0)
          {
            printf(" %s file is removed\n",tokens[1]);
    
          }
          else 
          printf("file cannot be remove\n");
       }
       if(strcmp(tokens[0], "exit")==0)
       {
         printf("......closing.....\n");
         exit(1);
       }
       if(strcmp(tokens[0],"sleep")==0)
       {
           printf("sleep for %s sec\n",tokens[1]);
           sleep(tokens[1]);
       }

       if(strcmp(tokens[0],"cd")==0)
       {
         char s[1000];
         if(chdir(tokens[1])==0)
         {
           printf("directory change to : %s\n",getcwd(s,1000));
           continue;
         }
       } 
        if(strcmp(tokens[0],"pwd")==0)
        {
          char s[1000];
          printf("directory is :%s\n",getcwd(s,1000));
          continue;
        }      
        if(strcmp(tokens[0],"ls")==0)
                {  

                           DIR *dirt = opendir(".");
                           struct dirent *dt;

                           while ((dt = readdir(dirt)) != NULL)
                                   printf("%s  ", dt->d_name);

                           closedir(dirt);
                          printf("\n");
                           continue;
                   }

       pid_t c_pid,pid;
        

        int stat;
        pid=fork();
        for(i=0;tokens[i+1]!=NULL;i++);
        stat=0;
        if(strcmp(tokens[i],"&")==0)
        {
          stat=1;
          tokens[i]=NULL;
        }
        if(pid==-1)
        {
          printf("\nFailed");
          return;
        }
        else if(pid==0)
        { //signal(SIGHUP, sighup);
          if(execvp(tokens[0],tokens)<0);
          perror("execution fail");

          exit(0);
        }
        else
        {  // kill(pid, SIGHUP);
            if(stat==0)
            {
                waitpid(pid,NULL,0);
            }
        }
        
       //do whatever you want with the commands, here we just print them

		for(i=0;tokens[i]!=NULL;i++){
			printf("found token %s (remove this debug output later)\n", tokens[i]);
		}
       
		// Freeing the allocated memory	
		for(i=0;tokens[i]!=NULL;i++){
			free(tokens[i]);
		}
		free(tokens);

	}
	return 0;
}
