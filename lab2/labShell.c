#include  <stdio.h>
#include  <sys/types.h>
#include  <stdlib.h>

void launch(char **argv){
  pid_t pid;
  pid = fork();
  if (pid == 0) {
      execvp(argv[0], argv);
  } else if (pid < 0) {
    fprintf(stderr, "Fork Failed");
  } else {
    wait(NULL);
  }
}

void execute(char **argv){
  if (argv[0] == NULL) {
    printf("No command command entered\n");
  }
  else if(strcmp(argv[0], "jobs") == 0){
        argv[0] = "ps";
        argv[1] = "-o";
        argv[2] = "pid,cmd";
        argv[3] = NULL;
        launch(argv);
    }
  else if(strcmp(argv[0], "help") == 0){
        printf("This is Hector's Shell\nType the command then the arguments and hit enter to run.\nThe internal commands are exit, jobs, help.\n");
    }
   else
         launch(argv);
}

void parse(char *line, char **argv){
    while (*line != '\0') {
        while (*line == ' '){
            *line++ = '\0';
        }
        *argv++ = line;
        while (*line != '\0' && *line != ' '){
            line++;
        }
    }
    *argv = '\0';
}

int main(){
    char line[300];
    char * argv[100];
    int check;

    do{
        //initialize line;
        //might not need this part
        int j;
        for(j = 0; j < 300; j++)
            line[j] = '\0';
        //read in line from user
        printf("User> ");
        gets(line);
        printf("\n");
        //check for wrong characters
        int i;
        for(i = 0; i <= 100; i++){
            if((line[i] <= 122 && line[i] >= 97) || (line[i] >= 'Z' && line[i] <= 'A') || (line[i] >= '-' && line[i] <= '9') || line[i] == '_' || line[i] == '\0' || line[i] == ' '){
                //printf("char check works\n");
            }
            else{
                printf("Error: Illegal character ignored. Characters after it were ignored too.\n");
                line[i] = '\0';
            }
        }
        //line length check
        if(line[100] != NULL){
            printf("Error: line was over 100 characters. Line truncated\n");
            line[100] = '\0';
        }

        parse(line, argv);

        if(strcmp(argv[0], "exit") == 0)
            exit(0);
        else
            execute(argv);
    }while(check);
    return 0;
}

