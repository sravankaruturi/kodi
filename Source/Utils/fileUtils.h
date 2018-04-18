#pragma once

#include <string>

namespace kodi {

	namespace utils {

		class FileUtils {

		public:
			static std::string readFile(const char * _filePath) {

				// RT ante Read Text ani Text ayithe linelanu ekkada aapaalo thelusthundhi.
				// Shaderlu vaaduthunappudu line endings manaku chaala important.
				FILE * fp = fopen(_filePath, "rt");
				fseek(fp, 0, SEEK_END);
				// Entha podugundho choosuko
				unsigned long length = ftell(fp);
				char * data = new char[length + 1];
				// Idhi zero pettaali. Endhukante, ftell konchem ekkuva chars isthundhi. Dheenitho, manam file ending cheppochchu.
				memset(data, 0, length + 1);
				fseek(fp, 0, SEEK_SET);
				fread(data, 1, length, fp);
				fclose(fp);

				std::string result(data);

				delete[] data;

				return result;

			}

		};

		

	}

}