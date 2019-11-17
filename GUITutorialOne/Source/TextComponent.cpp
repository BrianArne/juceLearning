/*
  ==============================================================================

    TextComponent.cpp
    Created: 16 Nov 2019 7:12:52pm
    Author:  Brian Arne

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "TextComponent.h"

//==============================================================================
TextComponent::TextComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

TextComponent::~TextComponent()
{
}

void TextComponent::paint (Graphics& g)
{
  Font theFont("Cooper Std", "black Italic", 50.0f);
  g.setFont(theFont);
  g.drawText("This is my house", 10, 10, 400, 60, Justification::topLeft);
}

void TextComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
