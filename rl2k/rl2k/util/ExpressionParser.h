#pragma once
#include <string>
#include <vector>
#include <stack>
using namespace std;
namespace ExpressionParser
{
	class token
	{
	public:
		string value;
		int Parse();
		token * parent = nullptr;
		token * child1 = nullptr;
		token * child2 = nullptr;

		bool isOperator();
	};


	class tree
	{
	public:
		token * root;
		void construct(vector<token *> tokens);
		int evaluate();
	private:
		void construct(vector<token *> tokens, int index);
		int evaluate(int index);
		
	};



	int Parse(string expression);
	vector<string> split(const char * str, char c);
	vector<string> split(string str, int lineMax, char c);
	vector<string> splitLength(string str, int lineMax);
};

