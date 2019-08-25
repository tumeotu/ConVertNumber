#include "XuLy.h"

using namespace std;
using namespace CongCu;
int main(int argc, char *argv[])
{
	//QFloat x;
	//x.BinToBit("0");
	//x.BitToDec();
	//QInt a;
	//cout << (3 % -10) << endl;
	//QInt a = -500000000;
	//QInt b = 3345343;
	//a /= b;
	//cout << a.DecString() << endl;
	//cout << (a % b).DecString() << endl;
	DocFile("input.txt", "output.txt", 1);
	//vector<string> MainMenu = { "QInt","QFloat","Nhap xuat tu file","Thoat" };
	//while (1)
	//{
	//	XuLy(Menu(MainMenu));
	//}
	//return 0;
}

//1010 -> QFloat -> -2 -> QFloat

//void menu()
//{
//	cout << "1. Nhap QFloat o he thap phan.\n";
//	cout << "2. Nhap QFloat o he nhi phan.\n";
//	cout << "3. Xuat QFloat o he thap phan.\n";
//	cout << "4. Xuat QFloat o he nhi phan.\n";
//	cout << "0. Thoat.\n";
//	cout << "Ban chon? ";
//}
//
//void work(int n, QFloat& x)
//{
//	switch (n)
//	{
//	case 1:
//	{
//		system("cls");
//		cout << "Nhap QFloat o he thap phan:\n";
//		string temp;
//		getline(cin >> ws, temp);
//		ScanQfloat_10(x, temp);
//		break;
//	}
//	case 2:
//	{
//		system("cls");
//		cout << "Nhap QFloat o he nhi phan:\n";
//		string temp;
//		getline(cin >> ws, temp);
//		ScanQfloat_2(x, temp);
//		break;
//	}
//	case 3:
//	{
//		system("cls");
//		cout << "QFloat o he thap phan:\n";
//		PrintQfloat_10(x);
//		system("pause");
//		break;
//	}
//	case 4:
//	{
//		system("cls");
//		cout << "QFloat o he nhi phan:\n";
//		PrintQfloat_2(x);
//		system("pause");
//		break;
//	}
//	default:
//		return;
//	}
//}