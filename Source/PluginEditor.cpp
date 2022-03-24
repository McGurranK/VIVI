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
		float VolumeSlider = MainControls[0]->getValue();
		processor.setParameter(15, VolumeSlider);
	}

	// Gate Slider Hook
	else if (sliderThatMoved == MainControls[0])
	{
		float GateSlider = MainControls[1]->getValue();
		processor.setParameter(6, GateSlider);
		
	}


}
	/*
	else if (sliderThatMoved == &Oscillators->Osc2)
	{
		float OscTwoSlider = Oscillators->Osc2.getValue();
		processor.setParameter(12,OscTwoSlider);
	}
	else if (sliderThatMoved == &Oscillators->Osc3)
	{
		float OscThreeSlider = Oscillators->Osc1.getValue();
		processor.setParameter(11, OscThreeSlider);

	}
	else if (sliderThatMoved == &Oscillators->Osc4)
	{
		float OscFourSlider = Oscillators->Osc4.getValue();
		processor.setParameter(8, OscFourSlider);
	}
	else if (sliderThatMoved == &Oscillators->Osc5)
	{
		float OscFiveSlider = Oscillators->Osc5.getValue();
		processor.setParameter(7, OscFiveSlider);
	}
	else if (sliderThatMoved == &Oscillators->Osc6)
	{
		float OscSixSlider = Oscillators->Osc6.getValue();
		processor.setParameter(10, OscSixSlider);
	}
	
}
/*
Implement toggle for mute and freeze
void VIVI_SynthAudioProcessorEditor::ButtonPressed(juce::TextButton* toggledMute)
{
	if (toggledMute == Mute.getToggleStateValue())
	{

	}

}
*/

// Hooking up oscillator Page (Not optimium but works) [Fix scaling in Gen~]
void OscillatorPage::sliderValueChanged(juce::Slider* slider)
{	
	// Oscillator One
	if (slider == Sliders[0])
	{
		float OscillatorOneValue = Sliders[0]->getValue();
		ProcessorLink.setParameter(9, OscillatorOneValue);
	}
	// Selecting Oscillator Two
	else if (slider == Sliders[1])
	{
		float OscillatorTwoValue = Sliders[1]->getValue();
		ProcessorLink.setParameter(12, OscillatorTwoValue);

	}
	// Selecting Oscillator Two
	else if (slider == Sliders[2])
	{
		float OscillatorThreeValue = Sliders[2]->getValue();
		ProcessorLink.setParameter(11, OscillatorThreeValue);

	}
	// Slecting Oscillator Three
	else if (slider == Sliders[3])
	{
		float OscillatorFourValue = Sliders[3]->getValue();
		ProcessorLink.setParameter(8, OscillatorFourValue);

	}
	// Selecting Oscillator Four
	else if (slider == Sliders[4])
	{
		float OscillatorFiveValue = Sliders[4]->getValue();
		ProcessorLink.setParameter(7, OscillatorFiveValue);

	}
	// Selecting Oscillator Six
	else if (slider == Sliders[5])
	{
		float OscillatorSixValue = Sliders[5]->getValue();
		ProcessorLink.setParameter(10, OscillatorSixValue);

	}
	// Selecting Spreader
	else if (slider == Sliders[6])
	{
		float SpreaderSliderValue = Sliders[6]->getValue();
		ProcessorLink.setParameter(14, SpreaderSliderValue);
	}

}

void VIVI_SynthAudioProcessorEditor::resized()
{
	
	// Border for Tab Interface
	Tab.setBounds(getLocalBounds().reduced(TabIndent));
	Tab.setTabBarDepth(TabDepth);

}


