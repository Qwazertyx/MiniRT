#include "../incl/miniRT.h"

char	*ft_free(char *a)
{
	free(a);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buff[10 + 1];
	char		*txt;
	int			i;

	i = 1;
	txt = NULL;
	if (fd < 0 || 10 == 0)
		return (0);
	if (ft_search(buff, '\n') != -1)
	{
		ft_cut(buff);
		txt = ft_join(txt, buff);
		if (txt[0] == '\0')
				txt = ft_free(txt);
	}
	while (ft_search(buff, '\n') == -1 && i > 0)
	{
		i = read(fd, buff, 10);
		if (i <= 0)
			return (txt);
		buff[i] = '\0';
		txt = ft_join(txt, buff);
	}
	return (txt);
}
