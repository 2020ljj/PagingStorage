#include"head.h"
int main() {
	vector<int> address_Q ={ 7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1 };
	int m,ch,hitnum;
	double hitrate;
	cout << "输入物理块数字：\n";
	cin >> m;
	while(1) {
		cout << "**************输入选择的置换算法：**************\n";
		cout << "**************1.FIFO**************\n";
		cout << "**************2.LRU**************\n";
		cout << "**************3.OPT**************\n";
		cin >> ch;
		switch (ch)
		{
		case 1: {
			hitnum = FIFOCache(m, address_Q);
			hitrate = (double)hitnum / (double)address_Q.size();
			cout << "FIFO命中率为：" << hitrate * 100 << "%" << '\n';
			break;
		}
		case 2: {
			hitnum = LRUCache(m, address_Q);
			hitrate = (double)hitnum / (double)address_Q.size();
			cout << "LRU命中率为：" << hitrate * 100 << "%" << '\n';
			break;
		}
		case 3: {
			hitnum = OPTCache(m, address_Q);
			break;
		}
		default:
			cout << "输入有误！\n";
			break;
		}
	
	
	}




	return 0;
}