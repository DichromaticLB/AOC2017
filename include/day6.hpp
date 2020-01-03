#ifndef INCLUDE_DAY6_HPP_
#define INCLUDE_DAY6_HPP_
#include<iostream>
#include<string>
#include<cstdint>
#include<fstream>
#include<vector>
#include<limits>
#include<map>
#include<algorithm>
using namespace std;

struct day6{

	day6(const string& filename){
		ifstream i(filename);
		uint32_t b;
		i>>b;

		while(i.good())
		{
			banks.push_back(b);
			i>>b;
		}
	}

	static void iterate(std::vector<uint8_t>& banks){

		uint8_t index=0,count=0;
		for(uint8_t i=0;i<banks.size();i++)
		{
			if(banks[i]>count)
			{
				index=i;
				count=banks[i];
			}
		}
		banks[index]=0;
		index++;
		while(count)
		{
			banks[index++%banks.size()]++;
			count--;
		}
	}

	union state{

		state(const vector<uint8_t>&v){
			id[0]=0;
			id[1]=0;
			uint8_t i=0;
			for(auto&vv:v)
				bank[i++]=vv;
		}

		bool operator<(const state&other) const{
			if(id[0]==other.id[0])
				return id[1]<other.id[1];

			return id[0]<other.id[0];
		}

		uint8_t bank[16];
		uint64_t id[2];
	};


	void getResult(){
		map<state,uint8_t> signatures;
		std::vector<uint8_t> banks=this->banks;
		uint32_t iter=0;
		while(true)
		{
			iter++;
			iterate(banks);
			state s(banks);
			if(signatures.count(s))
			{
				cout<<"First loop at "<<iter<<endl;
				return;
			}
			signatures[s]++;
		}

	}

	void getResult2(){
		map<state,uint32_t> signatures;
		std::vector<uint8_t> banks=this->banks;
		uint32_t iter=0;
		while(true)
		{
			iter++;
			iterate(banks);
			state s(banks);
			if(signatures.count(s))
			{
				cout<<"First loop len "<<(iter-signatures[s])<<endl;
				return;
			}
			signatures[s]=iter;
		}

	}

	std::vector<uint8_t> banks;
};



#endif
