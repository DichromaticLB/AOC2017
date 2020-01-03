#ifndef INCLUDE_DAY13_HPP_
#define INCLUDE_DAY13_HPP_
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




struct day13{

	day13(const string& filename){
		ifstream i(filename);
		uint32_t layer,length;
		i>>layer;
		i.ignore();
		i>>length;
		while(i.good())
		{
			layers.resize(layer+1);
			layers[layer]=length;
			i>>layer;
			i.ignore();
			i>>length;

		}

	}

	uint32_t pos(uint32_t layer,uint32_t time){
		return time%((layers[layer]-1)*2);
	}

	void getResult(){

		uint32_t res=0;
		for(uint32_t i=0;i<layers.size();i++)
			if(layers[i]&&pos(i,i)==0)
				res+=i*layers[i];
		cout<<res<<endl;
	}

	void getResult2(){
		uint32_t shift=1;
		while(true)
		{
			for(uint32_t i=0;i<layers.size();i++)
				if(layers[i]&&pos(i,i+shift)==0)
				{
					shift++;
					break;;
				}
				else if(i==layers.size()-1)
				{
					cout<<"Delay part 2 "<<shift<<endl;
					return;
				}
		}

	}

	vector<uint8_t> layers;
};



#endif
