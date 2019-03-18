#include "Data.h"
#include <stdlib.h>

void Data::readData(char* filePath)
{
   FILE* f = fopen(filePath, "r");

   if(!f)
   {
      printf("Problem while reading instance.\n");
      exit(1);
   }

   if(fscanf(f, "%d", &n_items) != 1)
   {
      printf("Problem while reading instance.\n");
      exit(1);
   }

   //reading costs
   costs = std::vector<double>(n_items, 0);
   for(int i = 0; i < n_items; i++)
   {
      if(fscanf(f, "%lf", &costs[i]) != 1)
      {
	 printf("Problem while reading instance.\n");
	 exit(0);
      }
   }
   //reading proteins
   proteins = std::vector<double>(n_items, 0);
   for(int i = 0; i < n_items; i++)
   {
      if(fscanf(f, "%lf", &proteins[i]) != 1)
      {
	 printf("Problem while reading instance.\n");
	 exit(0);
      }
   }
   //reading carbs
   carbs = std::vector<double>(n_items, 0);
   for(int i = 0; i < n_items; i++)
   {
      if(fscanf(f, "%lf", &carbs[i]) != 1)
      {
	 printf("Problem while reading instance.\n");
	 exit(0);
      }
   }
   //reading fats
   fats = std::vector<double>(n_items, 0);
   for(int i = 0; i < n_items; i++)
   {
      if(fscanf(f, "%lf", &fats[i]) != 1)
      {
	 printf("Problem while reading instance.\n");
	 exit(0);
      }
   }
}

int Data::getNItems()
{
   return n_items;
}

double Data::getItemCost(unsigned int item)
{
   if(item >= n_items)
   {
      return 0;
   }

   return costs[item]; 
}

double Data::getItemProtein(unsigned int item)
{
   if(item >= n_items)
   {
      return 0;
   }

   return proteins[item]; 
}

double Data::getItemFat(unsigned int item)
{
   if(item >= n_items)
   {
      return 0;
   }

   return fats[item]; 
}

double Data::getItemCarb(unsigned int item)
{
   if(item >= n_items)
   {
      return 0;
   }

   return carbs[item]; 
}
