#include<iostream>
using namespace std;

int n = 5, c = 8, f, tp = 10, te;

const int T_min = 5;

struct thing {
	int w, v, r, s;
}t[100];

void _init() {
	t[0].v = 2;
	t[1].v = 5;
	t[2].v = 8;
	t[3].v = 3;
	t[4].v = 6;

	t[0].w = 2;
	t[1].w = 3;
	t[2].w = 5;
	t[3].w = 1;
	t[4].w = 4;
	
	te = 10;
}

void random_i() {
	int All_w;
	do {
		All_w = 0;
		for (int i = 0; i < n; i++) {
			
			t[i].r = rand() % 2;
			//cout << t[i].r;
			if (t[i].r) All_w += t[i].w;
		}
	} while (All_w > c);

	for (int i = 0; i < n; i++) t[i].s = t[i].r;
}

int fit() {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		if (t[i].r) sum += t[i].v;
	}
	return sum;
}

void change() {
	for (int i = 0; i < 3; i++) {

		int All_w;
		do {
			All_w = 0;
			int bit = rand() % n;
			t[bit].r = rand() % 2;
			for (int i = 0; i < n; i++) {
				//t[i].r = rand() % 2;
				//cout << t[i].r;
				if (t[i].r) All_w += t[i].w;
			}
		} while (All_w > c);
	
		if (f < fit()) {
			f = fit();
			for (int i = 0; i < n; i++) t[i].s = t[i].r;
		}
		else {
			double random_ = (rand() % 10000) / 10000.0;
			double Pt = exp((fit() - f) / te);
			if (random_ < te) {
				f = fit();
				for (int i = 0; i < n; i++) t[i].s = t[i].r;
			}
		}

	}
	te--;
}


int main() {
	_init();
	random_i();
	f = fit();
	//cout << endl;
	/*
	for (int i = 0; i < n; i++) cout << t[i].r;
	cout << endl;
	cout << f << endl;
	*/
	while (te > T_min) {
		for (int i = 0; i < n; i++) cout << t[i].r;
		cout << endl;
		cout << f << endl;
		change();
	}
}