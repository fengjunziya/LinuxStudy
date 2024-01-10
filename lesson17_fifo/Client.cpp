#include "fifo.hpp"
#include "Log.hpp"
int main()
{
    // 1.打开命名管道文件
    // Client端进行读
    int fd = open(PATH_NAME, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(2);
    }
    char buffer[1024];
    Log(Debug) << "Client: open named_pipe success!  Step1" << std::endl;
    // sleep(5);
    //  开始进行读
    while (1)
    {
        memset(buffer, '\0', sizeof(buffer));
        int n = read(fd, buffer, sizeof(buffer) - 1);
        if (n == 0)
        {
            // 读到了文件末尾
            Log(Debug) << "Read done!" << std::endl;
            break;
        }
        else if (n > 0)
        {
            std::cout << "Server say: " << buffer << std::endl;
        }
    }

    close(fd);
    unlink(PATH_NAME);
    Log(Debug) << "Client: close named_pipe success!  Step2" << std::endl;
    Log(Debug) << "Client: close fd done!   Step3" << std::endl;
    return 0;
}