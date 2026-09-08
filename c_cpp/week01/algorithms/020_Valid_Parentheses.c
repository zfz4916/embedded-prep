#include <stdbool.h>
#include <string.h>

bool isValid(char* s) {
    int n = strlen(s);
    if (n % 2 != 0) return false;  // 奇数个直接排除
    
    char stack[n];  // 用数组模拟栈
    int top = -1;   // 栈顶指针，-1表示空栈
    
    for (int i = 0; i < n; i++) {
        char c = s[i];
        
        // 遇到左括号，入栈
        if (c == '(' || c == '[' || c == '{') {
            stack[++top] = c;
        } 
        // 遇到右括号，检查栈顶
        else {
            if (top == -1) return false;  // 栈空，没有左括号可匹配
            
            char topChar = stack[top--];  // 出栈
            
            // 检查是否匹配
            if ((c == ')' && topChar != '(') ||
                (c == ']' && topChar != '[') ||
                (c == '}' && topChar != '{')) {
                return false;  // 不匹配
            }
        }
    }
    
    return top == -1;  // 栈空说明全部匹配，否则有剩余左括号
}