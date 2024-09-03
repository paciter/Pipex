
#include "pipex.h"
//fonction findpath a pour but de chercher le chemin pour cmd 

char	*find_path(char *cmd, char **envp)
{
	char	**allpaths;
	char	*nicepath;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	allpaths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (allpaths[i])
	{
		part_path = ft_strjoin(allpaths[i], "/");
		nicepath = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(nicepath, F_OK) == 0)
			return (nicepath);
		free(nicepath);
		i++;
	}
	i = -1;
	while (allpaths[++i])
		free(allpaths[i]);
	free(allpaths);
	return (0);
}
void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}
//executer avec un chemin specifique 
void	execute(char *argv, char **envp)
{
	char	**cmd;
	int 	i;
	char	*path;
	
	i = -1;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], envp);
	if (!path)	
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
		error();
}
