#ifndef APP_DELEGATE_H  
#define APP_DELEGATE_H  

#include "cocos2d.h"  

// ί����
class AppDelegate : private cocos2d::Application {
public:

    virtual bool applicationDidFinishLaunching();

    virtual void applicationDidEnterBackground();

    virtual void applicationWillEnterForeground();
};

#endif