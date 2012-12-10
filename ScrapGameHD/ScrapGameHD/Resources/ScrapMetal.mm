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

-(void) setPhysicsBody:(b2Body *)body
{
	body_ = body;
}

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

// returns the transform matrix according the Chipmunk Body values
-(CGAffineTransform) nodeToParentTransform
{
	b2Vec2 pos = body_->GetPosition();
	
	float x = pos.x;
	float y = pos.y;
	
	if ( ignoreAnchorPointForPosition_ ) {
		x += anchorPointInPoints_.x;
		y += anchorPointInPoints_.y;
	}
	
	// Make matrix
	float radians = body_->GetAngle();
	float c = cosf(radians);
	float s = sinf(radians);
	
	if( ! CGPointEqualToPoint(anchorPointInPoints_, CGPointZero) ){
		x += c * -anchorPointInPoints_.x + -s * -anchorPointInPoints_.y;
		y += s * -anchorPointInPoints_.x + c *  -anchorPointInPoints_.y;
	}
	
	// Rot, Translate Matrix
	transform_ = CGAffineTransformMake( c,  s,
									   -s,	c,
									   x,	y );
	
	return transform_;
}

-(void) dealloc
{
	[super dealloc];
}

@end
