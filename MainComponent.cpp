#include "MainComponent.h"

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
void MainComponent::onPauseClicked() {
    playerAudio.pause();
}
void MainComponent::onEndClicked() {
    playerAudio.end();
}
void MainComponent::onGoToStartClicked() {
    playerAudio.goToStart();
}
