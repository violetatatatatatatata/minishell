/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 01:45:21 by avelandr          #+#    #+#             */
/*   Updated: 2025/11/23 02:04:41 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_prompt(void)
{
	printf("------------------------------------------------\n");
	printf("%s░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░\n", COLOR1);
	printf("%s░░░░░░░▒▒▒▒▒┌─┐┌─┐▒▒▒▒▒▒▒┌┐▒▒▒▒┌┐┌┐▒▒▒▒▒▒░░░░░░░\n", COLOR2);
	printf("%s░░░░░░░▒▒▒▒▒││└┘││▒▒▒▒▒▒▒││▒▒▒▒││││▒▒▒▒▒▒░░░░░░░\n", COLOR3);
	printf("%s░░░░░░░▒▒▒▒▒│┌┐┌┐├┬─┐┌┬──┤└─┬──┤│││▒▒▒▒▒▒░░░░░░░\n", COLOR4);
	printf("%s░░░░░░░▒▒▒▒▒│││││├┤┌┐┼┤──┤┌┐││─┤│││▒▒▒▒▒▒░░░░░░░\n", COLOR5);
	printf("%s░░░░░░░▒▒▒▒▒││││││││││├──│││││─┤└┤└┐▒▒▒▒▒░░░░░░░\n", COLOR6);
	printf("%s░░░░░░░▒▒▒▒▒└┘└┘└┴┴┘└┴┴──┴┘└┴──┴─┴─┘▒▒▒▒▒░░░░░░░\n", COLOR7);
	printf("%s░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░\n", COLOR7);
	printf("%s------------------------------------------------\n\n", COLOR0);
	printf("%s  - - - - - - - - - - - - - - - - - - - - -  - -\n", COLOR0);
	printf("%s░░░░░░░    /)  /) ~ ┏━━━━━━━━━━━━━━┓     ░░░░░░░\n", COLOR0);
	printf("%s░░░░░░░   ( •-• ) ~  Violeta & Alex      ░░░░░░░\n", COLOR0);
	printf("%s░░░░░░░    /づづ  ~ ┗━━━━━━━━━━━━━━┛     ░░░░░░░\n", COLOR0);
	printf("%s  - - - - - - - - - - - - - - - - - - - - -  - -\n", COLOR0);
}

char	*prompt(t_shell *data)
{
	char	*p;
	char	*user;
	char	*curpath;
	char	*tmp_str;

	user = ft_getenv("USER", data->env);
	if (!user)
		user = handle_missing_user();
	curpath = ft_getenv("PWD", data->env);
	/*if (!curpath)
		curpath = handle_missing_path();*/
	p = malloc(1);
	p[0] = '\0';
	tmp_str = ft_strjoin(p, user);
	free(p);
	p = ft_strjoin(tmp_str, ":");
	free(tmp_str);
	tmp_str = ft_strjoin(p, curpath);
	free(p);
	p = ft_strjoin(tmp_str, "$");
	free(tmp_str);
	return (p);
}

char	*handle_missing_user(void)
{
	return ("minishell: ");
}

/*char	*handle_missing_path(void)
{
	return (getcwd());
}*/
