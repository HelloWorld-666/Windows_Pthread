//#include <stdio.h>
//#include <windows.h>
//#include <process.h>
//#include <tchar.h>
//
//using namespace std;

////该文件与pthread7.cpp对应，分别在两个工程中打开两个运行窗口(两个进程)，以此来验证事件的"丢弃"问题.   https://blog.csdn.net/MoreWindows/article/details/7823572

//int main()
//{
//    HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, TRUE, _T("ProcessA!"));      //参数2：自动置位 参数3：初始状态->未触发状态
//    if (NULL == hEvent)
//    {
//        printf("打开事件失败！\n");
//    }
//    
//    DWORD iResult = WaitForSingleObject(hEvent, 10 * 1000);
//    switch (iResult)
//    {
//    case WAIT_ABANDONED:
//        printf("拥有事件的进程意外终止.\n");
//        break;
//    case WAIT_OBJECT_0:
//        printf("接收到信号.\n");
//        break;
//    case WAIT_TIMEOUT:
//        printf("未在规定时间内接收到信号.\n");
//        break;
//    default:
//        break;
//    }
//
//    CloseHandle(hEvent);
//
//    //getchar();
//    return 0;
//}
