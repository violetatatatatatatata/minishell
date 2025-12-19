/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 01:45:21 by avelandr          #+#    #+#             */
/*   Updated: 2025/12/19 17:51:06 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_the_other_part(void)
{
	ft_putstr_fd("  - - - - - - - - - - - - - - - - - - - - -  - -\n", 1);
	ft_putstr_fd(COLOR2, 1);
	ft_putstr_fd("░░░░░░░    /)  /) ~ ┏━━━━━━━━━━━━━━┓     ░░░░░░░\n", 1);
	ft_putstr_fd(COLOR2, 1);
	ft_putstr_fd("░░░░░░░   ( •-• ) ~  Violeta & Alex      ░░░░░░░\n", 1);
	ft_putstr_fd(COLOR2, 1);
	ft_putstr_fd("░░░░░░░    /づづ  ~ ┗━━━━━━━━━━━━━━┛     ░░░░░░░\n", 1);
	ft_putstr_fd(COLOR2, 1);
	ft_putstr_fd("  - - - - - - - - - - - - - - - - - - - - -  - -\n", 1);
	ft_putstr_fd(RESET, 1);
}

void	print_prompt(void)
{
	ft_putstr_fd(COLOR3, 1);
	ft_putstr_fd("------------------------------------------------\n", 1);
	ft_putstr_fd(COLOR0, 1);
	ft_putstr_fd("░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░\n", 1);
	ft_putstr_fd(COLOR1, 1);
	ft_putstr_fd("░░░░░░░▒▒▒▒▒┌─┐┌─┐▒▒▒▒▒▒▒┌┐▒▒▒▒┌┐┌┐▒▒▒▒▒▒░░░░░░░\n", 1);
	ft_putstr_fd(COLOR2, 1);
	ft_putstr_fd("░░░░░░░▒▒▒▒▒││└┘││▒▒▒▒▒▒▒││▒▒▒▒││││▒▒▒▒▒▒░░░░░░░\n", 1);
	ft_putstr_fd(COLOR3, 1);
	ft_putstr_fd("░░░░░░░▒▒▒▒▒│┌┐┌┐├┬─┐┌┬──┤└─┬──┤│││▒▒▒▒▒▒░░░░░░░\n", 1);
	ft_putstr_fd(COLOR4, 1);
	ft_putstr_fd("░░░░░░░▒▒▒▒▒│││││├┤┌┐┼┤──┤┌┐││─┤│││▒▒▒▒▒▒░░░░░░░\n", 1);
	ft_putstr_fd(COLOR5, 1);
	ft_putstr_fd("░░░░░░░▒▒▒▒▒││││││││││├──│││││─┤└┤└┐▒▒▒▒▒░░░░░░░\n", 1);
	ft_putstr_fd(COLOR6, 1);
	ft_putstr_fd("░░░░░░░▒▒▒▒▒└┘└┘└┴┴┘└┴┴──┴┘└┴──┴─┴─┘▒▒▒▒▒░░░░░░░\n", 1);
	ft_putstr_fd(COLOR7, 1);
	ft_putstr_fd("░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░\n", 1);
	ft_putstr_fd(COLOR3, 1);
	ft_putstr_fd("------------------------------------------------\n", 1);
	ft_putstr_fd(COLOR2, 1);
	print_the_other_part();
}

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	new_str = ft_strjoin(s1, s2);
	free(s1);
	return (new_str);
}

char	*prompt(t_shell *data)
{
	char	buff[PATH_MAX];
	char	*user;
	char	*cwd;
	char	*p;

	user = ft_getenv("USER", data->env);
	if (!user)
		user = "minishell";
	cwd = ft_getenv("PWD", data->env);
	if (!cwd)
		cwd = getcwd(buff, PATH_MAX);
	p = ft_strdup(user);
	p = ft_strjoin_free(p, ":");
	p = ft_strjoin_free(p, cwd);
	p = ft_strjoin_free(p, "$ ");
	return (p);
}
