#ifndef INCLUDE_DAY19_HPP_
#define INCLUDE_DAY19_HPP_
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
#include<iomanip>
#include<queue>


using namespace std;

struct day19{
	enum direction:uint8_t{UP=0,RIGHT=1,BOT=2,LEFT=3};
	struct pos{
		direction src;
		uint32_t x,y;

		void move(){
			switch(src){
			case UP:
				y--;
				break;
			case RIGHT:
				x++;
				break;
			case BOT:
				y++;
				break;
			case LEFT:
				x--;
				break;
			}
		}

		bool oposite(pos&p){
			return (src+2)%4==p.src;
		}

		pos moveCopy(){
			pos res=*this;
			res.move();
			return res;
		}

	};


	day19(const char* filename){
		ifstream i(filename);
		string s;
		std::getline(i,s);
		while(i.good())
		{
			net.push_back(s);
			std::getline(i,s);
		}
		start.y=0;
		start.x=0;
		start.src=BOT;

		for(;start.x<net[0].size();start.x++)
			if(net[0][start.x]!=' ')
				break;
	}

	bool valid(pos&p){
		if(p.y<net.size()&&p.x<net[p.y].size()&&net[p.y][p.x]!=' ')
			return true;
		return false;
	}

	vector<pos> around(pos&p){
		vector<pos> res;
		vector<direction> it={UP,RIGHT,BOT,LEFT};
		for(auto&v:it){
			res.push_back(p);
			res.back().src=v;
			res.back().move();
			if(!valid(res.back()))
				res.pop_back();
		}

		return res;

	}


	void getResult(){
		string path;
		pos iter=start;
		while(true){
			auto nxt=around(iter);
			if(nxt.size()==0||(nxt.size()==1&&iter.oposite(nxt[0])))
			{
				cout<<"Path 1 "<<path<<endl;
				return;
			}

			pos p=iter.moveCopy();

			if(valid(p))
			{
				iter=p;
			}
			else
			{
				for(auto&v:nxt){
					if(v.oposite(iter))
						continue;
					else
					{
						iter=v;
						break;
					}
				}
			}

			if(isalpha(net[iter.y][iter.x]))
				path+=net[iter.y][iter.x];
		}


	}

	void getResult2(){
		uint32_t count=0;
		pos iter=start;
		while(true){
			auto nxt=around(iter);
			if(nxt.size()==0||(nxt.size()==1&&iter.oposite(nxt[0])))
			{
				count++;
				cout<<"count "<<count<<endl;
				return;
			}

			pos p=iter.moveCopy();

			if(valid(p))
			{
				iter=p;
			}
			else
			{
				for(auto&v:nxt){
					if(v.oposite(iter))
						continue;
					else
					{
						iter=v;
						break;
					}
				}
			}
			count++;

		}

	}

	pos start;
	vector<string> net;


};



#endif
