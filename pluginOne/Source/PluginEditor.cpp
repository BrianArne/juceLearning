/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginOneAudioProcessorEditor::PluginOneAudioProcessorEditor (PluginOneAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 400);

    sliderAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.treeState, GAIN_ID, gainSlider);


    gainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainSlider.setRange(-48.0, 0.0);
    gainSlider.setValue(-5.0f);
    gainSlider.addListener(this);
    gainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    addAndMakeVisible(gainSlider);
}

PluginOneAudioProcessorEditor::~PluginOneAudioProcessorEditor()
{
  delete sliderAttach;
}

//==============================================================================
void PluginOneAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void PluginOneAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    gainSlider.setBounds(getLocalBounds());
}

void PluginOneAudioProcessorEditor::sliderValueChanged(Slider* slider){
  if(slider == &gainSlider){
    processor.rawVolume = pow(10, gainSlider.getValue() / 20);
    //processor.rawVolume = gainSlider.getValue();
  }
}

