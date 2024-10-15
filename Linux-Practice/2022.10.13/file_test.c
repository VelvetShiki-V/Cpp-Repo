#include<stdio.h>
#include<string.h>
#define NUM 128

int main(int argc, char* argv[]) {
    //FILE* fp = fopen("test1.txt", "w");
    //FILE* fp = fopen("test1.txt", "r");
    if(argc != 2) {
        printf("必须带一个参数!\n");
        return 0;
    }
    FILE* fp = fopen(argv[1], "r");
    if(fp == NULL) {
        perror("txt open");
        return 1;
    }
    // 进行文件操作
    char arr[NUM];
    while(fgets(arr, sizeof(arr), fp) != NULL) {
        fprintf(stdout, "%s", arr);
    }
    //const char* p1 = "hello fwrite\n";
    //const char* p2 = "hello fprintf\n";
    //const char* p3 = "hello fputs\n";
    //char c = 'k';
    //fwrite(p1, strlen(p1), 1, fp);
    //fprintf(fp, "%s", p2);
    //fputs(p3, fp);
    //fputc(c, fp);
    fclose(fp);
    return 0;
}
