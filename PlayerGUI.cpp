#include "PlayerGUI.h"

PlayerGUI::PlayerGUI()
{
    for (auto* btn : { &loadButton, &playButton, &stopButton, &restartButton,
        &pauseButton, &endButton,&goToStartButton,&loopButton
        , &TenSecondsForward , &TenSecondsBackward , &SaveSessionButton , 
        &LoadSessionButton,&nextButton,&prevButton})
    {
        addAndMakeVisible(btn);
        btn->addListener(this);
    }

    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    //position slider

    positionSlider.setRange(0.0, 1.0, 0.01);
    positionSlider.setValue(0.5);
    positionSlider.addListener(this);
    addAndMakeVisible(positionSlider);

    addAndMakeVisible(MuteButton);
    MuteButton.addListener(this);

    titleLabel.setText("Title: ---", juce::dontSendNotification);
    artistLabel.setText("Artist: ---", juce::dontSendNotification);
    durationLabel.setText("Duration: ---", juce::dontSendNotification);

    addAndMakeVisible(titleLabel);
    addAndMakeVisible(artistLabel);
    addAndMakeVisible(durationLabel);


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
    loopButton.setBounds(650, y, 80, 40);
    TenSecondsForward.setBounds(740, y, 80, 40);
    TenSecondsBackward.setBounds(830, y, 80, 40);
    volumeSlider.setBounds(20, 100, getWidth() - 40, 30);
    positionSlider.setBounds(20, 150, getWidth() - 40, 30);
    MuteButton.setBounds(920, y, 80, 40);
    SaveSessionButton.setBounds(1010, y, 80, 40);
    LoadSessionButton.setBounds(1100, y, 80, 40);

    titleLabel.setBounds(20, 200, getWidth() - 40, 20);
    artistLabel.setBounds(20, 230, getWidth() - 40, 20);
    durationLabel.setBounds(20, 260, getWidth() - 40, 20);

    prevButton.setBounds(20, 300, 80, 40);
    nextButton.setBounds(110, 300, 80, 40);


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
    else if (button == &loopButton) {
        static bool islooping = false;
        islooping = !islooping;
        loopButton.setButtonText(islooping ? "loop:on" : "loop:off");
        if (listener) {
            listener->onLoopClicked(islooping);
        }
    }
    else if (button == &TenSecondsForward) listener->onTenSecondsForward();
    else if (button == &TenSecondsBackward) listener->onTenSecondsBackward();
    else if (button == &SaveSessionButton) listener->onSaveSessionClicked();
    else if (button == &LoadSessionButton) listener->onLoadSessionClicked();
    else if (button == &MuteButton)
    {
        if (listener) {
            listener->onMuteClicked();
        }

        if (MuteButton.getButtonText() == "Mute") {
            MuteButton.setButtonText("Unmute");
        }
        else {
            MuteButton.setButtonText("Mute");
        }
    }

    else if (button == &nextButton)
    {
        if (listener) listener->onNextClicked();
    }
    else if (button == &prevButton)
    {
        if (listener) listener->onPrevClicked();
    }
}

void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (listener && slider == &volumeSlider)
        listener->onVolumeChanged((float)slider->getValue());
    if (listener && slider == &positionSlider)
        listener->onPositionChanged((float)slider->getValue());


}

void PlayerGUI::setMetadata(const juce::String& title,
                            const juce::String& artist,
                            const juce::String& duration)
{
    titleLabel.setText("Title: " + title, juce::dontSendNotification);
    artistLabel.setText("Artist: " + artist, juce::dontSendNotification);
    durationLabel.setText("Duration: " + duration, juce::dontSendNotification);
}



void PlayerGUI::setListener(Listener* newListener)
{
    listener = newListener;
}