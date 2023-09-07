/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainComponent.h"

/*
struct Person
{
    Person();
    int age, heightInInches, distanceTraveled;
    float hairLength, GPA;
    unsigned int SATScore;
    int run(int howFast, bool startWithLeftFoot);
    
};
*/
 
// Première manière d'initialiser les valeurs
/*
Person::Person()
{
    age = 0;
    heightInInches = 0;
    distanceTraveled = 0;
    hairLength = 0.f;
    GPA = 0.f;
    SATScore = 0;
}
*/
// Deuxième manière d'initialiser les valeurs
// Person::Person() : age(0), heightInInches(0), distanceTraveled(0), hairLength(0.f), GPA(0.f), SATScore(0) {}

// Troisième manière d'initialiser les valeurs

struct Person
{
    int age = 0;
    int heightInInches = 0;
    int distanceTraveled = 0;
    float hairLength = 0.f;
    float GPA = 0.f;
    unsigned int SATScore =0;
    
    int run(int howFast, bool startWithLeftFoot);
    void moveAndSetAge(int speed, int newAge);
    struct Foot
    {
        int stepForward()
        {
            return 0;
        }
    };
    Foot leftFoot, rightFoot;
    
    juce::String name;
    Person(juce::String personName) : name(personName)
    {
        DBG("Person ctor: " + name);
    };
    ~Person()
    {
        DBG("Person dtor: " + name);
    };
};


int Person::run(int howFast, bool startWithLeftFoot)
{
    if (startWithLeftFoot)
    {
        return leftFoot.stepForward() + rightFoot.stepForward();
    }
    return rightFoot.stepForward() + leftFoot.stepForward();
}

void Person::moveAndSetAge(int speed, int newAge)
{
    run(speed, true);
    age = newAge;
}

void doStuff()
{
    Person p{"Nicolas"};
    p.moveAndSetAge(5, 42);
}


/*
void Personfunction()
{
    Person p;
}
*/
//Person::Person() {}
 

//==============================================================================
class HelloWorldApplication  : public juce::JUCEApplication
{
public:
    //==============================================================================
    HelloWorldApplication() {}

    const juce::String getApplicationName() override       { return ProjectInfo::projectName; }
    const juce::String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override             { return true; }

    //==============================================================================
    void initialise (const juce::String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..
        Person person{"Tom"};
        DBG(person.age);
        DBG(person.heightInInches);
        mainWindow.reset (new MainWindow (getApplicationName()));
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const juce::String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainComponent class.
    */
    class MainWindow    : public juce::DocumentWindow
    {
    public:
        MainWindow (juce::String name)
            : DocumentWindow (name,
                              juce::Desktop::getInstance().getDefaultLookAndFeel()
                                                          .findColour (juce::ResizableWindow::backgroundColourId),
                              DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainComponent(), true);

           #if JUCE_IOS || JUCE_ANDROID
            setFullScreen (true);
           #else
            setResizable (true, true);
            centreWithSize (getWidth(), getHeight());
           #endif

            setVisible (true);
        }

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (HelloWorldApplication)
