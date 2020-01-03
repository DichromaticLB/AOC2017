#ifndef INCLUDE_DAY4_HPP_
#define INCLUDE_DAY4_HPP_
#include<iostream>
#include<string>
#include<cstdint>
#include<fstream>
#include<vector>
#include<limits>
#include<map>
#include<algorithm>
using namespace std;

struct day4{

	day4(const string& filename){
		ifstream i(filename);
		map<string,int> currentPass;

		while(i.good()){
			if(i.peek()=='\n')
			{
				i.ignore();
				password.push_back(currentPass);
				currentPass.clear();
			}

			string s;
			i>>s;
			currentPass[s]++;
		}

	}

	void getResult(){
		uint32_t good=0;
		for(auto& pass:password)
		{
			good++;
			for(auto&v:pass)
			{
				if(v.second>1)
				{
					good--;
					break;
				}
			}
		}
		cout<<"Valid password count: "<<good<<endl;
	}



	using charcount=map<char,uint32_t>;
	using scount=std::pair<const char, uint32_t>;

	static charcount fromString(const string&s){
		charcount res;

		for(auto&c:s)
			res[c]++;

		return res;
	}

	static bool compare(const charcount&a,const charcount&b){
		if(a.size()!=b.size())
			return false;

		for(auto&i:a)
		{
			if(!b.count(i.first))
				return false;

			if(b.at(i.first)!=i.second)
				return false;
		}

		return true;
	}

	void getResult2(){
		std::vector<map<charcount,uint8_t>> passwords;
		uint32_t good=0;

		for(auto&pass:password)
		{
			good++;
			passwords.emplace_back();
			for(auto&word:pass)
			{
				auto cc=fromString(word.first);
				passwords.back()[cc]++;
				if(word.second>1||passwords.back()[cc]>1)
				{
					good--;
					break;
				}

			}
		}


		cout<<"Valid pass count2:"<<good<<endl;
	}

	std::vector<map<string,int>> password;

};



#endif
