#include "pipex.h"



void child_process(char **argv, char **envp, int *fd)
{
    int infile;

    infile = open(argv[1], O_RDONLY, 0777);  // Ouvre le fichier spécifié par argv[1] en mode lecture seule.
    if (infile == -1)  // Vérifie si l'ouverture du fichier a échoué.
        error();  // Appelle la fonction `error()` pour afficher un message d'erreur et quitter le programme.
    //getnextline ici pour lire et stock la line 
    dup2(fd[1], STDOUT_FILENO);  // Redirige la sortie standard (stdout) vers l'extrémité d'écriture du pipe (fd[1]).
    dup2(infile, STDIN_FILENO);  // Redirige l'entrée standard (stdin) vers le fichier ouvert `filein`.
    close(fd[0]);  // Ferme l'extrémité de lecture du pipe car le processus enfant n'en a pas besoin.
    
    execute(argv[2], envp);  // Exécute la commande spécifiée par `argv[2]` en utilisant l'environnement `envp`.
}

void parent_process(char **argv, char **envp, int *fd)
{
    int outfile;

    outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);  // Ouvre ou crée le fichier spécifié par argv[4] en mode écriture, le créant s'il n'existe pas et le vidant s'il existe.
    if (outfile == -1)  // Vérifie si l'ouverture ou la création du fichier a échoué.
        error();  // Appelle la fonction `error()` pour afficher un message d'erreur et quitter le programme.
    //ecrire line stocker get next line 
    dup2(fd[0], STDIN_FILENO);  // Redirige l'entrée standard (stdin) vers l'extrémité de lecture du pipe (fd[0]).
    dup2(outfile, STDOUT_FILENO);  // Redirige la sortie standard (stdout) vers le fichier ouvert `fileout`.
    close(fd[1]);  // Ferme l'extrémité d'écriture du pipe car le processus parent n'en a pas besoin.
    
    execute(argv[3], envp);  // Exécute la commande spécifiée par `argv[3]` en utilisant l'environnement `envp`.
}


int pipex(int argc, char **argv, char **envp)
{
    int pipefd[2];  // Déclare un tableau de deux entiers pour les descripteurs de fichier du pipe.
    pid_t pid1;  // Déclare une variable pour stocker l'identifiant du processus enfant.

    if (argc == 5)  // Vérifie que le nombre d'arguments est correct (devrait être 5).
    {
        if (pipe(pipefd) == -1)  // Crée un pipe et vérifie si la création a échoué.
            error();  // Appelle la fonction `error()` pour afficher un message d'erreur et quitter le programme.

        pid1 = fork();  // Crée un processus enfant.
        if (pid1 == -1)  // Vérifie si le fork a échoué.
            error();  // Appelle la fonction `error()` pour afficher un message d'erreur et quitter le programme.

        if (pid1 == 0)  // Si le processus actuel est le processus enfant.
            child_process(argv, envp, pipefd);  // Appelle la fonction `child_process`.
        
        waitpid(pid1, NULL, 0);  // Attend que le processus enfant se termine.
        parent_process(argv, envp, pipefd);  // Appelle la fonction `parent_process`.
    }
    else
        return (EXIT_FAILURE);  // Si le nombre d'arguments est incorrect, renvoie un échec.

    return (0);  // Renvoie 0 pour indiquer que le programme s'est terminé avec succès.
}

