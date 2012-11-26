#ifndef MENU_H
#define MENU_H

#include	"surface.h"

namespace Tmpl8 {
class Surface;

class cMenu
{
public:
	cMenu();
	~cMenu();

	void Init( int a_DrawFlag );
	void Draw( Surface* a_Surface );
	void Move();
	void Tick( Surface* a_Surface );

	Sprite* Picture;
	Sprite*	StartImg;
	Sprite*	ExitImg;
	Sprite*	CreditImg;


	float StartX, StartY;
	float ExitX, ExitY;
	float CreditX, CreditY;

	bool StartAct, ExitAct, CreditAct;

	int m_DrawFlag;

};
};
#endif
