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

    //frequency
    addAndMakeVisible(frequencySlider);
    addAndMakeVisible(frequencyLabel);
    frequencySlider.setRange(50, 5000);
    frequencySlider.setTextValueSuffix(" Hz");
    frequencySlider.addListener(this);
    frequencyLabel.setText("Frequency", dontSendNotification);
    frequencyLabel.attachToComponent(&frequencySlider, true);
    

    //duration
    addAndMakeVisible(durationSlider);
    addAndMakeVisible(durationLabel);
    durationSlider.setRange(1.0 / frequencySlider.getMaximum(), 1.0 / frequencySlider.getMinimum());
    durationSlider.setTextValueSuffix(" s");
    durationSlider.addListener(this);
    durationLabel.setText("Duration", dontSendNotification);
    durationLabel.attachToComponent(&durationSlider, true);
  
    //Set init value so that the slider vals dont' jump on initial click
    frequencySlider.setValue(500.0);

    //Setting skews
    frequencySlider.setSkewFactorFromMidPoint(500.0f);
    durationSlider.setSkewFactorFromMidPoint(0.002f);

    frequencySlider.setTextBoxStyle(Slider::TextBoxLeft, false, 120, frequencySlider.getTextBoxHeight());
    durationSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 120, durationSlider.getTextBoxHeight());

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
  const int border = 120;
  frequencySlider.setBounds(border, 20, getWidth()-border, 20);
  durationSlider.setBounds(border, 50, getWidth()-border, 50);
}

void MainComponent::sliderValueChanged(Slider* slider){
  if(slider == &frequencySlider){
    durationSlider.setValue(1.0 / slider->getValue());
  }else if (slider == &durationSlider){
    frequencySlider.setValue(1.0 / slider->getValue());
  }
}
