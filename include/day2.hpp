#ifndef INCLUDE_DAY2_HPP_
#define INCLUDE_DAY2_HPP_
#include<iostream>
#include<string>
#include<cstdint>
#include<fstream>
#include<vector>
#include<limits>
using namespace std;

struct day2{

	day2(const string& filename){

		ifstream in(filename);
		rows.emplace_back();
		while(in.good())
		{
			if(in.peek()=='\n')
				rows.emplace_back();
			int v;
			in>>v;
			rows.back().push_back(v);
		}
	}

	int checksum(vector<int> &v){
		int max=0,min=std::numeric_limits<int>::max();

		for(auto&vv:v)
		{
			if(vv>max)
				max=vv;
			if(vv<min)
				min=vv;
		}
		return max-min;
	}

	int check2(vector<int> &v){
		for(auto&vv:v)
			for(auto&vvv:v)
				if(!(vv%vvv)&&vv!=vvv)
					return (vv/vvv);
		return 0;
	}

	void getResult(){
		int res=0;
		for(auto&v:rows)
			res+=checksum(v);
		std::cout<<res<<endl;
	}

	void getResult2(){
		int res=0;
		for(auto&v:rows)
			res+=check2(v);
		std::cout<<res<<endl;
	}

	vector<vector<int>> rows;
};



#endif
