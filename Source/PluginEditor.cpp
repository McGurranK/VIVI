/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Oscillator.h"
#include "Effects.h"
#include "SettingsPage.h"
#include <memory>
using namespace std;

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
	Tab.setAccessible(true);
	

	// 	Oscillator and Effects Pages setup with GUI objects
	//	Next Change is keyboard mapping and fixing tabbed interface for accessibility Stuff

	Tab.addTab("Oscillator Page", juce::Colours::linen,new OscillatorPage(audioProcessor), true);
	Tab.addTab("Effects Page", juce::Colours::purple,new EffectsPage(audioProcessor), true);
	Tab.addTab("Settings Page", juce::Colours::purple, new SettingsPage, true);


	for (int i = 0; i < Tab.getNumTabs(); i++)
		Tab.setTabBackgroundColour(i, juce::Colours::black);
	
	for (auto j = 0; j < MainControls.size(); j++)
	{
		addAndMakeVisible(MainControls[j]);
		MainControls[j]->setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
		MainControls[j]->setWantsKeyboardFocus(true);
		MainControls[j]->setRange(0.00, 1.00, 0.01);
		MainControls[j]->addListener(this);
		MainControls[j]->setColour(juce::Slider::trackColourId,juce::Colours::purple);
		MainControls[j]->setHasFocusOutline(true);
		MainControls[j]->setTextBoxStyle(juce::Slider::TextBoxBelow,false,500,500);
	}

	addAndMakeVisible(Mute);
	Mute.setClickingTogglesState(true);
	Mute.setBounds(ButtonOneX, ButtonTwoY, ButtonOneD, TabDepth);
	Mute.addListener(this);


	MainControls[0]->setBounds((windowWidth)-((windowWidth/5)*1.25),mainControlY ,mainControlWidth, mainControlHeight);
	MainControls[1]->setBounds(MainControls[0]->getX()+WindowTenth+20,mainControlY ,mainControlWidth, mainControlHeight);

}


VIVI_SynthAudioProcessorEditor::~VIVI_SynthAudioProcessorEditor()
{	
}

//==============================================================================
void VIVI_SynthAudioProcessorEditor::paint(juce::Graphics& g)
{
	g.fillAll(juce::Colours::purple);

}
// Select Volume, Gate and Mute Parameters
bool VIVI_SynthAudioProcessorEditor::keyPressed(const juce::KeyPress & press)
{
	if (press == 'V')
	{
		MainControls[0]->grabKeyboardFocus();
		DBG("Volume");
	}
	else if (press == 'G')
	{
		MainControls[1]->grabKeyboardFocus();
		DBG("Gate");
	}
	else if (press == 'M')
	{
		Mute.grabKeyboardFocus();
		DBG("Mute");
	}
	else if (press == 'O')
	{
		Tab.setCurrentTabIndex(0);
	}
	else if (press == 'E')
	{
		Tab.setCurrentTabIndex(1);
	}
	else if (press == 'L')
	{
		Tab.setCurrentTabIndex(2);
	}
	return 0;
}

void SettingsPage::buttonClicked(juce::Button* Button)
{
}

void VIVI_SynthAudioProcessorEditor::resized()
{

	// Border for Tab Interface
	Tab.setBounds(getLocalBounds().reduced(TabIndent));
	Tab.setTabBarDepth(TabDepth);

}

void VIVI_SynthAudioProcessorEditor::sliderValueChanged(juce::Slider* sliderThatMoved)
{
	// Gain Slider Hook
	if (sliderThatMoved == MainControls[0])
	{
		float VolumeSlider = sliderThatMoved->getValue();
		sliderThatMoved->grabKeyboardFocus();
		audioProcessor.setParameter(15, VolumeSlider);
	}

	// Gate Slider Hook
	else if (sliderThatMoved == MainControls[0])
	{
		float GateSlider = sliderThatMoved->getValue();
		sliderThatMoved->grabKeyboardFocus();
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

/// Oscillator Page

// Hooking up oscillator Page (Not optimium but works)
void OscillatorPage::sliderValueChanged(juce::Slider* sliderThatMoved)
{
	if (sliderThatMoved == Sliders[0]) converter(sliderThatMoved, 9); // Oscillator One
	else if (sliderThatMoved == Sliders[1]) converter(sliderThatMoved, 12); // Oscillator Two
	else if (sliderThatMoved == Sliders[2]) converter(sliderThatMoved, 11); // Oscillator Three
	else if (sliderThatMoved == Sliders[3]) converter(sliderThatMoved, 8);	// Oscillator Four
	else if (sliderThatMoved == Sliders[4]) converter(sliderThatMoved, 7); // Oscillator Five
	else if (sliderThatMoved == Sliders[5]) converter(sliderThatMoved, 10); // Oscillator Six

	// Selecting spreader and normalising it
	else if (sliderThatMoved == Sliders[6])
	{
		float SpreaderSliderValue = sliderThatMoved->getValue();
		float NormalisedSpreader = SpreaderSliderValue / Sliders[6]->getMaximum();
		ProcessorRef.setParameter(14, NormalisedSpreader);
	}
}

// Changing Log to Linear values
void OscillatorPage::converter(juce::Slider* slider, int GenReferenceNumber)
{
	// Scaling Slider Value
	float CurrentValue = slider->getValue();
	float Output = juce::Decibels::decibelsToGain(CurrentValue);

	// Linking to Gen Audio Processor through ProcessorRef
	ProcessorRef.setParameter(GenReferenceNumber, Output);
	DBG(ProcessorRef.getParameter(GenReferenceNumber));
	DBG(ProcessorRef.getParameterID(GenReferenceNumber));
	slider->grabKeyboardFocus();
}

bool OscillatorPage::keyPressed(const juce::KeyPress & press)
{	
// Shortcuts for all slider objects on oscillator page

	if (press == ',') SliderFocus(0);       // Oscillator One Focus
	else if (press == '.')SliderFocus(1);   // Oscillator Two Focus
	else if (press == '/') SliderFocus(2);  // Oscillator Three Focus
	if (press == ';') SliderFocus(3);       // Oscillator Four Focus
	else if (press == '[') SliderFocus(4);  // Oscillator Five Focus
	else if (press == '#') SliderFocus(5);  // Oscillator Six Focus
	else if (press == 'S') SliderFocus(6);  // Spread Focus

	return false;
}
// Focus Function
void OscillatorPage::SliderFocus(int SliderFocus)
{
	Sliders[SliderFocus]->grabKeyboardFocus();
	DBG(Sliders[SliderFocus]->getName());
}

/////// Effects Page
bool EffectsPage::keyPressed(const juce::KeyPress & press)
{
	if (press == 'R')
	{	
		DBG("Redux");
		Effects[0]->grabKeyboardFocus();
	}
	else if (press == 'B')
	{
		DBG("Bitcrush");
		Effects[1]->grabKeyboardFocus();
	}
	if (press == 'D')
	{
		DBG("Delay LFO");
		Effects[2]->grabKeyboardFocus();
	}
	else if (press == 'A')
	{
		DBG("Amplitude");
		Effects[3]->grabKeyboardFocus();
	}
	else if (press == 'C')
	{
		DBG("Cuttoff");
		Effects[4]->grabKeyboardFocus();
	}
	else if (press == 'Q')
	{
		DBG("Flter Q");
		Effects[5]->grabKeyboardFocus();
	}
	else if (press == 'F')
	{
		DBG("Freeze");
		Freeze.grabKeyboardFocus();
		Freeze.triggerClick();
	}
	return false;
}

// Linking all Parameters to Gen Processor
void EffectsPage::sliderValueChanged(juce::Slider* slider)
{	

	if (slider == Effects[0])SliderScaler(slider, 13);	// setting Redux 
	else if(slider == Effects[1]) SliderScaler(slider,1); // Setting Up Bitcrush
	else if (slider == Effects[2]) SliderScaler(slider, 2); // Setting Up Delay LFO
	else if (slider == Effects[3]) SliderScaler(slider, 0); // Setting Up AM
	else if (slider == Effects[4]) SliderScaler(slider, 3); // Setting Up Filter Cut
	else if (slider == Effects[5]) SliderScaler(slider, 4); // Setting Up Filter Q

}

// Scaling Effects Parameters to be normalised range for Gen Parameters and linking to processor
void EffectsPage::SliderScaler(juce::Slider* slider, int GenReferenceNumber)
{	
	// Scaling Slider Value
	float MaxValue = slider->getMaximum();
	float CurrentValue = slider->getValue();
	float Output = CurrentValue / MaxValue;
	slider->grabKeyboardFocus();

	// Linking to Gen Audio Processor through ProcessorRef
	processorRef.setParameter(GenReferenceNumber, Output);
}

// Linking Freeze Command to the ProcessorRef and setting up on/off functionality
void EffectsPage::buttonClicked(juce::Button* Button)
{	
	float FreezeOutput{ 0 };
	if (Button == &Freeze)
	{	
		bool Out = Button->getToggleState();
		if (Out == true)
		{
			Freeze.setButtonText("Frozen");
			FreezeOutput = 1;
			
		}		
		else 
		{	
			FreezeOutput = 0;
			Freeze.setButtonText("Unfrozen");

		}
		processorRef.setParameter(5, FreezeOutput);
	}
}


// 
