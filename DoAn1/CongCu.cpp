#include "CongCu.h"

std::string CongCu::PhepNhan(const std::string& base10, int value)
{
	int sen = (base10[0] == '-') ? 1 : 0;
	std::string output = base10;
	int mod = 0;
	for (int i = base10.length() - 1; i >= sen; i--)
	{
		int cache = (base10[i] - '0') * value + mod;
		mod = cache / 10;
		output[i] = char(cache % 10 + 48);
	}
	if (mod > 0)
		output.insert(output.begin() + sen, char(mod + 48));
	return output;

}

std::string CongCu::PhepChia(const std::string& base10, int& phandu, int value)
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

std::string CongCu::PhepCong(std::string left, std::string right)
{
	// Thêm 0 cho đến khi độ dài hai chuỗi bằng nhau

	while (left.length() < right.length()) left.insert(left.begin(), '0');
	while (right.length() < left.length()) right.insert(right.begin(), '0');


	int sum = 0, carry = 0;
	for (int i = left.length() - 1; i >= 0; i--)
	{
		sum = left[i] - '0' + right[i] - '0' + carry;
		carry = sum / 10;
		left[i] = sum % 10 + '0';
	}

	if (carry != 0) left.insert(left.begin(), 48 + carry);

	return left;
}
std::string CongCu::PhepLuyThua(const int& value, const  int& mu)
{
	std::string a;
	if (mu <= 30)
		return a = std::to_string(int(pow(value, mu)));
	else
	{
		a = std::to_string(int(pow(value, 30)));
		for (int i = 31; i <= mu; i++)
			a = PhepNhan(a, value);
	}
	return a;
}

std::string& CongCu::TrimStart(std::string& str, char c, size_t offset)
{
	size_t end = offset;
	for (auto i = str.begin() + offset; i != str.end(); i++)
	{
		if (*i == c) end++;
		else break;
	}
	if (end != offset)
		str.erase(str.begin() + offset, str.begin() + end);

	return str;
}
std::string& CongCu::TrimEnd(std::string& str, char c, size_t offset)
{
	size_t start = offset;
	for (auto i = str.rbegin() + offset; i != str.rend(); i++)
	{
		if (*i == c) start++;
		else break;
	}
	if (start != offset)
		str.erase(str.length() - start, str.length() - offset);

	return str;
}
std::string& CongCu::Trim(std::string& str, char c, size_t offset)
{
	TrimStart(str, c, offset);
	return TrimEnd(str, c, offset);
}

template<>
std::string CongCu::ToBit<std::string>(const std::string& val, bool IsSpace)
{
	std::string output;

	for (int i = 0; i <= val.length(); i++)
		std::string temp = ToBit<std::string::value_type>(val[i], false);
	return output;
}
template<>
std::string CongCu::ToBit<double>(const double& val, bool IsSpace)
{
	// 1 bit for sign
	// 11 bits for exponent
	// 52 bits for mantissa
	std::string output;

	unsigned char *p = (unsigned char*)&val;
	for (int i = 0; i < sizeof(double); i++)
	{
		std::string temp = ToBit<unsigned char>(p[i]);
		output.insert(output.begin(), temp.begin(), temp.end());
	}

	// 000000000000000000....0000000000000000
	// 0 00000000000 000000....0000000000000000
	if (IsSpace)
	{
		int s = 1, e = 12 + 1;
		output.insert(output.begin() + s, ' ');
		output.insert(output.begin() + e, ' ');
	}


	return output;
}
template<>
std::string CongCu::ToBit<float>(const float& val, bool IsSpace)
{
	//1 bit for sign
	//8 bits for exponent
	//21 bits for mantissa

	std::string output;

	unsigned char *p = (unsigned char*)&val;
	for (int i = 0; i < sizeof(float); i++)
	{
		std::string temp = ToBit<unsigned char>(p[i]);
		output.insert(output.begin(), temp.begin(), temp.end());
	}

	// 000000000000000000....0000000000000000
	// 0 000000000 000000....0000000000000000
	if (IsSpace)
	{
		int s = 1, e = 9 + 1;
		output.insert(output.begin() + s, ' ');
		output.insert(output.begin() + e, ' ');
	}

	return output;

}

std::string CongCu::HexToBin(const std::string& hex)
{
	std::string bin = "";
	for (int i = 0; i < hex.length(); i++)
	{
		switch (toupper(hex[i]))
		{
		case '0': bin.append("0000"); break;
		case '1': bin.append("0001"); break;
		case '2': bin.append("0010"); break;
		case '3': bin.append("0011"); break;
		case '4': bin.append("0100"); break;
		case '5': bin.append("0101"); break;
		case '6': bin.append("0110"); break;
		case '7': bin.append("0111"); break;
		case '8': bin.append("1000"); break;
		case '9': bin.append("1001"); break;
		case 'A': bin.append("1010"); break;
		case 'B': bin.append("1011"); break;
		case 'C': bin.append("1100"); break;
		case 'D': bin.append("1101"); break;
		case 'E': bin.append("1110"); break;
		case 'F': bin.append("1111"); break;
		}
	}
	return bin;
}

std::vector<bool> CongCu::CongBit(bool a, bool b)
{
	bool sum = a ^ b;
	bool carry = a && b;
	std::vector<bool> output = { sum,carry };
	output.shrink_to_fit();
	return output;
}

std::string CongCu::FromDecTo(std::string base10, Base base)
{
	int n = (base10[0] == '-') ? 1 : 0;
	std::string ChuoiKhong = std::string(base10.length(), '0');
	ChuoiKhong[0] = n ? '-' : '0';

	std::string KetQua = "";
	while (base10 != ChuoiKhong)
	{
		int value = 0;
		int SoDu = 0, Thuong = 0;
		for (int i = n; i < base10.length(); i++)
		{
			Thuong = (SoDu * 10 + (base10[i] - '0')) / base;
			SoDu = (SoDu * 10 + (base10[i] - '0')) % base;

			base10[i] = char(Thuong + 48);
		}
		if (0 <= SoDu && SoDu <= 9)
			KetQua.insert(KetQua.begin(), SoDu + '0');
		else if (10 <= SoDu)
			KetQua.insert(KetQua.begin(), SoDu + 55);
	}

	// Thêm dấu nếu nhận giá trị âm
	if (base != Binary)
		KetQua.insert(KetQua.begin(), '-');
	else
		KetQua.insert(KetQua.begin(), n + 48);

	return KetQua;
}

std::string& CongCu::NhomBit(std::string& ChuoiBit, unsigned int margin)
{
	size_t len = ChuoiBit.length();
	unsigned offset = 0;
	unsigned int i = margin;
	while (i < len)
	{
		ChuoiBit.insert(ChuoiBit.begin() + i + offset, ' ');
		i += margin;
		offset++;
	}
	return ChuoiBit;
}

std::string& CongCu::XoaBitThua(std::string& ChuoiBit, BitMode mode, unsigned int n)
{
	int i = FirstSignificantBit(ChuoiBit, mode);

	char Sign = ChuoiBit[0];
	char BitToAdd = (BitMode::ComplementTwo == mode) ? Sign : '0';
	// Từ vị trí sau bit dấu, xoá tất cả các bit thừa cho đến bit ý nghĩa đầu tiên
	TrimStart(ChuoiBit, BitToAdd, 1);

	//Thêm một lượng bit sao cho tổng số bit là một bội của n
	while ((++i + 1) % n != 0)
		ChuoiBit.insert(ChuoiBit.begin() + 1, BitToAdd);

	return ChuoiBit;
}

int CongCu::FirstSignificantBit(const std::string& ChuoiBit, BitMode mode)
{
	//Trường hợp bù 2: bất cứ bit nào có giá trị khác giá trị bit dấu là bit có nghĩa
	//Trường hợp chuẩn: bất cứ bit nào không phải bit 0 là bit có nghĩa

	char Sign = ChuoiBit[0];
	for (int i = 1; i < ChuoiBit.length(); i++)
	{
		char bit = ChuoiBit[i];
		if (mode == BitMode::ComplementTwo && bit != Sign) return ChuoiBit.length() - 1 - i;
		if (mode == BitMode::Standard && bit != '0') return ChuoiBit.length() - 1 - i;
	}
	return 0;
}
