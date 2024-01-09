#include <bits/stdc++.h>

using namespace std;

const int agent = 6;
const int iterations = 100;
const double c1 = 2.0;
const double c2 = 2.0;
const double wmin = 0.4;
const double wmax = 0.9;

double xmin, xmax, ymin, ymax;
double w;


//---------------------------------------------------------------------------- r ranges in (0.0 - 1.0) ----------------------------------------------------------------------------------------------------------------------
double r(){
	random_device val;
	mt19937 generator(val());
	uniform_real_distribution<double> range(0.0, 1.0);
	return range(generator);
}


//---------------------------------------------------------------------------- Generate Initial Population --------------------------------------------------------------------------------------------------------------
void generate_initial_population(vector<pair<double, double>> &X, vector<pair<double, double>> &pBest){
	for(int i = 0; i < agent; i++){
		double x = xmin + r() * (xmax - xmin);
		double y = ymin + r() * (ymax - ymin);
		X.push_back({x, y});
		pBest.push_back({x, y});
	}
}


//---------------------------------------------------------------------------- Generate Initial Velocity ---------------------------------------------------------------------------------------------------------------------
void generate_initial_velocity(vector<pair<double, double>> &v){
	for(int i = 0; i < agent; i++)
		v.push_back({2.0, 2.0});
}


//---------------------------------------------------------------------------- Bringing points into bounds --------------------------------------------------------------------------------------------------------------------
void position_update_check(vector<pair<double, double>> &X){
	for(int i = 0; i < agent; i++){
		if(X[i].first < xmin) X[i].first = xmin;
		if(X[i].first > xmax) X[i].first = xmax;
		if(X[i].second < ymin) X[i].second = ymin;
		if(X[i].second > ymax) X[i].second = ymax;
	}
}


//----------------------------------------------------------------------------- Calculating Fitness Value ---------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- Using Sphere Function --------------------------------------------------------------------------------------------------------------------
void calculate_fitness(vector<pair<double, double>> X, vector<pair<double, double>> v, vector<pair<double, double>> &pBest, pair<double, double> &gBest){
	double mn = LLONG_MAX;
	for(int i = 0; i < agent; i++){
		double curr_val = (X[i].first * X[i].first) + (X[i].second * X[i].second);
		double pBest_val = (pBest[i].first * pBest[i].first) + (pBest[i].second * pBest[i].second);
		if(pBest_val > curr_val){
			pBest_val = curr_val;
			pBest[i] = X[i];
		}
		if(pBest_val < mn){
			gBest = pBest[i];
		}
	}
}


//----------------------------------------------------------------------------- Updating the points ---------------------------------------------------------------------------------------------------------------------------
void update_points_and_velocity(vector<pair<double, double>> &X, vector<pair<double, double>> &v, vector<pair<double, double>> &pBest, pair<double, double> &gBest){
	for(int i = 0; i < agent; i++){
		v[i].first = (w * v[i].first) + (c1 * r() * (pBest[i].first - X[i].first)) + (c2 * r() * (gBest.first - X[i].first));
		X[i].first = X[i].first + v[i].first;
		v[i].second = (w * v[i].second) + (c1 * r() * (pBest[i].second - X[i].second)) + (c2 * r() * (gBest.second - X[i].second));
		X[i].second = X[i].second + v[i].second;
	}
}


//---------------------------------------------------------------------------- Particle Swarm Optimization ---------------------------------------------------------------------------------------------------------------------
void PSO(){
	cout << "(_,_) ----------------- (_,_)" << '\n';
	for(int i = 0; i < 10; i++) cout << "  |                       |  " << '\n';
	cout << "(_,_) ----------------- (_,_)" << '\n' << '\n';

	cout << "Choose the right point of x-axis : "; cin >> xmin; cout << '\n';
	cout << "Choose the left point of x-axis : "; cin >> xmax; cout << '\n';
	cout << "Choose the lower point of y-axis : "; cin >> ymin; cout << '\n';
	cout << "Choose the upper point of y-axis : "; cin >> ymax; cout << '\n';

	if(xmin > xmax) swap(xmin, xmax);
	if(ymin > ymax) swap(ymin, ymax);

	vector<pair<double, double>> X, v, pBest;
	pair<double, double> gBest;

	generate_initial_population(X, pBest);
	generate_initial_velocity(v);
	position_update_check(X);
	calculate_fitness(X, v, pBest, gBest);

	for(int i = 1; i <= iterations; i++){
		w = wmax - (((wmax - wmin) * i) / iterations);
		update_points_and_velocity(X, v, pBest, gBest);
		position_update_check(X);
		calculate_fitness(X, v, pBest, gBest);
	}

	cout << "The optimal point is: " << "(" << gBest.first << ", " << gBest.second << ")" << '\n';
}


void zahid(){
    	cout << "The algorithm is implemented by Zahid Hasan Mozumder" << '\n';
  	cout << "This is an implementation of Particle Swarm Optimization on 2D plane" << '\n';
}

int main(){
	zahid();
	PSO();
}
