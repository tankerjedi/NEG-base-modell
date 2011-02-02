
//Parameters

int iteration_limit = 500; //Itertaion limit

float lambda = 0.5; //Region's population share in region1 parameter
float gamma =1; //Speed of population moving 

float  mu = 0.5; //Cobb-Douglas utility function parameter
float sigma = 1; //CES utility fucnion parameter

//Equations


//Base modell

float income_region1(float wage_region1);

float income_region2(float wage_region2);

float price_index(g_region1(float wage_region1, float wage_region2);

float price_index(g_region2(float wage_region1, float wage_region2);

float wage_region1(float price_index_region1, float price_index_region2);

float wage_region2(float price_index_region1, float price_index_region2);

float real_wage_region1(float wage_region1, float price_index_region1);

float real_wage_region2(float wage_region2, float price_index_region2);

//Dinamics

float average_real_wage(float real_wage_region1, float real_wage_region2);

float new_lamda(float average_real_wage, float real_wage_region1); //The value of the population share in the next 

