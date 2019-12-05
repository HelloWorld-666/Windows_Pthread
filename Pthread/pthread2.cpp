#include <stdio.h>
#include <iostream>
#include <windows.h>    //CreateThread()
#include <tchar.h>
#include <process.h>    //_beginthread()
 
using namespace std;

//int counts;
//
//HANDLE hMutex = NULL;
//const DWORD THREAD_NUM = 50;//启动线程数
//
//unsigned int __stdcall ThreadFun(PVOID pM)
//{
//    WaitForSingleObject(hMutex, INFINITE);                    //方法1-a：互斥量
//    //Sleep(100);
//    //counts++;
//    //InterlockedIncrement((LPLONG)&counts);                  //方法2：InterlockedIncrement:实现数的原子性加法操作   减：InterLockedDecrement()
//    //Sleep(50);
//    printf("线程ID：%d \t 子线程报数：%d\n", GetCurrentThreadId(), counts);
//    ReleaseMutex(hMutex);                                      //方法1-b：互斥量
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
//        HANDLE handle[THREAD_NUM];                  //注意：handle[N];  i < N;  WaitForMultipleObjects(N, ...)
//        counts = 0;
//        for (int i = 0; i < THREAD_NUM; i++)
//        {
//            //counts = 0;   //错误
//            WaitForSingleObject(hMutex, INFINITE);
//            handle[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadFun, NULL, 0, NULL);          
//            ReleaseMutex(hMutex);
//        }
//        WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);           //等待第二个参数中的内核对象的，当内核对象有信号时，调用线程才会被调度，并返回值，顺序执行下去。第三个参数：如果此参数为TRUE，则在lpHandles数组中的所有对象的状态发出信号时，该函数返回
//        printf("有10个用户登录后记录结果是%d\n", counts);
//    }
//
//    getchar();
//    return 0;
//}

/*
    _beginthreadex()函数在创建新线程时会分配并初始化一个_tiddata块。这个_tiddata块自然是用来存放一些需要线程独享的数据。
    事实上新线程运行时会首先将_tiddata块与自己进一步关联起来。然后新线程调用标准C运行库函数如strtok()时就会先取得_tiddata块的地址再将需要保护的数据存入_tiddata块中。
    这样每个线程就只会访问和修改自己的数据而不会去篡改其它线程的数据了。
    因此，如果在代码中有使用标准C运行库中的函数时，尽量使用_beginthreadex()来代替CreateThread()。
*/


//事件Event：
//int counts = 0;
//const DWORD THREAD_NUM1 = 10;
//HANDLE hThreadEvent;
//HANDLE hMutex = NULL;
//
//unsigned int __stdcall ThreadFun(PVOID pM)
//{
//    int num = *(int*)pM;                   //68、69行顺序不能相反，否则不同步！！！                             
//    SetEvent(hThreadEvent);                                                             //2.触发事件
//    //开启线程是需要一定的开销的，所以新线程并不能第一时间执行到这里
//    WaitForSingleObject(hMutex, INFINITE);
//    Sleep(50);
//    counts++;
//    Sleep(0);                                                                           //让其他线程有机会优先执行
//    printf("线程传递参数线程编号为：%d  全局变量counts值为：%d\n", num, counts);
//    //cout << "i = " << *(int*)pM << '\t' << "counts = " << counts << endl;             //因为endl的原因导致输出乱码，需要用互斥量解决输出错乱问题
//    ReleaseMutex(hMutex);
//
//    return 0;
//}
// 
//int main()
//{
//    hMutex = CreateMutex(NULL, FALSE, _T("MainThread2"));
//    int n = 20;
//    HANDLE handle[THREAD_NUM1];                                                         //注意：handle[N];  i < N;  WaitForMultipleObjects(N, ...)
//    handle[0] = NULL;
//    hThreadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);                               //1. 创建事件    第二个参数确定事件是手动置位还是自动置位，TRUE:手动置位，FALSE:自动置位
//
//    for (int i = 0; i < THREAD_NUM1; i++)
//    {
//        WaitForSingleObject(hMutex, INFINITE);
//        handle[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadFun, &i, 0, NULL);
//        Sleep(0);
//        ReleaseMutex(hMutex);
//        WaitForSingleObject(hThreadEvent, INFINITE);                                    //4.等待事件被触发    如果为自动置位，则对该事件调用WaitForSingleObject()后会自动调用ResetEvent()使事件变成未触发状态
//    }
//    WaitForMultipleObjects(THREAD_NUM1, handle, TRUE, INFINITE);                        //等待第二个参数中的内核对象的，当内核对象有信号时，调用线程才会被调度，并返回值，顺序执行下去。第三个参数：如果此参数为TRUE，则在lpHandles数组中的所有对象的状态发出信号时，该函数返回
//    CloseHandle(hThreadEvent);                                                          //3.销毁事件
//
//    getchar();
//    return 0;
//}

/*
    主线程创建子线程并传入一个指向变量地址的指针作参数，由于线程启动须要花费一定的时间，所以在子线程根据这个指针访问并保存数据前，
    主线程应等待子线程保存完毕后才能改动该参数并启动下一个线程。
    这涉及到主线程与子线程之间的同步。否则子线程保存的数据可能是++i之后的新值        

    用事件Event处理主线程与子线程的同步(线程编号i)，用互斥量Mutex来处理各子线程间的互斥(全局变量counts)

    线程编号i的输出没有重复，说明主线程与子线程达到了同步； 全局变量的输出是递增的，说明各子线程已经互斥的访问和输出该全局资源。



    Mutex：
    Mutex的特殊性（就是主线程和子线程wait之后，获取信号的机会是一样的），所以无法达到同步的目的，只能用来互斥
    WaitForSingleObject只对主线程有效，对子线程无效。&quot;那是因为互斥量的线程所有权的原因

    ！！！主线程和子线程获取mutex的机会是一样的，所以有可能主线程先获取了mutex,那么就无法达到预期的要求了。所以mutex不方便用于同步。不像EVENT，可以确保子线程先得到信号。
*/


//#include <process.h>
//#include <windows.h>
//long g_nNum;
//unsigned int __stdcall Fun(void *pPM);
//const int THREAD_NUM = 10;
////事件与关键段
//HANDLE  g_hThreadEvent;
//CRITICAL_SECTION g_csThreadCode;
//int main()
//{
//    //初始化事件和关键段 自动置位,初始无触发的匿名事件
//    g_hThreadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
//    //InitializeCriticalSection(&g_csThreadCode);
//
//    HANDLE  handle[THREAD_NUM];
//    g_nNum = 0;
//    int i = 0;
//    while (i < THREAD_NUM)
//    {
//        handle[i] = (HANDLE)_beginthreadex(NULL, 0, Fun, &i, 0, NULL);
//        WaitForSingleObject(g_hThreadEvent, INFINITE); //等待事件被触发
//        i++;
//    }
//    WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);
//
//    //销毁事件和关键段
//    CloseHandle(g_hThreadEvent);
//    //DeleteCriticalSection(&g_csThreadCode);
//    return 0;
//}
//unsigned int __stdcall Fun(void *pPM)
//{
//    int nThreadNum = *(int *)pPM;
//    SetEvent(g_hThreadEvent); //触发事件
//
//    Sleep(50);//some work should to do
//
//    //EnterCriticalSection(&g_csThreadCode);
//    g_nNum++;
//    Sleep(0);//some work should to do
//    printf("线程编号为%d  全局资源值为%d\n", nThreadNum, g_nNum);
//    //LeaveCriticalSection(&g_csThreadCode);
//    getchar();
//    return 0;
//}
