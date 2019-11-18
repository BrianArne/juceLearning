/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
    addAndMakeVisible(dial1);
    addAndMakeVisible(dial2);

    dial1.setSliderStyle(Slider::SliderStyle::Rotary);
    dial2.setSliderStyle(Slider::SliderStyle::Rotary);

    dial1.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    dial2.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);

    getLookAndFeel().setColour(Slider::thumbColourId, Colours::purple);
    getLookAndFeel().setColour(Slider::rotarySliderFillColourId, Colours::azure);

    dial1.setLookAndFeel(&otherLookAndFeel);
}

MainComponent::~MainComponent()
{
}


//==============================================================================
void MainComponent::paint (Graphics& g)
{

}

void MainComponent::resized()
{
  const int border = 20;
  const int dialWidth = getWidth() / 2 - border;
  const int dialHeight = getWidth() / 2 - border - 100;

  dial1.setBounds(border, border, dialWidth, dialHeight);
  dial2.setBounds(getWidth()/2 + border, border, dialWidth, dialHeight);


}
