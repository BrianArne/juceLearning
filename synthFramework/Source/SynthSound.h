/*
  ==============================================================================

    SynthSound.h
    Created: 4 Dec 2019 5:57:54am
    Author:  Brian Arne

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound
{
  public:

    bool appliesToNote (int midiNodeNumber){
      return true;
    }

    bool appliesToChannel (int midiChannel){
      return true;
    }

};
