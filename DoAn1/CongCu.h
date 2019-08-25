#ifndef NS_CONGCU_H
#define NS_CONGCU_H

#include <string>
#include <vector>

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


namespace CongCu
{
	std::vector<bool> CongBit(bool a, bool b);
	std::string FromDecTo(std::string base10, Base base);
	std::string HexToBin(const std::string& hex);
	std::string PhepNhan(const std::string& base10, int);
	std::string PhepCong(std::string left, std::string right);
	std::string PhepLuyThua(const int& value, const  int& mu);
	std::string PhepChia(const std::string& base10, int& phandu, int value);

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

		return output;

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

	//Chỉnh sửa dãy bit thành các bộ n bit ngăn cách nhau bằng khoảng trắng
	std::string& NhomBit(std::string&, unsigned int n = 8u);

	//Find the position of first significant bit, starting from right to left
	int FirstSignificantBit(const std::string&, BitMode = BitMode::ComplementTwo);

	//Xoá các bộ n bit thừa sao cho giá trị của dãy biết vẫn không đổi
	std::string& XoaBitThua(std::string&, BitMode = BitMode::ComplementTwo, unsigned int n = 8u);
};

#endif