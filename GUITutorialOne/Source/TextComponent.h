/*
  ==============================================================================

    TextComponent.h
    Created: 16 Nov 2019 7:12:52pm
    Author:  Brian Arne

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class TextComponent    : public Component
{
public:
    TextComponent();
    ~TextComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TextComponent)
};
