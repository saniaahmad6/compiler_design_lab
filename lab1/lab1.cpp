#include <bits/stdc++.h>
#include <fstream>
using namespace std;

int stringToInt(string line)
{
    int i = 0;
    int num = 0;
    while (line[i] != 0)
    {
        if (line[0] == '-')
        {
            return -1;
        }
        num *= 10;
        num += (line[i] - '0');
        i++;
    }
    return num;
}

int main()
{
    string line;
    fstream DFA("lab1_input.txt",ios::in);
    int i = 0;
    int initial;
    vector<int> final;
    set<int> ff;
    vector<vector<int>> table;

    while (getline(DFA, line))
    {
        if (i == 0)
            initial = stringToInt(line);
        else if (i == 1)
        {
            int x = 0;
            string num = "";
            while (line[x] != 0)
            {
                if (line[x] == ' ')
                {
                    final.push_back(stringToInt(num));
                    ff.insert(stringToInt(num));
                    num = "";
                    x++;
                    continue;
                }
                num += line[x++];
            }
            final.push_back(stringToInt(num));
            ff.insert(stringToInt(num));
        }
        else
        {
            vector<int> temp;
            int x = 0;
            string num = "";
            while (line[x] != 0)
            {
                if (line[x] == ' ')
                {
                    temp.push_back(stringToInt(num));
                    num = "";
                    x++;
                    continue;
                }
                num += line[x++];
            }
            temp.push_back(stringToInt(num));
            table.push_back(temp);
        }
        i++;
    }

    DFA.close();

    //------------PRINTING THE DFA----------
    cout << "\nInitial State : " << initial << "\n";
    cout << "\nFinal States : ";
    for (int i = 0; i < final.size(); i++)
        cout << final[i] << " ";
    cout << "\n\nTransition Table :\n";
    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 0; j < table[i].size(); j++)
        {
            cout << table[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    //------------------------
    int curr = initial;
    bool isAccepted = false;
    cout << "\nEnter String : ";
    string input;
    getline(cin, input);
    int size = input.size(), k = 0;
    while (curr != -1 && k < size)
    {
        int index = input[k++]-'a';
        if (index<0 or index>=26 ) {
            goto end;
        }
        curr = table[curr][index];
    }
    if (ff.count(curr) && k==size) {
        isAccepted=true;
    }
    end:
    if (isAccepted) cout << "String accepted \n";
    else cout << "String Rejected\n";

    return 0;
}