#include "imageTools.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace imageTools {
	u_int32_t pngProcessor::bytesToLong(const unsigned char* bytes) {
		u_int32_t value = *reinterpret_cast<const u_int32_t*>(bytes);
		// clang-format off
        #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		    value = __builtin_bswap32(value);
        #endif
		// clang-format on
		return value;
	}

	void pngProcessor::load(std::string path, bool ignoreMagicNumber) {
		std::ifstream file(path, std::ios::binary);	 // Otwórz plik w trybie binarnym
		if (!file) {
			throw std::runtime_error("Can't open file: " + path);
		}

		// Pobierz rozmiar pliku
		file.seekg(0, std::ios::end);
		u_int64_t fileSize = static_cast<u_int64_t>(file.tellg());
		file.seekg(0, std::ios::beg);

		std::vector<u_char> buffer(fileSize);  // Stwórz bufor
		file.read(reinterpret_cast<char*>(buffer.data()), fileSize);

		if (!file) {
			throw std::runtime_error("Error reading the file.");
		}

		std::vector<u_char> magicNumber = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
		if (!ignoreMagicNumber && !std::equal(buffer.begin(), buffer.begin() + magicNumber.size(), magicNumber.begin())) {
			throw std::runtime_error("Magic number isn't valid");
		} else if (!ignoreMagicNumber) {
			file.seekg(8, std::ios::beg);
		}

		while (true) {
			u_char lengthBuffer[4];
			file.read(reinterpret_cast<char*>(lengthBuffer), 4);  // to sie kiedys na mnie zemści, rzutowanie wszystkiego za pomocą reinterpret
			u_int32_t length = bytesToLong(lengthBuffer);
			std::string chunkType(4, '\0');
			file.read(&chunkType[0], 4);
			u_char* data = new u_char[length];
			file.read(reinterpret_cast<char*>(data), length);
			file.seekg(4, std::ios::cur);  // pomiń crc
			std::cout << "Length: " << length << " Chunk type: " << chunkType << " Data: " << data << "\n";
			if (chunkType == "IEND") break;
		}
	}
}  // namespace imageTools