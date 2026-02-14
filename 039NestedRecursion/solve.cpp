#include<bits/stdc++.h>
using namespace std;
/*1、给定一个经过编码的字符串，返回它解码后的字符串。
编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。
你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。
此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。
*/
class Solution {
public:
    int where=0;
    string f(string &s,int i)
    {
        string cur;
        string later;
        int cnt=0;
        while(i<s.size()&&s[i]!=']')
        {
            if((s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z')) cur.push_back(s[i++]);
            else if(s[i]>='0'&&s[i]<='9') cnt=cnt*10+(s[i++]-'0');
            else
            {
                later=f(s,i+1);
                for(int j=0;j<cnt;j++) cur+=later;
                i=where+1;
                cnt=0;
            }
        }
        where=i;
        return cur;
    }
    string decodeString(string s) 
    {
        string ans;
        where=0;
        ans=f(s,0);
        return ans;
    }
};

/*2、原子的数量
给你一个字符串化学式 formula ，返回 每种原子的数量 。
原子总是以一个大写字母开始，接着跟随 0 个或任意个小写字母，表示原子的名字。
如果数量大于 1，原子后会跟着数字表示原子的数量。如果数量等于 1 则不会跟数字。
例如，"H2O" 和 "H2O2" 是可行的，但 "H1O2" 这个表达是不可行的。
两个化学式连在一起可以构成新的化学式。
例如 "H2O2He3Mg4" 也是化学式。
由括号括起的化学式并佐以数字（可选择性添加）也是化学式。
例如 "(H2O2)" 和 "(H2O2)3" 是化学式。
返回所有原子的数量，格式为：第一个（按字典序）原子的名字，跟着它的数量（如果数量大于 1），
然后是第二个原子的名字（按字典序），跟着它的数量（如果数量大于 1），以此类推。
*/
class Solution {
public:
    int where=0;
    map<string,int> g(string& formula,int i)
    {
        int cnt=0;
        map<string,int> omap;
        map<string,int> res;
        string name;
        while(i<formula.length()&&formula[i]!=')')
        {
            if((formula[i]>='A'&&formula[i]<='Z')||formula[i]=='(')
            {
                Fill(res,name,omap,cnt);
                name.clear();
                omap.clear();
                cnt=0;
                if(formula[i]>='A'&&formula[i]<='Z') name.push_back(formula[i++]);
                else
                {
                    omap=g(formula,i+1);
                    i=where+1;
                }
            } 
            else if(formula[i]>='a'&&formula[i]<='z') name.push_back(formula[i++]);
            else if(formula[i]>='0'&&formula[i]<='9') cnt=cnt*10+(formula[i++]-'0');
            
        }
        Fill(res,name,omap,cnt);
        where=i;
        return res;//递归，括号内结果作为外围的历史供调用
    }

    void Fill(map<string,int>& res,string& name,map<string,int> omap,int cnt)
    {
        if(name.length()>0||!omap.empty())
        {
            cnt=(cnt==0)?1:cnt;
            if(name.length()>0)
            {
                if(res.find(name)!=res.end()) res[name]+=cnt;
                else res.insert(pair<string,int>(name,cnt));
            }
            else
            {
                for(auto &entry:omap)
                {
                    if(res.find(entry.first)!=res.end()) res[entry.first]+=entry.second*cnt;
                    else res.insert(pair<string,int>(entry.first,entry.second*cnt));
                }
            }
        }
    }

    string countOfAtoms(string& formula) 
    {
        string ans;
        where=0;
        map<string,int> res=g(formula,0);
        for(const auto &entry:res)
        {
            ans+=entry.first;
            if(entry.second>1) ans+=to_string(entry.second);
        }
        return ans;
    }
};