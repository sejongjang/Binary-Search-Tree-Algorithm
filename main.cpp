#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "BST.h"

using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

int main(int argc, char * argv[]) {

	VS_MEM_CHECK;

	if (argc < 3) {
		cout << "Please provide the name of input and output files" << endl;
		return 1;
	}

	ifstream in(argv[1]);
	if (!in) {
		return 2;
	}

	ofstream out(argv[2]);
	if (!out) {
		return 3;
	}

	int key, removeVal, findVal = -1;
	BST myTree;
	string command, temp, removeTemp;

	while (getline(in, command)) {
		if (command.find("Add") != string::npos) {
			stringstream sss(command);
			sss >> temp;
			sss >> key;	
			myTree.AddLeaf(key);
		}
		else if (command.find("PrintBST") != string::npos) {
			cout << "PrintBST ";
			myTree.toString();
		}
		else if(command.find("Remove") != string::npos){
			
			stringstream ss(command);
			ss >> removeTemp >> removeVal;
			myTree.RemoveNode(removeVal);
		}
		else if (command.find("Clear") != string::npos) {
			myTree.~BST();
		}
		else if (command.find("Find") != string::npos) {
			stringstream ss(command);
			ss >> temp >> findVal;
			cout << temp << " " << findVal << " ";
			myTree.FoundValue(findVal);
		}
		else if (command.find("Tree") != string::npos) {
			cout << "Tree: ";
			myTree.PrintInOrder();
			cout << endl;
		}
		else {

		}
	}

	system("pause");
	return 0;
}