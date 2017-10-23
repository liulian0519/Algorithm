#include<stdio.h>
#include<stdlib.h> 
#include <string.h>
#include <iostream>
using namespace std;

static char reserveWord[32][20] = {
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};
//界符运算符表
static char operatorOrDelimiter[36][10] = {
    "+", "-", "*", "/", "<", "<=", ">", ">=", "=", "==",
    "!=", ";", "(", ")", "^", ",", "\"", "\'", "#", "&",
    "&&", "|", "||", "%", "~", "<<", ">>", "[", "]", "{",
    "}", "\\", ".", "\?", ":", "!"
};

static  char IDentifierTbl[1000][50] = {""};//标识符表


/*查找保留字*/
int searchReserve(char reserveWord[][20], char s[])
{
    for (int i = 0; i < 32; i++)
    {
    	//strcmp函数  若str1==str2相等，则返回 0 若str1<str2，则返回负数 
        if (strcmp(reserveWord[i], s) == 0)
        {//若成功查找，则返回种别码
            return i + 1;//返回种别码
        }
    }
    return -1;//否则返回-1，代表查找不成功，即为标识符
}

/*判断是否为字母*/
bool IsLetter(char letter)
{//下划线
    if (letter >= 'a'&&letter <= 'z' || letter >= 'A'&&letter <= 'Z'|| letter=='_')
    {
        return true;
    }
    else
    {
        return false;
    }
}
/*判断是否为数字*/
bool IsDigit(char digit)
{
    if (digit >= '0'&&digit <= '9')
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*编译预处理，取出无用的字符和注释*/
void filterResource(char r[], int pProject)
{
    char tempString[10000];
    int count = 0;
    for (int i = 0; i <= pProject; i++)
    {
        if (r[i] == '/'&&r[i + 1] == '/')
        {//若为单行注释“//”,则去除注释后面的东西，直至遇到回车换行
            while (r[i] != '\n')
            {
                i++;//向后扫描
            }
        }
        if (r[i] == '/'&&r[i + 1] == '*')
        {//若为多行注释“/* 。。。*/”则去除该内容
            i += 2;
            while (r[i] != '*' || r[i + 1] != '/')
            {
                i++;//继续扫描
                if (r[i] == '$')
                {
                    printf("注释出错，没有找到 */，程序结束！！！\n");
                    exit(0);
                }
            }
            i += 2;//跨过“*/”
        }
        if (r[i] != '\n'&&r[i] != '\t'&&r[i] != '\v'&&r[i] != '\r')
        {//若出现无用字符，则过滤；否则加载
            tempString[count++] = r[i];
        }
    }
    tempString[count] = '\0';
    strcpy(r, tempString);//产生过滤之后的源程序
}

void Scanner(int &syn, char resourceProject[], char token[], int &pProject)
{
    int i, count = 0;//count用来做token[]的指示器，收集有用字符
    char ch;//作为判断使用
    ch = resourceProject[pProject];
    while (ch == ' ')
    {//过滤空格，防止程序因识别不了空格而结束
        pProject++;
        ch = resourceProject[pProject];
    }
    for (i = 0; i<20; i++)
    {//每次收集前先清零
        token[i] = '\0';
    }
    if (IsLetter(resourceProject[pProject]))
    {//开头为字母
        token[count++] = resourceProject[pProject];//收集
        pProject++;//下移
        while (IsLetter(resourceProject[pProject]) || IsDigit(resourceProject[pProject]))
        {//后跟字母或数字
            token[count++] = resourceProject[pProject];//收集
            pProject++;//下移
        }//多读了一个字符既是下次将要开始的指针位置
        token[count] = '\0';
        syn = searchReserve(reserveWord, token);//查表找到种别码
        if (syn == -1)
        {//若不是保留字则是标识符
            syn = 100;//标识符种别码
        }
        return;
    }
    else if (IsDigit(resourceProject[pProject]))
    {//首字符为数字
        while (IsDigit(resourceProject[pProject]))
        {//后跟数字
            token[count++] = resourceProject[pProject];//收集
            pProject++;
        }//多读了一个字符既是下次将要开始的指针位置
        token[count] = '\0';
        syn = 99;//常数种别码
    }
    else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ';' || ch == '(' || ch == ')' || ch == '^'
        || ch == ',' || ch == '\"' || ch == '\'' || ch == '~' || ch == '#' || ch == '%' || ch == '['
        || ch == ']' || ch == '{' || ch == '}' || ch == '\\' || ch == '.' || ch == '\?' || ch == ':')
    {//若为运算符或者界符，查表得到结果
        token[0] = resourceProject[pProject];
        token[1] = '\0';//形成单字符串
        for (i = 0; i<36; i++)
        {//查运算符界符表
            if (strcmp(token, operatorOrDelimiter[i]) == 0)
            {
                syn = 33 + i;//获得种别码
                break;//查到即推出
            }
        }
        pProject++;//指针下移，为下一扫描做准备
        return;
    }
    else  if (resourceProject[pProject] == '<')
    {//<,<=,<<
        pProject++;//后移，超前搜索
        if (resourceProject[pProject] == '=')
        {
            syn = 38;
        }
        else if (resourceProject[pProject] == '<')
        {//左移
            pProject--;
            syn = 58;
        }
        else
        {
            pProject--;
            syn = 37;
        }
        pProject++;//指针下移
        return;
    }
    else  if (resourceProject[pProject] == '>')
    {//>,>=,>>
        pProject++;
        if (resourceProject[pProject] == '=')
        {
            syn = 40;
        }
        else if (resourceProject[pProject] == '>')
        {
            syn = 59;
        }
        else
        {
            pProject--;
            syn = 39;
        }
        pProject++;
        return;
    }
    else  if (resourceProject[pProject] == '=')
    {//=.==
        pProject++;
        if (resourceProject[pProject] == '=')
        {
            syn = 42;
        }
        else
        {
            pProject--;
            syn = 41;
        }
        pProject++;
        return;
    }
    else  if (resourceProject[pProject] == '!')
    {//!,!=
        pProject++;
        if (resourceProject[pProject] == '=')
        {
            syn = 43;
        }
        else
        {
            syn = 68;
            pProject--;
        }
        pProject++;
        return;
    }
    else  if (resourceProject[pProject] == '&')
    {//&,&&
        pProject++;
        if (resourceProject[pProject] == '&')
        {
            syn = 53;
        }
        else
        {
            pProject--;
            syn = 52;
        }
        pProject++;
        return;
    }
    else  if (resourceProject[pProject] == '|')
    {//|,||
        pProject++;
        if (resourceProject[pProject] == '|')
        {
            syn = 55;
        }
        else
        {
            pProject--;
            syn = 54;
        }
        pProject++;
        return;
    }
    else  if (resourceProject[pProject] == '$')
    {//结束符
        syn = 0;//种别码为0
    }
    else
    {//不能被以上词法分析识别，则出错。
        printf("error：there is no exist %c \n", ch);
        exit(0);
    }
}


int main()
{
    //打开一个文件，读取其中的源程序
    char resourceProject[10000];
    char token[20] = { 0 };
    int syn = -1, i;//初始化
    int pProject = 0;//源程序指针
    FILE *fp, *fp1;
    if ((fp = fopen("E:\\test.txt", "r")) == NULL)
    {//打开源程序
       printf("can't open this file");
        exit(0);
    }
    resourceProject[pProject] = fgetc(fp);
    while (resourceProject[pProject] != '$')
    {//将源程序读入resourceProject[]数组
        pProject++;
        resourceProject[pProject] = fgetc(fp);
    }
    resourceProject[++pProject] = '\0';
    fclose(fp);
    printf("源程序为\n："); 
  	printf(resourceProject) ;

    //对源程序进行过滤
    filterResource(resourceProject, pProject);
    printf("\n过滤后：\n");
    printf(resourceProject) ;
    pProject = 0;//从头开始读

    if ((fp1 = fopen("E:\\textResult.txt", "w+")) == NULL)
    {//打开源程序
    	printf("can't open this file");
        exit(0);
    }
    while (syn != 0)
    {
        //启动扫描
        Scanner(syn, resourceProject, token, pProject);
        if (syn == 100)
        {//标识符
            for (i = 0; i<1000; i++)
            {//插入标识符表中
                if (strcmp(IDentifierTbl[i], token) == 0)
                {//已在表中
                    break;
                }
                if (strcmp(IDentifierTbl[i], "") == 0)
                {//查找空间
                    strcpy(IDentifierTbl[i], token);
                    break;
                }
            }
            printf("(标识符  ,%s)\n", token);
            fprintf(fp1, "(标识符   ,%s)\n", token);
        }
        else if (syn >= 1 && syn <= 32)
        {//保留字
            printf("(%s   ,  --)\n", reserveWord[syn - 1]);
            fprintf(fp1, "(%s   ,  --)\n", reserveWord[syn - 1]);
        }
        else if (syn == 99)
        {//const 常数
            printf("(常数   ,   %s)\n", token);
            fprintf(fp1, "(常数   ,   %s)\n", token);
        }
        else if (syn >= 33 && syn <= 68)
        {
            printf("(%s   ,   --)\n", operatorOrDelimiter[syn - 33]);
            fprintf(fp1, "(%s   ,  --)\n", operatorOrDelimiter[syn - 33]);
        }
    }
//    while(IDentifierTbl[i]!=""){
//    	
//    	printf("第%d个标识符：  %s\n", i + 1, IDentifierTbl[i]);
//        fprintf(fp1, "第%d个标识符：  %s\n", i + 1, IDentifierTbl[i]);
//    } 
//    for (i = 0; i<100; i++)
//    {//插入标识符表中
//        printf("第%d个标识符：  %s\n", i + 1, IDentifierTbl[i]);
//        fprintf(fp1, "第%d个标识符：  %s\n", i + 1, IDentifierTbl[i]);
//    }
    fclose(fp1);
    return 0;
}
