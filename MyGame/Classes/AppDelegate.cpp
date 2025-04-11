#include "AppDelegate.h"  
#include "controllers/GameController.h"  

USING_NS_CC;


bool AppDelegate::applicationDidFinishLaunching() { 
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    if (!glview) {
        glview = GLViewImpl::createWithRect(u8"¿¨ÅÆÆ¥ÅäÓÎÏ·", cocos2d::Rect(0, 0, 1080, 2080), 0.5);
        director->setOpenGLView(glview);
    }

    glview->setDesignResolutionSize(1080, 2080, ResolutionPolicy::FIXED_WIDTH);

    director->setAnimationInterval(1.0f / 60);

    auto gameController = new GameController();
    gameController->startGame(1);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}