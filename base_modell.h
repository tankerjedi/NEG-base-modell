
//Parameters

int iteration_limit = 10; //Itertaion limit

double lambda = 0.5; //Region's population share in region1 parameter
double pgamma =1; //Speed of population moving 
double s3lambda = -0.1; //derivate step 

double  mu = 0.5; //Cobb-Douglas utility function parameter
double sigma = 5; //CES utility fucnion parameter

double T = 1.2; //Transportation cost

double w1 = 1; //bérváltozó kezdeti értéke
double w2 = 1;

//Equations


//Base modell

double income_region1(double wage1);

double income_region2(double wage2);

double price_index_region1(double wage1, double wage2);

double price_index_region2(double wage1, double wage2);

double wage_region1(double income1, double income2, double price_index1, double price_index2);

double wage_region2(double income1, double income2, double price_index1, double price_index2);

double real_wage_region1(double wage1, double price_index1);

double real_wage_region2(double wage2, double price_index2);

//Dinamics

double average_real_wage(double real_wage1, double real_wage2);

double new_lamda(double average_real_wage0, double real_wage1); //The value of the population share in the next 

//Solver

double goal_function(double wage1, double wage2, double price_index1, double price_index2);

double dwage_region1(double wage1, double wage2, double price_index1, double price_index2);

double dwage_region2(double wage1, double wage2, double price_index1, double price_index2);

double dprice_index_region1(double wage1, double wage2, double price_index1, double price_index2);

double dprice_index_region2(double wage1, double wage2, double price_index1, double price_index2);

double solve();

double solve2();

double solve3();

//void solve(double lambda0, double pgamma, double mu, double sigma, double T, int iteration limit = 500);

