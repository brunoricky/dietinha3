#ifndef _DATA_H_
#define _DATA_H_

#include <vector>
#include <stdio.h>

class Data{

	private:

		int n_items;
		std::vector<double> costs;
		std::vector<double> proteins;
		std::vector<double> fats;
		std::vector<double> carbs; 
		

	public:

		void readData(char* filePath);
		int getNItems();
		double getItemCost(unsigned int item);
		double getItemProtein(unsigned int item);
		double getItemFat(unsigned int item);
		double getItemCarb(unsigned int item);
};

#endif

