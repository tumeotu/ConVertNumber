#ifndef XULY_H_
#define XULY_H_

#include "QFloat.h"
#include "QInt.h"
#include <iostream>
#include <string>
#include <vector>

int Menu(const std::vector<std::string>& cmd);
int XuLyQInt(int option);
int XuLyQFloat(int option);
int XuLiDocGhi();
int XuLy(int option);
QInt NhapQInt(Base);
QFloat NhapQFloat(Base);

#endif