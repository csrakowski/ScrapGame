#ifndef CENEMY_H
#define CENEMY_H

#include	"surface.h"
#include    "Vector2D.h"

namespace Tmpl8 {
class Surface;

class cEnemy
{
public:
	cEnemy();
	~cEnemy();

	void Init( char* a_File, int a_NumberOfFrames, int a_DrawFlag );
	void Draw( Surface* a_Surface );
	void Move();
	void ColCheck();
	void Tick( Surface* a_Surface );

	Chris::Vector* m_Vec;

	Sprite* Picture;

	float X,Y;
	int m_DrawFlag;
	int m_Health;

};
};

#endif