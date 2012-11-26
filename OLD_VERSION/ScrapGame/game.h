// Template, major revision 3, beta
// IGAD/NHTV - Jacco Bikker - 2006-2009

#pragma once

namespace Tmpl8 {

class Surface;
class Game
{
public:
	void SetTarget( Surface* a_Surface ) { m_Surface = a_Surface; }
	void Init();
	void Tick( float a_DT );
	void KeyDown( unsigned int code )	{ m_Keys[code] = true; }
	void KeyUp(	unsigned int code )		{ m_Keys[code] = false; }
	bool GetKey( unsigned int code )	{ return m_Keys[code]; }
	void MouseMove( int x, int y ) { m_MouseX = x; m_MouseY = y; }
	POINT GetMouse() { POINT LocalTemp; LocalTemp.x = m_MouseX; LocalTemp.y = m_MouseY; return LocalTemp; }
	void MouseUp( int b ) { m_LButton = false; }
	void MouseDown( int b ) { m_LButton = true; }
	void ClearKeyFlags() { for(int i = 513; i>=0; --i) m_Keys[i] = false; }
	void Exit( int a_Code = NO_ERROR );

	bool MainMenu;
	bool m_LButton;

private:
	Surface* m_Surface;
	bool m_Keys[512];
	int m_MouseX, m_MouseY;
};

}; // namespace Tmpl8