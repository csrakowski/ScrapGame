#ifndef ASTEROID_H
#define ASTEROID_H

#include "Settings.h"
#include "Surface.h"

namespace Tmpl8 {

Sprite* One, *Two;

class Asteroid
{
public:
	Asteroid(): X(0), Y(0), Image(0) {};
	Asteroid( float a_X, float a_Y ): X(a_X), Y(a_Y), Image(0) {};

	void Init( int a_Frame, int a_Speed )
	{
		One = new Sprite( new Surface("Images/Asteroid1.png"), 16 );
		Two = new Sprite( new Surface("Images/Asteroid2.png"), 16 );
		//m_Scale = 1.0f;
		if( rand() % 5 >= 2 )	Image = One;
		else							Image = Two;
		Image->SetFlags( Sprite::FLARE );
		m_Speed = a_Speed + 1;
		m_Frame = a_Frame;
	}

	void Reset()
	{
		if( rand()%5 >= 2 )	Image = One;
		else							Image = Two;
		m_Speed = ( ( rand() % 5 ) + 1 );
		m_Frame = ( rand() % Image->Frames() );
		//m_Scale = ( ( (float)( rand() % 20 ) ) / 10 );
		Y = 0.0f;
		X = (float)( ( X - 10 ) + ( rand() % 20 ) );
		//X = (float)( ( ( SCRWIDTH>>2 ) - ( (Image->GetWidth()) >>1 ) + (rand()%(SCRWIDTH>>1) ) ) );
	}

	void Tick( Tmpl8::Surface* a_Surface )
	{
		Y += m_Speed;
		m_Frame++;
		m_Frame %= Image->Frames();
		Image->SetFrame( m_Frame );
		Image->Draw( (int)X, (int)Y, a_Surface );
		//Image->DrawScaled( (int)X, (int)Y, (int)( Image->GetWidth() * m_Scale ), (int)( Image->GetHeight() * m_Scale ), a_Surface );

		if( Y >= SCRHEIGHT )
		{
			Reset();
		}
	}

	Tmpl8::Sprite* Image;

	int m_Frame, m_Speed;

	float X, Y;
	//float m_Scale;
};

};

#endif