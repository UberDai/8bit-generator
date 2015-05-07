/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/06 23:21:27 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/07 02:55:04 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wav.h"
#include <math.h>
#include "AudioToolbox/AudioToolbox.h"

typedef struct	{
	double		phase;
	double		phase_inc;
	int			count;
}				PhaseBlah;

#define INCREMENT	(2 * M_PI * (440 + i * 0.005) / 44100)

static void	callback(void *file, AudioQueueRef queue, AudioQueueBuffer *buf)
{
	int					nsamp;
	short				*samp;
	int					i;

	(void)file;

	nsamp = buf->mAudioDataByteSize / 2;
	samp = buf->mAudioData;

	for (i = 0; i < nsamp; i++)
		samp[i] = (int) (30000.0 * sin(INCREMENT * i));

	printf("Callback\n");
	AudioQueueEnqueueBuffer(queue, buf, 0, NULL);
}

void		play_file(t_wav *file)
{
	AudioQueueRef				queue;
	PhaseBlah					phase = { 0, 2 * M_PI * 440 / 44100, 0 };
	OSStatus					status;
	AudioStreamBasicDescription	fmt;
	AudioQueueBufferRef			buf_ref;

	memset(&fmt, 0, sizeof(AudioStreamBasicDescription));
	fmt.mSampleRate = file->sample_rate;
	fmt.mFormatID = kAudioFormatLinearPCM;
	fmt.mFormatFlags = kAudioFormatFlagIsSignedInteger | kAudioFormatFlagIsPacked;
	fmt.mFramesPerPacket = 1; // Uncompressed
	fmt.mChannelsPerFrame = file->nb_channel;
	fmt.mBytesPerPacket = 2; // 2 = mono, 2 = stereo
	fmt.mBytesPerFrame = 2; // 2 = mono, 2 = stereo
	fmt.mBitsPerChannel = file->bit_per_sample;

	status = AudioQueueNewOutput(&fmt, callback, &phase, CFRunLoopGetCurrent(),
		kCFRunLoopCommonModes, 0, &queue);

	if (status == kAudioFormatUnsupportedDataFormatError)
		die("Bad format");

	AudioQueueAllocateBuffer(queue, 50000, &buf_ref);
	AudioQueueBuffer *buf = buf_ref;
	buf->mAudioDataByteSize = 50000;
	callback(&phase, queue, buf_ref);

	AudioQueueSetParameter(queue, kAudioQueueParam_Volume, 1.0);
	AudioQueueStart(queue, NULL);

	CFRunLoopRunInMode(
		kCFRunLoopDefaultMode,
		(50000 / 2) / fmt.mSampleRate, // seconds
		false // don't return after source handled
	);
}