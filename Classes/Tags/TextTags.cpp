#include "TextTags.h"

namespace SNovel
{
	TagRegitser<RTag> _rTag("reline");
	TagRegitser<PTag> _pTag("static_print");
	TagRegitser<CmTag> _cmTag("clear_message");
	TagRegitser<CnTag> _cnTag("clear_name");
	TagRegitser<LTag> _lTag("pause");
	TagRegitser<CurrentTag> _currentTag("current");
	TagRegitser<SetnameTag> _setnameTag("setname");
	TagRegitser<PrintTag> _printTag("streamed_print");
}