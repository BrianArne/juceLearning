/*
  ==============================================================================

   This file is part of the JUCE tutorials.
   Copyright (c) 2017 - ROLI Ltd.

   The code included in this file is provided under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license. Permission
   To use, copy, modify, and/or distribute this software for any purpose with or
   without fee is hereby granted provided that the above copyright notice and
   this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES,
   WHETHER EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR
   PURPOSE, ARE DISCLAIMED.

  ==============================================================================
*/

/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.
BEGIN_JUCE_PIP_METADATA 
 name:             PlayingSoundFilesTutorial
 version:          1.0.0
 vendor:           JUCE
 website:          http://juce.com
 description:      Plays audio files.

 dependencies:     juce_audio_basics, juce_audio_devices, juce_audio_formats,
                   juce_audio_processors, juce_audio_utils, juce_core,
                   juce_data_structures, juce_events, juce_graphics,
                   juce_gui_basics, juce_gui_extra
 exporters:        xcode_mac, vs2017, linux_make

 type:             Component
 mainClass:        MainContentComponent

 useLocalCopy:     1

 END_JUCE_PIP_METADATA

*******************************************************************************/


#pragma once

//==============================================================================
class MainContentComponent   : public AudioAppComponent,
                               public ChangeListener
{
public:
    MainContentComponent()
        :   state (Stopped)
    {
        addAndMakeVisible (&openButton);
        openButton.setButtonText ("Open...");
        openButton.onClick = [this] { openButtonClicked(); };

        addAndMakeVisible (&playButton);
        playButton.setButtonText ("Play");
        playButton.onClick = [this] { playButtonClicked(); };
        playButton.setColour (TextButton::buttonColourId, Colours::green);
        playButton.setEnabled (false);

        addAndMakeVisible (&stopButton);
        stopButton.setButtonText ("Stop");
        stopButton.onClick = [this] { stopButtonClicked(); };
        stopButton.setColour (TextButton::buttonColourId, Colours::red);
        stopButton.setEnabled (false);

        addAndMakeVisible (&timeLabel);
        timeLabel.setFont(Font(16.0f, Font::bold));
        timeLabel.setText("Play time: ", dontSendNotification);

        setSize (300, 200);

        formatManager.registerBasicFormats();       // [1]
        transportSource.addChangeListener (this);   // [2]

        setAudioChannels (0, 2);
    }

    ~MainContentComponent() override
    {
        shutdownAudio();
    }

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {
        transportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
    }

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        if (readerSource.get() == nullptr)
        {
            bufferToFill.clearActiveBufferRegion();
            return;
        }

        transportSource.getNextAudioBlock (bufferToFill);
    }

    void releaseResources() override
    {
        transportSource.releaseResources();
    }

    void resized() override
    {
        openButton.setBounds (10, 10, getWidth() - 20, 20);
        playButton.setBounds (10, 40, getWidth() - 20, 20);
        stopButton.setBounds (10, 70, getWidth() - 20, 20);
        timeLabel.setBounds(10,100, getWidth() -20, 20);
    }

    void changeListenerCallback (ChangeBroadcaster* source) override
    {
        if (source == &transportSource)
        {
            if (transportSource.isPlaying())
                changeState (Playing);
            else if ((state == Stopping) || (state == Playing))
              changeState (Stopped);
            else if (state == Pausing)
              changeState (Paused);
        }
    }

private:
    enum TransportState
    {
        Stopped,
        Starting,
        Playing,
        Pausing,
        Paused,
        Stopping
    };

    void changeState (TransportState newState)
    {
        if (state != newState)
        {
            state = newState;

            switch (state)
            {
                case Stopped:                           // [3]
                    stopButton.setEnabled (false);
                    playButton.setEnabled (true);
                    transportSource.setPosition (0.0);
                    break;

                case Starting:                          // [4]
                    playButton.setEnabled (false);
                    transportSource.start();
                    break;

                case Playing:                           // [5]
                    stopButton.setEnabled (true);
                    break;

                case Pausing:
                    transportSource.stop();
                    break;

                case Paused:
                    playButton.setButtonText ("Resume");
                    stopButton.setButtonText ("Return to Zero");
                    break;

                case Stopping:                          // [6]
                    transportSource.stop();
                    break;
            }
        }
    }

    void openButtonClicked()
    {
        FileChooser chooser ("Select a Wave file to play...",
                             {},
                             "*.wav;*.aif;*.aiff");                                        // [7]

        if (chooser.browseForFileToOpen())                                    // [8]
        {
            auto file = chooser.getResult();                                  // [9]
            auto* reader = formatManager.createReaderFor (file);              // [10]

            if (reader != nullptr)
            {
                std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource (reader, true)); // [11]
                transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);                     // [12]
                playButton.setEnabled (true);                                                                    // [13]
                readerSource.reset (newSource.release());                                                        // [14]
            }
        }
    }

    void playButtonClicked()
    {
      if ((state == Stopped) || (state == Paused))
        changeState (Starting);
      else if (state == Playing)
        changeState (Pausing);
    }

    void stopButtonClicked()
    {
      if (state == Paused)
        changeState (Stopped);
      else 
        changeState (Stopping);
    }

    //==========================================================================
    TextButton openButton;
    TextButton playButton;
    TextButton stopButton;
    Label timeLabel;

    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    TransportState state;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
