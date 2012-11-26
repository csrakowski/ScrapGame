#include "template.h"
#include "surface.h"
#include "Magnet.h"
#include "SDL_keysym.h"
#include "game.h"
#include "Player.h"
#include "ScrapMetal.h"
#include "MagnetBeam.h"

using namespace Tmpl8;

extern Game* game;
extern cScrap* Scrap;
extern cPlayer* Player;
cMagnetBeam* MagnetBeam;

cMagnet::cMagnet()
{
	m_DrawFlag = ADD;
	m_Rotation = new Chris::Vector();
	m_Vec = new Chris::Vector2D();
	m_Rotation->m_Angle = 0;
	Magnetized = false;
	StuckToShip = false;
	ShootMet = false;
}

void cMagnet::Init( char* a_File, int a_NumberOfFrames, int a_DrawFlag )
{	
	m_DrawFlag = a_DrawFlag;
	Surface* Temp = new Surface( a_File );
	Picture = new Sprite( Temp, a_NumberOfFrames );

	MagnetBeam = new cMagnetBeam();
	MagnetBeam->Init();
}

cMagnet::~cMagnet()
{
	delete Picture;
	Picture = NULL;
}

void cMagnet::Draw(Surface* a_Surface)
{
	// draw range lines
	//a_Surface->Line(X,Y,MiddleLineX,MiddleLineY,0x00ff00);
	//a_Surface->Line(X,Y,TopLineX, TopLineY, 0x00ff00); 
	//a_Surface->Line(X,Y,DownLineX, DownLineY, 0x00ff00); 

	if( m_DrawFlag != INV ) 
	{

		Pixel *buffer = Picture->GetBuffer();

		float cosine = (float)cos((m_Rotation->m_Angle)*RAD);
		float sine = (float)sin((m_Rotation->m_Angle)*RAD);

		int YSize = Picture->GetHeight();
		int XSize = Picture->GetWidth();

		if( m_DrawFlag == DEF )
		{
			for (int dy = -YSize; dy < YSize; dy++)
			{
				for (int dx = -XSize; dx < XSize; dx++)
				{
					int tx = (int)( (dx*cosine + dy*sine) + (XSize>>1) );
					int ty = (int)( (dy*cosine - dx*sine) + (YSize>>1) );

					if ((tx >= 0) && (ty >= 0) && (tx<XSize) && (ty<YSize))
					{
						if (buffer[(ty * XSize) + tx] != ALPHA) 
						{
							a_Surface->Plot((int)(X+dx), (int)(Y+dy), buffer[(ty * XSize) + tx]);
						}
					}
				}
			}
		}
		else
		{
			Picture->Draw( (int)X, (int)Y, a_Surface );
		}
	}
}

void cMagnet::DoLamePhysicsStuffAndStuffsThingy()
{
   
	// magnet rotation
	PlayerMiddleX = Player->X + (Player->Picture->GetWidth() / 2);
	PlayerMiddleY = Player->Y + (Player->Picture->GetHeight() / 2);

	if (game->GetMouse().x >= PlayerMiddleX)
	{
		TempX = game->GetMouse().x - PlayerMiddleX;
	}
	else 
	{
		TempX = PlayerMiddleX - game->GetMouse().x;
	}

	if (game->GetMouse().y >= PlayerMiddleY)
	{
		TempY = game->GetMouse().y - PlayerMiddleY;
	}
	else 
	{
		TempY = PlayerMiddleY - game->GetMouse().y;
	}

	if (game->GetMouse().x >= PlayerMiddleX && game->GetMouse().y >= PlayerMiddleY)
	{
		MouseAngle =  90 + (int)(atan( ( TempY / TempX ) ) / (RAD));
	}
	else if (game->GetMouse().x <= PlayerMiddleX && game->GetMouse().y >= PlayerMiddleY)
	{
		MouseAngle = 180 + (int) (atan( ( TempX / TempY ) ) / (RAD));
	}
	else if (game->GetMouse().x < PlayerMiddleX && game->GetMouse().y < PlayerMiddleY)
	{
		MouseAngle = 270 + (int) (atan( ( TempY / TempX ) ) / (RAD));
	}
	else
	{
		MouseAngle = (int) (atan( ( TempX / TempY ) ) / (RAD));
	}

	m_Rotation->m_Angle = (float) MouseAngle;

	MiddleDir = -(MouseAngle - 90)* (RAD) ;

	MiddleLineX = X + (cosf( MiddleDir ) * 300);
	MiddleLineY = Y - (sinf( MiddleDir ) * 300);

	TopLineX = X + (cosf( (float) (-(MouseAngle - 75)* (RAD) )) * 300);
	TopLineY = Y - (sinf( (float) (-(MouseAngle - 75)* (RAD) )) * 300);

	DownLineX = X + (cosf( (float) (-(MouseAngle - 105)* (RAD) )) * 300);
	DownLineY = Y - (sinf( (float) (-(MouseAngle - 105)* (RAD) )) * 300);

	// Magnet abtraction and stuff

	if (game->m_LButton)
	{
		MagnetBeam->GreenBeam = false;
		MagnetBeam->RedBeam = true;
	}
	else
	{
		MagnetBeam->GreenBeam = true;
		MagnetBeam->RedBeam = false;
	}

	if ((game->m_LButton) && Scrap->WithinShootRange)
	{
		Magnetized = false;
	}
	else
	{
		Magnetized = true;
		ShootMet = false;
	}

	if(!Magnetized )
	{
		ShootMet = true;
		Scrap->m_MoveVec->m_Angle = (float) MouseAngle;
	}

}

void cMagnet::Tick( Surface* a_Surface )
{
	DoLamePhysicsStuffAndStuffsThingy();
	Draw( a_Surface );
	MagnetBeam->Tick( a_Surface );
}

