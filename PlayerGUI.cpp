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
    addAndMakeVisible(playlistlabel);
    //volume slider
    volumeSlider.setSliderStyle(juce::Slider::LinearVertical);
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
    speedSlider.setSliderStyle(juce::Slider::LinearVertical);
    speedSlider.setRange(0.5, 2.0, 0.01);
    speedSlider.setValue(1.0);
    speedSlider.addListener(this);
    addAndMakeVisible(speedSlider);
    speed.setFont(juce::Font(16.0f, juce::Font::bold));
    addAndMakeVisible(speed);
    
    titleLabel.setText("Title: ---", juce::dontSendNotification);
    artistLabel.setText("Artist: ---", juce::dontSendNotification);
    durationLabel.setText("Duration: ---", juce::dontSendNotification);
    playlistlabel.setText("playlist box: ", juce::dontSendNotification);

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
    int y = 750;

    loadButton.setBounds(1050, 190, 80, 40);
    playButton.setBounds(660, y, 90, 50);
    stopButton.setBounds(980, y, 80, 40);
    pauseButton.setBounds(760, y, 90, 50); //290
    restartButton.setBounds(370, y, 80, 40);
    endButton.setBounds(460, y, 80, 40);
    goToStartButton.setBounds(1070, y, 100, 40); //870
    loopButton.setBounds(110, 240, 80, 40); 
    TenSecondsForward.setBounds(870, y, 100, 40);
    TenSecondsBackward.setBounds(550, y, 100, 40);
    MuteButton.setBounds(1420, 400, 80, 40);
    SaveSessionButton.setBounds(110, 300, 100, 40); //1070
    LoadSessionButton.setBounds(110, 360, 120, 40); //1180

    volume.setBounds(1400, 80, 200, 30);
    //volumeSlider.setBounds(20, 130, getWidth() - 40, 25);
    volumeSlider.setBounds(1450, 100, 30, 300); // x, y, width, height



    speed.setBounds(20, 80, 200, 30);
    //speedSlider.setBounds(20, 400, getWidth() - 40, 25);
    speedSlider.setBounds(20, 100, 30, 300);
    //metadata
    int p = 600; 
    titleLabel.setBounds(p, 110, getWidth() - 40, 20); //diffrence is 25
    artistLabel.setBounds(p, 135, getWidth() - 40, 20);
    durationLabel.setBounds(p, 160, getWidth() - 40, 20);
    prevButton.setBounds(750, 150, 80, 40);
    nextButton.setBounds(750, 110, 80, 40);

    position.setBounds(20, 675, 200, 30);
    positionSlider.setBounds(20, 700, getWidth() - 40, 25);
    // a-b segment loop
    int v = 600;
    segment.setBounds(20, v, 300, 30);
    Alabel.setBounds(340, v, 100, 30);
    setA.setBounds(440, v, 100, 30);
    Blabel.setBounds(560, v, 100, 30);
    setB.setBounds(660, v, 100, 30);
    segmentloop.setBounds(780, v, 150, 30);

    //playlistBox.setBounds(20, 500, getWidth() - 40, getHeight() - 520);
    
    playlistBox.setBounds(350, 240, getWidth() - 700, getHeight() - 600);
    playlistlabel.setBounds(350, 200, 200, 30);
    progressBar.setBounds(20, 650, getWidth() - 40, 20);

    AddMarkerButton.setBounds(1100, v, 80, 40);
    MarkerList.setBounds(1200, v , 100, 50);

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
