//
//  ScrapMetal.h
//  ScrapGameHD
//
//  Created by CHRISTIAAN Rakowski on 12/3/12.
//
//

#import "PhysicsSprite.h"

@interface ScrapMetal : PhysicsSprite
{
    b2Vec2 vector;
}

-(void) tick;

@end