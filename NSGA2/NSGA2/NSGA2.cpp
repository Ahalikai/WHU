#include <iostream>
#include <math.h>
using namespace std;

int num, dim, iters;
double x_min, x_max, pcross = 0.4, pmutation = 0.1;
double new_pop[1000][1000], pop[1000][1000], merge_pop[2000][1000], crowding_distance[2000];
double ft[1000][10];

int Np[1000], Sp[1000][1000];
int Pa[1000][1000], p1[1000], rank1[1000], H[1000]; //p1 = pop[][].size

int p2 = 0;// p2 = pop[].size


#pragma region donminate.py

void Fit(int x, int d) {
	double f = 0.0, f1 = pop[x][0];
	for (int i = 0; i <= d - 1; i++)
		f = f + 9 * (pop[x][i + 1]) / (d - 1);
	double g = 1 + f, f2 = g * (1 - (f1 / g) * (f1 / g));
	ft[x][1] = f1;
	ft[x][2] = f2;
	//return f1, f2
}

bool dominate(int x, int y) {
	int equal = 1;
	for (int i = 0; i < dim; i++) {
		if (pop[x][i] != pop[y][i]) equal = 0;
	}
	if (equal = 1) return false;

	for (int i = 0; i < dim; i++) {
		if (pop[x][i] > pop[y][i])
			return false;
	}
	return true;
}

void non_dominate(int n, int d) {
	memset(p1, 0, sizeof(p1));
	int slen[1000], s = 0;
	memset(slen, 0, sizeof(slen));
	for (int i = 0; i < n; i++) 
		Fit(i, d);
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (i == j) continue;
			if (dominate(i, j))
				Sp[s][slen[s]++] = j;
			if (dominate(i, j))
				Np[i] = Np[i] + 1;
		}
		s++;
		if (Np[i] == 0) {
			Pa[0][p1[0]++] = i;
			rank1[i] = 1;
		}
	}

	int i = 0;
	p2 = 0;
	while (p1[i] > 0) {
		memset(H, 0, sizeof(H));
		int hlen = 0;
		for (int j = 0; j < p1[i]; j++) {
			int index = Pa[i][j];
			for (int k = 0; k < slen[index]; k++) {
				int index2 = Sp[index][k];
				Np[index2]--;
				if (Np[index2] == 0) {
					H[hlen++] = Sp[index][k];
					rank1[index2] = i + 2;
				}
			}
		}
		i++;
		p2++;
		for (int j = 0; j < hlen; j++) {
			Pa[p2][p1[p2]++] = H[j];
		}
	}
	//return P, rank, fitness (Pa, rank1, ft)
}
#pragma endregion


void selection() {
	non_dominate(num, dim);

	for (int i = 0; i < num; i++) {
		int r1 = rand() % num;
		int r2 = rand() % num;

		while(r1 == r2) r2 = rand() % num;

		if (rank1[r1] < rank1[r2])
			for (int j = 0; j < dim; j++) new_pop[i][j] = pop[r1][j];
		else 
			for (int j = 0; j < dim; j++) new_pop[i][j] = pop[r2][j];
	}
}

void crossover() {
	for (int i = 0; i < num - 1; i += 2) {
		double a = (rand() % 10000) / 10000.0;
		if (a < pcross) {
			for (int j = 0; j < dim; j++) {
				new_pop[i][j] = a * pop[i][j] + (1 - a) * pop[i + 1][j];
				new_pop[i + 1][j] = a * pop[i + 1][j] + (1 - a) * pop[i][j];
			}
		}
	}
}

void mutatioin() {
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < dim; j++) {
			double a = (rand() % 10000) / 10000.0;
			if (a < pmutation) {
				double un = ((rand() % 20000) / 10000.0) - 1.0;
				new_pop[i][j] = new_pop[i][j] + un * 0.2;
				if (new_pop[i][j] < x_min)
					new_pop[i][j] = x_min;
				if (new_pop[i][j] > x_max)
					new_pop[i][j] = x_max;
			}
		}
	}
}

void contact() {
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < dim; j++) {
			merge_pop[i][j] = pop[i][j];
			merge_pop[i + num][j] = new_pop[i][j];
		}
	}
}

int cmp(const void *a, const void *b)
{
	int *c = (int *)a;
	int *d = (int *)b;
	if (*c != *d)
		return *c - *d;
	return *(d + 1) - *(c + 1);
}

void crowd_distance() {
	int index;
	for (int i = 0; i < p2 - 1; i++) {
		double f1[1000][2], f2[1000][2];
		for (int j = 0; j < p1[i]; j++) {
			index = Pa[i][j];
			f1[j][0] = ft[index][0];
			f1[j][1] = Pa[i][j];
			f2[j][0] = ft[index][1];
			f2[j][1] = Pa[i][j];
		}
		crowding_distance[int(f1[0][1])] = 100000;
		crowding_distance[int(f1[p1[i] - 1][1])] = 100000;

		double f1_min = f1[0][0],
			f1_max = f1[p1[i] - 1][0],
			f2_min = f2[0][0],
			f2_max = f2[p1[i] - 1][0];

		for (int a = 1; a < p1[i] - 2; a++) {
			index = int(f1[a][1]);
			crowding_distance[index] = (f1[a + 1][0] - f1[a - 1][0]) / (f1_max - f1_min + 1) + (f2[a + 1][0] - f2[a - 1][0]) / (f2_max - f2_min + 1);
		}

	}
}

void select_newpop() {
	double in1[1000];
	int N = 0, count = 0;
	while (N < num) {
		N += p2;
		count++;
	}
	int index;
	int k = 0;
	if (N == num) {
		for (int i = 0; i < count; i++) {
			for (int j = 0; j < p1[i]; j++) {
				index = Pa[i][j];
				for (int t = 0; t < dim; t++)
					pop[k][t] = merge_pop[index][t];
				in1[k] = index;
				k++;
			}
		}
	}
	else {
		for (int i = 0; i < count - 1; i++) {
			for (int j = 0; j < p1[i]; j++) {
				index = Pa[i][j];
				for (int t = 0; t < dim; t++)
					pop[k][t] = merge_pop[index][t];
				in1[k] = index;
				k++;
			}
		}

		int add = num - k;
		index = count - 1;

		double temp[1000][2];

		for (int i = 0; i < p1[index]; i++) {
			temp[i][0] = crowding_distance[Pa[index][i]];
			temp[i][1] = Pa[index][i];
		}
		qsort(temp, num, sizeof(temp[0]), cmp);

		for (int i = 0; i < add; i++) {
			int a = int(temp[i][1]);
			for (int t = 0; t < dim; t++)
				pop[k][t] = merge_pop[a][t];
			in1[k] = a;
			k++;
		}
	}
}


#pragma region Init.py
void init_pop(int n, int d) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < d; j++) {
			pop[i][j] = (rand() % 10000) / 10000.0;
		}
	}
}
#pragma endregion

void space(int t) {
	for (int i = 0; i < t; i++) cout << " ";
}

void draw() {
	non_dominate(num, dim);
	space(100);
	for (int i = 0; i < num; i++) {
		space(int(ft[i][1] * 100));
		cout << '.' << endl;
	}
}


void nsga2(int nums, int di, int iter, double mix, double max) {
	num = nums;
	dim = di;
	iters = iter;
	x_min = mix;
	x_max = max;

	init_pop(num, dim);

	selection();
	crossover();
	mutatioin();

	for (int i = 1; i <= iters; i++) {
		cout << i << endl;
		crossover();
		mutatioin();
		contact();
		non_dominate(2 * num, dim);
		crowd_distance();
		select_newpop();
	}

	draw();
}

int main()
{
	nsga2(120, 30, 300, 0, 1);
	return 0;
}