/*
  ==============================================================================

	Effects.h
	Created: 16 Mar 2022 9:40:04am
	Author:  Kristian

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class VIVI_SynthAudioProcessorEditor;

struct OscillatorPage : juce::Component
{

public:

	// Oscillator Sliders and Vector Storage
	juce::Slider Osc1, Osc2, Osc3, Osc4, Osc5, Osc6;
	std::vector<juce::Slider*> Sliders = { &Osc1,&Osc2,&Osc3,&Osc4,&Osc5,&Osc6 };

	// Array with all slider names to step through
	std::array < std::string, 6 > OscilllatorNames = 
	{ "Oscillator One",
	  "Oscillator Two",
	  "Oscilator Three",
	  "Oscillator Four",
	  "Oscillator Five",
	  "Oscillator Six" };


	// Initalising Slider variables
	int SliderWidth{ 250 }, SliderHeight{ 250 }, LeftMargin{ 20 }, TopMargin{ 20 }
	, SliderDistance{ 300 };


	// Constructor 
	OscillatorPage()
	{	
		
		// Loop through vector of objects to seteverything up
		for (auto i = 0; i < Sliders.capacity(); i++)
		{	

			addAndMakeVisible(Sliders[i]);		// Make all Sliders Visible
			Sliders[i]->setValue(0.00);			// Set Default Value
			Sliders[i]->setTitle(OscilllatorNames[i]);	// Set all names of variables

			// Oscilator Slider TextBox and Slider
			Sliders[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 200, 30);    // Text Box Setup
			Sliders[i]->setSliderStyle(juce::Slider::SliderStyle::Rotary);              // Set Slider style
			Sliders[i]->setWantsKeyboardFocus(true);   // Set focus for accessibility


			// Slider Layout

			// Slider One Position
			if (i == 0)
				Sliders[i]->setBounds(20, TopMargin, SliderWidth, SliderHeight);

			// Slider Two and three
			else if (i < 3)
				Sliders[i]->setBounds(Sliders[i - 1]->getX() + SliderDistance, TopMargin, SliderWidth, SliderHeight);

			// Sliders 4-6 Position
			else
				if (i == 3)
					Sliders[i]->setBounds(20, TopMargin + 250, SliderWidth, SliderHeight);
				else
					Sliders[i]->setBounds(Sliders[i - 1]->getX() + SliderDistance, TopMargin + 250, SliderWidth, SliderHeight);

		}

	}

	// Destructor
	~OscillatorPage(){}

};
