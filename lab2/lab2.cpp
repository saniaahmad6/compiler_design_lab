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
	fstream DFA("lab2_input.txt",ios::in);
	string line;
	int initial;
	vector< vector< int > > tt; 
	vector<int>final;
	set <int> ff;
	int i=0;
	while(getline(DFA,line)){
		if (i==0){
			initial=stringToNum(line);
		}
		else {
			int x=0;
			string num="";
			vector<int> temp;
			while(line[x]!='\0') {
				
				if (line[x]==' ') {
					temp.push_back(stringToNum(num));
					num="";
					x++;
					continue;
				}
				num+=line[x++];
			}
			temp.push_back(stringToNum(num));
			tt.push_back(temp);
		}
		i++;
	}
	DFA.close();
	cout<<"Printing Transition Table of DFA from file: " <<endl;
	for (int i=0;i<tt.size();i++){
		for (int j=0;j<tt[i].size();j++){
			cout<<tt[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	for (int i=0;i<tt.size();i++) {
		int sz=tt[i].size();
		final.push_back(tt[i][sz-1]);
		tt[i].pop_back();
	}
	
	
	cout<<"Initial State: " <<initial <<endl;
	cout<<"Enter string: ";
	string input;
	getline(cin,input);
	vector <int> states;
	int currState=initial;
	int inputLen=input.size();
	int k=0;
	while (currState!=-1 && k<inputLen) {
		
		cout<<final[currState];
		int index=input[k++]-'0';
		int newState=tt[currState][index];
		if (index>tt[currState].size() or index>=26 or index <0) {
			goto end;
		}
		currState=newState;
		
	}
	if (currState!=-1) cout<<final[currState];
	else if (currState==-1) cout<<"Output NOT completed"<<endl;
	end:
	if (k!=inputLen) {
		cout<<"Output not completed"<<endl;
			
	}
	
	return 0;
}
