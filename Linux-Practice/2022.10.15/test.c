#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

// dup输出重定向测试
//int main(int argc, char* argv[]) {
//    if(argc != 2) {
//        printf("必须带一个参数\n");
//        return 2;
//    }
//    int fd = open("out.txt", O_WRONLY|O_TRUNC|O_CREAT, 0666);
//    if(fd < 0) {
//        perror("output");
//        return 1;
//    }
//    printf("文件打开成功，stdout输出fd：%d\n", fd);
//    dup2(fd, 1);    // 重定向stdout
//    fprintf(stdout, "stdout中输出重定向内容如下\n");
//    write(1, argv[1], strlen(argv[1]));
//    printf("\n");
//    return 0;
//}


int main() {
    close(1);
    int fd = open("out.txt", O_WRONLY | O_TRUNC | O_CREAT);
    if(fd < 0) {
        perror("out open");
        return 1;
    }
    printf("打开的fd文件为：%d\n", fd);
    char p[128] = "this is output test!\n";
    fprintf(stdout, "%s", p);
    fflush(stdout);
    close(fd);
    return 0;
}

//int main() {
//    close(0);
//    int fd = open("log.txt", O_RDONLY);
//    if(fd < 0) {
//        perror("log open");
//        return 1;
//    }
//    char buf[128];
//    fgets(buf, sizeof buf, stdin);
//    printf("%s\n", buf);
//    close(fd);
//    return 0;
//}
