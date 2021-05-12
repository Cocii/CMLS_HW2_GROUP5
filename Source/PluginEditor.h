/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "Envelope.h"
#include "Filter.h"

//==============================================================================
/**
*/
class CMLS_HW2_GROUP5AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    CMLS_HW2_GROUP5AudioProcessorEditor(CMLS_HW2_GROUP5AudioProcessor&);
    ~CMLS_HW2_GROUP5AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CMLS_HW2_GROUP5AudioProcessor& processor;
    //juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> sliderTree;
    //juce::Slider attackSlider;
    //juce::Slider releaseSlider;
    Oscillator oscGUI;
    Envelope envGUI;
    Filter filterGUI;


    juce::Slider filterCutoffDial;
    juce::Slider filterResDial;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> filterCutoffValue;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> filterResValue;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CMLS_HW2_GROUP5AudioProcessorEditor)
};
