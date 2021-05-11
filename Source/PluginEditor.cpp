/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CMLS_HW2_GROUP5AudioProcessorEditor::CMLS_HW2_GROUP5AudioProcessorEditor(CMLS_HW2_GROUP5AudioProcessor& p)
 : AudioProcessorEditor (&p), processor (p), oscGUI(p), envGUI(p), filterGUI(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    //setSize (400, 300);
    //setSize (600, 400);
    setSize (600, 200);
    addAndMakeVisible(&oscGUI);
    addAndMakeVisible(&envGUI);
    addAndMakeVisible(&filterGUI);

    //attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    //attackSlider.setRange(0.1f,5000.0f);
    //attackSlider.setValue(0.1f);
    //attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 20.0, 10.0);
    //attackSlider.addListener(this);
    //addAndMakeVisible(&attackSlider);

    //releaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    //releaseSlider.setRange(0.1f, 5000.0f);
    //releaseSlider.setValue(0.1f);
    //releaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 20.0, 10.0);
    //releaseSlider.addListener(this);
    //addAndMakeVisible(&attackSlider);

    //sliderTree = new juce::AudioProcessorValueTreeState::SliderAttachment(processor.tree,"attack", attackSlider);
}

CMLS_HW2_GROUP5AudioProcessorEditor::~CMLS_HW2_GROUP5AudioProcessorEditor()
{
}

//==============================================================================
void CMLS_HW2_GROUP5AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    /*g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);*/
}

void CMLS_HW2_GROUP5AudioProcessorEditor::resized()
{
    attackSlider.setBounds(10, 10, 40, 100);// x, y, width, height
    juce::Rectangle<int> area = getLocalBounds();

    const int componentWidth = 200;
    const int componentHeight = 200;

    oscGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    filterGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    envGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));

}

void CMLS_HW2_GROUP5AudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &attackSlider)
    {
        processor.attackTime = attackSlider.getValue();
    }
    if (slider == &releaseSlider)
    {
        processor.attackTime = releaseSlider.getValue();
    }
}