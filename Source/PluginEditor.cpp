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
	// Size of editor page	
	setSize(1000, 700);
	
	int windowWidth{ getWidth() }, WindowTenth{windowWidth/10};

	float ButtonOneX{ getWidth() - TabIndent - ButtonOneD },
		ButtonTwoY{TabIndent - 1};


	addAndMakeVisible(Tab);
	

	// 	Oscillator and Effects Pages setup with GUI objects
	//	Next Change is keyboard mapping and fixing tabbed interface for accessibility Stuff

	Tab.addTab("Oscillator Page", juce::Colours::linen,OscPointer, false);
	Tab.addTab("Effects Page", juce::Colours::purple,EffectPointer, false);
	Tab.addTab("Settings Page", juce::Colours::purple,EffectPointer, false);

	//Tab.addTab("Settings Page", juce::Colours::limegreen, new juce::Component, false);


	for (int i = 0; i < Tab.getNumTabs(); i++)
		Tab.setTabBackgroundColour(i, juce::Colours::black);
	
	for (auto j = 0; j < MainControls.size(); j++)
	{

		addAndMakeVisible(MainControls[j]);
		MainControls[j]->setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
		MainControls[j]->setWantsKeyboardFocus(true);
		MainControls[j]->setRange(0.00, 1.00, 0.01);
		MainControls[j]->addListener(this);
	}

	addAndMakeVisible(Mute);
	Mute.setClickingTogglesState(true);
	Mute.setBounds(ButtonOneX, ButtonTwoY, ButtonOneD, TabDepth);
	Mute.addListener(this);


	MainControls[0]->setBounds((windowWidth)-((windowWidth/5)*1.25),mainControlY ,mainControlWidth, mainControlHeight);
	MainControls[1]->setBounds(MainControls[0]->getX()+WindowTenth+20,mainControlY ,mainControlWidth, mainControlHeight);
	
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

void VIVI_SynthAudioProcessorEditor::sliderValueChanged(juce::Slider* sliderThatMoved)
{

	// Gain Slider Hook
	if (sliderThatMoved == MainControls[0])
	{
		float VolumeSlider = sliderThatMoved->getValue();
		audioProcessor.setParameter(15, VolumeSlider);
	}

	// Gate Slider Hook
	else if (sliderThatMoved == MainControls[0])
	{
		float GateSlider = sliderThatMoved->getValue();
		audioProcessor.setParameter(6, GateSlider);

	}
}

// Mute Button On and off
void VIVI_SynthAudioProcessorEditor::buttonClicked(juce::Button* toggledButton)
{
	int ProcessorState = 1;

	if (toggledButton == &Mute)
	{
		bool Togglestate = Mute.getToggleState();

		// If True set mute parameter to 1. if false 0
		if (Togglestate == true) 
		{
			ProcessorState = 1;
			Mute.setDescription("ON");
			
		}
		else 
		{
			ProcessorState = 0;
			Mute.setDescription("OFF");
			DBG(ProcessorState);
		}
	}

}
// Hooking up oscillator Page (Not optimium but works) [Fix scaling in Gen~]


/*
(juce::Slider* sliderThatMoved)
{	
	// Oscillator One
	if (sliderThatMoved == Sliders[0])
	{
		float OscillatorOneValue = sliderThatMoved->getValue();
		auto OscillatorOneLin = juce::Decibels::decibelsToGain(OscillatorOneValue);
		ProcessorLink.setParameter(9, OscillatorOneLin);

		DBG(ProcessorLink.getParameter(9));
	}
	/*
	// Selecting Oscillator Two
	else if (sliderThatMoved == Sliders[1])
	{
		float OscillatorTwoValue = sliderThatMoved->getValue();
		auto OscillatorTwoLin = juce::Decibels::decibelsToGain(OscillatorTwoValue);
		ProcessorLink.setParameter(12, OscillatorTwoLin);
		DBG(ProcessorLink.getParameter(12));

	}
	// Selecting Oscillator Two
	else if (sliderThatMoved == Sliders[2])
	{
		float OscillatorThreeValue = sliderThatMoved->getValue();
		auto OscillatorThreeLin = juce::Decibels::decibelsToGain(OscillatorThreeValue);
		ProcessorLink.setParameter(11, OscillatorThreeLin);
		DBG(ProcessorLink.getParameter(11));
	}
	// Slecting Oscillator Three
	else if (sliderThatMoved == Sliders[3])
	{
		float OscillatorFourValue = sliderThatMoved->getValue();
		ProcessorLink.setParameter(8, OscillatorFourValue);

	}
	// Selecting Oscillator Four
	else if (sliderThatMoved == Sliders[4])
	{
		float OscillatorFiveValue = sliderThatMoved->getValue();
		ProcessorLink.setParameter(7, OscillatorFiveValue);

	}
	// Selecting Oscillator Six
	else if (sliderThatMoved == Sliders[5])
	{
		float OscillatorSixValue = sliderThatMoved->getValue();
		ProcessorLink.setParameter(10, OscillatorSixValue);

	}
	// Selecting Spreader
	else if (sliderThatMoved == Sliders[6])
	{
		float SpreaderSliderValue = sliderThatMoved->getValue();
		ProcessorLink.setParameter(14, SpreaderSliderValue);
	}
	*/

void EffectsPage::sliderValueChanged(juce::Slider* slider)
{	
	// Redux Slider link
	if (slider == Effects[0])
	{
		float ReduxLevel = Effects[0]->getValue();
		ProcessorLinker.setParameter(13,ReduxLevel);

	}
	// Bitcrush Volume link
	else if (slider == Effects[1])
	{
		float BitCrushLevel = Effects[0]->getValue();
		ProcessorLinker.setParameter(1,BitCrushLevel);
	}
	// Delay LFO 
	else if (slider == Effects[2])
	{
		float DelayLFOLevel = Effects[2]->getValue();
		ProcessorLinker.setParameter(2, DelayLFOLevel);
		

	}
	// AM
	else if (slider == Effects[3])
	{
		float AMLevel = Effects[3]->getValue();
		ProcessorLinker.setParameter(0, AMLevel);
		
	}
	// Filter Cuttoff
	else if (slider == Effects[4])
	{
		float CuttoffFreuency = Effects[4]->getValue();
		ProcessorLinker.setParameter(3, CuttoffFreuency);
	}
	// Filter Q
	else if (slider == Effects[5])
	{
		float FilterQlevel = Effects[5]->getValue();
		ProcessorLinker.setParameter(4, FilterQlevel);
	}
}

void VIVI_SynthAudioProcessorEditor::resized()
{
	
	// Border for Tab Interface
	Tab.setBounds(getLocalBounds().reduced(TabIndent));
	Tab.setTabBarDepth(TabDepth);

}


