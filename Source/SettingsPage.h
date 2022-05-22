/*
  ==============================================================================

    SettingsPage.h
    Created: 4 Apr 2022 10:21:29am
    Author:  Kristian

  ==============================================================================
*/

#pragma once
#include "juceheader.h"
#include "Themes.h"

struct SettingsPage : juce::Component, Themes
	//juce::Button::Listener
{

	Themes Themes;
	// Create button objects, store them, and create name array
	juce::TextButton ThemeOne, ThemeTwo, ThemeThree, ThemeFour;
	std::vector<juce::TextButton*> ThemeContainer = { &ThemeOne,&ThemeTwo,&ThemeThree,&ThemeFour };
	std::array<std::string, 4> ThemeNames = { "Theme One","Theme Two","Theme Three","Theme Four" };

	// Buttons dimensions and postion
	int ButtonX{ 250 }, ButtonY{ 250 };
	std::array<int, 4> ButtonWidth = {20,400,20,400};
	std::array<int,4> ButtonHeight = { 50, 50, 300, 300 };

	// Constructor for Button
	SettingsPage()
	{	
		Themes;
		for (int i = 0; i < ThemeContainer.size(); i++)
		{	
			addAndMakeVisible(ThemeContainer[i]);
			ThemeContainer[i]->setTitle(ThemeNames[i]);
			ThemeContainer[i]->setButtonText(ThemeNames[i]);
			ThemeContainer[i]->setName(ThemeNames[i]);
			ThemeContainer[i]->setClickingTogglesState(true);
			ThemeContainer[i]->setLookAndFeel(&OtherLookAndFeel);
			ThemeContainer[i]->setBounds(ButtonWidth[i], ButtonHeight[i], ButtonX, ButtonY);
			//ThemeContainer[i]->addListener(this);
		}
	
	}
	~SettingsPage()
	{
		ThemeContainer.clear();
		ThemeContainer.shrink_to_fit();
	}

	// Button Listener
	// void buttonClicked(juce::Button* Button) override;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SettingsPage)
};

