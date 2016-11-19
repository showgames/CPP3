#include <iostream>
#include "Stage.hpp"
using namespace std;

int main(int argc, char* argv[]) {
	const char* stageData = "#########..p   ##oo    ##      #########";
	int sizeX = 8, sizeY = 5;

	Stage* stage = new Stage(stageData, sizeX, sizeY);
	
	while (true) {
		stage->draw();
		if (stage->hasCleared()) break;
		cout << "a:left s:right w:up z:down. command?" << endl;
		char input;
		cin >> input;
		stage->update(input);
	}
	cout << "Congratulation's! you won" << endl;

	while (true) {
		;
	}

	return 0;
}