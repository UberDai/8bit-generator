/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 21:46:42 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/08 04:40:31 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wav.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

t_wav	*get_wav_file(const char *filename)
{
	int		fd;
	t_wav	*file;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		die("Could not open the file.");
	file = malloc(sizeof(t_wav));
	bzero(file, sizeof(t_wav));
	read(fd, file, sizeof(t_wav));
	file = realloc(file, file->file_size);
	read(fd, file->data, file->data_size);
	close(fd);

	return (file);
}

int		main(void)
{
	t_wav	*file;
	short	*data;
	t_sound	sound;
	int		data_length;

	file = get_wav_file("resources/Outkast_The_Whole_World_Stereo.wav");
	print_file(file);

	sound.pitch = 440;
	sound.volume = 1.0;
	sound.timbre = SIN;
	sound.duration = 1.0;
	data_length = generate_sound(file, &sound, &data);

	bzero(file->data, file->data_size);
	memcpy(file->data, data, data_length);

	play_file(file);

	return (0);
}