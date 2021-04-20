#include <iostream>
#include <algorithm>
#include <windows.h>
#include <iomanip>
#include "FilesManagment.h"
#include "StringManagment.h"
#include "Entertainment.h"

using namespace std;

int main()
{
	try
	{
		ent::ChangeColor(ent::red);

		vector<wstring> sixArts;
		vector<string> ext = { ".jpg", ".jpeg", ".png", ".mp4", ".gif", "jif" };
		fm::ReadDirectoryWS("", sixArts, ext);

		//cout << "1:";
		//copy(begin(sixArts), end(sixArts), ostream_iterator<wstring, wchar_t>(wcout, L"\n"));
		//cout << endl;
		if (sixArts.empty())
			throw fm::Error_t{ "NO FILES!" };

		auto remover = [](wstring ws)
		{
			if (ws[0] != L'.')
				return true;
			return false;
		};
		sixArts.erase(remove_if(begin(sixArts), end(sixArts), remover), end(sixArts));
		//cout << "2:";
		//copy(begin(sixArts), end(sixArts), ostream_iterator<wstring, wchar_t>(wcout, L"\n"));
		//cout << endl;
		if (sixArts.empty())
			throw fm::Error_t{ "NO FILES!" };

		const auto changer = [](wstring ws)
		{
			return ws.substr( ws.find_first_not_of('.') );
		};

		for (auto& sixArt : sixArts)
		{
			fm::HiddenFileW(sixArt, false);
			fm::RenameFileW(sixArt, changer(sixArt));
			ent::ChangeColor(ent::blue); cout << "FILE: " << setw(70) << sm::WSTS(sixArt);
			ent::ChangeColor(ent::lime); cout << "\tDONE" << endl;
		}

	}
	catch (fm::Error_t& e)
	{
		ent::ChangeColor(ent::red);
		cout << "Operation ended with error." << endl
			<< "\tCatched exception: fm::Error_t." << endl
			<< "\texception.what \"" << e.what << "\"" << endl << endl;

		system("pause");
		exit(2);
	}
	catch (...)
	{
		ent::ChangeColor(ent::red);
		cout << "Operation ended with error." << endl
			<< "\tUNKNOWN EXCEPTION." << endl;

		system("pause");
		exit(69);
	}

	ent::ChangeColor(ent::lime);		cout << "SUCCESS" << endl;
	system("pause");

	return 0;
}