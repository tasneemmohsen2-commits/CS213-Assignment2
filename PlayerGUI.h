#pragma once
#include <JuceHeader.h>

class PlayerGUI : public juce::Component,
    public juce::Button::Listener,
    public juce::Slider::Listener,
    public juce::ComboBox::Listener,
    public juce::ListBoxModel
{
public:
    PlayerGUI();
    ~PlayerGUI() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void updateMarkerList(const std::vector<double>& markers);


    void comboBoxChanged(juce::ComboBox* comboBoxChanged) override;

    void setMetadata(const juce::String& title,
                 const juce::String& artist,
                 const juce::String& duration);

    int getNumRows() override;
    void paintListBoxItem(int rowNumber, juce::Graphics& g,
                          int width, int height, bool rowIsSelected) override;
    void listBoxItemClicked(int row, const juce::MouseEvent& e) override;
    void PlayerGUI::refreshPlaylist()
    {
        playlistBox.updateContent();
        playlistBox.repaint();
    }

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
        virtual void onSaveSessionClicked() = 0;
        virtual void onLoadSessionClicked() = 0;
        virtual void onNextClicked() = 0;
        virtual void onPrevClicked() = 0;
        virtual void onSetAClicked() = 0;
        virtual void onSetBClicked() = 0;
        virtual void onsegmentloopClicked(bool enable) = 0;
        virtual void onSpeedChanged(double value) = 0;
        virtual int getPlaylistSize() const = 0;
        virtual juce::String getPlaylistItem(int index) const = 0;
        virtual void onSongSelected(int index) = 0;
        virtual void onAddMarkerClicked() = 0;
        virtual void onMarkerSelected(double position) = 0;

        
 
    };

    void setListener(Listener* newListener);
    void updatepositionslider(double value);
    void updateloop(double Atime, double Btime);
    void updateProgress(double value);
    
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
    juce::TextButton SaveSessionButton{ "Save Session" };
    juce::TextButton LoadSessionButton{ "Load Session" };
    juce::TextButton setA{ "set A" };
    juce::TextButton setB{ "set B" };
    juce::TextButton segmentloop{ "Segment Loop:off" };
    juce::Slider volumeSlider;
    juce::Slider positionSlider;
    juce::Slider speedSlider;
  
    juce::Label volume{ "Volume slider: " };
    juce::Label position{ "Position slider: " };
    juce::Label speed{ "Speed slider:", "Speed slider:" };
    juce::Label segment{ "Loop over a specific segment: " };
    juce::Label Alabel{ "A:", "A=0.0s" };
    juce::Label Blabel{ "B:", "B=0.0s" };
    juce::Label playlistlabel;
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;
    juce::Label titleLabel, artistLabel, durationLabel;
    juce::TextButton nextButton { "Next" };
    juce::TextButton prevButton { "Prev" };
    juce::ListBox playlistBox;
    double Progress_Value = 0.0;
    juce::ProgressBar progressBar{ Progress_Value };
    juce::ComboBox MarkerList;
    juce::TextButton AddMarkerButton{ "Add Marker" };

    Listener* listener = nullptr;
};