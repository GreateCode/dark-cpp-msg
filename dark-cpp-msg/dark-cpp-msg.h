// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� DARKCPPMSG_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// DARKCPPMSG_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef DARKCPPMSG_EXPORTS
#define DARKCPPMSG_API __declspec(dllexport)
#else
#define DARKCPPMSG_API __declspec(dllimport)
#endif

// �����Ǵ� dark-cpp-msg.dll ������
class DARKCPPMSG_API Cdarkcppmsg {
public:
	Cdarkcppmsg(void);
	// TODO: �ڴ�������ķ�����
};

extern DARKCPPMSG_API int ndarkcppmsg;

DARKCPPMSG_API int fndarkcppmsg(void);
