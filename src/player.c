/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/06 23:21:27 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/08 00:05:29 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wav.h"
#include <math.h>
#include <limits.h>
#include "AudioToolbox/AudioToolbox.h"

#define INCREMENT	(2 * M_PI * (440 + i * 0.005) / 44100)

static void	callback(void *ptr, AudioQueueRef queue, AudioQueueBuffer *buf)
{
	int					data_size;
	short				*data;
	t_wav				*file;

	file = (t_wav*)ptr;
	data_size = buf->mAudioDataByteSize / 2;
	data = buf->mAudioData;

	// for (int i = 0; i < data_size; i++)
	// 	data[i] = (short) (SHRT_MAX * sin(INCREMENT * i));
	memcpy(data, file->data, file->data_size);

	printf("Callback\n");
	AudioQueueEnqueueBuffer(queue, buf, 0, NULL);
}

void		play_file(t_wav *file)
{
	AudioQueueRef				queue;
	OSStatus					status;
	AudioStreamBasicDescription	fmt;
	AudioQueueBufferRef			buf_ref;

	memset(&fmt, 0, sizeof(AudioStreamBasicDescription));
	fmt.mSampleRate = file->sample_rate;
	fmt.mFormatID = kAudioFormatLinearPCM;
	fmt.mFormatFlags = kAudioFormatFlagIsSignedInteger | kAudioFormatFlagIsPacked;
	fmt.mFramesPerPacket = 1; // Uncompressed
	fmt.mChannelsPerFrame = file->nb_channel;
	fmt.mBytesPerPacket = file->bytes_per_frame; // 2 = mono, 4 = stereo
	fmt.mBytesPerFrame = file->bytes_per_frame; // 2 = mono, 4 = stereo
	fmt.mBitsPerChannel = file->bit_per_sample;

	status = AudioQueueNewOutput(&fmt, callback, file, CFRunLoopGetCurrent(),
		kCFRunLoopCommonModes, 0, &queue);

	if (status == kAudioFormatUnsupportedDataFormatError)
		die("Bad format");

	AudioQueueAllocateBuffer(queue, file->data_size, &buf_ref);
	AudioQueueBuffer *buf = buf_ref;
	buf->mAudioDataByteSize = file->data_size;
	callback(file, queue, buf_ref);

	AudioQueueSetParameter(queue, kAudioQueueParam_Volume, 0.4);
	AudioQueueStart(queue, NULL);

	CFRunLoopRunInMode(
		kCFRunLoopDefaultMode,
		(file->data_size / 2) / fmt.mSampleRate, // seconds
		false // don't return after source handled
	);
}