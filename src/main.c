/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 21:46:42 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/07 02:50:52 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wav.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FILE_SIZE	500

t_wav	*get_wav_file(const char *filename)
{
	int		fd;
	char	*raw_file;
	t_wav	*file;

	raw_file = (char *)malloc(sizeof(char) * FILE_SIZE);
	file = (t_wav*)raw_file;
	memset(raw_file, 0, sizeof(char) * FILE_SIZE);
	fd = open(filename, O_RDONLY);
	read(fd, raw_file, FILE_SIZE);
	close(fd);

	return file;
}

int		main(void)
{
	t_wav	*file;

	file = get_wav_file("resources/A440_16b.wav");
	print_file(file);
	play_file(file);

	return (0);
}