#ifndef INCLUDE_DAY20_HPP_
#define INCLUDE_DAY20_HPP_
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

struct day20{

	struct vec{
		vec(){
			x=y=z=0;
		}
		vec(istream& i):vec(){
			i>>x;
			i.ignore(10,',');
			i>>y;
			i.ignore(10,',');
			i>>z;
		}

		vec& operator+=(const vec& o){
			x+=o.x;
			y+=o.y;
			z+=o.z;

			return *this;
		}

		vec& operator*=(const int64_t& i){
			x*=i;
			y*=i;
			z*=i;

			return *this;
		}

		bool operator==(const vec& other)const{
			return x==other.x&&y==other.y&&z==other.z;
		}


		bool operator<(const vec& other)const{
			return length()<other.length();
		}


		uint64_t length()const{
			return abs(x)+abs(y)+abs(z);
		}

		int64_t x,y,z;
	};

	struct particle{
		particle(istream& i){
			pos=vec(i);
			i.ignore(100,'<');
			vel=vec(i);
			i.ignore(100,'<');
			acc=vec(i);
		}

		bool operator<(const particle& other)const{

			if(acc.length()==other.acc.length())
			{
				if(vel.length()==other.vel.length())
					return pos<other.pos;
				return vel<other.vel;
			}

			return acc<other.acc;

		}

		bool operator==(const particle& other)const{
			return pos==other.pos&&vel==other.vel&&acc==other.acc;
		}

		void update(){
			vel+=acc;
			pos+=vel;
		}
		vec pos,vel,acc;
		bool dead=false;
	};

	day20(const char* filename){
		ifstream i(filename);
		i.ignore(100,'<');
		while(i.good()){
			particle p(i);
			particles.push_back(p);
			i.ignore(100,'<');
		}

	}

	void getResult(){
		vector<particle> copy(particles);
		sort(copy.begin(),copy.end());
		for(uint32_t i=0;i<particles.size();i++)
		{
			if(particles[i]==copy[0])
			{
				cout<<"Index of closest particle to 0,0,0: "<<i<<endl;
				return;
			}
		}
	}

	void getResult2(){
		vector<particle> copy(particles);
		uint32_t stable=0;
		while(true)
		{
			map<uint64_t,vector<particle*>> reg;

			for(auto&v:copy){
				reg[v.pos.length()].push_back(&v);
			}

			for(auto&p:reg)
				for(uint32_t i=0;i<p.second.size();i++)
					for(uint32_t j=0;j<p.second.size();j++)
					{
						if(i==j)
							continue;

						if(p.second[i]->pos==p.second[j]->pos)
						{
							p.second[i]->dead=true;
							p.second[j]->dead=true;
						}
					}
			vector<particle> n;
			for(auto&v:copy)
				if(!v.dead)
				{
					v.update();
					n.push_back(v);
				}

			if(copy.size()==n.size())
				stable++;
			else
				stable=0;

			if(stable>5000)
			{
				cout<<"stabilized at "<<n.size()<<endl;
				break;
			}



			copy=n;
		}
	}

	vector<particle> particles;
};



#endif
