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

typedef struct OscillatorPage: juce::Component,
	juce::Slider::Listener,Themes
{
public:
	Themes Theme;

	int GrabFocus{ 0 };

	// Oscillator Sliders and Vector Storage
	juce::Slider Osc1, Osc2, Osc3, Osc4, Osc5, Osc6, Spread;
	std::vector<juce::Slider*> Sliders = { &Osc1,&Osc2,&Osc3,&Osc4,&Osc5,&Osc6, &Spread };

	// Constructor method
	OscillatorPage(VIVI_SynthAudioProcessor &p): ProcessorRef(p)
	{	
		Theme;

		// Loop through vector of objects to seteverything up
		for (auto i = 0; i < Sliders.capacity(); i++)
		{	
			// Making components visible
			addAndMakeVisible(OscLabels[i]);
			addAndMakeVisible(Sliders[i]);

			// Keyboard Functionality
			Sliders[i]->setWantsKeyboardFocus(true); 
			Sliders[i]->setHasFocusOutline(true);

			// Accessibility
			Sliders[i]->getAccessibilityHandler();


			// Set Default Value
			Sliders[i]->addListener(this);

			// Look and text
			Sliders[i]->setTitle(OscilllatorNames[i]);	// Set all names of variables
			Sliders[i]->setLookAndFeel(&OtherLookAndFeel);

			//Label Setup
			OscLabels[i]->setText(OscillatorLabelNames[i], juce::NotificationType::dontSendNotification);
			OscLabels[i]->setFont(juce::Font(72.0f, juce::Font::bold));
			OscLabels[i]->setMinimumHorizontalScale(1);
			OscLabels[i]->setColour(juce::Label::textColourId, juce::Colours::lightgreen);
			OscLabels[i]->setJustificationType(juce::Justification::centred);
			OscLabels[i]->attachToComponent(Sliders[i], false);
			OscLabels[i]->setBounds(65, 50, 100, 100);
			OscLabels[i]->setAccessible(false);

			// Slider Layout
			if (i < 6) {
			Sliders[i]->setRange(-100, 6, 1);
			Sliders[i]->setSliderStyle(juce::Slider::SliderStyle::Rotary);              // Set Slider style
			Sliders[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 200, 30);    // Text Box Setup
			

			// Positional Information
				if (i == 0)
					Sliders[i]->setBounds(20, TopMargin, SliderWidth, SliderHeight);

				// Slider Two and three
				else if (i < 3)
					Sliders[i]->setBounds(Sliders[i - 1]->getX() + SliderDistance, TopMargin, SliderWidth, SliderHeight);

				// Sliders 4-6 Position
				else
					if (i == 3)
						Sliders[i]->setBounds(20, TopMargin + 220, SliderWidth, SliderHeight);
					else
						Sliders[i]->setBounds(Sliders[i - 1]->getX() + SliderDistance, TopMargin + 220, SliderWidth, SliderHeight);

			}

			else
			{
				Sliders[i]->setSliderStyle(juce::Slider::SliderStyle::LinearBar);
				Sliders[i]->setBounds(20, Sliders[3]->getY() + SliderHeight + 50, 700, 75);
				Sliders[i]->setRange(0, 4, 0.01);
				Sliders[i]->setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 30);    // Text Box Setup
			}
		}

		// Initalise all slider Linking to APVTS
		mOscAttachment = std::make_unique
			<juce::AudioProcessorValueTreeState::SliderAttachment>
			(ProcessorRef.apvts,"OscOneVol",Osc1);
		mOscTwoAttachment = std::make_unique
			<juce::AudioProcessorValueTreeState::SliderAttachment>
			(ProcessorRef.apvts, "OscTwoVol", Osc2);
		mOscThreeAttachment = std::make_unique
			<juce::AudioProcessorValueTreeState::SliderAttachment>
			(ProcessorRef.apvts, "OscThreeVol", Osc3);
		mOscFourAttachment = std::make_unique
			<juce::AudioProcessorValueTreeState::SliderAttachment>
			(ProcessorRef.apvts, "OscFourVol", Osc4);
		mOscFiveAttachment = std::make_unique
			<juce::AudioProcessorValueTreeState::SliderAttachment>
			(ProcessorRef.apvts, "OscFiveVol", Osc5);
		mOscSixAttachment = std::make_unique
			<juce::AudioProcessorValueTreeState::SliderAttachment>
			(ProcessorRef.apvts, "OscSixVol", Osc6);
		SpreadAttachment = std::make_unique
			<juce::AudioProcessorValueTreeState::SliderAttachment>
			(ProcessorRef.apvts, "Spread", Spread);
	}

	// Destructor
	~OscillatorPage(){}

	// Positioning Labels for componenets
	void resized()
	{
		for (int i = 0; i < Sliders.size(); i++)
		{	
			float SliderY = Sliders[i]->getY();
			float SliderX = Sliders[i]->getX();
			if (i < 6) 
			{

				OscLabels[i]->setBounds(SliderX + 50, SliderY + 30, 100, 100);
			}
			else
			{	

				OscLabels[i]->setBounds(SliderX , SliderY , 100, 100);
			}
		}
	}

	// Grab foucus and debugging with slider listener
	void sliderValueChanged(juce::Slider* sliderThatMoved) override;
	void SliderFocus(int SliderFocus);
	void ValueChangedFocus(int GenRef, juce::Slider* SliderRef);
	

	// Keyboard implementation
	bool OscillatorPage::keyPressed(const juce::KeyPress & press) override;
	juce::KeyPress key;


private:

	// Initalising Slider variables
	int SliderWidth{ 200 }, SliderHeight{ 200 }, LeftMargin{ 20 }, TopMargin{ 20 }
	, SliderDistance{ 250 };

	// APVTS Parameter Linking for Oscillator Page parameters
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>mOscAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>mOscTwoAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>mOscThreeAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>mOscFourAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>mOscFiveAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>mOscSixAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>SpreadAttachment;


	// Array with all slider names to step through
	std::array < std::string, 7 > OscilllatorNames =
	{
	  "Oscillator One","Oscillator Two","Oscilator Three","Oscillator Four",
	  "Oscillator Five","Oscillator Six","Spread"
	};

	// Slider Labels and labe text
	juce::Label OscillatorOneLabel, OscillatorTwoLabel,
		OscillatorThreeLabel, OscillatorFourLabel, OscillatorFiveLabel,
		OscillatorSixLabel, SpreadLabel;

	std::vector<juce::Label*> OscLabels = { &OscillatorOneLabel, &OscillatorTwoLabel,
		&OscillatorThreeLabel, &OscillatorFourLabel, &OscillatorFiveLabel,
		&OscillatorSixLabel, &SpreadLabel };

	std::array<std::string, 7> OscillatorLabelNames =
	{ "1","2","3","4","5","6","Spread" };

	std::array<int, 7> GenReferenceNumbers = { 9, 12, 11, 8, 7, 10, 14 };



	VIVI_SynthAudioProcessor& ProcessorRef;
	
} OscRef;