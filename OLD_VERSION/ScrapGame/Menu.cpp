#include "template.h"
#include "surface.h"
#include "game.h"
#include "Menu.h"
#include "SDL_keysym.h"

using namespace Tmpl8;
using namespace Chris;

extern Game* game;

cMenu::cMenu()
{
	StartAct = false; 
	ExitAct = false; 
	CreditAct = false;

	StartX = 720;
	StartY = 135;

	ExitX = 720;
	ExitY = 296;

	CreditX = 720;
	CreditY = 457;
}

void cMenu::Init( int a_DrawFlag )
{	
	m_DrawFlag = a_DrawFlag;
	Surface* Temp = new Surface( "Images/Menu.png" );
	Picture = new Sprite( Temp, 1 );

	Temp = new Surface( "Images/StartActive.png" );
	StartImg = new Sprite( Temp, 1 );

	Temp = new Surface( "Images/ExitActive.png" );
	ExitImg = new Sprite( Temp, 1 );

	Temp = new Surface( "Images/CreditsActive.png" );
	CreditImg = new Sprite( Temp, 1 );
}

cMenu::~cMenu()
{
	delete Picture;
	Picture = NULL;

}

void cMenu::Draw(Surface* a_Surface)
{
	if( m_DrawFlag != INV ) 
	{
		Picture->Draw( 0, 0, a_Surface );

		if ( StartAct )
		{
			StartImg->Draw( (int) StartX, (int) StartY, a_Surface );
		}
		if ( ExitAct )
		{
			ExitImg->Draw( (int) ExitX, (int) ExitY, a_Surface );
		}
		if( CreditAct )
		{
			CreditImg->Draw( (int) CreditX, (int) CreditY, a_Surface );
		}
	}
}

void cMenu::Move()
{

	if ( ( game->GetMouse().x >= 720 && game->GetMouse().x <= 917 ) && ( game->GetMouse().y >= 135 ) && game->GetMouse().y <= 245 )
	{
		StartAct = true;
		if ( game->m_LButton )
		{
			game->MainMenu = false;
		}
	}
	else
	{
		StartAct = false;
	}

	if ( ( game->GetMouse().x >= 720 && game->GetMouse().x <= 917 ) && ( game->GetMouse().y >= 296 ) && game->GetMouse().y <= 406 )
	{
		ExitAct = true;
		if ( game->m_LButton )
		{
			exit(0);
		}
	}
	else
	{
		ExitAct = false;
	}

	if ( ( game->GetMouse().x >= 720 && game->GetMouse().x <= 917 ) && ( game->GetMouse().y >= 457 ) && game->GetMouse().y <= 567 )
	{
		CreditAct = true;
	}
	else
	{
		CreditAct = false;
	}

}

void cMenu::Tick( Surface* a_Surface )
{
	a_Surface->Clear( 0 );
	Move();
	Draw( a_Surface );

}
