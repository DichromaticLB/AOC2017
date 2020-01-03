#ifndef INCLUDE_DAY25_HPP_
#define INCLUDE_DAY25_HPP_
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
#include<regex>

using namespace std;

struct day25{

	struct action{
		action(){move=write=nextState=0;}
		action(istream&i):action(){
			string s;
			std::cmatch cm;
			std::getline(i,s);

			const string matches[]={
					"    - Write the value ([0-1])\\.",
					"    - Move one slot to the ([a-z]+)\\.",
					"    - Continue with state ([A-Z])\\."
			};

			while(i.good()){
				if(regex_match(s,regex(matches[0]))){
					regex_match(s.c_str(),cm,regex(matches[0]));
					write=cm[1].first[0]-'0';
					break;
				}
				std::getline(i,s);
			}

			while(i.good()){
				if(regex_match(s,regex(matches[1]))){
					regex_match(s.c_str(),cm,regex(matches[1]));
					move=cm[1].first[0]=='r'?1:-1;
					break;
				}
				std::getline(i,s);
			}

			while(i.good()){
				if(regex_match(s,regex(matches[2]))){
					regex_match(s.c_str(),cm,regex(matches[2]));
					nextState=cm[1].first[0];
					break;
				}
				std::getline(i,s);
			}
		}
		int move;
		int write;
		char nextState;
	};

	struct state{
		state():name(' '){}
		state(istream& i):state(){
			string s;
			std::cmatch cm;
			std::getline(i,s);
			const string matches[]={
					"In state ([A-Z]):"
			};

			while(i.good()){
				if(regex_match(s,regex(matches[0]))){
					regex_match(s.c_str(),cm,regex(matches[0]));
					name=cm[1].first[0];
					break;
				}
				std::getline(i,s);
			}

			zero=action(i);
			one=action(i);
		}

		action& operator[](char c){
			if(c==1)
				return one;
			return zero;
		}

		char name;
		action zero,one;
	};

	day25(const char* filename){
		ifstream i(filename);
		steps=0;
		while(i.good()&&!isdigit(i.peek()))
			i.ignore();
		i>>steps;

		while(i.good()){
			state s(i);
			if(i.good())
				states[s.name]=s;
		}

	}

	void getResult(){
		char state='A';
		int32_t index=0,total1=0;
		map<int32_t,char> tape;

		for(uint32_t i=0;i<steps;i++){
			char nextState=states[state][tape[index]].nextState;
			int32_t nextIndex=index+states[state][tape[index]].move;
			tape[index]=states[state][tape[index]].write;
			state=nextState;
			index=nextIndex;
		}

		for(auto&v:tape)
			if(v.second)
				total1++;

		cout<<"Total ones: "<<total1<<endl;
	}


	void getResult2(){
		std::cout<<"Merry Christmas!"<<endl;
	}


	uint32_t steps;
	map<char,state> states;
};



#endif
