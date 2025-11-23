/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_outfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcaide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:15:59 by aalcaide          #+#    #+#             */
/*   Updated: 2025/09/01 13:16:04 by aalcaide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

<<<<<<< HEAD
#include "../minishell.h"

static int	ft_search_file(char **args, int i)
{
	if (ft_strncmp(args[i], ">", 2) == 0)
		return (1);
	else if (ft_strncmp(args[i], ">>", 3) == 0)
=======
#include "../includes/minishell.h"

static int	ft_search_file(t_redir_type type)
{
	printf("TYPE TOKEN: %i\n", type);
	if (type == OUTPUT)
		return (1);
	else if (type == APPEND)
>>>>>>> 4e010f65a06e4435fcfc68b687145507eb73604f
		return (2);
	return (0);
}

<<<<<<< HEAD
static int	ft_open_output_file(char *filename, int is_append)
=======
static int	ft_open_output_file(char *filename, int mode)
>>>>>>> 4e010f65a06e4435fcfc68b687145507eb73604f
{
	int	fd_out;
	int	flags;

	flags = O_WRONLY | O_CREAT;
<<<<<<< HEAD
	if (is_append == 1)
=======
	if (mode == 1)
>>>>>>> 4e010f65a06e4435fcfc68b687145507eb73604f
		flags |= O_TRUNC;
	else
		flags |= O_APPEND;
	fd_out = open(filename, flags, 0644);
	if (fd_out < 0)
		perror(filename);
	return (fd_out);
}

<<<<<<< HEAD
static void	ft_parse_args(char ***args)
{
	int		args_size;
	char	**temp_args;
	int		i;
	int		j;

	args_size = ft_count_arr(args);
	printf("ARGS_SIZE OUT: %i\n", args_size);
	temp_args = malloc(sizeof(char *) * (args_size + 1));
	i = 0;
	j = 0;
	while (i < args_size)
	{
		if (ft_strncmp((*args)[i], ">>", 3) == 0
			|| ft_strncmp((*args)[i], ">", 2) == 0)
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

int	ft_open_outfile(char ***args)
{
	int	i;
	int	is_append;
	int	fd_out;

	fd_out = STDOUT_FILENO;
	i = 0;
	while ((*args)[i])
	{
		is_append = ft_search_file(*args, i);
		if (is_append == 1 || is_append == 2)
			fd_out = ft_open_output_file((*args)[i + 1], is_append);
		i++;
	}
	ft_parse_args(args);
=======
int	ft_open_outfile(t_token *token)
{
	int	mode;
	int	fd_out;

	fd_out = STDOUT_FILENO;
	while (token)
	{
		if (token->type == WORD)
		{
			token = token->right_side;
			continue ;
		}
		mode = ft_search_file(token->redir->redir_type);
		if (mode == 1 || mode == 2)
			fd_out = ft_open_output_file(token->redir->redir_content->content,
					mode);
		token = token->right_side;
	}
>>>>>>> 4e010f65a06e4435fcfc68b687145507eb73604f
	return (fd_out);
}
