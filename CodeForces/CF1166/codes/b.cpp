#include <bits/stdc++.h>
using namespace std;

string v = "aeiou";

string shift(string& s)
{
    string res = "";
    for(int i=0;i<(int)s.size();++i)
    {
        res += s[(i+1)%((int)s.size())];
    }
    return res;
}

int main()
{
    int k;
    cin >> k;
    for(int n=1;n*n<=k;++n)
    {
        if(k % n) continue;
        int m = k / n;
        if(n >= 5 && m >= 5)
        {
            string tmp = v;
            vector<vector<char>> mat(n, vector<char>(m));
            for(int i=0;i<5;++i)
            {
                for(int j=0;j<5;++j)
                    mat[i][j] = tmp[j];
                tmp = shift(tmp);
            }

            for(int i=5;i<n;++i)
            {
                for(int j=0;j<5;++j)
                    mat[i][j] = v[j];
                for(int j=5;j<m;++j)
                    mat[i][j] = 'b';
            }

            for(int i=5;i<m;++i)
            {
                for(int j=0;j<5;++j)
                    mat[j][i] = v[j];
            }

            string ans = "";
            for(auto& r: mat)
                for(char c: r)
                    ans += c;
            cout << ans << endl;

            return 0;
        }
    }

    cout << "-1\n";

    return 0;
}
