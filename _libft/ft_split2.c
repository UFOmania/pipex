#include "libft.h"

static void	handle_quote(char *str, int *i, int *count)
{
	(*i)++;
    while (str[*i] != '\0' && str[*i] != '\'')
        (*i)++;
    if (str[*i] == '\'')
        (*i)++;
    (*count)++;
}


static int count_commands(char *str)
{
    int count;
    int len;
    int i;

    i = 0;
    count = 0;
    len = ft_strlen(str);
    while (i < len)
    {
        if (str[i] == '\'')
            handle_quote(str, &i, &count);
        else if (str[i] != ' ')
        {
            while (i < len && str[i] != ' ' && str[i] != '\'')
                i++;
            count++;
            i++;
        }
        else
            i++;
    }
    return (count);
}

static char	*custom_strdub(char *s, size_t len)
{
	char	*res;

	res = (char *)malloc((len + 1) * sizeof(char));
	if (res == 0)
		return (NULL);
	ft_strlcpy(res, s, len + 1);
	return (res);
}

static int get_split_len(char *str)
{
    int i;

    i = 0;
    if (str[i] == '\'')
    {
        i++; // Skip opening quote
        while (str[i] != '\0' && str[i] != '\'')
            i++;
        if (str[i] == '\'')
            i++; // Include closing quote
        return (i); // Total length including quotes
    }
    else
    {
        while (str[i] != '\0' && str[i] != ' ')
            i++;
        return (i);
    }
}

static void	free_failed_list(char **list, int len)
{
	while (len-- >= 0)
		free(list[len]);
	free(  list);
}
char	**ft_split2(char *str)
{
	int		i;
	char	**cmd_list = NULL;
	int		len;
	int		j;

	cmd_list = malloc((count_commands(str) + 1) * sizeof(char *));
	if (!cmd_list)
		return (NULL);
	j = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i])
		{
			len = get_split_len(str + i);
			cmd_list[j] = custom_strdub(str + i, len);
			if (!cmd_list[j])
				return (free_failed_list(cmd_list, j), NULL);
			j++;
			i += len;
		}
	}
	if (j == 0)
		return (free(cmd_list), NULL);
	cmd_list[j] = NULL;
	return cmd_list;
}

// int main (int ac, char **av)
// {
// 	if (ac == 1)
// 		return 1;
// 	int i = -1;
// 	char **c = ft_split2(av[1]);
// 		printf("hh\n");

// 	while (c[++i])
// 	{
// 		printf("%s\n", c[i]);
// 	}
// }