#include "template.h"
#include "surface.h"
#include "Object.h"
#include "game.h"
#include "SDL_keysym.h"

using namespace Tmpl8;

extern Game* game;

Object::Object()
{
	m_DrawFlag = ADD;
	m_Vec = new Chris::Vector();
	X = 128;
	Y = 128;
}

void Object::Init()
{	
	Surface* Temp = new Surface("Images/Sprite.png");
	Picture = new Sprite( Temp, 1 );
}

Object::~Object()
{
	delete Picture;
	Picture = NULL;
}

void Object::Draw(Surface* a_Surface)
{
	if( m_DrawFlag != INV ) 
	{
			Pixel *buffer = Picture->GetBuffer();

			float cosine = (float)cos((m_Vec->m_Angle)*RAD);
			float sine = (float)sin((m_Vec->m_Angle)*RAD);

			int YSize = Picture->GetHeight();
			int XSize = Picture->GetWidth();

		if( m_DrawFlag == ADD )
		{
			for (int dy = -YSize; dy < YSize; dy++)
			{
				for (int dx = -XSize; dx < XSize; dx++)
				{
					int tx = (int)( (dx*cosine + dy*sine) + (XSize>>1) );
					int ty = (int)( (dy*cosine - dx*sine) + (YSize>>1) );

					if ((tx >= 0) && (ty >= 0) && (tx<XSize) && (ty<YSize))
					{
						int Offset = (int)((X+dx) * (Y+dy));
						if(Offset <= 0) { continue; }
						Pixel BackGround = a_Surface->GetBuffer()[ Offset ];
						Pixel a_Color = buffer[(ty * XSize) + tx];
						a_Color = AddBlend( a_Color, BackGround );
						if (a_Color != ALPHA) 
						{
							a_Surface->Plot((int)(X+dx), (int)(Y+dy), a_Color);
						}
					}
				}
			}
		}
		else if( m_DrawFlag == SUB )
		{
			for (int dy = -YSize; dy < YSize; dy++)
			{
				for (int dx = -XSize; dx < XSize; dx++)
				{
					int tx = (int)( (dx*cosine + dy*sine) + (XSize>>1) );
					int ty = (int)( (dy*cosine - dx*sine) + (YSize>>1) );

					if ((tx >= 0) && (ty >= 0) && (tx<XSize) && (ty<YSize))
					{
						Pixel BackGround = a_Surface->GetBuffer()[ (int)((X+dx) * (Y+dy)) ];
						Pixel a_Color = buffer[(ty * XSize) + tx];
						a_Color = SubBlend( a_Color, BackGround );
						if (a_Color != ALPHA) 
						{
							a_Surface->Plot((int)(X+dx), (int)(Y+dy), a_Color);
						}
					}
				}
			}
		}
		else
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
	}
}
 
void Object::Move()
{
	if( game->GetKey(SDLK_LEFT) )
	{
		m_Vec->m_Angle -= 1.0;
	}
	if( game->GetKey( SDLK_RIGHT ) )
	{
		m_Vec->m_Angle += 1.0;
	}
	if( game->GetKey( SDLK_UP ) )
	{
		if(m_Vec->m_Speed <= 0.5)
		{
			m_Vec->m_Speed += 0.1f;
		}
	}
	if( game->GetKey( SDLK_DOWN ) )
	{
		if(m_Vec->m_Speed >= -0.3)
		{
			m_Vec->m_Speed -= 0.1f;
		}
	}
	if (!game->GetKey( SDLK_DOWN ) && !game->GetKey( SDLK_UP ))
	{
		m_Vec->m_Speed = 0.0f;
	}

	X += m_Vec->UpdateX();
	Y += m_Vec->UpdateY();

}
void Object::Tick( Surface* a_Surface )
{

	Move();

	Draw( a_Surface );

}

