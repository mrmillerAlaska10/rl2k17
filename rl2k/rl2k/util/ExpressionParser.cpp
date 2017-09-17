#include "ExpressionParser.h"
#include <sstream>

/*
*patterns: 
*	(expression) + (expression)
*	(expression) - (expression)
*	(expression) * (expression)
*	(expression) / (expression)
*	(expression) d (expression)
*	$variable
*	integer
*/
int ExpressionParser::Parse(string expression)
{
	vector<string> s = split(expression.c_str(),' ');
	vector<token*> tokens;
	stack<string> expressionStack;
	for(int i = 0; i < s.size();i++)
	{
		tokens.push_back( new token());
		tokens[i]->value = s[i];

	}

	tree expT;
	expT.construct(tokens);
	return expT.evaluate();
}




vector<string> ExpressionParser::split(const char *str, char c = ' ')
{
	vector<string> result;

	do
	{
		const char *begin = str;

		while (*str != c && *str)
			str++;

		result.push_back(string(begin, str));
	} while (0 != *str++);

	return result;
}

vector<string> ExpressionParser::split(string str, int lineMax, char c = '\n')
{
	vector<string> split;

	//manual splits
	string temp = "";
	for (int i = 0; i < str.length(); i++)
	{if(i == (str.length() -1))
		{
		temp += str[i];
			split.push_back(temp);
		}
		else if (str[i] != '\n')
		{
			temp += str[i];
		}
		
		else
		{
			split.push_back(temp);
			temp = "";
		}

	}

	vector<string> result;

	if (lineMax == 0)
	{
		return split;
	}
	//auto split
	for (int i = 0; i < split.size(); i++)
	{
		vector<string> temp = splitLength(split[i], lineMax);
		for (int j = 0; j < temp.size(); j++)
		{
			result.push_back(temp[j]);
		}
	}
	return result;
}

vector<string> ExpressionParser::splitLength(string str, int lineMax)
{
	vector<string> result;
	int position = 0;
	
	while (position < str.length())
	{
		string temp = "";
		temp += str.substr(position, lineMax);
		result.push_back(temp);
		position += lineMax;
	}

	return result;
}


//evaluate tree nodes
int ExpressionParser::token::Parse()
{
	
	if (this->isOperator())
	{
		return (child1->Parse() + child2->Parse());
	}

	int v = stoi(value);
	return v;
}

bool ExpressionParser::token::isOperator()
{
	if (value == "+" || value == "-" || value == "*" || value == "/" || value == "d")
		return true;
	else
		return false;
}

void ExpressionParser::tree::construct(vector<token*> tokens)
{
	construct(tokens, 0);
}

int ExpressionParser::tree::evaluate()
{
	return root->Parse();
	
}

int ExpressionParser::tree::evaluate(int index)
{
	return root->Parse();
}

//xdy + 3 + 2d5
void ExpressionParser::tree::construct(vector<token*> tokens, int index)
{
	if (index >= tokens.size())
		return;
	//first entry cannot be an operator, and  will be child 1 of next entry
	if (index == 0)
	{
		if (tokens[index]->isOperator())
		{
			return;
		}
		root = tokens[index];
		construct(tokens, 1);
		return;
	}
	

	
	if (tokens[index]->isOperator())
	{
		tokens[index]->child1 = root;
		root = tokens[index];
		construct(tokens, index + 1);
	}
	// is number
	else
	{
		tokens[index - 1]->child2 = tokens[index];
		construct(tokens, index + 1);
	}



	

}
