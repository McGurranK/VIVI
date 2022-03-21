/*
  ==============================================================================

    Effects.h
    Created: 16 Mar 2022 9:40:04am
    Author:  Kristian

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


struct EffectsPage : juce::Component
{
	// Oscillator Sliders and Vector Storage

// Effects Page
	juce::Slider Redux, Bitcrush, DelayLFO, AM, FilterCut, FilterQ;	   // Declare Sliders
	std::vector<juce::Slider*> Effects =							   // Create Slider Vector
	{ &Redux,&Bitcrush,&DelayLFO, &AM, &FilterCut, &FilterQ };

	// Slider Titles
		std::array < std::string, 6 > EffectsNames =
	{ "Redux",
	  "Bitcrush",
	  "Delay LFO",
	  "Amplitude Mod",
	  "Filter Cuttoff",
	  "Filter Q"};

	
	
	// Freeze Button
	juce::TextButton Freeze{ "Freeze" };


	int SliderWidth{ 200 }, SliderHeight{ 200 }, LeftMargin{ 20 }, TopMargin{ 20 }
	, SliderDistance{ 250 };


	// Constructor
	EffectsPage()
	{	
		addAndMakeVisible(Freeze);
	    Freeze.setClickingTogglesState(true);
		Freeze.setBounds(20,(Effects[5]->getY() + 490), 700, 75);
		Effects[1]->setRange(0.0,16.0,0.1);
		Effects[2]->setRange(0.0,200.0,0.1);
		Effects[3]->setRange(0.0,200.0,0.1);
		Effects[4]->setRange(0,20000,1);
		Effects[5]->setRange(0,1,0.01);


		for (auto i = 0; i < Effects.capacity(); i++)
		{
			addAndMakeVisible(Effects[i]);		// Make all Sliders Visible
			Effects[i]->setValue(0.00);			// Set Default Value
			Effects[i]->setAccessible(true);	// Accessible Functions are on for all sliders
			Effects[i]->setWantsKeyboardFocus(true);
			Effects[i]->setTitle(EffectsNames[i]);

			// Oscilator Slider TextBox and Slider
			Effects[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 200, 30);
			Effects[i]->setSliderStyle(juce::Slider::SliderStyle::Rotary);

			// Freeze



			// Slider One Position
			if (i == 0)
				Effects[i]->setBounds(20, TopMargin, SliderWidth, SliderHeight);

			// Slider Two and three
			else if (i < 3)
				Effects[i]->setBounds(Effects[i - 1]->getX() + SliderDistance, TopMargin, SliderWidth, SliderHeight);

			// Sliders 4-6 Position
			else
				if (i == 3)
					Effects[i]->setBounds(20, TopMargin + 220, SliderWidth, SliderHeight);
				else
					Effects[i]->setBounds(Effects[i - 1]->getX() + SliderDistance, TopMargin + 220, SliderWidth, SliderHeight);

		}

	}
	
	// Destructor
	~EffectsPage()
	{	
		
		Effects.clear();
		Effects.shrink_to_fit();

	}

};

