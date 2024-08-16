#include <string>
#include <format>
#include <iostream>
#include <map>
#include "tinyxml2.h"

using std::cout;
using std::endl;
using namespace tinyxml2;

int main() {
	struct capability
	{
		std::map<std::string, int> available_values;
	};
	std::map<std::string, capability> collectedCapabilities;

	std::string g = "gosho";
	std::string poss = "123";

	collectedCapabilities[g].available_values[poss]++;

	cout << collectedCapabilities[g].available_values[poss];
}

