#ifndef TEXTBUTTON
#define TEXTBUTTON

class TextButton
{
public:
	TextButton();
	~TextButton();



protected:
	std::string _plasholder;
	std::string _text;
	int maxLength;
	bool fullInteger;
};

#endif // !TEXTBUTTON