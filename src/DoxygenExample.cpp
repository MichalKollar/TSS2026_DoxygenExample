/**
 * @file DoxygenExample.cpp
 * @brief Definition of the main window logic (menu actions and state updates).
 * @details
 * This file contains slot implementations and window title management for
 * the @ref DoxygenExample class.
 */

#include "DoxygenExample.h"
#include <QMessageBox>
#include <QFileDialog>

DoxygenExample::DoxygenExample(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// Using Qt-style "brief" comments:
	//! Assign standard keyboard shortcuts for convenience.
	ui.actionOpen->setShortcut(QKeySequence::Open);
	ui.actionSave->setShortcut(QKeySequence::Save);

	// Mark the document as dirty whenever text changes.
	connect(ui.plainTextEdit, &QPlainTextEdit::textChanged, this, [this] {
		setTextChanged(true);
		});

	updateWindowTitle();
}

/**
 * @brief Sets the dirty flag and updates the title if it changed.
 */
void DoxygenExample::setTextChanged(bool state)
{
	if (textChanged == state) {
		return;
	}

	textChanged = state;
	updateWindowTitle();
}

/**
 * @brief Builds the window title from current file name and the dirty flag.
 * @post Title includes '*' when @ref DoxygenExample::textChanged is true.
 */
void DoxygenExample::updateWindowTitle()
{
	QString name = currentPath.isEmpty() ? "untitled.txt" : currentPath;
	if (textChanged) name += "*";
	setWindowTitle(QString("%1").arg(name));
}

/**
 * @brief Slot: "File - Open".
 * @details
 * Prompts the user for a file path, loads the text via @ref IO::FileFactory,
 * and applies it to the central editor.
 * @warning Discards current changes if the user confirms.
 * @todo Validate file size before loading to prevent very large allocations.
 */
void DoxygenExample::on_actionOpen_triggered()
{
	if (textChanged) {
		auto response = QMessageBox::question(this, "Unsaved changes", "Discard current changes?");
		if (response != QMessageBox::Yes) {
			return;
		}
	}

	const QString path = QFileDialog::getOpenFileName(
		this, "Open text file", QString(), "Text files (*.txt);;All files (*.*)"
	);

	if (path.isEmpty()) {
		return;
	}

	if (file != nullptr) {
		delete file;
	}
	file = new IO::FileTxt();

	QString text;
	if (!file->open(path, text)) {
		QMessageBox::warning(this, "Error", "Cannot open the file.");
		return;
	}

	ui.plainTextEdit->setPlainText(text);

	currentPath = path;
	setTextChanged(false);
}

/**
 * @brief Slot: "File - Save".
 * @details
 * Saves the current content to @ref DoxygenExample::currentPath. If the path is empty,
 * a "Save As" dialog is displayed first.
 * @note Ensures UTF-8 encoding through the I/O layer.
 */
void DoxygenExample::on_actionSave_triggered()
{
	QString path = currentPath;
	if (path.isEmpty()) {
		path = QFileDialog::getSaveFileName(
			this, "Save as", "untitled.txt", "Text files (*.txt)"
		);
		if (path.isEmpty()) {
			return;
		}
	}

	if (file == nullptr) {
		file = new IO::FileTxt();
	}

	const QString text = ui.plainTextEdit->toPlainText();
	if (!file->save(path, text)) {
		QMessageBox::warning(this, "Error", "Cannot save the file.");
		return;
	}

	currentPath = path;
	setTextChanged(false);
}

/**
 * @brief Slot: "File - Exit".
 * @details
 * Asks to save the document if there are unsaved changes and then closes the window.
 */
void DoxygenExample::on_actionExit_triggered()
{
	if (textChanged) {
		auto r = QMessageBox::question(this, "Unsaved changes", "Save before exit?");
		if (r == QMessageBox::Yes) {
			on_actionSave_triggered();
			if (textChanged) {
				return;
			}
		}
		else if (r != QMessageBox::No) {
			return;
		}
	}
	close();
}