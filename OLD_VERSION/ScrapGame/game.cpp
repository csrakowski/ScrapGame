// Template, major revision 3, beta
// IGAD/NHTV - Jacco Bikker - 2006-2009
#include <fstream>

#include "string.h"
#include "surface.h"
#include "stdlib.h"
#include "template.h"
#include "game.h"
#include "fmod.h"
#include "Player.h"
#include "Enemy.h"
#include "ScrapMetal.h"
#include "Menu.h"
#include <time.h>
#include "Asteroid.h"
#include "SDL.h"

#include "Settings.h"
using namespace Tmpl8;
//using namespace std;

#ifdef TIMINGMODE
std::ofstream ofx("Timings.csv");
int frame = 0;
#endif

#ifdef SOUND
FSOUND_SAMPLE* handle;
bool Once = true;
#endif

cPlayer* Player;
cEnemy* Enemy;
cMagnet* Magnet;
cScrap*  Scrap;
cMenu*	Menu;

Surface* Background;
Surface* Background2;
Sprite* UI;

#define ASTEROIDS 5

Asteroid* Asteroids[ASTEROIDS];

bool ClearScreenFlag = false;

int UIHeight;
int yCoord = 0;
int yCoord2 = 0;

int Score = 0;

Surface* Backbuffer;

void Game::Init()
{
	MainMenu = true;

	srand ( (int)time(NULL) );

	ClearKeyFlags();

	Backbuffer = new Surface( SCRWIDTH, SCRHEIGHT );

	Scrap = new cScrap();
	Scrap->Init( "Images/MetalBall.png", 1, DEF );

	Magnet = new cMagnet();
	Magnet->Init( "Images/Magnet.png", 1, DEF );

	Player = new cPlayer();
	Player->Init( "Images/Player.png", 1, DEF );
	Player->X = (float)( ( SCRWIDTH>>1 ) - ( (Player->Picture->GetWidth()) >>1 ) );
	Player->Y = ( SCRHEIGHT>>1);
	Player->m_Vec->m_Angle = 0;
	Player->m_Magnet = Magnet;
	Player->m_Scrap = Scrap;

	Enemy = new cEnemy();
	Enemy->Init( "Images/Enemy.png", 1, DEF );
	Enemy->X = (float)( ( SCRWIDTH>>1 ) - ( (Enemy->Picture->GetWidth()) >>1 ) );
	Enemy->Y = (float)(Enemy->Picture->GetHeight());

	Background = new Surface("Images/Stars.png");
	Background2 = new Surface("Images/Nebula.png");

	UI = new Sprite( new Surface("Images/UI.png"), 1);

	int Size = SCRWIDTH / ASTEROIDS;
	for( int i = 0; i < ASTEROIDS; i++ )
	{
 		Asteroids[i] = new Asteroid( (float)( ( Size*i ) + ( rand() % Size ) ), (float)( rand()%10 ) );
		Asteroids[i]->Init( 0, (int)( rand()%5 ) );
	}

	Menu = new cMenu();
	Menu->Init( DEF );

	UIHeight = ( SCRHEIGHT - UI->GetHeight() - 1);

#ifdef SOUND
	FSOUND_Init (48000, 16, 0);
	handle = FSOUND_Sample_Load (0,"Sound/Main.mp3",0,0,0);
#endif

#ifdef TIMINGMODE
		ofx<<"PlayerTime;"<<"EnemyTime;"<<"AsteroidTime;BackgroundTime"<<std::endl;
#endif

}

void DrawBackdrop( Surface* a_Surface )
{
		// Create Parallax Scrolling Background(s)
		Background->CopyTo( a_Surface, 0, yCoord );
		Background->CopyTo( a_Surface, 0, ( yCoord - 768 ) );

		Background2->AddBlendCopyTo( a_Surface, 0, yCoord2 );
		Background2->AddBlendCopyTo( a_Surface, 0, ( yCoord2 - 768 ) );
}


void Game::Exit( int a_Code )
{
	SDL_Quit();
	exit( a_Code );
}
void Game::Tick( float a_DT )
{

	if (MainMenu)
	{
		Menu->Tick( m_Surface );
	}
	else
	{
		#ifdef SOUND
		if (Once)
		{
			FSOUND_PlaySound (0,handle);
			Once = false;
		}
		#endif

		#ifdef TIMINGMODE
		int start = GetTickCount();
		for( int i = 0; i < 100; i++ ) {
		#endif
		
		DrawBackdrop( Backbuffer );

		#ifdef TIMINGMODE
		} int BackgroundTime = GetTickCount() - start;

		start = GetTickCount();
		for( int i = 0; i < 100; i++ ) {
		#endif

		Player->Tick( Backbuffer );

		#ifdef TIMINGMODE
		} int PlayerTime = GetTickCount() - start;

		start = GetTickCount();
		for( int i = 0; i < 100; i++ ) {
		#endif

		for( int i = 0; i < ASTEROIDS; i++ )
		{
			Asteroids[i]->Tick( Backbuffer );
		}
		
		#ifdef TIMINGMODE
		} int AsteroidTime = GetTickCount() - start;

		start = GetTickCount();
		for( int i = 0; i < 100; i++ ) {
		#endif

		Enemy->Tick( Backbuffer );

		#ifdef TIMINGMODE
		} int EnemyTime = GetTickCount() - start;
		#endif

		UI->Draw(0, UIHeight, Backbuffer );

		Backbuffer->CopyTo( m_Surface );

		#ifdef TIMINGMODE
		// Player 300, Background 1800
		ofx<<PlayerTime<<";"<<EnemyTime<<";"<<AsteroidTime<<";"<<BackgroundTime<<std::endl;

		if( frame++ >= 19 ) 
		{
			ofx<<"=AVERAGE(A2:A21);"<<"=AVERAGE(B2:B21);"<<"=AVERAGE(C2:C21);"<<"=AVERAGE(D2:D21)"<<std::endl;
			ofx.close();
			Exit( 0 );
		}
		#endif

		char c[255];
		sprintf( c, "Score: %i", Score );
		m_Surface->Print( c, 4, 8, REDMASK );

		#ifdef TIMINGMODE
		sprintf( c, "Frame: %i", frame );
		m_Surface->Print( c, 4, 16, REDMASK );
		#endif

		yCoord+=1;	if( yCoord	>= 768 ) yCoord	= 0;
 		yCoord2+=4; if( yCoord2 >= 768 ) yCoord2	= 0;
 	}

}

// memset(mMinimum, mWidth - 1, mHeight * sizeof(int));