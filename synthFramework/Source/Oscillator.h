/*
  ==============================================================================

    Oscillator.h
    Created: 14 Dec 2019 6:53:46pm
    Author:  Brian Arne

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator    : public Component
{
public:
    Oscillator(SynthFrameworkAudioProcessor&);
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;

private:
    ComboBox oscMenu;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;

    SynthFrameworkAudioProcessor& processor;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
