#ifndef SCRAPMETAL_H
#define SCRAPMETAL_H

#include "Vector2D.h"
#include "Surface.h"

namespace Tmpl8 {
class Surface;

class cScrap
{
public:
	cScrap();
	~cScrap();

	void Init( char* a_File, int a_NumberOfFrames, int a_DrawFlag );
	void Draw( Tmpl8::Surface* a_Surface );
	void Move();
	void Tick( Tmpl8::Surface* a_Surface );
	float Dist(float x1, float y1 , float width1, float height1, float x2, float y2, float width2, float height2);

	Chris::Vector* m_Rotation;
	Chris::Vector2D* m_Vec;
	Chris::Vector* m_MoveVec;

	float X,Y;
	int m_DrawFlag;
	float MetSpeed;
	float MetDir;
	float Distance;
	bool WithinRange;
	int AngleRot;
	bool WithinShootRange;

	Tmpl8::Sprite* Picture;

	float TempX, TempY;

}; // Class cScrap

}; // Namespace Tmpl8

#endif