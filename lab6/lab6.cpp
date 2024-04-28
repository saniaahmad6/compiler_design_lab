#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
int stringToInt(string t){
	int ans=0;
	for(int i=0;i<t.size();i++){
		ans=(ans*10)+(t[i]-'0');
	}
	return ans;
}


void dfs(int node, vector <int> ds,vector <int> &vis, vector <vector <int>> &adjmat, vector <vector<vector<int>>> &dominatorListTemp) {
	ds.push_back(node);
	vis[node]=1;
	for (int i=1;i<adjmat[node].size();i++) {
		if (!vis[i] and i!=node and adjmat[node][i]==1) {
			dfs(i,ds,vis,adjmat,dominatorListTemp);
		}
	}
	// cout<<"yes"<<" ";
	dominatorListTemp[node].push_back(ds);
	vis[node]=0;
	ds.pop_back();
}
int main(){
    fstream DFA("input.txt",ios::in);
	string line;
	int initial;
	map <int,string> tac;
	set <int> leaders;
	int i=0;
	while(getline(DFA,line)){
		if (i==0) {
			leaders.insert(i+1);
		}
		stringstream ss(line);
		string x;
		int flag=0;
		while (ss>>x) {
			if (x=="goto") {
				flag=1;
			}
			else if (flag) {
				int len=x.size();
				x=x.substr(1,len-2);
				int y=i+1;
				y++; 
				leaders.insert(stringToInt(x));
				leaders.insert(y);
				break;
			}
		}
		tac[i+1]=line;
		i++;
	}
	int lastLine=i;
	DFA.close();
	cout<<"Printing leaders: "<<endl;
	for (auto e : leaders) {
		cout<<e<<"->" <<tac[e]<<" ";
		cout<<endl;
	}
	
	cout<<"\nPrinting blocks: "<<endl;
	auto prev=leaders.begin();
	auto curr=prev;
	curr++;
	vector <pair<int,int>> blocks;
	for (;curr!=leaders.end();curr++) {
		int end=*(curr)-1;
		int beg=*prev;
		blocks.push_back({beg,end});
		prev=curr;
	}
	blocks.push_back({*prev,lastLine});
	int k=1;
	map <int,int> mp;
	for (auto p : blocks) {
		cout<<"\n\nBlock "<<k<<endl;
		for (int i=p.first;i<=p.second;i++) {
			cout<<i<<"->"<<tac[i]<<endl;
			mp[p.first]=k;
		}
		k++;
	}
	int lastBlock=k-1;
	//Program 2
	vector <vector <int>> adjmat(k,vector <int> (k,0));
	k=1;
	for (auto p : blocks) {
		auto lastLine=tac[p.second];
		cout<<lastLine<<endl;
		if (lastLine.find("goto")==string::npos) {
			if (k!=lastBlock) {
				adjmat[k][k+1]=1;
//				cout<<k<<" "<<k+1<<endl;
			}
		}
		else {
			string jmp=lastLine.substr(lastLine.find("goto")+5);
			jmp=jmp.substr(1,jmp.size()-2);
			int jmpnum=stringToInt(jmp);
			// cout<<jmpnum<<endl;
			adjmat[k][mp[jmpnum]]=1;
//			cout<<k<<" "<<mp[jmpnum]<<endl;
			if (lastLine.find("goto")!=0) {
				if (k!=lastBlock) {
					adjmat[k][k+1]=1;
//					cout<<k<<" "<<k+1<<endl;
				}
				
			}
		}
		k++;
	}
	
	cout<<"\nPrinting adjacency matrix: "<<endl;
	fstream file("adjmat.txt",ios::out);
	for (int i=1;i<k;i++) {
		string line="";
		for (int j=1;j<k;j++) {
			line+=(adjmat[i][j]+'0');
			line+=" ";
			cout<<adjmat[i][j]<<" ";
		}
		line+="\n";
		file << line;
		cout<<endl;
	}
	

	// Dominator Lists
	vector <vector<vector<int>>> dominatorListTemp(k);
	vector <int> vis(k,0);
	dfs(1,vector<int> (),vis,adjmat,dominatorListTemp);


	map <int,map<int,int>> dominatorMap;
	map <int,set<int>> dominatorList;  

	for (int node=1;node<k;node++) {
		map <int,int> mp;
		int maxi=0;
		for (auto vec : dominatorListTemp[node]) {
			for (auto v : vec) {
				mp[v]++; 
				maxi=max(maxi,mp[v]);
			}
		}
		for (auto p : mp) {
			int v=p.first;
			int f=p.second;
			if (f==maxi) {
				dominatorList[node].insert(v);
			}
		}
	}

	for (auto p : dominatorList) {
		int node=p.first;
		auto list=p.second;
		cout<<node<<" -> { ";
		for (auto x : list) {
			cout<<x<<" ";
		}
		cout<<" }"<<endl;
	}
	return 0;
}


