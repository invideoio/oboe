#include <jni.h>
#include <oboe/Oboe.h>
#include "MusesAudioResampler.h"

extern "C" {

JNIEXPORT jlong JNICALL
Java_com_google_oboe_extended_invideo_AudioResampler_createStream(JNIEnv *env, jobject thiz,
                                                                          jint input_sample_rate,
                                                                          jint output_sample_rate,
                                                                          jint channel_count) {
    MusesAudioResampler *oboeResampler = new MusesAudioResampler(input_sample_rate, output_sample_rate,
                                                     channel_count);

    return reinterpret_cast<jlong>(oboeResampler);
}

JNIEXPORT void JNICALL
Java_com_google_oboe_extended_invideo_AudioResampler_destroyStream(JNIEnv *env,
                                                                           jobject thiz,
                                                                           jlong samplerHandle) {
    MusesAudioResampler *oboeResampler = reinterpret_cast<MusesAudioResampler *>(samplerHandle);
    if (oboeResampler) {
        delete oboeResampler->mResampler;
        delete oboeResampler;
    }
}

JNIEXPORT jint JNICALL
Java_com_google_oboe_extended_invideo_AudioResampler_getSampledByteBuffer(
        JNIEnv *env,
        jobject thiz,
        jint channelCount,
        jobject inputBuffer,
        jobject outputBuffer,
        jint inputFrames,
        jlong samplerHandle) {
    MusesAudioResampler *oboeResampler = reinterpret_cast<MusesAudioResampler *>(samplerHandle);
    auto *inputBufferPointer = (float *) env->GetDirectBufferAddress(
            inputBuffer);  // multi-channel buffer to be filled
    auto *outputBufferPointer = (float *) env->GetDirectBufferAddress(
            outputBuffer);  // multi-channel buffer to be filled
    int readSize = 0;

    int numOutputFrames = 0;
    int inputFramesLeft = inputFrames;
    if (oboeResampler) {
        while (inputFramesLeft > 0) {
            if (oboeResampler->mResampler->isWriteNeeded()) {
                oboeResampler->mResampler->writeNextFrame(inputBufferPointer);
                inputBufferPointer += channelCount;
                inputFramesLeft--;
            } else {
                oboeResampler->mResampler->readNextFrame(outputBufferPointer);
                outputBufferPointer += channelCount;
                readSize += channelCount;
                numOutputFrames++;
            }
        }
    }
    return readSize;
}

}
