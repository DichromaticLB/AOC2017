#ifndef INCLUDE_DAY17_HPP_
#define INCLUDE_DAY17_HPP_
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

struct day17{

	struct node{
		node(){
			val=0;
			prev=this;
			next=this;
		}

		uint32_t val;
		node *prev,*next;

		node* insert(uint32_t val,uint32_t iter){
			if(!iter)
			{
				node* n=new node();
				n->val=val;
				next->prev=n;
				n->next=next;
				next=n;
				n->prev=this;
				return n;
			}
			else
				return next->insert(val,iter-1);
		}
	};

	day17(uint32_t cycle){
		this->cycle=cycle;
	}


	void getResult(){
		node n=this->n;
		node* p=&n;
		for(uint32_t i=1;i!=2018;i++)
		{
			p=p->insert(i,cycle);
		}
		cout<<p->next->val<<endl;

	}

	void getResult2(){

		uint64_t count=1,next=0,at=0;

		for(uint32_t i=1;i!=50000001;i++)
		{
			at=(at+cycle)%count;
			if(at==0)
				next=i;
			at++;
			count++;
		}

		cout<<"Next val "<<next<<endl;

	}

	uint32_t cycle;
	node n;


};



#endif
