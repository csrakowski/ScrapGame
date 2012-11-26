#include "ScrapMetal.h"
#include "template.h"
#include "surface.h"
#include "Magnet.h"
#include "game.h"
#include "Player.h"
#include "SDL_keysym.h"

using namespace Tmpl8;
using namespace Chris;

extern Game* game;
extern cMagnet* Magnet;
extern cPlayer* Player;



cScrap::cScrap()
{
	m_DrawFlag = ADD;
	m_Rotation = new Chris::Vector();
	m_Vec = new Chris::Vector2D();
	m_MoveVec = new Chris::Vector();
	m_MoveVec->m_Angle = 0;

	X = (float)(rand() % 900 + 100);
	Y = (float)(rand() % 600 + 100);

	WithinRange = false;
	WithinShootRange = false;
	AngleRot = 0;

}

void cScrap::Init( char* a_File, int a_NumberOfFrames, int a_DrawFlag )
{	
	m_DrawFlag = a_DrawFlag;
	Surface* Temp = new Surface( a_File );
	Picture = new Sprite( Temp, a_NumberOfFrames );
}

cScrap::~cScrap()
{
	delete Picture;
	Picture = NULL;
}

void cScrap::Draw(Surface* a_Surface)
{
	if( m_DrawFlag != INV ) 
	{
		Picture->Draw( (int)X, (int)Y, a_Surface );
	}
}

float cScrap::Dist(float x1, float y1 , float width1, float height1, float x2, float y2, float width2, float height2)
{
	float mid_x1;
	float mid_y1;
	float mid_x2;
	float mid_y2;
	float dif_x;
	float dif_y;
	float distance;

	// calculates the midpoints of the objects
	mid_x1 = x1 + (width1 / 2); 
	mid_y1 = y1 + (height1 / 2); 

	mid_x2 = x2 + (width2 / 2); 
	mid_y2 = y2 + (height2 / 2); 

	// calculates the difference between the x/y of the mid points
	if (mid_x1 > mid_x2)
	{
		dif_x = mid_x1 - mid_x2;
	}
	else if (mid_x1 <= mid_x2){dif_x = mid_x2 - mid_x1;}

	if (mid_y1 > mid_y2)
	{
		dif_y = mid_y1 - mid_y2;
	}
	else if (mid_y1 <= mid_y2){dif_y = mid_y2 - mid_y1;}

	// calculates the distants between the two points
	distance = sqrtf((dif_x*dif_x) + (dif_y*dif_y));

	return distance;
}
 
void cScrap::Move()
{
	// let scrap move same speed as background
	if (!Magnet->StuckToShip)
	{
		Y+=1;
	}

	if ( X > 1024 || X < 0 || Y > 768 )
	{
		X = (float)(rand() % 900 + 100);
		Y = (float)(rand() % 100 - 200);
	}

	Distance = Dist(X,Y,(float)Picture->GetWidth(),(float)Picture->GetHeight(),Player->X,Player->Y, (float)Player->Picture->GetWidth(), (float)Player->Picture->GetHeight()); 

	// checks if metal balls are in range
	if ( ( Distance > 80 ) && ( Distance < 300 )&& 
		( m_MoveVec->m_Angle >= (Magnet->MouseAngle - 15) ) && 
		( m_MoveVec->m_Angle <= (Magnet->MouseAngle + 15) ) )
	{
		WithinRange = true;
		m_MoveVec->m_Speed = 15;
	}
	else { WithinRange = false;}

	if ( !WithinRange && !Magnet->ShootMet && Magnet->Magnetized)
	{
		if ( m_MoveVec->m_Speed > 0 )
		{
			m_MoveVec->m_Speed -= 0.5;
		}
		if ( m_MoveVec->m_Speed < 0 )
		{
			m_MoveVec->m_Speed += 0.5;
		}

	}


	// checks if metal balls are in shoot range
	if (Distance > 50 && Distance < 300 && m_MoveVec->m_Angle >= (Magnet->MouseAngle - 15) && m_MoveVec->m_Angle <= (Magnet->MouseAngle + 15))
	{
		WithinShootRange = true;
		m_MoveVec->m_Speed += 1;
	}
	else 
	{ 
		WithinShootRange = false;
	}

	// vector thingies for scrap
if ( Magnet->Magnetized && WithinRange)
{
	if (Magnet->Magnetized && !Magnet->StuckToShip)
	{
		if (X > Magnet->X){TempX = X - Magnet->X;}
		else {TempX = Magnet->X - X;}

		if (Y > Magnet->Y){TempY = Y - Magnet->Y;}
		else {TempY = Magnet->Y - Y;}

	}

	if (X >= Magnet->X && Y >= Magnet->Y)
	{
		m_MoveVec->m_Angle =  90.0f + (atan( ( TempY / TempX ) ) / (RAD));
	}
	else if (X <= Magnet->X && Y >= Magnet->Y)
	{
		m_MoveVec->m_Angle = 180.0f + (int) (atan( ( TempX / TempY ) ) / (RAD));
	}
	else if (X < Magnet->X && Y < Magnet->Y)
	{
		m_MoveVec->m_Angle = 270.0f + (int) (atan( ( TempY / TempX ) ) / (RAD));
	}
	else
	{
		m_MoveVec->m_Angle = (atan( ( TempX / TempY ) ) / (RAD));
	}
	m_MoveVec->m_Speed = -4.0;
}

	
	if (Magnet->StuckToShip )
	{
		AngleRot+= 5;
		X = (Magnet->X + (sinf( (float) (AngleRot* (RAD) )) * 75) - Picture->GetWidth()/2);
		Y = (Magnet->Y - (cosf( (float) (AngleRot* (RAD) )) * 75) - Picture->GetHeight()/2);
	}

	if ( Magnet->Magnetized && Distance <= 80 && !Magnet->ShootMet )
	{
		//Magnet->Magnetized = false;
		Magnet->StuckToShip = true;
	}
	else
	{
		Magnet->StuckToShip = false;
	}
	
	X += m_MoveVec->UpdateX();
	Y += m_MoveVec->UpdateY();


}
void cScrap::Tick( Surface* a_Surface )
{

	Move();

	Draw( a_Surface );

}

