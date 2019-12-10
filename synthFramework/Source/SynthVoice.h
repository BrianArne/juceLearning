/*
  ==============================================================================

    SynthVoice.h
    Created: 4 Dec 2019 5:58:04am
    Author:  Brian Arne

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

class SynthVoice  : public SynthesiserVoice
{
  public:
    
    bool canPlaySound (SynthesiserSound* sound){
      return dynamic_cast<SynthSound*>(sound) != nullptr;
    }

    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition){
      frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber, 440);
      std::cout << midiNoteNumber << std::endl;
        
    }

    void stopNote (float velocity, bool allowTailOff){
      clearCurrentNote();
    }

    void pitchWheelMoved (int newPitchWheel){

    }

    void controllerMoved (int controllerNumber, int newControllerValue){

    }

    void renderNextBlock (AudioBuffer<float> &coutputBuffer, int startSample, int numSamples){

    }


  private:
    double level;
    double frequency;



};

