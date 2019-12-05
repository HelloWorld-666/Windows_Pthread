#include <stdio.h>
#include <iostream>
#include <windows.h>    //CreateThread()
#include <tchar.h>
#include <process.h>    //_beginthread()

using namespace std;

////1�������ߣ�1�������
//#define NUM 10
//int g_buffer;
//HANDLE hMutex;
//HANDLE hEventFull, hEventEmpty;
//
////���ÿ���̨�����ɫ
//BOOL SetConsoleColor(WORD wAttributes)
//{
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);                      //����ָ����׼�豸�ľ����stdin,stdout,stderror����
//    if (hConsole == INVALID_HANDLE_VALUE)
//        return FALSE;
//    return SetConsoleTextAttribute(hConsole, wAttributes);
//}
//
//unsigned int __stdcall ProducerThreadFun(PVOID pM)
//{
//    for (int i = 0; i <= NUM; i++)
//    {
//        WaitForSingleObject(hEventEmpty, INFINITE);
//
//        WaitForSingleObject(hMutex, INFINITE);
//        g_buffer = i;
//        printf("�����߽�%d���뻺����.\n", i);
//        ReleaseMutex(hMutex);
//
//        SetEvent(hEventFull);
//    }
//
//    return 0;
//}
//
//unsigned int __stdcall ConsumerThreadFun(PVOID pM)
//{
//    /*volatile*/ bool flag = true;
//    while (flag)
//    {
//        WaitForSingleObject(hEventFull, INFINITE);
//
//        WaitForSingleObject(hMutex, INFINITE);                                      //�ӻ�����
//        SetConsoleColor(FOREGROUND_GREEN/*46*/);
//        printf("    �����ߴӻ�����ȡ��%d.\n", g_buffer);
//        SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
//        /*     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//             SetConsoleTextAttribute(hConsole, 7);*/
//        if (NUM == g_buffer)
//        {
//            flag = false;       
//        }
//        ReleaseMutex(hMutex);                                                       //�⻥����
//
//        SetEvent(hEventEmpty);
//        Sleep(10);
//    }
//
//    return 0;
//}
//
//int main()
//{
//    hMutex = CreateMutex(NULL, FALSE, NULL);                                          //����2��Mutex��Ϊ�κ��߳�ռ�ã����ڴ���״̬��
//    hEventFull = CreateEvent(NULL, FALSE, FALSE, NULL);                               //����2��FALSE�Զ���λ     ����3����ʼ״̬δ����
//    hEventEmpty = CreateEvent(NULL, FALSE, TRUE, NULL);                               //!!!������������ʼֵΪTRUE!!!
//
//    HANDLE hThread[2];
//    hThread[0] = (HANDLE)_beginthreadex(NULL, 0, ProducerThreadFun, NULL, 0, NULL);
//    hThread[1] = (HANDLE)_beginthreadex(NULL, 0, ConsumerThreadFun, NULL, 0, NULL);
//    WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
//
//    CloseHandle(hThread[0]);
//    CloseHandle(hThread[1]);
//
//    CloseHandle(hEventFull);
//    CloseHandle(hEventEmpty);
//
//    getchar();
//    return 0;
//}

/*
�����ߺ������߷ֱ���ҪSemaphore()������ͬ��������ȷ�����������������߻��������߽��в���(����ִ�������ǰ������)������ִ����������������
*/


//�������߸ĳ�2��������ظĳ�ӵ��4���������Ĵ󻺳�ء�
//#define NUM 9
//#define BUFFER_SIZE 4
//int g_buffer[BUFFER_SIZE];                                                  //�������൱��һ����ʱ�����Դ�Ĳֿ⣬���е���Դ�ǲ��ϱ仯��
//HANDLE hMutex;
//HANDLE hSemaphoreFull, hSemaphoreEmpty;
//int g_i = 0;    //������Ͷ�����ݵĻ��������
//int g_j = 0;    //������ȡ�����ݵĻ��������
//
////���ÿ���̨�����ɫ
//BOOL SetConsoleColor(WORD wAttributes)
//{
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);                      //����ָ����׼�豸�ľ����stdin,stdout,stderror����
//    if (hConsole == INVALID_HANDLE_VALUE)
//        return FALSE;
//    return SetConsoleTextAttribute(hConsole, wAttributes);
//}
//
//unsigned int __stdcall ProducerThreadFun(PVOID pM)
//{
//    for (int i = 0; i < NUM; i++)
//    {
//        WaitForSingleObject(hSemaphoreEmpty, INFINITE);
//
//        WaitForSingleObject(hMutex, INFINITE);
//        g_buffer[g_i] = i;
//        printf("�������ڻ���ص�%d����������Ͷ������%d\n", g_i, i);
//        g_i = (g_i + 1) % BUFFER_SIZE;
//        ReleaseMutex(hMutex);
//
//        ReleaseSemaphore(hSemaphoreFull, 1, NULL);      //֪ͨ�����߿����ѵ���Դ����1
//    }
//
//    return 0;
//}
//
//unsigned int __stdcall ConsumerThreadFun(PVOID pM)
//{
//    /*volatile*/ bool flag = true;
//    while (flag)
//    {
//        WaitForSingleObject(hSemaphoreFull, INFINITE);
//
//        WaitForSingleObject(hMutex, INFINITE);                                      //�ӻ�����
//        SetConsoleColor(/*FOREGROUND_GREEN*/46);
//        printf("    ���Ϊ%d�����ߴӵ�%d��������ȡ��%d.\n", GetCurrentThreadId(), g_j, g_buffer[g_j]);
//        SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
//        if (NUM == (g_buffer[g_j] + 1))                                             //��Ϊ���������Ǵ�0��ʼ�� 0-9 NUM=10
//        {
//            /*ReleaseMutex(hMutex);
//            ReleaseSemaphore(hSemaphoreFull, 1, NULL);*/
//            flag = false;
//            //break;
//        }
//        g_j = (g_j + 1) % BUFFER_SIZE;          //g_j��Ҫ���ϵ��� ++
//        ReleaseMutex(hMutex);                                                       //�⻥����
//
//        ReleaseSemaphore(hSemaphoreEmpty, 1, NULL);                                 //֪ͨ������������һ����Դ��������������һ����Դ
//        Sleep(10);
//    }
//
//    return 0;
//}
//
//int main()
//{
//    hMutex          = CreateMutex(NULL, FALSE, NULL);                                            //����2��Mutex��Ϊ�κ��߳�ռ�ã����ڴ���״̬��
//    hSemaphoreFull  = CreateSemaphore(NULL, 0, 4, NULL);                                //����2����ʼ��Դ����   ����3����󲢷���Դ����
//    hSemaphoreEmpty = CreateSemaphore(NULL, 4, 4, NULL);                                //!!��ʼEmpty��Դ����Ӧ���뻺��ص�������ͬ������4���Ա���Ϊ�������ṩ��������!!
//
//    //����һ�������ߺ�����������
//    HANDLE hThread[3];
//    hThread[0] = (HANDLE)_beginthreadex(NULL, 0, ProducerThreadFun, NULL, 0, NULL);
//    hThread[1] = (HANDLE)_beginthreadex(NULL, 0, ConsumerThreadFun, NULL, 0, NULL);
//    hThread[2] = (HANDLE)_beginthreadex(NULL, 0, ConsumerThreadFun, NULL, 0, NULL);
//    WaitForMultipleObjects(3, hThread, TRUE, INFINITE);                                 //����1�����̵߳ȴ����̸߳���(3)
//
//    CloseHandle(hThread[0]);
//    CloseHandle(hThread[1]);
//    CloseHandle(hThread[2]);
//
//    CloseHandle(hSemaphoreFull);
//    CloseHandle(hSemaphoreEmpty);
//
//    getchar();
//    return 0;
//}
