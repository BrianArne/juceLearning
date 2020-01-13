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
    attackSlider.setRange(0.1f, 5000.0f);
    attackSlider.setValue(1000.1f);
    attackSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0); addAndMakeVisible(&attackSlider);
    
    // Decay Slider
    decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(0.1f, 2000.0f);
    decaySlider.setValue(1000.0f);
    decaySlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&decaySlider);

    // Decay Slider
    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.0f, 1.0f);
    sustainSlider.setValue(0.8f);
    sustainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&sustainSlider);

    // Release Slider
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.1f, 5000.0f);
    releaseSlider.setValue(0.8f);
    releaseSlider.setTextBoxStyle(Slider::NoTextBox, true, 20, 10);
    addAndMakeVisible(&releaseSlider);

    attackVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "attack", attackSlider);
    decayVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "decay", decaySlider);
    sustainVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "sustain", sustainSlider);
    releaseVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "release", releaseSlider);
}

Envelope::~Envelope()
{
}

void Envelope::paint (Graphics& g)
{
  Rectangle<int> titleArea (0, 10, getWidth(), 20);
  g.fillAll(Colours::black);
  g.setColour(Colours::white);
  g.drawText("Envelope", titleArea, Justification::centredTop);

  g.drawText("A", 53, 150, 20, 20, Justification::centredTop);
  g.drawText("D", 77, 150, 20, 20, Justification::centredTop);
  g.drawText("S", 103, 150, 20, 20, Justification::centredTop);
  g.drawText("R", 128, 150, 20, 20, Justification::centredTop);

  Rectangle<float> area(25, 25, 150, 150);

  g.setColour(Colours::yellow);
  g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Envelope::resized()
{
  Rectangle<int> area = getLocalBounds().reduced(50);

  int sliderWidth = 25;
  int sliderHeight = 175;

  attackSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
  decaySlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
  sustainSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
  releaseSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}

