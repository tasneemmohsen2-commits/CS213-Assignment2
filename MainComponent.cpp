#include "MainComponent.h"
#include"PlayerAudio.h"

juce::String CurrentPath;

MainComponent::MainComponent()
{
    addAndMakeVisible(playerGUI);
    playerGUI.setListener(this);

    setAudioChannels(0, 2);
    
    setSize(500, 250);
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
        juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
        [this](const juce::FileChooser& fc)
        {
            auto file = fc.getResult();
            CurrentPath = file.getFullPathName();
            if (file.existsAsFile())
                playerAudio.loadFile(file);
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

void MainComponent::onVolumeChanged(float value)
{
    playerAudio.setGain(value);
}
void MainComponent::onPositionChanged(float value) {
    double duration = playerAudio.getLengthInSeconds();
    playerAudio.setPosition(value * duration);
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