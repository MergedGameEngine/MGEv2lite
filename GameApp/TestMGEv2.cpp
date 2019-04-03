// TestMGEv2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "stdio.h"
#include "string.h"
#include <cstdlib>

using namespace std;

#include <crtdbg.h>

#include "../MGE_Base/Type.h";
#include "../MGE_Base/Base.h";


void TestMGEv2 () {
//	unsigned long _slen;
//	unsigned long long i9 = 400000000022;
//	short i3 = 6789;
//	char *hw = "总时间";
//	_slen = strlen(hw);
//	printf("%d,%s\n", _slen, hw);
//	
//	_string str1("hello world!");
//	
//	_string str2 = "Asshole!";
//	
/////	str2 = _string("hello world!!");
//
//	printf("%d,%d,%s,%s\n", &str1, &str2, str1.GetBuffer(), str2.GetBuffer());
//
//	str2 += str2 + str1 + str2 + "" + str1 + _string(i3);
//
//	_string str3
//	= str2 + _string("%d,%d,%s,%s\n", &str1, &str2, str1.GetBuffer(), str2.GetBuffer()) + ";;;";
//	printf("%d,%d,%s,%s\n", &str1, &str2, str1.GetBuffer(), str2.GetBuffer());
//
//	str3 = str3;
//
//	str2 += str1 + "Asshole" + "" + _string(123.456) + ";" + _string(i9);
//	
//	printf("%d,%d,%s,%s\n", &str1, &str2, str1.GetBuffer(), str2.GetBuffer());
//	printf("===str3=[%s]===\n", str3.GetBuffer());

//	MGEHashtable _ht;
//	_ht.Add(_string("KEY"), &_string("OBJ"));

	//_wstring str1(L"Hello world!");

	//_wstring str2 = L"Asshole!";

	//wprintf(L"%d,%d,%s,%s\n", &str1, &str2, str1.GetBuffer(), str2.GetBuffer());

	//str2 += str2 + str1 + str2 + L"" + str1;

	//_wstring str3
	//= str2 + _wstring("%d,%d,%ls,%ls\n", &str1, &str2, str1.GetBuffer(), str2.GetBuffer()) + L";;;";
	//wprintf(L"%d,%d,%s,%s\n", &str1, &str2, str1.GetBuffer(), str2.GetBuffer());

	//str3 = str3;

	//str2 += str1 + L"Asshole" + L"";
	//
	//wprintf(L"%d,%d,%s,%s\n", &str1, &str2, str1.GetBuffer(), str2.GetBuffer());
	//wprintf(L"===str3=[%s]===\n", str3.GetBuffer());

	short _s0 = 99;
	_var _v2;
	_v2 = "";
	_var _v1 = 0;
	_v1 += _v1 + _s0 + _s0 + "" + _s0 + -40000 + _v1;
	_v1 += "90";
}

int _tmain(int argc, _TCHAR* argv[]) {
	TestMGEv2();
	_CrtDumpMemoryLeaks();
    return 0;
}
