/*
  ==============================================================================

    SynthSound.h
    Created: 7 May 2021 3:09:02pm
    Author:  Cocii

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int /*midiNoteNumber*/)
    {
        return true;
    }
    
    bool appliesToChannel(int /*midiChannel*/)
    {
        return true;
    }
};