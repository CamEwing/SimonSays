// FinalProject-041037946.cpp : Defines the entry point for the application.
//

#include "FinalProject-041037946.h"

#include <TGUI/TGUI.hpp>
#include <TGUI/Timer.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream> 
#include <vector>
#include <TGUI/Widget.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

void start();
void addColour();
void startDisplayTimer();
void displayColour();
void startInputTimer();
void takeInput();
void compareVectors();
void showLossMessage();
void enableColours();

enum buttons { top, left, right, bottom };
vector<int> colourSequence;
vector<int> userInput;
int buttonToDisplay = 0;
tgui::Label::Ptr level;
tgui::ChildWindow::Ptr popUp;
tgui::Timer::Ptr displayTimer, userTimer;
tgui::Button::Ptr startButton, playAgain, quit, topButton, leftButton, rightButton, bottomButton;
sf::SoundBuffer buffer, gameOverBuffer;
sf::Sound sound1, gameOver;

int main(int argc, const char* argv[]) {
	sf::RenderWindow window{ {800, 600},"Let's Play Simon!" };
	tgui::Gui gui{ window };
	gui.loadWidgetsFromFile("form.txt");

    
    if (!buffer.loadFromFile("sound1.flac")) { //can use .wav, .ogg/Vorbis, .FLAC
        return EXIT_FAILURE;
    }
    if (!gameOverBuffer.loadFromFile("gameOver.wav")) { //can use .wav, .ogg/Vorbis, .FLAC
        return EXIT_FAILURE;
    }

    sound1.setBuffer(buffer);

    gameOver.setBuffer(gameOverBuffer);
    gameOver.setVolume(50.f);


    displayTimer = tgui::Timer::create([]() { }, sf::milliseconds(500), false);
    userTimer = tgui::Timer::create([]() { }, sf::milliseconds(5000), false);

	startButton = gui.get<tgui::Button>("startButton");
	topButton = gui.get<tgui::Button>("topButton");
	leftButton = gui.get<tgui::Button>("leftButton");
	rightButton = gui.get<tgui::Button>("rightButton");
	bottomButton = gui.get<tgui::Button>("bottomButton");
    
    popUp = gui.get<tgui::ChildWindow>("goodGame");
    level = gui.get<tgui::Label>("LevelsInput");
    playAgain = gui.get<tgui::Button>("playAgain");
    quit = gui.get<tgui::Button>("quit");

    takeInput();
    srand(time(0));
    startButton->onClick([]() {
        start();
    });

	gui.mainLoop();
	return 0;
}


//Listen For Start button
void start() {
    cout << "Starting game\n";
    addColour();
    startDisplayTimer();
}

//Add random colour to vector
void addColour() {
    cout << "adding colour\n";
    colourSequence.push_back(rand() % 4);
}

void startDisplayTimer() {
    displayTimer->setEnabled(true);
    displayTimer->setCallback([]() {
        displayColour();
    });
}

//Display vector
void displayColour() {
    if (buttonToDisplay != colourSequence.size()) {
        switch (colourSequence[buttonToDisplay]) { 
        case 0:
            cout << "0\n";
            topButton->setEnabled(false);
            break;
        case 1:
            cout << "1\n";
            leftButton->setEnabled(false);
            break;
        case 2:
            cout << "2\n";
            rightButton->setEnabled(false);
            break;
        case 3:
            cout << "3\n";
            bottomButton->setEnabled(false);
            break;
        }
        buttonToDisplay++;

        displayTimer->setCallback([]() {
            enableColours();
        });
    }
    else {
        displayTimer->setEnabled(false);
        buttonToDisplay = 0;
        startInputTimer();
    }
}

void enableColours() {
    topButton->setEnabled(true);
    leftButton->setEnabled(true);
    rightButton->setEnabled(true);
    bottomButton->setEnabled(true);
    displayTimer->setCallback([]() {
        displayColour();
    });
}

void startInputTimer() {
    userTimer->setEnabled(true);
    userTimer->setCallback([]() {
        showLossMessage();
    });
}

//Take input
void takeInput() {
    topButton->onClick([]() { 
        sound1.play();
        cout << "0 pressed\n";
        userInput.push_back(0); 
        userTimer->restart();
        compareVectors();       
    });
    leftButton->onClick([]() { 
        sound1.play();
        cout << "1 pressed\n";
        userInput.push_back(1);
        userTimer->restart();
        compareVectors();       
    });
    rightButton->onClick([]() { 
        sound1.play();
        cout << "2 pressed\n";
        userInput.push_back(2);
        userTimer->restart();
        compareVectors();       
    });
    bottomButton->onClick([]() { 
        sound1.play();
        cout << "3 pressed\n";
        userInput.push_back(3);
        userTimer->restart();
        compareVectors();
    });

}

//Compare input with vector
void compareVectors() {
    int i = 0;
    if (userInput.size() > colourSequence.size()) {
        showLossMessage();
        return;
    }

    for (auto button : userInput) { 
        if (button != colourSequence[i]) {
            showLossMessage();
            break;
        }
        else if (userInput.size() == colourSequence.size()) {
            userInput.clear();
            userTimer->setEnabled(false);
            cout << "perfect match\n";
            start();
        }
        else {
            cout << "match\n";
        }
        i++;
    }
}


//Lose message
void showLossMessage() {
    string numLevels = to_string(colourSequence.size() - 1);
    userInput.clear();
    userTimer->setEnabled(false);

    
    if (colourSequence.size() - 1 < 100) {
        gameOver.play();
        colourSequence.clear();
        level->setText(numLevels);
        popUp->setVisible(true);
        cout << "Game over\n";
        playAgain->onClick([]() {
            popUp->setVisible(false);
            });

        quit->onClick([]() { 
            exit(0);
            });
    }
    colourSequence.clear();
    
}



