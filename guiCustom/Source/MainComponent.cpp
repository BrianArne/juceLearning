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
    dial1.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dial1.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    dial1.setLookAndFeel(&otherLookAndFeel);
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint(Graphics & g){
  g.fillAll(Colours::white);
}

void MainComponent::resized()
{
  dial1.setBounds(getLocalBounds());
}
