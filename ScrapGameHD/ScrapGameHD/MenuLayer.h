//
//  MenuLayer.h
//  ScrapGameHD
//
//  Created by Frits de Vos on 26-11-12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//


#import <GameKit/GameKit.h>

// When you import this file, you import all the cocos2d classes
#import "cocos2d.h"

// MenuLayer
@interface MenuLayer : CCLayer <GKAchievementViewControllerDelegate, GKLeaderboardViewControllerDelegate>
{


}

-(void) createMenu;

// returns a CCScene that contains the HelloWorldLayer as the only child
+(CCScene *) scene;

@end
