#include "template.h"
#include "surface.h"
#include "game.h"
#include "Enemy.h"
#include "Magnet.h"
#include "Player.h"
#include "Vector2D.h"
#include "SDL_keysym.h"

using namespace Tmpl8;
using namespace Chris;

extern Game* game;
extern cPlayer* Player;

extern int Score;

extern bool ClearScreenFlag;

cEnemy::cEnemy()
{
	m_Vec = new Vector();
	m_Health = 100;
	X = 0;
	Y = 0;
}

void cEnemy::Init( char* a_File, int a_NumberOfFrames, int a_DrawFlag )
{	
	m_DrawFlag = a_DrawFlag;
	Surface* Temp = new Surface( a_File );
	Picture = new Sprite( Temp, a_NumberOfFrames );
}

cEnemy::~cEnemy()
{
	delete Picture;
	Picture = NULL;

	delete m_Vec; 
	m_Vec = NULL;

}

void cEnemy::Draw(Surface* a_Surface)
{
	if( m_DrawFlag != INV ) 
	{
		if( m_Health > 0 )
		{
			Picture->Draw( (int)X, (int)Y, a_Surface );
		}
	}
}

void cEnemy::Move()
{
	if( m_Vec->m_Angle <= 100.0f ) 
	{
		m_Vec->m_Angle = 122.5f;
	}
	else if( m_Vec->m_Angle >= 260.0f)
	{
		m_Vec->m_Angle = 247.5;
	}
	else
	{
		switch( ( rand() % 4 ) )
		{
		case 0:
			{
				m_Vec->m_Angle += 6.0f;
				break;
			}
		case 1:
			{
				m_Vec->m_Angle += 3.0f;
				break;
			}
		case 2:
			{
				m_Vec->m_Angle -= 3.0f;
				break;
			}
		case 3:
			{
				m_Vec->m_Angle -= 6.0f;
				break;
			}
		default:
			{ break; }
		}
	}
	X += m_Vec->UpdateX();
	Y += 1 + m_Vec->UpdateY();

	if( Y < 0 || Y > SCRHEIGHT 
	//	|| X < 0 || X > SCRWIDTH 
		) 
	{
		m_Health = 0;
	}
	if( X < (SCRWIDTH * 0.15f ) || X > ( SCRWIDTH * 0.85f ) - Picture->GetWidth() ) 
	{
		float tempz0r = m_Vec->m_Angle;
		tempz0r -= 270;
		tempz0r = 270 - tempz0r;
		m_Vec->m_Angle = tempz0r;
	}
}

void cEnemy::ColCheck()
{
	float a_X = Player->m_Scrap->X;
	float a_Y = Player->m_Scrap->Y;
	int ScrapWidth = Player->m_Scrap->Picture->GetWidth() / 2;
	int ScrapHeight = Player->m_Scrap->Picture->GetHeight() / 2;
	int MyWidth = Picture->GetWidth() / 2;
	int MyHeight = Picture->GetHeight() / 2;

	if((
		( ( ( a_X + ScrapWidth )		-	( X + MyWidth ) ) >= -	MyWidth )		&& 
		( ( ( a_X + ScrapWidth )		-	( X + MyWidth ) ) <=		MyWidth ) )	&&
		( ( ( a_Y + ScrapHeight )		-	( Y + MyHeight) ) >= -	MyHeight )		&& 
		( ( ( a_Y + ScrapHeight )		-	( Y + MyHeight) ) <=		MyHeight )		)
	{
		m_Health = 0;
		Score += 100;
	}
}

void cEnemy::Tick( Surface* a_Surface )
{
	ColCheck();
	Move();
	Draw( a_Surface );

	if( m_Health <= 0 )
	{
		m_Health = 100;
		X = (float)( ( ( SCRWIDTH>>2 ) - ( (Picture->GetWidth()) >>1 ) + (rand()%(SCRWIDTH>>1) ) ) );
		Y = (float)(Picture->GetHeight());
		m_Vec->m_Angle = (112.5f + (22.5f * ( rand()% 3) ) );
	}


}
