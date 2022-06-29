package com.google.oboe.extended.invideo

import java.nio.FloatBuffer

class AudioResampler {

    private var handle: Long = 0

    companion object {
        init {
            System.loadLibrary("invideo")
        }
    }

    fun initStream(
            inputSampleRate: Int,
            outputSampleRate: Int,
            channelCount: Int
    ) {
        handle = createStream(inputSampleRate, outputSampleRate, channelCount)
    }

    fun destroyStream() {
        destroyStream(samplerHandle = handle)
    }

    fun getSampledByteBuffer(
            channelCount: Int,
            inputBuffers: FloatBuffer,
            outputBuffers: FloatBuffer,
            inputFrames: Int
    ): Int {
        return getSampledByteBuffer(channelCount, inputBuffers, outputBuffers, inputFrames, handle)
    }

    // Creates and starts Oboe stream to play audio
    private external fun createStream(
            inputSampleRate: Int,
            outputSampleRate: Int,
            channelCount: Int
    ): Long

    // Closes and destroys Oboe stream when app goes out of focus
    private external fun destroyStream(samplerHandle: Long)

    private external fun getSampledByteBuffer(
            channelCount: Int,
            inputBuffers: FloatBuffer,
            outputBuffers: FloatBuffer,
            inputFrames: Int,
            samplerHandle: Long
    ): Int
}