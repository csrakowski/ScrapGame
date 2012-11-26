#include "template.h"
#include "surface.h"
#include "MagnetBeam.h"
#include "SDL_keysym.h"
#include "game.h"
#include "Magnet.h"

using namespace Tmpl8;

extern Game* game;
extern cMagnet* Magnet;

cMagnetBeam::cMagnetBeam()
{
	m_DrawFlag = DEF;
	m_Rotation = new Chris::Vector();
	m_Vec = new Chris::Vector2D();
	m_Rotation->m_Angle = 0;
	RedBeam = false;
	GreenBeam = true;
}

void cMagnetBeam::Init()
{	
	Surface* Temp = new Surface( "Images/Green.png" );
	GreenBeamPic = new Sprite( Temp, 1 );

	Temp = new Surface( "Images/Red.png" );
	RedBeamPic = new Sprite( Temp, 1 );
}

cMagnetBeam::~cMagnetBeam()
{
	delete RedBeamPic;
	RedBeamPic = NULL;

	delete GreenBeamPic;
	GreenBeamPic = NULL;
}

void cMagnetBeam::Draw(Surface* a_Surface)
{
	// draw range lines
	//a_Surface->Line(X,Y,MiddleLineX,MiddleLineY,0x00ff00);
	//a_Surface->Line(X,Y,TopLineX, TopLineY, 0x00ff00); 
	//a_Surface->Line(X,Y,DownLineX, DownLineY, 0x00ff00); 

	Pixel* background = a_Surface->GetBuffer();
	int Pitch = a_Surface->GetPitch();


	if( m_DrawFlag != INV ) 
	{
	
		Pixel* buffer = 0;
		int XSize, YSize;

		if(GreenBeam)
		{
			buffer = GreenBeamPic->GetBuffer();
			YSize = GreenBeamPic->GetHeight();
			XSize = GreenBeamPic->GetWidth();
		}
		else if(RedBeam)
		{
			buffer = RedBeamPic->GetBuffer();
			YSize = RedBeamPic->GetHeight();
			XSize = RedBeamPic->GetWidth();
		}
		else 
		{ 
			return; 
		}


		float cosine = (float)cos((m_Rotation->m_Angle)*RAD);
		float sine = (float)sin((m_Rotation->m_Angle)*RAD);

		int Size = max( XSize, YSize );

		if( m_DrawFlag == DEF )
		{
			for (int dy = -Size; dy < Size; dy++)
			{
				if ( ( Y + dy >= SCRHEIGHT ) || ( Y + dy <= 0 ) ) continue;

				for (int dx = -Size; dx < Size; dx++)
				{
					if ( ( X + dx >= SCRWIDTH ) || ( X + dx <= 0 ) ) continue;

					int tx = (int)( (dx*cosine + dy*sine) + (XSize>>1) );
					int ty = (int)( (dy*cosine - dx*sine) + (YSize) );

					if ((tx >= 0) && (ty >= 0) && (tx<XSize) && (ty<YSize))
					{
						if ( buffer[(ty * XSize) + tx] != ALPHA) 
						{
							background[ (int)( (X+dx) + ( (Y+dy)*(Pitch) ) ) ] = 
							AddBlend(	  buffer[(int)(ty * XSize) + tx], 
									( background[(int)( ( ( Y + dy ) * Pitch) + ( X + dx ) ) ]) );
						}
					}
				}
			}
		}
		else if(GreenBeam)
		{
			GreenBeamPic->Draw( (int)X, (int)Y, a_Surface );
		}
		else if(RedBeam)
		{
			RedBeamPic->Draw( (int)X, (int)Y, a_Surface );
		}
		else
		{
			return;
		}
	}
}


void cMagnetBeam::Move()
{
   m_Rotation->m_Angle = (float)Magnet->MouseAngle;
   X = Magnet->X;
   Y = Magnet->Y;
}


void cMagnetBeam::Tick( Surface* a_Surface )
{
	Move();
	Draw( a_Surface );
}
