#include "Config.h"
#include "Interface.h"
#include "World.h"



//Start Screenh panel
cPanel* startScreenPanel;

//Pause screen panel
cPanel* pauseScreenPanel;

//Goal screen pop up panel
cPanel* completedScreenPanel;

//Panel wwhich holds the timer
cPanel* clockPanel;

//Start and exit button on start screen panel
cLabel* startButton ;
cLabel* exitButtonss ;

//Resume, exit and display button for pause panel
cLabel* resumeButton ;
cLabel* exitButtonps ;
cLabel* displayButton ;

//Next level and exit button for the completed goal screen
cLabel* nextLevel;
cLabel* exitcs;

//Label for the message if game is completed
cLabel* completedMessage;

//Label which shows the game timer
cLabel* clockInfo;

//Font for all the labels
cFontPtr font = NEW_CFONTCALIBRI20();
 
//Colours for the screen backgrounds
cColorf black;
cColorf blue;
cColorf white;

//Used for the resource path for the background image
string resourceRoot;
#define RESOURCE_PATH(p)    (char*)((resourceRoot+string(p)).c_str())

//Tells us if the game has started
bool gameStarted = false;

//Tells us if the game is paused
bool paused = false ;

//Tells us what colour mode the game is in
bool darkMode = true ;


/**
 * @brief Creates a start screen for the game
 */

void createStartscreen(){
    
    startScreenPanel = new cPanel();
    startButton = new cLabel(font);
    exitButtonss = new cLabel(font);
        
    startScreenPanel->setSize(width, height);
    startScreenPanel->setTransparencyLevel(1);

    camera->m_frontLayer->addChild(startScreenPanel);camera->m_frontLayer->addChild(startScreenPanel);
    

    black.set(0, 0, 0); 
    blue.set(0.0, 1.0, 1.0);

    startScreenPanel->m_texture = cTexture2d::create();
    startScreenPanel->m_texture->loadFromFile(RESOURCE_PATH("../../BoardGameArchitecture/src/images/MazeGame.png"));
    startScreenPanel->setUseTexture(true);
   

    //Adding startscreen labels
    startScreenPanel->addChild(startButton);
    startButton->setText("Start");
    startButton->setLocalPos(((width/2) - 20), (height/2) + 50, 0.1);
    startButton->m_fontColor.setWhite();

    startScreenPanel->addChild(exitButtonss);
    exitButtonss->setText("Exit");
    exitButtonss->setLocalPos(((width/2) - 20), (height/2) + 10, 0.1);
    exitButtonss->m_fontColor.setWhite();
}

void createPausescreen(){
    pauseScreenPanel =  new cPanel();

    pauseScreenPanel->setSize(width, height);
    pauseScreenPanel->setTransparencyLevel(0.8);

    resumeButton = new cLabel(font);        
    exitButtonps = new cLabel(font);
    displayButton = new cLabel(font);

    pauseScreenPanel->setColor(black);
  

        //Adding Buttons
    pauseScreenPanel->addChild(resumeButton);
    resumeButton->setText("Resume");
    resumeButton->setLocalPos(((width/2) - 35), (height/2) + 50, 0.1);
    resumeButton->m_fontColor.setWhite();

    pauseScreenPanel->addChild(exitButtonps);
    exitButtonps->setText("Exit");
    exitButtonps->setLocalPos(((width/2) - 20), (height/2), 0.1);
    exitButtonps->m_fontColor.setWhite();

    pauseScreenPanel->addChild(displayButton);
    displayButton->setText("Change Display Mode");
    displayButton->setLocalPos(((width/2) -75 ), (height/2)- 50, 0.1);
    displayButton->m_fontColor.setWhite();
}

/**
 * @brief Creates a panel if the game is completed 
 * 
 * @param timetaken Holds the number of seconds taken to reach the goal
 * @param level The current level the user completed
 */

void createCompletedScreen(int timetaken, int level){
    
    if (gameFinished = 1){
        //gameFinished++ ;
        
        string sTimetaken = to_string(timetaken);
        string sLevel = to_string(level);
        
        completedScreenPanel = new cPanel();
        completedScreenPanel->setSize(width, height);
        completedScreenPanel->setTransparencyLevel(1);

        camera->m_frontLayer->addChild(completedScreenPanel);

        completedScreenPanel->setColor(black);
        
        nextLevel = new cLabel(font);
        exitcs = new cLabel(font);
        completedMessage = new cLabel(font);

        completedScreenPanel->addChild(nextLevel);
        nextLevel->setText("Next Level");
        nextLevel->setLocalPos(((width/2) - 35), (height/2) + 50, 0.1);
        nextLevel->m_fontColor.setWhite();
        
        completedScreenPanel->addChild(exitcs);
        exitcs->setText("Exit");
        exitcs->setLocalPos(((width/2) - 20), (height/2), 0.1);
        exitcs->m_fontColor.setWhite();

        completedScreenPanel->addChild(completedMessage);

        completedMessage->setText("Well Done For Completing Level " + sLevel + " with a time of " + sTimetaken + " seconds");
        completedMessage->setLocalPos(((width/2) - 200), ((height/2) + 100), 0.1);
        completedMessage->m_fontColor.setWhite();
        

    }
    
}

/**
 * @brief Creates a panel for the clock and prints out the clock label
 */

void clockInterface(){

    //clock panel
    clockPanel = new cPanel();
    clockInfo = new cLabel(font);

    camera->m_frontLayer->addChild(clockPanel);
    clockPanel->setSize(width/4, height/7);
    clockPanel->m_material->setGrayDim();
    clockPanel->setTransparencyLevel(1.0);
    clockPanel->setLocalPos(width - (width/4), height-(height/7));
    

    clockPanel->addChild(clockInfo);
    clockInfo->setLocalPos(width/12, height/10, 0.1);
    clockInfo->m_fontColor.setBlack();

};


/**
 * @brief Changes the panel colours to Black
 */
void darkBackground (){
    pauseScreenPanel->setColor(black);
    darkMode = true;   
}


/**
 * @brief Changes the panel colours to Light blue
 */
void lightBackground (){ 
    pauseScreenPanel->setColor(blue);
    darkMode = false;
}



/**
 * @brief Resizes the panel screens if the window changes
 */
void resizeInterfaces(){
    
    //Reset panels
    pauseScreenPanel->setSize(width, height);
    startScreenPanel->setSize(width, height);
    clockPanel->setSize(width/4, height/7);
    
    clockPanel->setLocalPos(width - (width/4), height-(height/7));
    
    //StartScreen Labels
    startButton->setLocalPos(((width/2) - 20), (height/2) + 50, 0.1);
    exitButtonss->setLocalPos(((width/2) - 20), (height/2) + 10, 0.1);
    
    //PauseCreen Labels
    resumeButton->setLocalPos(((width/2) - 35), (height/2) + 50, 0.1);
    exitButtonps->setLocalPos(((width/2) - 20), (height/2), 0.1);
    displayButton->setLocalPos(((width/2) -75 ), (height/2)- 50, 0.1); 

    clockInfo->setLocalPos(width/12, height/10, 0.1);
    if (gameFinished > 0 )
    {
        completedScreenPanel->setSize(width, height);
        nextLevel->setLocalPos(((width/2) - 35), (height/2) + 50, 0.1);
        exitcs->setLocalPos(((width/2) - 20), (height/2), 0.1);
        completedMessage->setLocalPos(((width/2) - 200), ((height/2) + 100), 0.1);
    }
    


}
