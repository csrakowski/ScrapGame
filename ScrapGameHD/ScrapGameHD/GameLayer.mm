//
//  HelloWorldLayer.mm
//  ScrapGameHD
//
//  Created by Frits de Vos on 26-11-12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

#define BACKGROUND_SCROLL_SPEED 4

// Import the interfaces
#import "GameLayer.h"

// Needed to obtain the Navigation Controller
#import "AppDelegate.h"

#import "PhysicsSprite.h"
#import "ScrapMetal.h"

#import "Player.h"
#import "Magnet.h"

enum {
	kTagNodePlayer = 1,
    kTagNodeMagnet,
    kTagNodeEnemy,
    kTagNodeScrap,
};


#pragma mark - GameLayer

@implementation GameLayer
{
    CCLabelTTF *label;
    NSInteger score;
    CCSprite* backgroundLayer0;
    CCSprite* backgroundLayer1;
    CCSprite* backgroundLayer2;
    CCSprite* backgroundLayer3;
}

+(CCScene *) scene
{
	// 'scene' is an autorelease object.
	CCScene *scene = [CCScene node];
	
	// 'layer' is an autorelease object.
	GameLayer *layer = [GameLayer node];
	
	// add layer as a child to scene
	[scene addChild: layer];
	
	// return the scene
	return scene;
}

-(id) init
{
	if( (self=[super init])) {
		
		// enable events
		
		self.isTouchEnabled = YES;
		self.isAccelerometerEnabled = YES;
		CGSize s = [CCDirector sharedDirector].winSize;
		
		// init physics
		[self initPhysics];
		
        //Set up sprites
        [self setupBackgroundImage:s];

		CCSpriteBatchNode *spriteParent = [CCSpriteBatchNode batchNodeWithFile:@"Enemy.png" capacity:100];
		spriteTexture_ = [spriteParent texture];
        [self addChild:spriteParent z:10 tag:kTagNodeEnemy];
        
        CCSpriteBatchNode *scrapParent = [CCSpriteBatchNode batchNodeWithFile:@"Scrap.png" capacity:100];
		scrapTexture_ = [scrapParent texture];
        [self addChild:scrapParent z:11 tag:kTagNodeScrap];
        
        CCSpriteBatchNode *playerParent = [CCSpriteBatchNode batchNodeWithFile:@"Player.png" capacity:1];
		playerTexture_ = [playerParent texture];
        [self addChild:playerParent z:98 tag:kTagNodePlayer];
        
        CCSpriteBatchNode *magnetParent = [CCSpriteBatchNode batchNodeWithFile:@"Magnet.png" capacity:1];
		magnetTexture_ = [magnetParent texture];
        [self addChild:magnetParent z:99 tag:kTagNodeMagnet];
		
		
        Player *player = [Player spriteWithTexture:playerTexture_ rect:CGRectMake(0,0,128,128)];
        [playerParent addChild:player];
        player.position = ccp(s.width/2, s.height/2);
        
        
        Magnet *magnet = [Magnet spriteWithTexture:magnetTexture_ rect:CGRectMake(0,0,64,64)];
        [magnetParent addChild:magnet];
        magnet.position = ccp(s.width/2, s.height/2);
        player.magnet = magnet;
        
        label = [CCLabelTTF labelWithString:@"Score: 0000" fontName:@"Marker Felt" fontSize:32];
        [label setHorizontalAlignment:kCCTextAlignmentRight];
		[label setColor:ccc3(0,0,255)];
		label.position = ccp(s.width-85, s.height-20);
        [self addChild:label z:99];
		
		[self scheduleUpdate];
	}
	return self;
}

//Create our scrolling background
- (void)setupBackgroundImage:(CGSize)size
{
    CGRect rect = CGRectMake(0, 0, size.width, size.height);
    //create both sprite to handle background
    backgroundLayer0 = [CCSprite spriteWithFile:@"Stars.png" rect:rect];
    backgroundLayer1 = [CCSprite spriteWithFile:@"Stars.png" rect:rect];
    
    backgroundLayer2 = [CCSprite spriteWithFile:@"Nebula.png" rect:rect];
    backgroundLayer2.opacity = 128;
    
    backgroundLayer3 = [CCSprite spriteWithFile:@"Nebula.png" rect:rect];
    backgroundLayer3.opacity = 128;
    
    backgroundLayer0.position = ccp(size.width/2, size.height/2);
    backgroundLayer1.position = ccp(size.width/2, size.height*1.5);
    backgroundLayer2.position = ccp(size.width/2, size.height/2);
    backgroundLayer3.position = ccp(size.width/2, (size.height*1.5));
    
    //add them to main layer
    [self addChild:backgroundLayer0 z:0];
    [self addChild:backgroundLayer1 z:0];
    [self addChild:backgroundLayer2 z:1];
    [self addChild:backgroundLayer3 z:1];
    
    //add schedule to move backgrounds
    [self schedule:@selector(scroll:)];
}

- (void)scroll:(ccTime)dt {
    
    CGSize size = [CCDirector sharedDirector].winSize;
    
    backgroundLayer0.position = ccp( backgroundLayer0.position.x, backgroundLayer0.position.y - BACKGROUND_SCROLL_SPEED);
    backgroundLayer1.position = ccp( backgroundLayer1.position.x, backgroundLayer1.position.y - BACKGROUND_SCROLL_SPEED);
    
    backgroundLayer2.position = ccp( backgroundLayer2.position.x, backgroundLayer2.position.y - 2 * BACKGROUND_SCROLL_SPEED);
    backgroundLayer3.position = ccp( backgroundLayer3.position.x, backgroundLayer3.position.y - 2 * BACKGROUND_SCROLL_SPEED);
    
    //reset position when they are off from view.
    if (backgroundLayer0.position.y <= -(size.height/2)) {
        backgroundLayer0.position = ccp(backgroundLayer0.position.x, (size.height*1.5));
    } else if (backgroundLayer1.position.y <= -(size.height/2)) {
        backgroundLayer1.position = ccp(backgroundLayer1.position.x, (size.height*1.5));
    }
    
    if (backgroundLayer2.position.y <= -(size.height/2)) {
        backgroundLayer2.position = ccp(backgroundLayer2.position.x, (size.height*1.5));
    } else if (backgroundLayer3.position.y <= -(size.height/2)) {
        backgroundLayer3.position = ccp(backgroundLayer3.position.x, (size.height*1.5));
    }
}

-(void)incrementScore:(int)points
{
    [self setScore:(score + points)];
}

-(void) setScore:(int)newScore
{
    score = newScore;
    [label setString:[NSString stringWithFormat:@"Score: %04d", score]];
}

-(void) dealloc
{
	delete world;
	world = NULL;
	
	delete m_debugDraw;
	m_debugDraw = NULL;
	
	[super dealloc];
}	

-(void) initPhysics
{
	CGSize s = [[CCDirector sharedDirector] winSize];
	
	b2Vec2 gravity;
	gravity.Set(0.0f, -0.1f);
	world = new b2World(gravity);
	
	
	// Do we want to let bodies sleep?
	world->SetAllowSleeping(true);
	
	world->SetContinuousPhysics(true);
	
	m_debugDraw = new GLESDebugDraw( PTM_RATIO );
	world->SetDebugDraw(m_debugDraw);
	
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	//		flags += b2Draw::e_jointBit;
	//		flags += b2Draw::e_aabbBit;
	//		flags += b2Draw::e_pairBit;
	//		flags += b2Draw::e_centerOfMassBit;
	m_debugDraw->SetFlags(flags);		
	
	
	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0); // bottom-left corner
	
	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	
	// Define the ground box shape.
	b2EdgeShape groundBox;		
	
	// bottom
	
	groundBox.Set(b2Vec2(0,0), b2Vec2(s.width/PTM_RATIO,0));
	groundBody->CreateFixture(&groundBox,0);
	
	// top
	groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);
	
	// left
	groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(0,0));
	groundBody->CreateFixture(&groundBox,0);
	
	// right
	groundBox.Set(b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,0));
	groundBody->CreateFixture(&groundBox,0);
}

-(void) draw
{
	//
	// IMPORTANT:
	// This is only for debug purposes
	// It is recommend to disable it
	//
	[super draw];
	
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	
	kmGLPushMatrix();
	world->DrawDebugData();	
	kmGLPopMatrix();
}

-(void) addNewRandomScrap
{
    CGSize s = [[CCDirector sharedDirector] winSize];
    
    int x = (10 + (rand() % ((int)(s.width - 20))));
    [self addNewScrapAtPosition:ccp(x, s.height)];
}

-(void) addNewScrapAtPosition:(CGPoint)p
{
	CCLOG(@"Add scrap %0.2f x %02.f",p.x,p.y);
	CCNode *parent = [self getChildByTag:kTagNodeScrap];
	
	ScrapMetal *sprite = [ScrapMetal spriteWithTexture:scrapTexture_ rect:CGRectMake(0,0,64,64)];
    [sprite setPosition:ccp( p.x, p.y)];
    //sprite.position = ccp( p.x, p.y);
	[parent addChild:sprite];
	
	// Define the dynamic body.
	//Set up a 1m squared box in the physics world
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);
	b2Body *body = world->CreateBody(&bodyDef);
	
	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(.5f, .5f);//These are mid points for our 1m box
	
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;	
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
	
	[sprite setPhysicsBody:body];
}

-(void) addNewEnemyAtPosition:(CGPoint)p
{
	CCLOG(@"Add enemy %0.2f x %02.f",p.x,p.y);
	CCNode *parent = [self getChildByTag:kTagNodeEnemy];
	
	PhysicsSprite *sprite = [PhysicsSprite spriteWithTexture:spriteTexture_ rect:CGRectMake(0,0,128,128)];
	[parent addChild:sprite];
	
	sprite.position = ccp( p.x, p.y);
	
	// Define the dynamic body.
	//Set up a 1m squared box in the physics world
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);
	b2Body *body = world->CreateBody(&bodyDef);
	
	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(.5f, .5f);//These are mid points for our 1m box
	
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
	
	[sprite setPhysicsBody:body];
}

-(void) update: (ccTime) dt
{
	//It is recommended that a fixed time step is used with Box2D for stability
	//of the simulation, however, we are using a variable time step here.
	//You need to make an informed choice, the following URL is useful
	//http://gafferongames.com/game-physics/fix-your-timestep/
	
	int32 velocityIterations = 8;
	int32 positionIterations = 1;
	
	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
	world->Step(dt, velocityIterations, positionIterations);	
}

- (void)ccTouchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	//Add a new body/atlas sprite at the touched location
	for( UITouch *touch in touches ) {
		CGPoint location = [touch locationInView: [touch view]];
		
		location = [[CCDirector sharedDirector] convertToGL: location];
		
        
        [self incrementScore:150];
		[self addNewRandomScrap];
	}
}

@end