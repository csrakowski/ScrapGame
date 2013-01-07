//
//  ScrapMetal.m
//  ScrapGameHD
//
//  Created by CHRISTIAAN Rakowski on 12/3/12.
//
//

#import "ScrapMetal.h"

#pragma mark - ScrapMetal
@implementation ScrapMetal

-(void) tick
{

}

// this method will only get called if the sprite is batched.
// return YES if the physics values (angles, position ) changed
// If you return NO, then nodeToParentTransform won't be called.
-(BOOL) dirty
{
	//return YES;
    return (vector.Length() == 0);
}

@end
