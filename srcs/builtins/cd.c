int	bt_cd(char dc)
{
	char	*pwd;
	char	*last_dc;
	char	*curpath;

	if(!bt_pwd())
		return(EXIT_FAILURE);
	pwd = getcwd(NULL, 0);
	curpath = dc;
	// CON RUTAS RELATIVAS
	// if no dc operand and the HOME env variable is not empty, take it to home
	if (curpath == NULL /*&& env_home != NULL*/)
		chdir("~");
//	else if (dc[0] == '/')
		// hacer algo
	// si se le pasa el ..
	last_dc = ft_strrchr(curpath, '/');
	while (ft_strncmp(last_dc, "..") == 0 && curpath != NULL)
	{
		last_dc = ft_strrchr(curpath, '/');
		curpath = ft_strtrim(curpath, last_dc);
	}
	// RUTAS ABSOLUTAS
	if (curpath != NULL)
	{
		if(chdir(dc) != 0)
			print_msg(MSG, EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
