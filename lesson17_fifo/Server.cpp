#include "fifo.hpp"
#include "Log.hpp"

int main()
{
    // 1.申请命名管道
    int ret = mkfifo(PATH_NAME, 0666);
    if (ret == -1)
    {
        perror("mkfifo");
        exit(1);
    }
    int a = 0;
    Log(Debug) << "Server: make named_pipe success!  Step1" << std::endl;

    // 2.打开命名管道文件
    // Server端进行写操作
    int fd = open(PATH_NAME, O_WRONLY);
    if (fd == -1)
    {
        perror("open");
        exit(2);
    }
    Log(Debug) << "Server: open named_pipe success!   Step2" << std::endl;

    // 3.开始写
    std::string buffer;
    while (1)
    {
        std::cout << "Please Enter Message Line ,End enter 'end' :> ";
        std::getline(std::cin, buffer);
        if(buffer == END_STR) break;
        write(fd, buffer.c_str(), buffer.size());
    }

    //.关闭命名管道
    close(fd);
    Log(Debug) << "Server: close fc done!   Step3" << std::endl;
    return 0;
}