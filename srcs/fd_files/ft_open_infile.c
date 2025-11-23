/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_infile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:15:59 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/01 13:16:04 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

<<<<<<< HEAD
#include "../minishell.h"

static int	ft_search_open_file(char **tokens, int i)
{
	if (ft_strncmp(tokens[i], "<<", 3) == 0)
		return (1);
	else if (ft_strncmp(tokens[i], "<", 2) == 0)
=======
#include "../includes/minishell.h"

static int	ft_search_open_file(t_redir_type type)
{
	if (type == HEREDOC)
		return (1);
	else if (type == INPUT)
>>>>>>> 4e010f65a06e4435fcfc68b687145507eb73604f
		return (2);
	return (0);
}

<<<<<<< HEAD
static int	ft_open_fdin(char **args, int i)
{
	int		fd_in;

	fd_in = open(args[i + 1], O_RDONLY);
	if (fd_in < 0)
	{
		perror(args[i + 1]);
=======
static int	ft_open_fdin(char *str)
{
	int		fd_in;

	fd_in = open(str, O_RDONLY);
	if (fd_in < 0)
	{
		perror(str);
>>>>>>> 4e010f65a06e4435fcfc68b687145507eb73604f
		fd_in = open("/dev/null", O_RDONLY);
	}
	return (fd_in);
}

<<<<<<< HEAD
static int	ft_handle_heredoc(char **args, int i)
=======
static int	ft_handle_heredoc(char *str_lim)
>>>>>>> 4e010f65a06e4435fcfc68b687145507eb73604f
{
	char	*limiter;
	int		fd_in;

	fd_in = -1;
<<<<<<< HEAD
	limiter = ft_strdup(args[i + 1]);
=======
	limiter = ft_strdup(str_lim);
>>>>>>> 4e010f65a06e4435fcfc68b687145507eb73604f
	ft_here_doc(&fd_in, limiter);
	free(limiter);
	return (fd_in);
}

<<<<<<< HEAD
static void	ft_parse_args(char ***args)
{
	int		args_size;
	char	**temp_args;
	int		i;
	int		j;

	args_size = ft_count_arr(args);
	printf("ARGS_SIZE: %i\n", args_size);
	temp_args = malloc(sizeof(char *) * (args_size + 1));
	i = 0;
	j = 0;
	while (i < args_size)
	{
		if (ft_strncmp((*args)[i], "<<", 3) == 0
			|| ft_strncmp((*args)[i], "<", 2) == 0)
		{
			if ((*args)[i + 1])
				i += 2;
			else
				i++;
			continue ;
		}
		temp_args[j] = ft_strdup((*args)[i]);
		i++;
		j++;
	}
	temp_args[j] = NULL;
	i = 0;
	while ((*args)[i])
		free((*args)[i++]);
	free((*args));
	(*args) = temp_args;
}

int	ft_open_infile(char ***args)
{
	int	i;
	int	result;
	int	fd_in;

	fd_in = STDIN_FILENO;
	i = 0;
	while ((*args)[i])
	{
		result = 0;
		result = ft_search_open_file(*args, i);
		if (result == 1)
		{
			if (fd_in > 2)
				close(fd_in);
			fd_in = ft_handle_heredoc(*args, i);
		}
		else if (result == 2)
		{
			if (fd_in > 2)
				close(fd_in);
			fd_in = ft_open_fdin(*args, i);
		}
		i++;
	}
	ft_parse_args(args);
=======
static void	ft_open_infile_type(t_token *token, int *fd_in)
{
	int	result;

	result = 0;
	result = ft_search_open_file(token->redir->redir_type);
	if (result == 1)
	{
		if (*fd_in > 2)
			close(*fd_in);
		*fd_in = ft_handle_heredoc(token->redir->redir_content->content);
	}
	else if (result == 2)
	{
		if (*fd_in > 2)
			close(*fd_in);
		*fd_in = ft_open_fdin(token->redir->redir_content->content);
	}
}

int	ft_open_infile(t_token *token)
{
	int	fd_in;

	fd_in = STDIN_FILENO;
	while (token)
	{
		if (token->type == WORD)
		{
			token = token->right_side;
			continue ;
		}
		ft_open_infile_type(token, &fd_in);
		token = token->right_side;
	}
>>>>>>> 4e010f65a06e4435fcfc68b687145507eb73604f
	return (fd_in);
}
