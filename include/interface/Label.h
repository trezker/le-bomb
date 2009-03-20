#ifndef interface_Label_h
#define interface_Label_h

#include "interface/Widget.h"
#include <string>

namespace interface
{

class Label: public Widget
{
public:
	Label();
	virtual Widget* Clone();
	virtual void Render();
	
	void Set_text(const std::string& t);
	void Set_alignment(HAlignment a);
	void Set_vertical_alignment(VAlignment a);
private:
	std::string text;
	HAlignment halignment;
	VAlignment valignment;
};

}

#endif
