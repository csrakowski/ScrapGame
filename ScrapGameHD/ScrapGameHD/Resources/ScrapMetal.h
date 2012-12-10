//
//  ScrapMetal.h
//  ScrapGameHD
//
//  Created by CHRISTIAAN Rakowski on 12/3/12.
//
//

#import "cocos2d.h"
#import "Box2D.h"

@interface ScrapMetal : CCSprite
{
	b2Body *body_;	// strong ref
    
    b2Vec2 vector;
}

-(void) setPhysicsBody:(b2Body*)body;
-(void) tick;

@end