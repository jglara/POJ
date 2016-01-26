//============================================================================
// Name        : 1806.cpp
// Author      : jglara
// Version     :
// Copyright   :
// Description : http://poj.org/problem?id=1806
//============================================================================

#include <iostream>
#include <map>

typedef std::map<int, std::map<int, std::map<int, char> > > manhattan_map_t;

void manhattan_walk(manhattan_map_t &manh, unsigned int petrolUnits,
			unsigned int slice, unsigned int row, unsigned int col)
{
/*	std::cout << "pu: " << petrolUnits
			<< "s: " << slice
			<< "r: " << row
			<< "c: " << col
			<< std::endl;*/

	if (petrolUnits == 0) return;

	if ((row - 1) >=0 &&  manh[slice][row-1][col] > -1) {
		manh[slice][row-1][col] = petrolUnits-1;
		manhattan_walk(manh, petrolUnits-1, slice, row-1, col);
	}
	if ((row + 1) < manh.size() &&  manh[slice][row+1][col] == -1) {
		manh[slice][row+1][col] = petrolUnits-1;
		manhattan_walk(manh, petrolUnits-1, slice, row+1, col);
	}

	if ((col - 1) >=0 &&  manh[slice][row][col-1] == -1) {
		manh[slice][row][col-1] = petrolUnits-1;
		manhattan_walk(manh, petrolUnits-1, slice, row, col-1);
	}
	if ((col + 1) < manh.size() &&  manh[slice][row][col+1] == -1) {
		manh[slice][row][col+1] = petrolUnits-1;
		manhattan_walk(manh, petrolUnits-1, slice, row, col+1);
	}
	if ((slice - 1) >=0 &&  manh[slice-1][row][col] == -1) {
		manh[slice-1][row][col] = petrolUnits-1;
		manhattan_walk(manh, petrolUnits-1, slice-1, row, col);
	}
	if ((slice + 1) < manh.size() &&  manh[slice+1][row][col] == -1) {
		manh[slice+1][row][col] = petrolUnits-1;
		manhattan_walk(manh, petrolUnits-1, slice+1, row, col);
	}

	return;

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

		manhattan_map_t manh; // manhattan map

		// init map
		for (unsigned int i=0; i<mapSize;i++){
			for (unsigned int j=0; j<mapSize;j++){
				for (unsigned int k=0; k<mapSize;k++){
					manh[i][j][k] = -1;
				}
			}
		}
		manh[petrolUnits] [petrolUnits] [petrolUnits] = petrolUnits;
		manhattan_walk(manh, petrolUnits, petrolUnits, petrolUnits, petrolUnits);

		/// print each scenario
		for (unsigned int slice =0; slice < mapSize; ++slice) {

			std::cout << "slice #" << slice+1 << ":" << std::endl;
			for (unsigned int row =0; row < mapSize; ++row) {
				for (unsigned int col =0; col < mapSize; ++col) {
					char val = manh[slice][row][col];
					if (val < 0) {
						std::cout << '.';
					} else {
						std::cout << static_cast<char>('0' + petrolUnits - val);
					}
				}
				std::cout << std::endl;

			}

		}

	}


}
