#ifndef INCLUDE_DAY3_HPP_
#define INCLUDE_DAY3_HPP_
#include<iostream>
#include<string>
#include<cstdint>
#include<fstream>
#include<vector>
#include<limits>
#include<map>

using namespace std;

struct day3{

	day3(const string& filename){


	}

	uint32_t rinLen(uint32_t index){
		if(index==0)
			return 1;
		return (1+index*2)*4-4;
	}

	int32_t startX(uint32_t dex){
		return (int32_t)dex;
	}

	int32_t startY(uint32_t dex){
		if(dex==0)
			return 0;

		return -((int32_t)dex);
	}


	void getResult(uint32_t start=368078){
		uint32_t k=0,dex=0;
		while(k+rinLen(dex)<start)
		{
			k+=rinLen(dex);
			dex++;
		}

		int32_t x=startX(dex);
		int32_t y=startY(dex);
		int32_t steps=start-k;
		int32_t inc=dex*2;


		if(steps)
		{
			if(inc>=steps)
			{
				y+=steps;
				steps=0;
			}
			else
			{
				y+=inc;
				steps-=inc;
			}
		}
		if(steps)
		{
			if(inc>=steps)
			{
				x-=steps;
				steps=0;
			}
			else
			{
				x-=inc;
				steps-=inc;
			}
		}
		if(steps)
		{
			if(inc>=steps)
			{
				y-=steps;
				steps=0;
			}
			else
			{
				y-=inc;
				steps-=inc;
			}
		}
		if(steps)
		{
			if(inc>=steps)
			{
				x+=steps;
				steps=0;
			}
			else
			{
				x+=inc;
				steps-=inc;
			}
		}

		cout<<x<<","<<y<<endl;
	}
struct pos{
	int32_t x,y;
	pos(int32_t x,int32_t y){
		this->x=x;
		this->y=y;
	}
	bool operator<(const pos &other)const{

		if(other.x==x)
			return y<other.y;

		return x<other.x;
	}

};
	void update(map<pos,uint64_t> &vals,int32_t tx,int32_t ty){
		uint64_t sum=0;

		if(vals.count(pos(tx+1,ty)))
			sum+=vals[pos(tx+1,ty)];
		if(vals.count(pos(tx+1,ty+1)))
			sum+=vals[pos(tx+1,ty+1)];
		if(vals.count(pos(tx,ty+1)))
			sum+=vals[pos(tx,ty+1)];
		if(vals.count(pos(tx-1,ty+1)))
			sum+=vals[pos(tx-1,ty+1)];
		if(vals.count(pos(tx-1,ty)))
			sum+=vals[pos(tx-1,ty)];
		if(vals.count(pos(tx-1,ty-1)))
			sum+=vals[pos(tx-1,ty-1)];
		if(vals.count(pos(tx,ty-1)))
			sum+=vals[pos(tx,ty-1)];
		if(vals.count(pos(tx+1,ty-1)))
			sum+=vals[pos(tx+1,ty-1)];
		vals[pos(tx,ty)]=sum;

		if(sum>368078&&!finished)
		{
			cout<<sum<<endl;
			finished=true;
		}
	}

	void getResult2(){
		int32_t x=0,y=0;
		map<pos,uint64_t> vals={{pos(0,0),1}};
		uint32_t dex=1;
		x++;
		while(!finished){
			uint32_t inc=dex*2;
			for(uint32_t st=0;st<inc-1;st++){
				update(vals,x,y);
				y++;
			}
			for(uint32_t st=0;st<inc;st++){
				update(vals,x,y);
				x--;
			}
			for(uint32_t st=0;st<inc;st++){
				update(vals,x,y);
				y--;
			}
			for(uint32_t st=0;st<inc+1;st++){
				update(vals,x,y);
				x++;
			}
			dex++;
		}
	}

	bool finished=false;
};



#endif
