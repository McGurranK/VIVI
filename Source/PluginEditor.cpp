/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VIVI_SynthAudioProcessorEditor::VIVI_SynthAudioProcessorEditor (VIVI_SynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p) , Tab(juce::TabbedButtonBar::Orientation::TabsAtTop)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1000, 750);
	Themes(1);						// Initalise Theme Function


	addAndMakeVisible(Tab);
	Tab.addTab("Blank", juce::Colours::hotpink, new Component(), true);

	C74_GENPLUGIN::setparameter(0,9,100,0);
	

	// Going through Slider Vector
	for (auto i = 0; i < Sliders.size(); i++)
	{
		addAndMakeVisible(Sliders[i]);		// Make all Sliders Visible
		Sliders[i]->setValue(0.00);			// Set Default Value
		Sliders[i]->setAccessible(true);	// Accessible Functions are on for all sliders
		Sliders[i]->setLookAndFeel(&OtherLookAndFeel);	// Create look and feel 


		if (i != 6)
		{

			// First Slider Position in row
			if (i != 0) 
			{
				Sliders[i]->setBounds(Sliders[i - 1]->getX() + 150, TopMargin, SliderWidth, SliderHeight);
			}
			
			else
			{
				Sliders[i]->setBounds(20, TopMargin, SliderWidth, SliderHeight);
			}
			// Relative Positions
		   

			Sliders[i]->setSize(200, 200);
			// Oscilator Slider TextBox and Slider
			Sliders[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 200, 30);
			Sliders[i]->setSliderStyle(juce::Slider::SliderStyle::Rotary);
		}
		/*
		// Spread Slider
		else 
		{
			int centreWidth = getWidth() / 2;
			int centreHeight = getHeight() / 2;
			int SpreadWidth{ (getWidth() / 4) * 3 }, SpreadHeight{ 100 };
			Sliders[i]->setSliderStyle(juce::Slider::SliderStyle::LinearBar);
			Sliders[i]->setBounds(20, centreHeight-50, SpreadWidth, SpreadHeight);
			Sliders[i]->setTitle("Spread");
			Sliders[i]->setRange(0.00,4.00);

		}
		*/
		Osc1.setTitle("Oscilator One");
		Osc2.setTitle("Oscilator Two");
		Osc3.setTitle("Oscilator Three"); 		
		Osc4.setTitle("Oscilator Four");
		Osc5.setTitle("Oscilator Five");
		Osc6.setTitle("Oscilator Six");
		

	}

	  
	 
	for (auto j = 0; j < Button.size(); j++)
	{
		addAndMakeVisible(Button[j]);
		Button[j]->setClickingTogglesState(true);
	}

	Button[0]->setBounds(getWidth()-224, TopMargin +SliderHeight+ 50, 200, 200);
	Button[1]->setBounds(getWidth()-224, TopMargin+SliderHeight+350 , 200, 200);
	
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
	Tab.setBounds(getLocalBounds().reduced(20));
}
