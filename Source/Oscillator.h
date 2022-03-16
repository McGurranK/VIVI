/*
  ==============================================================================

	Effects.h
	Created: 16 Mar 2022 9:40:04am
	Author:  Kristian

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

struct OscillatorPage : juce::Component
{
	// Oscillator Sliders and Vector Storage

	juce::Slider Osc1, Osc2, Osc3, Osc4, Osc5, Osc6;
	std::vector<juce::Slider*> Sliders = { &Osc1,&Osc2,&Osc3,&Osc4,&Osc5,&Osc6 };

	int SliderWidth{ 300 }, SliderHeight{ 300 }, LeftMargin{ 24 }, TopMargin{ 24 }
	, SliderDistance{ 500 };

	OscillatorPage()
	{
		for (auto i = 0; i < Sliders.size(); i++)
		{
			addAndMakeVisible(Sliders[i]);		// Make all Sliders Visible
			Sliders[i]->setValue(0.00);			// Set Default Value
			Sliders[i]->setAccessible(true);	// Accessible Functions are on for all sliders

			// Oscilator Slider TextBox and Slider
			Sliders[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 200, 30);
			Sliders[i]->setSliderStyle(juce::Slider::SliderStyle::Rotary);


			if (i == 0)
			{

				Sliders[i]->setBounds(20, TopMargin, SliderWidth, SliderHeight);

			}
			else if (i < 3)
			{
				Sliders[i]->setBounds(Sliders[i - 1]->getX() + SliderDistance, TopMargin, SliderWidth, SliderHeight);

			}

			else
			{
				if (i == 3)
				{
					Sliders[i]->setBounds(20, TopMargin + 300, SliderWidth, SliderHeight);
				}
				else
				{
					Sliders[i]->setBounds(Sliders[i - 1]->getX() + SliderDistance, TopMargin + 300, SliderWidth, SliderHeight);
				}

			}

		}

	}

};
