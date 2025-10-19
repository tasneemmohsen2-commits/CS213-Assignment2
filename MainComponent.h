#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"
#include "PlayerGUI.h"

class MainComponent : public juce::AudioAppComponent,
                      public PlayerGUI::Listener
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

private:
    PlayerGUI playerGUI;
    PlayerAudio playerAudio;
    std::unique_ptr<juce::FileChooser> fileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
