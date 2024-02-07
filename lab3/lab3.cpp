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
	fstream DFA("lab3_input.txt",ios::in);
	string line;
	int initial;
	vector< vector< int > > tt; 
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
	
//	cout<<"" <<endl;
	cout<<"Printing Transition Table of DFA from file: " <<endl;
	for (int i=0;i<tt.size();i++){
		for (int j=0;j<tt[i].size();j++){
			cout<<tt[i][j]<<" ";
		}
		cout<<endl;
	}
	

	int n=tt.size();
	int m=tt[0].size()/2;
	vector <vector<int> > states;
	vector <vector<int> > output;
	cout<<endl;
	for (int i=0;i<tt.size();i++) {
		int sz=tt[i].size();
		vector <int> curx,cury;
		for (int j=0;j<sz;j++) {
			if (j%2==0) {
				curx.push_back(tt[i][j]);
			}else {
				cury.push_back(tt[i][j]);
			}
		}
		states.push_back(curx);
		output.push_back(cury);
	}
	cout<<"Printing state Table of DFA from file: " <<endl;
	for (int i=0;i<states.size();i++){
		for (int j=0;j<states[i].size();j++){
			cout<<states[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"Printing output Table of DFA from file: " <<endl;
	for (int i=0;i<output.size();i++){
		for (int j=0;j<output[i].size();j++){
			cout<<output[i][j]<<" ";
		}
		cout<<endl;
	}
	
	cout<<"Initial State: " <<initial <<endl;
	
	cout<<endl<<endl;
	
	

	cout<<"Enter string: ";
	string input;
	getline(cin,input);
	int currState=initial;
	int inputLen=input.size();
	int k=0;
	while (currState!=-1 && k<inputLen) {
		
		int index=input[k++]-'0';
		
		if (index>=states[currState].size() or index>=26 or index <0) {
			goto end;
		}
		int newState=states[currState][index];
		if (currState==-1) break;
		cout<<output[currState][index] <<"  ";
		currState=newState;
		
	}
	end:
	if (currState==-1) cout<<"Transition invalid"<<endl;
	
	else if (k!=inputLen) {
		cout<<"Output not completed"<<endl;
			
	}
	
	return 0;
}
