#ifndef IMAGETOOLS_H
#define IMAGETOOLS_H

#include <fstream>
#include <string>
#include <vector>

namespace imageTools {
	class pngProcessor {
		protected:
			u_int32_t width;
			u_int32_t height;
			u_char bitDepth;
			u_char colorType;
			bool compressionMethod;
			bool filterMethod;
			bool interlaceMethod;

			u_int32_t bytesToLong(const unsigned char* bytes);

		public:
			/**
			 * @brief function for development
			 */
			std::string debug();
			/**
			 * @brief loads image
			 * @param path path to image
			 */
			void load(std::string path, bool ignoreMagicNumber);
	};
}  // namespace imageTools

#endif