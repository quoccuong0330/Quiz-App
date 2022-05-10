#include"DoHoa.h"
using namespace std;
//định dạng câu hỏi
struct CauHoi		//Tạo struct gồm có các thuộc tính của câu hỏi
{
	int STT;
	string Hoi;
	string cauA;
	string cauB;
	string cauC;
	string cauD;
	string DapAn;
};

struct Node			//Tạo Node cơ bản gồm 1 thuộc tính và 1 con trỏ
{
	CauHoi dulieu;
	Node* pNext;
};

struct List
{
	Node* pHead, * pTail; //Tạo List cơ bản gồm 2 con trỏ đầu và đuổi
};

void inIt(List& l)	//khởi tạo List
{
	l.pHead = l.pTail = NULL;
}

Node* getNode(CauHoi dulieu)	//Lưu dữ liệu vào Node
{
	Node* p = new Node;
	p->dulieu = dulieu;
	p->pNext = NULL;
	return p;
}

void addHead(List& l, CauHoi dulieu)
{
	Node* p = new Node;
	p->dulieu = dulieu;
	p->pNext = NULL;

	if (l.pHead != NULL)
	{
		p->pNext = l.pHead;
		l.pHead = p;
	}

}

void addTail(List& l, CauHoi dulieu)
{
	Node* p = new Node;
	p->dulieu = dulieu;
	p->pNext = NULL;

	if (l.pHead == NULL)
	{
		l.pHead = l.pTail = p;
		return;
	}

	l.pTail->pNext = p;
	l.pTail = p;

}

void delHead(List& l)
{
	if (l.pHead == NULL)
		return;
	Node* p = l.pHead;
	l.pHead = l.pHead->pNext;
	delete p;
}

void delTail(List& l)
{
	if (l.pHead == NULL)
		return;
	if (l.pHead == l.pTail)
	{
		delHead(l);
		return;
	}

	Node* p = l.pHead;
	while (p != NULL)
	{
		if (p->pNext == l.pTail)
		{
			delete l.pTail;
			l.pTail = p;
			p->pNext = NULL;
			return;
		}
		p = p->pNext;
	}

}

void delAny(List& l)
{
	int x;
	cin >> x;
	if (l.pHead == NULL)
		return;
	if (l.pHead->dulieu.STT == x)
		delHead(l);
	if (l.pTail->dulieu.STT == x)
		delTail(l);

	Node* p = l.pHead;
	while (p != NULL)
	{
		if (p->dulieu.STT == x)
		{
			Node* g = new Node;
			g->pNext = p->pNext;
			delete p;
			g = p;
			return;
		}
		p = p->pNext;
	}
	cout << "\nKhong xoa duoc";
}



//định dạng thông tin
struct DN
{
	string HoTen;
	string GioiTinh;
	string MSSV;
};

struct NodeDN
{
	DN data;
	NodeDN* Next;
};

struct ListDN
{
	NodeDN* Head, * Tail;
};

void inItDN(ListDN& L)
{
	L.Head = L.Tail = NULL;
}

NodeDN* GetNode(DN dulieu)
{
	NodeDN* p = new NodeDN;
	p->data = dulieu;
	p->Next = NULL;
	return p;
}

void addTailDN(ListDN& l, NodeDN* p)
{
	if (l.Head == NULL)
		l.Head = l.Tail = p;
	else
	{
		l.Tail->Next = p;
		l.Tail = p;
	}
}



//thao tác với file cauhoi
void Doc_file_CauHoi(List& l)	//Thao tác Nhập bằng filestream
{
	ifstream filein; //Đọc dữ liệu FILE từ CHƯƠNG TRÌNH
	filein.open("cauhoi.txt", ios_base::in); //Mở FILE

	if (filein.fail() == true)	//Nếu mà không tìm thấy file thì chương trình sẽ thoát
	{
		cout << "\nFile does not exit.";
		system("pause");
		exit(0);
		return;
	}

	//Đọc dữ liệu từ FILE
	while (!filein.eof())
	{
		CauHoi data;
		filein >> data.STT;

		filein.ignore();
		getline(filein, data.Hoi);
		getline(filein, data.cauA);
		getline(filein, data.cauB);
		getline(filein, data.cauC);
		getline(filein, data.cauD);
		getline(filein, data.DapAn);
		addTail(l, data);	//Đọc dữ liệu từ FILE truyền vào LIST 
	}
	filein.close(); //Đóng FILE
}

void Ghi_CauHoi(ofstream& fileout, CauHoi data)
{
	//Ghi dữ liệu từ CHƯƠNG TRÌNH vào FILE
	fileout << data.STT << endl;
	fileout << data.Hoi << endl;
	fileout << data.cauA << endl;
	fileout << data.cauB << endl;
	fileout << data.cauC << endl;
	fileout << data.cauD << endl;
	fileout << data.DapAn << endl;
}

void CH(CauHoi& data)
{
	gotoxy(49, 5);
	cout << "2. ADD THE QUESTION";
	cin.ignore();
	gotoxy(45, 8);
	cout << "Enter the question: ";
	getline(cin, data.Hoi);
	gotoxy(45, 10);
	cout << "Enter answer A: ";
	getline(cin, data.cauA);
	gotoxy(45, 12);
	cout << "Enter answer B: ";
	getline(cin, data.cauB);
	gotoxy(45, 14);
	cout << "Enter answer C: ";
	getline(cin, data.cauC);
	gotoxy(45, 16);
	cout << "Enter answer D: ";
	getline(cin, data.cauD);
	gotoxy(45, 18);
	cout << "Enter the correct answer: ";
	getline(cin, data.DapAn);

}

void Themcauhoi(List& l)
{
	CauHoi data;
	CH(data);
	Node* p = getNode(data);
	addTail(l, data);
}

void Luu_Cauhoi(List l)	//Ghi LIST vào FILE
{
	ofstream fileout;
	fileout.open("cauhoi.txt", ios::out);
	int dem = 0;
	Node* p = l.pHead;
	while (p != NULL)
	{

		dem++;
		p->dulieu.STT = dem;
		Ghi_CauHoi(fileout, p->dulieu);
		if (p != l.pTail)
			fileout << endl;
		p = p->pNext;
	}
	fileout.close();
}

void TT(DN& tt)
{

	cin.ignore();
	gotoxy(45, 13);
	cout << "Enter your name: ";
	getline(cin, tt.HoTen);
	gotoxy(45, 15);
	cout << "Enter your sex: ";
	getline(cin, tt.GioiTinh);
	gotoxy(45, 17);
	cout << "Enter your ID: ";
	getline(cin, tt.MSSV);

}

void Xuat_ThongTin(DN tt)
{
	gotoxy(40, 12);
	cout << "Full name: " << tt.HoTen;
	gotoxy(40, 13);
	cout << "Sex: " << tt.GioiTinh;
	gotoxy(40, 14);
	cout << "ID: " << tt.MSSV;
}

//độ dài của danh sách
int size(List l)
{
	int size = 0;
	Node* p = l.pHead;
	while (p != NULL)
	{
		if (p->dulieu.Hoi == "")
			size--;
		size++;
		p = p->pNext;
	}
	return size;
}

void xuat1CauHoi(CauHoi dulieu)
{
	KhungCauHoi();
	gotoxy(30, 9);
	cout << " " << dulieu.Hoi << endl;
	KhungTraLoi(21, 13);
	gotoxy(22, 15);
	cout << " " << dulieu.cauA << endl;
	KhungTraLoi(64, 13);
	gotoxy(65, 15);
	cout << " " << dulieu.cauB << endl;
	KhungTraLoi(21, 18);
	gotoxy(22, 20);
	cout << " " << dulieu.cauC << endl;
	KhungTraLoi(64, 18);
	gotoxy(65, 20);
	cout << " " << dulieu.cauD << endl;
}

void XuatCauHoi(List& l, CauHoi dulieu, DN tt)
{
	int temp = 0, t = 15; //t là tọa độ
	string dapAn;
	Node* p = l.pHead;
	system("cls");
	gotoxy(40, 12);
	cout << "The list has " << size(l) << " question(s).";	int num, x = 0;

	gotoxy(40, 14);
	cout << "Enter the number of questions you want: ";	//Nhập số lượng câu hỏi muốn làm
	while (true)
	{
		cin >> num;
		cout << endl;
		if (num <= size(l) && num !=0)
			break;
		gotoxy(40, t);
		cout << "Enter again: ";
		t++;

	}
	system("cls");
	gotoxy(45, 15);
	cout << "Press enter to get started.\n"; gotoxy(45, 16);
	system("pause");

	//Xuất câu hỏi theo thứ tự
	system("cls");
	while (p != NULL)
	{
		if (x == num)
			break;
		x++;

		xuat1CauHoi(p->dulieu); // xuat ra 1 cau hoi 
		int m = 25;
		gotoxy(47, m);
		cout << "Enter your answer: ";
		while (true)
		{
			cin >> dapAn;
			if (dapAn == "a" || dapAn == "b" || dapAn == "c" || dapAn == "d")
				break;
			m++;
			gotoxy(47, m);
			cout << "Enter again: ";
		}
		if (dapAn == p->dulieu.DapAn)
			temp++;
		system("cls");
		p = p->pNext;
	}
	system("cls");
	gotoxy(40, 12);
	Xuat_ThongTin(tt);
	gotoxy(40, 15);
	cout << "Number of correct answers: " << temp << "/" << num;
	gotoxy(40, 16);
	cout << "Your point: " << float(temp) * 10 / num << "\n";
	gotoxy(40, 30);
	system("pause");

}

Node* XoaNodeCoKhoaBatKy(List& l)
{
	gotoxy(49, 5);
	cout << "3. DELETE THE QUESTION";
	gotoxy(40, 12);
	cout << "The list has " << size(l) << " question(s).";
	gotoxy(40, 13);
	cout << "Enter the question you want to delete: ";
	int x;
	cin >> x;


	if (x > size(l) || x==0)
		return NULL;

	Node* p = l.pHead;
	while (p != NULL)
	{
		if (p->dulieu.STT == x)
		{
			system("cls");
			xuat1CauHoi(p->dulieu);
			break;
		}
			p = p->pNext;
	}

	char i;
	gotoxy(47, 25);
	cout << "Do you want to delete question (y/n): ";
	cin >> i;
	if (i == 'n' || i == 'N')
	{
		system("cls");
		return NULL;
	}

	else if (i == 'y' || i == 'Y')
	{
		if (l.pHead == NULL)
			return NULL;

		if (l.pHead->dulieu.STT == x)
		{
			delHead(l);
			return l.pHead;
		}

		if (l.pTail->dulieu.STT == x)
		{
			delTail(l);
			return l.pTail;
		}



		Node* g = new Node;

		for (Node* k = l.pHead; k != NULL; k = k->pNext)
		{
			if (k->dulieu.STT == x)
			{
				g->pNext = k->pNext;
				delete k;
				break;
			}
			g = k;
		}
		return g;
	}
}

void xuLyct(CauHoi data, List l, DN tt, ListDN L)
{
	int x;
	while (true)
	{
		cout << "\n\n\n\n\t\t\t\t\t\t\MULTIPLE-CHOICE PROGRAM\n\n\n\n\n";
		cout << "\t\t\t\t\t\t1. Join in room.\n";
		cout << "\t\t\t\t\t\t2. Add the question.\n";
		cout << "\t\t\t\t\t\t3. Delete the question.\n";
		cout << "\t\t\t\t\t\t4. Exit. \n";
		cout << "\n\t\t\t\t\t\Choose: ";
		cin >> x;
		system("cls");
		switch (x)
		{
		case 1:
			system("cls");
			if (size(l) == 0)
			{
				gotoxy(45, 15);
				cout << "No questions yet.";
				Sleep(1500);
				break;
			}
			TT(tt);
			XuatCauHoi(l, data, tt);
			break;

		case 2:
			gotoxy(45, 6);
			cout << "The list has " << size(l) << " question(s).";
			Themcauhoi(l);
			Luu_Cauhoi(l);
			system("cls");
			gotoxy(50, 15);
			cout << "Save successfully.";
			Sleep(1000);
			system("cls");
			break;

		case 3:
		{
			system("cls");
			if (size(l) == 0)
			{
				gotoxy(45, 15);
				cout << "No questions yet.";
				Sleep(1500);
				break;
			}
			system("cls");
			int d;
			Node* x = XoaNodeCoKhoaBatKy(l);
			if (x != NULL)
			{
				system("cls");
				gotoxy(55, 15);
				cout << "Done! \n";
				Luu_Cauhoi(l);
			}
			else
			{
				gotoxy(50, 15);
				cout << "Failed to delete!" << endl << endl;
			}
			Sleep(1000);
			system("cls");
			break;
		}
		case 4:
			cout << "\n\n\n\t\t\t\t\t\t\GROUP 12.\n";
			return;
		}
		system("cls");
	}
}

int main()
{

	SetConsoleTitle(L"Multiple-choice");
	ListDN L;
	DN tt;
	inItDN(L);

	List l;
	CauHoi data;
	inIt(l);

	Doc_file_CauHoi(l);
	xuLyct(data, l, tt, L);

	return 0;
}