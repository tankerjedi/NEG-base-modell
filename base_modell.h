
//Parameters

int iteration_limit = 500; //Itertaion limit

float lambda = 0.8; //Region's population share in region1 parameter
float pgamma =1; //Speed of population moving 

float  mu = 0.4; //Cobb-Douglas utility function parameter
float sigma = 5; //CES utility fucnion parameter

float T = 1.7; //Transportation cost

float w1 = 1; //bérváltozó kezdeti értéke
float w2 = 1;

//Equations


//Base modell

float income_region1(float wage1);

float income_region2(float wage2);

float price_index_region1(float wage1, float wage2);

float price_index_region2(float wage1, float wage2);

float wage_region1(float income1, float income2, float price_index1, float price_index2);

float wage_region2(float income1, float income2, float price_index1, float price_index2);

float real_wage_region1(float wage1, float price_index1);

float real_wage_region2(float wage2, float price_index2);

//Dinamics

float average_real_wage(float real_wage1, float real_wage2);

float new_lamda(float average_real_wage0, float real_wage1); //The value of the population share in the next 

//Solver

float goal_function(float wage1, float wage2, float price_index1, float price_index2);

float dwage_region1(float wage1, float wage2, float price_index1, float price_index2);

float dwage_region2(float wage1, float wage2, float price_index1, float price_index2);

float dprice_index_region1(float wage1, float wage2, float price_index1, float price_index2);

float dprice_index_region2(float wage1, float wage2, float price_index1, float price_index2);

float solve();

//void solve(float lambda0, float pgamma, float mu, float sigma, float T, int iteration limit = 500);

