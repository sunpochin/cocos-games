/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hi I'm a good kitty", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        // label->setPosition(Vec2(origin.x + visibleSize.width/2,
        //                         origin.y + visibleSize.height - label->getContentSize().height));
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                visibleSize.height/2 - origin.y ));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    // auto sprite = Sprite::create("cat-1.jpg");
    if (sprite == nullptr)
    {
        problemLoading("'cat-1.jpg'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }

    myCatSprite2 = Sprite::create("cat-4.jpg");
    // myCatSprite2->setPosition( 
    //     Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2  + origin.y)
    // );
    myCatSprite2->setPosition( 
        Point(visibleSize.width / 2, visibleSize.height / 2  + origin.y)
    );
    this->addChild(myCatSprite2);

    // auto action = MoveBy::create(3, Point(100, 0));
    // myCatSprite2->runAction(action);

    // action = MoveTo::create(3, Point(100, 300));
    // myCatSprite2->runAction(action);


    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // auto listener = EventListenerTouchAllAtOnce::create();
    // listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
    // // listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
    // // listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);
    // _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    return true;
}


bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    CCLOG("onTouchBegan x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);

    // auto action = MoveTo::create(5, 
    //     Point(touch->getLocation().x, touch->getLocation().y));
    auto action = JumpTo::create(3, Point(touch->getLocation().x, touch->getLocation().y), 10, 6);
    myCatSprite2->runAction(action);

    return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
    // CCLOG("onTouch Moved x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);

    // auto action = MoveTo::create(3, 
    //     Point(touch->getLocation().x, touch->getLocation().y));
    // myCatSprite2->runAction(action);

}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{

}


// void HelloWorld::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {
//     CCLOG("onTouchesBegan");
//     // auto action = MoveTo::create(5, 
//     //     Point(touches->getLocation().x, touches->getLocation().y));
//     // myCatSprite2->runAction(action);
// }


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
