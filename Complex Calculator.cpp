#include <iostream>
#include <algorithm>
#include <complex>
#include <sstream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

int iCPri(string a) {    // in_come priority
	int pri;
	if (a == "(" || a == ")") { pri = 2; }
	else if (a == "*" || a == "/") { pri = 1; }
	else if (a == "+" || a == "-") { pri = 0; }
	else { pri = 3; }
	return pri;
}
int iSPri(string a) {    // in_stack priority
	int pri;
	if (a == "(" || a == ")") { pri = -1; }
	else if (a == "*" || a == "/") { pri = 1; }
	else if (a == "+" || a == "-") { pri = 0; }
	else { pri = -2; }
	return pri;
}
vector<string> inToPo(const vector<string>& infix, vector<string>& postfix, stack<string>& operStack) {
	operStack.push("#");
	for (int i = 0; i < infix.size(); i++) {
		if (iCPri(infix[i]) == 3) { postfix.push_back(infix[i]); }
		else if (infix[i] == ")") {
			while (operStack.top() != "(") {
				postfix.push_back(operStack.top());
				operStack.pop();
			}
			operStack.pop();
		}
		else {
			while (iSPri(operStack.top()) >= iCPri(infix[i])) {
				postfix.push_back(operStack.top());
				operStack.pop();
			}
			operStack.push(infix[i]);
		}
	}
	while (operStack.top() != "#") {
		postfix.push_back(operStack.top());
		operStack.pop();
	}
	
	return postfix;
}
complex<double> parse(const string &a) {
	double real;
	double imag;
	int plusPos = a.find("+");
	int minusPos = a.find("-");
	int iPos = a.find("i");
	
	if (plusPos != -1 || minusPos != -1) {
		int symPos = max(plusPos, minusPos);
		real = stod(a.substr(1, symPos - 1));
		if (iPos - symPos - 1 == 0) {	imag = 1;}
		else {	imag = stod(a.substr(symPos + 1, iPos - symPos - 1));}

		if (minusPos != -1) { imag *= -1; }
	}
	else {
		if (iPos != -1) {
			real = 0;
			if (iPos == 1 ) { imag = 1;}
			else if (iPos - 1 == minusPos) { imag = -1; }
			else { imag = stod(a.substr(1, iPos - 1)); }

			if (minusPos != -1) { imag *= -1; }
		}
		else {
			real = stod(a.substr(1,a.length() - 2));
			imag = 0;
		}
	}
	return complex<double> (real, imag);
}

complex<double> eval(complex<double> &op1, complex<double> &op2, string &operate) {
	if (operate == "*") { return op2 * op1; }
	else if (operate == "/") { return op2 / op1; }
	else if (operate == "+") { return op2 + op1; }
	else if (operate == "-") { return op2 - op1; }
	else return 0;
}

complex<double> evalPostfix(vector<string> &postfix) {
	stack< complex<double> > s;
	int size = postfix.size();
	int i = 0;
	string ch;
	complex<double> val;
	if (size == 1) {
		ch = postfix[0];
		return parse(ch);
	}
	else {
		while (i < size) {
			ch = postfix[i];
			if (ch[0] == '[') {
				s.push(parse(ch));
			}
			else {
				complex<double> op1 = s.top();
				s.pop();
				complex<double> op2 = s.top();
				s.pop();
				val = eval(op1, op2, ch);
				s.push(val);
			}
			i++;
		}
	}

	return val;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int N;
	
	cin >> N;
	cin.ignore(1000, '\n');
	
	for (int i = 0; i < N; i++) {
		string temp;
		istringstream ss;
		getline(cin, temp);
		
		vector<string> infix;
		vector<string> postfix;
		stack<string> operStack;

		int flag = 0;
		int leftpar;
		int rightpar;
		for (int j = 0; j < temp.length(); j++) {
			if (temp[j] == '+' || temp[j] == '-' || temp[j] == '*' 
				|| temp[j] == '/' || temp[j] == '(' || temp[j] == ')') {
				if (flag == 1) {continue;}
				else {
					string symbol(1, temp[j]);
					infix.push_back(symbol);
				}
			}
			else if (temp[j] == '['){
				leftpar = j;
				flag = 1;
			} 
			else if (temp[j] == ']'){
				rightpar = j;
				infix.push_back(temp.substr(leftpar , rightpar - leftpar + 1));
				flag = 0;
			}
		}
		vector<string> Postfix = inToPo(infix, postfix, operStack);
		
		complex<double> eva = evalPostfix(Postfix);
		for (int k = 0; k < Postfix.size(); k++) {
			cout << Postfix[k];
		}
		cout << '\n';
		//cout << eva;
		if (real(eva) == 0 && imag(eva) == 0) {
			cout << "[0]";
		}
		else if (real(eva) == 0 && imag(eva) != 0) {

			if (imag(eva) == 1) { cout << "[i]"; }
			else if (imag(eva) == -1) { cout << "[-i]"; }
			else { cout << "[" << imag(eva) << "i]"; }
		}
		else if (real(eva) != 0 && imag(eva) == 0) {
			cout << "[" << real(eva) << "]";
		}
		else { 
			if (imag(eva) < 0) {
				if (imag(eva) == -1) { cout << "[" << real(eva) << "-i]"; }
				else { cout << "[" << real(eva) << imag(eva) << "i]"; }
			}
			else{
				if (imag(eva) == 1){ cout << "[" << real(eva) << "+i]";}
				else { cout << "[" << real(eva) << "+" << imag(eva) << "i]"; }
			}
		}
		cout << '\n';
	}
	
	system("pause");
	return 0;
}