/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (800, 600);
    freqSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    freqSlider.setRange(50.0f, 500.0f);
    freqSlider.setValue(200.0f);
    freqSlider.addListener(this);
    freqSlider.setTextValueSuffix("Hz");
    addAndMakeVisible(freqSlider);

    freqLabel.setText("Frequency", dontSendNotification);
    freqLabel.attachToComponent(&freqSlider, true);

    ampSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    ampSlider.setRange(0.0f, 1.0f);
    ampSlider.setValue(.25f);
    ampSlider.addListener(this);
    ampLabel.setText("Amplitude", dontSendNotification);
    ampLabel.attachToComponent(&ampSlider, true);
    addAndMakeVisible(ampSlider);


    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
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
  amplitude = ampSlider.getValue();
  frequency = freqSlider.getValue();
  phase = 0;
  wtSize = 1024;
  increment = frequency * wtSize / sampleRate;
  currentSampleRate = sampleRate;

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
    updateFrequency();
  }
}

void MainComponent::releaseResources()
{
}


//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

}

void MainComponent::resized()
{
  const int labelSpace = 100;
  freqSlider.setBounds(labelSpace, 20, getWidth() - 100, 20);
  ampSlider.setBounds(labelSpace, 50, getWidth() - 100, 20);
}

void MainComponent::sliderValueChanged(Slider* slider){
  if(slider == &freqSlider){
    frequency = freqSlider.getValue();
  }else if(slider == &ampSlider){
    amplitude = ampSlider.getValue();
  }
}

void MainComponent::updateFrequency(){
  increment = frequency * wtSize / currentSampleRate;
  phase = fmod((phase + increment), wtSize);
}

