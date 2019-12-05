#include <stdio.h>
#include <iostream>
#include <windows.h>    //CreateThread()
#include <tchar.h>
#include <process.h>    //_beginthread()

using namespace std;

////1个消费者，1个缓冲池
//#define NUM 10
//int g_buffer;
//HANDLE hMutex;
//HANDLE hEventFull, hEventEmpty;
//
////设置控制台输出颜色
//BOOL SetConsoleColor(WORD wAttributes)
//{
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);                      //检索指定标准设备的句柄（stdin,stdout,stderror）。
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
//        printf("生产者将%d放入缓冲区.\n", i);
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
//        WaitForSingleObject(hMutex, INFINITE);                                      //加互斥量
//        SetConsoleColor(FOREGROUND_GREEN/*46*/);
//        printf("    消费者从缓冲区取出%d.\n", g_buffer);
//        SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
//        /*     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//             SetConsoleTextAttribute(hConsole, 7);*/
//        if (NUM == g_buffer)
//        {
//            flag = false;       
//        }
//        ReleaseMutex(hMutex);                                                       //解互斥量
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
//    hMutex = CreateMutex(NULL, FALSE, NULL);                                          //参数2：Mutex不为任何线程占用，处于触发状态。
//    hEventFull = CreateEvent(NULL, FALSE, FALSE, NULL);                               //参数2：FALSE自动置位     参数3：初始状态未触发
//    hEventEmpty = CreateEvent(NULL, FALSE, TRUE, NULL);                               //!!!第三个参数初始值为TRUE!!!
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
生产者和消费者分别需要Semaphore()来进行同步，才能确定接下来是由生产者还是消费者进行操作(满足执行任务的前提条件)，才能执行生产和消费任务
*/


//将消费者改成2个，缓冲池改成拥有4个缓冲区的大缓冲池。
//#define NUM 9
//#define BUFFER_SIZE 4
//int g_buffer[BUFFER_SIZE];                                                  //缓冲区相当于一个临时存放资源的仓库，其中的资源是不断变化的
//HANDLE hMutex;
//HANDLE hSemaphoreFull, hSemaphoreEmpty;
//int g_i = 0;    //生产者投放数据的缓冲区编号
//int g_j = 0;    //消费者取出数据的缓冲区编号
//
////设置控制台输出颜色
//BOOL SetConsoleColor(WORD wAttributes)
//{
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);                      //检索指定标准设备的句柄（stdin,stdout,stderror）。
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
//        printf("生产者在缓冲池第%d个缓冲区中投放数据%d\n", g_i, i);
//        g_i = (g_i + 1) % BUFFER_SIZE;
//        ReleaseMutex(hMutex);
//
//        ReleaseSemaphore(hSemaphoreFull, 1, NULL);      //通知消费者可消费的资源数加1
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
//        WaitForSingleObject(hMutex, INFINITE);                                      //加互斥量
//        SetConsoleColor(/*FOREGROUND_GREEN*/46);
//        printf("    编号为%d消费者从第%d个缓冲区取出%d.\n", GetCurrentThreadId(), g_j, g_buffer[g_j]);
//        SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
//        if (NUM == (g_buffer[g_j] + 1))                                             //因为数组坐标是从0开始的 0-9 NUM=10
//        {
//            /*ReleaseMutex(hMutex);
//            ReleaseSemaphore(hSemaphoreFull, 1, NULL);*/
//            flag = false;
//            //break;
//        }
//        g_j = (g_j + 1) % BUFFER_SIZE;          //g_j需要不断递增 ++
//        ReleaseMutex(hMutex);                                                       //解互斥量
//
//        ReleaseSemaphore(hSemaphoreEmpty, 1, NULL);                                 //通知生产者消费了一个资源数，请求再生产一个资源
//        Sleep(10);
//    }
//
//    return 0;
//}
//
//int main()
//{
//    hMutex          = CreateMutex(NULL, FALSE, NULL);                                            //参数2：Mutex不为任何线程占用，处于触发状态。
//    hSemaphoreFull  = CreateSemaphore(NULL, 0, 4, NULL);                                //参数2：初始资源数量   参数3：最大并发资源数量
//    hSemaphoreEmpty = CreateSemaphore(NULL, 4, 4, NULL);                                //!!初始Empty资源数量应该与缓存池的数量相同，等于4，以便于为生产者提供生产条件!!
//
//    //创建一个生产者和两个消费者
//    HANDLE hThread[3];
//    hThread[0] = (HANDLE)_beginthreadex(NULL, 0, ProducerThreadFun, NULL, 0, NULL);
//    hThread[1] = (HANDLE)_beginthreadex(NULL, 0, ConsumerThreadFun, NULL, 0, NULL);
//    hThread[2] = (HANDLE)_beginthreadex(NULL, 0, ConsumerThreadFun, NULL, 0, NULL);
//    WaitForMultipleObjects(3, hThread, TRUE, INFINITE);                                 //参数1：主线程等待子线程个数(3)
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
