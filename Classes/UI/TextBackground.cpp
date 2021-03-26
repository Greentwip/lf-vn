/*#include "Debug\TestMacro.h"
#include "TextBackground.h"

bool TextBackground::onTouchBegan(Touch* pTouch, Event* pEvent)
{

	Vec2 touchLocation = pTouch->getLocation();

	auto t = this;
	if (t && t->isVisible() && getTextBoxState() == State::TEXTBOX_STATE_VISIBLE)
	{
		Vec2 local = t->convertToNodeSpace(touchLocation);
		Rect r = getTextBoxRect();
		r.origin = Vec2::ZERO;

		if (r.containsPoint(local))
		{
			return true;
		}
	}
	return false;


}

void TextBackground::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	if (_textDisplay->getDisplayState() == TextDisplay::State::STATE_RENDERING)
	{
		updateText();
	}
	else
	{
		EventCustom e("EVENT_SCRIPT_CONTINUE");
		e.setUserData(this);
		_eventDispatcher->dispatchEvent(&e);
	}
}
*/