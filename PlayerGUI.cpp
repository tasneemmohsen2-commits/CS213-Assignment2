#include "PlayerGUI.h"


PlayerGUI::PlayerGUI()
{
    for (auto* btn : { 
        &loadButton, &playButton, &stopButton, &restartButton,
        &pauseButton, &endButton, &goToStartButton, &loopButton, 
        &TenSecondsForward, &TenSecondsBackward, &MuteButton, &SaveSessionButton, 
        &LoadSessionButton, &nextButton, &prevButton, &setA, &setB, &segmentloop
        , &AddMarkerButton, &ModeButton})
    
{
        addAndMakeVisible(btn);
        btn->addListener(this);
    }

    MarkerList.setTextWhenNothingSelected("Pick a Marker");

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
    if (is_Dark_Mode)
        g.fillAll(juce::Colours::black);
    else
        g.fillAll(juce::Colours::lightblue);
}

void PlayerGUI::resized()
{
    auto w = getWidth();
    auto h = getHeight();

    float y = h * 0.83f;

    loadButton.setBounds(w * 0.66f, h * 0.21f, w * 0.05f, h * 0.05f);
    playButton.setBounds(w * 0.415f, y, w * 0.06f, h * 0.06f);
    stopButton.setBounds(w * 0.61f, y, w * 0.05f, h * 0.05f);
    pauseButton.setBounds(w * 0.475f, y, w * 0.06f, h * 0.06f);
    restartButton.setBounds(w * 0.23f, y, w * 0.05f, h * 0.05f);
    endButton.setBounds(w * 0.29f, y, w * 0.05f, h * 0.05f);
    goToStartButton.setBounds(w * 0.67f, y, w * 0.06f, h * 0.05f);
    loopButton.setBounds(w * 0.13f, h * 0.27f, w * 0.05f, h * 0.05f);
    TenSecondsForward.setBounds(w * 0.54f, y, w * 0.06f, h * 0.05f);
    TenSecondsBackward.setBounds(w * 0.35f, y, w * 0.06f, h * 0.05f);
    MuteButton.setBounds(w * 0.89f, h * 0.44f, w * 0.05f, h * 0.05f);
    SaveSessionButton.setBounds(w * 0.13f, h * 0.33f, w * 0.06f, h * 0.05f);
    LoadSessionButton.setBounds(w * 0.13f, h * 0.40f, w * 0.075f, h * 0.05f);
    ModeButton.setBounds(w * 0.02f, h * 0.90f, w * 0.08f, h * 0.05f);

    // volume
    volume.setBounds(w * 0.875f, h * 0.09f, w * 0.12f, h * 0.04f);
    volumeSlider.setBounds(w * 0.91f, h * 0.11f, w * 0.05f, h * 0.33f);
    volumeSlider.setSliderStyle(juce::Slider::LinearVertical);
    volumeSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 60, 25);



    // speed
    speed.setBounds(w * 0.02f, h * 0.09f, w * 0.12f, h * 0.04f);
    speedSlider.setBounds(w * 0.02f, h * 0.11f, w * 0.05f, h * 0.33f);
    speedSlider.setSliderStyle(juce::Slider::LinearVertical);
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 60, 25);


    // metadata
    float p = w * 0.375f;
    titleLabel.setBounds(p, h * 0.12f, w * 0.5f, h * 0.03f);
    artistLabel.setBounds(p, h * 0.15f, w * 0.5f, h * 0.03f);
    durationLabel.setBounds(p, h * 0.18f, w * 0.5f, h * 0.03f);
    prevButton.setBounds(p, h * 0.21f, w * 0.05f, h * 0.05f);
    nextButton.setBounds(w * 0.45f, h * 0.21f, w * 0.05f, h * 0.05f);

    // position slider
    position.setBounds(w * 0.02f, h * 0.75f, w * 0.12f, h * 0.04f);
    positionSlider.setBounds(w * 0.02f, h * 0.78f, w * 0.96f, h * 0.03f);

    // A-B loop
    float v = h * 0.67f;
    segment.setBounds(w * 0.02f, v, w * 0.18f, h * 0.04f);
    Alabel.setBounds(w * 0.22f, v, w * 0.06f, h * 0.04f);
    setA.setBounds(w * 0.29f, v, w * 0.06f, h * 0.04f);
    Blabel.setBounds(w * 0.36f, v, w * 0.06f, h * 0.04f);
    setB.setBounds(w * 0.43f, v, w * 0.06f, h * 0.04f);
    segmentloop.setBounds(w * 0.51f, v, w * 0.09f, h * 0.04f);

    // playlist
    playlistBox.setBounds(w * 0.22f, h * 0.27f, w * 0.56f, h * 0.25f);
    playlistlabel.setBounds(w * 0.22f, h * 0.22f, w * 0.12f, h * 0.04f);

    // progress bar
    progressBar.setBounds(w * 0.02f, h * 0.72f, w * 0.96f, h * 0.02f);

    // markers
    AddMarkerButton.setBounds(w * 0.69f, v, w * 0.05f, h * 0.05f);
    MarkerList.setBounds(w * 0.76f, v, w * 0.05f, h * 0.05f);
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
    else if (button == &ModeButton)
    {
        is_Dark_Mode = !is_Dark_Mode;
        if (is_Dark_Mode)
            ModeButton.setButtonText("Light Mode");
        else
            ModeButton.setButtonText("Dark Mode");
        if (listener)
            listener->onModeClicked(is_Dark_Mode);
        repaint();

    }
        
    

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

            MarkerList.setSelectedId(0, juce::dontSendNotification);
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
