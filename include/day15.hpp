#ifndef INCLUDE_DAY15_HPP_
#define INCLUDE_DAY15_HPP_
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

struct day15{

	struct generator{
		generator(uint64_t currVal,uint64_t factor){
			this->currVal=currVal;
			this->factor=factor;
		}

		bool match(const generator &b) const{
			return (currVal&0xffff)==(b.currVal&0xffff);
		}

		void iterate(uint32_t div=0){
			currVal=(currVal*factor)%2147483647;
			if(div!=0&&currVal%div!=0)
				iterate(div);
		}

		uint64_t currVal,factor;
	};

	day15(const string& name):a(0,16807),b(0,48271){
		ifstream i(name);
		a.currVal=extract(i);
		b.currVal=extract(i);
	}

	static int64_t extract(ifstream&i){
		while(i.good()&&!isdigit(i.peek()))
			i.ignore();
		int64_t res;
		i>>res;
		return res;

	}

	void getResult(){
		generator a2(a);
		generator b2(b);
		uint32_t count=0;
		for(uint32_t i=0;i<1000*1000*40;i++)
		{
			a2.iterate();
			b2.iterate();
			if(a2.match(b2))
				count++;

		}

		cout<<"part 1 "<<count<<" total matches"<<endl;

	}

	void getResult2(){
		generator a2(a);
		generator b2(b);

		uint32_t count=0;
		for(uint32_t i=0;i<1000*1000*5;i++)
		{
			a2.iterate(4);
			b2.iterate(8);
			if(a2.match(b2))
				count++;

		}

		cout<<"part 2 "<<count<<" total matches"<<endl;

	}

	generator a,b;

};



#endif
