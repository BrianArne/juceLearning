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

    void getParam(float* attack, float* decay, float* sustain, float* release)
    {
      env1.setAttack(double(*attack));
      env1.setDecay(double(*decay));
      env1.setAttack(double(*sustain));
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
      for(int sample = 0; sample < numSamples; ++sample){
        // routing osc into the envelope
        double theSound = env1.adsr(setOscType(), env1.trigger);

        for(int channel = 0; channel < coutputBuffer.getNumChannels(); ++channel){
          coutputBuffer.addSample(channel, startSample, theSound);
        }
        ++startSample;
      }
    }

    // Sets user selected osc type to the member var theWave
    void getOscType(float* selection)
    {
      theWave = *selection;
    }

    double setOscType(){
      if(theWave == 0){
        return osc1.sinewave(frequency);
      }
      if(theWave == 1){
        return osc1.saw(frequency);
      }
      if(theWave == 2){
        return osc1.square(frequency);
      }
      return osc1.sinewave(frequency);
    }

  private:
    double level;
    double frequency;
    int theWave;

    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;
};

