/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TutorialPluginAudioProcessor::TutorialPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

TutorialPluginAudioProcessor::~TutorialPluginAudioProcessor()
{
}

//==============================================================================
const String TutorialPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TutorialPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TutorialPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TutorialPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TutorialPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TutorialPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TutorialPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TutorialPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String TutorialPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void TutorialPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TutorialPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void TutorialPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TutorialPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TutorialPluginAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{

  buffer.clear();

  MidiBuffer processedMidi;
  int time;
  MidiMessage m;

  for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
  {
    if (m.isNoteOn())
    {
      uint8 newVel = (uint8)noteOnVel;
      m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber(), newVel);
    }
    else if (m.isNoteOff())
    {
    }
    else if (m.isAftertouch())
    {
    }
    else if (m.isPitchWheel())
    {
    }

    processedMidi.addEvent (m, time);
  }

  midiMessages.swapWith (processedMidi);
}

//==============================================================================
bool TutorialPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TutorialPluginAudioProcessor::createEditor()
{
    return new TutorialPluginAudioProcessorEditor (*this);
}

//==============================================================================
void TutorialPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TutorialPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TutorialPluginAudioProcessor();
}
