/*
  ==============================================================================

    SynthVoice.h
    Created: 4 Dec 2019 5:58:04am
    Author:  Brian Arne

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "maximilian.h"
#include "SynthSound.h"

class SynthVoice  : public SynthesiserVoice
{
  public:

    bool canPlaySound (SynthesiserSound* sound)
    {
      return dynamic_cast<SynthSound*>(sound) != nullptr;
    }

    void getParam(float* attack, float* release)
    {
      env1.setAttack(double(*attack));
      env1.setRelease(double(*release));
    }

    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
      env1.trigger = 1;
      level = velocity;
      frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber, 440);
      std::cout << midiNoteNumber << std::endl;
    }

    void stopNote (float velocity, bool allowTailOff)
    {
      env1.trigger = 0;
      allowTailOff = true;
      if(velocity == 0)
        clearCurrentNote();
    }

    void pitchWheelMoved (int newPitchWheel)
    {

    }

    void controllerMoved (int controllerNumber, int newControllerValue)
    {

    }

    void renderNextBlock (AudioBuffer<float> &coutputBuffer, int startSample, int numSamples)
    {
      //Init settings for envelope
      env1.setDecay(500);
      env1.setSustain(0.8);

      for(int sample = 0; sample < numSamples; ++sample){
        // The osc
        double theWave = osc1.saw(frequency);

        // routing osc into the envelope
        double theSound = env1.adsr(theWave, env1.trigger) * level;

        // Filter
        //double filteredSound = filter1.lores(theSound, 200, 0.1);

        for(int channel = 0; channel < coutputBuffer.getNumChannels(); ++channel){
          coutputBuffer.addSample(channel, startSample, theSound);
        }
        ++startSample;
      }
    }

  private:
    double level;
    double frequency;

    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;



};

