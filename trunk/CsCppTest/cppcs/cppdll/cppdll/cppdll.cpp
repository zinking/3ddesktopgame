// cppdll.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include "cppdll.h"


#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

//// 这是导出变量的一个示例
//CPPDLL_API int ncppdll=0;
//
//// 这是导出函数的一个示例。
//CPPDLL_API int fncppdll(void)
//{
//	return 42;
//}
//
//// 这是已导出类的构造函数。
//// 有关类定义的信息，请参阅 cppdll.h
//Ccppdll::Ccppdll()
//{
//	return;
//}

CPPDLL_API void print()
{
	printf("hello world\n");
}

CPPDLL_API void passIntByPointer(int *i)
{
	*i = 2;
}

CPPDLL_API void passIntByReference(int &i)
{
	i = 2;
}

CPPDLL_API void passStringByCharPointer(char *string)
{
	printf("%s\n", string);
}

CPPDLL_API void smw::printInNamespace()
{
	printf("hello world from smw\n");
}
