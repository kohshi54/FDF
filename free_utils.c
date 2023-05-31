#include "fdf.h"

void	free_split(char **p)
{
	char	**head;

	head = p;
	while (*p)
	{
		free(*p);
		p++;
	}
	free(head);
}
