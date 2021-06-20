#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<bits/stdc++.h>
using namespace std;
int checkpara(string temp)
{
	int lc=0;
	string str;
	char word[50];
	ifstream pnt;
	pnt.open("pnttab.txt");
	while(pnt.getline(word,50))
	{
		lc++;
		stringstream iss(word);
		while(iss>>str)
		{
			if(str==temp)
				return lc-2;
		}
	}
	pnt.close();
	return 0;
}
int checkevn(string temp)
{
	int lc=0;
	string str;
	char word[50];
	ifstream evn;
	evn.open("evntab.txt");
	while(evn.getline(word,50))
	{
		lc++;
		stringstream iss(word);
		while(iss>>str)
		{
			if(str==temp)
				return lc-2;
		}
	}
	evn.close();
	return 0;
}
int checklab(string temp)
{
	int lc=0;
	string str;
	char word[50];
	ifstream sst;
	sst.open("ssttab.txt");
	while(sst.getline(word,50))
	{
		lc++;
		stringstream iss(word);
		while(iss>>str)
		{
			if(str==temp)
				return lc-2;
		}
	}
	sst.close();
	return 0;
}
int main()
{
	string temp;
	char word[50],line[50];
	int pp=0, kp=0, ev=0, mdtp=1, sstp=1, kpdtp=1, cnt=0, lc=0, sscnt=0;
	ifstream mac;
	ofstream mnt, pnt, kpdt, evn, sst, mdt;
	mac.open("macrotest2.txt");
	mnt.open("mnttab.txt");
	mnt<<"Macroname\t#PP\t#KP\t#EV\tMDTP\tSSTP\tKPDTP\n\n";
	pnt.open("pnttab.txt");
	pnt<<"Parameter name\n\n";
	kpdt.open("kpdtab.txt");
	kpdt<<"Default\tValue\n\n";
	evn.open("evntab.txt");
	evn<<"Expr Variable\n\n";
	sst.open("ssttab.txt");
	sst<<"Label\tLC\n\n";
	while(mac.getline(line,50))
	{
		stringstream lin(line);
		while(lin>>temp)
		{
			sscnt++;
			if(temp=="MACRO")
			{	
				lc=1;
				mac.getline(word,50);
				stringstream iss(word);
				while(iss>>temp)
				{
					if(cnt==0)
						mnt<<temp<<"\t";
					else if(temp[0]=='&')
					{
						pp++;
						for(int i=0;i<temp.length();i++)
						{
							if(temp[i]=='=')
							{
								for(int j=0;j<temp.length();j++)
								{
									if(temp[j]=='=')
									{
										if(j==temp.length()-1)
										{
											kpdt<<"\t"<<"NULL";
											break;
										}
										else
										{
											kpdt<<"\t";
											j++;
										}
									}
									kpdt<<temp[j];
								}
								kpdt<<"\n";
								kp++;
								break;
							}	
							pnt<<temp[i];	
						}
						pnt<<"\n";
					}
					cnt++;
				}
				pp-=kp;
			}
			else if(temp=="LCL")
			{
				while(lin>>temp)
				{
					if(temp[0]=='&')
					{
						evn<<temp<<"\n";
						ev++;
					}
				}
			}
			else if(temp[0]=='.'&&temp.length()!=1)
			{
				if(sscnt==1)
					sst<<temp<<"\t"<<lc-2<<"\n";
			}	
		}
		sscnt=0;
		lc++;
	}
	mnt<<pp<<"\t"<<kp<<"\t"<<ev<<"\t"<<mdtp<<"\t"<<sstp<<"\t"<<kpdtp<<"\t\n";
	mnt.close();
	pnt.close();
	mac.close();
	kpdt.close();
	evn.close();
	sst.close();
	sscnt=0;
	mac.open("macrotest2.txt");
	mdt.open("mdttab.txt");
	while(mac.getline(word,50))
	{
		stringstream iss(word);
		while(iss>>temp)
		{
			sscnt++;
			if(temp=="MACRO")
				mac.getline(word,50);
			else if(temp[0]=='&')
			{
				int templc=0;
				templc=checkpara(temp);
				if(templc!=0)
					mdt<<"(P, "<<templc<<" )  ";
				else
				{
					templc=checkevn(temp);
					if(templc!=0)
						mdt<<"(E, "<<templc<<" )  ";
				}
			}
			else if(temp[0]=='.'&&temp.length()!=1)
			{
				int templc=0;
				templc=checklab(temp);
				if(templc!=0)
					if(sscnt!=1)
						mdt<<"(S, "<<templc<<" )  ";
			}
			else if(temp=="LCL")
			{
				while(iss>>temp)
					continue;
			}
			else
				mdt<<temp<<" ";
		}
		sscnt=0;
		mdt<<"\n";
	}
	mdt.close();
	mac.close();
	return 0;
}
