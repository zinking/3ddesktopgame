// cppdll.cpp : ���� DLL Ӧ�ó������ڵ㡣
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

//// ���ǵ���������һ��ʾ��
//CPPDLL_API int ncppdll=0;
//
//// ���ǵ���������һ��ʾ����
//CPPDLL_API int fncppdll(void)
//{
//	return 42;
//}
//
//// �����ѵ�����Ĺ��캯����
//// �й��ඨ�����Ϣ������� cppdll.h
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
