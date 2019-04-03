// TestMGEv2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"

#include "stdio.h"
#include "string.h"
#include <cstdlib>

using namespace std;

#include <crtdbg.h>

#undef GetClassName

#include "../MGE_Base/Type.h"
#include "../MGE_Base/Base.h"

#include "../MGE_File/File.h"

#include <typeinfo>
  

wchar_t* QXUtf82Unicode(const char* utf, size_t *unicode_number)  
{  
    if(!utf || !strlen(utf))  
    {  
        *unicode_number = 0;  
        return NULL;  
    }  
    int dwUnicodeLen = MultiByteToWideChar(CP_UTF8,0,utf,-1,NULL,0);  
    size_t num = dwUnicodeLen*sizeof(wchar_t);  
    wchar_t *pwText = (wchar_t*)malloc(num);  
    memset(pwText,0,num);  
    MultiByteToWideChar(CP_UTF8,0,utf,-1,pwText,dwUnicodeLen);  
    *unicode_number = dwUnicodeLen - 1;  
    return pwText;  
}  
  
char* QXUnicode2Utf8(const wchar_t* unicode)  
{  
    int len;  
    len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);  
    char *szUtf8 = (char*)malloc(len + 1);  
    memset(szUtf8, 0, len + 1);  
    WideCharToMultiByte(CP_UTF8, 0, unicode, -1, szUtf8, len, NULL,NULL);  
    return szUtf8;  
} 

char* Local_2_UTF8(char *localStr)
{
	int n = MultiByteToWideChar(CP_ACP, 0, localStr, -1, NULL, 0);
	WCHAR *str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, localStr, -1,str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char *str2 = new char[n + 1];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	delete[]str1;
	str1 = NULL;
	//delete[]str2;
	//str2 = NULL;
	return str2;
}


_var Con0(_var &_var0, _var &_var1, _var &_var2) {
	_var ret;
	ret.CreateGenericObject();
	ret["attrib0"] = _var0;
	ret["attrib1"] = _var1;
	ret["attrib2"] = _var2;

//	ret.SetReturn();
//	return ret.SetReturn();

	VARRETURN(ret);
}


void TestMGEv2 () {
//	printf("%d,%s\n", _slen, hw);
//	
//	_string str1("hello world!");
//	
//	_string str2 = "Asshole!";
//	
/////	str2 = _string("hello world!!");
//
//	printf("%d,%d,%s,%s\n", &str1, &str2, str1.GetBuffer(), str2.GetBuffer());
//	str2 += str2 + str1 + str2 + "" + str1 + _string(i3);
//	_string str3
//	= str2 + _string("%d,%d,%s,%s\n", &str1, &str2, str1.GetBuffer(), str2.GetBuffer()) + ";;;";
//	printf("%d,%d,%s,%s\n", &str1, &str2, str1.GetBuffer(), str2.GetBuffer());
//	str3 = str3;
//	str2 += str1 + "Asshole" + "" + _string(123.456) + ";" + _string(i9);
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

	_string _str1;
	_v1.Copy2String(_str1);
	printf("\n var _v1=%s\n", _str1.GetBuffer());

	//_var _a0;
	//_a0.CreateArray();
	//_a0 += "Hello world";
	//_a0 = _a0 + "Hello world!" + "Asshole";
	//_a0 += 6.789;
	//_a0.DeleteAll();

	//_var _i1 = 9, _i2 = 10;
	//_var _i3 = _i1 / _i2;
	_var _oa0;
	_oa0.CreateArray();
	_oa0 = _oa0 + "AB" + "BC" + "CD";

	_var _ht0;
//	_ht0.CreateArray();
//	_ht0 += 7.89;
//	_ht0[3] = "Jesus Christ!";
////	_ht0.DeleteAll();
//	_ht0["KEY0"] = "Hello World";
//	_ht0["KEY1"] = 6.789;
//	_ht0["KEY2"] = _ht0["KEY1"] + _ht0["KEY0"];
//	_ht0["KEY3"] = "Asshole";
//	_ht0["KEY0"] = _ht0["KEY0"] + _ht0["KEY3"] + _ht0["KEY2"] + _ht0["KEY1"];

	_ht0.CreateHashtable();
//	_ht0 = _ht0 + ( _oa0 + _oa0 );
//	_ht0 = _ht0 + "B" + "C" + "A" + "B" + "C";
//	_ht0 = _ht0 + 1234 + 4321 + 3412 + 2143 + 1000;
	_ht0 = _ht0 + "B" + "C" + ( _oa0 + _oa0 ) + "A" + "B" + "C";

	if ( 1 ) {
		_var _ht1;
		_ht1 = _ht0 + "D" + "E";
	}

//	_ht0 = _ht0 + ( _ht0 + _ht0 ) + "B" + "C";// + ( _oa0 + _oa0 );// + "A";// + "B" + "C";
//	_ht0 += _ht0 + ( _ht0 + _ht0 ) + _oa0 + _oa0 + "KEY5" + "KEY6" + 6.789;

	//char *_utf8str = Local_2_UTF8("统一编码");
	//printf("\nstrlen=[%d],str=[%s]\n", strlen(_utf8str), _utf8str);
	//delete []_utf8str;
	//
	//MGEObject *_obj = reinterpret_cast<MGEObject *>(&_ht0);
	//
	//printf("\n _var typeid=[%s]\n", typeid(*_obj).name() );

	_ht0 = Con0(_var("blue"), _var("blonde"), _var("beauty"));
	printf("\n _var typeid=[%s]\n", (char*)(_ht0["attrib2"].GetBuffer(NULL)) );

}



int _tmain(int argc, _TCHAR* argv[]) {
	TestMGEv2();
//	TestMGEv2CL();
	_CrtDumpMemoryLeaks();
    return 0;
}
