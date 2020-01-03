#ifndef INCLUDE_DAY18_HPP_
#define INCLUDE_DAY18_HPP_
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

struct day18{


	struct computer{

		int64_t execute(string inst,string param1,string param2){
			int64_t increment=1;
			ns=false;
			if(inst=="snd")
			{
				if(soundMode)
					soundRegister=decode(param1);
				else
					out.emplace(decode(param1));
			}
			else if(inst=="set")
				decode(param1)=decode(param2);
			else if(inst=="add")
				decode(param1)+=decode(param2);
			else if(inst=="mul")
				decode(param1)*=decode(param2);
			else if(inst=="mod")
				decode(param1)%=decode(param2);
			else if(inst=="rcv")
			{
				if(soundMode)
				{
					if(decode(param1))
						ns=true;
				}
				else
				{
					if(in.size())
					{
						decode(param1)=in.front();
						in.pop();
					}
					else
						increment=0;
				}
			}
			else if("jgz")
				if(decode(param1)>0)
					increment=decode(param2);

			return increment;
		}

		int64_t& decode(const string&s){
			if(isalpha(s[0]))
				return memory[s[0]];

			voida=std::atoll(s.c_str());
			return voida;
		}

		void printOut(){
			queue<int64_t> q(out);
			while(q.size())
			{
				cout<<q.front()<<",";
				q.pop();
			}
			cout<<endl;
		}

		int64_t soundRegister;
		queue<int64_t> in,out;
		bool ns,soundMode=true;
		map<char,int64_t> memory;
		int64_t voida=0;
	};

	struct program{
			void getInstruction(ifstream& i){
				string ins;
				i>>ins;
				if(i.good()){
					instruction.emplace_back(ins);
					param1.emplace_back();
					param2.emplace_back();
					i>>param1.back();

					if(instruction.back()!="snd"&&instruction.back()!="rcv")
						i>>param2.back();
				}
			}
			vector<string> instruction;
			vector<string> param1;
			vector<string> param2;
		};


	day18(const char* filename){
		ifstream i(filename);
		while(i.good())
			p.getInstruction(i);

	}


	void getResult(){
		computer c;
		for(int64_t i=0;(uint64_t)i<p.instruction.size();)
		{
			if(c.ns)
			{
				cout<<"Sound "<<c.soundRegister<<endl;
				break;
			}
			i+=c.execute(p.instruction[i],p.param1[i],p.param2[i]);
		}

	}

	void getResult2(){
		computer c1,c2;
		c1.soundMode=c2.soundMode=false;
		c2.memory['p']=1;
		uint64_t i1=0,i2=0,count=0;
		int64_t inc1=0,inc2=0;
		while(i1<p.instruction.size()||i2<p.instruction.size()){

			if((i1<p.instruction.size()))
			{
				inc1=c1.execute(p.instruction[i1],p.param1[i1],p.param2[i1]);
				i1+=inc1;
			}

			while(c1.out.size())
			{
				c2.in.emplace(c1.out.front());
				c1.out.pop();
			}

			if((i2<p.instruction.size()))
			{
				inc2=c2.execute(p.instruction[i2],p.param1[i2],p.param2[i2]);
				i2+=inc2;
			}

			while(c2.out.size())
			{
				c1.in.emplace(c2.out.front());
				c2.out.pop();
				count++;
			}

			if(inc1==0&&inc2==0)
				break;
		}

		cout<<"times prog1 send a val "<<count<<endl;
	}

	program p;


};



#endif
