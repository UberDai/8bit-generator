/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wav.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 21:44:13 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/07 02:52:14 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WAV_H
# define WAV_H

typedef struct		s_wav
{
	char			riff[4]; // always RIFF
	int				file_size; // total file size
	char			type[4]; // ex: wav
	char			format[4]; // ex: fmt
	int				format_length; // length of the previous format field ?
	short			format_type;
	short			nb_channel; // 1 = mono, 2 = stereo
	int				sample_rate; // ex: 44100
	int				stuff; // sample_rate * (bit_per_sample / 8) ?
	short			other_stuff;
	short			bit_per_sample; // 8 bits or 16 bits, ...
	char			data_header[4]; // separator for data, always "data"
	int				data_size; // data length
	unsigned char	data[]; // data
}					t_wav;

void	die(const char *message);
void	play_file(t_wav *file);
void	print_wave(const t_wav *file);
void	print_file(const t_wav *file);

#endif
