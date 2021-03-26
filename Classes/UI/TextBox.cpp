#include "TextBox.h"


#if defined(TEST_TEXTBOX) \

namespace SNovel
{
	TextBox::TextBox(bool useEffect)
	{
		auto text = ui::Text::create();
		text->retain();
		TextBox(text, nullptr, nullptr, useEffect);
	}

	TextBox::TextBox(ui::Text* text, Sprite* background, Sprite* simpleBackground, bool useEffect)
		: _uiText(text)
		, UseEffect(useEffect)
	{
		_textDisplay = new TextDisplay(text);
		_background = background;
		_simpleBackground = simpleBackground;

		auto touch = EventListenerTouchOneByOne::create();
		touch->onTouchBegan = CC_CALLBACK_2(TextBox::onTouchBegan, this);
		touch->onTouchEnded = CC_CALLBACK_2(TextBox::onTouchEnded, this);
		touch->setSwallowTouches(true);

		Director::getInstance()->
		getEventDispatcher()->
		addEventListenerWithFixedPriority(touch, 1);

	}

	TextBox::~TextBox()
	{
		_uiText->release();
	}

	bool TextBox::onTouchBegan(Touch* pTouch, Event* pEvent)
	{
		Vec2 touchLocation = pTouch->getLocation();

		auto t = _uiText;
		if (t && t->isVisible() && _textDisplay->isWaiting())
		{
			Vec2 local = t->convertToNodeSpace(touchLocation);
			Rect r = 
				Rect(0, 
					 0, 
					_uiText->getTextAreaSize().width, 
					_uiText->getTextAreaSize().height);

			r.origin = Vec2::ZERO;

			if (r.containsPoint(local))
			{
				return true;
			}
		}
		return false;


	}

	void TextBox::onTouchEnded(Touch* pTouch, Event* pEvent)
	{
		if (_textDisplay->isWaiting())
		{
			EventCustom e("EVENT_SCRIPT_CONTINUE");
			e.setUserData(this);
			Director::getInstance()->
				getEventDispatcher()->dispatchEvent(&e);
		}
	}

	void TextBox::showTextBox()
	{
		if (_background) {
			_background->setVisible(true);
		}

		if (_simpleBackground) {
			_simpleBackground->setVisible(true);
		}

		_uiText->setVisible(true);
	}

	void TextBox::hideTextBox()
	{
		if (_background) {
			_background->setVisible(false);
		}

		if (_simpleBackground) {
			_simpleBackground->setVisible(false);
		}

		_uiText->setVisible(false);
	}

	void TextBox::showBackground() 
	{
		if (_background) {
			_background->setVisible(true);
		}
	}

	void TextBox::hideBackground() 
	{
		if (_background) {
			_background->setVisible(false);
		}
	}

	void TextBox::setText(const std::string& text)
	{
		_newText = text;
		updateText();
	}


	void TextBox::enterScene()
	{
		_uiText->setVisible(true);

		_isEnterScene = true;
	}

	void TextBox::updateText()
	{
		if (UseEffect)
		{
			displayText();
		}
		else
		{
			_shownText += _newText;
			_uiText->setString(_shownText);
		}
	}

	void TextBox::displayText()
	{
		if (_textDisplay->isWaiting())
		{
			_textDisplay->startEffect(_shownText, _newText, EffectDuration);
			_shownText += _newText;
		}
		else
		{
			CCLOG("Display Text Error");
		}
	}
	void TextBox::onClick()
	{
		if (_textDisplay->isWaiting())
		{
			EventCustom e("EVENT_SCRIPT_CONTINUE");
			CCLOG("On Continiue");
			Director::getInstance()->getEventDispatcher()->dispatchEvent(&e);
		}
		else if (_textDisplay->isRendering())
		{
			_uiText->setString(_shownText + _newText);
		}
	}

	void TextBox::clearMessage()
	{
		_shownText.clear();
	}

	void TextBox::reline()
	{
		_shownText.push_back('\n');
		_uiText->setString(_shownText);
	}
	/*
	TextBoxLayerColor* TextBoxLayerColor::create(const Color4B& color,
												 const Size& textSize,
												 const Size& backgroundSize,
												 const TTFConfig& textConfig,
												 bool useEffect)
	{
		auto pRet = new TextBoxLayerColor();
		if (pRet && pRet->init(color, textSize, backgroundSize, textConfig, useEffect))
		{
			pRet->autorelease();
		}
		else
		{
			delete pRet;
			pRet = nullptr;
		}
		return pRet;
	}
	bool TextBoxLayerColor::init(const Color4B& color,
								 const Size& textSize,
								 const Size& backgroundSize,
								 const TTFConfig& textConfig,
								 bool useEffect)
	{
		bool bRet = false;
		do
		{
			CC_BREAK_IF(!TextBox::init(textSize, textConfig, useEffect));

			_textboxBackground = LayerColor::create(color);
			_textboxBackground->setContentSize(backgroundSize);
			_textboxBackground->setAnchorPoint(Point(0, 0));
			_textboxBackground->setPosition(Point(0, 0));
			_textboxBackground->setVisible(true);
			this->addChild(_textboxBackground, -1);

			//setContentSize() 在创建textDiaplay之前
			setContentSize(backgroundSize);
			bRet = true;
		} while (0);
		return bRet;
	}

	Rect TextBoxLayerColor::getTextBoxRect()
	{
		auto pos = _textboxBackground->convertToWorldSpace(_textboxBackground->getPosition());
		auto size = _textboxBackground->getContentSize();
		auto anthor = _textboxBackground->getAnchorPoint();

		return Rect(pos.x - size.width * anthor.x,
					pos.y - size.height * anthor.y,
					size.width,
					size.height);
	}

	void TextBoxLayerColor::setContentSize(const Size& size)
	{
		TextBox::setContentSize(size);
		//_textboxBackground->setContentSize(size);
	}

	void TextBoxLayerColor::onEnter()
	{
		TextBox::onEnter();
		//setContentSize(_textboxBackground->getContentSize());
	}

	TextBoxSprite* TextBoxSprite::create(const char* filePath,
										 const Size& textSize,
										 const Size& backgroundSize,
										 const TTFConfig& textConfig,
										 bool useEffect)
	{
		auto pRet = new TextBoxSprite();
		if (pRet && pRet->init(filePath, textSize, backgroundSize, textConfig, true))
		{
			pRet->autorelease();
		}
		else
		{
			delete pRet;
			pRet = nullptr;
		}
		return pRet;
	}

	bool TextBoxSprite::init(const char* filePath,
							 const Size& textSize,
							 const Size& backgroundSize,
							 const TTFConfig& textConfig,
							 bool useEffect)
	{
		bool bRet = false;
		do
		{
			CC_BREAK_IF(!TextBox::init(textSize, textConfig, useEffect));

			_textboxBackground = Sprite::create(filePath);
			_textboxBackground->setContentSize(backgroundSize);
			_textboxBackground->setAnchorPoint(Point(0, 0));
			_textboxBackground->setPosition(Point(0, 0));
			_textboxBackground->setVisible(false);
			this->addChild(_textboxBackground);

			//setContentSize() 在创建textDiaplay之前
			setContentSize(_textboxBackground->getContentSize());
			bRet = true;
		} while (0);
		return bRet;
	}

	Rect TextBoxSprite::getTextBoxRect()
	{
		auto pos = _textboxBackground->convertToWorldSpace(_textboxBackground->getPosition());
		auto size = _textboxBackground->getContentSize();
		auto anthor = _textboxBackground->getAnchorPoint();

		return Rect(pos.x - size.width * anthor.x,
					pos.y - size.height * anthor.y,
					size.width,
					size.height);
	}

	void TextBoxSprite::setContentSize(const Size& size)
	{
		TextBox::setContentSize(size);
		_textboxBackground->setContentSize(size);
	}

	void TextBoxSprite::onEnter()
	{
		TextBox::onEnter();
		setContentSize(_textboxBackground->getContentSize());
	}*/
}
#endif