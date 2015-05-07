/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/06 23:30:30 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/08 00:07:06 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wav.h"
#include <stdio.h>
#include <stdlib.h>

void	die(const char *message)
{
	printf("%s\n", message);
	exit(0);
}

void	print_wave(const t_wav *file)
{
	for (int i = 0; i < file->data_size; i += 2)
	{
		for (int j = 0; j < file->data[i] / 3; j++)
			printf(" ");
		printf(".\n");
	}
}

void	print_file(const t_wav *file)
{
	printf("-----------------------\n");
	printf("riff: %.4s\n", file->riff);
	printf("file size: %i\n", file->file_size);
	printf("type: %.4s\n", file->type);
	printf("format: %.4s\n", file->format);
	printf("format_length: %i\n", file->format_length);
	printf("format_type: %hi\n", file->format_type);
	printf("nb_channel: %hi\n", file->nb_channel);
	printf("sample_rate: %i\n", file->sample_rate);
	printf("stuff: %i\n", file->stuff);
	printf("bytes_per_frame: %hi\n", file->bytes_per_frame);
	printf("bit_per_sample: %hi\n", file->bit_per_sample);
	printf("data_header: %.4s\n", file->data_header);
	printf("data_size: %i\n", file->data_size);
	printf("-----------------------\n");
}