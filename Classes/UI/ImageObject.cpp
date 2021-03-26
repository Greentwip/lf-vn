#include "ImageObject.h"

namespace SNovel
{
	ImageInfo::ImageInfo(ValueMap& param)
	{
		if (param.find("name") != param.end())
		{
			Name = param["name"].asString();
		}
		if (param.find("path") != param.end())
		{
			Path = param["path"].asString();
		}
		if (param.find("show") != param.end())
		{
			Show = param["show"].asBool();
		}
		if (param.find("fadeTime") != param.end())
		{
			Fadetime = param["fadeTime"].asFloat();
		}
		if (param.find("root") != param.end())
		{
			Root = param["root"].asString();
		}
		if (param.find("scale") != param.end())
		{
			Scale = param["scale"].asFloat();
		}
	}

	ImageObject::ImageObject(ImageInfo& info)
		: _info(info)
	{
		_image = Sprite::create(info.Path);

		/*auto imageSize = _image->getContentSize();

		auto windowSize = Director::getInstance()->getWinSize();

		auto imageRatio = imageSize.width / imageSize.height;
		auto windowRatio = windowSize.width / windowSize.height;

		_image->setScale(imageRatio / windowRatio);*/

		_image->retain();
		
		if (_image == nullptr)
		{
			CCLOG("can not find image:%s", info.Path);
		}

	}

	ImageObject::~ImageObject()
	{
		_image->release();
	}

	void ImageObject::fadeIn(float fadetime)
	{
		_image->setOpacity(0);

		auto alpha = FadeIn::create(fadetime); 
		
		if (_onAnimationFinish != nullptr)
		{
			auto seq = Sequence::createWithTwoActions(alpha, CallFunc::create(_onAnimationFinish));
			_image->runAction(seq);
		}
		_image->runAction(alpha);
	}

	void ImageObject::fadeOut(float fadetime)
	{
		auto alpha = FadeOut::create(fadetime);
		if (_onAnimationFinish != nullptr)
		{
			auto seq = Sequence::createWithTwoActions(alpha, CallFunc::create(_onAnimationFinish));
			_image->runAction(seq);
		}
		_image->runAction(alpha);
	}

	void ImageObject::move(Point& to, float duration)
	{
		Size winSize = Director::getInstance()->getWinSize();

		auto projectedTo = Point((int)(winSize.width * to.x), (int)(winSize.height * to.y));
		auto action = MoveTo::create(duration, projectedTo);
		auto seq = Sequence::createWithTwoActions(action, CallFunc::create(_onAnimationFinish));
		_image->runAction(seq);
	}

	void ImageObject::setPosition(const Point& pos)
	{
		Size winSize = Director::getInstance()->getWinSize();

		auto projectedTo = Point((int)(winSize.width * pos.x), (int)(winSize.height * pos.y));
		_image->setPosition(projectedTo);
	}
}