#include <iostream>
#include <map>
#include <fstream>
#include <cctype>
#include <string>
#include <bitset>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

map<string, int> symbolTable = { { "SP", 0 },{ "LCL", 1 },{ "ARG", 2 },{ "THIS", 3 },{ "THAT", 4 },{ "R0", 0 },{ "R1", 1 },{ "R2", 2 },{ "R3",3 },{ "R4",4 },{ "R5",5 },{ "R6",6 },{ "R7",7 },{ "R8",8 },{ "R9",9 },{ "R10",10 },{ "R11",11 },{ "R12",12 },{ "R13",13 },{ "R14",14 },{ "R15",15 },{ "SCREEN", 16384 },{ "KEYBOARD",24576 } };
map<string, string> dest;
map<string, string> comp;
map<string, string> jmp;
int n = 0;
int c = 0;
std::vector<string> input;
std::vector<string> cleanInput;

void Pass(string line);
string Ainstruction(string content, int& n);
string Cinstruction(string content);
string CleanLine(string line, int& c);

int main() {

	string x;
	string y;
	string str;
	while (getline(cin, x) && x != "")
	{
		if (x == "\n" || x == "")
			input.push_back(" ");
		else
			input.push_back(x);
	}



	for (int i = 0; i < input.size(); i++)
	{
		string newLine = CleanLine(input.at(i), c);
		if (newLine != "" && newLine.substr(0,1) != "(" && newLine.substr(0,2) != "//")
		{
			c++;
			cleanInput.push_back(newLine);
			
		}
	}

	for (int i = 0; i < cleanInput.size(); i++)
	{
		for(int j = 0; j < cleanInput.at(i).size(); j++)
		{ 
			if (cleanInput.at(i).at(j) == ' ' || cleanInput.at(i).at(j) == '/' || cleanInput.at(i) == "")
				cout << '_' << endl;
			else
				cout << cleanInput.at(i).at(j) << endl;
		}
		
	}

	for (int i = 0; i < cleanInput.size(); i++)
	{
		if (cleanInput.at(i) != "" && cleanInput.at(i).substr(0, 1) != "(" && cleanInput.at(i).substr(0, 2) != "//" && cleanInput.at(i) != ";" && cleanInput.at(i).at(0) != '/')
		{
			Pass(cleanInput.at(i));
			
		}
	}

	cin >> y;
	return 0;
}

string CleanLine(string line, int& c)
{
	string content = line;
	string newLine;
	int counter = 0;

	if (content.at(content.size() - 1) == ';')
	{
		cout << "ERROR: end of line expected but semicolon is found";
		exit(1);
	}

	if (content == "" || content.size() == 0 || content == "\n" || content.substr(0, 2) == "//")
	{
		return newLine;
	}
	else if (content.at(0) == ' ')
	{
		counter++;
	}

	if (content.find('(') != string::npos && content.find('(') != 0)
	{
		for (int i = 0; i < content.size(); i++)
		{
			if (content.substr(i, 2) == "//" && i == 0)
			{
				return "";
			}

			else if (content.substr(i, 2) == "//")
			{
				break;
			}

			else if (content.at(i) == '\t')
			{
				;
			}

			else if (content.at(i) == '\n')
			{
				;
			}

			else if (content.at(i) == ' ')
			{
				;
			}

			else if (content.at(i) != '(' && content.at(i) != ')' && content.at(i) != ' ')
			{
				newLine.push_back(content.at(i));
			}
		}
		if (symbolTable.count(newLine) == 0)
		{
			symbolTable.emplace(newLine, c);
		}
		//cout << newLine << endl;

		newLine = "";
	}
	else if (content != "" && content.size() != 0 && content != "\n")
	{

		for (int i = 0; i < content.size(); i++)
		{
			if (content.substr(i, 2) == "//" && i == 0)
			{
				return "";
			}

			else if (content.substr(i, 2) == "//")
			{
				break;
			}

			else if (content.at(i) == '\t')
			{
				;
			}

			else if (content.at(i) == '\n')
			{
				;
			}

			else if (content.at(i) == ' ')
			{
				;
			}

			else
			{
				newLine.push_back(content.at(i));

			}

		}



	}


	return newLine;
}


void Pass(string line)
{
	string content = line;

	if (content.find('@') != string::npos)
	{
		string temp = content.substr(1, content.size() - 1);
		string Ainst = Ainstruction(temp, n);
		cout << Ainst << endl;
	}

	else
	{
		string Cinst = Cinstruction(content);
		cout << Cinst << endl;
	}
}


string Ainstruction(string content, int& n)
{
	for (int i = 0; i < content.size(); i++)
	{
		if (!isdigit(content.at(i)))
		{
			if (symbolTable.count(content) != 0)
			{
				return bitset<16>(symbolTable.at(content)).to_string();
			}
			else
			{
				symbolTable.emplace(content, n + 16);
				n++;
				return bitset<16>(symbolTable.at(content)).to_string();
			}
		}
	}
	return bitset<16>(stoi(content)).to_string();
}

string Cinstruction(string content)
{
	dest.emplace("null", "000");
	dest.emplace("M", "001");
	dest.emplace("D", "010");
	dest.emplace("MD", "011");
	dest.emplace("A", "100");
	dest.emplace("AM", "101");
	dest.emplace("AD", "110");
	dest.emplace("AMD", "111");
	comp.emplace("0", "0101010");
	comp.emplace("1", "0111111");
	comp.emplace("-1", "0111010");
	comp.emplace("D", "0001100");
	comp.emplace("A", "0110000");
	comp.emplace("!D", "0001101");
	comp.emplace("!A", "0110001");
	comp.emplace("-D", "0001111");
	comp.emplace("-A", "0110011");
	comp.emplace("D+1", "0011111");
	comp.emplace("A+1", "0110111");
	comp.emplace("D-1", "0001110");
	comp.emplace("A-1", "0110010");
	comp.emplace("D+A", "0000010");
	comp.emplace("D-A", "0010011");
	comp.emplace("A-D", "0000111");
	comp.emplace("D&A", "0000000");
	comp.emplace("D|A", "0010101");
	comp.emplace("M", "1110000");
	comp.emplace("!M", "1110001");
	comp.emplace("-M", "1110011");
	comp.emplace("M+1", "1110111");
	comp.emplace("M-1", "1110010");
	comp.emplace("D+M", "1000010");
	comp.emplace("D-M", "1010011");
	comp.emplace("M-D", "1000111");
	comp.emplace("D&M", "1000000");
	comp.emplace("D|M", "1010101");
	jmp.emplace("null", "000");
	jmp.emplace("JGT", "001");
	jmp.emplace("JEQ", "010");
	jmp.emplace("JGE", "011");
	jmp.emplace("JLT", "100");
	jmp.emplace("JNE", "101");
	jmp.emplace("JLE", "110");
	jmp.emplace("JMP", "111");

	string cmp, dst, jm;
	if (content.find("=") != string::npos && content.find(";") != string::npos && content != "")
	{
		dst = content.substr(0, content.find("="));
		cmp = content.substr(content.find("=") + 1, (content.find(";") - content.find("=") - 1));
		jm = content.substr(content.find(";") + 1, content.length() - content.find(";") - 1);
	}
	else if (content.find("=") != string::npos && content != "")
	{
		jm = "null";
		dst = content.substr(0, content.find("="));
		cmp = content.substr(content.find("=") + 1, content.length() - content.find("=") - 1);
	}
	else if (content.find(";") != string::npos && content != "")
	{
		dst = "null";
		cmp = content.substr(0, content.find(";"));
		jm = content.substr(content.find(";") + 1, content.length() - content.find(";") - 1);
	}
	/*
	else
	{
	cout << "ERROR: end of line expected but semicolon is found" << endl;
	exit(1);
	return "Error";
	}
	*/
	string cIns = "111" + comp.at(cmp) + dest.at(dst) + jmp.at(jm);

	return cIns;
}

