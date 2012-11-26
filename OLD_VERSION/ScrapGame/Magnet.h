#ifndef MAGNET_H
#define MAGNET_H

#include	"surface.h"
#include    "Vector2D.h"
#include    "ScrapMetal.h"


namespace Tmpl8 {
class Surface;

class cMagnet
{
public:
	cMagnet();
	~cMagnet();

	void Init( char* a_File, int a_NumberOfFrames, int a_DrawFlag );
	void Draw( Surface* a_Surface );
	void DoLamePhysicsStuffAndStuffsThingy();
	void Tick( Surface* a_Surface );

	Chris::Vector* m_Rotation;
	Chris::Vector2D* m_Vec;

	float X,Y;
	int m_DrawFlag;
	bool Magnetized;
	bool StuckToShip;
	bool ShootMet;
	float TempX, TempY;
	int MouseAngle;
	float PlayerMiddleX, PlayerMiddleY;
	float TopLineX, TopLineY, DownLineX, DownLineY, MiddleLineX, MiddleLineY;
	float MiddleDir;

	cScrap* m_Metal;

	Sprite* Picture;

};
};
#endif
