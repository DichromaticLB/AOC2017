#ifndef INCLUDE_DAY12_HPP_
#define INCLUDE_DAY12_HPP_
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




struct day12{


	day12(const string& filename){
		ifstream i(filename);

		while(i.good())
		{
			int n,k;
			i>>n;
			i.ignore(100,'>');
			while(i.good())
			{
				i>>k;
				piping[n].insert(k);
				piping[k].insert(n);
				if(i.peek()=='\n')
					break;
				else
					i.ignore();
			}

			for(auto& v:piping[n])
				for(auto& v2:piping[n])
					piping[v].insert(v2);
		}

		for(auto&v:piping)
		{
			cout<<v.first<<"("<<v.second.size()<<") ";
			for(auto&vv:v.second)
				cout<<vv<<",";
			cout<<endl;
		}




	}

	void getResult(){
		cout<<piping[0].size()<<endl;
	}

	void getResult2(){
		map<int,set<int>> copy=piping;
		uint32_t ct=0;
		while(copy.size())
			for(auto v:copy)
			{
				set<int> t=v.second;
				copy.erase(v.first);
				for(auto&o:t)
					copy.erase(o);
				ct++;
				break;
			}

		cout<<ct<<endl;
	}

	map<int,set<int>> piping;
};



#endif
