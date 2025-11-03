#pragma once
#include <JuceHeader.h>


class PlayerAudio
{
public:
    PlayerAudio();
    ~PlayerAudio();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();
    //position slider
    double getLengthInSeconds() const;
    void setPosition(double newPositionInSeconds);
    double getCurrentPosition() const;


    void loadFile(const juce::File& file);
    void play();
    void stop();
    void restart();
    void pause();
    void end();
    void goToStart();
    void setGain(float gain);
    void setLooping(bool shouldloop);
    bool isLooping()const;
    void TenSecondsForward();
    void TenSecondsBackward();
    void ToggleMute();
    void SaveSession(const juce::String& , const juce::String&);
    void LoadSession(const juce::String&);

    juce::String title, artist, durationString, fileName;
    juce::String getTitle() const;
    juce::String getArtist() const;
    juce::String getDurationString() const;
    juce::String getFileName() const;
    void playNext();
    void playPrevious();



private:
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    bool looping = false;
    bool muted = false;
    float last_volume = 1.0f;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerAudio)

};