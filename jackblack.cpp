#include <iostream>
#include <vector>
#include <random>
#include <cstdlib> 
#include <ctime> 
#include <string>

#define pradine_suma 100;
using namespace std;

enum spalvos { BUGNAI, SIRDYS, PIKAI, KRYZIAI };
const string spalvos_pav[] = { "BUGNAI", "SIRDYS", "PIKAI", "KRYZIAI"};
const string skaiciai[] = {"DU","TRYS","KETURI","PENKI","SESI","SEPTYNI","ASTUONI","DEVYNI","DESIMT","A","J","Q","K"};


class Korta
{
public:
	int skaicius;
	spalvos spalva;

	Korta(int s, spalvos sp) : skaicius(s), spalva(sp) {}

public:
	int gautiReiksme() const
	{
		return (skaicius >= 10) ? 10 : skaicius + 2;
	}

	void atvaizdavimas() const
	{
		cout << skaiciai[skaicius] << " " << spalvos_pav[spalva] << endl;
	}
};

void PildytiKortas(vector<Korta>& kortos);
bool ArTesti();
bool TikrintiStatyma(double& statymas, double suma);
void RandKorta(vector<Korta>& kortos, vector<Korta>& zmogus);
bool Veiksmas(vector<Korta>& kortos, vector<Korta>& zmogus, int& zaidejo_taskai);
void SkaiciuotiTaskus(vector<Korta>& zmogus, int &taskai);
bool TikrintiPergale(int zaidejo_taskai, int dalintojo_taskai);
void DalintojoEjimas(vector<Korta>& kortos, vector<Korta>& zmogus, int& dalintojo_taskai);

int main()
{
	vector<Korta> kortos;
	vector<Korta> zaidejas;
	vector<Korta> dalintojas;
	double statymas=0;
	double suma = pradine_suma;
	bool trStat = false;
	int zaidejo_taskai=0;
	int dalintojo_taskai=0;
	
	PildytiKortas(kortos);

	cout << "SVEIKI ATVYKE I BLACKJACK ZAIDIMA!!" << endl;

	while (suma > 0 )
	{
		zaidejas.clear();
		dalintojas.clear();
		zaidejo_taskai = 0;
		dalintojo_taskai = 0;
		cout << "Jusu pinigai: " << suma << endl;
		do trStat=TikrintiStatyma(statymas, suma);
		 while (trStat == false);

		suma = suma - statymas;
		cout << "Jusu kortos: " << endl;
		for (int i = 0; i < 2; i++)
		{
			RandKorta(kortos, zaidejas);
			zaidejas[i].atvaizdavimas();
		}
		cout << "Dalintojo kortos: " << endl;
		for (int i = 0; i < 2; i++)
		{
			RandKorta(kortos, dalintojas);
			if (i == 0) dalintojas[i].atvaizdavimas();
		}
		cout << "Kitos dalintojo kortos pasleptos :)" << endl;

		SkaiciuotiTaskus(zaidejas, zaidejo_taskai);
		cout <<"Jusu taskai: "<< zaidejo_taskai << endl;

		SkaiciuotiTaskus(dalintojas, dalintojo_taskai);

		if (zaidejo_taskai == 21);
		else
		{
			while (Veiksmas(kortos, zaidejas, zaidejo_taskai) == true && zaidejo_taskai < 21);
		}

		while(dalintojo_taskai<17)DalintojoEjimas(kortos, dalintojas, dalintojo_taskai);
		
		cout << "Dalintojo taskai: " << dalintojo_taskai << endl;
		if(TikrintiPergale(zaidejo_taskai,dalintojo_taskai)) suma += statymas * 2;

		if (ArTesti() == false)
		{
			cout << "VISO GERO!!" << endl;
			return 0;
		}
	}
	
}

void PildytiKortas(vector<Korta> &kortos)
{
	kortos.clear();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			kortos.push_back(Korta(j,static_cast<spalvos>(i)));
		}
	}
}

bool ArTesti()
{
	bool arTesti = true;
	char testi;
	
	do
	{
		cout << "ar norite testi?(Y/N)" << endl;
		cin >> testi;
		switch (testi)
		{
		case 'Y':
			arTesti = true;
			return arTesti;
		case 'N':
			arTesti = false;
			return arTesti;
		default:
			cout << "netinkamas simbolis, iveskite is naujo" << endl;
			break;
		}
	} while ((testi != 'Y') && (testi != 'N'));
	return arTesti;
}

bool TikrintiStatyma(double &statymas, double suma)
{
	cout << "Statymas: ";
	cin >> statymas;

	if (statymas > suma)
	{
		cout << "permazai pinigu iveskite is naujo" << endl;
		return false;
	}
	else if (statymas <= 0)
	{
		cout << "neigiamu arba nuliniu statymu negali buti iveskite is naujo" << endl;
		return false;
	}
	else return true;

}

void RandKorta(vector<Korta> &kortos, vector<Korta>&zmogus)
{
	srand(time(0));
	int randomSk = rand() % kortos.size();
	zmogus.push_back(kortos[randomSk]);
	auto pos = kortos.begin() + randomSk;
	kortos.erase(pos);
}

bool Veiksmas(vector<Korta>& kortos, vector<Korta>& zmogus, int &zaidejo_taskai)
{
	char ch;
	
		cout << "Ka norite daryti? H(Hit)/S(Stand) " << endl;
		cin >> ch;
		switch (ch)
		{
		case 'H':
			RandKorta(kortos, zmogus);
			SkaiciuotiTaskus(zmogus, zaidejo_taskai);
			cout << "Jusu taskai: "<<zaidejo_taskai << endl;
			return true;
			break;
		case 'S':
			return false;
			break;
		default:
			cout << "tokio pasirinkimo nera" << endl;
			return true;
			break;			
		}

}

void SkaiciuotiTaskus(vector<Korta>& zmogus,int &taskai)
{
	taskai = 0;
	for (int i = 0; i < zmogus.size(); i++)taskai += zmogus[i].gautiReiksme();
}

bool TikrintiPergale(int zaidejo_taskai, int dalintojo_taskai)
{
	if (zaidejo_taskai == 21)
	{
		cout << "You win" << endl;
		return 1;
	}
	if (dalintojo_taskai == 21)
	{
		cout << "Dealer wins" << endl;
		return 0;
	}
	if (zaidejo_taskai == dalintojo_taskai)
	{
		cout << "You win" << endl;
		return 1;
	}
	else if (zaidejo_taskai<21 && dalintojo_taskai>21)
	{
		cout << "You win" << endl;
		return 1;
	}
	else if ((zaidejo_taskai < 21 && dalintojo_taskai < 21) && zaidejo_taskai > dalintojo_taskai)
	{
		cout << "You win" << endl;
		return 1;
	}
	else
	{
		cout << "Dealer wins" << endl;
		return 0;
	}
}

void DalintojoEjimas(vector<Korta>& kortos, vector<Korta>& zmogus, int& dalintojo_taskai)
{
	if (dalintojo_taskai < 17)
	{
		RandKorta(kortos, zmogus);
		SkaiciuotiTaskus(zmogus, dalintojo_taskai);
	}
}