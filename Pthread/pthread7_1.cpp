//#include <stdio.h>
//#include <windows.h>
//#include <process.h>
//#include <tchar.h>
//
//using namespace std;

////���ļ���pthread7.cpp��Ӧ���ֱ������������д��������д���(��������)���Դ�����֤�¼���"����"����.   https://blog.csdn.net/MoreWindows/article/details/7823572

//int main()
//{
//    HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, TRUE, _T("ProcessA!"));      //����2���Զ���λ ����3����ʼ״̬->δ����״̬
//    if (NULL == hEvent)
//    {
//        printf("���¼�ʧ�ܣ�\n");
//    }
//    
//    DWORD iResult = WaitForSingleObject(hEvent, 10 * 1000);
//    switch (iResult)
//    {
//    case WAIT_ABANDONED:
//        printf("ӵ���¼��Ľ���������ֹ.\n");
//        break;
//    case WAIT_OBJECT_0:
//        printf("���յ��ź�.\n");
//        break;
//    case WAIT_TIMEOUT:
//        printf("δ�ڹ涨ʱ���ڽ��յ��ź�.\n");
//        break;
//    default:
//        break;
//    }
//
//    CloseHandle(hEvent);
//
//    //getchar();
//    return 0;
//}
