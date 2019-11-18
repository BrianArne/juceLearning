/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class OtherLookAndFeel : public LookAndFeel_V4
{
  public:
    OtherLookAndFeel(){
      setColour(Slider::rotarySliderOutlineColourId, Colours::chocolate);
      setColour(Slider::thumbColourId, Colours::black);
      setColour(Slider::rotarySliderFillColourId, Colours::blue);
    }
};



class MainComponent   : public Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    Slider dial1;
    Slider dial2;

    //LookAndFeel_V4 otherLookAndFeel;
    OtherLookAndFeel otherLookAndFeel;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
