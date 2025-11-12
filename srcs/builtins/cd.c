int	bt_cd(char dc)
{
	char	*pwd;
	char	*last_dc;
	char	*curpath;

	if(!bt_pwd())
		return(EXIT_FAILURE);
	pwd = getcwd(NULL, 0);
	// CON RUTAS RELATIVAS
	// if no dc operand and the HOME env variable is not empty, take it to home
	if (dc == NULL /*&& env_home != NULL*/)
		chdir("~");
	else if (dc[0] == '/')
	else if (ft_strncmp(dc, "..") == 0)
	{
		last_dc = ft_strrchr(path, '/');
		curpath = ft_strtrim(path, last_dc);
	}
	// RUTAS ABSOLUTAS
	else if (dc != NULL)
	{
		if(chdir(dc) != 0)
			print_msg(MSG, EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
