#include <stdio.h>
#include <iostream>
#include <windows.h>    //CreateThread()
#include <tchar.h>
#include <process.h>    //_beginthread()
 
using namespace std;

//int counts;
//
//HANDLE hMutex = NULL;
//const DWORD THREAD_NUM = 50;//�����߳���
//
//unsigned int __stdcall ThreadFun(PVOID pM)
//{
//    WaitForSingleObject(hMutex, INFINITE);                    //����1-a��������
//    //Sleep(100);
//    //counts++;
//    //InterlockedIncrement((LPLONG)&counts);                  //����2��InterlockedIncrement:ʵ������ԭ���Լӷ�����   ����InterLockedDecrement()
//    //Sleep(50);
//    printf("�߳�ID��%d \t ���̱߳�����%d\n", GetCurrentThreadId(), counts);
//    ReleaseMutex(hMutex);                                      //����1-b��������
//
//    return 0;
//}
//
//int main()
//{
//    hMutex = CreateMutex(NULL, FALSE, _T("MainThread2"));
//
//    int n = 20;
//    while (n--)
//    {
//        cout << "n = " << n << endl;
//        HANDLE handle[THREAD_NUM];                  //ע�⣺handle[N];  i < N;  WaitForMultipleObjects(N, ...)
//        counts = 0;
//        for (int i = 0; i < THREAD_NUM; i++)
//        {
//            //counts = 0;   //����
//            WaitForSingleObject(hMutex, INFINITE);
//            handle[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadFun, NULL, 0, NULL);          
//            ReleaseMutex(hMutex);
//        }
//        WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);           //�ȴ��ڶ��������е��ں˶���ģ����ں˶������ź�ʱ�������̲߳Żᱻ���ȣ�������ֵ��˳��ִ����ȥ������������������˲���ΪTRUE������lpHandles�����е����ж����״̬�����ź�ʱ���ú�������
//        printf("��10���û���¼���¼�����%d\n", counts);
//    }
//
//    getchar();
//    return 0;
//}

/*
    _beginthreadex()�����ڴ������߳�ʱ����䲢��ʼ��һ��_tiddata�顣���_tiddata����Ȼ���������һЩ��Ҫ�̶߳�������ݡ�
    ��ʵ�����߳�����ʱ�����Ƚ�_tiddata�����Լ���һ������������Ȼ�����̵߳��ñ�׼C���п⺯����strtok()ʱ�ͻ���ȡ��_tiddata��ĵ�ַ�ٽ���Ҫ���������ݴ���_tiddata���С�
    ����ÿ���߳̾�ֻ����ʺ��޸��Լ������ݶ�����ȥ�۸������̵߳������ˡ�
    ��ˣ�����ڴ�������ʹ�ñ�׼C���п��еĺ���ʱ������ʹ��_beginthreadex()������CreateThread()��
*/


//�¼�Event��
//int counts = 0;
//const DWORD THREAD_NUM1 = 10;
//HANDLE hThreadEvent;
//HANDLE hMutex = NULL;
//
//unsigned int __stdcall ThreadFun(PVOID pM)
//{
//    int num = *(int*)pM;                   //68��69��˳�����෴������ͬ��������                             
//    SetEvent(hThreadEvent);                                                             //2.�����¼�
//    //�����߳�����Ҫһ���Ŀ����ģ��������̲߳����ܵ�һʱ��ִ�е�����
//    WaitForSingleObject(hMutex, INFINITE);
//    Sleep(50);
//    counts++;
//    Sleep(0);                                                                           //�������߳��л�������ִ��
//    printf("�̴߳��ݲ����̱߳��Ϊ��%d  ȫ�ֱ���countsֵΪ��%d\n", num, counts);
//    //cout << "i = " << *(int*)pM << '\t' << "counts = " << counts << endl;             //��Ϊendl��ԭ����������룬��Ҫ�û�������������������
//    ReleaseMutex(hMutex);
//
//    return 0;
//}
// 
//int main()
//{
//    hMutex = CreateMutex(NULL, FALSE, _T("MainThread2"));
//    int n = 20;
//    HANDLE handle[THREAD_NUM1];                                                         //ע�⣺handle[N];  i < N;  WaitForMultipleObjects(N, ...)
//    handle[0] = NULL;
//    hThreadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);                               //1. �����¼�    �ڶ�������ȷ���¼����ֶ���λ�����Զ���λ��TRUE:�ֶ���λ��FALSE:�Զ���λ
//
//    for (int i = 0; i < THREAD_NUM1; i++)
//    {
//        WaitForSingleObject(hMutex, INFINITE);
//        handle[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadFun, &i, 0, NULL);
//        Sleep(0);
//        ReleaseMutex(hMutex);
//        WaitForSingleObject(hThreadEvent, INFINITE);                                    //4.�ȴ��¼�������    ���Ϊ�Զ���λ����Ը��¼�����WaitForSingleObject()����Զ�����ResetEvent()ʹ�¼����δ����״̬
//    }
//    WaitForMultipleObjects(THREAD_NUM1, handle, TRUE, INFINITE);                        //�ȴ��ڶ��������е��ں˶���ģ����ں˶������ź�ʱ�������̲߳Żᱻ���ȣ�������ֵ��˳��ִ����ȥ������������������˲���ΪTRUE������lpHandles�����е����ж����״̬�����ź�ʱ���ú�������
//    CloseHandle(hThreadEvent);                                                          //3.�����¼�
//
//    getchar();
//    return 0;
//}

/*
    ���̴߳������̲߳�����һ��ָ�������ַ��ָ���������������߳�������Ҫ����һ����ʱ�䣬���������̸߳������ָ����ʲ���������ǰ��
    ���߳�Ӧ�ȴ����̱߳�����Ϻ���ܸĶ��ò�����������һ���̡߳�
    ���漰�����߳������߳�֮���ͬ�����������̱߳�������ݿ�����++i֮�����ֵ        

    ���¼�Event�������߳������̵߳�ͬ��(�̱߳��i)���û�����Mutex����������̼߳�Ļ���(ȫ�ֱ���counts)

    �̱߳��i�����û���ظ���˵�����߳������̴߳ﵽ��ͬ���� ȫ�ֱ���������ǵ����ģ�˵�������߳��Ѿ�����ķ��ʺ������ȫ����Դ��



    Mutex��
    Mutex�������ԣ��������̺߳����߳�wait֮�󣬻�ȡ�źŵĻ�����һ���ģ��������޷��ﵽͬ����Ŀ�ģ�ֻ����������
    WaitForSingleObjectֻ�����߳���Ч�������߳���Ч��&quot;������Ϊ���������߳�����Ȩ��ԭ��

    ���������̺߳����̻߳�ȡmutex�Ļ�����һ���ģ������п������߳��Ȼ�ȡ��mutex,��ô���޷��ﵽԤ�ڵ�Ҫ���ˡ�����mutex����������ͬ��������EVENT������ȷ�����߳��ȵõ��źš�
*/


//#include <process.h>
//#include <windows.h>
//long g_nNum;
//unsigned int __stdcall Fun(void *pPM);
//const int THREAD_NUM = 10;
////�¼���ؼ���
//HANDLE  g_hThreadEvent;
//CRITICAL_SECTION g_csThreadCode;
//int main()
//{
//    //��ʼ���¼��͹ؼ��� �Զ���λ,��ʼ�޴����������¼�
//    g_hThreadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
//    //InitializeCriticalSection(&g_csThreadCode);
//
//    HANDLE  handle[THREAD_NUM];
//    g_nNum = 0;
//    int i = 0;
//    while (i < THREAD_NUM)
//    {
//        handle[i] = (HANDLE)_beginthreadex(NULL, 0, Fun, &i, 0, NULL);
//        WaitForSingleObject(g_hThreadEvent, INFINITE); //�ȴ��¼�������
//        i++;
//    }
//    WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);
//
//    //�����¼��͹ؼ���
//    CloseHandle(g_hThreadEvent);
//    //DeleteCriticalSection(&g_csThreadCode);
//    return 0;
//}
//unsigned int __stdcall Fun(void *pPM)
//{
//    int nThreadNum = *(int *)pPM;
//    SetEvent(g_hThreadEvent); //�����¼�
//
//    Sleep(50);//some work should to do
//
//    //EnterCriticalSection(&g_csThreadCode);
//    g_nNum++;
//    Sleep(0);//some work should to do
//    printf("�̱߳��Ϊ%d  ȫ����ԴֵΪ%d\n", nThreadNum, g_nNum);
//    //LeaveCriticalSection(&g_csThreadCode);
//    getchar();
//    return 0;
//}
