#include "template.h"
#include "surface.h"
#include "game.h"
#include "Player.h"
#include "Magnet.h"
#include "Vector2D.h"
#include "SDL_keysym.h"

using namespace Tmpl8;
using namespace Chris;

extern Game* game;

cPlayer::cPlayer()
{
	m_Vec = new Vector();
	m_Magnet = NULL;
	m_Health = 100;
	X = 0;
	Y = 0;
}

void cPlayer::Init( char* a_File, int a_NumberOfFrames, int a_DrawFlag )
{	
	m_DrawFlag = a_DrawFlag;
	Surface* Temp = new Surface( a_File );
	Picture = new Sprite( Temp, a_NumberOfFrames );
}

cPlayer::~cPlayer()
{
	delete Picture;
	Picture = NULL;

	delete m_Vec; 
	m_Vec = NULL;

	delete m_Magnet;
	m_Magnet = NULL;
}

void cPlayer::Draw(Surface* a_Surface)
{
	if( m_DrawFlag != INV ) 
	{
		if( m_Health > 0 )
		{
			Picture->Draw( (int)X, (int)Y, a_Surface );
		}
	}
}

void cPlayer::Move()
{
	if( game->GetKey(SDLK_LEFT) )
	{
		X -= 3.0f;
	}
	if( game->GetKey( SDLK_RIGHT ) )
	{
		X += 3.0f;
	}
	if( game->GetKey( SDLK_UP ) )
	{
		Y -= 3.0f;
	}
	if( game->GetKey( SDLK_DOWN ) )
	{
		Y += 3.0f;
	}
}

void cPlayer::HandleMagnet( Surface* a_Surface )
{
	if( m_Magnet != NULL)
	{
		float TempX = ( X + ( Picture->GetWidth() >> 1 ) );
		float TempY = ( Y + ( Picture->GetHeight() >> 1 ) );

		m_Magnet->X = TempX;
		m_Magnet->Y = TempY;

		POINT Temp;
		Temp = game->GetMouse(); 

		//m_Magnet->m_Rotation->m_Angle = angle;
		m_Magnet->m_Vec = &Chris::Vector2D( (float)Temp.x, (float)Temp.y );

		m_Magnet->Tick( a_Surface );
	}
}
void cPlayer::Tick( Surface* a_Surface )
{

	Move();
	Draw( a_Surface );
	HandleMagnet( a_Surface );
	m_Scrap->Tick( a_Surface );

}
