#ifndef INCLUDE_DAY21_HPP_
#define INCLUDE_DAY21_HPP_
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

struct day21{

	struct pattern{
		pattern(){}
		pattern(const string& i){
			uint8_t buf=0,dex=0;
			for(auto c:i)
			{
				if(c=='#')
					buf|=(1<<(dex++));
				else if(c=='.')
					dex++;
				else
				{
					rows.push_back(buf);
					dex=0;
					buf=0;
				}

			}
			rows.push_back(buf);
		}

		pattern rotate(){
			pattern res=*this;

			for(auto&v:res.rows)
				v=0;

			for(uint8_t y=0;y<size();y++)
				for(uint8_t x=0;x<size();x++)
					if(access(x,y))
						res.rows[size()-x-1]|=(1<<y);

			return res;
		}

		pattern flipX(){
			pattern res=*this;

			for(auto&v:res.rows)
				v=0;

			for(uint8_t y=0;y<size();y++)
				for(uint8_t x=0;x<size();x++)
					if(access(x,y))
						res.rows[y]|=(1<<(size()-x-1));

			return res;
		}

		pattern flipY(){
			pattern res=*this;

			for(auto&v:res.rows)
				v=0;

			for(uint8_t y=0;y<size();y++)
				for(uint8_t x=0;x<size();x++)
					if(access(x,y))
						res.rows[size()-y-1]|=(1<<x);

			return res;
		}


		operator string(){
			string res;
			for(uint8_t y=0;y<size();y++)
			{
				for(uint8_t x=0;x<size();x++)
					if(access(x,y))
						res+='#';
					else
						res+='.';
				res+='\n';
			}
			return res;
		}


		uint8_t size() const{
			return rows.size();
		}

		bool access(uint8_t x,uint8_t y)const {
			return rows[y]&(1<<x);
		}

		bool operator<(const pattern& o) const{
			if(rows.size()==o.rows.size())
			{
				for(uint32_t i=0;i<size();i++)
					if(rows[i]!=o.rows[i])
						return rows[i]<o.rows[i];
			}

			return rows.size()<o.rows.size();
		}

		bool operator==(const pattern& o) const{
			if(rows.size()!=o.rows.size())
				return false;

			for(uint32_t i=0;i<size();i++)
				if(rows[i]!=o.rows[i])
					return false;

			return true;
		}
		vector<uint8_t> rows;
	};

	struct picture{
		picture(){
			size=3;
			data.resize(size*size,true);
			data[0]=data[2]=data[3]=data[4]=false;
		}

		pattern project(uint32_t x,uint32_t y,uint32_t s) const{
			pattern res;
			res.rows.resize(s,0);

			for(uint32_t yy=0;yy<s;yy++)
				for(uint32_t xx=0;xx<s;xx++)
					if(access(x+xx,y+yy))
						res.rows[yy]|=1<<xx;

			return res;
		}

		void imprint(uint32_t x,uint32_t y,const pattern&p) {
			for(uint32_t yy=0;yy<p.size();yy++)
				for(uint32_t xx=0;xx<p.size();xx++)
				{
					if(p.access(xx,yy))
						enable(x+xx,y+yy);
				}
		}


		bool access(uint32_t x,uint32_t y) const {return data[y*size+x];}
		void enable(uint32_t x,uint32_t y) {data[y*size+x]=true;}

		picture expand(const map<pattern,pattern>&pat) const{
			picture res=*this;
			uint32_t step=3;

			if(!(size%2))
				step=2;

			res.size+=size/step;
			res.data.clear();
			res.data.resize(res.size*res.size,false);
			for(uint32_t y=0;y<size/step;y++)
				for(uint32_t x=0;x<size/step;x++)
				{
					auto p=project(x*step,y*step,step);
					res.imprint(x*(step+1),y*(step+1),pat.at(p));
				}

			return res;

		}



		uint32_t count() const{
			uint32_t res=0;
			for(uint32_t y=0;y<size;y++)
				for(uint32_t x=0;x<size;x++)
					if(access(x,y))
						res++;
			return res;
		}

		uint32_t size;
		vector<bool> data;
	};

	day21(const char* filename){
		ifstream i(filename);
		string r1,r2;
		i>>r1;
		i.ignore(5,'>');
		i.ignore();
		i>>r2;
		auto r=picture().project(0,0,3);
		while(i.good())
		{

			pattern s(r1);
			pattern t(r2);
			patterns[s]=t;
			patterns[s.flipX()]=t;
			patterns[s.flipY()]=t;

			s=s.rotate();
			patterns[s]=t;
			patterns[s.flipX()]=t;
			patterns[s.flipY()]=t;

			s=s.rotate();
			patterns[s]=t;
			patterns[s.flipX()]=t;
			patterns[s.flipY()]=t;

			s=s.rotate();
			patterns[s]=t;
			patterns[s.flipX()]=t;
			patterns[s.flipY()]=t;

			i>>r1;
			i.ignore(5,'>');
			i.ignore();
			i>>r2;
		}
	}

	void getResult(){
		picture p;
		for(auto i=0;i<5;i++)
			p=p.expand(patterns);

		cout<<p.count()<<endl;
	}

	void getResult2(){
		picture p;
		for(auto i=0;i<18;i++)
			p=p.expand(patterns);

		cout<<p.count()<<endl;
	}

	map<pattern,pattern> patterns;


};



#endif
