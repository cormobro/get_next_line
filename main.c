/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonaert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:15:56 by fbonaert          #+#    #+#             */
/*   Updated: 2020/11/09 15:17:31 by fbonaert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int            main(int argc, char **argv)
{
    int        i;
    int        fd;
    char       line[40];

    if (argc == 2)
    {
        i = 0;
        fd = open(argv[1], O_RDONLY);
		while (read(fd, line, BUFFER_SIZE) != 0)
			printf("|%s|\n", line);
        close(fd);
    }
    return (0);
}
