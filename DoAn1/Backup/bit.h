#ifndef CL_BIT_H
#define CL_BIT_H
#include <vector>
#include<string>
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
	QFloat operator=(const double&a);

	std::string PhepCongThapPhan(const std::string& a, const std::string& b);
	std::string MuAm(const int &value, int mu);
	std::string PhepChia(const std::string& base10, int& phandu, int value);
	int count0(const std::string& str);
	std::string IntToBin(std::string src);
	std::string floatToBin(std::string src);


	void BinToBit(const std::string& base2);
	void DecToBit(const std::string& base10);
	std::string BitToBin();
	std::string BitToDec();
	QFloat(const double & a)
	{
		this->DecToBit(std::to_string(a));
	}
private:
	static const int nBitCount = 128;
	container MangBit = container(nBitCount / (sizeof(value_type)*8), 0);

};

#endif