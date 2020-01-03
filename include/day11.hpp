#ifndef INCLUDE_DAY11_HPP_
#define INCLUDE_DAY11_HPP_
#include<iostream>
#include<string>
#include<cstdint>
#include<fstream>
#include<vector>
#include<limits>
#include<map>
#include<algorithm>
#include<set>
#include<numeric>
#include<sstream>
#include <iomanip>
using namespace std;




struct day11{



	day11(const string& filename){
		ifstream i(filename);
		string s;
		char c;
		i>>c;
		while(i.good())
		{

			if(c==',')
			{
				path.push_back(s);
				s.clear();
			}
			else
				s+=c;
			i>>c;

		}
		path.push_back(s);

	}

	void getResult(){
		int64_t x=0,y=0;
		for(auto&s:path)
		{
			if(s=="n")
				y-=2;
			else if(s=="s")
				y+=2;
			else if(s=="e")
				x+=2;
			else if(s=="w")
				x-=2;
			else if(s=="ne")
			{
				y-=1;
				x+=1;
			}
			else if(s=="nw")
			{
				y-=1;
				x-=1;
			}
			else if(s=="se")
			{
				y+=1;
				x+=1;
			}
			else if(s=="sw")
			{
				y+=1;
				x-=1;
			}

		}
		cout<<x<<","<<y<<"  "<<(abs(x)+abs(y))/2<<endl;

	}


	void getResult2(){
		int64_t x=0,y=0,max=0;
		for(auto&s:path)
		{
			if(s=="n")
				y-=2;
			else if(s=="s")
				y+=2;
			else if(s=="e")
				x+=2;
			else if(s=="w")
				x-=2;
			else if(s=="ne")
			{
				y-=1;
				x+=1;
			}
			else if(s=="nw")
			{
				y-=1;
				x-=1;
			}
			else if(s=="se")
			{
				y+=1;
				x+=1;
			}
			else if(s=="sw")
			{
				y+=1;
				x-=1;
			}

			if((abs(x)+abs(y))/2>max)
				max=(abs(x)+abs(y))/2;

		}
				cout<<max<<endl;

	}

	vector<string> path;
};



#endif
