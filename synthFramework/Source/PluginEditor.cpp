/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthFrameworkAudioProcessorEditor::SynthFrameworkAudioProcessorEditor (SynthFrameworkAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (400, 300);

    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1f, 5000);
    attackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20, 10);
    attackSlider.setValue(0.1f);
    attackSlider.addListener(this);
    addAndMakeVisible(&attackSlider);


    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.1f, 5000);
    releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20, 10);
    releaseSlider.setValue(0.1f);
    releaseSlider.addListener(this);
    addAndMakeVisible(&releaseSlider);

    attackTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "attack", attackSlider);
    releaseTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "release", releaseSlider);
}

SynthFrameworkAudioProcessorEditor::~SynthFrameworkAudioProcessorEditor()
{
}

//==============================================================================
void SynthFrameworkAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

// How we set the positions on start up and on resize. Must be done
void SynthFrameworkAudioProcessorEditor::resized()
{
  attackSlider.setBounds(10, 10, 40, 100);
  releaseSlider.setBounds(60, 10, 40, 100);
}

void SynthFrameworkAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
  if(slider == &attackSlider){
    processor.attackTime = attackSlider.getValue();
  }

  if(slider == &releaseSlider){
    processor.releaseTime = releaseSlider.getValue();
  }
}

// Check calling methods without doing class
// Pointer delete with iterator
// 
