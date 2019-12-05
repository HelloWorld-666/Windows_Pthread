//#include <stdio.h>
//#include <windows.h>
//#include <process.h>
//#include <tchar.h>
//
///*
//        双线程读写队列数据：
//        https://blog.csdn.net/MoreWindows/article/details/8646902
//*/
//CRITICAL_SECTION cs;
//
//const int N = 5;
//int Dqueue[N] = { 0 };          //定义双向队列
//int i = 0; 
//int j = 0;
//HANDLE hEmptyNum;               //缓冲区空位数 -> 可写入data数
//HANDLE hReadDataNum;            //缓冲区空位数 -> 可读取data数
//
//unsigned int __stdcall ReaderThreadFun(PVOID pM)
//{
//    int OutputData = 0;
//    while (OutputData < 20)
//    {
//         WaitForSingleObject(hReadDataNum, INFINITE);
//
//         OutputData = Dqueue[i];
//         i = (i + 1) % N;
//         //EnterCriticalSection(&cs);
//         printf("从队列中读取数据%d\n", OutputData);
//         //LeaveCriticalSection(&cs);
//
//         ReleaseSemaphore(hEmptyNum, 1, NULL);
//    }
//    
//    return 0;
//}
//
//unsigned int __stdcall WriterThreadFun(PVOID pM)
//{
//    int InputData = 0;
//    while (InputData < 20)
//    {
//        WaitForSingleObject(hEmptyNum, INFINITE);
//
//        Dqueue[j] = ++InputData;
//        j = (j + 1) % N;
//        //EnterCriticalSection(&cs);
//        printf("    往队列中写入数据%d\n", InputData);
//        //LeaveCriticalSection(&cs);
//
//        ReleaseSemaphore(hReadDataNum, 1, NULL);
//    }
//
//    return 0;
//}
//
//int main()
//{
//    InitializeCriticalSection(&cs);
//    hEmptyNum    = CreateSemaphore(NULL, N, N, NULL);               //参数2：资源数初始化为N
//    hReadDataNum = CreateSemaphore(NULL, 0, N, NULL);
//
//    HANDLE handle[2];
//    handle[0] = (HANDLE)_beginthreadex(NULL, 0, WriterThreadFun, NULL, 0, NULL);
//    handle[1] = (HANDLE)_beginthreadex(NULL, 0, ReaderThreadFun, NULL, 0, NULL);
//    WaitForMultipleObjects(2, handle, TRUE, INFINITE);
//
//    for (int k = 0; k < 2; k++)
//    {
//        CloseHandle(handle[k]);
//    }
//    CloseHandle(hReadDataNum);
//    CloseHandle(hEmptyNum);
//    DeleteCriticalSection(&cs);
//
//    getchar();
//    return 0;
//}
//
///*
//    1.当队列空时，读取数据线程要等待队列中有数据.
//
//    2.当队列满时，写入数据线程要等待队列中有空位.
//
//    访问队列时，需要互斥吗？这将依赖于队列的数据结构实现，如果使用STL中的vector，由于vector会动态增长。因此要做互斥保护。            -> 对一个数据资源进行操作
//    如果使用循环队列，那么读取数据线程拥有读取指针，写入数据线程拥有写入指针，各自将访问队列中不同位置上的数据，因此不用进行互斥保护    -> 对多个数据资源进行操作
//*/