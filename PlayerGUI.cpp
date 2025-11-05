#include "PlayerGUI.h"


PlayerGUI::PlayerGUI()
{
    for (auto* btn : { 
        &loadButton, &playButton, &stopButton, &restartButton,
        &pauseButton, &endButton, &goToStartButton, &loopButton, 
        &TenSecondsForward, &TenSecondsBackward, &MuteButton, &SaveSessionButton, 
        &LoadSessionButton, &nextButton, &prevButton, &setA, &setB, &segmentloop
        , &AddMarkerButton})
    
{
        addAndMakeVisible(btn);
        btn->addListener(this);
    }

    //volume slider
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    //position slider
    positionSlider.setRange(0.0, 1.0, 0.01);
    positionSlider.setValue(0.5);
    positionSlider.addListener(this);
    addAndMakeVisible(positionSlider);

    //speed 
    speedSlider.setRange(0.5, 2.0, 0.01);
    speedSlider.setValue(1.0);
    speedSlider.addListener(this);
    addAndMakeVisible(speedSlider);
    speed.setFont(juce::Font(16.0f, juce::Font::bold));
    addAndMakeVisible(speed);
    
    titleLabel.setText("Title: ---", juce::dontSendNotification);
    artistLabel.setText("Artist: ---", juce::dontSendNotification);
    durationLabel.setText("Duration: ---", juce::dontSendNotification);

    addAndMakeVisible(titleLabel);
    addAndMakeVisible(artistLabel);
    addAndMakeVisible(durationLabel);

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

    addAndMakeVisible(playlistBox);
    playlistBox.setModel(this);

    addAndMakeVisible(progressBar);

    // Combo box (Marker)
    addAndMakeVisible(MarkerList);
    MarkerList.addListener(this);

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
    pauseButton.setBounds(290, y, 80, 40);
    restartButton.setBounds(380, y, 80, 40);
    endButton.setBounds(470, y, 80, 40);
    goToStartButton.setBounds(560, y, 100, 40);
    loopButton.setBounds(670, y, 80, 40);
    TenSecondsForward.setBounds(760, y, 100, 40);
    TenSecondsBackward.setBounds(870, y, 100, 40);
    MuteButton.setBounds(980, y, 80, 40);
    SaveSessionButton.setBounds(1070, y, 100, 40);
    LoadSessionButton.setBounds(1180, y, 120, 40);

    volume.setBounds(20, 100, 200, 30);
    volumeSlider.setBounds(20, 130, getWidth() - 40, 25);

    speed.setBounds(20, 170, 200, 30);
    speedSlider.setBounds(20, 200, getWidth() - 40, 25);

    titleLabel.setBounds(20, 240, getWidth() - 40, 20);
    artistLabel.setBounds(20, 265, getWidth() - 40, 20);
    durationLabel.setBounds(20, 290, getWidth() - 40, 20);

    prevButton.setBounds(20, 320, 80, 40);
    nextButton.setBounds(110, 320, 80, 40);

    position.setBounds(20, 370, 200, 30);
    positionSlider.setBounds(20, 400, getWidth() - 40, 25);

    segment.setBounds(20, 440, 300, 30);
    Alabel.setBounds(340, 440, 100, 30);
    setA.setBounds(440, 440, 100, 30);
    Blabel.setBounds(560, 440, 100, 30);
    setB.setBounds(660, 440, 100, 30);
    segmentloop.setBounds(780, 440, 150, 30);

    playlistBox.setBounds(20, 500, getWidth() - 40, getHeight() - 520);

    progressBar.setBounds(20, 590, getWidth() - 40, 20);

    AddMarkerButton.setBounds(1100, 300, 80, 40);
    MarkerList.setBounds(1200, 300 , 100, 50);

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
    else if (button == &AddMarkerButton) listener->onAddMarkerClicked();
        
    

}

void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (listener && slider == &volumeSlider)
        listener->onVolumeChanged((float)slider->getValue());
    if (listener && slider == &positionSlider)
        listener->onPositionChanged((float)slider->getValue());
    if (listener && slider == &speedSlider)
        listener->onSpeedChanged(slider->getValue());

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

int PlayerGUI::getNumRows() {
    if (listener == nullptr) return 0;
    return static_cast<int>(listener->getPlaylistSize());
}

void PlayerGUI::paintListBoxItem(int rowNumber, juce::Graphics& g,
                                 int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
        g.fillAll(juce::Colours::lightblue);

    g.setColour(juce::Colours::white);
    if (listener != nullptr)
    {
        g.drawText(listener->getPlaylistItem(rowNumber), 0, 0, width, height,
                   juce::Justification::centredLeft);
    }
}
void PlayerGUI::listBoxItemClicked(int row, const juce::MouseEvent& e) {
    if (listener != nullptr)
        listener->onSongSelected(row);
}
void PlayerGUI::updateProgress(double value)
{
    Progress_Value = value;
}

void PlayerGUI::comboBoxChanged(juce::ComboBox* comboBoxChanged)
{
    if (comboBoxChanged == &MarkerList && listener != nullptr)
    {
        int selectedId = MarkerList.getSelectedId();
        if (selectedId > 0)
        {
            double pos = MarkerList.getItemText(selectedId - 1).getDoubleValue();
            listener->onMarkerSelected(pos);
        }
    }
}

void PlayerGUI::updateMarkerList(const std::vector<double>& markers)
{
    MarkerList.clear();
    int id = 1;
    for (double pos : markers)
    {
        MarkerList.addItem(juce::String(pos, 2), id++);
    }
}
