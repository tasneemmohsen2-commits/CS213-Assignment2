#include "PlayerAudio.h"

PlayerAudio::PlayerAudio()
{
    formatManager.registerBasicFormats();
    resampler = std::make_unique<juce::ResamplingAudioSource>(&transportSource, false);
}

PlayerAudio::~PlayerAudio() {}

void PlayerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    if (resampler)
    {
        resampler->prepareToPlay(samplesPerBlockExpected, sampleRate);
    }
}

void PlayerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (resampler)
        resampler->getNextAudioBlock(bufferToFill);
    else
        transportSource.getNextAudioBlock(bufferToFill);
}

void PlayerAudio::releaseResources()
{
    transportSource.releaseResources();
    if (resampler)
    {
        resampler->releaseResources();
    }
}

void PlayerAudio::loadFile(const juce::File& file)
{
    if (auto* reader = formatManager.createReaderFor(file))
    {
        transportSource.stop();
        transportSource.setSource(nullptr);
        readerSource.reset();

        readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
        readerSource->setLooping(looping);
        transportSource.setSource(readerSource.get(),
            0, nullptr, reader->sampleRate);

        auto metadata = reader->metadataValues;
        if (metadata.containsKey("title"))
            title = metadata["title"];

        if (metadata.containsKey("artist"))
            artist = metadata["artist"];

        double length = reader->lengthInSamples / reader->sampleRate;
        durationString = juce::String(length, 2) + " sec";
    }
}

void PlayerAudio::play()
{
    transportSource.start();
}

void PlayerAudio::stop()
{
    transportSource.stop();
}

void PlayerAudio::restart()
{
    transportSource.setPosition(0.0);
    transportSource.start();
}

void PlayerAudio::setGain(float gain)
{
    transportSource.setGain(gain);
}
void PlayerAudio::pause() {
    transportSource.stop();
    transportSource.setPosition(transportSource.getCurrentPosition());
}
void PlayerAudio::end()
{
    if (readerSource != nullptr)
    {
        double length = transportSource.getLengthInSeconds();
        transportSource.setPosition(length);
    }
}
void PlayerAudio::goToStart() {
    transportSource.setPosition(0.0);
    transportSource.start();
}
void PlayerAudio::setLooping(bool shouldLoop) {
    if (readerSource != nullptr) {
        readerSource->setLooping(shouldLoop);
        looping = shouldLoop;
    }
}
bool PlayerAudio::isLooping()const {
    return looping;

}

//new slider
double PlayerAudio::getLengthInSeconds() const
{
    return transportSource.getLengthInSeconds();
}

void PlayerAudio::setPosition(double newPositionInSeconds)
{
    transportSource.setPosition(newPositionInSeconds);
}

double PlayerAudio::getCurrentPosition() const
{
    return transportSource.getCurrentPosition();
}

void PlayerAudio::TenSecondsForward()
{
    double Position = transportSource.getCurrentPosition() + 10.0;

    if (Position > transportSource.getLengthInSeconds())
    {
        Position = transportSource.getLengthInSeconds();
    }
    transportSource.setPosition(Position);
}

void PlayerAudio::TenSecondsBackward()
{
    double Position = transportSource.getCurrentPosition() - 10.0;

    if (Position < 0.0)
    {
        Position = 0.0;
    }
    transportSource.setPosition(Position);
}

void PlayerAudio::ToggleMute()
{
    if (!muted)
    {
        last_volume = transportSource.getGain();
        transportSource.setGain(0.0f);
        muted = true;
    }
    else
    {
        transportSource.setGain(last_volume);
        muted = false;
    }
}
void PlayerAudio::SaveSession(const juce::String& FilePath , const juce::String& SavePath)
{
    double PlaybackPosition = transportSource.getCurrentPosition();
    juce::FileOutputStream SessionFile(SavePath);
    if (SessionFile.openedOk())
    {
        SessionFile.setPosition(0);
        SessionFile.truncate();
        SessionFile << FilePath << '\n';
        SessionFile << PlaybackPosition << '\n';
    }


}

void PlayerAudio::LoadSession(const juce::String& Path)
{
    juce::FileInputStream SessionFile(Path);
    if (SessionFile.openedOk())
    {
        juce::String SongPath, SecondLine;
        SongPath = SessionFile.readNextLine();
        SecondLine = SessionFile.readNextLine();
        double PlaybackPosition = SecondLine.getDoubleValue();
        DBG("Song Path: " << SongPath << " \nPlayback Position : " << PlaybackPosition);
        
        PlayerAudio::loadFile(SongPath);
        transportSource.setPosition(PlaybackPosition);
    }
}

void PlayerAudio::setSpeed(double ratio) 
{
    if (resampler)
    {
        resampler->setResamplingRatio(ratio);
    }
}

void PlayerAudio::AddMarker()
{
    double PlaybackPosition = transportSource.getCurrentPosition();
    MarksPositions.push_back(PlaybackPosition);
}

juce::String PlayerAudio::getTitle() const   { return title; }
juce::String PlayerAudio::getArtist() const  { return artist; }
juce::String PlayerAudio::getDurationString() const { return durationString; }
juce::String PlayerAudio::getFileName() const { return fileName; }