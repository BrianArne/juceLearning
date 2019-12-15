/*
  ==============================================================================

    Envelope.cpp
    Created: 14 Dec 2019 8:37:14pm
    Author:  Brian Arne

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(SynthFrameworkAudioProcessor& p) : processor(p)
{
    setSize(200, 200);
    
    // Attack Slider
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1f, 5000);
    attackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20, 10);
    attackSlider.setValue(100.1f);
    attackSlider.addListener(this);
    addAndMakeVisible(&attackSlider);
    
    // Decay Slider
    decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(0.1f, 5000);
    decaySlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20, 10);
    decaySlider.setValue(100.1f);
    decaySlider.addListener(this);
    addAndMakeVisible(&decaySlider);

    // Decay Slider
    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.1f, 5000);
    sustainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20, 10);
    sustainSlider.setValue(100.1f);
    sustainSlider.addListener(this);
    addAndMakeVisible(&sustainSlider);

    // Release Slider
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(10.1f, 5000);
    releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20, 10);
    releaseSlider.setValue(100.1f);
    releaseSlider.addListener(this);
    addAndMakeVisible(&releaseSlider);

    attackTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "attack", attackSlider);
    decayTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "decay", decaySlider);
    sustainTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "sustain", sustainSlider);
    releaseTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "release", releaseSlider);
}

Envelope::~Envelope()
{
}

void Envelope::paint (Graphics& g)
{
  g.fillAll(Colours::black);

}

void Envelope::resized()
{
  Rectangle<int> area = getLocalBounds().reduced(40);
  attackSlider.setBounds(10, 10, 40, 100);
  decaySlider.setBounds(60, 10, 40, 100);
  sustainSlider.setBounds(110, 10, 40, 100);
  releaseSlider.setBounds(160, 10, 40, 100);
}

void Envelope::sliderValueChanged(Slider* slider)
{

}
