#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>
#include <fstream>

ALCdevice* device = nullptr;
ALCcontext* context = nullptr;
ALuint source, buffer;

// Simple WAV loader (PCM only)
bool LoadWAV(const char* filename, ALuint& buffer)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cout << "Failed to open WAV file\n";
        return false;
    }

    char chunkId[4];
    file.read(chunkId, 4); // "RIFF"
    file.ignore(4);        // file size
    file.read(chunkId, 4); // "WAVE"

    file.read(chunkId, 4); // "fmt "
    int subchunk1Size;
    file.read((char*)&subchunk1Size, 4);

    short audioFormat, numChannels;
    int sampleRate, byteRate;
    short blockAlign, bitsPerSample;

    file.read((char*)&audioFormat, 2);
    file.read((char*)&numChannels, 2);
    file.read((char*)&sampleRate, 4);
    file.read((char*)&byteRate, 4);
    file.read((char*)&blockAlign, 2);
    file.read((char*)&bitsPerSample, 2);

    // Skip extra bytes if present
    if (subchunk1Size > 16)
        file.ignore(subchunk1Size - 16);

    // Find "data" chunk
    char dataHeader[4];
    int dataSize;
    while (true) {
        file.read(dataHeader, 4);
        file.read((char*)&dataSize, 4);
        if (strncmp(dataHeader, "data", 4) == 0)
            break;
        file.ignore(dataSize);
    }

    char* data = new char[dataSize];
    file.read(data, dataSize);

    ALenum format = 0;
    if (bitsPerSample == 8)
        format = (numChannels == 1) ? AL_FORMAT_MONO8 : AL_FORMAT_STEREO8;
    else if (bitsPerSample == 16)
        format = (numChannels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, data, dataSize, sampleRate);

    delete[] data;
    return true;
}

void InitAudio()
{
    device = alcOpenDevice(nullptr);
    context = alcCreateContext(device, nullptr);
    alcMakeContextCurrent(context);
}

void PlayTestSound()
{
    alGenSources(1, &source);

    if (!LoadWAV("resources/Audio/Original_chalisa.wav", buffer)) {
        std::cout << "WAV load failed\n";
        return;
    }

    alSourcei(source, AL_BUFFER, buffer);
    alSourcef(source, AL_GAIN, 1.0f);
    alSourcei(source, AL_LOOPING, AL_TRUE);

    alSourcePlay(source);
}

void CleanupAudio()
{
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);

    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}
