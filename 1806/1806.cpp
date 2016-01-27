//============================================================================
// Name        : 1806.cpp
// Author      : jglara
// Version     :
// Copyright   :
// Description : http://poj.org/problem?id=1806
//============================================================================

#include <iostream>
#include <map>
#include <stdlib.h>

unsigned int manhattan_distance(unsigned int slice, unsigned int row, unsigned int col, unsigned int center)
{
	//std::cout << "p: " << center << " s: "<< slice << " r: " << row << " c: " << col;
	unsigned int distance = abs(row - center) + abs(col - center) + abs(slice - center);
	//std::cout << ". distance: " << distance << std::endl;

	return distance;
}

int main(int argc, char *argv[]) {
	unsigned int numScenarios(0);


	std::cin >> numScenarios;
	unsigned int scenario(0);

	while (std::cin && ++scenario <= numScenarios) {
		unsigned int petrolUnits(0);
		std::cin >> petrolUnits;

		unsigned int mapSize = 2 * petrolUnits + 1;

		std::cout << "Scenario #" << scenario << ":" << std::endl;


		/// print each scenario
		for (unsigned int slice =0; slice < mapSize; ++slice) {

			std::cout << "slice #" << slice+1 << ":" << std::endl;
			for (unsigned int row =0; row < mapSize; ++row) {
				for (unsigned int col =0; col < mapSize; ++col) {
					unsigned int distance = manhattan_distance(slice,row,col,petrolUnits);

					if (distance <= petrolUnits) {
						std::cout << static_cast<char>('0' + distance);
					} else {
						std::cout << '.';
					}
				}
				std::cout << std::endl;

			}

		}
		std::cout << std::endl;

	}


}
