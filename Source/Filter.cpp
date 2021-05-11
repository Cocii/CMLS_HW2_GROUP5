/*
  ==============================================================================

    Filter.cpp
    Created: 7 May 2021 3:09:30pm
    Author:  Cocii

  ==============================================================================
*/
#include <JuceHeader.h>
#include "Filter.h"

//==============================================================================
Filter::Filter(CMLS_HW2_GROUP5AudioProcessor& p) :
    processor(p)
{
    setSize(200, 200);

    filterCutoff.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterCutoff.setRange(40.0, 20000.0);
    filterCutoff.setValue(1000.0);
    filterCutoff.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&filterCutoff);
    filterVal = new juce::AudioProcessorValueTreeState::SliderAttachment(processor.tree, "filterCutoff", filterCutoff);
    filterCutoff.setSkewFactorFromMidPoint(1000.0);

    filterRes.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterRes.setRange(1, 5);
    filterRes.setValue(1);
    filterRes.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&filterRes);
    resVal = new juce::AudioProcessorValueTreeState::SliderAttachment(processor.tree, "filterRes", filterRes);
}

Filter::~Filter()
{
}

void Filter::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::aquamarine);
    g.drawText("Filter", titleArea, juce::Justification::centredTop);


    juce::Rectangle<float> area(25, 25, 150, 150);

    g.drawRoundedRectangle(area, 20.0f, 2.0f);
    g.drawText("cutoff", 30, 150, 70, 20, juce::Justification::centredTop);
    g.drawText("resonance", 100, 150, 70, 20, juce::Justification::centredTop);

    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::silver);                   // Set the handle color
    getLookAndFeel().setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::darkgrey);   // Set the knob value bar background color
    getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::aquamarine);    // Set the knob fill
    getLookAndFeel().setColour(juce::Slider::backgroundColourId, juce::Colours::darkgrey);            // Set the colour of the slider's background.
    getLookAndFeel().setColour(juce::Slider::trackColourId, juce::Colours::aquamarine);               // Set colour to draw the groove that the thumb moves along.
}

void Filter::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    filterCutoff.setBounds(30, 60, 70, 70);
    filterRes.setBounds(100, 60, 70, 70);
}
