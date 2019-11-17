/*
  ==============================================================================

    GrassComponent.h
    Created: 14 Nov 2019 6:12:06am
    Author:  Brian Arne

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class GrassComponent    : public Component
{
public:
    GrassComponent();
    ~GrassComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GrassComponent)
};
