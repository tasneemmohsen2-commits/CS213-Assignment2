#pragma once
#include <JuceHeader.h>

class PlayerGUI : public juce::Component,
                  public juce::Button::Listener,
                  public juce::Slider::Listener
{
public:
    PlayerGUI();
    ~PlayerGUI() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    // Listener interface so MainComponent can get events
    class Listener
    {
    public:
        virtual ~Listener() = default;
        virtual void onLoadClicked() = 0;
        virtual void onPlayClicked() = 0;
        virtual void onStopClicked() = 0;
        virtual void onRestartClicked() = 0;
        virtual void onPauseClicked() = 0;
        virtual void onEndClicked() = 0;
        virtual void onGoToStartClicked() = 0;
        virtual void onVolumeChanged(float value) = 0;
        virtual void onPositionChanged(float value) = 0;
        virtual void onLoopClicked(bool shouldloop) = 0;
        virtual void onTenSecondsForward() = 0;
        virtual void onTenSecondsBackward() = 0;
        virtual void onMuteClicked() = 0;
    };

    void setListener(Listener* newListener);

private:
    juce::TextButton loadButton{ "Load" };
    juce::TextButton playButton{ "Play" };
    juce::TextButton stopButton{ "Stop" };
    juce::TextButton restartButton{ "Restart" };
    juce::TextButton pauseButton{ "Pause" };
    juce::TextButton endButton{ "End" };
    juce::TextButton goToStartButton{ "Go To Start" };
    juce::TextButton loopButton{ "Loop:off" };
    juce::TextButton TenSecondsForward{ "10s Forward" };
    juce::TextButton TenSecondsBackward{ "10s Backward" };
    juce::TextButton MuteButton{ "Mute" };
    juce::Slider volumeSlider;
    juce::Slider positionSlider;
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;

    Listener* listener = nullptr;
};