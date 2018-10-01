// FileSystemComponent.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "stdafx.h"
#include "FileSystemFacade.h"
#include "FileSystemException.h"

using namespace filesystem;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	try {
		FileSystemFacade * dm = FileSystemFacade::INSTANCE();
		dm->addToRegisterFile("mainregister.txt");
		cout << dm->getValueInResource("common", "width") << "\n";
		cout << dm->getValueInFile("common.txt", "height") << "\n";
		dm->setValueInResource("common", "width", "1024");
		dm->setValueInResource("common", "height", "960");
		dm->saveResource("common");

		cout << "Int: " << dm->getIntInResource("common", "width") << "\n";
		cout << "Float: " << dm->getFloatInResource("common", "width") << "\n";
	} catch (FileSystemException ex) {
		cout << ex.getMessage();
	} catch (FileSystemException * ex) {
		cout << ex->getMessage();
	} catch (...) {
		cout << "unknown";
	}
	char ch;
	cin >> ch;
	return 0;
}

