/*
  ==============================================================================

    Envelope.h
    Created: 14 Dec 2019 8:37:14pm
    Author:  Brian Arne

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Envelope    : public Component,
                    public Slider::Listener
{
public:
    Envelope(SynthFrameworkAudioProcessor&);
    ~Envelope();

    void paint (Graphics&) override;
    void resized() override;

    void sliderValueChanged(Slider* slider) override;
    

private:
    SynthFrameworkAudioProcessor& processor;

    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackTree;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayTree;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sustainTree;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseTree;

    Slider attackSlider;
    Slider decaySlider;
    Slider sustainSlider;
    Slider releaseSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
