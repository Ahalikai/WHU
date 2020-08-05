#include <iostream>
#include<algorithm>
using namespace std;

struct Per {
	int xi[4];
	double f;
} X[10];

double pi[4];
int n = 3, all = 8, stop;

void fit(Per* t) {
	t->f = 0;
	for (int i = 0; i < n; i++) {
		t->f += t->xi[i];
	}
}

bool cmp(Per t1, Per t2) {
	return (t1.f > t2.f);
}


void reP(int re) {
	Per* t;
	cout << "reP:" << endl;
	for (int j = 0; j < n; j++) {
		pi[j] = 0;
		for (int i = 0; i < re; i++) {
			t = &X[i];
			pi[j] += t->xi[j];
		}
		pi[j] /= re;
		cout << pi[j] << " ";
	}
	cout << endl;
}

void start() {
	Per* t;
	//cout << "start:" << endl;
	for (int i = 0; i < all; i++) {
		t = &X[i];
		for (int j = 0; j < n; j++) {
			t->xi[j] = rand() % 2;
			//		cout << t->xi[j] << " ";
		}
		fit(t);
		//	cout << endl;
	}
}

void born() {
	for (int i = all / 2; i < all; i++) {
		cout << i << " : ";
		for (int j = 0; j < n; j++) {
			(rand() % 100) > (pi[j] * 100) ? X[i].xi[j] = 0 : X[i].xi[j] = 1;
			cout << X[i].xi[j] << " ";
		}
		cout << endl;
	}
}

void cssort() {
	for (int i = 0; i < all; i++){
		cout << X[i].f << " ";
	}
	cout << endl;
}

int main()
{
	while (true) {
		cout << "Please enter an int(stop):" << endl;
		cin >> stop;
		start();
		reP(all);
		do {
			sort(X, X + all, cmp);
			cssort();
			reP(all / 2);
			born();
			reP(all);
		} while (stop--);
		for (int i = 0; i < n; i++) cout << pi[i] << " ";
		cout << endl;
	}
	return 0;
}

