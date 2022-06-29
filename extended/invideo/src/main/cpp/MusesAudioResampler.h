//
// Created by Akshay Verma on 29/06/22.
//

#ifndef OBOE_MUSESAUDIORESAMPLER_H
#define OBOE_MUSESAUDIORESAMPLER_H

#include <math.h>
#include <algorithm>

#include <resampler/MultiChannelResampler.h>
#include <resampler/LinearResampler.h>

/*
 * This class is responsible for creating an audio stream and starting it.
 * It specifies a callback function onAudioReady which is called each time
 * the audio stream needs more data.
 * Inside this callback either silence is rendered or if the isOn variable
 * is true a sine wave will be rendered.
 * The sine wave's frequency is hardcoded to 440Hz inside kFrequency.
 */
class MusesAudioResampler {
public:

    MusesAudioResampler(jint inputSampleRate, jint outputSampleRate, jint channelCount) {
        mResampler = oboe::resampler::MultiChannelResampler::make(
                channelCount, // channel count
                inputSampleRate, // input sampleRate
                outputSampleRate, // output sampleRate
                oboe::resampler::MultiChannelResampler::Quality::Medium); // conversion quality

    }


    oboe::resampler::MultiChannelResampler *mResampler;

};

#endif //OBOE_MUSESAUDIORESAMPLER_H
