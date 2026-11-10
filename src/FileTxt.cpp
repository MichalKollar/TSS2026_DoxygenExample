/**
 * @file FileTxt.cpp
 * @brief Definition of the plain-text I/O implementation.
 */

#include "FileTxt.h"
#include <QFile>
#include <QTextStream>

using namespace IO;

bool FileTxt::open(const QString& path, QString& outText) {
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return false;
	}
	QTextStream inputStream(&file);

	inputStream.setEncoding(QStringConverter::Utf8);

	outText = inputStream.readAll();
	text = outText;
	return true;
}

bool FileTxt::save(const QString& path, const QString& inText) {
	QFile file(path);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		return false;
	}
	QTextStream outputStream(&file);
	outputStream.setEncoding(QStringConverter::Utf8);

	outputStream << inText;
	text = inText;
	return true;
}