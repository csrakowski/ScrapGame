#ifndef PLAYER_H
#define PLAYER_H

#include	"surface.h"
#include    "Vector2D.h"
#include	"Magnet.h"
#include	"ScrapMetal.h"

namespace Tmpl8 {
class Surface;

class cPlayer
{
public:
	cPlayer();
	~cPlayer();

	void Init( char* a_File, int a_NumberOfFrames, int a_DrawFlag );
	void Draw( Surface* a_Surface );
	void Move();
	void HandleMagnet( Surface* a_Surface );
	void Tick( Surface* a_Surface );

	Chris::Vector* m_Vec;
	Sprite* Picture;
	cMagnet* m_Magnet;
	cScrap* m_Scrap;

	float X, Y;
	int m_DrawFlag;
	int m_Health;
};
};
#endif
