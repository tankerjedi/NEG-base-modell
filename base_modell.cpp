#include <stdio.h>
#include <math.h>

#include "base_modell.h"

int main()
{
printf("Simulation starts\n");

printf("Wage in region1 is: %4.2f\n",wage_region1( income_region1(1), income_region2(1), price_index_region1(1,1), price_index_region2(1,1)));

printf("Value of goal function: %4.2f\n",goal_function(1,1,price_index_region1(1,1),price_index_region2(1,1)));

printf("Value of dL/dw1: %4.2f\n", dwage_region1(1.1,1,price_index_region1(1.1,1),price_index_region2(1.1,1)));

printf("Value of dL/dw2: %4.2f\n", dwage_region2(1,1,price_index_region1(1,1),price_index_region2(1,1)));

printf("Value of dL/dG1: %4.2f\n", dprice_index_region1(1,1,price_index_region1(1,1),price_index_region2(1,1)));

printf("Value of dL/dG2: %4.2f\n", dprice_index_region2(1,1,price_index_region1(1,1),price_index_region2(1,1)));

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

//Solver

float goal_function(float wage1, float wage2, float price_index1, float price_index2)
{

return 
pow((price_index_region1(wage1,wage2) - price_index1),2) + 
pow((price_index_region2(wage1,wage2) - price_index2),2) +
pow(wage_region1(income_region1(wage1),income_region2(wage2),price_index1,price_index2) - wage1,2) +
pow(wage_region2(income_region1(wage1),income_region2(wage2),price_index1,price_index2) - wage2,2);

};

float dwage_region1(float wage1, float wage2, float price_index1, float price_index2)
{

return 
2 * ( price_index_region1(wage1,wage2)- price_index1) * (1/(1 - sigma)) * pow( price_index_region1(wage1,wage2)  ,sigma)  * (1- sigma) * lambda * pow(wage1, -sigma) + 
2 * ( price_index_region2(wage1,wage2)- price_index2) * (1/(1 - sigma)) * pow( price_index_region2(wage1,wage2)  ,sigma)  * (1- sigma) * lambda * pow(wage1, -sigma) * pow(T, 1 - sigma) + 
2 * (wage_region1(income_region1(wage1),income_region2(wage2),price_index1,price_index2) - wage1) * ( ( 1 / sigma) *  pow(wage_region1(income_region1(wage1),income_region2(wage2),price_index1,price_index2), 1 - sigma) * mu * lambda * pow ( price_index1, sigma - 1) - 1) +
2 * (wage_region2(income_region1(wage1),income_region2(wage2),price_index1,price_index2) - wage2) *  ( 1 / sigma) *  pow(wage_region2(income_region1(wage1),income_region2(wage2),price_index1,price_index2), 1 - sigma) * mu * lambda * pow ( price_index1 / T , sigma - 1) ;

}; 

float dwage_region2(float wage1, float wage2, float price_index1, float price_index2)
{

return 
2 * ( price_index_region1(wage1,wage2)- price_index1) * (1/(1 - sigma)) * pow( price_index_region1(wage1,wage2)  ,sigma)  * (1- sigma) * (1 - lambda) * pow(wage2, -sigma) * pow( T, 1 - sigma) + 
2 * ( price_index_region2(wage1,wage2)- price_index2) * (1/(1 - sigma)) * pow( price_index_region2(wage1,wage2)  ,sigma)  * (1- sigma) * (1 - lambda) * pow(wage2, -sigma) + 
2 * (wage_region1(income_region1(wage1),income_region2(wage2),price_index1,price_index2) - wage1) * ( 1 / sigma) *  pow(wage_region1(income_region1(wage1),income_region2(wage2),price_index1,price_index2), 1 - sigma) * mu * (1 - lambda) * pow ( price_index2 / T, sigma - 1) +
2 * (wage_region2(income_region1(wage1),income_region2(wage2),price_index1,price_index2) - wage2) * ( ( 1 / sigma) *  pow(wage_region2(income_region1(wage1),income_region2(wage2),price_index1,price_index2), 1 - sigma) * mu * (1 - lambda) * pow ( price_index2 , sigma - 1) - 1);

};

float dprice_index_region1(float wage1, float wage2, float price_index1, float price_index2)
{

return
-2 * ( price_index_region1(wage1,wage2)- price_index1) + 
2 * (wage_region1(income_region1(wage1),income_region2(wage2),price_index1,price_index2) - wage1) * ( 1 / sigma) *  pow(wage_region1(income_region1(wage1),income_region2(wage2),price_index1,price_index2), 1 - sigma) * (mu * lambda * wage1 + (1 - mu) / 2 ) * (sigma - 1) * pow ( price_index1 , sigma - 2) +
2 * (wage_region2(income_region1(wage1),income_region2(wage2),price_index1,price_index2) - wage2) *  ( 1 / sigma) *  pow(wage_region2(income_region1(wage1),income_region2(wage2),price_index1,price_index2), 1 - sigma) * (mu * lambda * wage1 + (1 - mu) / 2 ) * (sigma - 1) * pow(T , 1 - sigma) * pow ( price_index1 , sigma - 2) ;

}
;

float dprice_index_region2(float wage1, float wage2, float price_index1, float price_index2)
{

return
-2 * ( price_index_region2(wage1,wage2)- price_index2) + 
2 * (wage_region1(income_region1(wage1),income_region2(wage2),price_index1,price_index2) - wage1) * ( 1 / sigma) *  pow(wage_region1(income_region1(wage1),income_region2(wage2),price_index1,price_index2), 1 - sigma) * (mu * (1 - lambda) * wage2 + (1 - mu) / 2 ) * (sigma - 1) * pow(T , sigma - 1)  * pow( price_index2 , sigma - 2) +
2 * (wage_region2(income_region1(wage1),income_region2(wage2),price_index1,price_index2) - wage2) *  ( 1 / sigma) *  pow(wage_region2(income_region1(wage1),income_region2(wage2),price_index1,price_index2), 1 - sigma) * (mu * (1 - lambda) * wage2 + (1 - mu) / 2 ) * (sigma - 1) * pow ( price_index2 , sigma - 2) ;

};
