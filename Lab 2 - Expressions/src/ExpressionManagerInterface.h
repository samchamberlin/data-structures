#pragma once
#include <iostream>
#include <string>
#include <stack>

using namespace std;


class ExpressionManagerInterface
{
public:
	ExpressionManagerInterface() {}
	virtual ~ExpressionManagerInterface() {}

	virtual bool isBalanced(string expression) = 0;
	virtual string postfixToInfix(string postfixExpression) = 0;
	virtual string postfixEvaluate(string postfixExpression) = 0;
	virtual string infixToPostfix(string infixExpression) = 0;

};
