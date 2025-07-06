//1.huodonganpai

#include <stdio.h>
#include <stdlib.h>
#include <minmax.h>

// 比较函数，按结束时间升序排序(按右边界排序)
int compare(const void *a, const void *b) {
//    按左边界排序（0是左边界，1是右边界）
    return ((int *)a)[0] - ((int *)b)[0];
}

int main() {
    int T;  //用于存储测试用例的个数
    scanf("%d", &T);//输入测试用例个数
    int t;   //用于循环计数，表示当前处理的测试用例编号
    for (t = 1; t <= T; t++) {
        int n;   //用于存储当前测试用例中活动的数量
        scanf("%d", &n);//输入活动个数n
        int nums[1005][2];//定义一个数组，最多存储1005个活动的信息
        int i;  //用于循环计数，表示当前处理的活动编号
        for (i = 0; i < n; i++) {
            //输出活动的开始时间和结束时间
            scanf("%d %d", &nums[i][0], &nums[i][1]);
        }
        if (n == 0) {
            //如果活动个数为0，输出当前测试用例结果为0
            printf("Case %d: 0\n", t);
            continue;   //跳过后续逻辑，直接处理下一个测试用例
        }
        //左边界排序（开始时间）
        qsort(nums, n, sizeof (int *), compare);
        int count = 0;  //初始化计数器，表示重叠的区间的数量
        for (i = 1; i < n; i++) {
            //遍历剩余的活动，判断当前活动开始时间是否大于等于上一个活动的结束时间
            if (nums[i][0] < nums[i-1][1]) {
                count++;  //增加计数器，表示可以完成更多的活动
                nums[i][1] = min(nums[i][1], nums[i-1][1]);  //将当前活动的右边界取（本活动右边界和上一活动右边界）的较小值
            }
        }
        printf("Case %d: %d\n", t, n - count);  //输出当前测试用例的结果
    }
    return 0;
}


//2.juzhenliancheng

#include <stdio.h>
#define MAX_N 601
#define INF 100000000

int p[MAX_N];         // 全局变量：存储矩阵维度：p[0]=A1行, p[1]=A1列/A2行, p[2]=A2列/A3行, ..., p[n]=An列
int dp[MAX_N][MAX_N]; // dp[i][j] = 计算 Ai..Aj 的最小乘法次数
int s[MAX_N][MAX_N];  // s[i][j] = Ai..Aj 的最优划分位置

int main() {
    int T;
    scanf("%d", &T);//输入测试用例个数

    while (T--) {
        int n;  //矩阵个数
        scanf("%d", &n);//输入矩阵个数

        // 读取矩阵维度 (第一个矩阵需要行和列)
        scanf("%d %d", &p[0], &p[1]);

        // 读取后续矩阵 (只需要列，因为行等于前一个矩阵的列)
        for (int i = 1; i < n; i++) {
            int x, y;//定义矩阵的行和列
            scanf("%d %d", &x, &y);//输入第二个矩阵开始的行和列
            p[i + 1] = y;  // 保存当前矩阵的列
        }

        // 初始化：单个矩阵乘法次数为0
        for (int i = 1; i <= n; i++) {
            dp[i][i] = 0; //单个矩阵的最小连乘次数为0
            s[i][i] = i;  // 单个矩阵的最优划分位置是自身
        }

        // 动态规划：按区间长度从小到大计算
        for (int len = 2; len <= n; len++) {  // 区间长度从2到n
            for (int i = 1; i <= n - len + 1; i++) {  // 区间起始点
                int j = i + len - 1;  // 区间结束点
                dp[i][j] = INF;  // dp数组初始化为无穷大

                // 四边形不等式优化：确定k的搜索范围
                int k0 = s[i][j - 1];    // 左边界
                int k1 = s[i + 1][j];    // 右边界：左边界+1
                if (len == 2) {          // 特判：两个矩阵的情况
                    k0 = i;  //左边界
                    k1 = i;  //右边界
                }

                // 在优化范围内搜索最优划分点k
                for (int k = k0; k <= k1 && k < j; k++) {
                    // 计算划分点k处的乘法次数
                    int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];

                    // 更新最优解
                    if (cost < dp[i][j]) {
                        dp[i][j] = cost;  //记录i,j最小乘连乘次数
                        s[i][j] = k;  // 记录最优划分位置
                    }
                }
            }
        }
        // 输出A1..An的最小乘法次数（dp[1][n]表示1到n的最佳乘法次数）
        printf("%d\n", dp[1][n]);
    }
    return 0;
}



//3.zuichanggonggongzixulie

#include<stdio.h>
#include<minmax.h>
#include<string.h>

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        char X[1005],Y[1005];
        scanf("%s\n",X);
        scanf("%s",Y);

        //获取字符串长度
        int Xlen = strlen(X);
        int Ylen = strlen(Y);

        //定义dp二维数组
        int dp[Xlen+1][Ylen+1];
        //初始化dp数组
        for(int i = 0; i < Xlen;i++){
            for(int j = 0 ; j < Ylen;j++){
                dp[i][j] = 0;
            }
        }
        for(int i = 1; i <= Xlen;i++){
            for(int j = 1; j <= Ylen;j++){
                if(X[i-1] == Y[j-1]){
                    dp[i][j] = dp[i-1][j-1] + 1;
                }else{
                    dp[i][j] = max(dp[i][j-1],dp[i-1][j]);
                }
            }
        }
        printf("%d\n",dp[Xlen][Ylen]);
    }
    return 0;
}



//4.zhengshuhuafen

#include<stdio.h>
int DividedNum(int n,int m){ //n表示需要划分的整数，m表示最大加数
    if(n==1 ||m==1){ //如果n或m为1，则只有一种划分方法，返回1
        return 1;
    }else if(n == m&& n>1){ //如果 n==m且n>1,最大加数进行递归n-1并+1
        return DividedNum(n,n-1)+1;
    }else if(n < m){  //如果m>n,不存在这种情况，所以令m=n
        return DividedNum(n,n);
    }else if(n > m)  //2种情况:不包含m的情况（m-1）和包含m的情况（m）
        return DividedNum(n,m-1) + DividedNum(n-m,m);
    return 0;
}
int main(){
    int n;
    while(EOF != scanf("%d",&n)){ //使用 while 循环持续读取用户的输入，直到遇到文件结束符 EOF
        printf("%d\n",DividedNum(n,n)); //打印DividedNum(n,n)的值，表示将整数 n 划分为最大加数不超过 n 的方案数
    }
    return 0;
}




//5.da zheng shu cheng fa
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DIGITS 32

void reverseString(char *str) {
    int len = strlen(str);
    int i;
    char temp;
    for (i = 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

char* multiplyStrings(char *num1, char *num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    if (len1 == 0 || len2 == 0 || strcmp(num1, "0") == 0 || strcmp(num2, "0") == 0) {
        char *result = (char *)malloc(2 * sizeof(char));
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    int resultSize = len1 + len2;
    int *result = (int *)calloc(resultSize, sizeof(int));

    int i_n1 = 0;
    int i_n2 = 0;
    int i;
    int j;
    int carry;
    int n1;
    int n2;
    int sum;

    for (i = len1 - 1; i >= 0; i--) {
        carry = 0;
        n1 = num1[i] - '0';
        i_n2 = 0;

        for (j = len2 - 1; j >= 0; j--) {
            n2 = num2[j] - '0';
            sum = n1 * n2 + result[i_n1 + i_n2] + carry;
            carry = sum / 10;
            result[i_n1 + i_n2] = sum % 10;
            i_n2++;
        }

        if (carry > 0) {
            result[i_n1 + i_n2] += carry;
        }
        i_n1++;
    }

    int k = resultSize - 1;
    while (k >= 0 && result[k] == 0) {
        k--;
    }

    if (k == -1) {
        char *finalResult = (char *)malloc(2 * sizeof(char));
        finalResult[0] = '0';
        finalResult[1] = '\0';
        free(result);
        return finalResult;
    }

    char *finalResult = (char *)malloc((k + 2) * sizeof(char));
    int idx = 0;
    while (k >= 0) {
        finalResult[idx++] = result[k--] + '0';
    }
    finalResult[idx] = '\0';

    free(result);
    return finalResult;
}

int main() {
    char num1[MAX_DIGITS + 1];
    char num2[MAX_DIGITS + 1];

    while (scanf("%s %s", num1, num2) == 2) {
        char *result = multiplyStrings(num1, num2);
        printf("%s\n", result);
        free(result);
    }

    return 0;
}



//6.qipanfugai

#include <stdio.h>
#include <math.h>

#define MAX 256
// 全局变量：四种骨牌类型
const char TILE_CHARS[4] = {'a', 'b', 'c', 'd'};
char board[MAX][MAX];
// 棋盘覆盖函数
void ChessBoard(int tr, int tc, int dr, int dc, int size) {
    if (size == 1) {
        return;
    }

    int s = size / 2;

    // 特殊方格在左上象限
    if (dr < tr + s && dc < tc + s) {
        board[tr + s - 1][tc + s] = TILE_CHARS[3];     // 右上
        board[tr + s][tc + s - 1] = TILE_CHARS[3];     // 左下
        board[tr + s][tc + s] = TILE_CHARS[3];         // 右下

        // 递归覆盖四个子棋盘
        ChessBoard(tr, tc, dr, dc, s); // 左上
        ChessBoard(tr, tc + s, tr + s - 1, tc + s, s); // 右上
        ChessBoard(tr + s, tc, tr + s, tc + s - 1, s); // 左下
        ChessBoard(tr + s, tc + s, tr + s, tc + s, s); // 右下
    }
        // 特殊方格在右上象限
    else if (dr < tr + s && dc >= tc + s) {
        board[tr + s - 1][tc + s - 1] = TILE_CHARS[2]; // 左上
        board[tr + s][tc + s - 1] = TILE_CHARS[2];     // 左下
        board[tr + s][tc + s] = TILE_CHARS[2];         // 右下
        // 递归覆盖四个子棋盘

        ChessBoard(tr, tc, tr + s - 1, tc + s - 1, s);
        ChessBoard( tr, tc + s, dr, dc, s);
        ChessBoard( tr + s, tc, tr + s, tc + s - 1, s);
        ChessBoard(tr + s, tc + s, tr + s, tc + s, s);
    }
        // 特殊方格在左下象限
    else if (dr >= tr + s && dc < tc + s) {
        board[tr + s - 1][tc + s - 1] = TILE_CHARS[1]; // 左上
        board[tr + s - 1][tc + s] = TILE_CHARS[1];     // 右上
        board[tr + s][tc + s] = TILE_CHARS[1];         // 右下
        // 递归覆盖四个子棋盘

        ChessBoard(tr, tc, tr + s - 1, tc + s - 1, s);
        ChessBoard(tr, tc + s, tr + s - 1, tc + s, s);
        ChessBoard(tr + s, tc, dr, dc, s);
        ChessBoard(tr + s, tc + s, tr + s, tc + s, s);
    }
        // 特殊方格在右下象限
    else if (dr >= tr + s && dc >= tc + s) {
        board[tr + s - 1][tc + s - 1] = TILE_CHARS[0]; // 左上
        board[tr + s - 1][tc + s] = TILE_CHARS[0];     // 右上
        board[tr + s][tc + s - 1] = TILE_CHARS[0];     // 左下
        // 递归覆盖四个子棋盘

        ChessBoard(tr, tc, tr + s - 1, tc + s - 1, s);
        ChessBoard(tr, tc + s, tr + s - 1, tc + s, s);
        ChessBoard(tr + s, tc, tr + s, tc + s - 1, s);
        ChessBoard(tr + s, tc + s, dr, dc, s);
    }
}

int main() {
    int T;
    scanf("%d", &T);

    while(T--){
        int K, X, Y;
        scanf("%d %d %d", &K, &X, &Y);

        // 计算棋盘大小
        int size = (int)pow(2, K);

        // 动态分配棋盘内存
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                board[i][j] = ' '; // 初始化为空格
            }
            board[i][size] = '\0'; // 每行末尾添加结束符
        }
        // 标记特殊方格位置（行列索引从0开始）
        board[X-1][Y-1] = '*';

        // 使用分治算法覆盖棋盘
        ChessBoard(0, 0, X-1, Y-1, size);

        // 打印棋盘
        for (int i = 0; i < size; i++) {
            printf("%s\n", board[i]);//按行 打印棋盘
        }
    }
    return 0;
}



//7.zuiyouzhuangzai

#include <stdio.h>
#include <stdlib.h>
// 比较函数：用于qsort排序（从小到大）
int compare(const void *a, const void *b) { //因为 void 类型没有大小或数据结构，无法知道如何解引用它
    return (*(int*)a - *(int*)b);  //(int*)a：将 void* 指针 a 转换为 int* 类型，表示它现在指向一个 int 值。
}  //*(int*)a：解引用这个 int* 指针，获取它所指向的实际 int 值。
//必须通过类型转换将 void* 转换为具体的指针类型（如 int*）后，再解引用获取值
//    使用 (*(int*)a - *(int*)b) 可以确保 qsort 正确地根据 int 值进行比较和排序

int main() {
    int T;
    scanf("%d", &T); // 测试样例个数

    for (int t = 1; t <= T; t++) {
        int n, C;
        scanf("%d %d", &n, &C); // 集装箱个数和轮船载重量

        int *BoxWeight = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%d", &BoxWeight[i]); // 读取每个集装箱重量
        }
//        获取所有集装箱重量后进行从小到大排序
        // 按重量从小到大排序（贪心策略关键）
        qsort(BoxWeight, n, sizeof(int), compare);

        int count = 0;      // 装载的集装箱数量
        int currentWt = 0;    // 当前装载的总重量

        for (int i = 0; i < n; i++) {  // 尝试装载每个集装箱
            if (currentWt + BoxWeight[i] <= C) { // 检查装载后是否超重
                currentWt += BoxWeight[i]; // 更新当前重量
                count++;               // 增加计数
            } else {
                break; // 超重则停止装载break
            }
        }
        // 输出结果（注意实际载重量是currentWt而非C）
        printf("Case %d: %d %d\n", t, count, currentWt);

        free(BoxWeight); // 释放内存
    }
    return 0;
}


//8.zhuangzaiwenti

#include<stdio.h>
#define MaxBox 1000 //集装箱最多数量
int BoxWeight[MaxBox]; //某个集装箱的重量
int BoxNum; //集装箱的数量
int C1; //船1的容量
int X[MaxBox];//集装箱的状态（0,1）0表示未装入，1表示装入船
int curC1Wt;//当前装入船1的重量
int restBoxWt; //表示当前剩余的集装箱总重量
int globalMaxWt;//表示在所有可能方案中，第一艘船能承载的最大重量。

void loadingBacktrack(int t){ //参数 t 表示当前处理的集装箱序号
    if(t == BoxNum){ //说明已经处理完所有集装箱，此时更新最大装载量 globalMaxWt 为当前装载量 curC1Wt。
        //同时也是一个边界条件，得到一个船1的更好可行解
        globalMaxWt = curC1Wt;
        return;
    }
    restBoxWt -= BoxWeight[t];//剩余的集装箱重量减去集装箱t的重量(扩展子节点时减少 restBoxWt 的值，表示正在尝试将第 t 个集装箱纳入考虑范围)
    if(curC1Wt + BoxWeight[t] <= C1){//判断当前装载量加上第 t 个集装箱的重量是否超过船的容量，如果不超过，则尝试将其装入船，约束剪枝
        X[t] =1;//表示第 t 个集装箱被装入第一艘船。
        curC1Wt += BoxWeight[t];//更新当前装载量 curC1Wt，增加第 t 个集装箱的重量
        loadingBacktrack(t + 1);//递归调用 loadingBacktrack，处理下一个集装箱
        curC1Wt -= BoxWeight[t]; //回溯时恢复当前装载量 curC1Wt，因为该路径尝试失败或已完成(本路径已经尝试过，所以回溯)
    }
    if(curC1Wt + restBoxWt > globalMaxWt){ //界限剪枝,判断当前装载量加上剩余所有集装箱的重量是否大于目前的最优解 globalMaxWt。
        //如果这个条件成立，说明还有可能找到比当前最优解更好的解，因此继续递归探索；否则，直接剪枝，不再继续探索该分支。
        X[t] = 0;//表示第 t 个集装箱未被装入第一艘船。省了这一步curC1Wt -= BoxWeight[t]
        loadingBacktrack(t + 1);//递归调用 loadingBacktrack，处理下一个集装箱
    }
    restBoxWt += BoxWeight[t]; //回溯时恢复剩余集装箱重量 restBoxWt，因为该路径尝试失败或已完成
}

int main(){
    int T;//测试用例个数
    int C2;//船2容量
    int totalBoxWt;//所有集装箱的总重量
    scanf("%d",&T);
    for(int t = 1; t <= T;t++) {
        scanf("%d", &BoxNum);
        scanf("%d%d", &C1, &C2);
        totalBoxWt = 0;//初始化 totalBoxWt 为 0，用于计算所有集装箱的总重量
        for (int i = 0; i < BoxNum; i++) { //使用 for 循环读取每个集装箱的重量，并累加到 totalBoxWt 中
            scanf("%d", &BoxWeight[i]);
            totalBoxWt += BoxWeight[i];
        }
        restBoxWt = totalBoxWt;//初始化 restBoxWt 为 totalBoxWt，表示尚未考虑的集装箱总重量
        curC1Wt = 0;//当前装入船1的重量赋值为0
        globalMaxWt = 0;//装入船1的最优装载量赋值为0
        loadingBacktrack(0);//调用 loadingBacktrack 函数，从第一个集装箱开始尝试装载（从零开始）
        //判断第二艘船能否容纳剩下的集装箱。如果可以，输出第一艘船的最大装载量；否则输出 "No"。（关键判断）
        if (C2 >= totalBoxWt - globalMaxWt) //当C2容量大于剩余集装箱的重量，集装箱可以装入C2
            printf("Case %d:\n%d\n",t, globalMaxWt); //此时说明船1最大装载量有效
        else
            printf("Case %d:\nNo\n",t);//否则说明船1最大装载量无效
    }
    return 0;
}


//9.n houowenti

#include<stdio.h>

int solutionCount;//定义解决方案个数全局变量（可行方案数）

int isValid(int row,int col,int *placedCol){ //（三个判断：同列，同斜线）
    for(int i = 0;i < row;i++){
        //判断位置是否为同一列
        if(col == placedCol[i])
            return 0;

        //判断位置是否为左上对角线45度(行差 == 列差)
        if((row - i) == (col - placedCol[i])){
            return 0;
        }

        //判断位置是否为右上对角线135度（行差 == 列差的绝对值）
        if((row - i) == ( placedCol[i]) - col){
            return 0;
        }
    }
    return 1;
}


void backtracking(int row,int n,int *placedCol) {

    //如果当前行 == n，则表示找到了一个可行方案，solutionCount++
    if (row == n) {
        solutionCount++;
        return;
    }
    //遍历当前行的所有列
    for (int col = 0; col < n; col++) {
        if (isValid(row, col, placedCol)) {
            placedCol[row] = col;

            //本行放置位置合法，递归下一行
            backtracking(row + 1, n ,placedCol);
        }
    }
}

int totalQueens(int n){
    solutionCount = 0;//初始化可行方案数为零

    int placedCol[n]; //定义放置皇后的列位置数组

    for(int i = 0; i < n;i++)
        placedCol[i] = -1; //初始化皇后列位置数组为-1

    backtracking(0,n,placedCol); //从零开始回溯递归（第一行）

    return solutionCount; //返回本棋盘大小最终可行方案数
}

int main(){
    int T;
    scanf("%d",&T); //输入测试用例个数
    while(T--) {
        int n;//定义棋盘大小
        scanf("%d", &n); //输入棋盘大小
        printf("%d\n", totalQueens(n)); //输出最终可行方案数
    }
    return 0;
}



//10. 01beibao

#include<stdio.h>
#include<stdlib.h>
#include<minmax.h>

//输入的第一行为测试样例的个数T，接下来有T个测试样例。
int main() {

    int T, n, C;
    scanf("%d", &T);//输入测试用例个数
    while(T--) {
        scanf("%d %d", &n, &C);//输入物品个数n和背包容量C

        int *w = (int *)malloc(n * sizeof(int));  //重量 动态分配内存
        int *v = (int *)malloc(n * sizeof(int)); //价值 动态分配内存

        for (int i = 0; i < n; ++i) {
            scanf("%d %d", &w[i], &v[i]);//输入每个物品的重量和价值
        }

        int **dp =(int **)malloc(n * sizeof(int *));  //初始化dp二维数组动态分配内存，记录

        for(int i = 0;i < n; ++i){
            dp[i] = (int *)malloc((C + 1) * sizeof(int));  //物品dp[i]动态分配内存
            for(int j = 0;j <= C;++j){
                dp[i][j] = 0;  //初始化dp二维数组
            }
        }

        for(int j = w[0]; j <= C;j++){
            dp[0][j] = v[0];  //初始化第一个物品，第一行每个容量
        }

        for(int i = 1; i < n; i++){  //先遍历物品（从第二个物品开始），再遍历背包容量
            for(int j = 0; j <= C; j++) {
                if (j < w[i]) {  //其实就是剩余容量小于物品重量时
                    dp[i][j] = dp[i - 1][j];//不放物品i
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);//放物品i
                }
            }
        }
        printf("%d\n",dp[n-1][C]);  //打印dp二维数组（因为遍历时是不包含n但是包含C的）

        free(w);  //释放内存
        free(v);  //释放内存

        for(int i = 0; i < n;++i){
            free(dp[i]);  //释放内存
        }
        free(dp);  //释放内存
    }
    return 0;
}


//11.lvxingshangwenti tsp


#include<stdio.h>
#include<minmax.h>

#define INF 100000000

int cost[18][18];
int dp[1<<18][18];

//取最小值(注意：这里取二者最小值，之前的题目是比较排序compare——从小到大或者从大到小，需要用到内置函数qsort)
//int min(int a, int b){
//    return a > b ? b : a;
//}

int main(){
    int T;
    scanf("%d",&T);//输入测试用例
    for(int t = 1; t <= T;t++){
        int n,m,u,v,w;
        scanf("%d%d",&n,&m);//输入顶点个数和边个数
        for(int i = 0;i < m; i++)
            for(int j = 0;j < n;j++)  //首先初始化cost数组为无穷大，表示从i到j的花费
                cost[i][j] = (i == j) ? 0 :INF;//所有边初始化为无穷大（顶点相等除外，因为自己到自己距离为0）

        for(int i = 0;i < m; i++){
            scanf("%d%d%d",&u,&v,&w);//输入两个顶点和之间的边权重
            v--;//顶点从0开始，所以全部减一
            u--;//顶点从0开始，所以全部减一
            if(cost[u][v] > w)  //如果边权重 小于 两顶点之间的花费
                cost[u][v] = cost[v][u] = w;//将边权重赋值给两顶点之间的花费
        }
        int N = (1<<n);//初始化包含n个状态的N（通过二进制存储）
        for(int s = 0; s < N;s++){ //状态s从0开始遍历
            for(int i = 0; i < n;i++){ //顶点从0开始遍历
                dp[s][i] = INF; //初始化dp数组为无穷大，dp数组表示在状态s下从顶点0出发到顶点i的最小花费
            }
        }
        dp[1][0] = 0; //***要为顶点特别初始化0到0花费为0
        for(int s = 1; s < N;s++) { //状态s从1开始，到N-1结束
            for (int i = 0; i < n; i++) { //顶点从0开始遍历
                if (!(s & (1 << i)))  //如果顶点i没有访问过（s与运算1<<i结果是i的状态，如果未访问顶点i，则跳过顶点i）
                    continue;  //跳过顶点1,访问顶点i的之前的所有顶点j

                for (int j = 0; j < n; j++) { //遍历顶点i的之前的所有顶点j，找出到达i最小花费
                    if (cost[j][i] < INF && i != j && s & (1 << j)) { //j已访问且j不等于i,且j到i有路
                        //比较不同的j到达i的花费，找出最小花费的顶点j
                        dp[s][i] = min(dp[s][i], dp[s ^ (1 << i)][j] + cost[j][i]);//（s^(1<<i)异或运算，不同为1，相同为0）
                        //最终可以获取剔除顶点i之后的顶点j的访问状态
                    }
                }
            }
        }
        int ans = INF; //将最终答案（旅行最小花费）初始化为无穷大
        for(int i = 1; i < n;i++){ //从第二个顶点开始遍历
            if(cost[i][0] < ans){ //如果顶点i回到0的花费小于ans
                ans = min(ans,dp[N-1][i] + cost[i][0]); //比较ans 与 从0到i再从i回到0的花费，取较小值
            }
        }
        printf("Case %d: %d\n",t,ans == INF ? -1 : ans); //打印输出测试用例t下的旅行最小花费
    }
    return 0;
}




//12.erfenchazhao


#include<stdio.h>
#include<stdlib.h>

int binarySearch(int *a,int b,int size){ //定义二分查找函数
    int start = 0;//定义左边界（起始）
    int end = size - 1;//定义右边界（结束）
    while(start <= end){ //当左边界大于右边界时停止循环
        int mid = (start +end) / 2;  //中间值（中点）
        if(b == a[mid]) //等于查找值key时，返回下标
            return mid;
        else if(b < a[mid]) //大于查找值key时，重新定义右边界（结束）
            end = mid - 1;
        else   //小于查找值key时，重新定义左边界（起始）
            start = mid + 1;
    }
    return -1; //没有找到key，返回-1
}

int main(){
    int *a,*b;//定义整数数组，和key数组
    int M,N,index;

    scanf("%d",&M);//输入整数个数
    a = (int *)malloc(M * sizeof(int));//动态分配整数数组
    for(int i = 0; i < M; i++)
        scanf("%d",&a[i]);//输入整数

    scanf("%d",&N);//输入key的个数
    b = (int *)malloc(N * sizeof(int));//动态分配key数组
    for(int i = 0; i < N; i++){
        scanf("%d",&b[i]);//输入key
        index = binarySearch(a,b[i],M);//调用二分查找函数，返回key值下标
        if(index == -1)
            printf("Not Found\n");//打印输出
        else
            printf("%d\n",index);//打印输出下标
    }
    free(a);//释放动态分配内存空间
    free(b);//释放动态分配内存空间
    return 0;
}



//13.duojidiaodu

#include<stdio.h>
#include<stdlib.h>

int compare(const void *a, const void *b){ //比较函数，从大到小进行排序
    return (*(int *)b - *(int *)a);
}

int main(){
    int T;
    scanf("%d",&T);//输入测试用例个数
    for(int t = 1; t <= T;t++){  //测试用例记得加等号！！！
        int n,m;
        scanf("%d %d",&n,&m);//输入作业个数n和机器个数m
        int *jobs = (int *)malloc(n * sizeof(int));//动态分配作业数组jobs
        for(int i = 0; i < n; i++){
            scanf("%d",&jobs[i]);//输入作业加工时间
        }

        if(n <= m){//如果作业个数小于等于机器个数，此时最短加工时间即加工时间最长的作业
            int max_time = 0;//定义最大加工时间
            for(int i = 0; i < n; i++){//获取加工时间最长的作业
                if(max_time < jobs[i]){
                    max_time = jobs[i];//将最长加工时间的作业赋值给max_time
                }
            }
            printf("Case %d: %d",t,max_time);//打印输出结果
            free(jobs);//释放动态分配的内存空间
            continue;//进入下一个测试用例
        }
        //使用内置排序函数qsort将jobs数组整体从大到小排序
        qsort(jobs,n,sizeof(int),compare);
        int *machines = (int *)calloc(m,sizeof(int)); //使用calloc动态分配机器负载数组，自带初始化为0

        for(int i = 0; i < n; i++){ //从零开始遍历 作业
            int min_machine = 0;//定义最小负载的机器变量（数组下标）
            for(int j = 1; j < m ;j++){ //遍历找出最小负载的机器
                if(machines[j] < machines[min_machine]){
                    min_machine = j;//将数组下标赋值给最小负载机器变量
                }  //遍历找出最小负载机器
            }
            machines[min_machine] += jobs[i];//添加当前作业 到 最小负载机器
        }

        int max_load = 0;//定义机器最大负载量
        for(int i = 0; i < m; i++) {  //遍历找出最大负载的机器并打印输出
            if (max_load < machines[i]) {
                max_load = machines[i]; //如果机器负载大于max_load，将机器负载赋值给max_load
            }
        }
        printf("Case %d: %d\n",t,max_load);//打印输出当前测试用例的最大负载，即为加工完所有作业的最短时间
        free(jobs);//释放动态分配的内存空间
        free(machines);//释放动态分配的内存空间
    }
    return 0;
}



















//lianzhang


//����ţ�̰�ģ��� huo dong an pai
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int start;
    int end;
} Activity;

// �ȽϺ�������������
int compare(const void *a, const void *b) {
    Activity *act1 = (Activity *)a;
    Activity *act2 = (Activity *)b;
    return act1->end - act2->end;
}

int main() {
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; t++) {
        int n;
        scanf("%d", &n);

        Activity activities[n];
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &activities[i].start, &activities[i].end);
        }

        // ���ս���ʱ������
        qsort(activities, n, sizeof(Activity), compare);

        int count = 1; // ���ٿ���ѡ���һ���
        int last_end = activities[0].end; // ��һ��ѡ�л�Ľ���ʱ��

        // ѡ�����ݻ
        for (int i = 1; i < n; i++) {
            if (activities[i].start >= last_end) {
                count++;
                last_end = activities[i].end;
            }
        }

        // ������
        printf("Case %d: %d\n", t, count);
    }

    return 0;
}












//�������ˣ�DP����jv zhen lian cheng
#include <stdio.h>
#include <limits.h>

#define MAX_N 600

int dp[MAX_N][MAX_N];
int dimensions[MAX_N + 1];

int min(int a, int b) {
return a < b ? a : b;
}

int matrixChainMultiplication(int n) {
    int i, j, k, L;
    int q;

    for (i = 1; i <= n; i++) {
        dp[i][i] = 0;
    }

    for (L = 2; L <= n; L++) {
        for (i = 1; i <= n - L + 1; i++) {
            j = i + L - 1;
            dp[i][j] = INT_MAX;
            for (k = i; k < j; k++) {
                q = dp[i][k] + dp[k + 1][j] + dimensions[i - 1] * dimensions[k] * dimensions[j];
                if (q < dp[i][j]) {
                    dp[i][j] = q;
                }
            }
        }
    }

    return dp[1][n];
}

int main() {
    int T;
    scanf("%d", &T);
    int t;

    for (t = 0; t < T; t++) {
        int n;
        scanf("%d", &n);

        int i;
        for (i = 0; i < n; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            dimensions[i] = x;
            if (i == n - 1) {
                dimensions[i + 1] = y;
            }
        }

        int result = matrixChainMultiplication(n);
        printf("%d\n", result);
    }

    return 0;
}













//�����������-�����������DP����zui chang gong gong zi xv lie-duo ce shi yong li
#include <stdio.h>
#include <string.h>

#define MAX_LEN 1001

int dp[MAX_LEN][MAX_LEN];

int max(int a, int b) {
return a > b ? a : b;
}

int lcs(char *X, char *Y) {
    int m = strlen(X);
    int n = strlen(Y);
    int i, j;

    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[m][n];
}

int main() {
    int T;
    scanf("%d", &T);
    int t;

    for (t = 0; t < T; t++) {
        char X[MAX_LEN];
        char Y[MAX_LEN];
        scanf("%s", X);
        scanf("%s", Y);

        int result = lcs(X, Y);
        printf("%d\n", result);
    }

    return 0;
}












//�����������⣨���Σ���������������
#include <stdio.h>

int partition(int n, int max)
{
    int i;
    int count;
    if (n == 0)
    {
        return 1;
    }
    if (n < 0 || max == 0)
    {
        return 0;
    }
    count = 0;
    for (i = max; i >= 1; i--)
    {
        count += partition(n - i, i);
    }
    return count;
}

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        int result;
        result = partition(n, n);
        printf("%d\n", result);
    }
    return 0;
}











//�������˷������Σ���da zheng shu cheng fa
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DIGITS 32

void reverseString(char *str) {
    int len = strlen(str);
    int i;
    char temp;
    for (i = 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

char* multiplyStrings(char *num1, char *num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    if (len1 == 0 || len2 == 0 || strcmp(num1, "0") == 0 || strcmp(num2, "0") == 0) {
        char *result = (char *)malloc(2 * sizeof(char));
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    int resultSize = len1 + len2;
    int *result = (int *)calloc(resultSize, sizeof(int));

    int i_n1 = 0;
    int i_n2 = 0;
    int i;
    int j;
    int carry;
    int n1;
    int n2;
    int sum;

    for (i = len1 - 1; i >= 0; i--) {
        carry = 0;
        n1 = num1[i] - '0';
        i_n2 = 0;

        for (j = len2 - 1; j >= 0; j--) {
            n2 = num2[j] - '0';
            sum = n1 * n2 + result[i_n1 + i_n2] + carry;
            carry = sum / 10;
            result[i_n1 + i_n2] = sum % 10;
            i_n2++;
        }

        if (carry > 0) {
            result[i_n1 + i_n2] += carry;
        }
        i_n1++;
    }

    int k = resultSize - 1;
    while (k >= 0 && result[k] == 0) {
        k--;
    }

    if (k == -1) {
        char *finalResult = (char *)malloc(2 * sizeof(char));
        finalResult[0] = '0';
        finalResult[1] = '\0';
        free(result);
        return finalResult;
    }

    char *finalResult = (char *)malloc((k + 2) * sizeof(char));
    int idx = 0;
    while (k >= 0) {
        finalResult[idx++] = result[k--] + '0';
    }
    finalResult[idx] = '\0';

    free(result);
    return finalResult;
}

int main() {
    char num1[MAX_DIGITS + 1];
    char num2[MAX_DIGITS + 1];

    while (scanf("%s %s", num1, num2) == 2) {
        char *result = multiplyStrings(num1, num2);
        printf("%s\n", result);
        free(result);
    }

    return 0;
}
















//���̸��ǣ����Σ���qi pan fu gai
#include <stdio.h>
// ȫ����������
char board[260][260];

// �ݹ麯��ʵ�����̸���
void solveChessBoard(int tr, int tc, int dr, int dc, int size) {
    int s; // �����̱߳���һ�� / half of the sub-board side length
    if (size == 1) {
        return;
    }
    s = size / 2; // �����̷ָ�Ϊ4��������
    // �ж����ⷽ�����ĸ����ޣ����������������޵Ľ��紦����һ��L�͹���
    
    if (dr < tr + s && dc < tc + s) {
        // ���ⷽ�������Ͻ������� (Special square is in the top-left quadrant)
       
        board[tr + s - 1][tc + s]     = 'd'; // ���������̵������ 
        board[tr + s]    [tc + s - 1] = 'd'; // ���������̵������ 
        board[tr + s]    [tc + s]     = 'd'; // ���������̵������ 

        solveChessBoard(tr, tc, dr, dc, s);                              // �ݹ鴦������������ 
        solveChessBoard(tr, tc + s, tr + s - 1, tc + s, s);              // �ݹ鴦������������ 
        solveChessBoard(tr + s, tc, tr + s, tc + s - 1, s);              // �ݹ鴦������������ 
        solveChessBoard(tr + s, tc + s, tr + s, tc + s, s);              // �ݹ鴦������������ 

    } else if (dr < tr + s && dc >= tc + s) {
        // ���ⷽ�������Ͻ������� 
        // �� 'c' �͹����������
        
        board[tr + s - 1][tc + s - 1] = 'c'; // ����
        board[tr + s]    [tc + s - 1] = 'c'; // ����
        board[tr + s]    [tc + s]     = 'c'; // ����

        solveChessBoard(tr, tc + s, dr, dc, s);                          
        solveChessBoard(tr, tc, tr + s - 1, tc + s - 1, s);              
        solveChessBoard(tr + s, tc, tr + s, tc + s - 1, s);              
        solveChessBoard(tr + s, tc + s, tr + s, tc + s, s);              

    } else if (dr >= tr + s && dc < tc + s) {
        // ���ⷽ�������½������� 
        // �� 'b' �͹����������
        
        board[tr + s - 1][tc + s - 1] = 'b'; // ����
        board[tr + s - 1][tc + s]     = 'b'; // ����
        board[tr + s]    [tc + s]     = 'b'; // ����

        solveChessBoard(tr + s, tc, dr, dc, s);                         
        solveChessBoard(tr, tc, tr + s - 1, tc + s - 1, s);             
        solveChessBoard(tr, tc + s, tr + s - 1, tc + s, s);              
        solveChessBoard(tr + s, tc + s, tr + s, tc + s, s);             

    } else { // dr >= tr + s && dc >= tc + s
        // ���ⷽ�������½�������
        // �� 'a' �͹����������
        
        board[tr + s - 1][tc + s - 1] = 'a'; // ����
        board[tr + s - 1][tc + s]     = 'a'; // ����
        board[tr + s]    [tc + s - 1] = 'a'; // ����

        solveChessBoard(tr + s, tc + s, dr, dc, s);                      
        solveChessBoard(tr, tc, tr + s - 1, tc + s - 1, s);             
        solveChessBoard(tr, tc + s, tr + s - 1, tc + s, s);              
        solveChessBoard(tr + s, tc, tr + s, tc + s - 1, s);              
    }
}

int main() {
    int T;         // ���԰������� 
    int K;         // ���̴�С���� 2^K x 2^K 
    int X, Y;      // ���ⷽ������� (1-indexed) 
    int board_size; // ���̵�ʵ�ʱ߳� 
    int special_r, special_c; // ���ⷽ���0-indexed���� 
    int i, j;      // ѭ����������ѭ���ⲿ���� 

    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &K, &X, &Y);

        board_size = 1 << K; // ���� 2^K /

        special_r = X - 1; // ת��Ϊ
        special_c = Y - 1;

        // �ڵ��õݹ麯��ǰ�������ⷽ����Ϊ '*'
        
        // �ݹ麯��������������з���
        
        board[special_r][special_c] = '*';

        solveChessBoard(0, 0, special_r, special_c, board_size);

        // �������
        for (i = 0; i < board_size; ++i) {
            for (j = 0; j < board_size; ++j) {
                printf("%c", board[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}









//����װ�أ�̰�ģ���zui you zhuang zai
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_C 10000

int weights[MAX_N];

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int T, caseNum;
    int n, C, i;
    int currentWeight, count;

    scanf("%d", &T);
    for (caseNum = 1; caseNum <= T; caseNum++) {
        scanf("%d %d", &n, &C);

        for (i = 0; i < n; i++) {
            scanf("%d", &weights[i]);
        }

        qsort(weights, n, sizeof(int), compare);

        currentWeight = 0;
        count = 0;

        for (i = 0; i < n; i++) {
            if (currentWeight + weights[i] <= C) {
                currentWeight += weights[i];
                count++;
            } else {
                break;
            }
        }

        printf("Case %d: %d %d\n", caseNum, count, currentWeight);
    }

    return 0;
}














//װ�����⣨���ݣ���֧�޽磩��zhuang zai wen ti
#include <stdio.h>

#define MAX_N 20

int n;                // ��װ������
int c1, c2;           // ���Ҵ���������
int weights[MAX_N];   // ��װ����������
int best_weight;      // ��һ�Ҵ������װ������

// ���ݺ��������Խ���װ����䵽��һ�Ҵ���
void backtrack(int index, int current_weight, int remaining_weight) {
    if (current_weight > c1) return; // ������һ�Ҵ�������������֦
    if (index == n) { // ���м�װ�䶼�ѿ���
        int weight2 = remaining_weight - current_weight;
        if (weight2 <= c2 && current_weight > best_weight) {
            best_weight = current_weight;
        }
        return;
    }
    // ���Խ���ǰ��װ������һ�Ҵ�
    backtrack(index + 1, current_weight + weights[index], remaining_weight);
    // ���Բ�����ǰ��װ������һ�Ҵ�
    backtrack(index + 1, current_weight, remaining_weight);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int case_num = 1; case_num <= T; case_num++) {
        scanf("%d", &n);
        scanf("%d %d", &c1, &c2);
        int total_weight = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &weights[i]);
            total_weight += weights[i];
        }
        printf("Case %d:\n", case_num);
        if (total_weight > c1 + c2) {
            printf("No\n");
            continue;
        }
        best_weight = 0;
        backtrack(0, 0, total_weight);
        if (best_weight == 0) {
            printf("No\n");
        } else {
            printf("%d\n", best_weight);
        }
    }
    return 0;
}















//n�����⣨���ݣ���֧�޽磩��n hou wen ti
#include <stdio.h>
#include <stdlib.h>

void solve(int col, int ld, int rd, int n, int* count) {
    int pos;
    int p;

    if (col == (1 << n) - 1) {
        (*count)++;
        return;
    }

    pos = (~(col | ld | rd)) & ((1 << n) - 1);
    while (pos != 0) {
        p = pos & -pos;
        pos -= p;
        solve(col | p, (ld | p) << 1, (rd | p) >> 1, n, count);
    }
}

int totalNQueens(int n) {
    int count;

    count = 0;
    solve(0, 0, 0, n, &count);
    return count;
}

int main() {
    int T;
    int n;
    int i;
    int result;

    scanf("%d", &T);

    for (i = 0; i < T; i++) {
        scanf("%d", &n);
        result = totalNQueens(n);
        printf("%d\n", result);
    }

    return 0;
}
















//0/1�������⣨DP����0/1 bei bao wen ti
#include <stdio.h>
#include <stdlib.h>

// �������������������Ŀ����C �� 13000
#define MAX_CAPACITY 13001
#define MAX_ITEMS 3501

int main() {
    int T; // ������������
    scanf("%d", &T);

    while (T--) {
        int n; // ��Ʒ����
        int C; // ��������
        scanf("%d %d", &n, &C);

        // ������Ʒ�������ͼ�ֵ����
        int *w;
        int *v;
        w = (int *)malloc(n * sizeof(int));
        v = (int *)malloc(n * sizeof(int));

        // ����ÿ����Ʒ�������ͼ�ֵ
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &w[i], &v[i]);
        }

        // ������̬�滮��dp[i][j]��ʾǰi����Ʒ������jʱ������ֵ
        // ����ʹ��һά�����Ż��ռ临�Ӷ�
        int *dp;
        dp = (int *)malloc((C + 1) * sizeof(int));

        // ��ʼ��dp����
        for (int j = 0; j <= C; j++) {
            dp[j] = 0;
        }

        // ��̬�滮���
        for (int i = 0; i < n; i++) {
            for (int j = C; j >= w[i]; j--) {
                if (dp[j - w[i]] + v[i] > dp[j]) {
                    dp[j] = dp[j - w[i]] + v[i];
                }
            }
        }

        // ������
        printf("%d\n", dp[C]);

        // �ͷ��ڴ�
        free(w);
        free(v);
        free(dp);
    }

    return 0;
}











//�����ۻ�Ա���⣨���ݣ���֧�޽磩��lv xing shou huo yuan wen ti
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 18
#define INF INT_MAX

int n, m;
int graph[MAX_N][MAX_N]; // �ڽӾ���洢ͼ
int dp[1<<MAX_N][MAX_N]; // ״̬ѹ��DP��

void initialize() {
    memset(graph, -1, sizeof(graph)); // ��ʼ���ڽӾ���Ϊ-1����ʾ�ޱߣ�
    memset(dp, -1, sizeof(dp)); // ��ʼ��DP��Ϊ-1(��ʾ���ɴ�)
}

int solveTSP() {
    // ��ʼ���������1�����Ϊ0������
    dp[1][0] = 0; // ������1��ʾֻ�����˳���1

    // ��������״̬
    for (int mask = 1; mask < (1<<n); mask++) {
        for (int u = 0; u < n; u++) {
            if (dp[mask][u] == -1) continue; // ���Բ��ɴ�״̬

            // ���Է���δ���ʵĳ���
            for (int v = 0; v < n; v++) {
                if (!(mask & (1<<v)) && graph[u][v] != -1) { // ���vδ������u-v�б�
                    int new_mask = mask | (1<<v);
                    int new_dist = dp[mask][u] + graph[u][v];

                    // ����DP��
                    if (dp[new_mask][v] == -1 || new_dist < dp[new_mask][v]) {
                        dp[new_mask][v] = new_dist;
                    }
                }
            }
        }
    }

    // �������״̬�����г��ж����ʹ����ܻص����
    int final_mask = (1<<n)-1;
    int min_dist = INF;
    for (int u = 1; u < n; u++) { // ���������лص����
        if (graph[u][0] != -1 && dp[final_mask][u] != -1) {
            int total = dp[final_mask][u] + graph[u][0];
            if (total < min_dist) {
                min_dist = total;
            }
        }
    }

    return (min_dist == INF) ? -1 : min_dist;
}

int main() {
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; t++) {
        scanf("%d %d", &n, &m);
        initialize();

        // ��ȡ����Ϣ
        for (int i = 0; i < m; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            u--; v--; // ת��Ϊ0-based���
            graph[u][v] = graph[v][u] = w; // ����ͼ
        }

        int result = solveTSP();
        printf("Case %d: %d\n", t, result);
    }

    return 0;
}













//���ֲ��ң����Σ���e fen cha zhao
#include <stdio.h>
#include <stdlib.h>

// ���ֲ��Һ���
int binarySearch(int *arr, int size, int key) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2; // ��ֹ���

        if (arr[mid] == key) {
            return mid; // �ҵ�key������λ��
        } else if (arr[mid] < key) {
            left = mid + 1; // key���Ұ벿��
        } else {
            right = mid - 1; // key����벿��
        }
    }

    return -1; // δ�ҵ�key
}

int main() {
    int M; // �����ĸ���
    scanf("%d", &M);

    // ����������洢����������
    int *arr;
    arr = (int *)malloc(M * sizeof(int));

    // ����M������
    for (int i = 0; i < M; i++) {
        scanf("%d", &arr[i]);
    }

    int N; // Ҫ���ҵĹؼ��ָ���
    scanf("%d", &N);

    // ����������洢�ؼ��ֵ�����
    int *keys;
    keys = (int *)malloc(N * sizeof(int));

    // ����N���ؼ���
    for (int i = 0; i < N; i++) {
        scanf("%d", &keys[i]);
    }

    // ��ÿ���ؼ��ֽ��ж��ֲ���
    for (int i = 0; i < N; i++) {
        int pos = binarySearch(arr, M, keys[i]);

        if (pos != -1) {
            printf("%d\n", pos); // �ҵ������λ��
        } else {
            printf("Not Found\n"); // δ�ҵ�
        }
    }

    // �ͷ��ڴ�
    free(arr);
    free(keys);

    return 0;
}









//����������⣨̰�ģ���duo ji diao du wen ti
#include <stdio.h>
#include <stdlib.h>

// �ȽϺ��������ڽ�������
int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main() {
    int T; // ������������
    scanf("%d", &T);

    for (int t = 1; t <= T; t++) {
        int n; // ��ҵ����
        int m; // ��������
        scanf("%d %d", &n, &m);

        // ����������洢��ҵʱ�������
        int *jobs;
        jobs = (int *)malloc(n * sizeof(int));

        // ����ÿ����ҵ�Ĵ���ʱ��
        for (int i = 0; i < n; i++) {
            scanf("%d", &jobs[i]);
        }

        // ����ҵ������ʱ�併������
        qsort(jobs, n, sizeof(int), compare);

        // ��������ʼ��������������
        int *machines;
        machines = (int *)malloc(m * sizeof(int));
        for (int i = 0; i < m; i++) {
            machines[i] = 0;
        }

        // ������ҵ������
        for (int i = 0; i < n; i++) {
            // �ҵ���ǰ������С�Ļ���
            int min_index = 0;
            for (int j = 1; j < m; j++) {
                if (machines[j] < machines[min_index]) {
                    min_index = j;
                }
            }
            // ����ǰ��ҵ������û���
            machines[min_index] += jobs[i];
        }

        // �ҵ����л����е�����أ���Ϊ������ʱ��
        int max_time = machines[0];
        for (int i = 1; i < m; i++) {
            if (machines[i] > max_time) {
                max_time = machines[i];
            }
        }

        // ������
        printf("Case %d: %d\n", t, max_time);

        // �ͷ��ڴ�
        free(jobs);
        free(machines);
    }

    return 0;
}






