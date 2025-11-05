#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"
#include "PlayerGUI.h"

class MainComponent : public juce::AudioAppComponent,
                      public PlayerGUI::Listener,
    public juce::Timer
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    // GUI listener functions
    void onLoadClicked() override;
    void onPlayClicked() override;
    void onStopClicked() override;
    void onRestartClicked() override;
    void onPauseClicked() override;
    void onVolumeChanged(float value) override;
    void onPositionChanged(float value) override;
    void onEndClicked() override ;
    void onGoToStartClicked() override;
    void onLoopClicked(bool shouldloop) override;
    void onsegmentloopClicked(bool enable) override;
    void onTenSecondsForward() override;
    void onTenSecondsBackward() override;
    void onMuteClicked() override;
    void onSaveSessionClicked();
    void onLoadSessionClicked();
    void onSpeedChanged(double value) override;
    void onModeClicked(bool is_dark) override;

    std::vector<juce::File> playlist;
    int currentIndex = 0;
    void onNextClicked() override;
    void onPrevClicked() override;
    void timerCallback();
    void onSetAClicked();
    void onSetBClicked();
    int getPlaylistSize() const;
    juce::String getPlaylistItem(int index) const;
    void onSongSelected(int index);
    void onAddMarkerClicked();
    void onMarkerSelected(double position) override;


private:
    PlayerGUI playerGUI;
    PlayerAudio playerAudio;
    std::unique_ptr<juce::FileChooser> fileChooser;
    double loopStart = 0.0;
    double loopEnd = 0.0;
    bool isSegmentLoopEnabled = false;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};