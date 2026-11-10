/**
 * @file DoxygenExample.cpp
 * @brief Definition of the main window logic (menu actions and state updates).
 * @details
 * This file contains slot implementations and window title management for
 * the @ref DoxygenExample class.
 */

#include "DoxygenExample.h"
#include "FileTxt.h"
#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>

DoxygenExample::DoxygenExample(QWidget* parent)
	: QMainWindow(parent), file(std::make_unique<IO::FileTxt>())
{
	ui.setupUi(this);

	// Assign standard keyboard shortcuts.
	ui.actionOpen->setShortcut(QKeySequence::Open);
	ui.actionSave->setShortcut(QKeySequence::Save);

	// Mark the document as dirty whenever text changes.
	connect(ui.plainTextEdit, &QPlainTextEdit::textChanged, this, [this] {
		setTextChanged(true);
		});

	updateWindowTitle();
}

void DoxygenExample::setTextChanged(bool state)
{
	textChanged = state;
	updateWindowTitle();
}

void DoxygenExample::updateWindowTitle()
{
	QString name = currentPath.isEmpty() ? "untitled.txt" : currentPath;
	if (textChanged) name += "*";
	setWindowTitle(QString("%1").arg(name));
}

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

	QString text;
	if (!file->open(path, text)) {
		QMessageBox::warning(this, "Error", "Cannot open the file.");
		return;
	}

	ui.plainTextEdit->setPlainText(text);

	currentPath = path;
	setTextChanged(false);
}

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

	const QString text = ui.plainTextEdit->toPlainText();
	if (!file->save(path, text)) {
		QMessageBox::warning(this, "Error", "Cannot save the file.");
		return;
	}

	currentPath = path;
	setTextChanged(false);
}

void DoxygenExample::on_actionExit_triggered()
{
	close();
}

void DoxygenExample::closeEvent(QCloseEvent* event)
{
	if (textChanged) {
		const auto response = QMessageBox::question(this, "Unsaved changes", "Save before exit?",
			QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Cancel);
		if (response == QMessageBox::Yes) {
			on_actionSave_triggered();
		}
		if (response != QMessageBox::No && textChanged) {
			event->ignore();
			return;
		}
	}
	QMainWindow::closeEvent(event);
}
