#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

typedef struct book
{
	string name;
	string type;
	string author;
	string price;
	string year;
}book;

struct nodeBook
{
	book data;
	nodeBook* pnext;
};

typedef struct nodeBook nodeBook;

typedef struct listBook
{
	nodeBook* phead = NULL;
	nodeBook* ptail = NULL;
}listBook;

void menu();
istream& operator >> (istream& is, book& a);
nodeBook* create(book x);
void clearFile(string infile, string outfile);
void writeFile(listBook listBook, string file);
void addBook(listBook& l, book x);
void addTail(listBook& l, nodeBook* p);
void readABook(ifstream& filein, book& book);
void outListBook(listBook l);
void loadFile(listBook& l);
void deleteBook(listBook& l, string name);
void EditNameBook(listBook& l, string nameBook);
void sortName(listBook& l);
void sortPrice(listBook& l);
void sortYear(listBook& l);
void outOneBook(book book);
void lookForNameBook(listBook l, string nameBook);
void writeInforBook(ofstream& fileout, book book);

void main()
{
	menu();
	system("pause");
}
void menu()
{
	listBook listBook;
	loadFile(listBook);
	bool check = true;
	while (check == true)
	{
		system("cls");
		cout << "1. Them sach" << endl;
		cout << "2. In danh sach sach" << endl;
		cout << "3. Xoa sach theo ten" << endl;
		cout << "4. Sap xep theo ten" << endl;
		cout << "5. Sap xep theo gia" << endl;
		cout << "6. Sap xep theo nam" << endl;
		cout << "7. Tim kiem sach theo ten" << endl;
		cout << "8. Sua thong tin sach" << endl;
		cout << "0. Thoat" << endl;
		int op;
		cout << "Nhap lua chon: "; 
		cin >> op;
		switch (op)
		{
		case 1:
		{
			int cnt; 
			cout << "nhap so luong sach can them: ";
			cin >> cnt;
			cin.ignore();
			for (int i = 1; i <= cnt; i++)
			{
				cout << "\t\t------- nhap sach " << i << " ----------" << endl;

				book x;
				cin >> x;
				addBook(listBook, x);
			}
			break;
		}
		case 2:
		{
			outListBook(listBook);
			system("pause");
			break;
		}
		case 3:
		{
			string vt;
			cin.ignore();
			cout << "Nhap ten sach can xoa: "; 
			getline(cin, vt);
			deleteBook(listBook, vt);
			cout << "Da xoa" << endl;
			system("pause");
			break;
		}
		case 4:
		{
			sortName(listBook);
			cout << "Da sap xep va xuat ra file" << endl;
			system("pause");
			break;
		}

		case 5:
		{
			sortPrice(listBook);
			cout << "Da sap xep va xuat ra file" << endl;
			system("pause");
			break;
		}
		case 6:
		{
			sortYear(listBook);
			cout << "Da sap xep va xuat ra file" << endl;
			system("pause");
			break;
		}
		case 7:
		{
			string name;
			cin.ignore();
			cout << "Nhap ten sach can tim kiem: ";
			getline(cin, name);
			lookForNameBook(listBook, name);
			system("pause");
			break;
		}
		case 8:
		{
			string name;
			cin.ignore();
			cout << "Nhap ten sach can sua: ";
			getline(cin, name);
			EditNameBook(listBook, name);
			system("pause");
			break;
		}
		case 0:
		{
			check = false;
			break;
		}
		}
	}
}
istream& operator >> (istream& is, book& a)
{
	cout << "Nhap ten sach: "; getline(is, a.name);
	cout << "Nhap the loai: "; getline(is, a.type);
	cout << "Nhap tac gia: "; getline(is, a.author);
	cout << "Nhap gia sach: "; getline(is, a.price);
	cout << "Nhap nam them: "; getline(is, a.year);


	return is;
}

nodeBook* create(book x)
{
	nodeBook* p = new nodeBook;
	p->data = x;
	p->pnext = NULL;
	return p;
}

void addTail(listBook& l, nodeBook* p)
{
	if (l.phead == NULL) {
		l.phead = p;
		l.ptail = p;
	}
	else {
		l.ptail->pnext = p;
		l.ptail = p;
	}
}

void writeFile(listBook listBook, string file) {
	ofstream fileout;
	fileout.open(file, ios::out);
	for (nodeBook* k = listBook.phead; k != NULL; k = k->pnext)
	{
		writeInforBook(fileout, k->data);
		fileout << endl;
	}
	fileout.close();
}

void clearFile(string infile, string outfile) {
	vector<string> lines;
	string line;


	ifstream input_file(infile);;
	while (getline(input_file, line)) {
		lines.push_back(line);
	}

	for (int i = 0; i < lines.size(); i++) {
		if (lines[i] == ",,,,") 
		{
			lines.erase(lines.begin() + i);
		}
	}
	input_file.close();

	ofstream fileoutt;
	fileoutt.open(outfile, ios::out);
	for (int i = 0; i < lines.size(); i++) {
		fileoutt << lines[i] << endl;
	}

	fileoutt.close();
}

void addBook(listBook& l, book x)
{
	nodeBook* p = create(x);
	if (l.phead == NULL)
	{
		l.phead = l.ptail = p;
	}
	else
	{
		l.ptail->pnext = p;
		l.ptail = p;
	}

	writeFile(l, "test.TXT");
	clearFile("test.TXT" , "test.TXT");
}

void printBook(book book) {

	cout << "Ten sach: " << book.name << endl;
	cout << "The loai: " << book.type << endl;
	cout << "Ten tac gia: " << book.author << endl;
	cout << "Gia sach: " << book.price << endl;
	cout << "Nam them: " << book.year << endl;
}

void outListBook(listBook l)
{
	int i = 1;
	int t = 0;
	for (nodeBook* k = l.phead; k != NULL; k = k->pnext)
	{
		if (k->data.type == "") {
			t++;
		}
		else {
			cout << "\t\t------ Sach " << i++ << " ------" << endl;
			printBook(k->data);
		}


	}
}

void readABook(ifstream& filein, book& book) 
{
	getline(filein, book.name, ',');
	//filein.seekg(1, 1);
	getline(filein, book.type, ',');
	//filein.seekg(1, 1);
	getline(filein, book.author, ',');
	//filein.seekg(1, 1);
	getline(filein, book.price, ',');
	//filein.seekg(1, 1);
	getline(filein, book.year);
	//filein.ignore();
}

void loadFile(listBook& l)
{

	ifstream filein("test.txt");

	while (!filein.eof())
	{
		book a;
		readABook(filein, a);
		nodeBook* p = create(a);
		addTail(l, p);
	}

	filein.close();
}

void deleteBook(listBook& l, string name)
{
	nodeBook* h = NULL;
	for (nodeBook* k = l.phead; k != NULL; )
	{
		if (_stricmp(k->data.name.c_str(), name.c_str()) == 0 && k == l.phead)
		{
			l.phead = l.phead->pnext;
			delete k;
			k = l.phead;	
		}
		else
		{
			if (_stricmp(k->data.name.c_str(), name.c_str()) == 0)
			{
				h->pnext = k->pnext;
				delete k;
				k = h;

				if (h->pnext == NULL)
				{
					l.ptail = h;
					return;
				}
			}

			h = k;
			k = k->pnext;
		}
	}



	writeFile(l, "test.TXT");
	clearFile("test.TXT", "test.TXT");
}

void sortName(listBook& l)
{
	for (nodeBook* k = l.phead; k->pnext != NULL; k = k->pnext)
	{
		for (nodeBook* h = k->pnext; h != NULL; h = h->pnext)
		{
			if (_stricmp(h->data.name.c_str(), k->data.name.c_str()) < 0)
			{
				swap(k->data, h->data);
			}
		}
	}

	writeFile(l, "sapXepTheoTen.TXT");
	writeFile(l, "test.TXT");
	clearFile("sapXepTheoTen.TXT", "sapXepTheoTen.TXT");
	clearFile("test.TXT", "test.TXT");

}

void sortPrice(listBook& l)
{
	for (nodeBook* k = l.phead; k->pnext != NULL; k = k->pnext)
	{
		for (nodeBook* h = k->pnext; h != NULL; h = h->pnext)
		{
			if (_stricmp(h->data.price.c_str(), k->data.price.c_str()) < 0)
			{
				swap(k->data, h->data);
			}
		}
	}

	writeFile(l, "sapXepTheoGia.TXT");
	writeFile(l, "test.TXT");
	clearFile("sapXepTheoGia.TXT", "sapXepTheoGia.TXT");
	clearFile("test.TXT", "test.TXT");
}

void sortYear(listBook& l)
{
	for (nodeBook* k = l.phead; k->pnext != NULL; k = k->pnext)
	{
		for (nodeBook* h = k->pnext; h != NULL; h = h->pnext)
		{
			if (_stricmp(h->data.year.c_str(), k->data.year.c_str()) < 0)
			{
				swap(k->data, h->data);
			}
		}
	}

	writeFile(l, "sapXepTheoNam.TXT");
	writeFile(l, "test.TXT");
	clearFile("sapXepTheoNam.TXT", "sapXepTheoNam.TXT");
	clearFile("test.TXT", "test.TXT");
}

void outOneBook(book book)
{
	cout << "\nTen sach: " << book.name;
	cout << "\nThe loai :" << book.type;
	cout << "\nTac gia:" << book.author;
	cout << "\nGia sach:" << book.price;
	cout << "\nNam them:" << book.year;
}

void lookForNameBook(listBook l, string nameBook)
{
	int check = 0;
	for (nodeBook* k = l.phead; k != NULL; k = k->pnext) {
		check++;
	}
	int check2 = 0;
	for (nodeBook* k = l.phead; k != NULL; k = k->pnext)
	{
		string name = k->data.name;
		if (_stricmp(name.c_str(), nameBook.c_str()) == 0)
		{
			outOneBook(k->data);
			cout << endl << endl;
		}
		else {
			check2++;
		}
	}

	if (check == check2) {
		cout << "khong co sach nay trong danh sach" << endl;
	}
}

void EditNameBook(listBook& l, string nameBook)
{
	for (nodeBook* k = l.phead; k != NULL; k = k->pnext)
	{
		string name = k->data.name;
		if (_stricmp(name.c_str(), nameBook.c_str()) == 0)
		{
			cout << endl << "Thong tin hien tai" << endl;
			outOneBook(k->data);
			cout << endl << endl;

		}
	}

	cout << "Thong tin can chinh sua" << endl;
	string nameN, typeN, authorN, priceN, yearN;
	cout << "Nhap lai ten sach: ";
	cin >> nameN;
	cout << "Nhap lai the loai sach: ";
	cin >> typeN;
	cout << "Nhap lai tac gia : ";
	cin >> authorN;
	cout << "Nhap lai gia sach : ";
	cin >> priceN;
	cout << "Nhap lai nam them : ";
	cin >> yearN;

	for (nodeBook* k = l.phead; k != NULL; k = k->pnext)
	{
		string name = k->data.name;
		if (_stricmp(name.c_str(), nameBook.c_str()) == 0)
		{

			k->data.name = nameN;
			k->data.author = authorN;
			k->data.type = typeN;
			k->data.price = priceN;
			k->data.year = yearN;
			cout << endl << endl;

		}
	}

	writeFile(l, "test.TXT");
	clearFile("test.TXT", "test.TXT");
}

void writeInforBook(ofstream& fileout, book book)
{
	fileout << book.name << ",";
	fileout << book.type << ",";
	fileout << book.author << ",";
	fileout << book.price << ",";
	fileout << book.year;
}