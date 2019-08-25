#include "bit.h"
#include "QIntV2.h"


#pragma region -------------------------------THAO TÁC TRÊN BIT-------------------------------
bool QFloat::LayBit(int i) const
{
	if (i < 0 || i >= nBitCount)
		throw std::out_of_range("LayBit");
	int x = MangBit[MangBit.size() - 1 - i / (sizeof(value_type) * 8)];
	return (x >> (i % (sizeof(value_type) * 8))) & 1;
}
void QFloat::BatBit(int i)
{
	MangBit[MangBit.size() - 1 - i / (sizeof(value_type) * 8)] |= (1 << (i % (sizeof(value_type) * 8)));
}
void QFloat::TatBit(int i)
{
	MangBit[MangBit.size() - 1 - i / (sizeof(value_type) * 8)] &= ~(1 << (i % (sizeof(value_type) * 8)));
}
void QFloat::ChuyenBit(int vitri, bool bit)
{
	bit ? BatBit(vitri) : TatBit(vitri);
}
#pragma endregion


#pragma region -------------------------------OPERATOR-------------------------------
QFloat QFloat::operator=(const double& a)
{
	std::string base10 = std::to_string(a);
	DecToBit(base10);
	return *this;
}

#pragma endregion


std::string QFloat::PhepCongThapPhan(const std::string& a, const std::string& b)
{
	std::string c = a.substr(a.find(',') + 1);
	std::string d = b.substr(b.find(',') + 1);
	if (c.length() < d.length())
	{
		c.resize(d.length(), '0');
	}
	else
	{
		d.resize(c.length(), '0');
	}
	return PhepCong(c, d);
}
std::string QFloat::MuAm(const int &value, int mu)
{
	std::string output;
	if (mu < 7)
	{
		output = std::to_string(pow(value, -mu));
		output[1] = ',';
	}
	else
	{
		output = std::to_string(pow(value, -6));
		output = output.substr(output.find('.') + 1);
		for (int i = 7; i < mu + 1; i++)
		{
			int size = output.length();
			output = PhepNhan(output, 5);
			if (output.length() == size)
				output.insert(output.begin(), '0');
		}
		output.insert(output.begin(), ',');
		output.insert(output.begin(), '0');
	}

	return output;
}
std::string QFloat::PhepChia(const std::string& base10, int& phandu, int value)
{
	std::string result;
	int sodu = 0;
	int thuong = 0;
	for (int i = 0; i < base10.length(); i++)
	{
		thuong = (sodu * 10 + (base10[i] - '0')) / value;
		sodu = (sodu * 10 + (base10[i] - '0')) % value;
		result.push_back(char(thuong + 48));
	}
	phandu = sodu;
	return TrimStart(result, '0');
}


int QFloat::count0(const std::string& str)
{
	int kq = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '0') kq++;
	}
	return kq;
}

std::string QFloat::IntToBin(std::string src)
{
	int du = 0;
	std::string temp("");
	do
	{
		src = PhepChia(src, du, 2);
		temp.append(1, char(du + '0'));
	} while (src != "");
	std::string result("");
	for (std::string::reverse_iterator it = temp.rbegin();it != temp.rend();it++)
	{
		result.append(1, *it);
	}
	return result;
}
std::string QFloat::floatToBin(std::string src)
{
	std::string result("");
	std::string temp;
	int i = 0;
	do
	{
		temp = PhepNhan(src, 2);
		if (temp.length() > src.length())
		{
			result.append(1, '1');
			src = std::string(temp.begin() + 1, temp.end());
		}
		else
		{
			result.append(1, '0');
			src = temp;
		}
		i++;
		if (i == 112)
		{
			result[i - 2] = (result[i - 1] == '1') ? '1' : '0';
		}
	} while ((temp[0] != '1' || count0(temp) != temp.length() - 1) && i != 112);
	return result;
}


void QFloat::BinToBit(const std::string& base2)
{
	for (int i = 0;i < nBitCount;i++)
	{
		ChuyenBit(nBitCount - 1 - i, base2[i] - '0');
	}
}
void QFloat::DecToBit(const std::string& base10)
{

	int E;char sign;std::string F;
	sign = (base10[0] == '-') ? '1' : '0';
	int point = base10.find(',');
	std::string sub1 = (sign == '1') ? base10.substr(1, point - 1) : base10.substr(0, point);
	std::string sub2 = base10.substr(point + 1);

	std::string binOfInt = IntToBin(sub1);
	std::string binOfFloat = floatToBin(sub2);
	std::string binOfNumber = binOfInt + binOfFloat;
	int temp = binOfNumber.find('1');
	F = binOfNumber.substr(temp + 1);

	F.resize(111, '0');
	E = binOfInt.length() - temp - 1;

	std::string E_str = std::to_string(int(E + pow(2, 15) - 1));
	std::string E_e_str = IntToBin(E_str);

	std::string result("");
	result.append(1, sign);
	result += E_e_str;
	result += F;
	BinToBit(result);
}

std::string QFloat::BitToBin()
{
	std::string output;
	for(int i=nBitCount-1;i>=0;i--)
	{
		output.push_back(char(LayBit(i)+48));
	}
	output.insert(output.begin() + 1, ' ');
	output.insert(output.begin() + 17, ' ');
	return output;

}
std::string QFloat::BitToDec()
{
	std::string floatPoint = BitToBin();
	std::string result("");
	std::string sign, E_str, F_str;
	int E = 0;
	sign = floatPoint[0];
	E_str = std::string(floatPoint.begin() + 1, floatPoint.begin() + 17);
	F_str = std::string(floatPoint.begin() + 17, floatPoint.end());
	if (sign == "1")
		result.append("-");
	for (int i = 0; i < E_str.length(); i++)
	{
		E += (E_str[i] - '0')*pow(2, E_str.length() - i - 1);
	}
	E = E + 1 - pow(2, 15);
	std::string	integer_str = "1" + F_str.substr(0, E);
	std::string floating_str = F_str.substr(E);

	unsigned int integer = 0;
	for (int i = 0; i < integer_str.length(); i++)
	{
		integer += (integer_str[i] - '0')*pow(2, integer_str.length() - i - 1);
	}
	std::string floating = "0,0";
	for (int i = 0; i < floating_str.length(); i++)
	{
		if (floating_str[i] == '1')
			floating = PhepCongThapPhan(floating, MuAm(2, i + 1));
	}
	result += std::to_string(integer) + "," + floating;
	return result;
}