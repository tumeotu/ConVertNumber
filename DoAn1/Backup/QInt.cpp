#include "QInt.h"
#include <iostream>
using namespace std;
const int QInt::nBitCount = 128;


#pragma region --------------------------------- NON-MEMBER FUNCTIONS ---------------------------------
std::string PhepNhan(const std::string& base10, int value)
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
std::vector<bool> CongBit(bool a, bool b)
{
	bool sum = a ^ b;
	bool carry = a && b;
	std::vector<bool> output = { sum,carry };
	output.shrink_to_fit();
	return output;
}
std::string PhepCong(std::string left, std::string right)
{
	// Thêm 0 cho đến khi độ dài hai chuỗi bằng nhau

	while (left.length() < right.length()) left.insert(left.begin(), '0');
	while(right.length() < left.length()) right.insert(right.begin(), '0');


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
std::string PhepLuyThua(const int& value, const  int& mu)
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

std::string& TrimStart(std::string& str, char c, size_t offset)
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
std::string& TrimEnd(std::string& str, char c, size_t offset)
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
std::string& Trim(std::string& str, char c, size_t offset)
{
	TrimStart(str, c, offset);
	return TrimEnd(str, c, offset);
}
bool QInt::KiemTraChuoi(std::string val, std::string& msg)
{
	if (val == "" || val =="+" || val == "-")
	{
		msg = "Chuoi can it nhat 1 trong cac ki tu thuoc [0-9], [a-f], [A-F]";
		return false;
	}
	int SoDau = 0;
	std::string KiTuHopLe = "+-1234567890ABCDEFabcdef";
	for (int i = 0; i < val.length(); i++)
	{
		size_t pos = KiTuHopLe.find_first_of(val[i]);
		if (pos == std::string::npos)
		{
			msg = "Cac ki tu hop le: +,-,[0-9],[a-f],[A-F]";
			return false;
		}
		if (pos == 0 || pos == 1)
		{
			if (++SoDau > 1)
			{
				msg = "Chi cho phep ton tai 1 dau + hoac 1 dau -";
				return false;
			}
		}
		if (i > 0 && (pos == 0 || pos == 1))
		{
			msg = "Vi tri cua dau + hoac dau - khong hop le";
			return false;
		}
	}

	msg = "";
	return true;
}
template<>
std::string ToBit<std::string>(const std::string& val, bool IsSpace)
{
	std::string output;

	for (int i = 0; i <= val.length(); i++)
		std::string temp = ToBit<std::string::value_type>(val[i], false);

	return IsSpace ? QInt::NhomBit(output) : output;
}
template<>
std::string ToBit<double>(const double& val, bool IsSpace)
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
std::string ToBit<float>(const float& val, bool IsSpace)
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



#pragma endregion


#pragma region ------------------------------CONSTRUCTOR-------------------------------
QInt::QInt(const std::string& value, Base base)
{
	std::string msg;
	if (!KiemTraChuoi(value, msg))
	{
		std::cout << "Input: " << value << "\nError: " << msg << std::endl;
		std::cout << "Khoi tao mac dinh bang 0" << std::endl;
		return;
	}
	int n = value[0] == '+' ? 1 : 0;
	switch (base)
	{
	case Base::Binary:
		this->BinToQInt(value.substr(n));
		return;
	case Base::Demical:
		this->DecToQInt(value.substr(n));
		return;
	case Base::Hexademical:
		this->HexToQInt(value.substr(n));
		return;
	default:
		std::cout << "Error: Co so khong hop le. Chi cho phep 2,10,16\n";
		std::cout << "Khoi tao mac dinh bang 0" << std::endl;
		break;
	}
}
#pragma endregion


#pragma region -------------------------------BỘ CHUYỂN ĐỔI CƠ SỐ-------------------------------

std::string FromDecTo(std::string base10, Base base)
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
	if (base != Base::Binary)
		KetQua.insert(KetQua.begin(), '-');
	else
		KetQua.insert(KetQua.begin(), n + 48);

	return KetQua;
}

std::string HexToBin(const std::string& hex)
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

void QInt::BinToQInt(const std::string& base2)
{
	int ViTriBatDau = ((nBitCount <= base2.length()) ? nBitCount : base2.length()) - 1;

	for (int i = ViTriBatDau; i >= 1; i--)
	{
		ChuyenBit(ViTriBatDau - i, base2[i] - '0');
	}
	ChuyenBit(nBitCount - 1, base2[0] - '0');

	*this = LayBu2();
}

void QInt::HexToQInt(const std::string& base16)
{
	std::string base2;
	int n = (base16[0] == '-') ? 1 : 0;

	base2 = HexToBin(base16.substr(n));
	base2.insert(base2.begin(), n + 48);

	BinToQInt(base2);
}

std::string& QInt::QIntToBin(BitMode mode, std::string& output) const
{
	QInt temp = *this;

	if (mode == BitMode::Standard)
		temp = this->LayBu2();

	for (int i = 0; i < nBitCount; i++)
		temp[i] ? output.insert(output.begin(), '1') : output.insert(output.begin(), '0');

	return output;


}
std::string& QInt::QIntToDec(std::string& output) const
{
	output = "0";
	std::string input;

	QIntToBin(BitMode::Standard, input);
	for (int i = 1; i < nBitCount; i++)
	{
		if (input[i] == '1')
		{
			output = PhepCong(output, PhepLuyThua(2, nBitCount - 1 - i));
		}
	}

	if (input[0] == '1')
		output.insert(output.begin(), '-');

	return output;
}
std::string& QInt::QIntToHex(BitMode mode, std::string& output) const
{
	std::string input;
	QIntToBin(mode, input);

	input.insert(input.begin() + 1, LayBit(nBitCount - 1) ? '1' : '0');
	string tmp = "0000";
	for (int j = 1; j < nBitCount + 1; j += 4)
	{
		tmp = input.substr(j, 4);
		if (!tmp.compare("0000")) output += "0";
		else if (!tmp.compare("0001")) output += "1";
		else if (!tmp.compare("0010")) output += "2";
		else if (!tmp.compare("0011")) output += "3";
		else if (!tmp.compare("0100")) output += "4";
		else if (!tmp.compare("0101")) output += "5";
		else if (!tmp.compare("0110")) output += "6";
		else if (!tmp.compare("0111")) output += "7";
		else if (!tmp.compare("1000")) output += "8";
		else if (!tmp.compare("1001")) output += "9";
		else if (!tmp.compare("1010")) output += "A";
		else if (!tmp.compare("1011")) output += "B";
		else if (!tmp.compare("1100")) output += "C";
		else if (!tmp.compare("1101")) output += "D";
		else if (!tmp.compare("1110")) output += "E";
		else if (!tmp.compare("1111")) output += "F";
	}

	//Thêm dấu '-' nếu là số âm và xuất ở dạng chuẩn
	if (BitMode::Standard == mode && input[0] == '1')
		output.insert(output.begin(), '-');

	return output;
}
#pragma endregion


#pragma region -------------------------------XUAT-------------------------------
std::string QInt::HexString(BitMode mode, bool fullsize) const
{
	std::string output;
	QIntToHex(mode, output);
	if (!fullsize)
		XoaBitThua(output, mode, 4u);

	return NhomBit(output, 4u);
}
std::string QInt::BinString(BitMode mode, bool fullsize) const
{
	std::string output;
	QIntToBin(mode, output);
	if (!fullsize)
		XoaBitThua(output, mode);

	return NhomBit(output);
}
std::string QInt::DecString() const
{
	std::string output;
	return QIntToDec(output);
}


#pragma endregion


#pragma region -------------------------------PHEP TOAN TREN SO-------------------------------
QInt QInt::operator - () const
{
	// Ghi nhớ: Nếu dãy bit có giá trị dương thì cách biểu diễn ở dạng chuẩn và dạng bù 2 là như nhau
	// Suy ra:
	// Nếu giá trị dãy bit là 1 số dương => đảo bit dấu rồi lấy bù 2
	// Ngược lại nếu giá trị dãy bit là một số âm
	// => lấy bù 2 để đưa về dạng chuẩn rồi đảo bit dấu

	QInt output = *this;

	if (this->LayBit(nBitCount - 1))
	{
		output = output.LayBu2();
		output.ChuyenBit(nBitCount - 1, !output[nBitCount - 1]);
	}
	else
	{
		output.ChuyenBit(nBitCount - 1, !output[nBitCount - 1]);
		output = output.LayBu2();
	}



	return output;
}

QInt QInt::operator + (const QInt& a) const
{
	QInt result;

	int iSum = 0, iCarry = 1;
	std::vector<bool> LuotTruoc = { false,false }; // 0, 1
	std::vector<bool> BoNhoTam = { false,false };

	for (int i = 0; i < nBitCount; i++)
	{
		//Cộng 2 bit của mỗi hạng tử trước
		BoNhoTam = CongBit(this->operator[](i), a[i]); // 1 + 0 = 1, 0

		//Lưu carry của kết quả trên
		bool carry = BoNhoTam[iCarry]; // -> 0

		// Cộng kết quả trên với số nhớ từ kết quả của lượt trước đó (hay carry trong LuotTruoc)
		// suy ra tổng cuối cùng
		BoNhoTam = CongBit(BoNhoTam[iSum], LuotTruoc[iCarry]);// 1 + 1 = 0, 1

		// So sánh carry từ phép cộng ở bước 1 và ở kết quả trên
		// Chọn carry có giá trị lớn hơn
		LuotTruoc = { BoNhoTam[iSum],carry || BoNhoTam[iCarry] };

		result.ChuyenBit(i, LuotTruoc[iSum]);
	}
	return result;
}

QInt QInt::operator - (const QInt &a) const
{
	return this->operator+(-a);
}

QInt QInt::operator * (QInt Q) const
{
	QInt A = 0;
	bool Qminus1 = false;

	int n = nBitCount;
	while (n > 0)
	{
		bool Q0 = Q.LayBit(0);
		if (Q0 == true && Qminus1 == false)		//Q0Q1 = 10
		{
			A = A - *this;
		}
		else if (Q0 == false && Qminus1 == true)	//01
		{
			A = A + *this;
		}


		// Shift Right [A,Q,Q-1]
		bool A0 = A.LayBit(0);
		Qminus1 = Q0;
		Q = Q >> 1;
		Q.ChuyenBit(nBitCount - 1, A0);
		A = A >> 1;

		n--;
	}



	return Q;
}
QInt QInt::operator / (const QInt &M) const
{
	QInt Q = *this;
	QInt A;
	if (Q < 0)
	{
		A = -1;
		A.ChuyenBit(0, true);
	}

	int n = nBitCount;
	while (n > 0)
	{
		// Shift left [A,Q]
		bool Q0 = Q[nBitCount - 1];
		A << 1;
		A.ChuyenBit(0, Q0);
		Q << 1;

		A = A - M;

		if (A < 0)
		{
			Q.ChuyenBit(0, false);
			A = A + M;
		}
		else
			Q.ChuyenBit(0, true);

		n--;
	}

	return Q;
}
QInt QInt::operator % (const QInt &M) const
{
	QInt Q = *this;
	QInt A;
	if (Q < 0)
	{
		A = -1;
		A.ChuyenBit(0, true);
	}

	int n = nBitCount;
	while (n > 0)
	{
		// Shift left [A,Q]
		bool Q0 = Q[nBitCount - 1];
		A << 1;
		A.ChuyenBit(0, Q0);
		Q << 1;

		A = A - M;

		if (A < 0)
		{
			Q0 = false;
			A = A + M;
		}
		else
			Q0 = true;

		n--;
	}

	return A;
}

#pragma endregion


#pragma region -------------------------------THAO TÁC TRÊN BIT-------------------------------
bool QInt::LayBit(int i) const
{
	if (i < 0 || i >= nBitCount)
		throw std::out_of_range("LayBit");
	int x = MangBit[MangBit.size() - 1 - i / (sizeof(value_type) * 8)];
	return (x >> (i % (sizeof(value_type) * 8))) & 1;
}
void QInt::BatBit(int i)
{
	MangBit[MangBit.size() - 1 - i / (sizeof(value_type) * 8)] |= (1 << (i % (sizeof(value_type) * 8)));
}
void QInt::TatBit(int i)
{
	MangBit[MangBit.size() - 1 - i / (sizeof(value_type) * 8)] &= ~(1 << (i % (sizeof(value_type) * 8)));
}
void QInt::ChuyenBit(int vitri, bool bit)
{
	bit ? BatBit(vitri) : TatBit(vitri);
}
QInt QInt::LayBu1() const
{
	if (LayBit(nBitCount - 1) == false) //Số dương không đổi
		return *this;

	QInt output = *this;
	for (int i = 0; i < nBitCount - 1; i++)
		output.ChuyenBit(i, !this->LayBit(i));

	return output;
}
QInt QInt::LayBu2() const
{
	if (LayBit(nBitCount - 1) == false) //Số dương không đổi
		return *this;

	QInt output = this->LayBu1();

	int i = 0;
	while (i < nBitCount && output.LayBit(i))
		output.TatBit(i++);
	if (i < nBitCount) output.BatBit(i);

	return output;
}
QInt QInt::XoayBit()const
{
	QInt output;
	for (int i = 0; i < nBitCount; i++)
		output.ChuyenBit(nBitCount - 1 - i, LayBit(i));
	return output;
}

#pragma endregion


#pragma region ------------------------------- SO SÁNH GIÁ TRỊ SỐ-------------------------------
bool QInt::IsZero() const
{
	for (int i = 0; i < nBitCount; i++)
	{
		if (this->LayBit(i)) return false;
	}
	return true;
}
bool QInt::operator==(const QInt& a) const
{
	return !(bool)this->operator^(a);

}
bool QInt::operator>(const QInt& a) const
{
	if (this->operator==(a)) return false;

	bool SignBitLeft = this->LayBit(nBitCount - 1);	// false là dương, true là âm
	bool SignBitRight = a.LayBit(nBitCount - 1);

	if (SignBitLeft < SignBitRight) return true;
	if (SignBitLeft > SignBitRight) return false;

	for (int i = 0; i < nBitCount; i++)
	{
		bool _this = this->LayBit(i);
		bool _a = a.LayBit(i);

		// Số dương
		if (!SignBitLeft && this->LayBit(i) < a.LayBit(i)) return false;

		// Số âm
		if (SignBitLeft &&this->LayBit(i) > a.LayBit(i)) return false;

	}
	return true;
}
bool QInt::operator<(const QInt& a) const
{
	return !(this->operator>(a) || this->operator==(a));
}
bool QInt::operator>=(const QInt& a) const
{
	return !this->operator<(a);
}
bool QInt::operator<=(const QInt& a) const
{
	return !this->operator>(a);
}
bool QInt::operator!=(const QInt& a) const
{
	return !this->operator==(a);
}
bool QInt::operator!() const
{
	return this->IsZero();
}
#pragma endregion


#pragma region ------------------------------- CÁC PHÉP TOÁN TRÊN BIT -------------------------------
QInt QInt::operator&(const QInt& a) const
{
	QInt output;
	for (int i = 0; i < MangBit.size(); i++)
		output.MangBit[i] = this->MangBit[i] & a.MangBit[i];
	return output;
}
QInt QInt::operator|(const QInt& a) const
{
	QInt output;
	for (int i = 0; i < MangBit.size(); i++)
		output.MangBit[i] = this->MangBit[i] | a.MangBit[i];
	return output;
}
QInt QInt::operator^(const QInt& a) const
{
	QInt output;
	for (int i = 0; i < MangBit.size(); i++)
		output.MangBit[i] = this->MangBit[i] ^ a.MangBit[i];
	return output;
}
QInt QInt::operator~() const
{
	QInt output;
	for (int i = 0; i < MangBit.size(); i++)
		output.MangBit[i] = ~this->MangBit[i];
	return output;
}

QInt QInt::operator<<(int offset) const
{
	QInt output = 0;
	for (int i = nBitCount-1; i >= offset; i--)
	{
		output.ChuyenBit(i, LayBit(i - offset));
	}
	//*this = output;
	return output;
}
QInt QInt::operator>>(int offset) const
{
	bool n = LayBit(nBitCount - 1) ? true : false;
	QInt output;
	int i;
	for (i = 0; i < nBitCount - offset; i++)
	{
		output.ChuyenBit(i, LayBit(i + offset));
	}
	for (i; i < nBitCount; i++)
		output.ChuyenBit(i, n);
	return output;
}
#pragma endregion


int QInt::FirstSignificantBit() const
{
	bool Sign = this->LayBit(nBitCount - 1);
	for (int i = nBitCount - 2; i >= 0; i--)
	{
		bool bit = this->LayBit(i);
		if (Sign == true && bit == false) return  i;
		else if (Sign == false && bit == true) return i;
	}
	return 0;
}

int QInt::FirstSignificantBit(const std::string& ChuoiBit, BitMode mode)
{
	//Trường hợp bù 2: bất cứ bit nào có giá trị khác giá trị bit dấu là bit có nghĩa
	//Trường hợp chuẩn: bất cứ bit nào không phải bit 0 là bit có nghĩa

	char Sign = ChuoiBit[0] - '0';
	for (int i = 1; i < ChuoiBit.length(); i++)
	{
		char bit = ChuoiBit[i] - '0';
		if (mode == BitMode::ComplementTwo && bit != Sign) return ChuoiBit.length() - 1 - i;
		if (mode == BitMode::Standard && bit != '0') return ChuoiBit.length() - 1 - i;
	}
	return 0;
}


std::string& QInt::NhomBit(std::string& ChuoiBit, unsigned int margin)
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

std::string& QInt::XoaBitThua(std::string& ChuoiBit, BitMode mode, unsigned int n)
{
	int i = FirstSignificantBit(ChuoiBit, mode);

	char Sign = ChuoiBit[0];
	char BitToAdd = (BitMode::ComplementTwo == mode) ? Sign : '0';
	// Từ vị trí sau bit dấu, xoá tất cả các bit thừa cho đến bit ý nghĩa đầu tiên
	TrimStart(ChuoiBit, BitToAdd, 1);

	//Thêm một lượng bit sao cho tổng số bit là một bội của n
	while ((++i +1)% n != 0)
		ChuoiBit.insert(ChuoiBit.begin() + 1, BitToAdd);

	return ChuoiBit;
}


