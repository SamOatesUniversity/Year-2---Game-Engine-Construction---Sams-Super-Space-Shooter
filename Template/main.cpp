#include "world.h"
#include "BackGround.h"
#include "SpaceShip.h"
#include "Explosion.h"
#include "AiManger.h"
#include "GuiManager.h"
#include "sound_ids.h"
#include "resource.h"

void HAPI_Main()
{
	//Create the world, and initilise it with screen width and height
	CWorld *world = new CWorld();
	world->init( 800, 600 );
	//Fill in some ftp details, to download missing files, if possible
	world->setFtpDetails( "ftp.samoatesgames.com", "uni@samoatesgames.com", "j9060283", "/GEC/" );
	//turn the backdrop off as were gonna use a background image
	world->visualisation()->setBackdropOn( false );

	//Replace the application icon
	HWND hWnd = GetActiveWindow();
	HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON) );
	SendMessage( hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon );
	SendMessage( hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon );

	//Create an entity for the background
	CBackGround *background = new CBackGround();
	if( !world->addEntity( background, "images/background.jpg", Tbackground ) )HAPI->Close();

	//Create a sound entity, and world entity for an explosion
	if( !world->addSound( soundExplosion, "sounds/explosion.ogg" ) ) HAPI->Close();
	CExplosion *smallExplosion = new CExplosion();
	if( !world->addEntity( smallExplosion, "images/explosion.png" ) ) HAPI->Close();
	smallExplosion->init();

	//Create the player spaceship
	CSpaceShip *SpaceShip = new CSpaceShip();
	createSpaceShip( SpaceShip, smallExplosion, world );

	//Create an ai manager, inwhich all ai entitys are created and controlled
	CAiManger *ai_manager = new CAiManger();
	ai_manager->init( smallExplosion, world );

	//load audio and images for the gui and menu
	if( !world->addSound( soundAmbient, "sounds/main_theme.ogg" ) ) HAPI->Close();
	CGuiManager *gui_manager = new CGuiManager();
	if( !world->addEntity( gui_manager, "images/gui.jpg" ) ) HAPI->Close();
	CGuiMenu *menu_image = new CGuiMenu();
	if( !world->addEntity( menu_image, "images/menu.png" ) ) HAPI->Close();
	gui_manager->init( world->visualisation(), menu_image );
	
	//reset the ai timers
	ai_manager->reset();
	
	bool inGame = false;

	while( HAPI->Update() )
	{
		//Run main menu
		if( !gui_manager->inMenu() )
		{
			//if not in menu, check if new game
			if( !inGame )
			{
				//if new game reset everything
				SpaceShip->restart();
				SpaceShip->setDifficulty( gui_manager->getDifficulty() );
				ai_manager->reset();
				inGame = true;
			}
			//update the ai
			ai_manager->update( gui_manager->getDifficulty() );
		}
		else
		{
			inGame = false;
		}

		//update the world
		world->update();

		//update the gui and pass required values
		gui_manager->setScore( SpaceShip->getScore() );
		gui_manager->setHealth( SpaceShip->getHealth() );
		gui_manager->update();	
	}

	//clean up
	delete ai_manager;
	delete world;
}