#ifndef INCLUDE_DAY9_HPP_
#define INCLUDE_DAY9_HPP_
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



struct group{
	group(istream& i){
		if(i.peek()!='{')
			throw("Bad group construction");
		i.ignore();

		while(i.peek()!='}')
		{
			if(i.peek()=='{')
				subgroups.emplace_back(i);
			else if(i.peek()=='<')
				parseGarbage(i);
			else if(i.peek()==',')
				i.ignore();
			else
				throw(string("Bad subgroup"));


		}
		i.ignore();
	}

	uint64_t score(uint64_t mine){
		return mine+accumulate(subgroups.begin(),subgroups.end(),0l,[&](uint64_t a,group&g){
			return a+g.score(mine+1);
		});
	}

	uint64_t garbageCount(){
		uint64_t res=0;
		for(auto&g:garbages)
			res+=g.size();
		return res;
	}


	uint64_t gscore(){
		return garbageCount()+accumulate(subgroups.begin(),subgroups.end(),0l,[&](uint64_t a,group&g){
			return a+g.gscore();
		});
	}


	void parseGarbage(istream&i){
		i.ignore();
		string st="";
		while(i.peek()!='>')
		{
			if(i.peek()=='!')
				i.ignore(2);
			else
			{
				char c;
				i>>c;
				st+=c;
			}

		}
		garbages.push_back(st);
		i.ignore();
	}

	std::vector<group> subgroups;
	std::vector<string> garbages;
};


struct day9{

	day9(const string& filename){
		ifstream i(filename);
		while(i.good())
		{
			if(i.peek()=='{')
				groups.emplace_back(i);
			else if(i.peek()==',')
				i.ignore();
			else if(i.peek()!='\n')
			{
				throw("Invalid char");
			}
			else
				break;
		}

	}

	void getResult(){
		uint64_t res=0;
		for(auto&v:groups)
			res+=v.score(1);
		cout<<"Group score: "<<res<<endl;
	}


	void getResult2(){
		uint64_t res=0;
		for(auto&v:groups)
			res+=v.gscore();
		cout<<"Garbage score: "<<res<<endl;
	}

	vector<group> groups;

};



#endif
