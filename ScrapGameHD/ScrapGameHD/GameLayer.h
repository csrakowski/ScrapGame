//
//  GameLayer.h
//  ScrapGameHD
//
//  Created by Frits de Vos on 26-11-12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

// When you import this file, you import all the cocos2d classes
#import "cocos2d.h"
#import "Box2D.h"
#import "GLES-Render.h"

//Pixel to metres ratio. Box2D uses metres as the unit for measurement.
//This ratio defines how many pixels correspond to 1 Box2D "metre"
//Box2D is optimized for objects of 1x1 metre therefore it makes sense
//to define the ratio so that your most common object type is 1x1 metre.
#define PTM_RATIO 32

// GameLayer
@interface GameLayer : CCLayer
{
	CCTexture2D *spriteTexture_;	// weak ref
    CCTexture2D *scrapTexture_;     // weak ref
    CCTexture2D *playerTexture_;    // weak ref
    CCTexture2D *magnetTexture_;    // weak ref
	b2World* world;					// strong ref
	GLESDebugDraw *m_debugDraw;		// strong ref
}


-(void) initPhysics;
-(void) addNewScrapAtPosition:(CGPoint)p;
-(void) addNewEnemyAtPosition:(CGPoint)p;


// returns a CCScene that contains the HelloWorldLayer as the only child
+(CCScene *) scene;

@end
