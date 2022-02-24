#include <iostream>
#include <string>
#include <deque>

int main()
{
    int x;
    std::cin >> x;
    std::deque<std::string> expression;
    expression.push_back(std::to_string(x));
    int n;
    std::cin >> n;
    char prev_op;
    for (int i = 0 ; i < n; i++)
    {
        int a;
        char op;
        std::cin >> op >> a;
        if (i && (prev_op == '+' || prev_op == '-') && (op == '*' || op == '/'))
        {
            expression.push_front("(");
            expression.push_back(")");
        }
        expression.push_back(" " + std::string(1,op) + " " + std::to_string(a));
        prev_op = op;
    }
    for (std::string s: expression)
    {
        std::cout << s;
    }
    return 0;
}