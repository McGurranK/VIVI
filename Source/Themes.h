/*
  ==============================================================================

    Themes.h
    Created: 4 Apr 2022 11:31:12am
    Author:  Kristian

  ==============================================================================
*/
#pragma once
#include "juceheader.h""

struct Themes
{
public:
	Themes() 
	{	
		OtherLookAndFeel.setColour(juce::Slider::thumbColourId, juce::Colours::purple);
		OtherLookAndFeel.setColour(juce::Slider::backgroundColourId, juce::Colours::blue);
		OtherLookAndFeel.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::white);
	}

	// Custom Look
	juce::LookAndFeel_V4 OtherLookAndFeel;

};