#ifndef INCLUDE_DAY22_HPP_
#define INCLUDE_DAY22_HPP_
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
#include<cmath>

using namespace std;

struct day22{

	enum dir:uint8_t{UP=0,RIGHT=1,BOT=2,LEFT=3};

	struct pos{
		pos(){x=y=d=UP;}
		pos(uint32_t x,uint32_t y):pos(){
			this->x=x;
			this->y=y;
		}

		int32_t x,y;
		dir d;

		void right(){
			d=(dir)((d+1)%4);
		}

		void left(){
			d=(dir)((d+3)%4);
		}

		void move(){
			switch(d){
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


		bool operator<(const pos&o)const{

			if(y==o.y)
				return x<o.x;

			return y<o.y;
		}
	};

	day22(const char* filename){
		ifstream i(filename);
		string s;
		i>>s;
		int32_t y=0;
		while(i.good())
		{
			for(uint32_t x=0;x<s.size();x++)
				status[pos(x,y)]=(s[x]=='#')?1:0;

			y++;
			i>>s;
		}

		start.x=start.y=12;
		start.d=UP;
	}

	void getResult() const{
		pos start=this->start;
		map<pos,uint8_t> status=this->status;

		uint32_t bursts=0;
		for(uint32_t i=0;i<10000;i++){

			if(status[start])
				start.right();
			else
			{
				start.left();
				bursts++;
			}

			status[start]^=1;
			start.move();
		}

		cout<<"Total bursts "<<bursts<<endl;
	}

	void getResult2() const{
		pos start=this->start;
		map<pos,uint8_t> status=this->status;

		for(auto& v:status)
			if(v.second)
				v.second=2;

		uint32_t bursts=0;
		for(uint32_t i=0;i<10000000;i++){

			if(status[start]==0)
				start.left();
			else if(status[start]==2)
				start.right();
			else if(status[start]==1)
				bursts++;
			else
			{
				start.right();
				start.right();
			}

			status[start]=(status[start]+1)%4;
			start.move();
		}

		cout<<"Total bursts "<<bursts<<endl;
	}

	pos start;
	map<pos,uint8_t> status;
};



#endif
