#include <iostream>
#include<math.h>
using namespace std;

double l = 0.9, w[10][10], o_[10], s[10], o[10], e[10], t[10];
int all = 3;

struct Per
{
	double x;
}P[10];

void pre_start() {
	P[1].x = 1;
	P[2].x = 0;
	P[3].x = 1;
	w[1][4] = 0.2;
	w[1][5] = -0.3;
	w[2][4] = 0.4;
	w[2][5] = 0.1;
	w[3][4] = -0.5;
	w[3][5] = 0.2;
	w[4][6] = -0.3;
	w[5][6] = -0.2;

	o_[4] = -0.4;
	o_[5] = 0.2;
	o_[6] = 0.1;

	for (int i = 1; i <= 10; i++) {
		t[i] = 1.0;
	}
}

void start() {
	s[4] = w[1][4] * P[1].x + w[2][4] * P[2].x + w[3][4] * P[3].x + o_[4];
	o[4] = 1 / (1 + exp(-s[4]));
	s[5] = w[1][5] * P[1].x + w[2][5] * P[2].x + w[3][5] * P[3].x + o_[5];
	o[5] = 1 / (1 + exp(-s[5]));
	s[6] = w[4][6] * o[4] + w[5][6] * o[5] + o_[6];
	o[6] = 1 / (1 + exp(-s[6]));

	for (int i = 4; i <= 6; i++) {
		cout << i << " s[]: " << s[i] << "o[]: " << o[i] <<endl;
	}
}

void back() {
	int j = 6;
	cout << o[j] << "  " << (1 - o[j]) << "  " << (t[j] - o[j]) << "  " << endl;
	e[j] = o[j] * (1 - o[j]) * (t[j] - o[j]);
	for (j = 5; j >= 4; j--) {
		e[j] = o[j] * (1 - o[j]) * w[j][6] * e[6];
	}


	for (int i = 4; i <= 6; i++) {
		cout << i << " e[]: " << e[i] << endl;
	}
}

void rebuild() {
	for (int i = 0; i < 10; i++) {
		o_[i] = o_[i] + l * e[i];
		cout << i << "o_[]" << o_[i] << endl;
		for (int j = 0; j < 10; j++) {
			w[i][j] = w[i][j] + l * o[i] * e[j];
			cout << i  << j << "w[i][j]   ;" << w[i][j];
		}
		cout << endl;
	}
}

int main()
{
	pre_start();
	start();
	back();
	rebuild();
	return 0;
}
