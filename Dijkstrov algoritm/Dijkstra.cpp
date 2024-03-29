// Dijkstra.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <queue>     
#include <vector>
#include <string>
using namespace std;

int vel, stPov;
int C[30][30];
struct vozlisce {
	string voz;
	int v;
	int predhodnik;
	int predhodnikVozlisce;
	double dolzina;
}; 
void beri(string f) {
	fstream dat(f.c_str(), fstream::in);
	dat >> vel;
	int i = 0;
	int p, q, c;

	while (!dat.eof()) {
		dat >> p >> q >> c;
		C[p - 1][q - 1] = c;
		C[q - 1][p - 1] = c;
		i++;
	}
	dat.close();
}
int _tmain() {
	beri("Graf.txt");
	cout << "Velikost: " << vel << endl;
	for (int j = 0; j < vel; j++) {
		for (int i = 0; i < vel; i++)
			cout << C[i][j] << " ";
		cout << endl;
	}

	return 0;
}
int Meni() {
	int i;
	do {
		cout << "\nDijkstrov algoritem - izbira:\n" << endl;
		cout << "1. Nalozi graf" << endl;
		cout << "2. Zagon algoritma" << endl;
		cout << "3. Izpis najkrajse poti" << endl;
		cout << "4. Konec\n" << endl;
		cout << "Vasa izbira: ";
		cin >> i;
	} while (i > 4 || i < 1);

	return i;
}
void Zamenjaj(vector<vozlisce> &a, int prvi, int drugi) {
	vozlisce pomozna;

	pomozna = a[prvi];
	a[prvi] = a[drugi];
	a[drugi] = pomozna;
}
int Deli(vector<vozlisce> &a, int dno, int vrh)
{
	int desni, levi, mediana;
	double pe;

	mediana = (dno + vrh) / 2;
	Zamenjaj(a, dno, mediana);

	pe = a[dno].dolzina;

	desni = vrh;
	levi = dno;

	while (levi < desni)
	{
		while ((a[levi].dolzina <= pe) && (levi < vrh)) {
			levi++;
		}
		while ((a[desni].dolzina >= pe) && (desni > dno)) {
			desni--;
		}

		if (levi < desni) {
			Zamenjaj(a, levi, desni);
		}
		else {
			Zamenjaj(a, dno, desni);
		}
	}
	return(desni);
}
void HitroUredi(vector<vozlisce> &a, int dno, int vrh) {

	int j;
	if (dno < vrh)
	{
		j = Deli(a, dno, vrh);
		HitroUredi(a, dno, j - 1);
		HitroUredi(a, j + 1, vrh);
	}
}
vozlisce Najmanjsi(vector<vozlisce> &Q) {
	vozlisce min = Q.front();
	int stevec = 0;
	int stevec1 = 0;

	for (vector<vozlisce>::iterator x = Q.begin(); x < Q.end(); x++) {
		if (min.dolzina > x->dolzina) {
			min = *x;
			stevec1 = stevec;
		}
		stevec++;
	}
	Q.erase(Q.begin() + stevec1);
	return min;
}
void Dijkstrov_algoritem(vozlisce G[], vozlisce &s) {
	vector<vozlisce> Q;
	int stevec = 0;
	int pomoc = 0;

	for (int i = 0; i < vel; i++) {
		G[i].voz = 65 + i;
		G[i].v = i;
		G[i].dolzina = INFINITY;
		G[i].predhodnik = NULL;
	}
	/*for (int j = 0; j <stPov; j++) {
		if (G[j].p >= 0 >= 0 && G[j].q >=0 && G[j].cena >= 0) {
			d[G[j].p-1].v = G[j].p;
			d[G[j].p-1].voz = 64 + G[j].p;
			d[G[j].q - 1].v = G[j].q;
			d[G[j].q - 1].voz = 64 + G[j].q;
		}
		else {
			pomoc++;
		}
	}
	vel = vel - pomoc;
	 -> nisi se ziher c bo druga moznost delala, druga je zgoraj 
	for (int j = 0; j <stPov; j++) {
		if (G[j].p == stevec || G[j].q == stevec && G[j].p >= 0) {
			d[pomoc].v = stevec;
			d[pomoc].voz = 64 + d[pomoc].v;
			stevec++;
			pomoc++;
		}
	}*/
	s.dolzina = 0;
	s.predhodnikVozlisce = -1;

	for (int i = 0; i<vel; i++) {
		Q.push_back(G[i]);
	}

	while (!Q.empty()) {
		HitroUredi(Q, 0, Q.size() - 1);
		vozlisce u = Najmanjsi(Q);
		stevec = Q.size()-1;
		for (int i = 0; i < vel; i++) {
			if (C[u.v][i] != 0) {
				if (G[i].dolzina > C[u.v][i] + u.dolzina) {
					/*cout << "___________________________________________________________" << endl;
					cout << "Q vzeto: " <<u.voz << endl;
					cout <<"cena povezave iz "<<u.voz<<" v "<< G[i].voz<<" je "<< C[u.v][i] << endl;
					cout <<"Trenutrna dozlina" <<G[i].voz<<" je "<< G[i].dolzina << endl;*/
					G[i].dolzina = C[u.v][i] + u.dolzina;
					//cout << "Zdaj nastavljena dozlina " << G[i].voz << " je " << G[i].dolzina << endl;
					G[i].predhodnik = u.dolzina;
					G[i].predhodnikVozlisce = u.v;
					//cout << "predhodnik vozlisca " << G[i].voz <<" ima dolzino " <<G[i].predhodnik << endl;
					for (int j = 0; j < Q.size(); j++) {
						if (i == Q[j].v) {
							//cout << "Q[j].voz " << Q[j].voz << endl;
							Q[j].dolzina = C[u.v][i] + G[i].predhodnik;
						}
					}
				//	cout << "Q[i-stevec].dolzina " << Q[i - stevec].dolzina << endl;
				}
			}
		}
	}
}
void IzpisPoti(vozlisce G[], vozlisce &s, vozlisce &v, int dolzina) {
	
	if (s.v == v.v) {
		cout << v.voz <<endl;
		cout << "Dolzina poti do " << s.voz << " je " << dolzina << endl;
	}
	else if(G[v.v].predhodnikVozlisce == -1){
		cout << "Med " << s.voz << " in " << v.voz << " ni poti" << endl;
	}
	else {
		cout << v.voz << " ";
		IzpisPoti(G, s, G[v.predhodnikVozlisce], dolzina);
	}
}
int main()
{
	int izbira = 1, i = 0;
	bool drevo = true;
	string name;
	vozlisce *g = new vozlisce;
	vozlisce *prvi = new vozlisce;
	int d = 0, skupaj=0;

	while (izbira != 4) {

		izbira = Meni();

		if (izbira == 1) {
			_tmain();
			g = new vozlisce[vel];
		}
		else if (izbira == 2) {
			cout << "Dolocite izhodiscno vozlisce z stevilom na voljo imate naslednja vozlisca: " << endl;
			for (int i = 0; i < vel; i++) {
				name = 65 + i;
				cout << "Vozlisce: " << name <<" - "<<i<< endl;
			}
			cout << "Vasa izbira: " << endl;
			cin >> i;
			prvi = &g[i];
			Dijkstrov_algoritem(g, *prvi);
			skupaj = 0;
			for (int i = 0; i < vel; i++) {
				cout << "Vozlisce: " << g[i].voz << " Predhodnik: " << g[i].predhodnikVozlisce << " ima dolzino " << g[i].dolzina << endl;
				skupaj += g[i].dolzina;
			}
			cout << "Cena oz. dolzina vseh sprejetih poti skupaj znasa: " << skupaj << endl;
			drevo = true;
		}
		else if (izbira == 3) {
			if (drevo == true) {

				cout << "Vnesite ime cilnjega vozlisca" << endl;
				cin >> name;

				for (i = 0; i < vel; i++) {
					if (g[i].voz == name) {
						break;
					}
				}
				IzpisPoti(g, *prvi, g[i], g[i].dolzina);
				d = 0;
			}
			else {
				cout << "Iskalno drevo se ni generirano." << endl;
			}
		}
		else {
			exit(0);
		}

	}

	return 0;
}