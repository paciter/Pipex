#ifndef PIPEX_H
# define PIPEX_H


# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>


char	*find_path(char *cmd, char **envp);
int	pipex(int argc, char **argv, char **envp);
void	error(void);
void	execute(char *argv, char **envp);
void	child_process(char **argv, char **envp, int *fd);
void	parent_process(char **argv, char **envp, int *fd);

#endif