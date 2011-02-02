#include <stdio.h>
#include <math.h>

#include "base_modell.h"

int main()
{
printf("Simulation starts\n");

return 0;
}

//Equations


//Base modell

float income_region1(float wage_region1)
{
return mu * lambda * wage_region1 + (1 - mu) / 2;
};

float income_region2(float wage_region2)
{
return mu * (1 - lambda) *wage_region2 + (1 - mu) / 2;
};

float price_index_region1(float wage_region1, float wage_region2)
{
return pow(lambda * pow (wage_region1, 1 - sigma) + (1 - lambda) * pow (wage_region2 * T, 1 - sigma),(1 / (1 - sigma)));
};

float price_index_region2(float wage_region1, float wage_region2)
{
return pow(lambda * pow (wage_region1 * T, 1 - sigma) + (1 - lambda) * pow (wage_region2, 1 - sigma),(1 / (1 - sigma)));
};

float wage_region1(float income1, float income2, float price_index_region1, float price_index_region2)
{
return pow(income1 * pow (price_index_region1, sigma - 1) + income2 * pow (price_index_region2 / T, sigma -1),(1 /  sigma));
};

float wage_region2(float income1, float income2, float price_index_region1, float price_index_region2)
{ 
return pow(income1 * pow (price_index_region1 / T, sigma - 1) + income2 * pow (price_index_region2 , sigma -1),(1 /  sigma));
};

float real_wage_region1(float wage_region1, float price_index_region1)
{
return wage_region1 * pow(price_index_region1, -mu);
};

float real_wage_region2(float wage_region2, float price_index_region2)
{
return wage_region2 * pow(price_index_region2, -mu);
};

//Dinamics

float average_real_wage(float real_wage_region1, float real_wage_region2)
{
return 0;
};

float new_lamda(float average_real_wage, float real_wage_region1) //The value of the population share in the next
{
return 0;

};
