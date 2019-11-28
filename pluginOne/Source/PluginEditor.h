/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class PluginOneAudioProcessorEditor  : public AudioProcessorEditor,
                                       public Slider::Listener

{
public:
    PluginOneAudioProcessorEditor (PluginOneAudioProcessor&);
    ~PluginOneAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider) override;


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginOneAudioProcessor& processor;
    Slider gainSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginOneAudioProcessorEditor)
};
