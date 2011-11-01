#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "base_modell.h"

int main(int argc, char * argv[])
{
printf("Simulation starts\n");

printf("Wage in region1 is: %4.2f\n",wage_region1( income_region1(1), income_region2(1), price_index_region1(1,1), price_index_region2(1,1)));

printf("Value of goal function: %4.10f\n",goal_function(1.1,1.1,price_index_region1(1.1,1.1),price_index_region2(1.1,1.1)));

printf("Value of dL/dw1: %4.2f\n", dwage_region1(1.1,1.1,price_index_region1(1.1,1.1),price_index_region2(1.1,1.1)));

printf("Value of dL/dw2: %4.2f\n", dwage_region2(1.1,1.1,price_index_region1(1.1,1.1),price_index_region2(1.1,1.1)));

printf("Value of dL/dG1: %4.2f\n", dprice_index_region1(1.1,1.1,price_index_region1(1.1,1.1),price_index_region2(1.1,1.1)));

printf("Value of dL/dG2: %4.2f\n", dprice_index_region2(1.1,1.1,price_index_region1(1.1,1.1),price_index_region2(1.1,1.1)));


//bemeneti érték vizsgálat és kiíratás
//char * vege;
if (argc > 1) {s3lambda = atof(argv[1]);}
printf("__________________________Lambda paraméter: %f\n", s3lambda);


solve3();

return 0;
}

//Equations


//Base modell

double income_region1(double wage1)
{
return mu * lambda * wage1 + (1 - mu) / 2;
};

double income_region2(double wage2)
{
return mu * (1 - lambda) * wage2 + (1 - mu) / 2;
};

double price_index_region1(double wage1, double wage2)
{
return pow(lambda * pow(wage1, 1 - sigma) + (1 - lambda) * pow(wage2 * T, 1 - sigma),(1 / (1 - sigma)));
};

double price_index_region2(double wage1, double wage2)
{
return pow(lambda * pow(wage1 * T, 1 - sigma) + (1 - lambda) * pow(wage2, 1 - sigma),(1 / (1 - sigma)));
};

double wage_region1(double income1, double income2, double price_index1, double price_index2)
{
return pow(income1 * pow(price_index1, sigma - 1) + income2 * pow(price_index2 / T, sigma -1),(1 /  sigma));
};

double wage_region2(double income1, double income2, double price_index1, double price_index2)
{ 
return pow(income1 * pow(price_index1 / T, sigma - 1) + income2 * pow(price_index2 , sigma -1),(1 /  sigma));
};

double real_wage_region1(double wage1, double price_index1)
{
return wage1 * pow(price_index1, -mu);
};

double real_wage_region2(double wage2, double price_index2)
{
return wage2 * pow(price_index2, -mu);
};

//Dinamics

double average_real_wage(double real_wage1, double real_wage2)
{
return 0;
};

double new_lamda(double average_real_wage0, double real_wage1) //The value of the population share in the next
{
return 0;

};

//Solver

double goal_function(double wage1, double wage2, double price_index1, double price_index2)
{

return 
pow((price_index_region1(wage1,wage2) - price_index1),2) + 
pow((price_index_region2(wage1,wage2) - price_index2),2) +
pow(wage_region1(income_region1(wage1),income_region2(wage2),price_index1,price_index2) - wage1,2) +
pow(wage_region2(income_region1(wage1),income_region2(wage2),price_index1,price_index2) - wage2,2);

};

double dwage_region1(double wage1, double wage2, double price_index1, double price_index2)
{

return 
2 * ( price_index_region1(wage1,wage2)- price_index1) * (1/(1 - sigma)) * pow( price_index_region1(wage1,wage2)  ,sigma)  * (1- sigma) * lambda * pow(wage1, -sigma) + 
2 * ( price_index_region2(wage1,wage2)- price_index2) * (1/(1 - sigma)) * pow( price_index_region2(wage1,wage2)  ,sigma)  * (1- sigma) * lambda * pow(wage1, -sigma) * pow(T, 1 - sigma) + 
2 * (wage_region1(income_region1(wage1),income_region2(wage2),price_index1,price_index2) - wage1) * ( ( 1 / sigma) *  pow(wage_region1(income_region1(wage1),income_region2(wage2),price_index1,price_index2), 1 - sigma) * mu * lambda * pow ( price_index1, sigma - 1) - 1) +
2 * (wage_region2(income_region1(wage1),income_region2(wage2),price_index1,price_index2) - wage2) *  ( 1 / sigma) *  pow(wage_region2(income_region1(wage1),income_region2(wage2),price_index1,price_index2), 1 - sigma) * mu * lambda * pow ( price_index1 / T , sigma - 1) ;

}; 

double dwage_region2(double wage1, double wage2, double price_index1, double price_index2)
{

return 
2 * ( price_index_region1(wage1,wage2)- price_index1) * (1/(1 - sigma)) * pow( price_index_region1(wage1,wage2)  ,sigma)  * (1- sigma) * (1 - lambda) * pow(wage2, -sigma) * pow( T, 1 - sigma) + 
2 * ( price_index_region2(wage1,wage2)- price_index2) * (1/(1 - sigma)) * pow( price_index_region2(wage1,wage2)  ,sigma)  * (1- sigma) * (1 - lambda) * pow(wage2, -sigma) + 
2 * (wage_region1(income_region1(wage1),income_region2(wage2),price_index1,price_index2) - wage1) * ( 1 / sigma) *  pow(wage_region1(income_region1(wage1),income_region2(wage2),price_index1,price_index2), 1 - sigma) * mu * (1 - lambda) * pow ( price_index2 / T, sigma - 1) +
2 * (wage_region2(income_region1(wage1),income_region2(wage2),price_index1,price_index2) - wage2) * ( ( 1 / sigma) *  pow(wage_region2(income_region1(wage1),income_region2(wage2),price_index1,price_index2), 1 - sigma) * mu * (1 - lambda) * pow ( price_index2 , sigma - 1) - 1);

};

double dprice_index_region1(double wage1, double wage2, double price_index1, double price_index2)
{

return
-2 * ( price_index_region1(wage1,wage2)- price_index1) + 
2 * (wage_region1(income_region1(wage1),income_region2(wage2),price_index1,price_index2) - wage1) * ( 1 / sigma) *  pow(wage_region1(income_region1(wage1),income_region2(wage2),price_index1,price_index2), 1 - sigma) * (mu * lambda * wage1 + (1 - mu) / 2 ) * (sigma - 1) * pow( price_index1 , sigma - 2) +
2 * (wage_region2(income_region1(wage1),income_region2(wage2),price_index1,price_index2) - wage2) *  ( 1 / sigma) *  pow(wage_region2(income_region1(wage1),income_region2(wage2),price_index1,price_index2), 1 - sigma) * (mu * lambda * wage1 + (1 - mu) / 2 ) * (sigma - 1) * pow(T , 1 - sigma) * pow( price_index1 , sigma - 2) 
;
}
;

double dprice_index_region2(double wage1, double wage2, double price_index1, double price_index2)
{

return
-2 * ( price_index_region2(wage1,wage2)- price_index2) + 
2 * (wage_region1(income_region1(wage1),income_region2(wage2),price_index1,price_index2) - wage1) * ( 1 / sigma) *  pow(wage_region1(income_region1(wage1),income_region2(wage2),price_index1,price_index2), 1 - sigma) * (mu * (1 - lambda) * wage2 + (1 - mu) / 2 ) * (sigma - 1) * pow(T , 1 - sigma)  * pow( price_index2 , sigma - 2) + 
2 * (wage_region2(income_region1(wage1),income_region2(wage2),price_index1,price_index2) - wage2) *  ( 1 / sigma) *  pow(wage_region2(income_region1(wage1),income_region2(wage2),price_index1,price_index2), 1 - sigma) * (mu * (1 - lambda) * wage2 + (1 - mu) / 2 ) * (sigma - 1) * pow( price_index2 , sigma - 2)
 ;

};

//Simulta nsolver
double solve() 
{
w1 = 1.1;
w2 = 1.1;
double g1 = price_index_region1(w1,w2);
double g2 = price_index_region2(w1,w2);

double F = goal_function(w1, w2, g1, g2);

//Find a applicable slambdas

//double slambda = -2;

double slambda_w1 = -2;
double slambda_w2 = -2;
double slambda_g1 = -2;
double slambda_g2 = -2;

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
goal_function(w1,w2+i*0.1*dwage_region2(w1,w2,g1,g2),g1,g2) < goal_function(w1,w2+slambda_w2*dwage_region2(w1,w2,g1,g2),g1,g2)) 

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

double dw1, dw2, dg1, dg2;

//Ha kosntans lambdát állítanánk be
slambda_w1 = -0.2;
slambda_w2 = -0.2;
slambda_g1 = -0.2;
slambda_g2 = -0.2;


printf("w1: %f , w2: %f, g1: %f,  g2: %f, célfüggvény értéke: %f\n",w1,w2,g1,g2,F);

for(i = 1; i <= iteration_limit; i++)
{

dw1 = dwage_region1(w1,w2,g1,g2);
dw2 = dwage_region2(w1,w2,g1,g2);
dg1 = dprice_index_region1(w1,w2,g1,g2);
dg2 = dprice_index_region2(w1,w2,g1,g2);


w1 = w1 + slambda_w1 * dw1;
w2 = w2 + slambda_w2 * dw2;
g1 = g1 + slambda_g1 * dg1;
g2 = g2 + slambda_g2 * dg2;
F = goal_function(w1,w2,g1,g2);
printf("w1: %f, %f , w2: %f, %f, g1: %f, %f,  g2: %f, %f, célfüggvény értéke: %f\n",w1,dw1,w2,dw2,g1,dg1,g2,dg2,F);
} 

printf("Érték w1 %f és f2 %f; fügvénnyel w1: %f  és w2: %f\n",w1,w2,wage_region1(income_region1(w1),income_region2(w2),g1,g2),wage_region2(income_region1(w1),income_region2(w2),g1,g2));

return 0;
}


//Solve2 function, solve too slow, sequencial solver

double solve2()
{

int terjedelem = 10;
w1 = 1.01;
w2 = 1.01;
double g1 = price_index_region1(w1,w2);
double g2 = price_index_region2(w1,w2);

double F = goal_function(w1, w2, g1, g2);

printf("w1: %f, %f , w2: %f, %f, g1: %f, %f,  g2: %f, %f, célfüggvény értéke: %f\n",w1,dwage_region1(w1,w2,g1,g2),w2,dwage_region2(w1,w2,g1,g2),g1,dprice_index_region1(w1,w2,g1,g2),g2,dprice_index_region2(w1,w2,g1,g2),F);
//Find a applicable slambdas

//double slambda = -2;

double slambda = -0.1 * terjedelem;

int i,j;

for(j = 1; j <= iteration_limit; j++)
{


for(i = -terjedelem + 1;i <= terjedelem; i++)
{
//slambda_w1

if 

(F > goal_function(w1+i * 0.1 * dwage_region1(w1,w2,g1,g2),w2,g1,g2) 
&&  
goal_function(w1+i*0.1*dwage_region1(w1,w2,g1,g2),w2,g1,g2) < goal_function(w1+slambda*dwage_region1(w1,w2,g1,g2),w2,g1,g2)) 

{
slambda = i * 0.1;
}
}

w1 = w1 + slambda * dwage_region1(w1,w2,g1,g2);

F = goal_function(w1,w2,g1,g2);
printf("w1: %f, %f , w2: %f, %f, g1: %f, %f,  g2: %f, %f, célfüggvény értéke: %1.8f\n",w1,dwage_region1(w1,w2,g1,g2),w2,dwage_region2(w1,w2,g1,g2),g1,dprice_index_region1(w1,w2,g1,g2),g2,dprice_index_region2(w1,w2,g1,g2),F);

//slambda_w2

for(i = -terjedelem + 1;i <= terjedelem; i++)
{
if 

(F > goal_function(w1,w2+i * 0.1 * dwage_region2(w1,w2,g1,g2),g1,g2) 
&&  
goal_function(w1,w2+i*0.1*dwage_region2(w1,w2,g1,g2),g1,g2) < goal_function(w1,w2+slambda*dwage_region2(w1,w2,g1,g2),g1,g2)) 

{
slambda = i * 0.1;
}
}

w2 = w2 + slambda * dwage_region2(w1,w2,g1,g2);

F = goal_function(w1,w2,g1,g2);
printf("w1: %f, %f , w2: %f, %f, g1: %f, %f,  g2: %f, %f, célfüggvény értéke: %f\n",w1,dwage_region1(w1,w2,g1,g2),w2,dwage_region2(w1,w2,g1,g2),g1,dprice_index_region1(w1,w2,g1,g2),g2,dprice_index_region2(w1,w2,g1,g2),F);

//slambda_g1

for(i = -terjedelem + 1;i <= terjedelem; i++)
{
if 

(F > goal_function(w1,w2,g1 + i * 0.1 * dprice_index_region1(w1,w2,g1,g2),g2) 
&&  
goal_function(w1,w2,g1 + i *0.1 * dprice_index_region1(w1,w2,g1,g2),g2) < goal_function(w1,w2,g1 + slambda * dprice_index_region1(w1,w2,g1,g2),g2)) 

{
slambda = i * 0.1;
}
}

g1 = g1 + slambda * dprice_index_region1(w1,w2,g1,g2);

F = goal_function(w1,w2,g1,g2);
printf("w1: %f, %f , w2: %f, %f, g1: %f, %f,  g2: %f, %f, célfüggvény értéke: %f\n",w1,dwage_region1(w1,w2,g1,g2),w2,dwage_region2(w1,w2,g1,g2),g1,dprice_index_region1(w1,w2,g1,g2),g2,dprice_index_region2(w1,w2,g1,g2),F);

//slambda_w2

for(i = -terjedelem + 1;i <= terjedelem; i++)
{
if 

(F > goal_function(w1,w2,g1,g2 + i * 0.1 * dprice_index_region2(w1,w2,g1,g2)) 
&&  
goal_function(w1,w2,g1,g2 + i * 0.1 * dprice_index_region2(w1,w2,g1,g2)) < goal_function(w1, w2, g1, g2 + slambda * dprice_index_region2(w1,w2,g1,g2))) 

{
slambda = i * 0.1;
}
}

g2 = g2 + slambda * dprice_index_region2(w1,w2,g1,g2);

F = goal_function(w1,w2,g1,g2);
printf("w1: %f, %f , w2: %f, %f, g1: %f, %f,  g2: %f, %f, célfüggvény értéke: %1.20f\n",w1,dwage_region1(w1,w2,g1,g2),w2,dwage_region2(w1,w2,g1,g2),g1,dprice_index_region1(w1,w2,g1,g2),g2,dprice_index_region2(w1,w2,g1,g2),F);

}

return goal_function(w1,w2,g1,g2);
}

double solve3()
{
//változók kezdeti értékei
int i;
double cpi1 = price_index_region1(w1,w2);
double cpi2 = price_index_region2(w1,w2);
double dw1, dw2, dcpi1, dcpi2;

for(i = 1; i <= iteration_limit; i++)
{
//derivált értékek
dw1 = dwage_region1(w1,w2,cpi1,cpi2);
dw2 = dwage_region2(w1,w2,cpi1,cpi2);
dcpi1 = dprice_index_region1(w1,w2,cpi1,cpi2);
dcpi2 = dprice_index_region1(w1,w2,cpi1,cpi2);

//pontok kiszámítása
w1 = w1 + s3lambda * dw1;
w2 = w2 + s3lambda * dw2;
cpi1 = cpi1 + s3lambda * dcpi1;
cpi2 = cpi2 + s3lambda * dcpi2;

//célfüggvény érékének kiíratása
printf("A célfüggvény értéke %f \n",goal_function(w1,w2,cpi1,cpi2));
}
//értékek kiíratása

double jov1 = income_region1(w1);
double jov2 = income_region2(w2);
printf("w1: %f, %f , w2: %f, %f, g1: %f, %f,  g2: %f, %f, jöv1:%f, jöv2:%f\n",w1,dwage_region1(w1,w2,cpi1,cpi2),w2,dwage_region2(w1,w2,cpi1,cpi2),cpi1,dprice_index_region1(w1,w2,cpi1,cpi2),cpi2,dprice_index_region2(w1,w2,cpi1,cpi2),jov1,jov2);
}
