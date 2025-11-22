#include <minishell.h>

void	print_prompt()
{
	printf("----------------------------------------------------------\n");
	printf("%s░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░\n", COLOR1);
	printf("%s░░░░░░░░░░░░▒▒▒▒▒┌─┐┌─┐▒▒▒▒▒▒▒┌┐▒▒▒▒┌┐┌┐▒▒▒▒▒▒░░░░░░░░░░░░\n", COLOR2);
	printf("%s░░░░░░░░░░░░▒▒▒▒▒││└┘││▒▒▒▒▒▒▒││▒▒▒▒││││▒▒▒▒▒▒░░░░░░░░░░░░\n", COLOR3);
	printf("%s░░░░░░░░░░░░▒▒▒▒▒│┌┐┌┐├┬─┐┌┬──┤└─┬──┤│││▒▒▒▒▒▒░░░░░░░░░░░░\n", COLOR4);
	printf("%s░░░░░░░░░░░░▒▒▒▒▒│││││├┤┌┐┼┤──┤┌┐││─┤│││▒▒▒▒▒▒░░░░░░░░░░░░\n", COLOR5);
	printf("%s░░░░░░░░░░░░▒▒▒▒▒││││││││││├──│││││─┤└┤└┐▒▒▒▒▒░░░░░░░░░░░░\n", COLOR6);
	printf("%s░░░░░░░░░░░░▒▒▒▒▒└┘└┘└┴┴┘└┴┴──┴┘└┴──┴─┴─┘▒▒▒▒▒░░░░░░░░░░░░\n", COLOR7);
	printf("%s░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░\n", COLOR7);
	printf("%s----------------------------------------------------------\n\n", COLOR0);
	printf("%s - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n", COLOR0);
	printf("%s░░░░░░░░░░░░    /)  /) ~ ┏━━━━━━━━━━━━━━┓     ░░░░░░░░░░░░\n", COLOR0);
	printf("%s░░░░░░░░░░░░   ( •-• ) ~  Violeta & Alex      ░░░░░░░░░░░░\n", COLOR0);
	printf("%s░░░░░░░░░░░░    /づづ  ~ ┗━━━━━━━━━━━━━━┛     ░░░░░░░░░░░░\n", COLOR0);
	printf("%s - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n", COLOR0);
}

char	*handle_missing_user(void)
{
	return ("TMP-Change");
}

char	*handle_missing_path(void)
{
	return ("TMP-Change");
}

char	*prompt(void)
{
	char	*p;
	char	*user;
	char	*curpath;

	user = getenv("$USER");
	if (!user)
		return (handle_missing_user());
	curpath = getenv("$PWD");
	if (!curpath)
		return (handle_missing_path());
	p = (char *)malloc(sizeof(char) + ft_strlen(user) + ft_strlen(curpath) + 2);
	p = ft_strjoin(p, user);
	p = ft_strjoin(p, ":");
	p = ft_strjoin(p, curpath);
	p = ft_strjoin(p, "$");
	return (p);
}
