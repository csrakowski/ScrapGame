#ifndef OBJECT_H
#define OBJECT_H

#include	"surface.h"
#include    "Vector2D.h"

namespace Tmpl8 {
class Surface;

class Object
{
public:
	Object();
	~Object();

	void Init();
	void Draw( Surface* a_Surface );
	virtual void Move();
	virtual void Tick( Surface* a_Surface );

	Chris::Vector* m_Vec;

	Sprite* Picture;

	float X,Y;
	int m_DrawFlag;

};
};
#endif
