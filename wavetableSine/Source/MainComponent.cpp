/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
  amplitude = 0.25;
  frequency = 880;
  phase = 0;
  wtSize = 1024;
  increment = frequency * wtSize / sampleRate;

  //One cycle of a sine wave
  for(int i = 0; i < wtSize; i++){
    waveTable.insert(i, sin(2.0 * double_Pi * i / wtSize));
  }
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
  float * const leftSpeaker = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
  float * const rightSpeaker = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);

  for (int sample = 0; sample < bufferToFill.numSamples; sample++){
    leftSpeaker[sample] = waveTable[(int)phase] * amplitude;
    rightSpeaker[sample] = waveTable[(int)phase] * amplitude;
    phase = fmod((phase + increment), wtSize);

  }

}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

