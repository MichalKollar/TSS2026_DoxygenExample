/**
 * @file FileTxt.h
 * @brief Plain-text implementation of @ref IO::FileFactory using Qt I/O.
 */

#pragma once
#include "FileFactory.h"

namespace IO {
	/**
	 * @class FileTxt
	 * @ingroup io
	 * @brief UTF-8 text reader/writer implementation.
	 *
	 * @details
	 * Uses @c QFile and @c QTextStream to read/write textual data in UTF-8.
	 *
	 * @since 1.0
	 * @see FileFactory
	 */
	class FileTxt : public FileFactory {
	public:
		FileTxt() = default;
		~FileTxt() override = default;
		/// @copydoc FileFactory::open()
		bool open(const QString& path, QString& outText) override;
		/// @copydoc FileFactory::save()
		bool save(const QString& path, const QString& inText) override;
	private:
		QString text = ""; /*!< Last content processed by this instance.
							@deprecated This cache is kept only for demo purposes.
							Prefer returning data via parameters. */
	};
} // namespace IO