#ifndef INCLUDE_DAY24_HPP_
#define INCLUDE_DAY24_HPP_
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

struct day24{

	struct port{

		port(uint32_t sideA,uint32_t sideB){
			this->sideA=sideA;
			this->sideB=sideB;
		}

		uint32_t otherSide(uint32_t side){

			if(side==sideA)
				return sideB;

			return sideA;
		}

		uint32_t sideA,sideB;
	};

	struct node{

		vector<port*> targets;
	};

	day24(const char* filename){
		ifstream i(filename);
		uint32_t a,b;
		i>>a;
		i.ignore();
		i>>b;
		while(i.good())
		{
			ports.emplace_back(a,b);
			i>>a;
			i.ignore();
			i>>b;
		}

		for(auto&v:ports){
			graph[v.sideA].targets.push_back(&v);
			graph[v.sideB].targets.push_back(&v);
		}

	}

	uint32_t strength(set<port*>& used){
		uint32_t res=0;
		for(auto& p:used)
			res+=p->sideA+p->sideB;
		return res;
	}

	uint32_t iterate(set<port*> used=set<port*>(),uint32_t node=0,uint32_t max=0){
		for(auto n:graph[node].targets)
		{
			if(used.count(n))
				continue;

			set<port*> up(used);
			up.insert(n);
			uint32_t ch=iterate(up,n->otherSide(node),max);
			if(ch>max)
				max=ch;
		}

		uint32_t ch=strength(used);

		if(ch>max)
			max=ch;


		return max;
	}

	uint32_t iterate2(uint32_t& maxLen,uint32_t& max,set<port*> used=set<port*>(),uint32_t node=0){

		for(auto n:graph[node].targets)
		{
			if(used.count(n))
				continue;

			set<port*> up(used);
			up.insert(n);
			iterate2(maxLen,max,up,n->otherSide(node));
		}

		if(used.size()>maxLen){
			maxLen=used.size();
			max=strength(used);
		}
		else if(used.size()==maxLen){
			if(strength(used)>max)
				max=strength(used);
		}

		return max;
	}


	void getResult(){
		cout<<"strongest bridge: "<<iterate()<<endl;

	}


	void getResult2(){
		uint32_t maxLen=0,max=0;
		cout<<"strongest longest bridge: "<<iterate2(maxLen,max)<<endl;

	}

	vector<port> ports;
	map<uint32_t,node> graph;

};



#endif
