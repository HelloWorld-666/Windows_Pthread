//#include <stdio.h>
//#include <iostream>
//#include <windows.h>
//#include <tchar.h>
//#include <fstream>
//#include <string>
//#include <tchar.h>
//
//using namespace std;
//
////互斥量进行线程同步
//HANDLE hMutex = NULL;
//
//DWORD WINAPI Fun(LPVOID lpParament)
//{
//    for (int i = 0; i < 10; i++)
//    {
//        WaitForSingleObject(hMutex, INFINITE);
//        cout << "A Thread Fun Display!" << endl;
//        ReleaseMutex(hMutex);
//        //Sleep(200);     //Sleep要放在循环内部
//    }
//
//    return 0L;
//}
//
//int main()
//{
//    HANDLE handle1 = CreateThread(NULL, NULL, Fun, NULL, NULL, NULL);
//    CloseHandle(handle1);                                               //Close并不是真正的结束掉线程，而是将内核的引用计数减1，减到0时才会被OS回收
//
//    hMutex = CreateMutex(NULL, FALSE, _T("MainThread"));
//    for(int i = 0; i < 10; i++)
//    {
//        WaitForSingleObject(hMutex, INFINITE);                          //请求一个互斥量锁  INFINITE：无限等待
//        cout << "Main Thread Fun Display!" << endl;
//        ReleaseMutex(hMutex);                                           //释放互斥量锁
//        //Sleep(200);     //Sleep要放在循环内部
//    }
//
//    getchar();
//    return 0;
//}
//
//
///*
//    只允许一个线程拥有对共享资源的独占，这里我们用互斥量(Mutex)来进行线程同步。
//    https://www.cnblogs.com/codingmengmeng/p/5913068.html
//*/