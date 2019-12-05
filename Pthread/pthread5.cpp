#include <stdio.h>
#include <windows.h>
#include <process.h>

//using namespace std;
////读写者问题：一写 N读(可同时)
//CRITICAL_SECTION  g_cs/*, g_csReaderCount*/; 
//HANDLE hEventWriterIsOK;                                    // 写者是否完成 是否可读
//HANDLE hEventReaderIsOK;                                    // 读者是否完成 是否可写
//int    ReaderNum = 0;
//
//unsigned int __stdcall ReaderThreadFun(PVOID pM)
//{
//    printf("    编号为%d的读者进入等待中...\n", GetCurrentThreadId());
//    WaitForSingleObject(hEventWriterIsOK, INFINITE);        //等待写者完成写任务
//
//    EnterCriticalSection(&g_cs);
//    ReaderNum++;
//    if (1 == ReaderNum)
//    {
//        ResetEvent(hEventReaderIsOK);                       //读者read操作为未完成状态(不可触发),写者不能进行write操作
//    }
//    LeaveCriticalSection(&g_cs);
//
//    printf("编号为%d的读者正在读文件...\n", GetCurrentThreadId());
//    printf("编号为%d的读者结束读文件...\n", GetCurrentThreadId());
//
//    EnterCriticalSection(&g_cs);
//    ReaderNum--;
//    if (0 == ReaderNum)
//    {
//        SetEvent(hEventReaderIsOK);                         //所有读者都完成read操作，接下来写者可write
//    }
//    LeaveCriticalSection(&g_cs);
//
//    return 0;
//}
//
//unsigned int __stdcall WriteThreadFun(PVOID pM)
//{
//    printf("    编号为%d的写者进入等待中...\n", GetCurrentThreadId());
//    WaitForSingleObject(hEventReaderIsOK, INFINITE);        //等待所有读者完成read操作后，才能write
//    ResetEvent(hEventWriterIsOK);                           //write操作未完成 -> 不可读
//    printf("编号为%d的写者正在写文件...\n", GetCurrentThreadId());
//    printf("编号为%d的写者结束写文件...\n", GetCurrentThreadId());         //先结束 才能设置状态
//    SetEvent(hEventWriterIsOK);                             //write 操作已完成 -> 可读                 //SetEvent(&hEventWriterIsOK);错误，不加取地址符！！！！！！！！！！！！！！
//
//    return 0;
//}
//
//int main()
//{
//    InitializeCriticalSection(&g_cs);
//    hEventReaderIsOK = CreateEvent(NULL, FALSE, FALSE, NULL);
//    hEventWriterIsOK = CreateEvent(NULL, FALSE, TRUE, NULL);          //初始化：写者执行写文件操作
//
//    //读者、写者一共6个 0-5
//    HANDLE handle[6];
//    for (int i = 1; i <= 4; i++)    
//    {
//        //创建四个读者
//        handle[i] = (HANDLE)_beginthreadex(NULL, 0, ReaderThreadFun, NULL, 0, NULL);
//    }
//    //创建一个写者
//    handle[0] = (HANDLE)_beginthreadex(NULL, 0, WriteThreadFun, NULL, 0, NULL);
//    //创建一个读者
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
        第一．写者要等到没有读者时才能去写文件。

        第二．所有读者要等待写者完成写文件后才能去读文件。

        关键段维持读者数目增减的互斥操作，用两个Event表示文中的两种“等待情况.
*/



//读者与写者问题继 读写锁SRWLock：
//https://blog.csdn.net/MoreWindows/article/details/7650574https://blog.csdn.net/MoreWindows/article/details/7650574

//CRITICAL_SECTION cs;
//SRWLOCK rwlock;
//
//unsigned int __stdcall ReaderThreadFun(PVOID pM)
//{
//    printf("编号为%d的读者进入等待...\n", GetCurrentThreadId());
//    AcquireSRWLockShared(&rwlock);
//    EnterCriticalSection(&cs);
//    printf("编号为%d的读者正在读文件...\n", GetCurrentThreadId());
//    LeaveCriticalSection(&cs);
//    printf("编号为%d的读者结束读文件...\n", GetCurrentThreadId());
//    ReleaseSRWLockShared(&rwlock);
//
//    return 0;
//}
//
//unsigned int __stdcall WriterThreadFun(PVOID pM)
//{
//    printf("    编号为%d的写者进入等待...\n", GetCurrentThreadId());
//    AcquireSRWLockExclusive(&rwlock);
//    EnterCriticalSection(&cs);
//    printf("    编号为%d的写者正在写文件...\n", GetCurrentThreadId());
//    LeaveCriticalSection(&cs);
//    printf("    编号为%d的写者结束写文件...\n", GetCurrentThreadId());
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
//        //创建四个读者
//        handle[i] = (HANDLE)_beginthreadex(NULL, 0, ReaderThreadFun, NULL, 0, NULL);
//    }
//    //创建一个写者
//    handle[0] = (HANDLE)_beginthreadex(NULL, 0, WriterThreadFun, NULL, 0, NULL);
//    //创建一个读者
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
