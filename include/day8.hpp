#ifndef INCLUDE_DAY8_HPP_
#define INCLUDE_DAY8_HPP_
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
using namespace std;
struct instruction{
	string target;
	bool increment;
	int64_t incVal;
	string reg;
	string op;
	int64_t num;
};


istream& operator>>(istream&i,instruction& ins){
	i>>ins.target;
	if(i.good()){
		string s;

		i>>s;
		ins.increment=s=="inc";

		i>>ins.incVal;
		i>>s;

		i>>ins.reg;
		i>>ins.op;
		i>>ins.num;
	}
	return i;
}

struct day8{


	day8(const string& filename){
		ifstream i(filename);
		instruction ins;
		i>>ins;
		while(i.good())
		{
			instructions.push_back(ins);
			i>>ins;
		}
		IP=0;
		max=0;
	}

	bool execute(){
		if(IP>=instructions.size())
			return false;

		auto i=instructions[IP];
		bool success=false;

		if(i.op=="=="&&registers[i.reg]==i.num)
			success=true;
		else if(i.op=="<"&&registers[i.reg]<i.num)
			success=true;
		else if(i.op==">"&&registers[i.reg]>i.num)
			success=true;
		else if(i.op==">="&&registers[i.reg]>=i.num)
			success=true;
		else if(i.op=="<="&&registers[i.reg]<=i.num)
			success=true;
		else if(i.op=="!="&&registers[i.reg]!=i.num)
			success=true;


		if(success)
			registers[i.target]+=(i.increment?1:-1)*i.incVal;

		if(registers[i.target]>max)
			max=registers[i.target];


		IP++;
		return true;
	}

	void getResult(){
		IP=0;
		registers.clear();
		while(execute());
		int64_t max=0;
		for(auto&v:registers)
		{
			if(v.second>max)
				max=v.second;
		}
		cout<<max<<endl;
	}


	void getResult2(){
		IP=0;
		registers.clear();
		while(execute());
		cout<<max<<endl;
	}

	uint64_t IP;
	int64_t max;
	std::vector<instruction> instructions;
	map<string,int64_t> registers;

};



#endif
