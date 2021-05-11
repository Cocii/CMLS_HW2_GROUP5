/*
  ==============================================================================

    Envelope.cpp
    Created: 7 May 2021 3:09:30pm
    Author:  Cocii

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(CMLS_HW2_GROUP5AudioProcessor& p) :
    processor(p)
{
    setSize(200, 200);

    attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);    // Set Slider style
    attackSlider.setRange(0.1f, 5000.0f);                                      // Set the value range
    attackSlider.setValue(0.1f);                                               // Set default values
    attackSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);        // Set the text box
    addAndMakeVisible(&attackSlider);
    
    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.1f, 5000.0f);
    releaseSlider.setValue(0.8f);
    releaseSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&releaseSlider);
    
    decaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(1.0f, 2000.0f);
    decaySlider.setValue(1.0f);
    decaySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&decaySlider);
    
    sustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.0f, 1.0f);
    sustainSlider.setValue(0.8f);
    sustainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&sustainSlider);
    
    //sends value of the slider to the tree state in the processor
    attackVal = new juce::AudioProcessorValueTreeState::SliderAttachment(processor.tree, "attack", attackSlider);
    releaseVal = new juce::AudioProcessorValueTreeState::SliderAttachment(processor.tree, "release", releaseSlider);
    decayVal = new juce::AudioProcessorValueTreeState::SliderAttachment(processor.tree, "decay", decaySlider);
    sustainVal = new juce::AudioProcessorValueTreeState::SliderAttachment(processor.tree, "sustain", sustainSlider);
}

Envelope::~Envelope()
{
}

void Envelope::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::aquamarine);
    g.drawText("Envelope", titleArea, juce::Justification::centredTop);

    g.drawText("A", 53, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("D", 77, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("S", 103, 150, 20, 20,juce::Justification::centredTop);
    g.drawText("R", 128, 150, 20, 20,juce::Justification::centredTop);
    
    juce::Rectangle<float> area(25, 25, 150, 150);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Envelope::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(50);

    int sliderWidth = 25;
    int sliderHeight = 175;

    attackSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    decaySlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    sustainSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    releaseSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}
