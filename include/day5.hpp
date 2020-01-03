#ifndef INCLUDE_DAY5_HPP_
#define INCLUDE_DAY5_HPP_
#include<iostream>
#include<string>
#include<cstdint>
#include<fstream>
#include<vector>
#include<limits>
#include<map>
#include<algorithm>
using namespace std;

struct day5{

	day5(const string& filename){
		ifstream i(filename);
		int64_t b;
		i>>b;

		while(i.good())
		{
			jumps.push_back(b);
			i>>b;
		}

	}

	void getResult(){
		std::vector<int64_t> j=jumps;
		uint64_t index=0,ct=0;
		while(index>=0&&index<j.size())
		{
			index+=j[index]++;
			ct++;
		}
		cout<<"Jumps to escape "<<ct<<endl;

	}

	void getResult2(){

		std::vector<int64_t> j=jumps;
		uint64_t index=0,ct=0;
		while(index>=0&&index<j.size())
		{
			int64_t& inc=j[index];
			index+=inc;
			if(inc>=3)
				inc--;
			else
				inc++;
			ct++;
		}
		cout<<"Jumps to escape2 "<<ct<<endl;
	}

	std::vector<int64_t> jumps;
};



#endif
