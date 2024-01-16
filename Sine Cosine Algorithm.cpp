#include <bits/stdc++.h>

using namespace std;

const double pi = acos(-1.0);
const int agent = 6;
const int iterations = 100;

double xmin, xmax, ymin, ymax;
double rr1;


//------------------------------------------------------------------------------- r1 ranges in (0.00 - 1.00) ----------------------------------------------------------------------------------------------------------------------------------------------------------------
double r1(){
	random_device val;
	mt19937 generator(val());
	uniform_real_distribution<double> range(0.0, 1.0);
	return range(generator);
}


//------------------------------------------------------------------------------- r2 ranges in (0, 2pi) ------------------------------------------------------------------------------------------------------------------------------
double r2(){
	random_device val;
	mt19937 generator(val());
	uniform_real_distribution<double> range(0.0, 2 * pi);
	return range(generator); 
}


//------------------------------------------------------------------------------- r3 ranges in (0.00 - 2.00) --------------------------------------------------------------------------------------------------------------------
double r3(){
	random_device val;
	mt19937 generator(val());
	uniform_real_distribution<double> range(0.0, 2.0);
	return range(generator);
}


//------------------------------------------------------------------------------- r4 ranges in (0.00 - 1.00) --------------------------------------------------------------------------------------------------------------
double r4(){
	random_device val;
	mt19937 generator(val());
	uniform_real_distribution<double> range(0.0, 1.0);
	return range(generator);
}


//------------------------------------------------------------------------------ Generate Initial Population --------------------------------------------------------------------------------------------------------------
void generate_initial_population(vector<pair<double, double>> &X){
	for(int i = 0; i < agent; i++){
		double x = xmin + r1() * (xmax - xmin);
		double y = ymin + r1() * (ymax - ymin);
		X.push_back({x, y});
	}
}


//------------------------------------------------------------------------------- Bringing points into bounds --------------------------------------------------------------------------------------------------------------
void position_update_check(vector<pair<double, double>> &X){
	for(int i = 0; i < agent; i++){
		if(X[i].first < xmin) X[i].first = xmin;
		if(X[i].first > xmax) X[i].first = xmax;
		if(X[i].second < ymin) X[i].second = ymin;
		if(X[i].second > ymax) X[i].second = ymax;
	}
}


//-------------------------------------------------------------------------------- Calculating the fitness ----------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Using Sphere Function ------------------------------------------------------------------------------------------------------------
pair<double, double> calculate_fitness(vector<pair<double, double>> X){
	pair<double, double> xd;
	double mn = LLONG_MAX;
	for(int i = 0; i < agent; i++){
		double curr = (X[i].first * X[i].first) + (X[i].second * X[i].second);
		if(curr < mn){
			mn = curr;
			xd = X[i];
		}
	}
	return xd;
}


//-------------------------------------------------------------------------------- Updating points ----------------------------------------------------------------------------------------------------------------------
void update_points(vector<pair<double, double>> &X, pair<double, double> xd){
	for(int i = 0; i < agent; i++){
		if(r4() < 0.5) X[i].first = X[i].first + rr1 * sin(r2()) * fabs(r3() * xd.first - X[i].first);
		else X[i].first = X[i].first + rr1 * cos(r2()) * fabs(r3() * xd.first - X[i].first);

		if(r4() < 0.5) X[i].second = X[i].second + rr1 * sin(r2()) * fabs(r3() * xd.second - X[i].second);
		else X[i].second = X[i].second + rr1 * cos(r2()) * fabs(r3() * xd.second - X[i].second);
	}
}


//-------------------------------------------------------------------------------- Sine Cosine Algorithm ----------------------------------------------------------------------------------------------------------------------
void SCA(){
	cout << "(_,_) ----------------- (_,_)" << '\n';
	for(int i = 0; i < 10; i++) cout << "  |                       |  " << '\n';
	cout << "(_,_) ----------------- (_,_)" << '\n' << '\n';

	cout << "Choose the right point of x-axis : "; cin >> xmin; cout << '\n';
	cout << "Choose the left point of x-axis : "; cin >> xmax; cout << '\n';
	cout << "Choose the lower point of y-axis : "; cin >> ymin; cout << '\n';
	cout << "Choose the upper point of y-axis : "; cin >> ymax; cout << '\n';

	if(xmin > xmax) swap(xmin, xmax);
	if(ymin > ymax) swap(ymin, ymax);

	vector<pair<double, double>> X;
	generate_initial_population(X);
	position_update_check(X);
	pair<double, double> xd = calculate_fitness(X);

	for(int i = 1; i <= iterations; i++){
		rr1 = 2.0 - 2.0 * ((double)i / iterations);
		update_points(X, xd);
		position_update_check(X);
		xd = calculate_fitness(X);
	}

	cout << "The optimal point is: " << "(" << xd.first << ", " << xd.second << ")" << '\n';
}


void zahid(){
  	cout << "The algorithm is implemented by Zahid Hasan Mozumder" << '\n';
  	cout << "This is an implementation of Sine Cosine Algorithm on 2D plane" << '\n';
}


int main(){
	zahid();
  	SCA();
}
