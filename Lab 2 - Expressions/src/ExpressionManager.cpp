#include "ExpressionManager.h"

bool ExpressionManager::isBalanced(string expression){
    stack<char> myStack;
    bool balanced = true;
    int index = 0;
    
    while(balanced == true && index < expression.size()){
        char temp = expression.at(index);
        if(temp == '(' || temp == '[' || temp == '{'){
            myStack.push(temp);
        } else if(temp == ')' || temp == ']' || temp == '}'){
            if(myStack.empty()){
                return false;
            } else if(myStack.top() == '(' && temp != ')'){
                balanced = false;
            } else if(myStack.top() == '[' && temp != ']'){
                balanced = false;
            } else if(myStack.top() == '{' && temp != '}'){
                balanced = false;
            }
            myStack.pop();
        }
        index++;
    }
    if(!myStack.empty()){
        balanced = false;
    }
    return balanced;
}

string ExpressionManager::postfixToInfix(string postfixExpression){
    stack<string> myStack;
    string token;
    string infixExpression = "";
    int index = 0;
    vector<string> tokens;
    istringstream inSS(postfixExpression);
    
    while(getline(inSS, token, ' ')){
        tokens.push_back(token);
        if (token.find(".") != string::npos) {
            return "invalid";
        }
        if(isdigit(tokens.at(index).front())){
            string temp = tokens.at(index);
            myStack.push(temp);
        } else if(tokens.at(index) == "+" || tokens.at(index) == "-" || tokens.at(index) == "*" || tokens.at(index) == "/" || tokens.at(index) == "%"){
            if(myStack.empty()){
                return "invalid";
            }
            string newValue = "";
            string rightValue = myStack.top();
            myStack.pop();
            if(myStack.empty()){
                return "invalid";
            }
            string leftValue = myStack.top();
            myStack.pop();
            newValue = "( " + leftValue + " " + tokens.at(index) + " " + rightValue + " )";
            myStack.push(newValue);
        } else{
            return "invalid";
        }
        index++;
    }
    infixExpression = myStack.top();
    myStack.pop();
    if(!myStack.empty()){
        return "invalid";
    }
    return infixExpression;
}

string ExpressionManager::postfixEvaluate(string postfixExpression){
    stack<int> myStack;
    string token;
    string answer = "";
    int index = 0;
    vector<string> tokens;
    istringstream inSS(postfixExpression);
    
    while(getline(inSS, token, ' ')){
        tokens.push_back(token);
        
        if(isdigit(tokens.at(index).front())){
            int temp = stoi(tokens.at(index));
            myStack.push(temp);
        } else if(tokens.at(index) == "+" || tokens.at(index) == "-" || tokens.at(index) == "*" || tokens.at(index) == "/" || tokens.at(index) == "%"){
            int newValue = 0;
            
            if(!myStack.empty()){
                int rightValue = myStack.top();
                myStack.pop();
                int leftValue = myStack.top();
                myStack.pop();
                if(tokens.at(index) == "+"){
                    newValue = leftValue + rightValue;
                } else if(tokens.at(index) == "-"){
                    newValue = leftValue - rightValue;
                } else if(tokens.at(index) == "*"){
                    newValue = leftValue * rightValue;
                } else if(tokens.at(index) == "/"){
                    if(rightValue == 0){
                        return "invalid";
                    }
                    newValue = leftValue / rightValue;
                } else if(tokens.at(index) == "%"){
                    newValue = leftValue % rightValue;
                }
                myStack.push(newValue);
            } else {
                return "invalid";
            }
        } else{
            return "invalid";
        }
        index++;
    }
    if(!myStack.empty()){
        answer = to_string(myStack.top());
        myStack.pop();
    }
    return answer;
}

bool process_operator(stack<string> &opStack, string &postfixExpression, string &op){
    int precedenceOp = 0;
    int precedenceStackTop = 0;
    if(opStack.empty() && (op != ")" && op != "]" && op != "}")){
        opStack.push(op);
        return true;
    } else if(op == "(" || op == "{" || op == "[" || opStack.top() == "(" || opStack.top() == "[" || opStack.top() == "{"){
        opStack.push(op);
        return true;
    } else if(op == ")" || op == "]" || op == "}"){
        if(!opStack.empty()){
            if(op == ")"){
                while(opStack.top() != "("){
                    postfixExpression = postfixExpression + opStack.top() + " ";
                    opStack.pop();
                    if(opStack.empty()){
                        return false;
                    }
                }
                opStack.pop();
                return true;
            } else if(op == "]"){
                while(opStack.top() != "["){
                    postfixExpression = postfixExpression + opStack.top() + " ";
                    opStack.pop();
                    if(opStack.empty()){
                        return false;
                    }
                }
                opStack.pop();
                return true;
            } else if(op == "}"){
                while(opStack.top() != "{"){
                    postfixExpression = postfixExpression + opStack.top() + " ";
                    opStack.pop();
                    if(opStack.empty()){
                        return false;
                    }
                }
                opStack.pop();
                return true;
            }
        } else{
            return false;
        }
    } else{
        precedenceOp = 0;
        precedenceStackTop = 0;
        if(op == "+" || op == "-"){
            precedenceOp = 1;
        }
        if(op == "*" || op == "/" || op == "%"){
            precedenceOp = 2;
        }
        if(opStack.top() == "+" || opStack.top() == "-" ){
            precedenceStackTop = 1;
        }
        if(opStack.top() == "*" || opStack.top() == "/" || opStack.top() == "%"){
            precedenceStackTop = 2;
        }
        while(precedenceOp <= precedenceStackTop && !opStack.empty()){
            postfixExpression = postfixExpression + opStack.top() + " ";
            opStack.pop();
            if(!opStack.empty()){
                precedenceStackTop = 0;
                if(opStack.top() == "+" || opStack.top() == "-" ){
                    precedenceStackTop = 1;
                }
                if(opStack.top() == "*" || opStack.top() == "/" || opStack.top() == "%"){
                    precedenceStackTop = 2;
                }
            }
        }
        opStack.push(op);
    }
    return true;
}

string ExpressionManager::infixToPostfix(string infixExpression){
    string postfixExpression = "";
    stack<string> myStack;
    int index = 0;
    string token;
    vector<string> tokens;
    istringstream inSS(infixExpression);
    
    while(getline(inSS, token, ' ')){
        tokens.push_back(token);
        if(tokens.at(index) == "+" || tokens.at(index) == "-" || tokens.at(index) == "*" || tokens.at(index) == "/" || tokens.at(index) == "%"){
            if(index > 0){
                if(tokens.at(index - 1) == "+" || tokens.at(index - 1) == "-" || tokens.at(index - 1) == "*" || tokens.at(index - 1) == "/" || tokens.at(index - 1) == "%"){
                    return "invalid";
                }
            }
        }
        if (token.find(".") != string::npos) {
            return "invalid";
        }
        if(isdigit(tokens.at(index).front())){
            postfixExpression = postfixExpression + tokens.at(index) + " ";
        } else if(tokens.at(index) == "+" || tokens.at(index) == "-" || tokens.at(index) == "*" || tokens.at(index) == "/" || tokens.at(index) == "%" || tokens.at(index) == "(" || tokens.at(index) == "[" || tokens.at(index) == "{" || tokens.at(index) == ")" || tokens.at(index) == "]" || tokens.at(index) == "}"){
            if(process_operator(myStack, postfixExpression, token) == false){
                return "invalid";
            }
        } else{
            return "invalid";
        }
        index++;
    }
    while(!myStack.empty()){
        if(myStack.top() == "(" || myStack.top() == "[" || myStack.top() == "{"){
            return "invalid";
        }
        if(postfixExpression == ""){
            return "invalid";
        }
        if(myStack.size() == 1){
            postfixExpression = postfixExpression + myStack.top();
            myStack.pop();
        } else{
            postfixExpression = postfixExpression + myStack.top() + " ";
            myStack.pop();
        }
    }
    if(postfixExpression.back() == ' '){
        postfixExpression.pop_back();
    }
    return postfixExpression;
}
