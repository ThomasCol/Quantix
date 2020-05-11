#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <vector>
#include <Inspector.h>

class Console
{
public:
	Console();
	~Console();

	void			Init(Quantix::Core::Platform::Application* app);
	void			PrintLog();
	void			ConsoleUI();
	void			Update();

private:
	QXuint												_sizeLog;
	std::vector<bool>									_showTypeLog;
	std::vector<Quantix::Resources::Texture*>			_imgTypeLog;

};

#endif _CONSOLE_H_