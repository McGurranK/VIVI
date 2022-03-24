/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VIVI_SynthAudioProcessor::VIVI_SynthAudioProcessor()
:m_CurrentBufferSize(0)
{
	// use a default samplerate and vector size here, reset it later
	m_C74PluginState = (CommonState *)C74_GENPLUGIN::create(44100, 64);
	C74_GENPLUGIN::reset(m_C74PluginState);

	m_InputBuffers = new t_sample *[C74_GENPLUGIN::num_inputs()];
	m_OutputBuffers = new t_sample *[C74_GENPLUGIN::num_outputs()];
	
	for (int i = 0; i < C74_GENPLUGIN::num_inputs(); i++) {
		m_InputBuffers[i] = NULL;
	}
	for (int i = 0; i < C74_GENPLUGIN::num_outputs(); i++) {
		m_OutputBuffers[i] = NULL;
	}

}

VIVI_SynthAudioProcessor::~VIVI_SynthAudioProcessor()
{
	C74_GENPLUGIN::destroy(m_C74PluginState);
}

//==============================================================================
const juce::String VIVI_SynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int VIVI_SynthAudioProcessor::getNumParameters()
{
	return C74_GENPLUGIN::num_params();
}

float VIVI_SynthAudioProcessor::getParameter (int index)
{
	t_param value;
	t_param min = C74_GENPLUGIN::getparametermin(m_C74PluginState, index);
	t_param range = fabs(C74_GENPLUGIN::getparametermax(m_C74PluginState, index) - min);
	
	C74_GENPLUGIN::getparameter(m_C74PluginState, index, &value);
	
	value = (value - min) / range;
	
	return value;
}

void VIVI_SynthAudioProcessor::setParameter (int index, float newValue)
{
	t_param min = C74_GENPLUGIN::getparametermin(m_C74PluginState, index);
	t_param range = fabs(C74_GENPLUGIN::getparametermax(m_C74PluginState, index) - min);
	t_param value = newValue * range + min;
	
	C74_GENPLUGIN::setparameter(m_C74PluginState, index, value, NULL);
}

const juce::String VIVI_SynthAudioProcessor::getParameterName (int index)
{
    return juce::String(C74_GENPLUGIN::getparametername(m_C74PluginState, index));
}

const juce::String VIVI_SynthAudioProcessor::getParameterText (int index)
{
	juce::String text = juce::String(getParameter(index));
	text += juce::String(" ");
	text += juce::String(C74_GENPLUGIN::getparameterunits(m_C74PluginState, index));

	return text;
}

const juce::String VIVI_SynthAudioProcessor::getInputChannelName (int channelIndex) const
{
    return juce::String (channelIndex + 1);
}

const juce::String VIVI_SynthAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return juce::String (channelIndex + 1);
}

bool VIVI_SynthAudioProcessor::isInputChannelStereoPair (int index) const
{
	index;
	return C74_GENPLUGIN::num_inputs() == 2;
}

bool VIVI_SynthAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return C74_GENPLUGIN::num_outputs() == 2;
}

bool VIVI_SynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VIVI_SynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool VIVI_SynthAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double VIVI_SynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VIVI_SynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int VIVI_SynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VIVI_SynthAudioProcessor::setCurrentProgram (int index)
{
	index;
}

const juce::String VIVI_SynthAudioProcessor::getProgramName (int index)
{
	index;
	return juce::String();
}

void VIVI_SynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void VIVI_SynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	
	// initialize samplerate and vectorsize with the correct values
	m_C74PluginState->sr = sampleRate;
	m_C74PluginState->vs = samplesPerBlock;

	assureBufferSize(samplesPerBlock);
}

void VIVI_SynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void VIVI_SynthAudioProcessor::processBlock (juce::AudioSampleBuffer& buffer, juce::MidiBuffer& midiMessages)
{
	assureBufferSize(buffer.getNumSamples());
	
	// fill input buffers
	for (int i = 0; i < C74_GENPLUGIN::num_inputs(); i++) {
		if (i < getNumInputChannels()) {
			for (int j = 0; j < m_CurrentBufferSize; j++) {
				m_InputBuffers[i][j] = buffer.getReadPointer(i)[j];
			}
		} else {
			memset(m_InputBuffers[i], 0, m_CurrentBufferSize *  sizeof(double));
		}
	}
	
	// process audio
	C74_GENPLUGIN::perform(m_C74PluginState,
								  m_InputBuffers,
								  C74_GENPLUGIN::num_inputs(),
								  m_OutputBuffers,
								  C74_GENPLUGIN::num_outputs(),
								  buffer.getNumSamples());

	// fill output buffers
	for (int i = 0; i < getNumOutputChannels(); i++) {
		if (i < C74_GENPLUGIN::num_outputs()) {
			for (int j = 0; j < buffer.getNumSamples(); j++) {
				buffer.getWritePointer(i)[j] =(float) (m_OutputBuffers[i][j]) * 2;
			}
		} else {
			buffer.clear (i, 0, buffer.getNumSamples());
		}
	}
}

//==============================================================================
bool VIVI_SynthAudioProcessor::hasEditor() const
{
    return true; // (change this to true if you choose to supply an editor)
}

juce::AudioProcessorEditor* VIVI_SynthAudioProcessor::createEditor()
{	
	
	return new VIVI_SynthAudioProcessorEditor(*this);
	
    //return new juce::GenericAudioProcessorEditor(this);
	
}

//==============================================================================
void VIVI_SynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
	
	char *state;
	size_t statesize = C74_GENPLUGIN::getstatesize(m_C74PluginState);
	state = (char *)malloc(sizeof(char) * statesize);
	
	C74_GENPLUGIN::getstate(m_C74PluginState, state);
	destData.replaceWith(state, sizeof(char) * statesize);

	if (state) free(state);
}

void VIVI_SynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
	C74_GENPLUGIN::setstate(m_C74PluginState, (const char *)data);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VIVI_SynthAudioProcessor();
}

//==============================================================================
// C74 added methods

void VIVI_SynthAudioProcessor::assureBufferSize(long bufferSize)
{
	if (bufferSize > m_CurrentBufferSize) {
		for (int i = 0; i < C74_GENPLUGIN::num_inputs(); i++) {
			if (m_InputBuffers[i]) delete m_InputBuffers[i];
			m_InputBuffers[i] = new t_sample[bufferSize];
		}
		for (int i = 0; i < C74_GENPLUGIN::num_outputs(); i++) {
			if (m_OutputBuffers[i]) delete m_OutputBuffers[i];
			m_OutputBuffers[i] = new t_sample[bufferSize];
		}
		
		m_CurrentBufferSize = bufferSize;
	}
}
