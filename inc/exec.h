#ifndef EXEC_H
# define EXEC_H

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	int		fd_in;
	int		fd_out;
	pid_t	pid;
}

#endif