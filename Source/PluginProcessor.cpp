/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CMLS_HW2_GROUP5AudioProcessor::CMLS_HW2_GROUP5AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput  ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
tree (*this, nullptr
    ,"PARAMETERS", 
    {
        std::make_unique<juce::AudioParameterFloat>("attack", "Attack", juce::NormalisableRange<float>(0.1f, 5000.0f), 0.1f),
        std::make_unique<juce::AudioParameterFloat>("release", "Release", juce::NormalisableRange<float>(0.1f, 5000.0f), 0.1f),
        std::make_unique<juce::AudioParameterFloat>("sustain", "Sustain", juce::NormalisableRange<float>(0.0f, 1.0f), 0.8f),
        std::make_unique<juce::AudioParameterFloat>("decay", "Decay", juce::NormalisableRange<float>(1.0f, 2000.0f), 1.0f),
        std::make_unique<juce::AudioParameterFloat>("wavetype", "WaveType", juce::NormalisableRange<float>(0.0f, 3.0f), 0.0f),
        std::make_unique<juce::AudioParameterFloat>("filterCutoff", "FilterCutoff", juce::NormalisableRange<float>(40.0f, 20000.0f), 1000.0f),
        std::make_unique<juce::AudioParameterFloat>("filterRes", "FilterRes", juce::NormalisableRange<float>(1.0f, 5.0f), 1.0f),
    }
    ), lowPassFilter(juce::dsp::IIR::Coefficients<float>::makeLowPass(44100, 20000.0f, 0.1f))
#endif
{
    //juce::NormalisableRange<float> attackParam(0.1f, 5000.0f);
    //juce::NormalisableRange<float> releaseParam(0.1f, 5000.0f);
    //juce::NormalisableRange<float> sustainParam(0.0f, 1.0f);
    //juce::NormalisableRange<float> decayParam(1.0f, 2000.0f);
    //juce::NormalisableRange<float> waveTypeParam(0.0f, 2.0f);
    //juce::NormalisableRange<float> filterCutOffParam(40.0f, 20000.0f);
    //juce::NormalisableRange<float> filterResParam(1.0f, 5.0f);
    //tree.createAndAddParameter("attack", "Attack", "Attack", attackParam, 0.1f, nullptr, nullptr);
    //tree.createAndAddParameter("release", "Release", "Release", releaseParam, 0.1f, nullptr, nullptr);
    //tree.createAndAddParameter("sustain", "Sustain", "Sustain", sustainParam, 0.8f, nullptr, nullptr);
    //tree.createAndAddParameter("decay", "Decay", "Decay", decayParam, 1.0f, nullptr, nullptr);
    //tree.createAndAddParameter("wavetype", "WaveType", "WaveType", waveTypeParam, 0.0f, nullptr, nullptr);
    //tree.createAndAddParameter("filterCutoff", "FilterCutoff", "FilterCutoff", filterCutOffParam, 1000.0f, nullptr, nullptr);
    //tree.createAndAddParameter("filterRes", "FilterRes", "FilterRes", filterResParam, 1.0f, nullptr, nullptr);

    mySynth.clearVoices();

    for (int i = 0; i < 5; i++)
    {
        mySynth.addVoice(new SynthVoice());
    }

    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());

}

CMLS_HW2_GROUP5AudioProcessor::~CMLS_HW2_GROUP5AudioProcessor()
{
}

//==============================================================================
const juce::String CMLS_HW2_GROUP5AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CMLS_HW2_GROUP5AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CMLS_HW2_GROUP5AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CMLS_HW2_GROUP5AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CMLS_HW2_GROUP5AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CMLS_HW2_GROUP5AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CMLS_HW2_GROUP5AudioProcessor::getCurrentProgram()
{
    return 0;
}

void CMLS_HW2_GROUP5AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String CMLS_HW2_GROUP5AudioProcessor::getProgramName (int index)
{
    return {};
}

void CMLS_HW2_GROUP5AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void CMLS_HW2_GROUP5AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = lastSampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    lowPassFilter.reset();
    lowPassFilter.prepare(spec);
    updateFilter();
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void CMLS_HW2_GROUP5AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CMLS_HW2_GROUP5AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void CMLS_HW2_GROUP5AudioProcessor::updateFilter()
{
    int freq = *tree.getRawParameterValue("filterCutoff");
    int res = *tree.getRawParameterValue("filterRes");

    *lowPassFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(lastSampleRate, freq, res);
}

void CMLS_HW2_GROUP5AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{


    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))))
        {
            float* newAttack = (float*)tree.getRawParameterValue("attack");
            float* newRelease = (float*)tree.getRawParameterValue("release");
            float* newSustain = (float*)tree.getRawParameterValue("sustain");
            float* newDecay = (float*)tree.getRawParameterValue("decay");
            float* newOscType = (float*)tree.getRawParameterValue("wavetype");
            float* newFilterCutoff = (float*)tree.getRawParameterValue("filterCutoff");
            float* newFilterRes = (float*)tree.getRawParameterValue("filterRes");

            myVoice->getEnvParam(newAttack, newRelease,newSustain, newDecay);
            myVoice->getOscType(newOscType);
            myVoice->getFilParam(newFilterCutoff, newFilterRes);
            //float* newFloatPtrAttack = (float*)tree.getRawParameterValue("attack");
            //float* newFloatPtrRelease = (float*)tree.getRawParameterValue("release");
            //float* newFloatPtrSustain = (float*)tree.getRawParameterValue("sustain");
            //float* newFloatPtrDecay = (float*)tree.getRawParameterValue("decay");
            //float* newFloatPtrOscType = (float*)tree.getRawParameterValue("wavetype");
            //float* newFloatPtrFilterCutoff = (float*)tree.getRawParameterValue("filterCutoff");
            //float* newFloatPtrFilterRes = (float*)tree.getRawParameterValue("filterRes");
            //myVoice->getEnvParam(newFloatPtrAttack, newFloatPtrRelease, newFloatPtrSustain, newFloatPtrDecay);
            //myVoice->getOscType(newFloatPtrOscType);
            //myVoice->getFilterParams(newFloatPtrFilterCutoff, newFloatPtrFilterRes);
        }
    }
    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    updateFilter();
    juce::dsp::AudioBlock<float> block(buffer);
    lowPassFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
    //juce::ScopedNoDenormals noDenormals;
    //auto totalNumInputChannels  = getTotalNumInputChannels();
    //auto totalNumOutputChannels = getTotalNumOutputChannels();

    //// In case we have more outputs than inputs, this code clears any output
    //// channels that didn't contain input data, (because these aren't
    //// guaranteed to be empty - they may contain garbage).
    //// This is here to avoid people getting screaming feedback
    //// when they first compile a plugin, but obviously you don't need to keep
    //// this code if your algorithm always overwrites all the output channels.
    //for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    //    buffer.clear (i, 0, buffer.getNumSamples());

    //// This is the place where you'd normally do the guts of your plugin's
    //// audio processing...
    //// Make sure to reset the state if your inner loop is processing
    //// the samples and the outer loop is handling the channels.
    //// Alternatively, you can process the samples with the channels
    //// interleaved by keeping the same state.
    //for (int channel = 0; channel < totalNumInputChannels; ++channel)
    //{
    //    auto* channelData = buffer.getWritePointer (channel);

    //    // ..do something to the data...
    //}
}

//==============================================================================
bool CMLS_HW2_GROUP5AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* CMLS_HW2_GROUP5AudioProcessor::createEditor()
{
    return new CMLS_HW2_GROUP5AudioProcessorEditor(*this);
}

//==============================================================================
void CMLS_HW2_GROUP5AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CMLS_HW2_GROUP5AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CMLS_HW2_GROUP5AudioProcessor();
}
