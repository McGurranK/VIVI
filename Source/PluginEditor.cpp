// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Oscillator.h"
#include "Effects.h"
#include "SettingsPage.h"
#include <memory>
using namespace std;


//==============================================================================
// Constructor for the editor page
VIVI_SynthAudioProcessorEditor::VIVI_SynthAudioProcessorEditor 
(VIVI_SynthAudioProcessor& p, Themes& T)
    : AudioProcessorEditor (&p), audioProcessor (p)  ,
	Tab (juce::TabbedButtonBar::Orientation::TabsAtTop), Theme(T)
{
	setSize(1000, 700);      // Window Size

	// Setting up object dimenstions
	int windowWidth{ getWidth() }, WindowTenth{windowWidth/10};
	float ButtonOneX{ getWidth() - TabIndent - ButtonOneD };
	float ButtonTwoY{TabIndent - 1};

	// Setting up tab functionality
	addAndMakeVisible(Tab);        // Add to screen
	Tab.setAccessible(true);       // This is set to false by default
	Tab.setHasFocusOutline(true);  // Provides a yellow outline when selected
	Tab.setWantsKeyboardFocus(true); // Allows focus to be past to this object
	Tab.setDescription("Oscillator and Effects Tabs"); // Description for screen reader

	// Adding Oscillator and effects headers to tabbed interface
	Tab.addTab("Oscillator Page", juce::Colours::linen,OscReference, true);
	Tab.addTab("Effects Page", juce::Colours::purple, EffectsReference, true);

	// Coded out for testing as not enough time to implement well
	// Tab.addTab("Settings Page", juce::Colours::purple,SettingsReference, true);


	// Looping through MainControls vector that has the volume and Gate sliders
	// Saves having to call the same function twice
	for (auto j = 0; j < MainControls.size(); j++)
	{
		// Visible
		addAndMakeVisible(MainControls[j]);
		// Setting Style
		MainControls[j]->setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
		MainControls[j]->setTextBoxStyle(juce::Slider::TextBoxBelow,false,500,500);

		// Accessibility
		MainControls[j]->setWantsKeyboardFocus(true); 
		MainControls[j]->setAccessible(true); 
		MainControls[j]->addListener(this); // Only used for audible feedback for tab
		MainControls[j]->setHasFocusOutline(true);

		// Colour, name, and title
		MainControls[j]->setColour(juce::Slider::trackColourId,juce::Colours::purple);
		MainControls[j]->setColour(juce::Slider::textBoxTextColourId,juce::Colours::white);
		MainControls[j]->setColour(juce::Slider::textBoxHighlightColourId,juce::Colours::purple);
		MainControls[j]->setName(MainControlsLabelText[j]);
		MainControls[j]->setTitle(MainControlsLabelText[j]);
		
		// Setting Up Label
		MainControlLabels[j]->attachToComponent(MainControls[j], false);
		MainControlLabels[j]->setFont(juce::Font(42.0f, juce::Font::bold));
		MainControlLabels[j]->setText(MainControlsLabelText[j], juce::NotificationType::dontSendNotification);
		MainControlLabels[j]->setColour(juce::Label::textColourId, juce::Colours::white);
		MainControlLabels[j]->setJustificationType(juce::Justification::centredTop);
		MainControlLabels[j]->setBounds(65, 50, 100, 100);
		MainControlLabels[j]->setAccessible(false);
	}

	// Position for gate and volume controls
	MainControls[0]->setBounds((windowWidth)-((windowWidth/5)*1.25),(int)mainControlY ,(int)mainControlWidth,(int) mainControlHeight);
	MainControls[1]->setBounds(MainControls[0]->getX()+WindowTenth+20,(int)mainControlY ,(int)mainControlWidth,(int) mainControlHeight);
	
	// Mute Parameter (Put in for safety in testing incase of feedback)
	/*
	addAndMakeVisible(Mute);
	Mute.setClickingTogglesState(true);
	Mute.setBounds((int)ButtonOneX,(int) ButtonTwoY,(int) ButtonOneD, (int)TabDepth);
	Mute.addListener(this);
	*/
	// Linking to the apvts for controlling the instrument
	mVolAttachment = std::make_unique
		<juce::AudioProcessorValueTreeState::SliderAttachment>
		(audioProcessor.apvts, "Volume", Volume);
	mGateAttachment = std::make_unique
		<juce::AudioProcessorValueTreeState::SliderAttachment>
		(audioProcessor.apvts, "GateLevel", Gate);
}

// Clearing Memory allocation
VIVI_SynthAudioProcessorEditor::~VIVI_SynthAudioProcessorEditor()
{	
	MainControls.clear();
	MainControlLabels.clear();
	MainControls.shrink_to_fit();
	MainControlLabels.shrink_to_fit();

	juce::LookAndFeel::setDefaultLookAndFeel(nullptr);

	delete OscReference;
	delete EffectsReference;
	delete SettingsReference;

}

// ==============================================================================
void VIVI_SynthAudioProcessorEditor::paint(juce::Graphics& g)
{
	g.fillAll(juce::Colours::purple);

	for (int i = 0; i < Tab.getNumTabs(); i++)
		Tab.setTabBackgroundColour(i, juce::Colours::black);


	// Grabs  focus when window is open
	// VIVI_SynthAudioProcessorEditor::grabKeyboardFocus();
}

// Key press listener
bool VIVI_SynthAudioProcessorEditor::keyPressed(const juce::KeyPress & press)
{
	// Main Navigation and Control
	if (press == 'V') MainControls[0]->grabKeyboardFocus();
	else if (press == 'G') MainControls[1]->grabKeyboardFocus();
	else if (press == 'M') Mute.grabKeyboardFocus();
	else if (press == 'O') Tab.setCurrentTabIndex(0);
	else if (press == 'E') Tab.setCurrentTabIndex(1);
	// else if (press == 'L') Tab.setCurrentTabIndex(2);

	// Oscillator Page
	else if (press == ',')KeyboardCommandsForPages(0,0);
	else if (press == '.') KeyboardCommandsForPages(0, 1);
	else if (press == '/') KeyboardCommandsForPages(0, 2);
	else if (press == ';') KeyboardCommandsForPages(0, 3);
	else if (press == '[') KeyboardCommandsForPages(0, 4);
	else if (press == '#') KeyboardCommandsForPages(0, 5);
	else if (press == 'S') KeyboardCommandsForPages(0, 6);

	// Effects Page
	if (press == 'R')	   KeyboardCommandsForPages(1, 0);
	else if (press == 'B') KeyboardCommandsForPages(1, 1);
	else if (press == 'D') KeyboardCommandsForPages(1, 2);
	else if (press == 'A') KeyboardCommandsForPages(1, 3);
	else if (press == 'C') KeyboardCommandsForPages(1, 4);
	else if (press == 'Q') KeyboardCommandsForPages(1, 5);
	else if (press == 'F') 
	{ 
		Tab.setCurrentTabIndex(1);
		Tab.grabKeyboardFocus();
		EffectsReference->Freeze.grabKeyboardFocus();
		EffectsReference->Freeze.triggerClick();
	}

	// Increasing and decreasing value with keys/ Up and Down
	else if (press == juce::KeyPress::rightKey)KeyboardControl(true);
	else if (press == juce::KeyPress::leftKey)KeyboardControl(false);
	else if (press == juce::KeyPress::upKey) ArrowTraverser(true);
	else if (press == juce::KeyPress::downKey) ArrowTraverser(false);

	return 0;
}

void VIVI_SynthAudioProcessorEditor::KeyboardControl(bool NegOrPlus)
{
	int currentTab = Tab.getCurrentTabIndex();

	switch (currentTab)
	{
	case 0:
		// Used to add an amount to the selected parameter.
		if (NegOrPlus) {
			for (int i = 0; i < OscSize; i++)
			{
				Name = OscReference->Sliders[i]->getName();
				Focus = OscReference->Sliders[i]->getCurrentlyFocusedComponent()->getName();

				VolumeMain = MainControls[0]->getName();
				VolumeFocusMain = MainControls[0]->getCurrentlyFocusedComponent()->getName();
				GateMain = MainControls[1]->getName();
				GateFocusMain = MainControls[1]->getCurrentlyFocusedComponent()->getName();
				if (Name == Focus)
				{
					OscValue = OscReference->Sliders[i]->getValue();

					if (Name == "Spread")
					{
						NewValue = OscValue + 0.05;
						OscReference->Sliders[i]->setValue(NewValue);
					}
					else
					{
						NewValue = OscValue + 1.0;
						OscReference->Sliders[i]->setValue(NewValue);
					}

					break;
				}
				else if (VolumeMain == VolumeFocusMain)
				{
					MainComponentSelect(0, false);
					break;
				}
				else if (GateMain == GateFocusMain)
				{
					MainComponentSelect(1, false);
					break;
				}

			}
		}
		// Used to minus off the selected object
		else
		{
			for (int i = 0; i < OscSize; i++)
			{

				Name = OscReference->Sliders[i]->getName();
				Focus = OscReference->Sliders[i]->getCurrentlyFocusedComponent()->getName();
				VolumeMain = MainControls[0]->getName();
				VolumeFocusMain = MainControls[0]->getCurrentlyFocusedComponent()->getName();
				GateMain = MainControls[1]->getName();
				GateFocusMain = MainControls[1]->getCurrentlyFocusedComponent()->getName();

				if (Name == Focus)
				{
					OscValue = OscReference->Sliders[i]->getValue();
					if (Name == "Spread")
					{
						NewValue = OscValue - 0.05;
						OscReference->Sliders[i]->setValue(NewValue);
					}
					else
					{
						NewValue = OscValue - 1.0;
						OscReference->Sliders[i]->setValue(NewValue);
					}
					break;
				}
				else if (VolumeMain == VolumeFocusMain)
				{
					MainComponentSelect(0, true);
					break;
				}
				else if (GateMain == GateFocusMain)
				{
					MainComponentSelect(1, true);
					break;
				}

			}
		}
		break;


	case 1:
		// Effects page adding value for selected component
		if (NegOrPlus) {
			for (int i = 0; i < EffectsReference->Effects.size(); i++)
			{

				Name = EffectsReference->Effects[i]->getName();
				Focus = EffectsReference->Effects[i]->getCurrentlyFocusedComponent()->getName();
				VolumeMain = MainControls[0]->getName();
				VolumeFocusMain = MainControls[0]->getCurrentlyFocusedComponent()->getName();
				GateMain = MainControls[1]->getName();
				GateFocusMain = MainControls[1]->getCurrentlyFocusedComponent()->getName();

				if (Name == Focus)
				{

					Effects = EffectsReference->Effects[i]->getValue();

					if (Focus == "Delay LFO" || Focus == "Amplitude Mod")
					{
						NewValue = Effects + 1;
						EffectsReference->Effects[i]->setValue(NewValue);
						break;
					}
					else if (Focus == "Redux" || Focus == "Filter Q")
					{
						NewValue = Effects + 0.01;
						EffectsReference->Effects[i]->setValue(NewValue);
						break;
					}
					else if (Focus == "Filter Cuttoff")
					{
						NewValue = Effects + 50.0;
						EffectsReference->Effects[i]->setValue(NewValue);
						break;
					}
					else if (Name == "Bitcrush")
					{
						NewValue = Effects + 0.5;
						EffectsReference->Effects[i]->setValue(NewValue);
						break;
					}

					break;
				}					
				else if (VolumeMain == VolumeFocusMain)
				{
					MainComponentSelect(0, false);
					break;
				}
				else if (GateMain == GateFocusMain)
				{
					MainComponentSelect(1, false);
					break;
				}
			}
		}
		// Effects Page minus
		else
		{
			for (int i = 0; i < EffectsReference->Effects.size(); i++)
			{

				Name = EffectsReference->Effects[i]->getName();
				Focus = EffectsReference->Effects[i]->getCurrentlyFocusedComponent()->getName();
				VolumeMain = MainControls[0]->getName();
				VolumeFocusMain = MainControls[0]->getCurrentlyFocusedComponent()->getName();
				GateMain = MainControls[1]->getName();
				GateFocusMain = MainControls[1]->getCurrentlyFocusedComponent()->getName();

				if (Name == Focus) {

					Effects = EffectsReference->Effects[i]->getValue();

					if (Focus == "Delay LFO" || Focus == "Amplitude Mod")
					{
						NewValue = Effects - 1;
						EffectsReference->Effects[i]->setValue(NewValue);
						break;
					}
					else if (Focus == "Redux" || Focus == "Filter Q")
					{
						NewValue = Effects - 0.01;
						EffectsReference->Effects[i]->setValue(NewValue);
						break;
					}
					else if (Focus == "Filter Cuttoff")
					{
					NewValue = Effects - 50.0;
					EffectsReference->Effects[i]->setValue(NewValue);
					break;
					}
					else if (Name == "Bitcrush")
					{
					NewValue = Effects - 0.5;
					EffectsReference->Effects[i]->setValue(NewValue);
					break;
					}

				break;

				}
				// If the volume object has focus call this function
				else if (VolumeMain == VolumeFocusMain)
				{
					MainComponentSelect(0, true);
					break;
				}
				// If the Gate object has focus call this function
				else if (GateMain == GateFocusMain)
				{
					MainComponentSelect(1, true);
					break;
				}
			}
		}
		break;
	}
}

// This function is not optimised and could make a function call as an alternative
void VIVI_SynthAudioProcessorEditor::ArrowTraverser(bool UpDown)
{
	// What tab is the user currently on
	int currentTab = Tab.getCurrentTabIndex();
	
	switch (currentTab)
	{
	case 0:
		// If upbutton pressed
		if (UpDown) {
			for (int i = 0; i < OscReference->Sliders.size(); i++)
			{
				// Looping through names to see which is pressed
				NameOsc = OscReference->Sliders[i]->getName();
				FocusOsc = OscReference->Sliders[i]->getCurrentlyFocusedComponent()->getName();
				
				// Oscillator and spread Sliders Focus
				if (NameOsc == FocusOsc)
				{
					if (i < 6) OscReference->Sliders[i + 1]->grabKeyboardFocus();
					else MainControls[0]->grabKeyboardFocus();
					break;
				}
				// Main Sliders Focus
				else if (VolumeMain == VolumeFocusMain)
				{
					MainControls[1]->grabKeyboardFocus();
					break;
				}
				else if (GateMain == GateFocusMain)
				{
					OscReference->Sliders[0]->grabKeyboardFocus();
					break;
				}				
			}
			break;
		}

		// If down arrow pressed
		else
		{
			for (int i = 0; i < OscReference->Sliders.size(); i++)
			{
				
				NameOsc = OscReference->Sliders[i]->getName();
				FocusOsc = OscReference->Sliders[i]->getCurrentlyFocusedComponent()->getName();
				VolumeMain = MainControls[0]->getName();
				VolumeFocusMain = MainControls[0]->getCurrentlyFocusedComponent()->getName();
				GateMain = MainControls[1]->getName();
				GateFocusMain = MainControls[1]->getCurrentlyFocusedComponent()->getName();
				if (NameOsc == FocusOsc)
				{
					if (i != 0)
					{
						OscReference->Sliders[i - 1]->grabKeyboardFocus();
						break;
					}
					else
					{
						MainControls[1]->grabKeyboardFocus();
						break;
					}
					break;
				}
				else if (GateMain == GateFocusMain)
				{
					MainControls[0]->grabKeyboardFocus();
					break;
				}
				else if (VolumeMain == VolumeFocusMain)
				{
					OscReference->Sliders[6]->grabKeyboardFocus();
					break;
				}
				
			}
			break;
		}

	// Effects Page references
	case 1:

		// If up button pressed
		if (UpDown) {
			for (int i = 0; i < EffectsReference->Effects.size(); i++)
			{
				// Main effects page references
				NameEffects = EffectsReference->Effects[i]->getName();
				FocusEffects = EffectsReference->Effects[i]->getCurrentlyFocusedComponent()->getName();

				// Main Freeze Controls
				FreezeEffects = EffectsReference->Freeze.getName();
				FreezeFocusEffects = EffectsReference->Freeze.getCurrentlyFocusedComponent()->getName();
				
				// Volume and Gate Controls
				VolumeMain = MainControls[0]->getName();
				VolumeFocusMain = MainControls[0]->getCurrentlyFocusedComponent()->getName();
				GateMain = MainControls[1]->getName();
				GateFocusMain = MainControls[1]->getCurrentlyFocusedComponent()->getName();

				// Rotating through effects and main components.
				if (NameEffects == FocusEffects)
				{
					if (i < 5)
					{
						EffectsReference->Effects[i + 1]->grabKeyboardFocus();
					}
					else
					{
						EffectsReference->Freeze.grabKeyboardFocus();
					}
					break;
				}
				else if (FreezeEffects == FreezeFocusEffects)
				{
					MainControls[0]->grabKeyboardFocus();
					break;
				}
				else if (VolumeMain == VolumeFocusMain)
				{
					MainControls[1]->grabKeyboardFocus();
					break;
				}
				else if (GateMain == GateFocusMain)
				{
					EffectsReference->Effects[0]->grabKeyboardFocus();
					break;
				}
				

			}
			break;
		}
		// Down arrow reverse through list of components and give focus
		else
		{
			
			for (int i = 0; i < EffectsReference->Effects.size(); i++)
			{
				
				NameEffects = EffectsReference->Effects[i]->getName();
				FocusEffects = EffectsReference->Effects[i]->getCurrentlyFocusedComponent()->getName();
				FreezeEffects = EffectsReference->Freeze.getName();
				FreezeFocusEffects = EffectsReference->Freeze.getCurrentlyFocusedComponent()->getName();
				VolumeMain = MainControls[0]->getName();
				VolumeFocusMain = MainControls[0]->getCurrentlyFocusedComponent()->getName();
				GateMain = MainControls[1]->getName();
				GateFocusMain = MainControls[1]->getCurrentlyFocusedComponent()->getName();

				if (NameEffects == FocusEffects)
				{
					if (i != 0)
					{
						EffectsReference->Effects[i - 1]->grabKeyboardFocus();
					}
					else
					{
						MainControls[1]->grabKeyboardFocus();
					}
					break;
				}
				else if (GateMain == GateFocusMain)
				{
					MainControls[0]->grabKeyboardFocus();
					break;
				}
				else if (VolumeMain == VolumeFocusMain)
				{
					EffectsReference->Freeze.grabKeyboardFocus();
					break;
				}
				else if (FreezeEffects == FreezeFocusEffects)
				{
					EffectsReference->Effects[5]->grabKeyboardFocus();
					break;
				}
			}
			break;

		}
	}
}

// Code to slect betwen the Gate and Volume control and +/-
// MainComp selects between volume 0 and gate 1
// PlusNeg if false +--------if true +

// Changing Volume and Gate controls throughkeyboard commands
void VIVI_SynthAudioProcessorEditor::MainComponentSelect(int MainComp, bool PlusNeg)
{
	// If 0 select volume, else if 1 gate
	switch (MainComp)
	{
	case 0:
			// if left arrow -0.5 if right arrow +0.5 to the volume
			MainValue = MainControls[0]->getValue();
			if (PlusNeg) NewValue = MainValue - 0.05;
			else NewValue = MainValue + 0.5;
			MainControls[0]->setValue(NewValue);
			break;

	case 1:
			// if left arrow -0.5 if right arrow +0.5 to the Gate
			MainValue = MainControls[1]->getValue();
			if (PlusNeg) NewValue = MainValue - 0.5;
			else NewValue = MainValue + 0.5;
			MainControls[1]->setValue(NewValue);
			break;
	}

}
// Grabbing focus for components if keypress hit
void VIVI_SynthAudioProcessorEditor::KeyboardCommandsForPages
(int TabIndex, int SliderRef)
{
	Tab.setCurrentTabIndex(TabIndex);
	Tab.grabKeyboardFocus();
	switch (TabIndex)
	{
	case 0:	
		OscReference->Sliders[SliderRef]->grabKeyboardFocus();
		break;
	case 1:	
		EffectsReference->Effects[SliderRef]->grabKeyboardFocus();
		break;
	case 2:		break;
	}
}
#
void VIVI_SynthAudioProcessorEditor::resized()
{
	// Border for Tab Interface
	Tab.setBounds(getLocalBounds().reduced(TabIndent));
	Tab.setTabBarDepth(TabDepth);
}

/*
// Not enough time to implment
// Mute Button On and off Not enough time to finish
void VIVI_SynthAudioProcessorEditor::buttonClicked(juce::Button* toggledButton)
{
	if (toggledButton == &Mute)
	{
		bool Togglestate = Mute.getToggleState();
		int ProcessorState = 1;
		// If True set mute parameter to 1. if false 0
		if (Togglestate == true) 
		{
			Mute.setDescription("ON");
		}
		else 
		{
			ProcessorState = 0;
			Mute.setDescription("OFF");
			DBG(ProcessorState);
		}
	}
}
*/
 
/*
void SettingsPage::buttonClicked(juce::Button* Button)
{
	if (Button == ThemeContainer[0])
	{
		bool Out = Button->getToggleState();
		if (Out == true)
		{
			SettingsPage::sendLookAndFeelChange();
		}
		else
		{
			OtherLookAndFeel.setColour(juce::TextButton::buttonOnColourId, juce::Colours::pink);
			SettingsPage::sendLookAndFeelChange();
		}
	}
}
*/

// Main Control Listener
void VIVI_SynthAudioProcessorEditor::sliderValueChanged(juce::Slider* sliderThatMoved)
{
	// Same as the Oscillator page
	for (int i = 0; i < MainControls.size(); i++)
	{
		if (sliderThatMoved == MainControls[i])
		{
			juce::Component* MainFocus = sliderThatMoved->getCurrentlyFocusedComponent();
			if (MainFocus != nullptr)
			{
				sliderThatMoved->grabKeyboardFocus();
			}
		}
	}
}
// Oscillator Page Listener
void OscillatorPage::sliderValueChanged(juce::Slider* sliderThatMoved)
{
	// If the slider value changes give that parameter keyboard focus
	// AKA let accessibility handler know that the value has changed
	for (int i = 0; i < Sliders.size(); i++) 
	{
		if (sliderThatMoved == Sliders[i])
		{
			juce::Component* SliderFocus = sliderThatMoved->getCurrentlyFocusedComponent();
			if (SliderFocus != nullptr)
			{
				sliderThatMoved->grabKeyboardFocus();
			}

		}
	}
}
// Effects Listener same as the Oscillator
void EffectsPage::sliderValueChanged(juce::Slider* sliderThatMoved)
{
	for (int i = 0; i < Effects.size(); i++)
	{
		if (sliderThatMoved == Effects[i])
		{
			juce::Component* EffectsSlidersFocus = sliderThatMoved->getCurrentlyFocusedComponent();
			if (EffectsSlidersFocus != nullptr)
			{
				sliderThatMoved->grabKeyboardFocus();
			}

		}
	}
}

// Toggle Button
void EffectsPage::buttonClicked(juce::Button* Button)
{	
	if (Button == &Freeze)
	{	
		bool Out = Button->getToggleState();
		if (Out == true) Freeze.setButtonText("Unfrozen");
		else Freeze.setButtonText("Frozen");
	}
}