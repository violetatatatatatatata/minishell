void	fill_env(char **env)
{
	t_data	 data;
	
	ft_memset(&data, 0, sizeof(t_data));
	// controlar la ausencia de USER
	if (!getenv("USER"))
		missing_env(data, env)
	else
	{
		data->user_name = getenv(USER);
	}
}

int	get_path(t_data data)
{
	data->curpath = getcwd(NULL, 0); 
}

int	get_home(t_data data)
{
    data->home_pwd = ;
    if (dc == NULL)
    {   
        if (target_path == NULL)
        {
            free(old_pwd);
            perror("cd: HOME not set");
        }
    }   
}
