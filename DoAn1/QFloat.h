#ifndef CL_BIT_H
#define CL_BIT_H
#include<iostream>
#include <vector>
#include<string>
#include"CongCu.h"
using namespace CongCu;
class QFloat
{

public:
	typedef unsigned char value_type;
	typedef std::vector<value_type> container;

	void BatBit(int);
	void TatBit(int);
	void ChuyenBit(int, bool);
	bool LayBit(int) const;
	bool operator[](int i) { return LayBit(i); }
	QFloat(const std::string& val, Base base);
	QFloat operator=(const double&a);
	QFloat operator=(const std::string& a);
	friend std::ostream& operator<<(std::ostream& outDev, QFloat x);

	static std::string PhepCongThapPhan(const std::string& a, const std::string& b);
	static std::string MuAm(const int &value, int mu);
	static int count0(const std::string& str);

	static std::string IntToBin(std::string src);
	static std::string floatToBin(std::string src);

	static bool KiemTraChuoi(std::string val, std::string& msg);
	static bool KiemTraCoSo(std::string val, Base base, std::string& msg);

	void BinToBit(const std::string& base2);
	void DecToBit(const std::string& base10);

	std::string BitToBin();
	std::string BitToDec();

	QFloat(const double & a)
	{
		this->DecToBit(std::to_string(a));
	}
	QFloat(const std::string& a)
	{
		this->DecToBit(a);
	}
	QFloat() { }

private:
	static const int nBitCount = 128;
	container MangBit = container(nBitCount / (sizeof(value_type) * 8), 0);

};




#endif