#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
struct Car
{
    struct CarSeat
    {
        bool seatisLeather;
    };
    int numberOfWheels;
    bool convertible;
    void accelerate(float howFarToPushthePedal);
    CarSeat driverSeat;
    CarSeat PassengerSeat;
    bool switchSeats(CarSeat oldSeat, CarSeat recentSeat);
};

class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    juce::ToggleButton toggleButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
