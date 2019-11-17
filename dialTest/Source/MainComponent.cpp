/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    dial1.setSliderStyle(Slider::SliderStyle::Rotary);
    dial1.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(dial1);

    dial2.setSliderStyle(Slider::SliderStyle::Rotary);
    dial2.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(dial2);

    slider1.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    slider1.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(slider1);
    setSize (600, 400);
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
  const int border = 10;

  Rectangle<int> area = getLocalBounds();
  Rectangle<int> dialArea = area.removeFromTop(area.getHeight() / 2);
  dial2.setBounds(dialArea.removeFromRight(area.getWidth() / 2).reduced(border));
  dial1.setBounds(dialArea.removeFromLeft(area.getWidth() / 2).reduced(border));
  slider1.setBounds(area);
}
