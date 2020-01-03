#ifndef INCLUDE_DAY1_HPP_
#define INCLUDE_DAY1_HPP_
#include<iostream>
#include<string>
#include<cstdint>
#include<fstream>
#include<vector>

using namespace std;

struct day1{

	day1(const string& filename){

		ifstream in(filename);
		string input;
		in>>input;

		for(auto&c:input)
			nums.push_back(c-'0');




	}

	void getResult(){
		unsigned res=0;
		for(unsigned i=0;i<nums.size();i++)
		{
			if(nums[i%nums.size()]==nums[(i+1)%nums.size()])
				res+=nums[i%nums.size()];
		}
		cout<<res<<endl;
	}



	void getResult2(){

		unsigned res=0;
			for(unsigned i=0;i<nums.size();i++)
			{
				if(nums[i%nums.size()]==nums[(i+nums.size()/2)%nums.size()])
					res+=nums[i%nums.size()];
			}

			cout<<res<<endl;
	}

	vector<int> nums;
};



#endif
