#include "comm.hpp"
#include <sys/wait.h>

static void getMessage(int fd)
{
    char buffer[SIZE];
    while (true)
    {
        memset(buffer, '\0', sizeof(buffer));
        ssize_t s = read(fd, buffer, sizeof(buffer) - 1);
        if (s > 0)
        {
            cout <<"["  << getpid() << "] "<< "client say> " << buffer << endl;
        }
        else if (s == 0)
        {
            // end of file
            cerr <<"["  << getpid() << "] " << "read end of file, clien quit, server quit too!" << endl;
            break;
        }
        else
        {
            // read error
            perror("read");
            break;
        }
    }
}

int main()
{
    // 1. 创建管道文件
    if (mkfifo(ipcPath.c_str(), MODE) < 0)
    {
        perror("mkfifo");
        exit(1);
    }

    Log("创建管道文件成功", Debug) << " step 1" << endl;

    // 2. 正常的文件操作
    int fd = open(ipcPath.c_str(), O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        exit(2);
    }
    Log("打开管道文件成功", Debug) << " step 2" << endl;

    int nums = 3;
    for (int i = 0; i < nums; i++)
    {
        pid_t id = fork();
        if (id == 0)
        {
            // 3. 编写正常的通信代码了
            getMessage(fd);
            exit(1);
        }
    }
    for(int i = 0; i < nums; i++)
    {
        waitpid(-1, nullptr, 0);
    }
    // 4. 关闭文件
    close(fd);
    Log("关闭管道文件成功", Debug) << " step 3" << endl;

    unlink(ipcPath.c_str()); // 通信完毕，就删除文件
    Log("删除管道文件成功", Debug) << " step 4" << endl;

    return 0;
}