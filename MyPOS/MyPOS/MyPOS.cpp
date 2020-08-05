#include<iostream>
#include <algorithm>
using namespace std;

int maxx = 10, minx = -10, stop, num = 50;
double gBest[3], now = 9999;
double w = 0.9, c1 = 0, c2 = 2.0;

struct Per{
	double v[3], x[3], pBest[3], f;
} p[105];

double fit(double x1, double x2) {
	return x1 * x1 + x2 * x2;
}

void renow(Per* t) {
	if (now > (t -> f)) {
		now = t -> f;
		gBest[0] = t->pBest[0];
		gBest[1] = t->pBest[1];
	}
}

void start() {
	Per* t;
	for (int i = 0; i < num; i++) {
		t = &p[i];
		for (int j = 0; j < 2; j++) {
			t->v[j] = rand() % 20 - 10;
			t->pBest[j] = t->x[j] = rand() % 20 - 10;
			//cout << "t->v[" << j << "]: " << t->v[j] << endl;
			//cout << "t->x[" << j << "]: " << t->x[j] << endl;
			//cout << "t->pBest[" << j << "]: " << t->pBest[j] << endl;
		}
		t->f = fit(t->x[0], t->x[1]);
		//cout << "t->f: " << t->f << endl;
		renow(t);
	}
	//cout << "gBest[0]: " << gBest[0] << endl;
	//cout << "gBest[1]: " << gBest[1] << endl;
}

void run() {
	cout << "please enter an int(stop):" << endl;
	cin >> stop;
	Per* t;
	for (int h = 0; h < stop; h++) {
		//w -= (0.5 / stop);
		for (int i = 0; i < num; i++) {
			t = &p[i];
			double c1 = (rand() % 200) / 100.0;
			double c2 = (rand() % 200) / 100.0;
			double r1 = (rand() % 100) / 100.0;
			double r2 = (rand() % 100) / 100.0;
			double w = (rand() % 100) / 100.0;
			//cout << "r1: " << r1 << endl;
			//cout << "r2: " << r2 << endl;
			for (int j = 0; j < 2; j++) {
				//cout << w * (t->v[j]) << endl << c1 * r1 * ((t->pBest[j]) - (t->x[j])) << endl << c2 * r2 * (gBest[j] - (t->x[j])) << endl;
				t->v[j] = w * (t->v[j]) + c1 * r1 * ((t->pBest[j]) - (t->x[j])) + c2 * r2 * (gBest[j]- (t->x[j]));
				t->x[j] = t->x[j] + t->v[j];
				//cout << "t->v[" << j << "]: " << t->v[j] << endl;
				//cout << "t->x[" << j << "]: " << t->x[j] << endl;
			}
			if (t->f > fit(t->x[0], t->x[1])) {
				t->f = fit(t->x[0], t->x[1]);
				//cout << "t->f: " << t->f << endl;
				t->pBest[0] = t->x[0];
				t->pBest[1] = t->x[1];
			}
			renow(t);
		}
	}
}

void print() {
	//cout << 0.5 / stop << endl;
	cout << "gBest[0]: " << gBest[0] << endl;
	cout << "gBest[1]: " << gBest[1] << endl;
}

int main() {
	while (true) {
		start();
		run();
		print();
	}
	return 0;
}