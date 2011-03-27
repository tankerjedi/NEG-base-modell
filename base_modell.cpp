#include <stdio.h>
#include <math.h>

#include "base_modell.h"

int main()
{
printf("Simulation starts\n");

printf("Wage in region1 is: %4.2f\n",wage_region1( income_region1(1), income_region2(1), price_index_region1(1,1), price_index_region2(1,1)));

printf("Value of goal function: %4.10f\n",goal_function(1.1,1.1,price_index_region1(1.1,1.1),price_index_region2(1.1,1.1)));

printf("Value of dL/dw1: %4.2f\n", dwage_region1(1.1,1.1,price_index_region1(1.1,1.1),price_index_region2(1.1,1.1)));

printf("Value of dL/dw2: %4.2f\n", dwage_region2(1.1,1.1,price_index_region1(1.1,1.1),price_index_region2(1.1,1.1)));

printf("Value of dL/dG1: %4.2f\n", dprice_index_region1(1.1,1.1,price_index_region1(1.1,1.1),price_index_region2(1.1,1.1)));

printf("Value of dL/dG2: %4.2f\n", dprice_index_region2(1.1,1.1,price_index_region1(1.1,1.1),price_index_region2(1.1,1.1)));

solve();

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

float solve() 
{
w1 = 1.1;
w2 = 1.1;
float g1 = price_index_region1(w1,w2);
float g2 = price_index_region2(w1,w2);

float F = goal_function(w1, w2, g1, g2);

//Find a applicable slambdas

float slambda_w1 = -2;
float slambda_w2 = -2;
float slambda_g1 = -2;
float slambda_g2 = -2;

int i;

for(i = -19;i <= 20; i++)
{
//slambda_w1

if 

(F > goal_function(w1+i * 0.1 * dwage_region1(w1,w2,g1,g2),w2,g1,g2) 
&&  
goal_function(w1+i*0.1*dwage_region1(w1,w2,g1,g2),w2,g1,g2) < goal_function(w1+slambda_w1*dwage_region1(w1,w2,g1,g2),w2,g1,g2)) 

{
slambda_w1 = i * 0.1;
}

//slambda_w2

if 

(F > goal_function(w1,w2+i * 0.1 * dwage_region2(w1,w2,g1,g2),g1,g2) 
&&  
goal_function(w1,w2+i*0.1*dwage_region2(w1,w2,g1,g2),g1,g2) < goal_function(w1,w2+slambda_w2*dwage_region1(w1,w2,g1,g2),g1,g2)) 

{
slambda_w2 = i * 0.1;
}
//slambda_g1

if 

(F > goal_function(w1,w2,g1 + i * 0.1 * dprice_index_region1(w1,w2,g1,g2),g2) 
&&  
goal_function(w1,w2,g1 + i *0.1 * dprice_index_region1(w1,w2,g1,g2),g2) < goal_function(w1,w2,g1 + slambda_g1 * dprice_index_region1(w1,w2,g1,g2),g2)) 

{
slambda_g1 = i * 0.1;
}
//slambda_w2

if 

(F > goal_function(w1,w2,g1,g2 + i * 0.1 * dprice_index_region2(w1,w2,g1,g2)) 
&&  
goal_function(w1,w2,g1,g2 + i * 0.1 * dprice_index_region2(w1,w2,g1,g2)) < goal_function(w1, w2, g1, g2 + slambda_g2 * dprice_index_region2(w1,w2,g1,g2))) 

{
slambda_g2 = i * 0.1;
}

//It is good, if we get lower value than the original goal function and the new goal function is lower too
//if 
//(F > goal_function(w1+i * 0.1 * dwage_region1(w1,w2,g1,g2),w2+ i * 0.1*dwage_region2(w1,w2,g1,g2),g1+ i * 0.1 *dprice_index_region1(w1,w2,g1,g2),g2+ i * 0.1 *dprice_index_region2(w1,w2,g1,g2)) 

//&&  

//goal_function(w1+i*0.1*dwage_region1(w1,w2,g1,g2),w2+i * 0.1 *dwage_region2(w1,w2,g1,g2),g1+i * 0.1 *dprice_index_region1(w1,w2,g1,g2),g2+ i * 0.1 *dprice_index_region2(w1,w2,g1,g2)) < goal_function(w1+slambda*dwage_region1(w1,w2,g1,g2),w2+slambda*dwage_region2(w1,w2,g1,g2),g1+slambda*dprice_index_region1(w1,w2,g1,g2),g2+slambda*dprice_index_region2(w1,w2,g1,g2)) 
//)
//{
//printf("Hűha \n");
//slambda = i * 0.1;
//}


//Check slambda value
//printf("%1.1f sor %f Az slambda értéke %f a %f érték mellett\n",i*0.1,F,slambda_w1,goal_function(w1+0.1 * i * dwage_region1(w1,w2,g1,g2),w2+ 0.1 * i *dwage_region2(w1,w2,g1,g2),g1+ 0.1 * i *dprice_index_region1(w1,w2,g1,g2),g2+ 0.1 * i * dprice_index_region2(w1,w2,g1,g2)));

printf("%1.1f sor, F: %1.1f, slambda_w1 %f, %f érték |",i*0.1,F,slambda_w1,goal_function(w1+0.1 * i * dwage_region1(w1,w2,g1,g2),w2,g1,g2));
printf(" slambda_w2: %1.1f, %f érték |",slambda_w2,goal_function(w1,w2+0.1 * i * dwage_region2(w1,w2,g1,g2),g1,g2));
printf(" slambda_g1: %1.1f, %f érték |",slambda_g1,goal_function(w1, w2, g1 + 0.1 * i * dprice_index_region1(w1,w2,g1,g2),g2));
printf(" slambda_g2: %1.1f, %f érték \n",slambda_g2,goal_function(w1, w2, g1, g2 +0.1 * i * dprice_index_region2(w1,w2,g1,g2)));
}

printf("Az slambda értéke: %f\n",slambda_w1);

//Indul az iteráció

for(i = 1; i <= iteration_limit; i++)
{

w1 = w1 + slambda_w1 * dwage_region1(w1,w2,g1,g2);
w2= w2 + slambda_w2 * dwage_region2(w1,w2,g1,g2);
g1 = g1 + slambda_g1 * dprice_index_region1(w1,w2,g1,g2);
g2 = g2 + slambda_g2 * dprice_index_region2(w1,w2,g1,g2);
F = goal_function(w1,w2,g1,g2);
printf("w1: %f, w2: %f, g1: %f, g2: %f, célfüggvény értéke: %f\n",w1,w2,g1,g2,F);
} 

return 0;
}

