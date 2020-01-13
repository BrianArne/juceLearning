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
    void getEnvelopeParams(float* attack, float* decay, float* sustain, float* release)
    {
      env1.setAttack(double(*attack));
      env1.setDecay(double(*decay));
      env1.setSustain(double(*sustain));
      env1.setRelease(double(*release));
    }

    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
      env1.trigger = 1;
      level = velocity;
      frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber, 440);
      std::cout << "Midi Note: " << midiNoteNumber << std::endl;
    }

    void stopNote (float velocity, bool allowTailOff)
    {
      env1.trigger = 0;
      allowTailOff = true;
      clearCurrentNote();
    }

    void pitchWheelMoved (int newPitchWheel)
    {

    }

    void controllerMoved (int controllerNumber, int newControllerValue)
    {

    }

    // 
    double setEnvelope()
    {
      return env1.adsr(setOscType(), env1.trigger);
    }


    void renderNextBlock (AudioBuffer<float> &coutputBuffer, int startSample, int numSamples)
    {
      auto sampleRate = getSampleRate();
      for(int sample = 0; sample < numSamples; ++sample){
        for(int channel = 0; channel < coutputBuffer.getNumChannels(); ++channel){
          auto myVal = setEnvelope();
          coutputBuffer.addSample(channel, startSample, setEnvelope() * 0.5f);
        }
        ++startSample;
      }
    }

    // Sets user selected osc type to the member var theWave
    void getOscType(float* selection)
    {
      theWave = *selection;
    }

    // Change to case statement
    double setOscType(){
      double sample1;
      switch(theWave){
        case 0:
          sample1 = osc1.sinewave(frequency);
        case 1:
          sample1 = osc1.square(frequency);
          break;
        case 2:
          sample1 = osc1.saw(frequency);
          break;
        default:
          sample1 = osc1.sinewave(frequency);
      }
      return sample1;
    }

    // Sets user selected filter type to the member var filterChoice;
    void getFilterParams(float* filterType, float* filterCutoff, float* filterRes)
    {
      filterChoice = *filterType;
      cutoff = *filterCutoff;
      resonance = *filterRes;
    }

    // Change to case statement
    double setFilterParams()
    {
      double sample1;
      switch(filterChoice){
        case 0:
          sample1 = filter1.lores(setEnvelope(), cutoff, resonance);
          break;
        case 1:
          sample1 = filter1.hires(setEnvelope(), cutoff, resonance);
          break;
        case 2:
          sample1 = filter1.bandpass(setEnvelope(), cutoff, resonance);
          break;
      }
      return sample1;
    }

  private:
    double level;
    double frequency;
    int theWave;

    int filterChoice;
    int resonance;
    float cutoff;

    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;
};

