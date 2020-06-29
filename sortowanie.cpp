#include<iostream>
#include<fstream>
#include<string>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <time.h>

using namespace std;


clock_t start, stop;
double czas_bubble, czas_quicksort, czas_convert, czas_sort;
string daneS[100005];
float liczby[100000];
float srednia = 0;

void read_CSV_file()
{
	fstream file;
	file.open("Dane.csv", ios::in);
	if (file.good() == true)
	{
		string line;
		for (int i = 0; i < 100005; i++)
		{
			getline(file, line);
			daneS[i] = line;
		}
		system("cls");
		cout << "Uzyskano dostep do pliku!" << endl;
	}
	else
		cout << "Nie uzyskano dostępu do pliku!" << endl;
	Sleep(2000);
	for (int i = 0; i < 100005; i++)
	{
		if (i > 4)
		{
			liczby[i - 5] = strtof((daneS[i]).c_str(), 0);
		}
	}
	file.close();
}

void save_CSV_file(float liczby[])
{
	fstream file;
	file.open("wynik.csv", ios::out);
	file << "# Plik z danymi SDiZO grupa xxxx coĹ›tam. coĹ›tam" << endl;
	file << "[SDIZO]" << endl;
	file << "READ_RECORDS=500000 # Liczba rekordĂłw do wczytania" << endl;
	file << "READ_AS=float # Typ danych do wczytania - float/int" << endl;
	file << "[DATA]" << endl;
	file << "Bubblesort [ms];" << "Qucksort [ms];" << "Counting sort [ms];" << "Heapsort [ms];" << endl;
	file << czas_bubble << ";" << czas_quicksort << ";" << czas_convert << ";" << czas_sort << endl;
	file << "Średnia;" << srednia << endl;

	for (int i = 1; i < 100000; i++)
	{
		file << liczby[i] << endl;
	}

	if (file.good() == true) {
		cout << "Zapisano";
		file.close();
	}
	else {
		cout << "Wynik nie zapisany" << endl;
	}
	file.close();
}


float average(float liczby[])
{

	for (int i = 0; i < 100000; i++)
	{
		srednia = srednia + liczby[i];
	}
	srednia = srednia / 100000;
	cout << "Srednia zbioru wynosi: " << srednia;
	return srednia;
}

void bubble_sort(float liczby[])
{
	float bufor;
	cout << "Trwa sortowanie algorytmem babelkowym. Prosze czekac." << endl;
	for (int i = 0; i < 99999; i++)
	{
		for (int j = 0; j < 99999; j++)
		{
			if (liczby[j] < liczby[j - 1])
			{
				bufor = liczby[j - 1];
				liczby[j - 1] = liczby[j];
				liczby[j] = bufor;
			}
		}
	}
	cout << "Posortowano!" << endl;
}

void quicksort(int p, int r, float* tab)
{
	int i = 0;
	int j = 0;
	float piwot = tab[r];

	for (j = i = p; i < r; i++)
	{
		if (tab[i] < piwot)
		{
			swap(tab[i], tab[j]);
			j++;
		}
	}
	swap(tab[r], tab[j]);
	if (p < j - 1)
		quicksort(p, j - 1, tab);
	if (j + 1 < r)
		quicksort(j + 1, r, tab);
}

int min_element(int* tab, int size)
{
	int min_element = tab[1];
	for (int i = 0; i < size; i++)
	{
		if (min_element > tab[i])
			min_element = tab[i];
	}
	return min_element;
}

int max_element(int* tab, int size)
{
	int max_element = tab[1];
	for (int i = 0; i < size; i++)
	{
		if (max_element < tab[i])
			max_element = tab[i];
	}
	return max_element;
}
void Countingsort(int tab_int[], int rozmiar)
{
	int i, j;
	float key;
	for (i = 1; i < rozmiar; i++) {
		key = tab_int[i];
		j = i - 1;

		while (j >= 0 && tab_int[j] > key) {
			tab_int[j + 1] = tab_int[j];
			j = j - 1;
		}
		tab_int[j + 1] = key;
	}
}

void convert(float liczby[])
{
	cout << "Trwa sortowanie algorytmem przez zliczanie" << endl;
	int tab_int[100000 - 3];
	for (int i = 0; i < 100000 - 3; i++)
		tab_int[i] = (int)liczby[i];
	Countingsort(tab_int, 100000 - 3);
	cout << "Posortowano" << endl;

	for (int i = 0; i < 100000 - 3; i++)
		liczby[i] = (float)tab_int[i];

}
////////////////////
void Heap(float* tab, int heap_size, int i) //heapify
{
	int largest;
	float temp;
	int l = 2 * i, r = (2 * i) + 1;
	if (l <= heap_size && tab[l] > tab[i])
		largest = l;
	else largest = i;
	if (r <= heap_size && tab[r] > tab[largest])
		largest = r;
	if (largest != i)
	{
		temp = tab[largest];
		tab[largest] = tab[i];
		tab[i] = temp;
		Heap(tab, heap_size, largest);
	}
}
void budujKopiec(float* tab, int rozmiar)
{
	for (int i = rozmiar / 2; i > 0; i--)
		Heap(tab, rozmiar, i);
}

void sort(float* tab, int rozmiar)
{
	float temp;
	budujKopiec(tab, rozmiar);
	for (int i = rozmiar; i > 1; i--)
	{
		temp = tab[i];
		tab[i] = tab[1];
		tab[1] = temp;
		rozmiar--;
		Heap(tab, rozmiar, 1);


	}
	for (int i = 0; i < 100000 - 3; i++)
		liczby[i] = (float)tab[i];

}
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //uchwyt

void gotoxy(int x, int y) //ustawienie kursora teksyu
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(handle, c);
}

void WriteMenuPos(string& str, int id, int idset)
{
	if (id == idset)
	{
		SetConsoleTextAttribute(handle, 240);
		cout << str << "[" << id << "]" << endl;
		SetConsoleTextAttribute(handle, 7);
	}
	else {
		cout << str << "[" << id << "]" << endl;
	}

}

//rysowanie ramki
void WriteLine(unsigned int width)
{
	for (unsigned int i = 0; i < width; i++)
	{
		cout << "=";
	}
	cout << endl;
}

//rysowanie menu
int Menu(string title, vector<string>& tMenu, int& id)
{
J:
	gotoxy(1, 1);
	WriteLine(title.size());
	cout << title << endl;
	WriteLine(title.size());
	for (int i = 0; i < tMenu.size(); i++)
	{
		WriteMenuPos(tMenu[i], i, id);
	}
	int s = _getch();
	if (s == 224)
	{
		s = s << 8;
		s |= _getch();
	}
	switch (s)
	{
	case(224 << 8) | 72:
		id = id ? id - 1 : 0;
		gotoxy(1, 1);
		goto J;
	case(224 << 8) | 80:
		id = id + 1 < tMenu.size() ? id + 1 : tMenu.size() - 1;
		gotoxy(1, 1);
		goto J;
	default:
		if (s > 47 && s < 48 + tMenu.size())
		{
			id = s - 48;
			return id;
		}
		break;
	}
	return id;
}



int main() {

	vector<string> iMenuG;
	iMenuG.push_back("0. Wgraj dane z pliku");
	iMenuG.push_back("1. Sortowanie algorytmem babelkowym");
	iMenuG.push_back("2. Sortowanie algorytmem szybkim");
	iMenuG.push_back("3. Sortownaie przez zliczanie");
	iMenuG.push_back("4. Sortowanie kopcowe");
	iMenuG.push_back("5. Obliczenie sredniej arytmetycznej");
	iMenuG.push_back("6. Zapisz plik wynikowy");
	iMenuG.push_back("7. Zamknij program");
	int id = 0;

	//srand(time(NULL));
	do
	{
		Menu("Menu Glowne", iMenuG, id);
		system("cls");
		switch (id)
		{
		case 0:
			system("cls");
			read_CSV_file();
			cout << "Wcisnij y jesli chcesz przejsc do MENU" << endl;
			if (_getch() == 'y')
				id = 0;
			cout << endl;
			break;
		case 1:
			system("cls");
			start = clock();
			bubble_sort(liczby);
			stop = clock();
			czas_bubble = (double)(stop - start);
			cout << "Czas sortowania wyniosl: " << czas_bubble << "ms" << endl;
			cout << "Wcisnij y jesli chcesz przejsc do MENU" << endl;
			if (_getch() == 'y')
				id = 0;
			cout << endl;
			break;
		case 2:
			system("cls");
			start = clock();
			quicksort(0, 99999, liczby);
			stop = clock();
			czas_quicksort = (double)(stop - start);
			cout << "Czas sortowania wyniosl: " << czas_quicksort << "ms" << endl;
			cout << "Wcisnij y jesli chcesz przejsc do MENU" << endl;
			if (_getch() == 'y')
				id = 0;
			cout << endl;
			break;
		case 3:
			system("cls");
			start = clock();
			convert(liczby);
			stop = clock();
			czas_convert = (double)(stop - start);
			cout << "Czas sortowania wyniosl: " << czas_convert << "ms" << endl;
			cout << "Wcisnij y jesli chcesz przejsc do MENU" << endl;
			if (_getch() == 'y')
				id = 0;
			cout << endl;
			break;
		case 4:
			system("cls");
			start = clock();
			sort(liczby, 100000);
			stop = clock();
			czas_sort = (double)(stop - start);
			cout << "Czas sortowania wyniosl: " << czas_sort << "ms" << endl;
			cout << "Wcisnij y jesli chcesz przejsc do MENU" << endl;
			if (_getch() == 'y')
				id = 0;
			cout << endl;
			Sleep(2000);
			break;
		case 5:
			system("cls");
			average(liczby);
			Sleep(2000);
			break;
		case 6:
			system("cls");
			save_CSV_file(liczby);
			Sleep(2000);
			break;
		case 7:
		{
			cout << "Wcisnij y jesli chcesz wyjsc z programu";
			if (_getch() == 'y')
				id = -1;
			cout << endl;
		}
		break;
		}
		if (id > 0)
		{
			WriteLine(50);
			cout << "Wcisnij enter, aby przejsc do MENU";
			_getch();
		}
		system("cls");
	} while (id > -1);
	cout << "Wcisnij enter, aby zamknac program";
	cin.get();
	return 0;
}
