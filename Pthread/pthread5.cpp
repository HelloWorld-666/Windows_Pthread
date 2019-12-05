#include <stdio.h>
#include <windows.h>
#include <process.h>

//using namespace std;
////��д�����⣺һд N��(��ͬʱ)
//CRITICAL_SECTION  g_cs/*, g_csReaderCount*/; 
//HANDLE hEventWriterIsOK;                                    // д���Ƿ���� �Ƿ�ɶ�
//HANDLE hEventReaderIsOK;                                    // �����Ƿ���� �Ƿ��д
//int    ReaderNum = 0;
//
//unsigned int __stdcall ReaderThreadFun(PVOID pM)
//{
//    printf("    ���Ϊ%d�Ķ��߽���ȴ���...\n", GetCurrentThreadId());
//    WaitForSingleObject(hEventWriterIsOK, INFINITE);        //�ȴ�д�����д����
//
//    EnterCriticalSection(&g_cs);
//    ReaderNum++;
//    if (1 == ReaderNum)
//    {
//        ResetEvent(hEventReaderIsOK);                       //����read����Ϊδ���״̬(���ɴ���),д�߲��ܽ���write����
//    }
//    LeaveCriticalSection(&g_cs);
//
//    printf("���Ϊ%d�Ķ������ڶ��ļ�...\n", GetCurrentThreadId());
//    printf("���Ϊ%d�Ķ��߽������ļ�...\n", GetCurrentThreadId());
//
//    EnterCriticalSection(&g_cs);
//    ReaderNum--;
//    if (0 == ReaderNum)
//    {
//        SetEvent(hEventReaderIsOK);                         //���ж��߶����read������������д�߿�write
//    }
//    LeaveCriticalSection(&g_cs);
//
//    return 0;
//}
//
//unsigned int __stdcall WriteThreadFun(PVOID pM)
//{
//    printf("    ���Ϊ%d��д�߽���ȴ���...\n", GetCurrentThreadId());
//    WaitForSingleObject(hEventReaderIsOK, INFINITE);        //�ȴ����ж������read�����󣬲���write
//    ResetEvent(hEventWriterIsOK);                           //write����δ��� -> ���ɶ�
//    printf("���Ϊ%d��д������д�ļ�...\n", GetCurrentThreadId());
//    printf("���Ϊ%d��д�߽���д�ļ�...\n", GetCurrentThreadId());         //�Ƚ��� ��������״̬
//    SetEvent(hEventWriterIsOK);                             //write ��������� -> �ɶ�                 //SetEvent(&hEventWriterIsOK);���󣬲���ȡ��ַ������������������������������
//
//    return 0;
//}
//
//int main()
//{
//    InitializeCriticalSection(&g_cs);
//    hEventReaderIsOK = CreateEvent(NULL, FALSE, FALSE, NULL);
//    hEventWriterIsOK = CreateEvent(NULL, FALSE, TRUE, NULL);          //��ʼ����д��ִ��д�ļ�����
//
//    //���ߡ�д��һ��6�� 0-5
//    HANDLE handle[6];
//    for (int i = 1; i <= 4; i++)    
//    {
//        //�����ĸ�����
//        handle[i] = (HANDLE)_beginthreadex(NULL, 0, ReaderThreadFun, NULL, 0, NULL);
//    }
//    //����һ��д��
//    handle[0] = (HANDLE)_beginthreadex(NULL, 0, WriteThreadFun, NULL, 0, NULL);
//    //����һ������
//    handle[5] = (HANDLE)_beginthreadex(NULL, 0, ReaderThreadFun, NULL, 0, NULL);
//    WaitForMultipleObjects(6, handle, TRUE, INFINITE);
//
//    for (int i = 0; i < 6; i++)
//    {
//        CloseHandle(handle[i]);
//    }
//    CloseHandle(hEventReaderIsOK);
//    CloseHandle(hEventWriterIsOK);
//    DeleteCriticalSection(&g_cs);
//
//    getchar();
//    return 0;
//}

/*
        ��һ��д��Ҫ�ȵ�û�ж���ʱ����ȥд�ļ���

        �ڶ������ж���Ҫ�ȴ�д�����д�ļ������ȥ���ļ���

        �ؼ���ά�ֶ�����Ŀ�����Ļ��������������Event��ʾ���е����֡��ȴ����.
*/



//������д������� ��д��SRWLock��
//https://blog.csdn.net/MoreWindows/article/details/7650574https://blog.csdn.net/MoreWindows/article/details/7650574

//CRITICAL_SECTION cs;
//SRWLOCK rwlock;
//
//unsigned int __stdcall ReaderThreadFun(PVOID pM)
//{
//    printf("���Ϊ%d�Ķ��߽���ȴ�...\n", GetCurrentThreadId());
//    AcquireSRWLockShared(&rwlock);
//    EnterCriticalSection(&cs);
//    printf("���Ϊ%d�Ķ������ڶ��ļ�...\n", GetCurrentThreadId());
//    LeaveCriticalSection(&cs);
//    printf("���Ϊ%d�Ķ��߽������ļ�...\n", GetCurrentThreadId());
//    ReleaseSRWLockShared(&rwlock);
//
//    return 0;
//}
//
//unsigned int __stdcall WriterThreadFun(PVOID pM)
//{
//    printf("    ���Ϊ%d��д�߽���ȴ�...\n", GetCurrentThreadId());
//    AcquireSRWLockExclusive(&rwlock);
//    EnterCriticalSection(&cs);
//    printf("    ���Ϊ%d��д������д�ļ�...\n", GetCurrentThreadId());
//    LeaveCriticalSection(&cs);
//    printf("    ���Ϊ%d��д�߽���д�ļ�...\n", GetCurrentThreadId());
//    ReleaseSRWLockExclusive(&rwlock);
//
//    return 0;
//}
//
//int main()
//{
//    InitializeSRWLock(&rwlock);
//    InitializeCriticalSection(&cs);
//
//    HANDLE handle[6];
//    for (int i = 1; i <= 4; i++)    
//    {
//        //�����ĸ�����
//        handle[i] = (HANDLE)_beginthreadex(NULL, 0, ReaderThreadFun, NULL, 0, NULL);
//    }
//    //����һ��д��
//    handle[0] = (HANDLE)_beginthreadex(NULL, 0, WriterThreadFun, NULL, 0, NULL);
//    //����һ������
//    handle[5] = (HANDLE)_beginthreadex(NULL, 0, ReaderThreadFun, NULL, 0, NULL);
//    WaitForMultipleObjects(6, handle, TRUE, INFINITE);
//    
//    for (int i = 0; i < 6; i++)
//    {
//        CloseHandle(handle[i]);
//    }
//    DeleteCriticalSection(&cs);
//
//    getchar();
//    return 0;
//}
