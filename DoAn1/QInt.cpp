#include "QInt.h"

using namespace CongCu;

const unsigned int QInt::nBitCount = 128;

bool QInt::KiemTraChuoi(std::string val, std::string& msg)
{
	if (val == "" || val =="+" || val == "-")
	{
		msg = "Chuoi can it nhat 1 trong cac ki tu thuoc [0-9], [a-f], [A-F]";
		return false;
	}
	int SoDau = 0;
	std::string KiTuHopLe = "+-1234567890ABCDEFabcdef";
	for (size_t i = 0; i < val.length(); i++)
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

bool QInt::KiemTraCoSo(std::string val, Base base, std::string& msg)
{
	unsigned n = (val[0] == '-' || val[0] == '+') ? 1 : 0;
	for (unsigned i = n; i < val.length(); i++)
	{
		if (base == Hexademical && (val[i] >= 'A' && val[i] <= 'F' || val[i] >= 'a' && val[i] <= 'f'))
			continue;
		if (val[i] - '0' >= 0 && val[i] - '0' < (int)base)
			continue;
		msg = "Co so khong hop le";
		return false;
	}
	return true;
}

QInt QInt::OneInit()
{
	QInt op;
	for (size_t i = 0; i < nBitCount; i++)
		op.ChuyenBit(i, true);
	return op;
}

QInt::QInt(const std::string& value, Base base)
{
	std::string msg;
	if (!KiemTraChuoi(value, msg))
	{
		std::cout << "Input: " << value << "\nError: " << msg << std::endl;
		std::cout << "Khoi tao mac dinh bang 0" << std::endl;
		return;
	}
	if (!KiemTraCoSo(value, base, msg))
	{
		std::cout << "Input: " << value << "\nError: " << msg << std::endl;
		std::cout << "Khoi tao mac dinh bang 0" << std::endl;
		return;
	}
	int n = (value[0] == '+') ? 1 : 0;
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

void QInt::DecToQInt(const std::string& base10)
{
	*this = QInt(CongCu::FromDecTo(base10, Binary), Binary);
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
			output = CongCu::PhepCong(output, CongCu::PhepLuyThua(2, nBitCount - 1 - i));
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

	input.insert(input.begin() + 1, '0');
	std::string tmp = "0000";
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


QInt QInt::operator - () const
{
	QInt result = *this;
	result.PhepTru();
	return result;
}

QInt QInt::operator + (const QInt& a) const
{
	QInt result = *this;
	result.PhepCong(a);
	return result;
}

QInt QInt::operator - (const QInt &a) const
{
	QInt result = *this;
	result.PhepTru(a);
	return result;
}

QInt QInt::operator * (const QInt &Q) const
{
	QInt result = *this;
	return result.PhepNhan(Q);
}
QInt QInt::operator / (QInt M) const
{
	QInt result = *this;
	QInt mod = 0;

	result.PhepChia(M, mod);

	return result;
}
QInt QInt::operator % (QInt M) const
{
	QInt result = *this;
	QInt mod = 0;

	result.PhepChia(M, mod);

	return mod;
}


QInt& QInt::PhepCong(const QInt& a)
{
	int iSum = 0, iCarry = 1;
	std::vector<bool> LuotTruoc = { false,false }; // 0, 1
	std::vector<bool> BoNhoTam = { false,false };

	for (int i = 0; i < nBitCount; i++)
	{
		//Cộng 2 bit của mỗi hạng tử trước
		BoNhoTam = CongBit(this->LayBit(i), a[i]); // 1 + 0 = 1, 0

		//Lưu carry của kết quả trên
		bool carry = BoNhoTam[iCarry]; // -> 0

		// Cộng kết quả trên với số nhớ từ kết quả của lượt trước đó (hay carry trong LuotTruoc)
		// suy ra tổng cuối cùng
		BoNhoTam = CongBit(BoNhoTam[iSum], LuotTruoc[iCarry]);// 1 + 1 = 0, 1

		// So sánh carry từ phép cộng ở bước 1 và ở kết quả trên
		// Chọn carry có giá trị lớn hơn
		LuotTruoc = { BoNhoTam[iSum],carry || BoNhoTam[iCarry] };

		this->ChuyenBit(i, LuotTruoc[iSum]);
	}
	return *this;
}
QInt& QInt::PhepTru()
{
	//Đảo bit cộng 1

	*this = this->operator~();

	unsigned i = 0;
	while (i < nBitCount && this->LayBit(i) == true)
		this->TatBit(i++);
	if (i < nBitCount)
		this->BatBit(i);

	return *this;
}

QInt& QInt::PhepTru(const QInt& a)
{
	QInt minusA = -a;
	return this->PhepCong(minusA);
}

QInt& QInt::PhepNhan(QInt Q)
{

	QInt A = 0;
	bool Qminus1 = false;


	int n = nBitCount;
	while (n > 0)
	{
		bool Q0 = Q.LayBit(0);
		if (Q0 == true && Qminus1 == false)		//Q0Q1 = 10
		{
			A.PhepTru(*this);
		}
		else if (Q0 == false && Qminus1 == true)	//01
		{
			A.PhepCong(*this);
		}


		// Shift Right [A,Q,Q-1]
		Qminus1 = Q.LayBit(0);
		Q.ShiftRight(1u);
		Q.ChuyenBit(nBitCount - 1, A.LayBit(0));
		A.ShiftRight(1u);

		n--;
	}

	*this = Q;

	return *this;
}
QInt& QInt::PhepChia(QInt right, QInt& mod)
{
	if (right == 0)
		throw std::overflow_error("Division by zero");
	if (right == 1 || right == -1)
	{
		mod = 0;
		this->PhepNhan(right);
		return *this;
	}
	if (this->FirstSignificantBit() <= sizeof(long long) * 8u && right.FirstSignificantBit() <= sizeof(long long) * 8)
	{
		long long llLeft = *this;
		long long llRight = right;
		*this = llLeft / llRight;
		mod = llLeft % llRight;
		return *this;
	}

	QInt& M = right;
	QInt& Q = *this;
	int count = nBitCount;
	QInt A = 0; // A = 000000....0000000 (128 bit, default value when construct)
	bool DauQ = Q.LayBit(nBitCount - 1);
	int sign = 0;

	if (M.LayBit(nBitCount - 1) + Q.LayBit(nBitCount - 1) == 1)
		sign = 1; // negative
	if (Q.LayBit(nBitCount - 1) == 1) //Q < 0
		Q.PhepTru();

	if (M.LayBit(nBitCount - 1) == 1) // M < 0
		M.PhepTru();

	do
	{
		// shift bit of A
		A.ShiftLeft(1u);

		// shift MSB of Q to LSB of A
		if (Q.LayBit(nBitCount - 1) == 1)
			A.BatBit(0);
		else
			A.TatBit(0);

		// shift bit of Q
		Q.ShiftLeft(1);

		A.PhepTru(M);
		if (A.LayBit(nBitCount - 1) == 1)
		{
			Q.TatBit(0);
			A.PhepCong(M);
		}
		else
			Q.BatBit(0);
		count--;
	} while (count > 0);

	if (sign == 1)
	{
		Q.PhepTru();
	}
	mod = (DauQ) ? -A : A;
	return Q;
}

QInt QInt::TinhToan( QInt&a, QInt& b, std::string c)
{
	if (c == "+") // phép cộng
		return (a + b);
	else if (c == "-") // phép trừ
		return (a - b);
	else if (c == "*") //phép nhân
		return (a * b);
	else if (c == "/") //phép chia
		return (a / b);
	else if (c == "%") //phép mod
		return (a % b);
	else if (c == ">>") //shift phải
		return (a >> unsigned (stoi(b.QIntToDec(c))));
	else if (c == "<<") //shift trái
		return (a << unsigned(stoi(QIntToDec(c))));
	else if (c == "&") //phép AND
		return (a & b);
	else if (c == "|") //phép OR
		return (a | b);
	else if (c == "^") //phép XOR	
		return (a ^ b);
	else if (c == "~") //phep NOT
		return (~a);
	else if (c == "rol") //xoay trai	
		return (a.rol(stoi(b.QIntToDec(c))));
	else if (c == "~") //xoay phải	
		return (a.ror(stoi(b.QIntToDec(c))));
}

bool QInt::SoSanh(QInt&a, QInt& b, std::string c)
{
	if (c == ">") // so sánh lớn hơn
		return (a > b);
	else if (c == "<") // so sánh nhỏ hơn
		return (a < b);
	else if (c == ">=") //so sánh lớn hơn hoặc bằng
		return (a >= b);
	else if (c == "<=") //so sánh nhỏ hơn hoặc bằng
		return (a <= b);
	else if (c == "==") //so sánh bằng
		return (a == b);
	else if (c == "!=") //so sánh khác
		return (a != b);
}

string QInt::XuatBool(const bool& a)
{
	if (a == true)
		return "True";
	else
		return "False";
}
#pragma endregion


bool QInt::LayBit(unsigned i) const
{
	if (i < 0 || i >= nBitCount)
		throw std::out_of_range("LayBit");
	unsigned x = MangBit[MangBit.size() - 1 - i / (sizeof(value_type) * 8)];
	return (x >> (i % (sizeof(value_type) * 8))) & 1;
}
void QInt::BatBit(unsigned i)
{
	if (i < 0 || i >= nBitCount)
		throw std::out_of_range("LayBit");
	MangBit[MangBit.size() - 1 - i / (sizeof(value_type) * 8)] |= (1 << (i % (sizeof(value_type) * 8)));
}
void QInt::TatBit(unsigned i)
{
	if (i < 0 || i >= nBitCount)
		throw std::out_of_range("LayBit");
	MangBit[MangBit.size() - 1 - i / (sizeof(value_type) * 8)] &= ~(1 << (i % (sizeof(value_type) * 8)));
}
void QInt::ChuyenBit(unsigned vitri, bool bit)
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
QInt& QInt::rol(int value)
{
	for (int i = 0;i < value;i++)
	{
		bool a = LayBit(nBitCount - 1);
		this->ShiftLeft(1u);
		this->ChuyenBit(0, a);
	}
	return *this;
}
QInt& QInt::ror(int value)
{
	for (int i = 0;i < value;i++)
	{
		bool a = LayBit(0);
		this->ShiftRight(1u);
		this->ChuyenBit(nBitCount - 1, a);
	}
	return *this;
}
bool QInt::AllZeroBit() const
{
	for (int i = nBitCount - 1; i >= 0; i--)
	{
		if (this->LayBit(i)) return false;
	}
	return true;
}

bool QInt::AllOneBit() const
{
	for (int i = nBitCount - 1; i >= 0; i--)
	{
		if (this->LayBit(i) == false) return false;
	}
	return true;
}


bool QInt::operator==(const QInt& a) const
{
	return (this->operator^(a)).AllZeroBit();

}
bool QInt::operator>(const QInt& a) const
{
	if (this->operator==(a)) return false;

	bool SignBitLeft = this->LayBit(nBitCount - 1);	// false là dương, true là âm
	bool SignBitRight = a.LayBit(nBitCount - 1);

	if (SignBitLeft < SignBitRight) return true;
	if (SignBitLeft > SignBitRight) return false;

	//So sánh từ bit có nghĩa nhất (trái sang phải)
	for (int i = nBitCount - 1; i >= 0; i--)
	{
		bool _this = this->LayBit(i);
		bool _a = a.LayBit(i);

		if (this->LayBit(i) > a.LayBit(i)) return true;
		if (this->LayBit(i) < a.LayBit(i)) return false;

	}
	return false;
}
bool QInt::operator<(const QInt& a) const
{
	return !(this->operator==(a) || this->operator>(a));
}
bool QInt::operator>=(const QInt& a) const
{
	return !(this->operator<(a));
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
	return this->AllZeroBit();
}
#pragma endregion

QInt QInt::operator&(const QInt& a) const
{
	QInt output;
	for (size_t i = 0; i < MangBit.size(); i++)
		output.MangBit[i] = this->MangBit[i] & a.MangBit[i];
	return output;
}
QInt QInt::operator|(const QInt& a) const
{
	QInt output;
	for (size_t i = 0; i < MangBit.size(); i++)
		output.MangBit[i] = this->MangBit[i] | a.MangBit[i];
	return output;
}
QInt QInt::operator^(const QInt& a) const
{
	QInt output;
	for (size_t i = 0; i < MangBit.size(); i++)
		output.MangBit[i] = this->MangBit[i] ^ (a.MangBit[i]);
	return output;
}
QInt QInt::operator~() const
{
	QInt output;
	for (size_t i = 0; i < MangBit.size(); i++)
		output.MangBit[i] = ~(this->MangBit[i]);
	return output;
}

QInt QInt::operator<<(unsigned offset) const
{
	QInt output = *this;
	output.ShiftLeft(offset);
	return output;
}
QInt QInt::operator>>(unsigned offset) const
{
	QInt output = *this;
	output.ShiftRight(offset);
	return output;
}

unsigned QInt::FirstSignificantBit() const
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

void QInt::ShiftLeft(unsigned offset)
{
	if (offset == 0) return;
	int i = nBitCount - 1;

	for (i; i >= offset; i--)
		this->ChuyenBit(i, LayBit(i - offset));

	while (i >= 0)
		this->ChuyenBit(i--, false);

}
void QInt::ShiftRight(unsigned offset)
{
	if (offset == 0) return;
	bool n = LayBit(nBitCount - 1) ? true : false;

	int i;
	for (i = 0; i < nBitCount - offset; i++)
		this->ChuyenBit(i, LayBit(i + offset));

	while (i < nBitCount)
		this->ChuyenBit(i++, n);

}

#pragma region------------------------------- ĐỌC GHI FILE -------------------------------
void DocFile(const std::string&input, string output, int type)
{
	ifstream doc;
	ofstream ghi;
	string toantu = "+-*/%>><<";
	doc.open(input, std::ios::in);
	if (doc.fail())
	{
		cout << "Mo file khong thanh cong!!!\n\n";
		return;
	}
	ghi.open(output);
	ghi.clear();
	ghi.close();
	std::vector<string>data(4);
	std::string luu;
	while (doc.good())
	{
		int i = 0;
		getline(doc, luu, '\n');
		cout << luu << " = ";
		while (!luu.empty())
		{
			data[i] = luu.substr(0, luu.find(' '));
			luu.erase(0, data[i].size() + 1);
			i++;
		}
		if (type == 1)
			GhiFileQInt(output,data);
		else if(type==2)
			GhiFileQFloat(output,data);
		else
		{
			cout << "Ban phap kieu doc file khong dung!!!";
			return;
		}
		data[3] = "";
	}
	doc.close();
	cout << "Ket qua da duoc luu vao file output.txt!!!\n";
}
void GhiFileQInt(std::string output,std::vector<std::string> data)
{
	ofstream ghi;
	QInt a;
	std::string temp;
	ghi.open(output, std::ios::app);
	if (data[3].empty())
	{
		a = QInt(data[2], Base(stoi(data[0])));
		if (data[1] == "10") // đổi từ nhị phân sang thập phân
		{
			ghi << a.DecString() << '\n';
			cout << a.DecString() << endl;
		}
		else if (data[1] == "2") //đổi từ thập phân sang nhị phân
		{
			ghi << a.BinString(Standard, true) << '\n';
			cout << a.BinString(Standard, false) << '\n';
		}
		else if (data[1] == "16")// đổi từ nhị phân sang thập lục phân
		{
			ghi << a.HexString() << '\n';
			cout << a.HexString() << '\n';
		}
	}
	else
	{
		std::string value = "><>=<=!===";
		if (value.find(data[2]) == value.length())
		{
			if (data[0] == "2")// tính toán với cơ số 2
			{
				QInt value1, value3;
				value1.BinToQInt(data[1]);
				value3.BinToQInt(data[3]);
				ghi << a.TinhToan(value1, value3, data[2]).BinString(Standard, false) << '\n';
				cout << a.TinhToan(value1, value3, data[2]).BinString(Standard, true) << '\n';
			}
			if (data[0] == "10")// tính toán với cơ số 10
			{
				QInt value1, value3;
				value1.DecToQInt(data[1]);
				value3.DecToQInt(data[3]);
				ghi << a.TinhToan(value1, value3, data[2]).QIntToDec(temp) << '\n';
				cout << a.TinhToan(value1, value3, data[2]).QIntToDec(temp) << '\n';
			}
			if (data[0] == "16")// tính toán với cơ số 16
			{
				QInt value1, value3;
				value1.HexToQInt(data[1]);
				value3.HexToQInt(data[3]);
				ghi << a.TinhToan(value1, value3, data[2]).QIntToHex(Standard, temp) << '\n';
				cout << a.TinhToan(value1, value3, data[2]).QIntToHex(Standard, temp) << '\n';
			}
		}
		else
		{
			if (data[0] == "2")// tính toán với cơ số 2
			{
				QInt value1, value3;
				value1.BinToQInt(data[1]);
				value3.BinToQInt(data[3]);
				ghi << a.XuatBool(a.SoSanh(value1, value3, data[2])) << '\n';
				cout << a.XuatBool(a.SoSanh(value1, value3, data[2])) << '\n';
			}
			if (data[0] == "10")// tính toán với cơ số 10
			{
				QInt value1, value3;
				value1.DecToQInt(data[1]);
				value3.DecToQInt(data[3]);
				ghi << a.XuatBool(a.SoSanh(value1, value3, data[2])) << '\n';
				cout << a.XuatBool(a.SoSanh(value1, value3, data[2])) << '\n';
			}
			if (data[0] == "16")// tính toán với cơ số 16
			{
				QInt value1, value3;
				value1.HexToQInt(data[1]);
				value3.HexToQInt(data[3]);
				ghi << a.XuatBool(a.SoSanh(value1, value3, data[2])) << '\n';
				cout << a.XuatBool(a.SoSanh(value1, value3, data[2])) << '\n';
			}
		}
	}
	ghi.close();
}
void GhiFileQFloat(const std::string& output,std::vector<std::string> data)
{
	//ofstream ghi;
	//QFloat a;
	//std::string temp;
	//ghi.open(output, std::ios::app);
	//if (data[3].empty())
	//{
	//	a = QInt(data[2], Base(stoi(data[0])));
	//	if (data[1] == "10") // đổi từ nhị phân sang thập phân
	//	{
	//		ghi << a.DecString() << '\n';
	//		cout << a.DecString() << endl;
	//	}
	//	else if (data[1] == "2") //đổi từ thập phân sang nhị phân
	//	{
	//		ghi << a.BinString(Standard, true) << '\n';
	//		cout << a.BinString(Standard, false) << '\n';
	//	}
	//	else if (data[1] == "16")// đổi từ nhị phân sang thập lục phân
	//	{
	//		ghi << a.HexString() << '\n';
	//		cout << a.HexString() << '\n';
	//	}
	//}
	//ghi.close();
}
#pragma endregion