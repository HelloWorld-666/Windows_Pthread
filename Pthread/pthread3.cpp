//#include <stdio.h>
//#include <iostream>
//#include <windows.h>    //CreateThread()
//#include <tchar.h>
//#include <process.h>    //_beginthread()
//
//
////信号量Semaphore：
//int counts = 0;
//const DWORD THREAD_NUM1 = 10;
//HANDLE hThreadSemaphore;
//HANDLE hMutex = NULL;
//
//unsigned int __stdcall ThreadFun(PVOID pM)
//{
//    int num = *(int*)pM;                   //68、69行顺序不能相反，否则不同步！！！
//    ReleaseSemaphore(hThreadSemaphore, 1, NULL);                                        //Semaphore值递增
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
//
//    hThreadSemaphore = CreateSemaphore(NULL, 0, 1, NULL);                               //属性、初始Semaphore值、最大pthread并发数、匿名Semaphore
//
//    for (int i = 0; i < THREAD_NUM1; i++)
//    {
//        WaitForSingleObject(hMutex, INFINITE);
//        handle[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadFun, &i, 0, NULL);
//        Sleep(0);
//        WaitForSingleObject(hThreadSemaphore, INFINITE);                                //当前值为 0 ；等待ReleaseSemaphore() +1 使信号量值 > 0
//        ReleaseMutex(hMutex);
//    }
//    WaitForMultipleObjects(THREAD_NUM1, handle, TRUE, INFINITE);                        //等待第二个参数中的内核对象的，当内核对象有信号时，调用线程才会被调度，并返回值，顺序执行下去。第三个参数：如果此参数为TRUE，则在lpHandles数组中的所有对象的状态发出信号时，该函数返回
//    CloseHandle(hThreadSemaphore);
//
//    getchar();
//    return 0;
//}

/*
    https://blog.csdn.net/morewindows/article/details/7481609
*/