#include "PlayerGUI.h"

PlayerGUI::PlayerGUI()
{
    for (auto* btn : { &loadButton, &playButton, &stopButton, &restartButton,
        &pauseButton, &endButton,&goToStartButton,&loopButton
        , &TenSecondsForward , &TenSecondsBackward , &SaveSessionButton , 

        &LoadSessionButton,&nextButton,&prevButton, &setA, &setB, &segmentloop })
    
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

    //volume and position slider labels

    volume.setText("Volume slider:", juce::dontSendNotification);
    volume.setFont(juce::Font(16.0f, juce::Font::bold));

    addAndMakeVisible(volume);

    position.setText("Position slider:", juce::dontSendNotification);
    position.setFont(juce::Font(16.0f, juce::Font::bold));

    addAndMakeVisible(position);


    segment.setText("Loop over a specific segment A-B:", juce::dontSendNotification);
    segment.setFont(juce::Font(16.0f, juce::Font::bold));
    addAndMakeVisible(segment);


    Alabel.setText("A: A=0.0s", juce::dontSendNotification);
    Alabel.setFont(juce::Font(16.0f, juce::Font::bold));
    addAndMakeVisible(Alabel);


    Blabel.setText("B: B=0.0s", juce::dontSendNotification);
    Blabel.setFont(juce::Font(16.0f, juce::Font::bold));
    addAndMakeVisible(Blabel);



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
    volume.setBounds(20, 100, 80, 40);
    volumeSlider.setBounds(20, 150, getWidth() - 40, 30);
    position.setBounds(20, 500, 80, 40);
    positionSlider.setBounds(20, 550, getWidth() - 40, 30);
    segment.setBounds(20, 610, 150, 60);
    Alabel.setBounds(300, 610, 150, 40);
    setA.setBounds(400, 610, 150,40);

    Blabel.setBounds(600, 610, 150, 40);
    setB.setBounds(700, 610, 150, 40);
    segmentloop.setBounds(900, 610, 80, 40);
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
    else if (button == &segmentloop) {
        static bool issegmentlooping = false;
        issegmentlooping = !issegmentlooping;
        segmentloop.setButtonText(issegmentlooping ? "segment loop: on" : "segment loop: off");
        if (listener) {
            listener->onsegmentloopClicked(issegmentlooping);
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

    else if (button == &setA)  listener->onSetAClicked();
    else if (button == &setB) listener->onSetBClicked();
        
    

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



void PlayerGUI::updatepositionslider(double value)
{
    positionSlider.setValue(value, juce::dontSendNotification);
}


void PlayerGUI::setListener(Listener* newListener)
{
    listener = newListener;
}
//feature 10
void PlayerGUI::updateloop(double Atime, double Btime)
{
    auto formatTime = [](double t) {
        int minutes = int(t) / 60;
        int seconds = int(t) % 60;
        return juce::String(minutes) + ":" + (seconds < 10 ? "0" : "") + juce::String(seconds);
        };

    Alabel.setText("A: " + formatTime(Atime), juce::dontSendNotification);
    Blabel.setText("B: " + formatTime(Btime), juce::dontSendNotification);
}
