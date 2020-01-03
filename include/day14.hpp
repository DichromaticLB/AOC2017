#ifndef INCLUDE_DAY14_HPP_
#define INCLUDE_DAY14_HPP_
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
#include<queue>
#include"day10.hpp"

using namespace std;

struct day14{

	day14(const string& name){
		for(uint32_t i=0;i<128;i++)
		{
			matrix.emplace_back(day10::doHash(name+"-"+to_string(i)));
		}
	}

	void getResult(){
		uint32_t count=0;
		for(auto row:matrix)
			for(uint8_t c:row)
			{
				while(c)
				{
					if(c&1)
						count++;
					c>>=1;
				}
			}

		cout<<count<<endl;

	}

	bool used(uint32_t col,uint32_t row)
	{
		return matrix[row][col/8]&(1<<(7-(col%8)));
	}

	void clear(uint32_t col,uint32_t row)
	{
		matrix[row][col/8]&= 0xff^(1<<(7-(col%8)));
	}
	struct pos:public pair<uint32_t,uint32_t>
	{
		pos(uint32_t x,uint32_t y):pair<uint32_t,uint32_t>(x,y){}

	};

	vector<pos> around(uint32_t x,uint32_t y){
		vector<pos> res;
		if(x>0)
			res.emplace_back(x-1,y);

		if(y>0)
			res.emplace_back(x,y-1);

		if(x<127)
			res.emplace_back(x+1,y);

		if(y<127)
			res.emplace_back(x,y+1);

		return res;

	}

	void getResult2(){
		vector<char> visited(128*128,0);
		uint32_t ct=0;
		for(uint32_t i=0;i<visited.size();i++)
		{
			if(visited[i]||!used(i%128,i/128))
				continue;

			visited[i]=true;

			queue<pos> remaining;
			remaining.emplace(i%128,i/128);
			while(remaining.size())
			{
				pos p=remaining.front();
				remaining.pop();
				auto ar=around(p.first,p.second);
				clear(p.first,p.second);
				for(auto& p2:ar)
				{
					if(visited[p2.first+p2.second*128])
						continue;
					visited[p2.first+p2.second*128]=1;
					if(used(p2.first,p2.second))
					{
						clear(p2.first,p2.second);
						remaining.emplace(p2.first,p2.second);
					}
				}
			}
			ct++;
		}

		cout<<ct<<endl;
	}

	vector<vector<char>> matrix;

};



#endif
