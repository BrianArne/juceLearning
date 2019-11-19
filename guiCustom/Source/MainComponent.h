/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class OtherLookAndFeel : public LookAndFeel_V4{
public:
   void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, 
                         float rotaryEndAngle, Slider& slider) override{
     float diameter = jmin(width, height);
     float radius = diameter/2;
     float centerX = x + width/2;
     float centerY = y + height/2;
     float rx = centerX - radius;
     float ry = centerY - radius;
     float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));

     Rectangle<float> dialArea(rx, ry, diameter, diameter);

     g.setColour(Colours::red);
     g.fillEllipse(dialArea);

     g.setColour(Colours::black);

     Path dialTick;
     dialTick.addRectangle(0, -radius, 10.0f, radius*0.33);
     g.fillPath(dialTick, AffineTransform::rotation(angle).translated(centerX, centerY));

     g.setColour(Colours::black);
     g.drawEllipse(rx, ry, diameter, diameter, 5.0f);



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
    OtherLookAndFeel otherLookAndFeel;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
