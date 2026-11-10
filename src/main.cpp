/**
 * @file main.cpp
 * @brief Application entry point.
 * @details
 * Creates a Qt application and displays the @ref DoxygenExample main window.
 * @see DoxygenExample
 */

#include "DoxygenExample.h"
#include <QtWidgets/QApplication>

/**
 * @brief Starts the editor and enters the Qt event loop.
 * @param[in] argc Number of command-line arguments.
 * @param[in,out] argv Command-line arguments, which Qt may modify.
 * @return Exit code of the Qt event loop.
 */
int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	DoxygenExample window;
	window.show();
	return app.exec();
}
