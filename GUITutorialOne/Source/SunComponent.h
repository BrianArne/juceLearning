/*
  ==============================================================================

    SunComponent.h
    Created: 16 Nov 2019 7:08:51pm
    Author:  Brian Arne

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class SunComponent    : public Component
{
public:
    SunComponent();
    ~SunComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SunComponent)
};
