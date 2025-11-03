int	bt_pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (EXIT_FAILURE);
	printf("%s", pwd);
	return (EXIT_SUCCESS);
}
