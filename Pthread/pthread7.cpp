//#include <stdio.h>
//#include <windows.h>
//#include <process.h>
//#include <tchar.h>
//
//using namespace std;

/////该文件与pthread7_1.cpp对应，到时候分别在两个工程中打开两个运行窗口(两个进程)，以此来验证事件的"丢弃"问题.   https://blog.csdn.net/MoreWindows/article/details/7823572
////（先运行此文件，在运行pthread7_1.cpp）
//int main()
//{
//    HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, _T("ProcessA!"));      //参数2：自动置位 参数3：初始状态->未触发状态
//    printf("事件已经创建，现在按a触发事件，按其它键终止进程\n");
//    char ch;
//    scanf("%c", &ch);
//    if ('a' == ch)
//    {
//        exit(0);
//    }
//    SetEvent(hEvent);          //设置为正在调用状态，其他进程等待
//
//    CloseHandle(hEvent);
//
//    //getchar();
//    return 0;
//}
