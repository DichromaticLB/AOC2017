#ifndef INCLUDE_DAY16_HPP_
#define INCLUDE_DAY16_HPP_
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

struct day16{

	struct move{
		char move;
		char parameter1;
		char parameter2;
		operator string(){
			stringstream s;
			switch(move){
			case 'x':
				s<<'x'<<(int)parameter1<<'/'<<(int)parameter2;
				break;
			case 'p':
				s<<'p'<<parameter1<<'/'<<parameter2;
				break;
			case 's':
				s<<'s'<<(int)parameter1;
				break;
			}
			return s.str();
		}
	};

	day16(const string& name){
		ifstream i(name);
		move m;
		int a,b;
		char c;
		i>>c;
		while(i.good())
		{
			switch(c){
			case 'x':
				i>>a;
				i.ignore();
				i>>b;
				m.parameter1=a;
				m.parameter2=b;
				break;
			case 'p':
				i>>m.parameter1;
				i.ignore();
				i>>m.parameter2;
				break;
			case 's':
				i>>a;
				m.parameter1=a;
				break;
			default:
				throw("bad input");
			}
			m.move=c;
			moves.push_back(m);
			i.ignore();
			i>>c;
		}
		for(char c='a';c!='q';c++)
			stage.push_back(c);
	}

	void dance(){
		for(auto&v:moves)
		{
			if(v.move=='s')
			{
				string newstate;
				for(uint32_t i=0;i<stage.size();i++)
					newstate.push_back(stage[((i+stage.size())-v.parameter1)%stage.size()]);
				stage=newstate;
			}
			else if(v.move=='x')
			{
				std::swap(stage[v.parameter1],stage[v.parameter2]);
			}
			else
			{
				for(auto&c:stage)
				{
					if(v.parameter1==c)
						c=v.parameter2;
					else if(v.parameter2==c)
						c=v.parameter1;
				}
			}

		}
	}

	void getResult(){
		dance();
		cout<<stage<<endl;

	}

	void getResult2(){
		map<string,uint64_t> cache;
		uint64_t i,lim=1000*1000*1000-1;
		for(i=0;i<lim;i++)
		{

			if(cache.count(stage))
				break;
			cache[stage]=i;
			dance();

		}

		lim-=i;
		lim=lim%(i-cache[stage]);
		while(lim--)
			dance();

		cout<<stage<<endl;
	}

	string stage;
	std::vector<move> moves;

};



#endif
