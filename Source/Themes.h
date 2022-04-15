/*
  ==============================================================================

    Themes.h
    Created: 4 Apr 2022 11:31:12am
    Author:  Kristian

  ==============================================================================
*/
#pragma once
#include "juceheader.h"

struct Themes
{
public:
	// Custom Look
	juce::LookAndFeel_V4 OtherLookAndFeel;
	Themes()
	{	

		OtherLookAndFeel.setColour(juce::Slider::thumbColourId, juce::Colours::purple);
		OtherLookAndFeel.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::white);
		OtherLookAndFeel.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::green);
		OtherLookAndFeel.setColour(juce::Slider::trackColourId, juce::Colours::purple);
		OtherLookAndFeel.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::purple);
		OtherLookAndFeel.setColour(juce::TextButton::buttonOnColourId, juce::Colours::red);
		OtherLookAndFeel.setColour(juce::TextButton::buttonColourId, juce::Colours::green);

	}
	

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Themes)
};