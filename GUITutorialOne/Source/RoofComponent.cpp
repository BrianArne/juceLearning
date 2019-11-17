/*
  ==============================================================================

    RoofComponent.cpp
    Created: 14 Nov 2019 6:23:42am
    Author:  Brian Arne

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "RoofComponent.h"

//==============================================================================
RoofComponent::RoofComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

RoofComponent::~RoofComponent()
{
}

void RoofComponent::paint (Graphics& g)
{
  g.setColour(Colours::red); 
  Path p;
  p.addTriangle(300, 110, 500, 110, 400, 70);
  g.fillPath(p);

}

void RoofComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
