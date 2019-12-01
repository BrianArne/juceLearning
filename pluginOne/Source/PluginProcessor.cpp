/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginOneAudioProcessor::PluginOneAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
     //rawVolume(-5.0f),
     treeState(*this, nullptr)
#endif
{
  NormalisableRange<float> gainRange(-48.0f, 0.0f);
  treeState.createAndAddParameter(GAIN_ID, GAIN_NAME, GAIN_NAME, gainRange, 0.5, nullptr, nullptr);
  treeState.state = ValueTree("savedParams");
}

PluginOneAudioProcessor::~PluginOneAudioProcessor()
{
}

//==============================================================================
const String PluginOneAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PluginOneAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluginOneAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PluginOneAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PluginOneAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginOneAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PluginOneAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PluginOneAudioProcessor::setCurrentProgram (int index)
{
}

const String PluginOneAudioProcessor::getProgramName (int index)
{
    return {};
}

void PluginOneAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void PluginOneAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
  rawVolume = 0.5f;
  previousGain = pow(10, *treeState.getRawParameterValue(GAIN_ID) / 20);
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void PluginOneAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PluginOneAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void PluginOneAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    float currentGain = pow(10, *treeState.getRawParameterValue(GAIN_ID) / 20);

     
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    //Gain ramp
    if(currentGain == previousGain){
      buffer.applyGain(currentGain);
    }else{
      buffer.applyGainRamp(0, buffer.getNumSamples(), previousGain, currentGain);
      previousGain = currentGain;
    }

} 
//==============================================================================
bool PluginOneAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PluginOneAudioProcessor::createEditor()
{
    return new PluginOneAudioProcessorEditor (*this);
}

//==============================================================================
void PluginOneAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your treeState in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    //XmlElement* xml  = new XmlElement(treeState.state.createXml);
    std::shared_ptr<XmlElement> xml (treeState.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void PluginOneAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your treeState from this memory block,
    // whose contents will have been created by the getStateInformation() call.
  std::shared_ptr<XmlElement> theParams (getXmlFromBinary(data, sizeInBytes));
  if(theParams != nullptr){
    if(theParams->hasTagName(treeState.state.getType())){
      treeState.state = ValueTree::fromXml(*theParams);
    }
  }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginOneAudioProcessor();
}
