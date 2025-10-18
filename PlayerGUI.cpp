#include "PlayerGUI.h"

PlayerGUI::PlayerGUI()
{
    for (auto* btn : { &loadButton, &playButton, &stopButton, &restartButton, &pauseButton, &endButton,&goToStartButton })
    {
        addAndMakeVisible(btn);
        btn->addListener(this);
    }

    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);
}

PlayerGUI::~PlayerGUI() {}

void PlayerGUI::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void PlayerGUI::resized()
{
    int y = 20;
    loadButton.setBounds(20, y, 80, 40);
    playButton.setBounds(110, y, 80, 40);
    stopButton.setBounds(200, y, 80, 40);
    restartButton.setBounds(380, y, 80, 40);
    pauseButton.setBounds(290, y, 80, 40);
    endButton.setBounds(470, y, 80, 40);
    goToStartButton.setBounds(560, y, 80, 40);
    volumeSlider.setBounds(20, 100, getWidth() - 40, 30);
}

void PlayerGUI::buttonClicked(juce::Button* button)
{
    if (listener == nullptr) return;

    if (button == &loadButton) listener->onLoadClicked();
    else if (button == &playButton) listener->onPlayClicked();
    else if (button == &stopButton) listener->onStopClicked();
    else if (button == &restartButton) listener->onRestartClicked();
    else if (button == &pauseButton) listener->onPauseClicked();
    else if (button == &endButton) listener->onEndClicked();
    else if (button == &goToStartButton) listener->onGoToStartClicked();

}

void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (listener && slider == &volumeSlider)
        listener->onVolumeChanged((float)slider->getValue());
}

void PlayerGUI::setListener(Listener* newListener)
{
    listener = newListener;
}
