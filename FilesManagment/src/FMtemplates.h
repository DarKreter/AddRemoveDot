#ifndef FMTEMPLATES_H
#define FMTEMPLATES_H

template<typename T>
inline void ReadDirectory(const std::string name, std::vector<T>& v, const std::vector<std::string>& filters, bool dir, bool fullPath)
{
	//std::cout << "name = " << name << std::endl;

	std::vector<std::string> tempFiles;
	std::vector<std::string> tempDir;

	std::string pattern(name);
	pattern.append("*");
	WIN32_FIND_DATA data;
	HANDLE hFind;

	std::wstring stemp = std::wstring(pattern.begin(), pattern.end());
	LPCWSTR sw = stemp.c_str();

	if ((hFind = FindFirstFile(sw, &data)) != INVALID_HANDLE_VALUE) {
		do {

			if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (dir)
				{
					std::string temppp{ sm::WSTS(data.cFileName) };

					if (fullPath)
						tempDir.push_back(name + temppp);
					else
						tempDir.push_back(temppp);
				}
			}
			else
			{
				std::string temppp{ sm::WSTS(data.cFileName) };

				if (fullPath)
					tempFiles.push_back(name + temppp);
				else
					tempFiles.push_back(temppp);
			}

		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}

	auto RemoverFiles([&filters](std::string t)
		{
			return FilesFilter(t, filters);
		}); //Lambda ktora zwroci true dla rozszerzen spoza puli

	auto RemoverDir([](std::string t)
		{
			return (t == "." || t == "..");
		}); //Lambda ktora zwroci true dla kropek

	remove_copy_if(begin(tempFiles), end(tempFiles), back_inserter(v), RemoverFiles);
	remove_copy_if(begin(tempDir), end(tempDir), back_inserter(v), RemoverDir);

}


template<typename T>
void ReadDirectoryWS(const std::string name, std::vector<T>& v, const std::vector<std::string>& filters, bool dir, bool fullPath)
{
	//std::cout << "name = " << name << std::endl;

	std::vector<std::wstring> tempFiles;
	std::vector<std::wstring> tempDir;

	std::string pattern(name);
	pattern.append("*");
	WIN32_FIND_DATA data;
	HANDLE hFind;

	std::wstring stemp = std::wstring(pattern.begin(), pattern.end());
	LPCWSTR sw = stemp.c_str();

	if ((hFind = FindFirstFile(sw, &data)) != INVALID_HANDLE_VALUE) {
		do {

			if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (dir)
				{
					std::wstring wsTmp(name.begin(), name.end());

					if (fullPath)
						tempDir.push_back(wsTmp + data.cFileName);
					else
						tempDir.push_back(data.cFileName);
				}
			}
			else
			{
				std::wstring wsTmp(name.begin(), name.end());

				if (fullPath)
					tempFiles.push_back(wsTmp + data.cFileName);
				else
					tempFiles.push_back(data.cFileName);
			}

		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}

	auto RemoverFiles([&filters](std::wstring t)
		{
			return FilesFilter(t, filters);
		}); //Lambda ktora zwroci true dla rozszerzen spoza puli

	auto RemoverDir([](std::wstring t)
		{
			return (t == L"." || t == L"..");
		}); //Lambda ktora zwroci true dla kropek

	remove_copy_if(begin(tempFiles), end(tempFiles), back_inserter(v), RemoverFiles);
	remove_copy_if(begin(tempDir), end(tempDir), back_inserter(v), RemoverDir);

}

#endif //FMTEMPLATES_H