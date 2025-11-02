int	bt_pwd()
{
	if (getcwd() == NULL)
		return (EXIT_FAILURE);
	printf("%s", getcwd());
	return (EXIT_SUCCESS);
}
