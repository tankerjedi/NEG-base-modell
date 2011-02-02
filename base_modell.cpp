#include <stdio.h>
#include <math.h>

#include "base_modell.h"

int main()
{
printf("Simulation starts\n");

printf("Wage in region1 is: %4.2f\n",wage_region1( income_region1(1), income_region2(1), price_index_region1(1,1), price_index_region2(1,1)));

return 0;
}

//Equations


//Base modell

float income_region1(float wage1)
{
return mu * lambda * wage1 + (1 - mu) / 2;
};

float income_region2(float wage2)
{
return mu * (1 - lambda) *wage2 + (1 - mu) / 2;
};

float price_index_region1(float wage1, float wage2)
{
return pow(lambda * pow (wage1, 1 - sigma) + (1 - lambda) * pow (wage2 * T, 1 - sigma),(1 / (1 - sigma)));
};

float price_index_region2(float wage1, float wage2)
{
return pow(lambda * pow (wage1 * T, 1 - sigma) + (1 - lambda) * pow (wage2, 1 - sigma),(1 / (1 - sigma)));
};

float wage_region1(float income1, float income2, float price_index1, float price_index2)
{
return pow(income1 * pow (price_index1, sigma - 1) + income2 * pow (price_index2 / T, sigma -1),(1 /  sigma));
};

float wage_region2(float income1, float income2, float price_index1, float price_index2)
{ 
return pow(income1 * pow (price_index1 / T, sigma - 1) + income2 * pow (price_index2 , sigma -1),(1 /  sigma));
};

float real_wage_region1(float wage1, float price_index1)
{
return wage1 * pow(price_index1, -mu);
};

float real_wage_region2(float wage2, float price_index2)
{
return wage2 * pow(price_index2, -mu);
};

//Dinamics

float average_real_wage(float real_wage1, float real_wage2)
{
return 0;
};

float new_lamda(float average_real_wage0, float real_wage1) //The value of the population share in the next
{
return 0;

};