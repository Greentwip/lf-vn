#include "TitleScene.h"

#include "ui\CocosGUI.h"

#include "Debug/TestScene.h"

USING_NS_CC;

Scene* Title::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Title::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Title::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /*auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));*/

    // add the label as a child to this layer
    //this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto background = Sprite::create("image/Title/background.png");

    // position the sprite on the center of the screen
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    auto logo = Sprite::create("image/Title/logo.png");

    // position the sprite on the center of the screen
    logo->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 1.5f + origin.y));


    // add the sprite as a child to this layer
    this->addChild(background);
    this->addChild(logo);

    auto buttonBackground = Sprite::create("image/Title/button.png");
    //buttonBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 1.5 + origin.y));
    buttonBackground->setScale(1.25);

    auto startButton = ui::Button::create("image/Title/button.png");
    auto loadButton = ui::Button::create("image/Title/button.png");
    auto optionsButton = ui::Button::create("image/Title/button.png");
    auto exitButton = ui::Button::create("image/Title/button.png");

    startButton->addClickEventListener(CC_CALLBACK_1(Title::startGameCallback, this));
    exitButton->addClickEventListener(CC_CALLBACK_1(Title::menuCloseCallback, this));

    startButton->setAnchorPoint(Vec2(0.5, 0.5));
    loadButton->setAnchorPoint(Vec2(0.5, 0.5));
    optionsButton->setAnchorPoint(Vec2(0.5, 0.5));
    exitButton->setAnchorPoint(Vec2(0.5, 0.5));

    startButton->setScale(1, 0.90f);
    loadButton->setScale(1, 0.90f);
    optionsButton->setScale(1, 0.90f);
    exitButton->setScale(1, 0.90f);

    startButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 3.25f));
    
    loadButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, 
                                 startButton->getPosition().y - (startButton->getContentSize().height) + 8));
    
    optionsButton->setPosition(Vec2(visibleSize.width / 2 + origin.x,
        loadButton->getPosition().y - (loadButton->getContentSize().height) + 8));

    exitButton->setPosition(Vec2(visibleSize.width / 2 + origin.x,
        optionsButton->getPosition().y - (optionsButton->getContentSize().height) + 8));

    auto start = Sprite::create("image/Title/start.png");
    auto load = Sprite::create("image/Title/load.png");
    auto options = Sprite::create("image/Title/options.png");
    auto exit = Sprite::create("image/Title/exit.png");

    start->setScale(0.50f);
    load->setScale(0.50f);
    options->setScale(0.50f);
    exit->setScale(0.50f);


    start->setPosition(Vec2(startButton->getContentSize().width / 2, startButton->getContentSize().height / 2));
    load->setPosition(Vec2(startButton->getContentSize().width / 2, startButton->getContentSize().height / 2));
    options->setPosition(Vec2(startButton->getContentSize().width / 2, startButton->getContentSize().height / 2));
    exit->setPosition(Vec2(startButton->getContentSize().width / 2, startButton->getContentSize().height / 2));

    startButton->addChild(start);
    loadButton->addChild(load);
    optionsButton->addChild(options);
    exitButton->addChild(exit);

    this->addChild(startButton);
    this->addChild(loadButton);
    this->addChild(optionsButton);
    this->addChild(exitButton);

    return true;
}

void Title::startGameCallback(Ref* pSender)
{
    auto testScene = SNovel::TestScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(1, testScene, Color3B(0, 0, 0)));
}

void Title::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
