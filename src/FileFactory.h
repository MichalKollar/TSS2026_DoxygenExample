/**
 * @file FileFactory.h
 * @brief I/O abstraction (interface) for opening and saving text files.
 */

#pragma once
#include <QString>

 /**
  * @defgroup io I/O Layer
  * @brief Types used for loading and saving textual content.
  *
  * The I/O group contains interfaces and implementations responsible for
  * file access and encoding setup.
  */

namespace IO {
	/**
	 * @namespace IO
	 * @brief Namespace holding the I/O layer types (interfaces and implementations).
	 * @details
	 * Keeping I/O in a namespace clarifies ownership and simplifies cross-references
	 * (e.g., @ref IO::FileFactory, @ref IO::FileTxt).
	 */

	 /**
	* @class FileFactory
	* @ingroup io
	* @brief Abstract interface for text file operations.
	 * @details
	 * Implementations are expected to guarantee UTF-8 encoding by default.
	 *
	 * @see IO::FileTxt
	 */
	class FileFactory
	{
	public:
		/// Virtual destructor for safe polymorphic deletion.
		virtual ~FileFactory() = default;
		// [open]
		/**
		 * @brief Opens a file and reads its contents as text.
		 * @param[in] path Absolute or relative path to the file.
		 * @param[out] outText Text read from the file on success.
		 * @retval true The file was read successfully.
		 * @retval false The file could not be read. @p outText is unchanged.
		 * @see save()
		 */
		virtual bool open(const QString& path, QString& outText) = 0;
		// [open]

		/**
		 * @brief Saves text content to a file.
		 * @param[in] path Absolute or relative path to the file.
		 * @param[in] inText Text to be written to disk.
		 * @return @c true on success, @c false otherwise.
		 * @see open()
		 */
		virtual bool save(const QString& path, const QString& inText) = 0;
	};
} // namespace IO
