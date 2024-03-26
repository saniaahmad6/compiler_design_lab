#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

void findFirst(int currSymbol, map <char,set<string>> &gram,map <char,set<char>> &first, map <char,bool> &vis) {
	if (vis[currSymbol]) return;
	vis[currSymbol]=1;
	
	for (auto prod : gram[currSymbol]) {
	
		if ((prod[0]>='a' and prod[0]<='z') or prod[0]=='#') {
			first[currSymbol].insert(prod[0]);	
		}else{

			for (int i=0;i<prod.size();i++) { // string iterate
				if ((prod[i]>='a' and prod[i]<='z')) {
					first[currSymbol].insert(prod[i]);	
					break;
				}
				findFirst(prod[i],gram,first,vis); // call first
				bool isEpsilon=false; // check epsilonness
				for (auto ff: first[prod[i]]) { 
					if (ff!='#') {
						first[currSymbol].insert(ff);
					}else {
						isEpsilon=true;
						if (i==prod.size()-1) {
							first[currSymbol].insert('#');
						}
					}
				}
				if (!isEpsilon) break;
			}
			
		}
		
	}
}

bool addFirsts(char currSymbol, char nextSymbol,map <char,set<char>> &follow,map <char,set<char>> &first) {
	bool hasEpsilon=false;
	for (auto ff : first[nextSymbol]) {
		if (ff!='#') follow[currSymbol].insert(ff);
		else hasEpsilon=true;
	}
	return hasEpsilon;
}
void findFollow(int currSymbol, map <char,set<string>> &grammar,map <char,set<char>> &follow,map <char,set<char>> &first){
	for (auto row : grammar) {
		for (auto production : row.second) {
			for (int i=0;i<production.size();i++) {
				char symbol=production[i];
				if (symbol==currSymbol) {
					//find currSymbol in RHS
						int j;
						for (j=i+1;j<production.size();j++) {
							char nextSymbol=production[j];
							if (nextSymbol>='a' and nextSymbol<='z') {
								follow[currSymbol].insert(nextSymbol);
								break;
							}else {//non terminal
								bool hasEpsilon=addFirsts(currSymbol,nextSymbol,follow,first);
								if (!hasEpsilon) {
									break;
								}
							}
						}
						if (j==production.size() and row.first!=currSymbol) {
							follow[currSymbol].insert(row.first); // non terminal parent LHS
						}
					
				} 
			}
		}
	}
}

void updateFollow(map <char, set <char>> &follow){
	bool hasVariables=true;
	while (hasVariables) {
		hasVariables=false;

		for (auto &row : follow) {
			set <char> VarTobeDel;
			for (auto &ch : row.second) {
				if (ch>='a' and ch<='z' or ch=='$') continue;
				for (auto ff : follow[ch]) {
					follow[row.first].insert(ff);
				}
				VarTobeDel.insert(ch);
			}

			for (auto e : VarTobeDel) {
				follow[row.first].erase(e);
			}
		}

		for (auto &row : follow) {
			for (auto &ch : row.second){
				if (ch>='A' and ch<='Z') {
					hasVariables=true;
					break;
				}
			}
			if (hasVariables) break;
		}
	}
}
int main(){
    fstream DFA("lab5_Input.txt",ios::in);
	string line;
	int initial;
	map <char,set<string>> gram;

	int i=0;
	char startSymbol;
	while(getline(DFA,line)){
		if (i==0) {
			startSymbol=line[0];
		}
		int x=3;
		string num="";
		char var=line[0];
		while(line[x]!=0) {
			num+=line[x++];	
			if (line[x]=='|') {
					gram[var].insert(num);
					num="";
					x++;
					continue;
			}
			
		}
		gram[var].insert(num);
		i++;
	}
	DFA.close();
	std::cout<<"Printing Grammar from file: " <<endl;
	auto itr = gram.begin();
	for (;itr!=gram.end();itr++){
		auto state=itr->first;
		auto vec=itr->second;
		std::cout<<state <<" -> ";
		for (auto prod : vec){
			std::cout<<prod<<" | ";
		}
		std::cout<<endl;
	}
	std::cout<<endl;
	
	//first
	map <char,set<char>> first;
	map <char,bool>vis;
	char currSymbol=startSymbol;
	for (auto ch : gram) {
		if (!vis[ch.first]) findFirst(ch.first,gram,first,vis);
	}
	
	std::cout<<"Printing first of symbols from file: " <<endl;
	auto itr1 = first.begin();
	for (;itr1!=first.end();itr1++){
		auto state=itr1->first;
		auto vec=itr1->second;
		std::cout<<state <<" { ";
		for (auto prod : vec){
			std::cout<<prod<<" ";
		}
		std::cout<<" }"<<endl;
	}
	std::cout<<endl;
	
	//follow
	vis.clear();
	map <char,set<char>> follow;
	follow[startSymbol].insert('$'); //insert dollar
	for (auto row : gram) {
		findFollow(row.first,gram,follow,first); 
	}
	updateFollow(follow);

	std::cout<<"Printing follow of symbols from file: " <<endl;
	auto itr2 = follow.begin();
	for (;itr2!=follow.end();itr2++){
		auto state=itr2->first;
		auto vec=itr2->second;
		std::cout<<state <<" { ";
		for (auto prod : vec){
			std::cout<<prod<<" ";
		}
		std::cout<<" }"<<endl;
	}
	std::cout<<endl;
	
	return 0;
}
