// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� CPPDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// CPPDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef CPPDLL_EXPORTS
#define CPPDLL_API __declspec(dllexport)
#else
#define CPPDLL_API __declspec(dllimport)
#endif

//// �����Ǵ� cppdll.dll ������
//class CPPDLL_API Ccppdll {
//public:
//	Ccppdll(void);
//	// TODO: �ڴ�������ķ�����
//};
//
//extern CPPDLL_API int ncppdll;
//
//CPPDLL_API int fncppdll(void);


CPPDLL_API void print();

CPPDLL_API void passIntByPointer(int *i);

CPPDLL_API void passIntByReference(int &i);

CPPDLL_API void passStringByCharPointer(char *string);

namespace smw {
	CPPDLL_API void printInNamespace();
}

class 

