#include <iostream>
using namespace std;

int maxn = 10, minx = -10, stop, num = 5;
double best = 9999, AllEval = 0, sex = 0.88, C = 0.1;

struct Per{
	double x[3], f, Eval, r;
} c1[100], c2[100], c3[100], Bestc;

double fit(double x1, double x2) {
	return x1 * x1 + x2 * x2;
}

void renew(Per* t) {
	//Per*h = &Bestc;
	//cout << "renew t->f:" << t->f << endl;
	if ((t->f) < best) {
		Bestc = *t;
		best = t->f;
	}
	//Per*h = &Bestc;
	//cout << "h->f" << h->f << endl;
}

void start() {
	Per* t;
	for (int i = 0; i < num; i++) {
		t = &c1[i];
		for (int j = 0; j < 2; j++) {
			t->x[j] = (rand() % 10000) / 500.0 - 10;
			//cout << "t->x[" << j << "]: " << t->x[j] << endl;
		}
		t->f = fit(t->x[0], t->x[1]);
		//cout << "t->f" << t->f << endl;
		AllEval += t->f;
		renew(t);
		//cout << i << endl;
	}
	//t = &Bestc;
	//cout <<  "t = &Bestc" << t->f << endl;
}

void RWS() {
	int j = 0;
	double m = 0;
	//double r = (rand() % 100) / 100.0;
	double r = 0.5;
	//cout << "r:" << r << endl;
	Per* t;
	while (j < num) {
		for (int i = 0; i < num; i++) {
			t = &c1[i];
			m += t->Eval;
			while (m > 1.0) --m;
			if (r <= m) {
				t->r = (rand() % 100) / 100.0;
				c2[j++] = *t;
				//cout << "c2:" << i << endl;
			}
		}
	}
}

void select() {
	Per* t;
	for (int i = 0; i < num; i++) {
		t = &c1[i];
		t->Eval = t->f / AllEval;
		//cout << "t->Eval:" << t->Eval << endl;
	}
	RWS();
	//cout << "RWS" << endl;
}

void turn() {
	int h = 0, a = 0;
	while (h < num) {
		Per* t1;
		Per* t2;
		t1 = &c2[a];
		if (t1->r < sex) {
			//cout << "t1->r;" << t1->r << endl;
			int n = rand() % num;
			t2 = &c2[n];
			//cout << "t2 = &c2[n];" << n << endl;
			int size = rand() % 2;
			for (int i = size; i < 2; i++) 
				swap(t2->x[i], t1->x[i]);
			h++;
		}
		h++;
		a = (a + 1) % num;
	}
}

void change() {
	for (int i = 0; i < num; i++) {
		Per* t;
		t = &c2[i];
		for (int j = 0; j < 2; j++) {
			double r = (rand() % 100) / 100.0;
			if (r < C) t->x[j] = (rand() % 20) - 10;
		}
		t->f = fit(t->x[0], t->x[1]);
		//cout << "t->f" << t->f << endl;
		AllEval += t->f;
		renew(t);
		//cout << i << endl;
	}
}


int main() {
	while (true) {
		cout << "please enter an int(stop)" << endl;
		cin >> stop;
		while (stop--) {
			//cout << stop << endl;
			start();
			select();
			turn();
			change();
			//sex = (rand() % 100) / 100.0;
			//C = (rand() % 100) / 100.0;
		}
		Per* t = &Bestc;
		cout << "Bestc x[0]:" << t->x[0] << "  x[1]:" << t->x[1] << endl;
	}
	
	return 0;
}
