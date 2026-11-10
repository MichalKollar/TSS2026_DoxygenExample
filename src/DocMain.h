/**
 * @file DocMain.h
 * @brief Documentation-only file that defines the Doxygen main page.
 *
 * This file is not compiled. It only contains documentation blocks that form
 * the main page and general project overview.
 */

 /**
  * @mainpage Mini Text Editor – Doxygen Showcase
  *
  * @image html ui_overview.png "Main window of the text editor" width=600px
  *
  * @section intro Introduction
  *
  * The **Mini Text Editor** is a small Qt-based application used as an example
  * project for learning how to document source code with **Doxygen**.
  * It demonstrates:
  * - Class-level documentation (`@class`, `@ingroup`)
  * - File-level headers (`@file`)
  * - Function and parameter comments (`@param`, `@return`)
  * - Cross-references (`@ref`, `@link`), source excerpts (`@snippet`) and diagrams
  *
  * @par Technologies used
  * - C++17 and Qt 6 Widgets
  * - Doxygen for documentation generation
  * - Graphviz for UML diagrams
  *
  * @section structure Project structure
  * The project is divided into two logical modules (Doxygen groups):
  * - @ref ui – user interface (Qt main window, menus, and actions)
  * - @ref io – input/output layer (file handling and encoding)
  *
  * @section usage How to generate the documentation
  * 1. Extract the ZIP and open PowerShell in the project folder.
  * 2. Run the bundled Windows version of Doxygen:
  *    \code
  *    cd docs
  *    ..\tools\doxygen\doxygen.exe Doxyfile
  *    \endcode
  * 3. Open `docs/out/html/index.html` in your browser.
  *
  * @subsection example_code Example of code documentation
  * This excerpt comes from @ref FileFactory.h and shows how
  * @ref IO::FileFactory::open() documents parameters and return values.
  * @snippet FileFactory.h open
  * The @link IO::FileTxt::open() implementation @endlink reuses that description
  * through `@copydoc`.
  *
  * @section resources Useful resources
  * - https://www.doxygen.nl/index.html Official Doxygen homepage
  * - https://graphviz.org Graphviz – tool for diagrams
  * - https://doc.qt.io Qt official documentation
  *
  * @note
  * The image shown above is stored in `docs/images/ui_overview.png`.
  * To make sure Doxygen finds it, set in your Doxyfile:
  * \code
  * IMAGE_PATH = images
  * \endcode
  *
  */
