#include <bits/stdc++.h>
using namespace std;

class PageRep 
{
	public:
		void FIFO(vector<int>,vector<int>);
		void LRU(vector<int>,vector<int>);
};

void PageRep::FIFO(vector<int> ref_str,vector<int> frames)
{
	int hits=0,faults=0,idx=0;
	cout<<"FIFO Page Replacement :-"<<endl;
	for(int i=0;i<ref_str.size();i++)
	{
		int isHit=0;
		for(int j=0;j<frames.size();j++)
		{
			if(frames[j]==ref_str[i])
			{
				isHit=1;
				break;
			}
		}
		if(!isHit)
		{
			cout<<"Page "<<ref_str[i]<<" : Fault ";
			int pos = idx%frames.size();
			frames[pos] = ref_str[i];
			for(int j=0;j<frames.size();j++)
				cout<<frames[j]<<" ";
			cout<<endl;
			faults++;
			idx++;
		}
		else
		{
			cout<<"Page "<<ref_str[i]<<" : Hit ";
			for(int j=0;j<frames.size();j++)
				cout<<frames[j]<<" ";
			cout<<endl;
			hits++;
		}
	}
	cout<<"Page Faults :- "<<faults<<" Hits :- "<<hits<<endl;
	
}

void PageRep::LRU(vector<int> ref_str,vector<int> frames)
{
	int hits=0,faults=0;
	vector<int> lru;
	cout<<"LRU Page Replacement :-"<<endl;
	for(int i=0;i<ref_str.size();i++)
	{
		int isHit=0;
		for(int j=0;j<frames.size();j++)
		{
			if(frames[j]==ref_str[i])
			{
				isHit=1;
				break;
			}
		}
		if(!isHit)
		{
			cout<<"Page "<<ref_str[i]<<" : Fault ";
			if(lru.size()==frames.size())
			{
				int frame = lru[0];
				lru.erase(lru.begin());
				lru.push_back(ref_str[i]);
				for(int j=0;j<frames.size();j++)
				{
					if(frame==frames[j])
					{
						frames[j] = ref_str[i];
						break;
					}
				}
			}
			else
			{
				lru.push_back(ref_str[i]);
				frames[lru.size()-1] = ref_str[i];
			}
			for(int j=0;j<frames.size();j++)
				cout<<frames[j]<<" ";
			cout<<endl;
			faults++;
		}
		else
		{
			cout<<"Page "<<ref_str[i]<<" : Hit ";
			for(int j=0;j<frames.size();j++)
				cout<<frames[j]<<" ";
			cout<<endl;
			for(int j=0;j<lru.size();j++)
			{
				if(lru[j]==ref_str[i])
				{
					lru.erase(lru.begin()+j);
					lru.push_back(ref_str[i]);
				}
			}
			hits++;
		}
	}
	cout<<"Page Faults :- "<<faults<<" Hits :- "<<hits<<endl;
}

int main()
{
	int n,m;
	cout<<"Enter the no of pages :-";
	cin>>n;
	vector<int> ref_str(n);
	cout<<"Enter the reference string :-";
	for(int i=0;i<n;i++)
		cin>>ref_str[i];
	cout<<"Enter the no of frames :-";
	cin>>m;
	vector<int> frames(m,-1);
	PageRep pg;
	pg.FIFO(ref_str,frames);
	pg.LRU(ref_str,frames);
	return 0;
}
