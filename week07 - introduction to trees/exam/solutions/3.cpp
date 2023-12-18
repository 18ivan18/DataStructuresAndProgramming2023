#include <stack>
#include <string>
#include <cassert>

char evaluate(std::stack<char> &s)
{
    bool seenTrueUpToThisPoint = false, seenFalseUpToThisPoint = false;
    while (s.top() != '&' && s.top() != '!' && s.top() != '|')
    {
        if (s.top() == 't')
        {
            seenTrueUpToThisPoint = true;
        }
        else
        {
            seenFalseUpToThisPoint = true;
        }
        s.pop();
    }
    if (s.top() == '&' && seenFalseUpToThisPoint == false)
    {
        return 't';
    }
    if (s.top() == '!' && seenFalseUpToThisPoint == true)
    {
        return 't';
    }
    if (s.top() == '|' && seenTrueUpToThisPoint == true)
    {
        return 't';
    }
    return 'f';
}

int createNumber(const std::string &str, int &i)
{
    int start = i;
    while (isdigit(str[i]))
    {
        i++;
    }
    // i-- because otherwise we'll skip an element
    return std::stoi(str.substr(start, i-- - start));
}

bool parseBoolExpr(const std::string &expression)
{
    std::stack<char> s;
    for (int i = 0; i < expression.size(); i++)
    {
        char ch = expression[i];
        if (ch != ')' && ch != '(' && ch != ',')
        {
            if (isdigit(ch))
            {
                int number = createNumber(expression, i);
                s.push(number % 2 == 0 ? 't' : 'f');
            }
            else
            {
                s.push(ch);
            }
        }
        if (ch == ')')
        {
            char evaluationResult = evaluate(s);
            s.pop();
            s.push(evaluationResult);
        }
    }
    return s.top() == 't';
}

int main()
{
    std::string input1 = "!(13)";
    assert(parseBoolExpr(input1) == true);

    std::string input2 = "|(3,4)";
    assert(parseBoolExpr(input2) == true);

    std::string input3 = "&(2,17)";
    assert(parseBoolExpr(input3) == false);

    std::string input4 = "|(&(2,1,4),!(4))";
    assert(parseBoolExpr(input4) == false);
}