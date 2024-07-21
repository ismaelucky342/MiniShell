#include "../includes/minishell.h"

void	ft_free_tree_val(char **value)
{
	char	**holder;

	holder = value;
	while (*value)
	{
		free(*value);
		value++;
	}
	free(holder);
}