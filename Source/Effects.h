/*
  ==============================================================================

    Effects.h
    Created: 16 Mar 2022 9:40:04am
    Author:  Kristian

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Themes.h"


struct EffectsPage : juce::Component, juce::Button::Listener, Themes,
juce::Slider::Listener
{

	// Constructor
	EffectsPage(VIVI_SynthAudioProcessor& p) : processorRef (p)
	{	

		Theme;
		addAndMakeVisible(Freeze);
	    Freeze.setClickingTogglesState(true);
		Freeze.setBounds(20,(Effects[5]->getY() + 490), 700, 75);
		Freeze.setLookAndFeel(&OtherLookAndFeel);


		for (auto i = 0; i < Effects.capacity(); i++)
		{	
			// Setting up Colours
			Effects[i]->setLookAndFeel(&OtherLookAndFeel);

			// Making Sliders Visible
			addAndMakeVisible(Effects[i]);

			// Accessibility Functionality
			Effects[i]->getAccessibilityHandler();
			Effects[i]->setWantsKeyboardFocus(true);
			Effects[i]->setHasFocusOutline(true);
			Effects[i]->setDescription(EffectsNames[i]);
			Effects[i]->setName(EffectsNames[i]);
			Effects[i]->addListener(this);
			Freeze.addListener(this);


			// Oscilator Slider TextBox and Slider
			Effects[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 200, 30);
			Effects[i]->setSliderStyle(juce::Slider::SliderStyle::Rotary);

			// Labels
			EffectsLabels[i]->setText(EffectsLabelNames[i], juce::NotificationType::dontSendNotification);
			EffectsLabels[i]->setFont(juce::Font(28.0f, juce::Font::bold));
			EffectsLabels[i]->setMinimumHorizontalScale(1);
			EffectsLabels[i]->setColour(juce::Label::textColourId, juce::Colours::lightgreen);
			EffectsLabels[i]->setJustificationType(juce::Justification::centred);
			EffectsLabels[i]->attachToComponent(Effects[i], false);
			EffectsLabels[i]->setBounds(65, 50, 100, 100);
			EffectsLabels[i]->setAccessible(false);

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

		// Initalise all slider Linking to APVTS
		mReduxAttachment = std::make_unique
			<juce::AudioProcessorValueTreeState::SliderAttachment>
			(processorRef.apvts, "ReDux", Redux);
		mBitCurshAttachment = std::make_unique
			<juce::AudioProcessorValueTreeState::SliderAttachment>
			(processorRef.apvts, "Bitcrush", Bitcrush);
		mDelayLFOAttachment = std::make_unique
			<juce::AudioProcessorValueTreeState::SliderAttachment>
			(processorRef.apvts, "DelayLFO",DelayLFO );
		mAMAttachment = std::make_unique
			<juce::AudioProcessorValueTreeState::SliderAttachment>
			(processorRef.apvts, "AM", AM);
		mFilterCutAttachment = std::make_unique
			<juce::AudioProcessorValueTreeState::SliderAttachment>
			(processorRef.apvts, "FilterCutOff", FilterCut);
		mFilterQAttachment = std::make_unique
			<juce::AudioProcessorValueTreeState::SliderAttachment>
			(processorRef.apvts, "FilterQ", FilterQ);
		mFreezeAttachment = std::make_unique
			<juce::AudioProcessorValueTreeState::ButtonAttachment>
			(processorRef.apvts, "Freeze", Freeze);
		
	}
	
	// Destructor
	~EffectsPage()
	{	
		// Clearing vector from memory
		Effects.clear();
		Effects.shrink_to_fit();
		EffectsLabels.clear();
		EffectsLabels.shrink_to_fit();
	}

	// Labels
	void resized()
	{

		for (int i = 0; i < Effects.size(); i++)
		{
			int SliderY = Effects[i]->getY();
			int SliderX = Effects[i]->getX();
			EffectsLabels[i]->setBounds(SliderX + 50, SliderY + 30, 100, 100);

		}
		EffectsPage::sendLookAndFeelChange();
	}

	// Button Listener
	void buttonClicked(juce::Button* Button) override;
	void sliderValueChanged(juce::Slider* sliderThatMoved) override;
	
	Themes Theme;

	// Effects Page
	juce::Slider Redux, Bitcrush, DelayLFO, AM, FilterCut, FilterQ;	   // Declare Sliders
	std::vector<juce::Slider*> Effects =							   // Create Slider Vector
	{ &Redux,&Bitcrush,&DelayLFO, &AM, &FilterCut, &FilterQ };
	// Freeze Button
	juce::TextButton Freeze{ "Freeze" };

private:

	// APVTS Parameter Linking for Effects Page parameters
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>mReduxAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>mBitCurshAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>mDelayLFOAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>mAMAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>mFilterCutAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>mFilterQAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>mFreezeAttachment;


	// Slider Names
	std::array < std::string, 6 > EffectsNames =
	{ "Redux","Bitcrush","Delay LFO","Amplitude Mod","Filter Cuttoff","Filter Q" };

	int SliderWidth{ 200 }, SliderHeight{ 200 }, LeftMargin{ 20 }, TopMargin{ 20 }
	, SliderDistance{ 250 };


	// Parameter Labels
	juce::Label ReduxLabel, BitcrushLabel,
		DelayLFOLabel, AmplitudeLabel, CuttOffLabel,
		QLabel;

	std::vector<juce::Label*> EffectsLabels = { &ReduxLabel, &BitcrushLabel,
		&DelayLFOLabel, &AmplitudeLabel, &CuttOffLabel,
		&QLabel };

	std::array<std::string, 6> EffectsLabelNames =
	{ "Redux","Bit","Delay","AM","Filter","Q" };


	// Processor Reference to link Sliders to plugins
	VIVI_SynthAudioProcessor& processorRef;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EffectsPage)
};