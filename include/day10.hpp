#ifndef INCLUDE_DAY10_HPP_
#define INCLUDE_DAY10_HPP_
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
using namespace std;




struct day10{

	struct vlist:public std::vector<int64_t>
	{
		int64_t& operator[](int64_t index){
			if(index<0)
			{
				auto add=(index/(int64_t)size())*size();
				index-=add;
			}

			return std::vector<int64_t>::operator []((index+size())%size());
		}

		vlist sublist(int64_t begin,int64_t length){
			vlist res;
			for(int64_t l=0;l<length;l++)
				res.push_back(operator [](begin+l));

			return res;
		}

		void merge(const vlist&v,int64_t dex){
			for(auto&vv:v)
				(*this)[dex++]=vv;
		}

		void invert(){
			vlist me=*this;
			uint64_t dex=0;
			for(auto e=me.rbegin();e!=me.rend();e++)
			{
				(*this)[dex++]=*e;
			}
		}

		int64_t doxor(){
			return accumulate(begin(),end(),0,[](auto a,auto b){return a^b;});
		}


	};


	day10(const string& filename){
		ifstream i(filename);
		int64_t l;
		i>>l;
		while(i.good())
		{
			i.ignore();
			lengths.push_back(l);
			i>>l;
		}
		i.close();
		i=ifstream(filename);
		char c;

		i>>c;

		while(i.good())
		{
			lengths2.push_back(c);
			i>>c;
		}

		lengths2.push_back(17);
		lengths2.push_back(31);
		lengths2.push_back(73);
		lengths2.push_back(47);
		lengths2.push_back(23);
	}

	void getResult(){
		uint32_t skip=0;
		uint32_t index=0;
		vlist data;
		for(int64_t i=0;i<256;i++)
			data.push_back(i);

		for(auto&l:lengths)
		{
			vlist sub=data.sublist(index,l);
			sub.invert();
			data.merge(sub,index);
			index+=l+skip;
			skip++;
		}

		cout<<(data[0]*data[1])<<endl;

	}


	void getResult2(){
		uint32_t skip=0;
		uint32_t index=0;
		vlist data;

		for(int64_t i=0;i<256;i++)
			data.push_back(i);

		for(uint32_t i=0;i<64;i++)
			for(auto&l:lengths2)
			{
				vlist sub=data.sublist(index,l);
				sub.invert();
				data.merge(sub,index);
				index+=l+skip;
				skip++;
			}

		ostringstream o;

		for(uint32_t i=0;i<16;i++)
			o<< std::setfill('0') << std::setw(2)<<std::hex<<(int64_t)data.sublist(i*16,16).doxor();

		cout<<o.str()<<endl;
	}

	static vector<char> doHash(string input)
	{
		vector<char> res;
		uint32_t skip=0;
		uint32_t index=0;
		vlist data;
		input.push_back(17);
		input.push_back(31);
		input.push_back(73);
		input.push_back(47);
		input.push_back(23);

		for(int64_t i=0;i<256;i++)
			data.push_back(i);

		for(uint32_t i=0;i<64;i++)
			for(uint8_t l:input)
			{
				vlist sub=data.sublist(index,l);
				sub.invert();
				data.merge(sub,index);
				index+=l+skip;
				skip++;
			}


		for(uint32_t i=0;i<16;i++)
			res.push_back(data.sublist(i*16,16).doxor());

		return res;
	 }

	vlist lengths;
	vlist lengths2;
};



#endif
