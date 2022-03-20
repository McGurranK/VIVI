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
	

	// 	Oscillator and Effects Pages setup with GUI objects
	//	Next Change is keyboard mapping and fixing tabbed interface for accessibility Stuff

	Tab.addTab("Oscillator Page", juce::Colours::linen,OscPointer, false);
	Tab.addTab("Effects Page", juce::Colours::purple,EffectPointer, false);
	Tab.addTab("Settings Page", juce::Colours::purple,EffectPointer, false);

	//Tab.addTab("Settings Page", juce::Colours::limegreen, new juce::Component, false);


	for (int i = 0; i < Tab.getNumTabs(); i++)
		Tab.setTabBackgroundColour(i, juce::Colours::black);
	
	for (auto j = 0; j < Button.size(); j++)
	{
		addAndMakeVisible(Button[j]);
		Button[j]->setClickingTogglesState(true);
	}

	float ButtonOneX{ getWidth() - TabIndent - ButtonOneD },
		ButtonTwoY{TabIndent+TabDepth};
	
	Button[0]->setBounds(ButtonOneX, ButtonTwoY, ButtonOneD, ButtonOneD);

	Button[1]->setBounds(getWidth()-224, 20+250+350 , 200, 200);
	
	// For loop through Background Colour
	for (int i = 0; i < Tab.getNumTabs(); i++)
		Tab.setTabBackgroundColour(i, juce::Colours::black);

}

VIVI_SynthAudioProcessorEditor::~VIVI_SynthAudioProcessorEditor()
{	

	// Deallocation of Heap
	delete OscPointer;
	delete EffectPointer;

}

//==============================================================================
void VIVI_SynthAudioProcessorEditor::paint(juce::Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)



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
	Tab.setBounds(getLocalBounds().reduced(TabIndent));
	Tab.setTabBarDepth(TabDepth);

}
