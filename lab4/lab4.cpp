#include <bits/stdc++.h>
#include <fstream>
using namespace std; 
int stringToNum (string str) {
	int num=0;
	int i=0;
	while (str[i]!=0) {
		if (str[i]=='-') {
			return -1;
		}
		num*=10;
		num+=str[i]-'0';
		i++;
	}
	return num;
}
int main(){
	fstream DFA("lab4_Input.txt",ios::in);
	string line;
	int initial;
	map < string, vector< string > > tt; 
	vector<string>final;
	set <string> ff;
	int i=0;
	while(getline(DFA,line)){
		if (i==0){
			initial=stringToNum(line);
		}
		else if (i==1) {
			int x=0;
			string num="";
			while(line[x]!=0) {
				
				if (line[x]==' ') {
					final.push_back(num);
					ff.insert(num);
					num="";
					x++;
					continue;
				}
				num+=line[x++];
			}
			final.push_back(num);
			ff.insert(num);
						
		}else {
			int x=0;
			string num="";
			vector<string> temp;
			while(line[x]!=0) {
				
				if (line[x]==' ') {
					string newnum="";
					for (auto ch : num) {
						if (ch!=',') newnum+=ch;
					}
					temp.push_back(newnum);
					num="";
					x++;
					continue;
				}
				num+=line[x++];
			}
			string newnum="";
			for (auto ch : num) {
				if (ch!=',') newnum+=ch;
			}
			temp.push_back(newnum);
			
			tt[to_string(i-2)]=temp;
		}
		i++;
	}
	DFA.close();

	//Print Old Transition table
	cout<<"Initial State: " <<initial <<endl;
	cout<<"Final States: " <<endl;
	for (int i=0;i<final.size();i++) cout<<final[i]<<" ";
	cout<<endl<<endl;
	cout<<"Printing Transition Table of NFA from file: " <<endl;
	auto itr = tt.begin();
	for (;itr!=tt.end();itr++){
		auto state=itr->first;
		auto vec=itr->second;
		cout<<state <<" -> ";
		for (int j=0;j<vec.size();j++){
			cout<<vec[j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	//convert NFA to DFA
	map <string , vector < string > > newtt;
	newtt[to_string(initial)]=tt[to_string(initial)];
	int cols=newtt[to_string(initial)].size();
	auto itr1 = tt.begin();
	auto itr2 = newtt.begin();
	for (;itr2!=newtt.end();itr2++){
		auto state =itr2->first;
		auto vec=itr2->second;
		for (int j=0;j<vec.size();j++){
			
			auto currStr=vec[j];
			if (currStr=="-1") continue;
			if (newtt.find(currStr)!=newtt.end()) continue;

			
			
			for (int inp=0;inp<cols;inp++) {
				set <char> st;
				for (auto ch : currStr ){
					
					string chh="";
					chh+=ch;
					if (ff.find(chh)!=ff.end()){
						ff.insert(currStr);
					}
					if (tt[chh][inp]!="-1") {
						for (auto chhr : tt[chh][inp]) {
							st.insert(chhr);
						}
					}
				}
				string newstr="";
				for (auto ch : st) {
					newstr+=ch;
				}
				if (st.empty()) newstr="-1";
				newtt[currStr].push_back(newstr);
			}
			
			
		}
		
	}

	// Print new DFA Transition table 
	cout<<"Print transition table of DFA : \n";
	cout<<"Initial State: " <<initial <<endl;
	for (auto p: tt) {
		auto key=p.first;
		if (newtt.find(key)==newtt.end()) ff.erase(key);
	}
	cout<<"Final States: " <<endl;
	for (auto x :ff) cout<<x<<" ";
	cout<<endl;
	itr = newtt.begin();
	for (;itr!=newtt.end();itr++){
		auto state =itr->first;
		auto vec=itr->second;
		cout<<state<<"-> ";
		if (tt.find(state)!=tt.end()) {
			
		}
		for (int j=0;j<vec.size();j++){
			cout<<vec[j]<<" ";
		}
		cout<<endl;
	}

	itr = tt.begin();
	for (;itr!=tt.end();itr++){
		
		auto state =itr->first;
		auto vec=itr->second;
		if (newtt.find(state)!=newtt.end())continue; 
		cout<<state<<"-> ";
		if (tt.find(state)!=tt.end()) {
			
		}
		for (int j=0;j<vec.size();j++){
			cout<<vec[j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;

	return 0;
}
