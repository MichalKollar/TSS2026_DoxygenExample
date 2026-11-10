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
	 * @see IO::FileFactory
	 */
	class FileTxt : public FileFactory {
	public:
		/// Constructs a text file handler.
		FileTxt() = default;
		/// Destroys the text file handler.
		~FileTxt() override = default;
		/// @copydoc FileFactory::open()
		bool open(const QString& path, QString& outText) override;
		/// @copydoc FileFactory::save()
		/// @attention If saving fails, the previous file contents are preserved.
		bool save(const QString& path, const QString& inText) override;
	private:
		QString text = ""; /*!< Last content processed by this instance.
							@deprecated This cache is kept only for demo purposes.
							Prefer returning data via parameters. */
	};
} // namespace IO
