#include<stack>
#include<queue>
using std::stack;

class MinStack; //最小栈

//最小栈
class MinStack 
{
public:
    MinStack() {
        min_Stack.push(INT_MAX);
    }

    void push(int val) {
        x_stack.push(val);
        min_Stack.push(std::min(min_Stack.top(), val));
    }

    void pop() {
        x_stack.pop();
        min_Stack.pop();
    }

    int top() {
        return x_stack.top();
    }

    int getMin(){
        return min_Stack.top();
    }
private:
    stack<int>min_Stack;
    stack<int>x_stack;
};