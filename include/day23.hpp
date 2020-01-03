#ifndef INCLUDE_DAY23_HPP_
#define INCLUDE_DAY23_HPP_
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


using namespace std;

struct day23{

	struct computer{

		int64_t execute(string inst,string param1,string param2){
			int64_t increment=1;
			if(inst=="set")
				decode(param1)=decode(param2);
			else if(inst=="sub")
				decode(param1)-=decode(param2);
			else if(inst=="mul")
				decode(param1)*=decode(param2);
			else if(inst=="jnz")
			{
				if(decode(param1))
					increment=decode(param2);
			}
			else
				throw inst;

			return increment;
		}

		int64_t& decode(const string&s){
			if(isalpha(s[0]))
				return memory[s[0]];

			voida=std::atoll(s.c_str());
			return voida;
		}

		map<char,int64_t> memory;
		int64_t voida=0;
	};

	struct program{
			void getInstruction(ifstream& i){
				string ins;
				i>>ins;
				if(i.good()){
					instruction.emplace_back(ins);
					param1.emplace_back();
					param2.emplace_back();
					i>>param1.back();
					i>>param2.back();
				}
			}
			vector<string> instruction;
			vector<string> param1;
			vector<string> param2;
		};


	day23(const char* filename){
		ifstream i(filename);
		while(i.good())
			p.getInstruction(i);

	}


	void getResult(){
		computer c;
		uint32_t mults=0;
		for(int64_t i=0;(uint64_t)i<p.instruction.size();)
		{
			if(p.instruction[i]=="mul")
				mults++;
			i+=c.execute(p.instruction[i],p.param1[i],p.param2[i]);
		}
		cout<<"Total multiplications: "<<mults<<endl;

	}

	bool isprime(uint32_t j){
		for(uint32_t i=2;i<=j/2;i++)
			if(j%i==0)
				return false;
		return true;
	}

	void getResult2(){
		computer c;
		c.memory['a']=1;
		for(int64_t i=0;i<8;)
		{
			i+=c.execute(p.instruction[i],p.param1[i],p.param2[i]);
		}

		uint32_t start=c.memory['b'];
		uint32_t target=c.memory['c'];
		int32_t increment=std::atoi(p.param2[p.param2.size()-2].c_str());
		uint32_t count=0;
		for(;start<=target;start-=increment){
			if(!isprime(start))
				count++;
		}
		cout<<"Total non prime numbers: "<<count<<endl;
	}

	program p;


};



#endif
