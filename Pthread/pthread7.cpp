//#include <stdio.h>
//#include <windows.h>
//#include <process.h>
//#include <tchar.h>
//
//using namespace std;

/////���ļ���pthread7_1.cpp��Ӧ����ʱ��ֱ������������д��������д���(��������)���Դ�����֤�¼���"����"����.   https://blog.csdn.net/MoreWindows/article/details/7823572
////�������д��ļ���������pthread7_1.cpp��
//int main()
//{
//    HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, _T("ProcessA!"));      //����2���Զ���λ ����3����ʼ״̬->δ����״̬
//    printf("�¼��Ѿ����������ڰ�a�����¼�������������ֹ����\n");
//    char ch;
//    scanf("%c", &ch);
//    if ('a' == ch)
//    {
//        exit(0);
//    }
//    SetEvent(hEvent);          //����Ϊ���ڵ���״̬���������̵ȴ�
//
//    CloseHandle(hEvent);
//
//    //getchar();
//    return 0;
//}
