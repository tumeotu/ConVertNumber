#ifndef CL_QINTV2_H
#define CL_QINTV2_h

#include <vector>
#include <string>
#include <type_traits>
#include <iostream>

//------------------ NON-MEMBER FUNCITONS ------------------
enum BitMode
{
	Standard = 0,
	ComplementTwo = 2
};
enum Base
{
	Binary = 2,
	Demical = 10,
	Hexademical = 16
};
std::vector<bool> CongBit(bool a, bool b);
std::string FromDecTo(std::string base10, Base base);
std::string HexToBin(const std::string& hex);
std::string PhepNhan(const std::string& base10, int);
std::string PhepCong(std::string left, std::string right);
std::string PhepLuyThua(const int& value, const  int& mu);

//Get the bits serie which is stored in the computer, result maybe variety from different OS
template<typename INT>
std::string ToBit(const INT& val, bool IsSpace = true)
{
	static_assert(!std::is_pointer<INT>(), "Pointer is not allowed");
	static_assert(!std::is_array<INT>(), "Any type of array is not allowed but string"
										", if you are using c-string consider using std::string or std::wstring instead");

	std::string output;
	for (int i = 0; i < sizeof(INT) * 8; i++)
		output.insert(output.begin(), ((val >> i) & 1) ? '1' : '0');

	return IsSpace ? QInt::NhomBit(output, sizeof(unsigned char) * 8) : output;

}

//Get the bits serie which is stored in the computer, result maybe variety from different OS
template<>
std::string ToBit<std::string>(const std::string& val, bool isSpace);

//Get the bits serie which is stored in the computer, result maybe variety from different OS
template<>
std::string ToBit<double>(const double& val, bool isSpace);

//Get the bits serie which is stored in the computer, result maybe variety from different OS
template<>
std::string ToBit<float>(const float& val, bool isSpace);

//@param offset start triming after offset characters from th1e left
std::string& TrimStart(std::string&, char c = ' ', size_t offset = 0);

//@param offset start triming after offset characters from the right
std::string& TrimEnd(std::string&, char c = ' ', size_t offset = 0);

//@param offset start triming after offset characters from the right and from the left
std::string& Trim(std::string&, char c = ' ', size_t offset = 0);

class QInt
{
	friend std::string ToBit<std::string>(const std::string& val, bool IsSpace);
	template<typename INT> friend std::string ToBit<INT>(const INT& val, bool IsSpace);
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
	typedef unsigned char value_type;
	typedef std::vector<value_type> container;

	virtual ~QInt() {}
	QInt() {}

	//Initialize value with every bit is 0
	static QInt ZeroInit() { return QInt(); }

	//Initialize value with every bit is 1
	static QInt OneInit() { QInt op = -1; op.ChuyenBit(0, true); return op; }

	//Find the position of first significant bit, starting from right to left
	int FirstSignificantBit() const;

#pragma region ------------------CONSTRUCTORS VÀ CHUYỂN ĐỔI KIỂU DỮ LIỆU------------------
	QInt(const std::string& value, Base base);
	template <typename INT>
	QInt(const INT& val)
	{
		this->ConvertFrom(val);
	}

	template<typename INT>
	QInt& operator=(const INT& val)
	{
		return ConvertFrom(val);
	}

	template<typename INT>
	operator INT() const
	{
		return ConvertTo();
	}

	// trả false nếu mảng chỉ chứa bit 0, còn lại là true
	operator bool() const
	{
		return !IsZero();
	}
	QInt operator=(const bool& val)
	{
		return !IsZero();
	}
#pragma endregion

#pragma region ------------------ PHÉP TOÁN TRÊN SỐ ------------------
	QInt operator + (const QInt& a) const;
	QInt operator - () const;
	QInt operator - (const QInt &a) const;
	QInt operator * (QInt Q) const;
	QInt operator / (const QInt &M) const;
	QInt operator % (const QInt &M) const;
	QInt operator << (int offset) const;
	QInt operator >> (int offset) const;


#pragma endregion

#pragma region ----------------------SO SANH----------------------
	bool IsZero() const;

	template <typename INT>
	bool operator==(const INT& val) const
	{
		return this->operator==((QInt)val);
	}

	template <typename INT>
	bool operator>(const INT& val) const
	{
		return this->operator>((QInt)val);
	}

	template <typename INT>
	bool operator<(const INT& val) const
	{
		return this->operator<((QInt)val);
	}

	template <typename INT>
	bool operator<=(const INT& val) const
	{
		return this->operator<=((QInt)val);
	}

	template <typename INT>
	bool operator>=(const INT& val) const
	{
		return this->operator>=((QInt)val);
	}

	template <typename INT>
	bool operator!=(const INT& val) const
	{
		return this->operator!=((QInt)val);
	}

bool operator==(const QInt& a) const;
bool operator>(const QInt& a) const;
bool operator<(const QInt& a) const;
bool operator>=(const QInt& a) const;
bool operator<=(const QInt& a) const;
bool operator!=(const QInt& a) const;
bool operator!() const;
#pragma endregion

#pragma region ----------------------PHEP TOAN TREN BIT----------------------
	QInt operator&(const QInt& a) const;
	QInt operator|(const QInt& a) const;
	QInt operator^(const QInt& a) const;
	QInt operator~() const;
#pragma endregion

#pragma region ----------------------THAO TAC TREN BIT----------------------
	bool LayBit(int vitri) const;
	void BatBit(int vitri);
	void TatBit(int vitri);
	void ChuyenBit(int vitri, bool bit);
	bool operator[](int vitri) const { return LayBit(vitri); }
	QInt XoayBit()const;

#pragma endregion

#pragma region ----------------------NHAP XUAT----------------------
	std::string HexString(BitMode mode = BitMode::Standard, bool fullsize = false) const;
	std::string BinString(BitMode mode = BitMode::Standard, bool fullsize = false) const;
	std::string DecString() const;
#pragma endregion

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
private:
	container MangBit = container(nBitCount / (sizeof(value_type) * 8), 0); //Dữ liệu được lưu ở dạng bù 2
	static const int nBitCount;

#pragma region ------------------CÔNG CỤ CHUYỂN ĐỔI KIỂU DỮ LIỆU------------------
	void BinToQInt(const std::string& base2);
	void HexToQInt(const std::string& base16);
	void DecToQInt(const std::string& base10) { *this = QInt(FromDecTo(base10, Binary), Binary); }

	std::string& QIntToBin(BitMode mode, std::string&) const;
	std::string& QIntToDec(std::string&) const;
	std::string& QIntToHex(BitMode mode, std::string&) const;

	template<typename INT>
	INT ConvertTo() const
	{
		static_assert(std::is_integral<INT>(), "Only allow instantiation of integral type");
		static_assert(!std::is_pointer<INT>(), "Pointer is not allowed");
		static_assert(!std::is_array<INT>(), "Any type of array is not allowed");
		// Lưu ý: do ta lưu vào mảng dãy bit ở dạng bù 2 trùng hợp với cách lưu số nguyên mà máy tính sử dụng
		// nên mới có thể thực hiện được cách dưới đây

		// Gán các bit từ mảng vào kiểu dữ liệu cần chuyển, số lượng bit gán phụ thuộc vào kích thước của kiểu dữ liệu
		INT output = 0;
		for (int i = 0; i < sizeof(INT) * 8; i++)
		{
			if (LayBit(i))
				output |= ((INT)1 << i);
			else
				output &= ~((INT)1 << i);
		}
		return output;
	}

	template<typename INT>
	QInt& ConvertFrom(const INT& val)
	{
		static_assert(std::is_integral<INT>(), "Only allow instantiation of integral type");
		static_assert(!std::is_pointer<INT>(), "Pointer is not allowed");
		static_assert(!std::is_array<INT>(), "Any type of array is not allowed");

		// Lưu ý: trong máy tính, số nguyên được lưu ở dạng bù 2 
		// Gán các bit từ val vào mảng bit

		*this = QInt();
		int i = 0;
		for (i; i < sizeof(INT) * 8 - 1; i++)
		{
			ChuyenBit(i, (val >> i) & 1);
		}
		ChuyenBit(nBitCount - 1, (val >> i) & 1);

		if (LayBit(nBitCount - 1))
		{
			while (i < nBitCount - 1)
				BatBit(i++);
		}

		//std::cout << this->ComplementTwoBitString() << std::endl;

		return *this;
	}
#pragma endregion

#pragma region ----------------------THAO TAC TREN BIT----------------------
	QInt LayBu1() const;
	QInt LayBu2() const;
#pragma endregion

	/**
	 * Kiểm tra nếu chuỗi chỉ chứa các kí tự hợp lệ: +, - , [0 : 9]. Yêu cầu: [+-][1234567890], không có khoảng trắng ở giữa
	 * @param val Chuỗi được kiểm tra
	 * @param msg nội dung lỗi nếu chuỗi đưa vào không hợp lệ, "" nếu hợp lệ
	*/
	static bool KiemTraChuoi(std::string val, std::string& msg);

	//Chỉnh sửa dãy bit thành các bộ n bit ngăn cách nhau bằng khoảng trắng
	static std::string& NhomBit(std::string&, unsigned int n = sizeof(value_type) * 8);

	//Xoá các bộ n bit thừa sao cho giá trị của dãy biết vẫn không đổi
	static std::string& XoaBitThua(std::string&, BitMode = BitMode::ComplementTwo, unsigned int n = sizeof(value_type) * 8);

	//Find the position of first significant bit, starting from right to left
	static int FirstSignificantBit(const std::string&, BitMode = BitMode::ComplementTwo);
};

#endif