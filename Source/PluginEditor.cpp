/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Oscillator.h"
#include "Effects.h"

//==============================================================================
VIVI_SynthAudioProcessorEditor::VIVI_SynthAudioProcessorEditor (VIVI_SynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)  , Tab (juce::TabbedButtonBar::Orientation::TabsAtTop)
{
    /*  
		Make sure that before the constructor has finished, you've set the
		editor's size to whatever you need it to be. 
	*/

	setSize(1500, 900);
	addAndMakeVisible(Tab);
	Tab.setAccessible(true);

	// 	Oscillator and Effects Pages setup with GUI objects
	//	Next Change is keyboard mapping and fixing tabbed interface for accessibility Stuff

	Tab.addTab("Oscillator", juce::Colours::linen,new OscillatorPage(), false);
	Tab.addTab("Effects", juce::Colours::purple, new EffectsPage(), false);

	Tab.addTab("Settings Page", juce::Colours::limegreen, new juce::Component, false);

	Themes(1);						// Initalise Theme Function

	for (auto j = 0; j < Button.size(); j++)
	{
		addAndMakeVisible(Button[j]);
		Button[j]->setClickingTogglesState(true);
	}
	/*
	Button[0]->setBounds(getWidth()-224, TopMargin +SliderHeight+ 50, 200, 200);
	Button[1]->setBounds(getWidth()-224, TopMargin+SliderHeight+350 , 200, 200);
	*/

}

VIVI_SynthAudioProcessorEditor::~VIVI_SynthAudioProcessorEditor()
{

}

//==============================================================================
void VIVI_SynthAudioProcessorEditor::paint(juce::Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(juce::Colours::aqua);

}
void  VIVI_SynthAudioProcessorEditor::Themes(int SelectedTheme)
{

	switch (SelectedTheme)
	{
	case 1:

		OtherLookAndFeel.setColour(juce::Slider::thumbColourId, juce::Colours::white);
		OtherLookAndFeel.setColour(juce::Slider::backgroundColourId, juce::Colours::black);

		break;
	case 2:

		OtherLookAndFeel.setColour(juce::Slider::thumbColourId, juce::Colours::purple);
		OtherLookAndFeel.setColour(juce::Slider::backgroundColourId, juce::Colours::white);

		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}

}

void VIVI_SynthAudioProcessorEditor::resized()
{
	// Border for Tab Interface
	Tab.setBounds(getLocalBounds().reduced(20));
	
}
