/**
 * @file main.cpp
 * @brief Application entry point.
 * @details
 * Creates a Qt application and displays the @ref DoxygenExample main window.
 * @see DoxygenExample
 */

#include "DoxygenExample.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	DoxygenExample window;
	window.show();
	return app.exec();
}