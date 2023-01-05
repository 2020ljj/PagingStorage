#pragma once
#ifndef HEAD_H
#define HEAD_H
#include<iostream>
#include <iomanip>  
#include<list>
#include<unordered_map>
#include<map>
#include<vector>
using namespace std;
struct Order
{
	int id;       //序列号
	int num_page;  //访问页号
};
 struct Page
{
	int pagenum ;
	struct Page* next;
	Page() {
		pagenum = -1;
		next = NULL;
	}
	Page(int k) {
		pagenum = k;
		next = NULL;
	}
};

int FIFOCache(int m, vector<int> order) {//使用线性链表
	Page* head = new Page;
	Page* p = head;
	Page* old = head;
	for (int i = 0; i < m-1; i++) {
		Page* node = new Page;
		p->next = node;
		p = p->next;
	}
	int size = (int)order.size();
	int hitnum = 0;						//命中次数
	//查询内存中有无需要的页：
	for (int i = 0; i < size; i++) {
		p = head;
		while (p != NULL) {
			if (-1==p->pagenum ) {		//找到空的物理块，直接调入页面
				p->pagenum = order[i];
				break;
			}
			if (p->pagenum == order[i]) {//内存中找到对应的页，直接执行
				hitnum++;
				break;
			}
				
			p = p->next;
		}
		if (p == NULL) {					//内存已满且找不到对应的页，调入页面
			old->pagenum = order[i];
			old = ((old ->next== NULL)? head:old->next);//当替换指针指向最后一个块时，使它下次指向第一个块
		}

	}
	return hitnum;
	
}
int LRUCache(int m, vector<int> order) {//使用哈希表+链表来模拟（可以从中间弹出元素，但只能插入在最后（链首））
	int hitnum = 0;
	int size = order.size();
	list<Page> lst;
	unordered_map<int, list<Page>::iterator> ump;
	for (int i = 0; i < size; i++) {
		if (ump.find(order[i]) != ump.end()){//如果找到了
			lst.erase(ump[order[i]]);
			hitnum++;
		}
		else if (lst.size() >= m)			//如果没找到且 list容量已满
			{
				ump.erase(lst.back().pagenum);	//删除该页面在哈希中的记录//原本是key
				lst.pop_back();				//删除list中最后一个页面
			}
		//把新结点添加在list的头部
			lst.push_front({ order[i] });
		//保存结点到map中
			ump[order[i]] = lst.begin();
		}
	return hitnum;
}
int OPTCache(int m, vector<int> order) {
	int hitnum = 0;
	int size = order.size();
	int existpage = 0;						//内存中已有的页数目
	int p,index;
	vector<int> temp;
	unordered_map <int, vector<int>> mymap;  //key代表页面号，value代表页面出现的位置，如{1,4,7}
	map<int, int> ump;						//key代表页号，value代表块中的位置
	for (int i = 0; i < size; i++) {		//第一次遍历记录各页号需要调用的顺序
		temp = mymap[order[i]];
		temp.push_back(i);
		mymap[order[i]] = temp;
	}
	
	for (int i = 0; i < size; i++) {
		if (ump.find(order[i]) != ump.end()) {//找到了
			hitnum++;
		}
		else if (ump.size() < m) {			//没找到且内存未满
			ump[order[i]] = existpage;
		}
		else {								//没找到且内存已满
			std::map<int, int>::iterator iter = ump.begin();
			p = optselect(i, ump, mymap);
				while (iter!=ump.end()) {
					if (iter->first == p) {
						index = iter->second;
						ump.erase(iter);
						break;
					}
					iter++;
				}
`			ump[order[i]] = index;
		}
	}
	return hitnum;
}

int optselect(int i,map<int, int>,unordered_map <int, vector<int>>) {		//返回需要被替换的页面号

}
#endif // HEAD_H

