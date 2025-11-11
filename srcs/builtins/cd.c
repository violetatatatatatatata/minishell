int bt_cd(char *dc)
{
	char	*current;
	char	*target_path;
	char	*env_home;

	current = getcwd(NULL, 0);
	if (current == NULL)
		perror("cd: failed to retrieve current directory");
	env_home = get_env("HOME");
	if (dc == NULL)
	{
		target_path = env_home;
		if (target_path == NULL)
		{
			free(current);
			perror("cd: HOME not set");
		}
	}
	else
		target_path = dc;
	if (chdir(target_path) != 0)
	{
		free(current); 
		perror("Error: No such file or directory");
	}
	return (update_variables((current));
}
