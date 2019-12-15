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
    : AudioProcessorEditor (&p), processor (p), oscGui(p), envGui(p)
{
    setSize (400, 200);

    addAndMakeVisible(&oscGui);
    addAndMakeVisible(&envGui);
}

SynthFrameworkAudioProcessorEditor::~SynthFrameworkAudioProcessorEditor()
{
}

//==============================================================================
void SynthFrameworkAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::black);
}

// How we set the positions on start up and on resize. Must be done
void SynthFrameworkAudioProcessorEditor::resized()
{
  const int componentWidth = 200;
  const int componentHeight = 200;
  Rectangle<int> area = getLocalBounds();
  oscGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
  envGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
}
