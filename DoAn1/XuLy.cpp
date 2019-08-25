#include "XuLy.h"

QInt NhapQInt(Base base)
{
	std::string input, error;
	QInt Value;

	std::getline(std::cin, input);

	Value = QInt(input, base);
	return Value;
}

QFloat NhapQFloat(Base base)
{
	std::string input, error;
	QFloat Value;
	std::cout << "Nhap gia tri: ";

	std::getline(std::cin, input);

	Value = QFloat(input, base);
	return Value;
}

int Menu(const std::vector<std::string>& cmds)
{
	std::string input;
	while (true)
	{
		system("cls");
		for (unsigned i = 0; i < cmds.size(); i++)
			std::cout << i + 1u << ". " << cmds[i] << std::endl;
		std::cout << "Chon Lenh: ";
		std::getline(std::cin, input);
		try
		{
			int option = std::stoi(input);
			if (1 <= option && option <= cmds.size())
				return option;
		}
		catch (const std::invalid_argument& e)
		{
			continue;
		}
	}

}

int XuLyQInt(int option)
{
	//  "10 -> 16", "10 -> 2", "2 -> 10", "2 -> 16", "16 -> 10", "16 -> 2",
	QInt QIntOut;
	switch (option)
	{
	case 1:
	{
		std::cout << "Nhap gia tri: ";
		QIntOut = NhapQInt(Base::Demical);
		std::cout << "He 16: " << QIntOut.HexString() << std::endl;
		break;
	}
	case 2:
	{
		std::cout << "Nhap gia tri: ";
		QIntOut = NhapQInt(Base::Demical);
		std::cout << "He 2: " << QIntOut.BinString() << std::endl;
		break;
	}
	case 3:
	{
		std::cout << "Nhap gia tri: ";
		QIntOut = NhapQInt(Base::Binary);
		std::cout << "He 10: " << QIntOut.DecString() << std::endl;
		break;
	}
	case 4:
	{
		std::cout << "Nhap gia tri: ";
		QIntOut = NhapQInt(Base::Binary);
		std::cout << "He 16: " << QIntOut.HexString() << std::endl;
		break;
	}
	case 5:
	{
		std::cout << "Nhap gia tri: ";
		QIntOut = NhapQInt(Base::Hexademical);
		std::cout << "He 10: " << QIntOut.DecString() << std::endl;
		break;
	}
	case 6:
	{
		std::cout << "Nhap gia tri: ";
		QIntOut = NhapQInt(Base::Hexademical);
		std::cout << "He 2: " << QIntOut.BinString() << std::endl;
		break;
	}
	//	"Phep +", "Phep -", "Phep *", "Phep /",
	case 7:
	{
		std::cout << "a(10) = ";
		QInt a = NhapQInt(Demical);
		std::cout << "b(10) = ";
		QInt b = NhapQInt(Demical);
		std::cout << "a + b = " << (a + b).DecString() << std::endl;
		break;
	}
	case 8:
	{
		std::cout << "a(10) = ";
		QInt a = NhapQInt(Demical);
		std::cout << "b(10) = ";
		QInt b = NhapQInt(Demical);
		std::cout << "a - b = " << (a - b).DecString() << std::endl;
		break;
	}
	case 9:
	{
		std::cout << "a(10) = ";
		QInt a = NhapQInt(Demical);
		std::cout << "b(10) = ";
		QInt b = NhapQInt(Demical);
		std::cout << "a * b = " << (a * b).DecString() << std::endl;
		break;
	}
	case 10:
	{
		std::cout << "a(10) = ";
		QInt a = NhapQInt(Demical);
		std::cout << "b(10) = ";
		QInt b = NhapQInt(Demical);
		if (b == 0)
		{
			std::cout << "Error: Division by Zero\n";
			break;
		}
		std::cout << "a / b = " << (a / b).DecString() << std::endl;
		break;
	}
	case 11:
	{
		std::cout << "a(10) = ";
		QInt a = NhapQInt(Demical);
		std::cout << "b(10) = ";
		QInt b = NhapQInt(Demical);
		if (b == 0)
		{
			std::cout << "Error: Division by Zero\n";
			break;
		}
		std::cout << "a % b = " << (a % b).DecString() << std::endl;
		break;
	}
	//	"Phep AND", "Phep OR", "Phep XOR", "Phep NOT"
	case 12:
	{
		std::cout << "a(10) = ";
		QInt a = NhapQInt(Demical);
		std::cout << "b(10) = ";
		QInt b = NhapQInt(Demical);
		std::cout << "a(2) bu 2  = " << a.BinString() << std::endl;
		std::cout << "b(2) bu 2  = " << b.BinString() << std::endl;
		std::cout << "a & b bu 2 = " << (a & b).BinString() << std::endl;
		break;
	}
	case 13:
	{
		std::cout << "a(10) = ";
		QInt a = NhapQInt(Demical);
		std::cout << "b(10) = ";
		QInt b = NhapQInt(Demical);
		std::cout << "a(2) bu 2  = " << a.BinString() << std::endl;
		std::cout << "b(2) bu 2  = " << b.BinString() << std::endl;
		std::cout << "a | b bu 2 = " << (a | b).BinString() << std::endl;
		break;
	}
	case 14:
	{
		std::cout << "a(10) = ";
		QInt a = NhapQInt(Demical);
		std::cout << "b(10) = ";
		QInt b = NhapQInt(Demical);
		std::cout << "a(2) bu 2  = " << a.BinString() << std::endl;
		std::cout << "b(2) bu 2  = " << b.BinString() << std::endl;
		std::cout << "a ^ b bu 2 = " << (a ^ b).BinString() << std::endl;
		break;
	}
	case 15:
	{
		std::cout << "a(10) = ";
		QInt a = NhapQInt(Demical);
		std::cout << " a(2) bu 2 = " << a.BinString(ComplementTwo) << std::endl;
		std::cout << "~a(2) bu 2 = " << (~a).BinString(ComplementTwo) << std::endl;
		break;
	}
	//"Xoay Trai", "Xoay Phai"
	case 16:
	{
		std::cout << "a(10) = ";
		QInt a = NhapQInt(Demical);
		std::cout << "          a(2) bu 2 = " << a.BinString(ComplementTwo) << std::endl;
		std::cout << "xoay trai a(2) bu 2 = " << a.rol(1).BinString(ComplementTwo) << std::endl;
		break;
	}
	case 17:
	{
		std::cout << "a(10) = ";
		QInt a = NhapQInt(Demical);
		std::cout << "          a(2) bu 2 = " << a.BinString(ComplementTwo) << std::endl;
		std::cout << "xoay phai a(2) bu 2 = " << a.rol(1).BinString(ComplementTwo) << std::endl;
		break;
	}
	default:
		return -1;
	}
	std::string sen;
	std::cout << "Bam enter de tiep tuc...";
	std::getline(std::cin, sen);
	return 0;
}
int XuLyQFloat(int option)
{
	switch (option)
	{
	case 1:
	{
		QFloat a = NhapQFloat(Demical);
		std::cout << a.BitToBin() << std::endl;
		break;
	}
	case 2:
	{
		QFloat a = NhapQFloat(Binary);
		std::cout << a.BitToDec() << std::endl;
		break;
	}
	default:
		return -1;
	}
	std::string sen;
	std::cout << "Bam enter de tiep tuc...";
	std::getline(std::cin, sen);
	return 0;
}
int XuLiDocGhi(int option)
{
	switch (option)
	{
	case 1:
	{
		std::string input, value;
		cout << "Nhap ten file can doc voi dinh dang 'abc.txt'!!!\n";
		getline(cin, input);
		while (input.find(".txt") != (input.length() - 4))
		{
			cout << "Bam nhap sia ten fiel moi nhap lai!!!\n";
			cout << "Nhap ten file can doc voi dinh dang 'abc.txt'!!!\n";
			getline(cin, input);
		}
		DocFile(input,"ouput.txt",option);
		break;
	}
	case 2:
	{
		std::string input, value;
		cout << "Nhap ten file can doc voi dinh dang 'abc.txt'!!!\n";
		getline(cin, input);
		while (input.find(".txt") != (input.length() - 4))
		{
			cout << "Bam nhap sia ten fiel moi nhap lai!!!\n";
			cout << "Nhap ten file can doc voi dinh dang 'abc.txt'!!!\n";
			getline(cin, input);
		}
		DocFile(input, "ouput.txt",option);
		break;
	}
	default:
		return -1;
	}
	std::string sen;
	std::cout << "Bam enter de tiep tuc...";
	std::getline(std::cin, sen);
	return 0;
}
int XuLy(int option)
{
	static std::vector<std::string> QIntCmds =
	{
		"10 -> 16","10 -> 2","2 -> 10","2 -> 16","16 -> 10", "16 -> 2",
		"Phep +", "Phep -","Phep *","Phep /","Phep %",
		"Phep AND", "Phep OR","Phep XOR","Phep NOT",
		"Xoay Trai","Xoay Phai",
		"Quay lai"
	};
	static std::vector<std::string> QFloatCmds =
	{
		"10 -> 2","2 -> 10",
		"Quay lai"
	};
	static std::vector<std::string> DocGhiCmds =
	{
		"Doc QInt","Doc QFloat",
		"Quay lai"
	};
	switch (option)
	{
	case 1:
	{
		while(XuLyQInt(Menu(QIntCmds)) != -1);
		break;
	}
	case 2:
	{
		while (XuLyQFloat(Menu(QFloatCmds)) != -1);
		break;
	}
	case 3:
		while (XuLiDocGhi(Menu(DocGhiCmds)) != -1);
		break;
	default:
		exit(1);
	}
}