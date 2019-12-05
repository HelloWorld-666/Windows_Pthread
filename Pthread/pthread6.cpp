//#include <stdio.h>
//#include <windows.h>
//#include <process.h>
//#include <time.h>
//#include <fstream>  //ofstream
//
//using namespace std;
//
///*
//    第一题 放水果 南京大学计算机考研真题:https://blog.csdn.net/morewindows/article/details/7650470
//
//    桌上有一空盘，允许存放一只水果。爸爸可向盘中放苹果，也可向盘中放桔子，儿子专等吃盘中的桔子，女儿专等吃盘中的
//    苹果。规定当盘空时一次只能放一只水果供吃者取用，请用P、V原语实现爸爸、儿子、女儿三个并发进程的同步。
//
//    ofstream和ifstream详细用法：https://blog.csdn.net/augusdi/article/details/8865378
//*/
//
////HANDLE hEmptyDish, hApple, hOrange;
////CRITICAL_SECTION cs;
////
//////write data2 .txt
////void Data2Txt(char* pM)
////{
////    ofstream examplefile_write("example.txt", ios::app);            //ios::app  在文件末尾追加
////    if (examplefile_write.is_open())
////    {
////        examplefile_write << pM;
////        //examplefile_write.close();
////        examplefile_write.clear();
////    }
////}
////
////char* str = NULL;
////unsigned int __stdcall DishThread(PVOID pM)
////{
////    srand((unsigned)time(NULL));                    //不可漏
////
////    while (1)
////    {
////        WaitForSingleObject(hEmptyDish, INFINITE);      //p
////
////        if (rand() % 2 == 0)
////        {
////            ReleaseSemaphore(hOrange, 1, NULL);         //v
////            EnterCriticalSection(&cs);
////            str = "放橘子\n";
////            printf("%s", str);
////            Data2Txt(str);
////            LeaveCriticalSection(&cs);
////        }
////        else
////        {
////            ReleaseSemaphore(hApple, 1, NULL);          //v
////            EnterCriticalSection(&cs);
////            str = "放苹果\n";
////            printf("%s", str);
////            Data2Txt(str);
////            LeaveCriticalSection(&cs);
////        }
////        Sleep(1000);
////    }
////
////    return 0;
////}
////
////unsigned int __stdcall AppleThread(PVOID pM)
////{
////    while (1)
////    {
////        WaitForSingleObject(hApple, INFINITE);          //p
////        EnterCriticalSection(&cs);
////        str = "取苹果\n";
////        printf("%s", str);
////        Data2Txt(str);
////        //Sleep(rand() % 100);
////        LeaveCriticalSection(&cs);
////        ReleaseSemaphore(hEmptyDish, 1, NULL);          //v
////        Sleep(1000);
////    }
////
////    return 0;
////}
////
////unsigned int __stdcall OrangeThread(PVOID pM)
////{
////    while (1)
////    {
////        WaitForSingleObject(hOrange, INFINITE);         //p
////        EnterCriticalSection(&cs);
////        str = "取橘子\n";
////        printf("%s", str);
////        Data2Txt(str);
////        LeaveCriticalSection(&cs);
////        //Sleep(rand() % 100);
////        ReleaseSemaphore(hEmptyDish, 1, NULL);          //v
////        Sleep(1000);
////    }
////
////    return 0;
////}
////
////int main()
////{   
////    hEmptyDish = CreateSemaphore(NULL, 1, 1, NULL);
////    hApple     = CreateSemaphore(NULL, 0, 1, NULL);
////    hOrange    = CreateSemaphore(NULL, 0, 1, NULL);
////
////    InitializeCriticalSection(&cs);
////
////    HANDLE handle[3];
////    handle[0] = (HANDLE)_beginthreadex(NULL, 0, DishThread, NULL, 0, NULL);
////    handle[1] = (HANDLE)_beginthreadex(NULL, 0, AppleThread, NULL, 0, NULL);
////    handle[2] = (HANDLE)_beginthreadex(NULL, 0, OrangeThread, NULL, 0, NULL);
////    WaitForMultipleObjects(3, handle, TRUE, INFINITE);
////
////    for (int i = 0; i < 3; i++)
////    {
////        CloseHandle(handle[i]);
////    }
////    DeleteCriticalSection(&cs);
////
////    getchar();
////    return 0;
////}
//
/////*
////    第一．爸爸要等待盘子为空。
////
////    第二．儿子要等待盘中水果是桔子。
////
////    第三．女儿要等待盘中水果是苹果。
////*/
//
//
//
//
//
//
//
///*
//    在南开大学和天津大学之间有一条弯曲的小路,其中从S到T一段路每次只允许一辆自行通过,但中间有一个小的“安全岛”M(同时允许两辆自行车停留),
//    可供两辆自行车已从两端进小路情况下错车使用,如图所示。试设计一个算法使来往的自行车均可顺利通过.
//    https://wenku.baidu.com/view/f38d0e1f964bcf84b9d57bcd.html
//
//
//    首先中间的安全岛M仅允许两辆自行车通过，应作为临界资源设置信号量。但仔细分析发现，在任何时刻进入小路的自行车最多不会超过两辆（南开和天大方向各一辆），
//    因此不需为安全岛M设置信号量。在路口S处，南开出发的若干辆自行车应进行路口资源的争夺，以决定谁先进入小路SK段，为此设置信号量S，用以控制路口资源的争夺；
//    同理，设置信号量T，控制天大方向自行车对路口T的争夺。又小路SK段仅允许一辆车通过，设置信号量SK初值为1，同理设置小路LT段信号量LT初值为1。
//
//    1进程进入安全岛M后，释放了路段K，但没有释放路口N，原因在于它是向对面的2进程释放路段资源K，而在1进程离开小路L后，才会将路口N释放给其他1进程，
//    如不这样，就会死锁。请考虑如下情况：两个方向各有一辆车前进，若在1进程到达安全岛M后，执行V(N)及V(K)操作，则有可能使得同方向的其它1进程得到路段K的
//    使用权，而进入小路；同理，Q进程到达安全岛后执行V(L)及V(T)操作，有可能使得同方向的其它2进程得到路段L而进入小路。此时共有四辆车在整个路径中，
//    最终出现死锁状态。
//
//                      ————————————————
//                      |                 2.
//                      |    L           T路口
//                      |       _______
//    ——————————————————|       |  
//    |                         |
//    |                 M安全岛  |  
//    |   k   ——————————————————|
//    |       |
//    |       |  
//————|       |
//  1.  N路口
//
//*/
////只有当NT的车完全离开整个路段后，才能释放N端的路口；反之同理。
//CRITICAL_SECTION cs;
//HANDLE hN, hT;  //N、T路口
//HANDLE hK, hL;  //K、L小路
//HANDLE hNT, hTN;
//
////NT方向：
//unsigned int __stdcall NTThread(PVOID pM)
//{
//    //先争夺权限
//    WaitForSingleObject(hN, INFINITE);  //等待 N路口可进入 
//    WaitForSingleObject(hK, INFINITE);  //等待 K小路可通行
//    //NM段
//    EnterCriticalSection(&cs);
//    printf("NM\n");
//    LeaveCriticalSection(&cs);
//    /*到达M安全岛*/
//    ReleaseSemaphore(hK, 1, NULL);      //小车完全通过整个NM路段 -> 释放K小路
//    //MT段
//    WaitForSingleObject(hL, INFINITE);  //同对面车辆争夺L小路使用权
//    EnterCriticalSection(&cs);
//    printf("MT\n");
//    LeaveCriticalSection(&cs);
//    ReleaseSemaphore(hL, 1, NULL);      //小车完全通过整个MT路段 -> 释放L小路
//    ReleaseSemaphore(hN, 1, NULL);      //小车完全通过整个NT路段 -> 释放N路口
//
//    return 0;
//}
//
////TN方向：
//unsigned int __stdcall TNThread(PVOID pM)
//{
//    WaitForSingleObject(hT, INFINITE);  //等待 T路口可进入 
//    WaitForSingleObject(hL, INFINITE);  //等待 L小路可通行
//    //TM段
//    EnterCriticalSection(&cs);
//    printf("TM\n");
//    LeaveCriticalSection(&cs);    
//    /*到达M安全岛*/      
//    ReleaseSemaphore(hL, 1, NULL);      //小车完全通过整个TM路段 -> 释放L小路
//    //MN段：
//    WaitForSingleObject(hK, INFINITE);  //同对面车辆争夺K小路使用权
//    EnterCriticalSection(&cs);
//    printf("MN\n");
//    LeaveCriticalSection(&cs);
//    ReleaseSemaphore(hK, 1, NULL);      //小车完全通过整个MT路段 -> 释放K小路
//    ReleaseSemaphore(hT, 1, NULL);      //小车完全通过整个TN路段 -> 释放T路口
//
//    return 0;
//}
//
//int main()
//{
//    InitializeCriticalSection(&cs);
//
//    hN = CreateSemaphore(NULL, 1, 1, NULL);     //设置初值为1
//    hT = CreateSemaphore(NULL, 1, 1, NULL);
//    hK = CreateSemaphore(NULL, 1, 1, NULL);
//    hL = CreateSemaphore(NULL, 1, 1, NULL);
//
//    HANDLE handle[2];
//    handle[0] = (HANDLE)_beginthreadex(NULL, 0, TNThread, NULL, 0, NULL);
//    handle[1] = (HANDLE)_beginthreadex(NULL, 0, NTThread, NULL, 0, NULL);
//    WaitForMultipleObjects(2, handle, TRUE, INFINITE);
//
//    for (int i = 0; i < 2; i++)
//    {
//        CloseHandle(handle[i]);
//    }
//    DeleteCriticalSection(&cs);
//
//    getchar();
//    return 0;
//}
