#include "MainComponent.h"
#include"PlayerAudio.h"

juce::String CurrentPath;

double loopStart = 0.0;
double loopEnd = 0.0;
bool isLoopEnabled = false;


MainComponent::MainComponent()
{
    addAndMakeVisible(playerGUI);
    playerGUI.setListener(this);


    setAudioChannels(0, 2);
    
    setSize(500, 250);

    startTimerHz(60);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    playerAudio.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    playerAudio.getNextAudioBlock(bufferToFill);
    if (isSegmentLoopEnabled) {
        double currentPos = playerAudio.getCurrentPosition();
        if (currentPos >= loopEnd) {
            playerAudio.setPosition(loopStart);
        }
    }
}

void MainComponent::releaseResources()
{
    playerAudio.releaseResources();
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void MainComponent::resized()
{
    playerGUI.setBounds(getLocalBounds());
}

void MainComponent::onLoadClicked()
{
    fileChooser = std::make_unique<juce::FileChooser>("Select an audio file...", juce::File{}, "*.wav;*.mp3");
    fileChooser->launchAsync(
        juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles | juce::FileBrowserComponent::canSelectMultipleItems,
        [this](const juce::FileChooser& fc)
        {
            auto selectedFiles = fc.getResults();

            currentIndex = 0;
            if (selectedFiles.isEmpty())
                return;
            for (auto& file : selectedFiles)
                playlist.push_back(file);

            auto file = playlist[currentIndex];
            if (file.existsAsFile()) {
                playerAudio.loadFile(file);
            CurrentPath = file.getFullPathName();
                juce::String title = playerAudio.title.isNotEmpty() ? playerAudio.title : file.getFileNameWithoutExtension();
                juce::String artist = playerAudio.artist.isNotEmpty() ? playerAudio.artist : "Unknown";
                juce::String duration = playerAudio.durationString.isNotEmpty() ? playerAudio.durationString : "Unknown";

                playerGUI.setMetadata(title, artist, duration);

            }

        });
}

void MainComponent::onPlayClicked()
{
    playerAudio.play();
}

void MainComponent::onStopClicked()
{
    playerAudio.stop();
}

void MainComponent::onRestartClicked()
{
    playerAudio.restart();
}
//positionandvolume slider
void MainComponent::onVolumeChanged(float value)
{
    playerAudio.setGain(value);
}
void MainComponent::onPositionChanged(float value) {
    double duration = playerAudio.getLengthInSeconds();
    playerAudio.setPosition(value * duration);
}

void MainComponent::timerCallback() {

    double slider_position = playerAudio.getCurrentPosition();
    double length = playerAudio.getLengthInSeconds();
    if (length > 0) {
        playerGUI.updatepositionslider(slider_position / length);
        if (isSegmentLoopEnabled && slider_position >= loopEnd) {
            playerAudio.setPosition(loopStart);
        }
    };
 }

void MainComponent::onPauseClicked() {
    playerAudio.pause();
}
void MainComponent::onEndClicked() {
    playerAudio.end();
}
void MainComponent::onGoToStartClicked() {
    playerAudio.goToStart();
}
void MainComponent::onLoopClicked(bool shouldloop) {

    playerAudio.setLooping(shouldloop);
}
void MainComponent::onsegmentloopClicked(bool enable) {
    isSegmentLoopEnabled = enable;
}

void MainComponent::onTenSecondsForward()
{
    playerAudio.TenSecondsForward();
}

void MainComponent::onTenSecondsBackward()
{
    playerAudio.TenSecondsBackward();
}

void MainComponent::onMuteClicked()
{
    playerAudio.ToggleMute();
}

void MainComponent::onSaveSessionClicked()
{
    
    fileChooser = std::make_unique<juce::FileChooser>("Save Your Session File...", juce::File{}, "*.txt");
    fileChooser->launchAsync(
        juce::FileBrowserComponent::saveMode | juce::FileBrowserComponent::warnAboutOverwriting,
        [this](const juce::FileChooser& fc)
        {
            auto file = fc.getResult();
            juce::String SavePath = file.getFullPathName();
            playerAudio.SaveSession(CurrentPath , SavePath);   
        });

}

void MainComponent::onLoadSessionClicked()
{
    fileChooser = std::make_unique<juce::FileChooser>("Select a Session File...", juce::File{}, "*.txt");
    fileChooser->launchAsync(
        juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
        [this](const juce::FileChooser& fc)
        {

            auto file = fc.getResult();
            juce::String FullPath = file.getFullPathName();
            playerAudio.LoadSession(FullPath);
        });
}

void MainComponent::onNextClicked()
{
    if (playlist.empty()) return;

    currentIndex++;
    if (currentIndex >= (int)playlist.size())
        currentIndex = 0;

    juce::File file = playlist[currentIndex];
    playerAudio.loadFile(file);

    juce::String title    = playerAudio.getTitle().isNotEmpty() ? playerAudio.getTitle() : file.getFileNameWithoutExtension();
    juce::String artist   = playerAudio.getArtist().isNotEmpty() ? playerAudio.getArtist() : "Unknown";
    juce::String duration = playerAudio.getDurationString().isNotEmpty() ? playerAudio.getDurationString() : "Unknown";

    playerGUI.setMetadata(title, artist, duration);
    playerAudio.play();
}

void MainComponent::onPrevClicked()
{
    if (playlist.empty()) return;

    currentIndex--;
    if (currentIndex < 0)
        currentIndex = playlist.size() - 1; // go to last song

    juce::File file = playlist[currentIndex];
    playerAudio.loadFile(file);

    juce::String title    = playerAudio.getTitle().isNotEmpty() ? playerAudio.getTitle() : file.getFileNameWithoutExtension();
    juce::String artist   = playerAudio.getArtist().isNotEmpty() ? playerAudio.getArtist() : "Unknown";
    juce::String duration = playerAudio.getDurationString().isNotEmpty() ? playerAudio.getDurationString() : "Unknown";

    playerGUI.setMetadata(title, artist, duration);
    playerAudio.play();
}

void MainComponent::onSetAClicked()
{
    loopStart = playerAudio.getCurrentPosition();
    playerGUI.updateloop(loopStart, loopEnd);
}

void MainComponent::onSetBClicked()
{
    loopEnd = playerAudio.getCurrentPosition();
    playerGUI.updateloop(loopStart, loopEnd);
    isSegmentLoopEnabled = true;
}

void MainComponent::onSpeedChanged(double value)
{
    playerAudio.setSpeed(value);
}

