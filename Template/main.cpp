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
	CWorld *world = new CWorld();
	world->init( 800, 600 );
	world->setFtpDetails( "ftp.samoatesgames.com", "uni@samoatesgames.com", "j9060283", "/GEC/" );
	world->visualisation()->setBackdropOn( false );

	HWND hWnd = GetActiveWindow();
	HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON) );
	SendMessage( hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon );
	SendMessage( hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon );

	CBackGround *background = new CBackGround();
	if( !world->addEntity( background, "images/background.jpg", Tbackground ) )HAPI->Close();

	if( !world->addSound( soundExplosion, "sounds/explosion.wav" ) ) HAPI->Close();
	CExplosion *smallExplosion = new CExplosion();
	if( !world->addEntity( smallExplosion, "images/explosion.png" ) ) HAPI->Close();
	smallExplosion->init();

	CSpaceShip *SpaceShip = new CSpaceShip();
	createSpaceShip( SpaceShip, smallExplosion, world );

	CAiManger *ai_manager = new CAiManger();
	ai_manager->init( smallExplosion, world );

	if( !world->addSound( soundAmbient, "sounds/space_theme.wav" ) ) HAPI->Close();
	CGuiManager *gui_manager = new CGuiManager();
	if( !world->addEntity( gui_manager, "images/gui.jpg" ) ) HAPI->Close();
	CGuiMenu *menu_image = new CGuiMenu();
	if( !world->addEntity( menu_image, "images/menu.png" ) ) HAPI->Close();
	gui_manager->init( world->visualisation(), menu_image );
	
	ai_manager->reset();
	
	bool inGame = false;

	while( HAPI->Update() )
	{
		if( !gui_manager->inMenu() )
		{
			if( !inGame )
			{
				SpaceShip->restart();
				SpaceShip->setDifficulty( gui_manager->getDifficulty() );
				ai_manager->reset();
				inGame = true;
			}
			ai_manager->update( gui_manager->getDifficulty() );
		}
		else
		{
			inGame = false;
		}

		world->update();

		gui_manager->setScore( SpaceShip->getScore() );
		gui_manager->setHealth( SpaceShip->getHealth() );
		gui_manager->update();	
	}

	delete ai_manager;
	delete world;
}