#ifndef CL_QINT_H
#define CL_QINT_H

#include <vector>
#include <string>
#include <type_traits>
#include <iostream>
#include<fstream>
#include "CongCu.h"
#include"QFloat.h"
using namespace std;

class QInt
{
public:
	typedef unsigned char value_type;
	typedef std::vector<value_type> container;

	virtual ~QInt() {}
	QInt() {}

	static bool KiemTraChuoi(std::string val, std::string& msg);
	static bool KiemTraCoSo(std::string val, Base base, std::string& msg);

	//Find the position of first significant bit, starting from right to left
	unsigned FirstSignificantBit() const;

#pragma region ------------------CONSTRUCTORS VÀ CASTING------------------

	//Initialize value with every bit is 0
	static QInt ZeroInit() { return QInt(); }
	bool AllZeroBit() const;

	//Initialize value with every bit is 1
	static QInt OneInit();
	bool AllOneBit() const;

	QInt(const std::string& value, Base base);

	template <typename INT>
	QInt(const INT& val) { this->ConvertFrom(val); }

	template<typename INT>
	QInt& operator=(const INT& val) { return ConvertFrom(val); }

	template<typename INT>
	operator INT() const { return ConvertTo<INT>(); }

	// trả false nếu mảng chỉ chứa bit 0, còn lại là true
	operator bool() const { return !AllZeroBit(); }

#pragma endregion

#pragma region ------------------ PHÉP TOÁN TRÊN SỐ ------------------

	QInt operator + (const QInt &a) const;
	QInt operator - () const;
	QInt operator - (const QInt &a) const;
	QInt operator * (const QInt &Q) const;
	QInt operator / (QInt M) const;
	QInt operator % (QInt M) const;

	QInt& operator += (const QInt& a) { return PhepCong(a); }
	QInt& operator -= (const QInt& a) { return PhepTru(a); }
	QInt& operator *= (const QInt& a) { return PhepNhan(a); }
	QInt& operator /= (const QInt& a) { QInt mod; return PhepChia(a, mod); }
	QInt& operator %= (const QInt& a) { QInt mod; PhepChia(a, mod); return mod; }

	QInt& operator++() { return this->operator+=(1); }								//++a
	QInt operator++(int) { QInt out = *this;	this->PhepCong(1); return out; }	//a++
	QInt& operator--() { return this->operator-=(1); }								//--a
	QInt operator--(int) { QInt out = *this;	this->PhepTru(1); return out; }		//a--

	QInt TinhToan (QInt&a, QInt& b, std::string c);
	bool SoSanh(QInt&a, QInt& b, std::string c);
	string XuatBool(const bool& a);
#pragma endregion

#pragma region ----------------------SO SÁNH----------------------


	template <typename INT>
	bool operator==(const INT& val) const { return this->operator==((QInt)val); }

	template <typename INT>
	bool operator>(const INT& val) const { return this->operator>((QInt)val); }

	template <typename INT>
	bool operator<(const INT& val) const { return this->operator<((QInt)val); }

	template <typename INT>
	bool operator<=(const INT& val) const { return this->operator<=((QInt)val); }

	template <typename INT>
	bool operator>=(const INT& val) const { return this->operator>=((QInt)val); }

	template <typename INT>
	bool operator!=(const INT& val) const { return this->operator!=((QInt)val); }

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
	QInt operator << (unsigned offset) const;
	QInt operator >> (unsigned offset) const;

#pragma endregion

#pragma region ----------------------THAO TAC TREN BIT----------------------

	bool LayBit(unsigned vitri) const;
	void BatBit(unsigned vitri);
	void TatBit(unsigned vitri);
	void ChuyenBit(unsigned vitri, bool bit);
	bool operator[](unsigned vitri) const { return LayBit(vitri); }
	QInt& rol(int value);
	QInt& ror(int value);

#pragma endregion

#pragma region ----------------------NHAP XUAT----------------------

	std::string HexString(BitMode mode = BitMode::Standard, bool fullsize = false) const;
	std::string BinString(BitMode mode = BitMode::Standard, bool fullsize = false) const;
	std::string DecString() const;

#pragma endregion

#pragma region------------------------------- ĐỌC GHI FILE -------------------------------

	friend void DocFile( const std::string& input, string output,int type );
	friend void GhiFileQInt( std::string output,std::vector<std::string> data);
	friend void GhiFileQFloat(const std::string& output,std::vector<std::string> data);

#pragma endregion

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
private:
	container MangBit = container(nBitCount / (sizeof(value_type) * 8), 0); //Dữ liệu được lưu ở dạng bù 2
	static const unsigned int nBitCount;

#pragma region ------------------CÔNG CỤ CHUYỂN ĐỔI KIỂU DỮ LIỆU------------------
	void BinToQInt(const std::string& base2);
	void HexToQInt(const std::string& base16);
	void DecToQInt(const std::string& base10);

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

		this->ZeroInit();
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

		return *this;
	}
#pragma endregion

	QInt LayBu1() const;
	QInt LayBu2() const;

	/**
	 * Kiểm tra nếu chuỗi chỉ chứa các kí tự hợp lệ: +, - , [0 : 9]. Yêu cầu: [+-][1234567890], không có khoảng trắng ở giữa
	 * @param val Chuỗi được kiểm tra
	 * @param msg nội dung lỗi nếu chuỗi đưa vào không hợp lệ, "" nếu hợp lệ
	*/


	void ShiftLeft(unsigned offset);
	void ShiftRight(unsigned offset);

	QInt& PhepChia(QInt, QInt& sodu);
	QInt& PhepCong(const QInt&);
	QInt& PhepTru(const QInt&);
	QInt& PhepTru();
	QInt& PhepNhan(QInt);
};

#endif