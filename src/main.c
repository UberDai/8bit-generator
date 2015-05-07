/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 21:46:42 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/08 00:00:12 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wav.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FILE_SIZE	90000

t_wav	*get_wav_file(const char *filename)
{
	int		fd;
	t_wav	*file;

	file = malloc(sizeof(t_wav));
	bzero(file, sizeof(t_wav));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		die("Could not open the file.");
	read(fd, file, sizeof(t_wav));
	file = realloc(file, file->file_size);
	read(fd, file->data, file->data_size);
	close(fd);

	return (file);
}

int		main(void)
{
	t_wav	*file;

	file = get_wav_file("resources/Outkast_The_Whole_World_Stereo.wav");
	print_file(file);

	// for (int i = 0; i < file->data_size; i++)
	// 	printf("%hi\n", file->data[i]);
	play_file(file);

	return (0);
}