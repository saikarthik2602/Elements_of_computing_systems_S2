#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

// Bonagiri Sai Karthik

int match(string p);

int state(string l,string q,vector<string> &vardec_local);

int check_identifier(string m);

int check_let(string p,vector<string> &vardec_local);

int check_return(string s);

int check_do(string s);

int check_subr(string p);

int check_var(string s,vector<string> &vardec_local);

int check_subroutine(string p);

void comment(string p);

int check_if(string p,vector<string> &vardec_local);

int check_while(string p,vector<string> &vardec_local);

int check_else(string p,vector<string> &vardec_local);

int check_other(string p);

int check_ori(string p);


vector<string> vardec;

string s;

set<string> set1;

string lookhead;

int main_cnt;


std::string& ltrim(std::string& s)
{
	auto it = std::find_if(s.begin(), s.end(),
					[](char c) {
						return !std::isspace<char>(c, std::locale::classic());
					});
	s.erase(s.begin(), it);
	return s;
}

std::string& rtrim(std::string& s)
{
	auto it = std::find_if(s.rbegin(), s.rend(),
					[](char c) {
						return !std::isspace<char>(c, std::locale::classic());
					});
	s.erase(it.base(), s.end());
	return s;
}

std::string& trim(std::string& s)
{
	return ltrim(rtrim(s));
}


int match(string p)
{
	if(lookhead==p)
	{
		return 1;
	}
	else
	{
		return -1;
	}
	return 0;
}


int state(string l,string q,vector<string> &vardec_local)
{
	if(l=="while")
	{
		int rem = check_while(q,vardec_local);
		if(rem==-1)
		{
			cout<<"Error occured in the line "<<main_cnt<<endl;
			return -1;
		}
		else
		{
			return 1;
		}
	}
	else if(l=="if")
	{
		int rem = check_if(q,vardec_local);
		if(rem==-1)
		{
			cout<<"Error occured in the line "<<main_cnt<<endl;
			return -1;
		}
	}
	else if(l=="return")
	{
		int rem = check_return(q);
		if(rem==-1)
		{
			cout<<"Error occured in the line "<<main_cnt<<endl;
			return -1;
		}
		else
		{
			return 1;
		}
	}
	else if(l=="do")
	{
		int rem = check_do(q);

		if(rem==-1)
		{
			cout<<"Error occured in the line "<<main_cnt<<endl;
			return -1;
		}
		else
		{
			return 1;
		}
	}
	else if(l=="let")
	{
		int rem = check_let(q,vardec_local);
		if(rem==-1)
		{
			cout<<"Error occured in the line "<<main_cnt<<endl;
			return -1;
		}
		else
		{
			return 1;
		}
	}
	else if(l=="else")
	{
		int rem = check_else(q,vardec_local);
		if(rem==-1)
		{
			cout<<"Error occured in the line "<<main_cnt<<endl;
			return -1;
		}
		else
		{
			return 1;
		}
	}
	else if(l=="var")
	{
		int rem = check_var(q,vardec_local);

		// cout<<rem<<endl;

		// cout<<"In the line 168"<<endl;

		if(rem==-1)
		{
			cout<<"Error occured in the line "<<main_cnt<<endl;
			return -1;
		}
		else
		{
			return 1;
		}
	}
	return 0;
}


int check_identifier(string m)
{
	int rem = int(m[0]);
	if(rem>=48 && rem<=57)
	{
		return -1;
	}
	if(!((rem>=48 && rem<=57) || (rem>=65 && rem <=90) || (rem>=97 && rem<=122) || (rem==95)))
	{
		return -1;
	}

	for(int i=1;i<m.length();i++)
	{
		int rem = int(m[i]);
		if((rem>=48 && rem<=57) || (rem>=65 && rem <=90) || (rem>=97 && rem<=122) || (rem==95))
		{
			continue;
		}
		else
		{
			return -1;
		}
	}
	return 1;
}

int check_let(string p,vector<string> &vardec_local)
{
	stack<char> st;
	string g = "";
	int f=-1;
	for(int i=0;i<p.length();i++)
	{
		if(p[i]=='[')
		{
			st.push(p[i]);
			f=1;
			break;
		}
	}
	int i;
	for(i=3;i<p.length();i++)
	{
		if(p[i]!=' ')
		{
			break;
		}
	}
	if(f==1)
	{
		// cout<<"FIRST WITH [ "<<endl;

		string y="";
		for(int j=i;j<p.length();j++)
		{
			if(p[j]=='[')
			{
				break;
			}
			else
			{
				y=y+p[j];
			}
		}
		int check_1 = check_identifier(y);

		auto it1 = find(vardec.begin(),vardec.end(),y);

		if(check_1==-1)
		{
			return -1;
		}
		else if(it1 == vardec.end())
		{
			auto it2 = find(vardec_local.begin(),vardec_local.end(),y);

			if(it2 != vardec_local.end())
			{
				string m = "";
				int f1=-1;
				for(int j=i;j<p.length();j++)
				{
					if(p[j]=='[')
					{
						f1=1;
						break;
					}
					else
					{
						m=m+p[j];
					}
				}
				if(f1==1)
				{
					int check2 = check_identifier(m);
					if(check2==-1)
					{
						return -1;
					}
					else
					{
						stack<char> st;
					  	int f3=-1;
					  	int cnt=0;
					  	int cnt_equ=0;
					  	for(int i=0;i<p.length();i++)
					  	{
					  		if(p[i]=='[' || p[i]=='(')
					  		{
					  			st.push(p[i]);
					  		}
					  		if(p[i]==')')
					  		{
					  			if(st.empty()==true)
								{
									return -1;
								}
					  			if(st.top()=='(')
					  			{
					  				st.pop();
					  			}
					  			else
					  			{
					  				return -1;
					  			}
					  		}
					  		if(p[i]==']')
					  		{
					  			if(st.empty()==true)
								{
									return -1;
								}
					  			if(st.top()=='[')
					  			{
					  				st.pop();
					  			}
					  			else
					  			{
					  				return -1;
					  			}
					  		}
					  		if(p[i]=='=')
					  		{
					  			cnt_equ++;
					  		}
					  		if(p[i]==';')
					  		{
					  			if(st.empty()==true)
					  			{
					  				if(cnt==0 && f3==-1)
					  				{
					  					cnt++;
					  					f3=1;
					  				}
					  				else
					  				{
					  					cnt++;
					  				}
					  			}
					  			else
					  			{
					  				cnt++;
					  			}
					  		}
					  	}
					  	if(cnt==1 && cnt_equ==1)
					  	{
					  		return 1;
					  	}
					  	else
					  	{
					  		return -1;
					  	}
					}
				}
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
	}
	else
	{
		// cout<<"SECOND WITH OUT [] "<<endl;

		string m = "";
		int f1=-1;
		for(int j=i;j<p.length();j++)
		{
			if(p[j]=='=')
			{
				f1=1;
				break;
			}
			else if(p[j]==' ')
			{
				continue;
			}
			else
			{
				m=m+p[j];
			}
		}
		if(f1==1)
		{
			int check_2 = check_identifier(m);

			auto it1 = find(vardec.begin(),vardec.end(),m);
			
			if(check_2==-1)
			{
				// cout<<"WENT WRONG IN THIS LINE 611"<<endl;
				return -1;
			}
			else if(it1 == vardec.end())
			{
				// cout<<"Entered the line 401 the string is "<<m<<endl;
				
				auto it2 = find(vardec_local.begin(),vardec_local.end(),m);

				if(it2 != vardec_local.end())
				{
					// cout<<"Entered the line 407 "<<endl;

					int cnt_equ=0;
				  	stack<char> st;
				  	int f3=-1;
				  	int cnt=0;

				  	for(int i=0;i<p.length();i++)
				  	{
				  		if(p[i]=='=')
				  		{
				  			cnt_equ++;
				  		}
				  		if(p[i]=='[' || p[i]=='(')
				  		{
				  			st.push(p[i]);
				  		}
				  		if(p[i]==')')
				  		{
				  			if(st.empty()==true)
							{
								return -1;
							}
				  			if(st.top()=='(')
				  			{
				  				st.pop();
				  			}
				  			else
				  			{
								// cout<<"WENT WRONG IN THIS LINE 633"<<endl;
				  				return -1;
				  			}
				  		}
				  		if(p[i]==']')
				  		{
				  			if(st.empty()==true)
							{
								return -1;
							}
				  			if(st.top()=='[')
				  			{
				  				st.pop();
				  			}
				  			else
				  			{
				  				// cout<<"WENT WRONG IN THIS LINE 645"<<endl;
				  				return -1;
				  			}
				  		}
				  		if(p[i]==';')
				  		{
				  			if(st.empty()==true)
				  			{
				  				if(cnt==0 && f3==-1)
				  				{
				  					cnt++;
				  					f3=1;
				  				}
				  				else
				  				{
				  					cnt++;
				  				}
				  			}
				  			else
				  			{
				  				cnt++;
				  			}
				  		}
				  	}
				  	if(cnt==1 && cnt_equ==1)
				  	{
				  		return 1;
				  	}
				  	else
				  	{
				  		// cout<<cnt<<endl;
				  		// cout<<st.size()<<endl;
				  		// cout<<"WENT WRONG IN THIS LINE 672"<<endl;
				  		return -1;
				  	}
				}
				else
				{
					// cout<<"Entered the line 489 "<<endl;
					return -1;
				}
			}
			else if(it1 != vardec.end())
			{

				int cnt_equ=0;
				stack<char> st;
				int f3=-1;
				int cnt=0;

				for(int i=0;i<p.length();i++)
				{
					if(p[i]=='=')
					{
						cnt_equ++;
					}
					if(p[i]=='[' || p[i]=='(')
					{
						st.push(p[i]);
					}
					if(p[i]==')')
					{
						if(st.empty()==true)
					{
						return -1;
					}
						if(st.top()=='(')
						{
							st.pop();
						}
						else
						{
							return -1;
						}
					}
					if(p[i]==']')
					{
						if(st.empty()==true)
					{
						return -1;
					}
						if(st.top()=='[')
						{
							st.pop();
						}
						else
						{
							return -1;
						}
					}
					if(p[i]==';')
					{
						if(st.empty()==true)
						{
							if(cnt==0 && f3==-1)
							{
								cnt++;
								f3=1;
							}
							else
							{
								cnt++;
							}
						}
						else
						{
							cnt++;
						}
					}
				}
				if(cnt==1 && cnt_equ==1)
				{
					return 1;
				}
				else
				{
					return -1;
				}
			}
		}
		else
		{
			return -1;
		}
	}
	return 0;
}

int check_return(string s)
{
	stack<char> st;
	int cnt=0;
	for(int i=0;i<s.length();)
	{
		if(s[i]=='/')
		{
			if(s[i+1]=='/')
			{
				return 1;
			}
			if(s[i+1]=='*')
			{
				int j;
				for(j=i;j<s.length()-1;j++)
				{
					if(s[j]=='*' && s[j+1]=='/')
					{
						i=j;
						break;
					}
				}
			}
		}

		if(s[i]=='(' || s[i]=='{' || s[i]=='[')
		{
			st.push(s[i]);
		}
		if(s[i]==')')
		{
			if(st.empty()==true)
			{
				return -1;
			}
			if(st.top()=='(')
			{
				st.pop();
			}
			else
			{
				return -1;
			}
		}
		if(s[i]=='}')
		{
			if(st.empty()==true)
			{
				return -1;
			}
			if(st.top()=='{')
			{
				st.pop();
			}
			else
			{
				return -1;
			}
		}
		if(s[i]==']')
		{
			if(st.empty()==true)
			{
				return -1;
			}
			if(st.top()=='[')
			{
				st.pop();
			}
			else
			{
				return -1;
			}
		}
		if(s[i]==';')
		{
			if(st.empty()==true)
			{
				cnt++;
			}
			else
			{
				cnt++;
			}
		}
		i++;         
	}
	if(cnt==1 && st.empty()==true)
	{
		return 1;
	}
	else
	{
		return -1;
	}
	return 0;
}

int check_do(string s)
{
	string p = "";
	int i;
	int f=-1;
	int cnt_semi = 0;
	for(i=2;i<s.length();i++)
	{ 
		if(s[i]!=' ')
		{
			break;
		}
	}
	for(int j=i;j<s.length();j++)
	{
		if(s[j]==';')
		{
			p=p+s[j];
			f=1;
			break;
		}
		else
		{
			p=p+s[j];
		}
	}
	if(f==1)
	{
		int y = check_subr(p);
		if(y==1)
		{
			stack<char> st;
			for(int i=0;i<s.length();)
			{
				if(s[i]=='/')
				{
					if(s[i+1]=='/')
					{
						return 1;
					}
					if(s[i+1]=='*')
					{
						int j;
						for(j=i;j<s.length()-1;j++)
						{
							if(s[j]=='*' && s[j+1]=='/')
							{
								i=j;
								break;
							}
						}
					}
				}


				if(s[i]=='(' || s[i]=='{' || s[i]=='[')
				{
					st.push(s[i]);
				}
				if(s[i]==')')
				{
					if(st.empty()==true)
					{
						return -1;
					}
					if(st.top()=='(')
					{
						st.pop();
					}
					else
					{
						return -1;
					}
				}
				if(s[i]=='}')
				{
					if(st.empty()==true)
					{
						return -1;
					}
					if(st.top()=='{')
					{
						st.pop();
					}
					else
					{
						return -1;
					}
				}
				if(s[i]==']')
				{
					if(st.empty()==true)
					{
						return -1;
					}
					if(st.top()=='[')
					{
						st.pop();
					}
					else
					{
						return -1;
					}
				}
				if(s[i]==';')
				{
					cnt_semi++;
				}
				i++;
			} 
			if(st.empty()==true)
			{
				if(cnt_semi==1)
				{
					return 1;
				}
				else
				{
					return -1;
				}
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
	return 0;
}

int check_subr(string p)
{
	// cout<<p<<endl;

	int f=-1;
	int f2=-1;
	for(int i=0;i<p.length();i++)
	{
		if(p[i]=='(')
		{
			f2=1;
		}
		if(p[i]=='.' && f2==-1)
		{
			f=1;
			break;
		}
	}

	if(f==1)
	{
		string m = "";
		int i;
		for(i=0;i<p.length();i++)
		{
			if(p[i]=='.')
			{
				break;
			}
			else
			{
				m=m+p[i];
			}
		}
		/*cout<<"IN 337 LINE"<<endl;
		cout<<m<<endl;*/
		int first_char = check_identifier(m);
		
		if(first_char==-1)
		{
			// cout<<"Not correct"<<endl;
			return -1;
		}

		int f3=-1;
		string second = "";
		int j;
		for(j=i+1;j<p.length();j++)
		{
			if(p[j]=='(')
			{
				f3=1;
				break;
			}	
			else
			{
				second = second+p[j];
			}
		}
		if(f3==1)
		{
			/*cout<<"IN THE 363 LINE"<<endl;
			cout<<second<<endl;*/
			int f_chart = check_identifier(second);
			if(f_chart==-1)
			{
				return -1;
			}
			int f4=1;

			for(int k=j;k<p.length();k++)
			{
				if(p[k]==';')
				{
					if(p[k-1]==')')
					{
						f4++;
						break;
					}
				}
			}

			if((f4)!=2)
			{
				return -1;
			}
			else
			{
				return 1;
			}
		}
		else
		{
			return -1;
		}
	}
	else
	{
		int j;
		string u="";
		int f=-1;
		for(j=0;j<p.length();j++)
		{
			if(p[j]=='(')
			{
				f=1;
				break;
			}
			else
			{
				u=u+p[j];
			}
		}
		if(f==1)
		{
			int req = check_identifier(u);
 
			/* cout<<req<<" In the line 907"<<endl;
			cout<<u<<endl; */

			if(req==-1)
			{
				return -1;
			}
			else
			{
				stack<char> st;
				for(int i=0;i<p.length();i++)
				{
					if(p[i]=='(' || p[i]=='[' || p[i]=='{')
					{
						st.push(p[i]);
					}
					if(p[i]==')')
					{
						if(st.empty()==true)
						{
							return -1;
						}
						if(st.top()=='(')
						{
							st.pop();
						}
						else
						{
							return -1;
						}
					}
					if(p[i]=='}')
					{
						if(st.empty()==true)
						{
							return -1;
						}
						if(st.top()=='{')
						{
							st.pop();
						}
						else
						{
							return -1;
						}
					}
					if(p[i]==']')
					{
						if(st.empty()==true)
						{
							return -1;
						}
						if(st.top()=='[')
						{
							st.pop();
						}
						else
						{
							return -1;
						}
					}
				}
				if(st.empty()==true)
				{
					return 1;
				}
				else
				{
					return -1;
				}
			}
		}
		else
		{
			return -1;
		}
	}
	return 0;
}

int check_other(string s)
{
	int f1=-1;
	int cnt_semi=0;
	string p = "";
	int i;

	for(i=0;i<s.length();i++)
	{
		if(s[i]==' ')
		{
			f1=1;
			break;
		}
		else
		{
			p=p+s[i];
		}
	}

	if(f1==1)
	{
		string req = "";

		int j;
		
		int f3 = -1;

		for(j=i+1;j<s.length();j++)
		{
			if(s[j]==' ')
			{
				f3=1;
				break;
			}
			else
			{
				req = req+s[j];
			}
		}
		
		if(f3==1)
		{
			int second = check_identifier(req);

			if(second==-1)
			{
				return -1;
			} 
			
			else
			{
				int cnt_semi=0;

				string q="";
				
				int f2=-1;
				
				for(int k=j+1;k<s.length();k++)
				{
					if(s[k]==';')
					{
						cnt_semi++;
					}
					else if(s[k]==',')
					{
						f2 = 1;
						int g = check_identifier(q);
						if(g==-1)
						{
							return -1;
						}
						else
						{
							auto it = find(vardec.begin(),vardec.end(),q);

							if(it!=vardec.end())
							{
								return -1;
							}
							else
							{
								vardec.push_back(q);
							}
						}
						q="";
					}
					else
					{
						q=q+s[k];
					}
				}
				if(cnt_semi==1)
				{
					if(f2==1)
					{
						int g = check_identifier(q);
						if(g==-1)
						{
							return -1;
						}
						else
						{
							auto it1 = find(vardec.begin(),vardec.end(),q);
							if(it1 != vardec.end())
							{
								return -1;
							}
							else
							{
								vardec.push_back(q);
								return 1;
							}
						}
					}
					else
					{
						int g = check_identifier(q);

						if(g==-1)
						{
							return -1;
						}
						auto it1 = find(vardec.begin(),vardec.end(),q);

						if(it1 != vardec.end())
						{
							return -1;
						}
						else
						{
							vardec.push_back(q);
							return 1;
						}
					}
				}
			}
		}
		else
		{
			return -1;
		}
	}
	return 0;
}

int check_var(string s,vector<string> &vardec_local)
{
	int f1=-1;
	
	int cnt_semi=0;

	string p = "";

	int i;
	
	for(i=0;i<s.length();i++)
	{
		if(s[i]==' ')
		{
			break;
		}
		else
		{
			p=p+s[i];
		}
	}

	if(p=="var")
	{
		f1=1;
	}

	if(f1==1)
	{
		string req = "";

		int j;
		
		int f3 = -1;

		for(j=i+1;j<s.length();j++)
		{
			if(s[j]==' ')
			{
				f3=1;
				break;
			}
			else
			{
				req = req+s[j];
			}
		}
		
		if(f3==1)
		{
			int second = check_identifier(req);

			if(second==-1)
			{
				return -1;
			} 
			
			else
			{
				int cnt_semi=0;

				string q="";
				
				int f2=-1;
				
				for(int k=j+1;k<s.length();k++)
				{
					if(s[k]==';')
					{
						cnt_semi++;
					}
					else if(s[k]==',')
					{
						f2 = 1;
						int g = check_identifier(q);
						if(g==-1)
						{
							return -1;
						}
						else
						{
							auto it = find(vardec_local.begin(),vardec_local.end(),q);

							if(it!=vardec_local.end())
							{
								return -1;
							}
							else
							{
								vardec_local.push_back(q);
							}
							q="";
						}
					}
					else
					{
						q=q+s[k];
					}
				}
				if(cnt_semi==1)
				{
					if(f2==1)
					{
						int g = check_identifier(q);
						if(g==-1)
						{
							return -1;
						}
						else
						{
							auto it1 = find(vardec_local.begin(),vardec_local.end(),q);
							if(it1 != vardec_local.end())
							{
								return -1;
							}
							else
							{
								vardec_local.push_back(q);
								return 1;
							}
						}
					}
					else
					{
						int g = check_identifier(q);

						if(g==-1)
						{
							return -1;
						}
						auto it1 = find(vardec_local.begin(),vardec_local.end(),q);

						if(it1 != vardec_local.end())
						{
							return -1;
						}
						else
						{
							vardec_local.push_back(q);
							return 1;
						}
					}
				}
			}
		}
		else
		{
			return -1;
		}
	}
	return 0;
}

int check_ori(string p)
{
	vector<string> v;
	string ps = "";
	for(int i=0;i<p.length();i++)
	{
		if(p[i]==',')
		{
			v.push_back(ps);
			ps="";
		}
		else
		{
			ps=ps+p[i];
		}
	}
	v.push_back(ps);
	for(int i=0;i<v.size();i++)
	{
		string pqr = trim(v[i]);
		string first = "";
		vector<string> dummyv;
		for(int j=0;j<pqr.length();j++)
		{
			if(pqr[j]==' ')
			{
				int rem=check_identifier(first);
				if(rem==-1)
				{
					return rem;
				}
				dummyv.push_back(first);
				first="";
			}
			else
			{
				first+=pqr[j];
			}
		}
		int rem=check_identifier(first);
		if(rem==-1)
		{
			return -1;
		}
		dummyv.push_back(first);
		first="";
		/*  for(int k=0;k<dummyv.size();k++)
		{
			cout<<dummyv[k]<<endl;
		} */
		if(dummyv.size()!=2)
		{
			return -1;
		}
	}
	return 0;
}

int check_subroutine(string p)
{
	stack<char> st;

	vector<string> vardec_local;
	
	int f=-1;

	vector<string> v_pattern;

	string key = "";

	for(int i=0;i<p.length();i++)
	{
		if(p[i]=='(')
		{
			break;
		}
		else if(p[i]==' ')
		{
			if(key=="")
			{
				continue;
			}
			else
			{
				key = key+p[i]; 
			}
		}
		else
		{ 
			if(p[i]!=' ')
			{
				if(p[i-1]==' ')
				{
					// cout<<key<<endl;
				
					v_pattern.push_back(key);
					
					key = "";

					key = key+p[i];
				}
				else
				{
					key = key+p[i];
				}
			}
		}
	}
	v_pattern.push_back(key);

	if(v_pattern.size()==3)
	{
		for(int i=0;i<v_pattern.size();i++)
		{
			string qw = trim(v_pattern[i]);

			// cout<<"After trim "<<qw<<endl;
			
			int ui = check_identifier(qw);
			
			if(ui==-1)
			{
				return -1;
			}
		}
	}
	else
	{
		return -1;
	}

	for(int i=0;i<p.length();i++)
	{
		if(p[i]=='/')
		{
			if(p[i+1]=='/')
			{
				break;
			}
		}
		if(p[i]=='(' || p[i]=='[')
		{
			st.push(p[i]);
		}
		if(p[i]=='{')
		{
			f=1;
			if(st.empty()==true)
			{
				st.push(p[i]);
			}
			else
			{
				return -1;
			}
		}
		if(p[i]==')')
		{
			if(st.empty()==true)
			{
				return -1;
			}
			else if(st.top()=='(')
			{
				st.pop();
			}
			else
			{
				return -1;
			}
		}
		if(p[i]==']')
		{
			if(st.empty()==true)
			{
				return -1;
			}
			else if(st.top()=='[')
			{
				st.pop();
			}
			else
			{
				return -1;
			}
		}
	}

	int i;

	int flag1=-1;

	for(i=0;i<p.length();i++)
	{
		if(p[i]=='(')
		{
			flag1 = 1;
			break;
		}
	}
	if(flag1==-1)
	{
		return -1;
	} 
	else
	{
		string main = "";
		string answ = "";
		for(int j=i+1;j<p.length();j++)
		{
			if(s[j]==')')
			{
				break;
			}
			else
			{
				main = main+s[j];
			}
		}

		string ori = trim(main);

		if(ori=="")
		{

		}
		else
		{
			int dummy = check_ori(ori);

			if(dummy==-1)
			{
				return -1;
			}
		}
	}

	if(f==1)
	{
		while(getline(cin,s))
		{
			main_cnt++;
			string present = trim(s);

			if(present=="}")
			{
				if(st.empty()==true)
				{
					return -1;
				}
				else if(st.top()=='{' && st.size()==1)
				{
					st.pop();
					return 1;
				}
				else
				{
					return -1;
				}
			}
			string h = "";

			for(int i=0;i<present.length();i++)
			{
				h = h + present[i];
				auto it = set1.find(h);
				if(it!=set1.end())
				{
					int answer = state(h,present,vardec_local);
					if(answer==-1)
					{
						return -1;
					}
					break;
				}
			}
		}
	}
	else
	{
		int f1 = -1;
		while(getline(cin,s))
		{
			main_cnt++;

			string present = trim(s);
			if(present=="{")
			{
				f1=1;
				if(st.empty()==true)
				{
					char l = '{';
					st.push(l);
				}
				else
				{
					return -1;
				}
			}
			break;
		}
		if(f1==-1)
		{
			return -1;
		}
		else
		{
			while(getline(cin,s))
			{
				main_cnt++;

				string present = trim(s);

				if(present=="}")
				{
					if(st.empty()==true)
					{
						return -1;
					}
					else if(st.top()=='{' && st.size()==1)
					{
						return 1;
					}
					else
					{
						return -1;
					}
				}

				else
				{
					string h = "";

					for(int i=0;i<present.length();i++)
					{
						h = h + present[i];
						auto it = set1.find(h);
						if(it!=set1.end())
						{
							int answer = state(h,present,vardec_local);
							if(answer==-1)
							{
								// return -1;
							}
							break;
						}
					}
				}
			}
		}
	}
	return 0;
}


void comment(string p)
{
	for(int i=0;i<p.length()-1;i++)
	{
		if(p[i]=='*' && p[i+1]=='/')
		{ 
			return;
		}	
	}
	while(getline(cin,s))
	{
		main_cnt++;
		string p = trim(s);
		for(int i=0;i<p.length()-1;i++)
		{
			if(p[i]=='*' && p[i+1]=='/')
			{ 
				return;
			}
		}	
	}
}

int check_if(string p,vector<string> &vardec_local)
{
	stack<char> st;
	int i;
	for(i=2;i<p.length();i++)
	{
		if(p[i]!=' ')
		{
			lookhead = p[i];
			break;
		}
	}
	
	string need = "(";

	int req = match(need);
	
	// cout<<"Check for open bracket ( "<<endl;

	// cout<<req<<endl;
	
	if(req==-1)
	{
		return -1;
	}
	else
	{
		// stack<char> st;
		int f1=-1;
		for(int i=0;i<p.length();i++)
		{
			if(p[i]=='(' || p[i]=='[')
			{
				st.push(p[i]);
			}
			if(p[i]=='{')
			{
				if(st.empty()==true)
				{
					f1=1;
					st.push(p[i]);
				}
				else
				{
					return -1;
				}
			}
			if(p[i]==')')
			{
				if(st.empty()==true)
				{
					return -1;
				}
				if(st.top()=='(')
				{
					st.pop();
				}
				else
				{
					return -1;
				}
			}
			if(p[i]==']')
			{
				if(st.empty()==true)
				{
					return -1;
				}
				if(st.top()=='[')
				{
					st.pop();
				}
				else
				{
					return -1;
				}
			}
		} 		
		if(f1==1)
		{
			while(getline(cin,s))
			{
				main_cnt++;
				
				if(s=="")
				{
					// cout<<"blank line entered"<<endl;
					return -1;
				}

				string p = trim(s);
				if(p[0]=='/' && p[1]=='/')
				{
					// cout<<"First if condition"<<endl;
					return -1;
				}
				if(p[0]=='/' && p[1]=='*')
				{
					// cout<<"Second if condition"<<endl;
					return -1;
					comment(p);
				}


				string q = trim(s);

				for(int i=0;i<q.length();)
				{

					if(q[i]=='}')
					{
						if(st.empty()==true)
						{
							return -1;
						}
						if(st.top()=='{' && st.size()==1)
						{
							st.pop();
							return 1;
						}
					}
					i++;
				}

				string l = "";

				
				for(int i=0;i<q.length();i++)
				{
					l=l+q[i];
					auto it = set1.find(l);
					if(it!=set1.end())
					{
						int answer = state(l,q,vardec_local);
						if(answer==-1)
						{
							// return -1;
						}
						break;
			 		}
				}
			}
	 	}  
	 	else
	 	{
	 		// stack<char> st;

	 		int f1=-1;

	 		while(getline(cin,s))
	 		{
	 			main_cnt++;
	 			
	 			if(s=="")
				{
					// cout<<"blank line entered"<<endl;
					return -1;
				}
				else
				{
					string p = trim(s);
					if(p[0]=='/' && p[1]=='/')
					{
						// cout<<"First if condition"<<endl;
						return -1;
					}
					else if(p[0]=='/' && p[1]=='*')
					{
						// cout<<"Second if condition"<<endl;
						return -1;
						comment(p);
					}
					else
					{
						lookhead = p[0];
						string need = "{";

						int req = match(need);
						if(req==-1)
						{
							return -1;
						}
						else
						{
							if(st.empty()==true)
							{
								st.push(p[0]);
								f1=1;
							}
							else
							{
								return -1;
							}
						}
						break;
					}
				}	
	 		}
	 		/* cout<<"THE STACK SIZE IS"<<endl;
	 		cout<<st.size()<<endl; */

	 		// the stack size is 1
	 		
	 		if(f1==-1)
	 		{
	 			return -1;
	 		}
	 		else
	 		{
		 		while(getline(cin,s))
				{
					main_cnt++;
					string q = trim(s);


					/*cout<<"THE STRING AFTER TRIM IN IF IS"<<endl;

					cout<<q<<endl;

					cout<<q.size()<<endl;
					
					cout<<"tHe sTAck size iS"<<endl;

					cout<<st.size()<<endl;*/

					if(s=="")
					{
						// cout<<"blank line entered"<<endl;
						return -1;
					}

					string p = trim(s);
					if(p[0]=='/' && p[1]=='/')
					{
						// cout<<"First if condition"<<endl;
						return -1;
					}
					if(p[0]=='/' && p[1]=='*')
					{
						// cout<<"Second if condition"<<endl;
						return -1;
						comment(p);
					}


					if(q[0]=='}')
					{
						if(st.empty()==true)
						{
							return -1;
						}
						if(st.top()=='{')
						{
							st.pop();
							return 1;
						}
						else
						{
							return -1;
						}
					}
					

					string l = "";
					for(int i=0;i<q.length();i++)
					{
						l=l+q[i];
						auto it = set1.find(l);
						if(it!=set1.end())
						{
							int answer = state(l,q,vardec_local);
							if(answer==-1)
							{
								// return -1;
							}
							break;
				 		}
					}
				}
	 		}
	 	}
	}
	return 0;
}

int check_while(string p,vector<string> &vardec_local)
{
	string g="";
	int f=-1;
	for(int i=5;i<p.length();i++)
	{
		if(p[i]!=' ')
		{
			/*cout<<"The first character after the while is !!! "<<endl;
			cout<<p[i]<<endl;*/
			lookhead = p[i];
			break;
		}
	}
	string required = "(";
	int y = match(required);

	// cout<<"The value after the match with ( with the lookhead is "<<y<<endl;

	if(y==-1)
	{
		return -1;
	}
	else
	{

		stack<char> st;
		int f1=-1;
		for(int i=0;i<p.length();i++)
		{
			if(p[i]=='(' || p[i]=='[')
			{
				st.push(p[i]);
			}
			if(p[i]==')')
			{
				if(st.empty()==true)
				{
					return -1;
				}
				if(st.top()=='(')
				{
					st.pop();
				}
			}
			if(p[i]==']')
			{
				if(st.empty()==true)
				{
					return -1;
				}
				if(st.top()=='[')
				{
					st.pop();
				}
			}
			if(p[i]=='{')
			{
				if(st.empty()==true)
				{
					f1=1;
					st.push(p[i]);
				}
				else
				{
					return -1;
				}
			}
		} 		
		if(f1==1)
		{
			while(getline(cin,s))
			{
				main_cnt++;
				if(s=="")
				{
					// cout<<"blank line entered"<<endl;
					return -1;
				}

				string q = trim(s);

				if(q[0]=='/' && q[1]=='/')
				{
					// cout<<"First if condition"<<endl;
					return -1;
				}
				if(q[0]=='/' && q[1]=='*')
				{
					// cout<<"Second if condition"<<endl;
					return -1;
					comment(q);
				}

				for(int i=0;i<q.length();)
				{

					if(q[i]=='}')
					{
						if(st.empty()==true)
						{
							return -1;
						}
						if(st.top()=='{' && st.size()==1)
						{
							st.pop();
							return 1;
						}
					}
					i++;
				}

				string l = "";
				int present = -1;
						
				for(int i=0;i<q.length();i++)
				{
					l=l+q[i];
					auto it = set1.find(l);
					if(it!=set1.end())
					{
						present = 1;
						int answer = state(l,q,vardec_local);
						if(answer==-1)
						{
							// return -1;
						}
						break;
			 		}
				}
			}
	 	}
	 	else
	 	{
	 		// stack<char> st;

			int f1=-1;

			while(getline(cin,s))
			{
				main_cnt++;
				if(s=="")
				{
					// cout<<"blank line entered"<<endl;
					return -1;
				}

				else
				{
					string p = trim(s);
					if(p[0]=='/' && p[1]=='/')
					{
						// cout<<"First if condition"<<endl;
						return -1;
					}
					else if(p[0]=='/' && p[1]=='*')
					{
						// cout<<"Second if condition"<<endl;
						return -1;
						comment(p);
					}
					else
					{
						lookhead = p[0];
						string need = "{";

						int req = match(need);
						if(req==-1)
						{
							return -1;
						}
						else
						{

							if(st.empty()==true)
							{
								f1=1;
								st.push(p[0]);
							}
							else
							{
								return -1;
							}
						}
						break;
					}
				}	
			}
			if(f1==-1)
			{
				return -1;
			}
			else
			{
				while(getline(cin,s))
				{
					main_cnt++;

					/* cout<<"ENTERED THE ELSE PART THE STRING IS"<<endl;
					
					cout<<s<<endl; */
					
					string q = trim(s);

					if(q=="")
					{
						// cout<<"IT IS NOT  CORRECT $%"<<endl;
						return -1;
					}

					if(q[0]=='/' && q[1]=='/')
					{
						// cout<<"First if condition"<<endl;
						return -1;
					}
					else if(q[0]=='/' && q[1]=='*')
					{
						// cout<<"Second if condition"<<endl;
						return -1;
						comment(q);
					}
					/*cout<<"THE STRING AFTER TRIM IN IF IS"<<endl;

					cout<<q<<endl;

					cout<<q.size()<<endl;
					
					cout<<"tHe sTAck size iS"<<endl;

					cout<<st.size()<<endl;*/


					if(q[0]=='}')
					{
						if(st.empty()==true)
						{
							return -1;
						}
						if(st.top()=='{')
						{
							st.pop();
							return 1;
						}
						else
						{
							return -1;
						}
					}
					

					string l = "";
					int present = -1;
					for(int i=0;i<q.length();i++)
					{
						l=l+q[i];
						auto it = set1.find(l);
						if(it!=set1.end())
						{
							present = 1;
							int answer = state(l,q,vardec_local);
							if(answer==-1)
							{
								// return -1;
							}
							break;
				 		}
					}
				}
			}
	 	}  
	}
	return 0;
}


int check_else(string p,vector<string> &vardec_local)
{
	
	stack<char> st;
	int i;
	
	if(p.size()==4)
	{
		// stack<char> st;

 		int f1=-1;

 		while(getline(cin,s))
 		{
 			main_cnt++;
 			if(s=="")
			{
				// cout<<"blank line entered"<<endl;
				return -1;
			}
			else
			{
				string p = trim(s);
				if(p[0]=='/' && p[1]=='/')
				{
					// cout<<"First if condition"<<endl;
					return -1;
				}
				else if(p[0]=='/' && p[1]=='*')
				{
					// cout<<"Second if condition"<<endl;
					return -1;
					comment(p);
				}
				else
				{
					lookhead = p[0];
					string need = "{";

					int req = match(need);
					if(req==-1)
					{
						return -1;
					}
					else
					{
						if(st.empty()==true)
						{
							st.push(p[0]);
							f1=1;
						}
					}
					break;
				}
			}	
 		}
 		/* cout<<"THE STACK SIZE IS"<<endl;
 		cout<<st.size()<<endl; */

 		// the stack size is 1
 		
 		if(f1==-1)
 		{
 			return -1;
 		}
 		else
 		{
	 		while(getline(cin,s))
			{
				main_cnt++;
				
				string q = trim(s);

				/*cout<<"THE STRING AFTER TRIM IN IF IS"<<endl;

				cout<<q<<endl;

				cout<<q.size()<<endl;
				
				cout<<"tHe sTAck size iS"<<endl;

				cout<<st.size()<<endl;*/

				if(q=="")
				{
					// cout<<"blank line entered"<<endl;
					return -1;
				}

				if(q[0]=='/' && q[1]=='/')
				{
					// cout<<"First if condition"<<endl;
					return -1;
				}
				else if(q[0]=='/' && q[1]=='*')
				{
					// cout<<"Second if condition"<<endl;
					return -1;
					comment(q);
				}


				if(q[0]=='}')
				{
					if(st.empty()==true)
					{
						return -1;
					}
					if(st.top()=='{')
					{
						st.pop();
						return 1;
					}
					else
					{
						return -1;
					}
				}
				
				string l = "";

				int present=-1;
				
				for(int i=0;i<q.length();i++)
				{
					l=l+q[i];
					auto it = set1.find(l);

					if(it!=set1.end())
					{
						present = 1;
						int answer = state(l,q,vardec_local);
						if(answer==-1)
						{
							// return -1;
						}
						break;
			 		}
				}
				if(present==-1)
				{
					return -1;
				}
			}
	 	}
	}
 	
 	else
	{
		stack<char> st;
		int f1=-1;
		for(int i=0;i<p.length();i++)
		{
			if(p[i]=='(' || p[i]=='[')
			{
				st.push(p[i]);
			}
			if(p[i]=='{')
			{
				if(st.empty()==true)
				{
					f1=1;
					st.push(p[i]);
				}
				else
				{
					return -1;
				}
			}
		} 		
		if(f1==1)
		{
			while(getline(cin,s))
			{
				main_cnt++;
				string q = trim(s);
				for(int i=0;i<q.length();)
				{

					if(q[i]=='}')
					{
						if(st.empty()==true)
						{
							return -1;
						}
						if(st.top()=='{' && st.size()==1)
						{
							st.pop();
							return 1;
						}
						else
						{
							return -1;
						}
					}
					else
					{
						return -1;
					}
					i++;
				}
				int present = -1;
				string l = "";
				for(int i=0;i<q.length();i++)
				{
					l=l+q[i];
					auto it = set1.find(l);

					if(it!=set1.end())
					{
						present = 1;
						int answer = state(l,q,vardec_local);
						if(answer==-1)
						{
							// return -1;
						}
						break;
			 		}
				}
				if(present==-1)
				{
					return -1;
				}
			}
	 	}  
	 	else
	 	{
	 		return -1;
	 	}
	}
	return 0;	
}


int main(void)
{
	set1.insert("do");
	set1.insert("return");
	set1.insert("while");
	set1.insert("let");
	set1.insert("if");
	set1.insert("else");
	set1.insert("var");

	freopen("Main2.jack","r",stdin);	

	stack<char> stack_1;

	while(getline(cin,s))
	{
		main_cnt++;

		string p = trim(s);

		int flag=-1;

		if(p=="{")
		{
			flag=1;
			char c = '{';
			stack_1.push(c);
		}
		else if(p=="}")
		{
			flag=1;
			if(stack_1.empty()==true)
			{
				return -1;
			}
			else if(stack_1.top()=='{' && stack_1.size()==1)
			{
				stack_1.pop();
			}
		}
		else if(p=="")
		{
			flag=1;
			continue;
		}
		else if(p[0]=='/')
		{
			flag=1;
			if(p[1]=='/')
			{
				continue;
			}
		}
		else if(p[0]=='/' && p[1]=='*')
		{
			flag=1;
			comment(p);
			continue;
		}
		else
		{
			string h = "";

			for(int i=0;i<p.length();i++)
			{
				h = h + p[i];
				if(h=="class")
				{
					flag=1;

					string check_class = "";
					
					for(int j=i+1;j<p.length();j++)
					{
						check_class += p[j];
					}

					int ans = check_identifier(trim(check_class));
					
					if(ans==-1)
					{
						cout<<"Error occured in the line "<<main_cnt<<endl;
						return -1;
					}
					else
					{
						continue;
					}
					break;
				}
				if(h=="function" || h=="method" || h=="constructor")
				{
					flag = 1;
					int rem = check_subroutine(p);
					if(rem==-1)
					{
						cout<<"Error occured in the line "<<main_cnt<<endl;
						return -1;
					}
					break;
				}
				if(h=="static" || h=="field")
				{
					flag = 1;
					int rem = check_other(p);
					if(rem==-1)
					{
						cout<<"Error occured in the line "<<main_cnt<<endl;
						return -1;
					}
					break;
				}
			}
		}
		if(flag==-1)
		{
			cout<<"Error occured in the line "<<main_cnt<<endl;
			cout<<"The line did not match the grammar"<<endl;
			return -1;
		}
	}
}