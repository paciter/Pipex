#include "pipex.h"
//marche pas probleme dans la comprehension de comment faire marcher cmd1 et cmd2 
int     ftpipex(int argc, char **argv, char**envp)
{
    if (argc != 5)
    {
         perror("Usage: ./pipex infile cmd1 cmd2 outfile");
        return (EXIT_FAILURE);
    }
    int infile;
    int outfile;
    int pipe_fd[2];
    int pid;
    char **cmd1;

    infile = open(argv[1], O_RDONLY);
    if (infile < 0)
    {
        perror("Error opening infile");
        return EXIT_FAILURE;
    }

    outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile < 0)
    {
        perror("Error opening outfile");
        close(infile); // Fermer infile avant de sortir
        return EXIT_FAILURE;
    }
    
    if(pipe(pipe_fd) == -1)
    {
        perror("erreur: impossible creer une pipe");
        return(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0)
    {
        perror("impossible fork proccesus enfant");
        close(infile);
        close(outfile);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if(dup2(infile, STDIN_FILENO == -1))
            perror("impossible rediriger l entree standard");
            exit(EXIT_FAILURE);
        if (dup2(pipe_fd[1], STDOUT_FILENO == -1))
        {
           perror("impossible de rediriger la sortie standard");
           exit(EXIT_FAILURE);
        }
        close(pipefd(0));
        closed(pipefd(1));
        close(infile);

        cmd1[0] = argv[2];
        cmd1[1] = NULL;
        
        if (execve(cmd1[0], cmd1, envp) == -1)
        {
            perror("impossible d executer le code");
            exit(EXIT_FAILURE);
        }
        
    }
    else
    {
        //processus parent
    }



    close(infile);
    close(outfile);

    return(EXIT_SUCCESS);
}



    




















/*
// child_process(f1, cmd1);
// ajouter une protection si dup2() < 0
// dup2 ferme stdin, f1 devient le nouveau stdin
dup2(f1, STDIN_FILENO); // nous voulons que f1 soit l'entrée de execve()
dup2(end[1], STDOUT_FILENO); // nous voulons que end[1] soit la sortie de execve()
close(end[0]); // --> toujours fermer l'extrémité du tuyau que vous n'utilisez pas,
               // tant que le tuyau est ouvert, l'autre extrémité attendra 
               // une sorte d'entrée et ne pourra pas terminer son processus
close(f1);
// fonction execve pour chaque chemin possible (voir ci-dessous)
exit(EXIT_FAILURE);

//et pour le parent similaire avec watpid au debut 
int status;
waitpid(-1, &status, 0); // Attendre la fin d'un processus enfant et récupérer son statut
dup2(f2, STDOUT_FILENO); // f2 devient la sortie standard (stdout)
dup2(end[0], STDIN_FILENO); // end[0] devient l'entrée standard (stdin)
close(end[1]); // Fermer l'extrémité du tuyau que vous n'utilisez pas (ici end[1])
close(f2); // Fermer f2 car il est maintenant redirigé vers stdout
// fonction execve pour chaque chemin possible (voir ci-dessous)
exit(EXIT_FAILURE); // Quitter en cas d'échec d'execve


// parsing (somewhere in your code)
char *PATH_from_envp;
char **mypaths;
char **mycmdargs;
// retrieve the line PATH from envp
PATH_from_envp = ft_substr(envp ....);
mypaths = ft_split(PATH_from_envp, ":"); // see section 4 for a
                                            small note[0]
mycmdargs = ft_split(ag[2], " ");
// in your child or parent process
int  i;
char *cmd;
i = -1;
while (mypaths[++i])
{
    cmd = ft_join(mypaths[i], ag[2]); // protect your ft_join
    execve(cmd, mycmdargs, envp); // if execve succeeds, it exits
    // perror("Error"); <- add perror to debug
    free(cmd) // if execve fails, we free and we try a new path
}
return (EXIT_FAILURE);


void    pipex(int f1, int f2, char *cmd1, char *cmd 2)
{
    int   end[2];
    int   status;
    pid_t child1;
    pid_t child2;
    pipe(end);
    child1 = fork();
    if (child1 < 0)
         return (perror("Fork: "));
    if (child1 == 0)
        child_one(f1, cmd1);
    child2 = fork();
    if (child2 < 0)
         return (perror("Fork: "));
    if (child2 == 0)
        child_two(f2, cmd2);
    close(end[0]);         // this is the parent
    close(end[1]);         // doing nothing
    waitpid(child1, &status, 0);  // supervising the children
    waitpid(child2, &status, 0);  // while they finish their task
int main(int argc, char **argv, char **envp)
{
     int f1;
     int f2;
     f1 = open(ag[1], O_RDONLY);
     f2 = open(ag[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
     if (f1 < 0 || f2 < 0)
          return (-1);
     pipex(f1, f2, ag, envp);
     return (0);
}


*/