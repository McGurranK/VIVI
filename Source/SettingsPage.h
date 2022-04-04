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

struct SettingsPage : juce::Component, juce::Button::Listener, Themes
{

	// Create button objects, store them, and create name array
	juce::TextButton ThemeOne, ThemeTwo, ThemeThree, ThemeFour;
	std::vector<juce::TextButton*> Theme = { &ThemeOne,&ThemeTwo,&ThemeThree,&ThemeFour };
	std::array<std::string, 4> ThemeNames = { "Theme One","Theme Two","Theme Three","Theme Four" };

	// Buttons dimensions and postion
	int ButtonX{ 250 }, ButtonY{ 250 };
	std::array<int, 4> ButtonWidth = {20,400,20,400};
	std::array<int,4> ButtonHeight = { 50, 50, 300, 300 };

	// Constructor for Button
	SettingsPage()
	{	
		Look;
		for (int i = 0; i < Theme.size(); i++)
		{	
			addAndMakeVisible(Theme[i]);
			Theme[i]->setTitle(ThemeNames[i]);
			Theme[i]->setButtonText(ThemeNames[i]);
			Theme[i]->setName(ThemeNames[i]);
			Theme[i]->setClickingTogglesState(true);
			Theme[i]->setLookAndFeel(&OtherLookAndFeel);
			Theme[i]->setBounds(ButtonWidth[i], ButtonHeight[i], ButtonX, ButtonY);

		}
	
	}

	// Button Listener
	void buttonClicked(juce::Button* Button) override;
	Themes Look;

};

