#ifndef MAGNET_BEAM_H
#define MAGNET_BEAM_H

#include	"surface.h"
#include    "Vector2D.h"


namespace Tmpl8 {
class Surface;

class cMagnetBeam
{
public:
	cMagnetBeam();
	~cMagnetBeam();

	void Init( );
	void Draw( Surface* a_Surface );
	void Move();
	void Tick( Surface* a_Surface );

	Chris::Vector* m_Rotation;
	Chris::Vector2D* m_Vec;

	float X,Y;
	int m_DrawFlag;
	bool RedBeam, GreenBeam;
	
	Sprite* GreenBeamPic;
	Sprite* RedBeamPic;

};
};
#endif
