#include <iostream>
using namespace std;

double  minx, maxx, mu[100], cross[100], pop[100], best;
int num, iters;
double F = 0.5, CR = 0.7;

double fit(double x) {
	return -x * (x - 4);
}

void mutation() {
	//double mu[100];
	for (int i = 1; i <= num; i++) {
		int r1 = 0, r2 = 0, r3 = 0;
		while (r1 == i || r2 == i || r3 == i || r1 == r2 || r2 == r3 || r3 == r1) {
			r1 = rand() % (num - 1);
			r2 = rand() % (num - 1);
			r3 = rand() % (num - 1);
		}
		mu[i] = pop[r1] + F * (pop[r2] - pop[r3]);
		if (mu[i] < minx) mu[i] = minx;
		else if (mu[i] > maxx) mu[i] = maxx;
	}
}

void crossover() {
	//double cross[100];
	for (int i = 1; i <= num; i++) {
		double r = (rand() % 100) / 100.0;
		if (r < CR) {
			cross[i] = mu[i];
		}
		else {
			cross[i] = pop[i];
		}
	}
}

void selection() {
	for (int i = 1; i <= num; i++) {
		if (fit(pop[i]) > fit(cross[i]))
			pop[i] = pop[i];
		else pop[i] = cross[i];
	}
}

void evaluate() {
	for (int i = 1; i <= num; i++) {
		best < fit(pop[i]) ? best = fit(pop[i]) : best = best;
	}
}

void update() {
	mutation();
	crossover();
	selection();
	evaluate();
}

void init_pop() {
	for(int i = 1; i <= num; i++){
		pop[i] = (rand() % (int)(maxx - minx)) + minx;
	}
	evaluate();
}

void DE(int size, int iter, double mix, double max) {
	num = size;
	iters = iter;
	minx = mix;
	maxx = max;
	init_pop();
	for (int i = 1; i <= iter; i++) {
		cout << i << endl;
		update();
		cout << best << endl;
	}
}

int main()
{
	DE(10, 50, -100, 100);
	return 0;
}
