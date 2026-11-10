/**
 * @file FileTxt.cpp
 * @brief Definition of the plain-text I/O implementation.
 */

#include "FileTxt.h"
#include <QFile>
#include <QSaveFile>
#include <QTextStream>

using namespace IO;

bool FileTxt::open(const QString& path, QString& outText) {
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return false;
	}
	QTextStream inputStream(&file);

	inputStream.setEncoding(QStringConverter::Utf8);

	const QString contents = inputStream.readAll();
	if (inputStream.status() != QTextStream::Ok || file.error() != QFileDevice::NoError) {
		return false;
	}

	outText = contents;
	text = contents;
	return true;
}

bool FileTxt::save(const QString& path, const QString& inText) {
	QSaveFile file(path);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		return false;
	}
	QTextStream outputStream(&file);
	outputStream.setEncoding(QStringConverter::Utf8);

	outputStream << inText;
	outputStream.flush();
	if (outputStream.status() != QTextStream::Ok || !file.commit()) {
		return false;
	}

	text = inText;
	return true;
}
