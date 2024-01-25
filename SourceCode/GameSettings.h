#pragma once
#include <SFML/Graphics.hpp>

//definition of main game properties

//window settings
#define ScreenHeight 1024
#define ScreenWidth 768

//splash screen settings
#define SplashScreenClosedFilePath "Assets/Images/SplashScreenLogoClosed.png"
#define SplashScreenOpenFilePath "Assets/Images/SplashScreenLogoOpen.png"
#define SplashScreenTime 3.5

//game background and game title filepaths
#define GameBackgroundFilepath "Assets/Images/MachinaryBackground.png"
#define GameNameFilepath "Assets/Images/GameName.png"

//play ,retry and quit button filepath, no and hover
#define PlayButtonFilepath "Assets/Images/PlayButton.png"
#define PlayButtonHoverFilepath "Assets/Images/PlayButtonHover.png"
#define RetryButtonFilepath "Assets/Images/RetryButton.png"
#define RetryButtonHoverFilepath "Assets/Images/RetryButtonHover.png"
#define QuitButtonFilepath "Assets/Images/QuitButton.png"
#define QuitButtonHoverFilepath "Assets/Images/QuitButtonHover.png"
#define DashReadyButtonFilepath "Assets/Images/DashReady.png"
#define DashNotReadyButtonFilepath "Assets/Images/DashNotReady.png"

//assets
#define SawUp1Filepath "Assets/Images/SawUP/SawUP1.png"
#define SawUp2Filepath "Assets/Images/SawUP/SawUP2.png"
#define SawUp3Filepath "Assets/Images/SawUP/SawUP3.png"
#define SawUp4Filepath "Assets/Images/SawUP/SawUP4.png"
#define SawDown1FilePath "Assets/Images/SawDOWN/SawDOWN1.png"
#define SawDown2FilePath "Assets/Images/SawDOWN/SawDOWN2.png"
#define SawDown3FilePath "Assets/Images/SawDOWN/SawDOWN3.png"
#define SawDown4FilePath "Assets/Images/SawDOWN/SawDOWN4.png"
#define LandFilepath "Assets/Images/Land2.png"
#define DargonFrame1Filepath "Assets/Images/Dragon/Dragon1.png"
#define DargonFrame2Filepath "Assets/Images/Dragon/Dragon2.png"
#define DargonFrame3Filepath "Assets/Images/Dragon/Dragon3.png"
#define DargonFrame4Filepath "Assets/Images/Dragon/Dragon4.png"
#define DargonFrame5Filepath "Assets/Images/Dragon/Dragon5.png"
#define DargonFrame6Filepath "Assets/Images/Dragon/Dragon6.png"
#define DargonFrame7Filepath "Assets/Images/Dragon/Dragon7.png"
#define DargonFrame8Filepath "Assets/Images/Dragon/Dragon8.png"
#define ScoringSawFilepath "Assets/Images/ScoringSaw.png"
#define ThickFontFilepath "Assets/Fonts/Thick.ttf"
#define GameOverScoreBoardFilepath "Assets/Images/GameOverSCORETAB.png"
#define GameOverTitleFilepath "Assets/Images/GameOverTITLE.png"
#define HighScoreTxtFilepath "Assets/HighScore/HighScore.txt"
#define BronzeMedalFilepath "Assets/Images/BronzeMedal.png"
#define SilverMedalFilepath "Assets/Images/SilverMedal.png"
#define GoldMedalFilepath "Assets/Images/GoldMedal.png"
#define ButtonClickFilepath "Assets/Audio/ButtonClick.wav"
#define ThunderSoundFilepath "Assets/Audio/Thunder.wav"
#define WingFlapFilepath "Assets/Audio/WingFlap.wav"
#define GroundHitFilepath "Assets/Audio/GroundHit.wav"
#define ChainSawHitFilepath "Assets/Audio/ChainSawHit.wav"
#define ScoreBoardScreenSoundTransition "Assets/Audio/ScoreBoardSound.wav"
#define WeeeSoundFilepath "Assets/Audio/weee.wav"
//thx to David Fesliyan for free to use music sample, this sample is non commercial use only
#define BackgroundMusic "Assets/Audio/LandofFantasyByDavidFesliyan.wav"



//numerical settings
#define SawSpawnFrequency .68f
#define DragonAnimationFramerate 0.5f
#define DragonRigidState 1
#define DragonFallingState 2
#define DragonFlyingState 3
#define GravityInGame 350.f
#define FlySpeed 350.f
#define FlyDuration 0.25f
#define DragonRoatationVelocity 100.f
#define FlasScreenSpeed 1500.f
#define TimeBeforeGameOver 1.2f
#define ThickFontSize 140
#define ScreenXOffestHUD 0
#define ScreenYOffsetHUD -150
#define HUDColor sf::Color(239,244,255,255)
#define ScoreBoardFontSize 60
#define ScoreBoardFontColor sf::Color(255,255,255,255)
#define StandByNotificationSize 35
#define ScoreToGetBronzeMedal 50
#define ScoreToGetSilverMedal 100
#define ScoreToGetGoldMedal 150
#define DashSpeed 800.f
#define DefaultHorizontalSpeed 200.f
#define DashTimeout 1.f

//states to check
enum GameStates{
    eStandby, ePlaying, eGameOver
};