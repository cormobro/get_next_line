/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonaert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:04:11 by fbonaert          #+#    #+#             */
/*   Updated: 2021/01/03 15:16:59 by fbonaert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

void    ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}
void    ft_putchar(char c)
{
	write(1, &c, 1);
}

static char		*ft_strjoin(char *line, char *tmp)
{
	char *res;
	int i;
	int j;
	
	//ATTENTION PRINTF
	printf("%s\n", "ft_strjoin debut");
	if(!(res = (char *)malloc((ft_strlen(line) + ft_strlen(tmp) + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	if (line)
		while (line[i])
		{
			res[i] = line[i];
			i++;
		}
	j = 0;
	if (tmp)
		while (tmp[j])
		{
			res[i + j] = tmp[j];
			j++;
		}
	res[i + j] = '\0';
	//ATTENTION PRINTF
	printf("%s\n", "ft_strjoin OK");
	return (res);
}

static char		**copy_line(char *tmp, int start, int end, char **line, int k)
{
	int i;

	//ATTENTION PRINTF
	printf("%s\n", "copy_line debut");
	i = 0;
	if (!(line[k] = (char *)malloc((end - start + 1) * sizeof(char))))
		return (NULL);
	while (start < end)
	{
		line[k][i] = tmp[start];
		start++;
		i++;
	}
	line[k][i] = '\0';
	//ATTENTION PRINTF
	printf("%s\n", "copy_line OK");
	return (line);
}

static char		**get_next_line3(char *tmp, char **line)
{
	int i;
	static int k;

	//ATTENTION PRINTF
	printf("%s\n", "get_next_line3 debut");
	i = 0;
	if (line[k] != NULL)
	{
		printf("%s%s\n", "get_next_line3 premiere condition", line[k]);
		tmp = ft_strjoin(line[k], tmp);
		if (line[k])
			free(line[k]);
		printf("|%s|\n", tmp);
	}
	//printf("%s\n", tmp);
	while (tmp[i] && tmp[i] != '\n' && tmp[i] != EOF)
	{
		printf("|%c|\n", tmp[i]);
		i++;
	}
	//ATTENTION PRINTF
	printf("%s\n", "get_next_line3 avant fonctions copies");
	if (tmp[i] == '\n' || tmp[i] == EOF)
	{
		line = copy_line(tmp, 0, i, line, (int)k);
		printf("|%s|\n", tmp);
		printf("%s\n", line[k]);
		k++;
		printf("%d\n", k);
		line = copy_line(tmp, i + 1, ft_strlen(tmp), line, (int)k);
		printf("|%s|\n", line[k]);
	}
	else
		line = copy_line(tmp, 0, i, line, (int)k);
	//ATTENTION PRINTF
	printf("%s\n", "get_next_line3 apres fonctions copies");
	return (line);
}

static int		get_next_line2(const int fd, char **line, unsigned int buffer)
{
	char 		tmp[buffer + 1];
	char		save[buffer + 1];
	int 		i;

	i = 0;
	if (!line || read(fd, tmp, 0) < 0)
	{
		printf("%zd\n", read(fd, tmp, 0));
		printf("Oh dear something went wrong with read()! %s\n", strerror(errno));
		return (-1);
	}
	//CONDITIONS return -1 et 0
	if (read(fd, tmp, buffer) > 0)
	{
		//ATTENTION PRINT
		printf("%s\n", tmp);
		printf("%s\n", "get_next_line2 boucle");
		while (tmp[i] != '\0')
		{
			save[i] = tmp[i];
			i++;
		}
		save[i] = '\0';
		line = get_next_line3(save, line);
	}
	printf("%d\n", fd);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	unsigned int	buffer;

	buffer = BUFFER_SIZE;
	if (buffer <= 0)
		return (-1);
	//ATTENTION PRINTF
	printf("%d\n%d\n", get_next_line2(fd, line, buffer), fd);
	return (get_next_line2(fd, line, buffer));
}

/* int            main(int argc, char **argv)
{
	int        i;
	int        fd;
	char        *line;

	if (argc == 2)
	{
		i = 0;
		fd = open(argv[1], O_RDONLY);
		printf("%d\n", fd);
		while ((get_next_line(fd, &line)) == 1)
		{
			//printf("%s\n%d\n", "tour dans la boucle main", fd);
			ft_putstr(line);
			ft_putchar('\n');
		}
		close(fd);
	}
	return (0);
}
*/
#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "stdio.h"
#include <limits.h>

int	main(int ac, char **av)
{
	char	*line;
	char	*gline;
	int		fd;
	int		gd;
	int		ret;
	int		gret;

	if (ac < 2)
		return (0);
	line = NULL;
	gline = NULL;
	fd = open(av[1], O_RDONLY);
	gd = open(av[2], O_RDONLY);
	printf("OPEN_MAX = %d\n", OPEN_MAX);
	ret = 1;
	gret = 1;
	while (ret > 0 || gret > 0)
	{
		ret = get_next_line(fd, &line);
		printf("[%d]->%s\n", ret, line);
		if (ret >= 0)
			free(line);
	}
}
