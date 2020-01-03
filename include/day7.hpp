#ifndef INCLUDE_DAY7_HPP_
#define INCLUDE_DAY7_HPP_
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

struct program{
		string name;
		uint32_t weight;
		std::vector<string> rel;
	};

static istream& operator>>(istream& i,program& m){

	m.rel.clear();
	i>>m.name;
	if(i.good())
	{
		i.ignore(100,'(');
		i>>m.weight;

		while(i.peek()!='>'&&i.peek()!='\n')
			i.ignore();

		if(i.peek()!='\n')
		{
			i.ignore();
			while(i.peek()!='\n')
			{
				string rel;
				i>>rel;
				if(rel.back()==',')
					rel.pop_back();

				m.rel.push_back(rel);
			}
		}
	}
	return i;
}

struct day7{



	day7(const string& filename){
		ifstream i(filename);
		program m;
		i>>m;

		while(i.good()){
			relations[m.name]=m.rel;
			weights[m.name]=m.weight;
			i>>m;
		}

	}


	string bottom(){
		set<string> children;
		for(auto&v:relations)
		{
			children.insert(v.second.begin(),v.second.end());
		}

		for(auto&v:relations)
		{
			if(!children.count(v.first))
				return v.first;
		}

		return "";
	}


	void getResult(){
		cout<<"Bottom program "<<bottom()<<endl;
	}

	uint64_t realWeight(const string&name){
		if(!rweights.count(name))
			rweights[name]=weights[name]+
				accumulate(relations[name].begin(),relations[name].end(),0l,[&](uint64_t a,const string& b){
			return a+realWeight(b);
		});

		return rweights[name];
	}

	void balance(const std::vector<string>& target){
		std::map<uint64_t,uint64_t> st;
		uint64_t is=0,needs2b=0;
		for(auto&c:target)
			st[realWeight(c)]++;

		for(auto& entr:st){
			if(entr.second==1)
				is=entr.first;
			else
				needs2b=entr.first;
		}

		for(auto&c:target)
		{
			auto w=realWeight(c);
			if(w==is)
			{
				cout<<"Fixing "<<c<<" which weights "<<is<<" and needs to be "<<needs2b<<endl;
				weights[c]-=is-needs2b;
				cout<<"new weight for "<<c<<":"<<weights[c]<<endl;
				break;
			}
		}

	}

	void getResult2(){
		for(auto& r:relations){
			std::map<uint64_t,uint64_t> st;
			for(auto&c:r.second)
				st[realWeight(c)]++;

			if(st.size()>1){
				cout<<"imbalanced program "<<r.first<<" ";
				for(auto&v:st){
					cout<<v.first<<"->"<<v.second<<" ";
				}
				cout<<endl;
				balance(r.second);
				rweights.clear();
				getResult2();
				return;
			}
		}

	}

	std::map<string,std::vector<string>> relations;
	std::map<string,uint32_t> weights;
	std::map<string,uint32_t> rweights;

};



#endif
