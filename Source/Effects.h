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

	int SliderWidth{ 300 }, SliderHeight{ 300 }, LeftMargin{ 24 }, TopMargin{ 24 }
	, SliderDistance{ 500 };

	EffectsPage()
	{
		for (auto i = 0; i < Effects.size(); i++)
		{
			addAndMakeVisible(Effects[i]);		// Make all Sliders Visible
			Effects[i]->setValue(0.00);			// Set Default Value
			Effects[i]->setAccessible(true);	// Accessible Functions are on for all sliders

			// Oscilator Slider TextBox and Slider
			Effects[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 200, 30);
			Effects[i]->setSliderStyle(juce::Slider::SliderStyle::Rotary);


			if (i == 0)
			{

				Effects[i]->setBounds(20, TopMargin, SliderWidth, SliderHeight);

			}
			else if (i < 3)
			{
				Effects[i]->setBounds(Effects[i - 1]->getX() + SliderDistance, TopMargin, SliderWidth, SliderHeight);

			}

			else
			{
				if (i == 3)
				{
					Effects[i]->setBounds(20, TopMargin + 300, SliderWidth, SliderHeight);
				}
				else
				{
					Effects[i]->setBounds(Effects[i - 1]->getX() + SliderDistance, TopMargin + 300, SliderWidth, SliderHeight);
				}

			}

		}

	}
	
	// Destructor
	~EffectsPage()
	{	
		
		Effects.clear();
		Effects.shrink_to_fit();

	}

};

