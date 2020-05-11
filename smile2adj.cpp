#include "mylib.h"
#include <bits/stdc++.h>

using namespace std;

#define ELEMENT_NOT_FOUND -1
#define BUF_SZ 4096
#define alpha(a) (a>=0 && a< 26)
#define RNG_SIZE 50

class PeriodTable
{
	int element2[26][26];  
	int element1 [58]; // A~Z ~ a~z
	static const char* vElement [123];  //118 elements + 5 aromatic elements
	static const int oElement [123];
	static const set<int> organicsubset;
	static PeriodTable* p;
	PeriodTable(){
		memset(element2,ELEMENT_NOT_FOUND,sizeof(element2));
		memset(element1,ELEMENT_NOT_FOUND,sizeof(element1));
		const char* t;
		int idx;
		int cnt = sizeof(vElement)/sizeof(*vElement);
		for(int i=0;i<cnt;++i)
		{
			t = vElement[i];
			idx = t[1]-'a';
			if(alpha(idx))
			{
				element2[t[0]-'A'][idx] = i;
			}
			else
			{
				element1[t[0]-'A'] = i;
			}
		}
	};
	
public:
	int getIdx(char str[], bool one);
	static const char* idx2element(int idx);
	static void ini();
	static const int idx2order(int idx);
	inline static PeriodTable* instance();
	static bool isorganic(int idx);
};

const char* PeriodTable::vElement[] = {
		"H",
		"He",
		"Li",
		"Be",
		"B",
		"C",
		"N",
		"O",
		"F",
		"Ne",
		"Na",
		"Mg",
		"Al",
		"Si",
		"P",
		"S",
		"Cl",
		"Ar",
		"K",
		"Ca",
		"Sc",
		"Ti",
		"V",
		"Cr",
		"Mn",
		"Fe",
		"Co",
		"Ni",
		"Cu",
		"Zn",
		"Ga",
		"Ge",
		"As",
		"Se",
		"Br",
		"Kr",
		"Rb",
		"Sr",
		"Y",
		"Zr",
		"Nb",
		"Mo",
		"Tc",
		"Ru",
		"Rh",
		"Pd",
		"Ag",
		"Cd",
		"In",
		"Sn",
		"Sb",
		"Te",
		"I",
		"Xe",
		"Cs",
		"Ba",
		"La",
		"Ce",
		"Pr",
		"Nd",
		"Pm",
		"Sm",
		"Eu",
		"Gd",
		"Tb",
		"Dy",
		"Ho",
		"Er",
		"Tm",
		"Yb",
		"Lu",
		"Hf",
		"Ta",
		"W",
		"Re",
		"Os",
		"Ir",
		"Pt",
		"Au",
		"Hg",
		"Tl",
		"Pb",
		"Bi",
		"Po",
		"At",
		"Rn",
		"Fr",
		"Ra",
		"Ac",
		"Th",
		"Pa",
		"U",
		"Np",
		"Pu",
		"Am",
		"Cm",
		"Bk",
		"Cf",
		"Es",
		"Fm",
		"Md",
		"No",
		"Lr",
		"Rf",
		"Db",
		"Sg",
		"Bh",
		"Hs",
		"Mt",
		"Ds",
		"Rg",
		"Cn",
		"Nh",
		"Fl",
		"Mc",
		"Lv",
		"Ts",
		"Og",
		"c",
		"n",
		"o",
		"p",
		"s",
	};
	
const int PeriodTable::oElement[] = {
	1,
	0,
	1,
	2,
	3,
	4,
	3,
	2,
	1,
	0,
	1,
	2,
	3,
	4,
	5,
	6,
	1,
	0,
	1,
	2,
	3,
	4,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	1,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	1,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	4,
	3,
	2,
	3,
	2
};

const set<int> PeriodTable::organicsubset={4,5,6,7,8,14,15,16,34,52};

bool PeriodTable::isorganic(int idx)
{
	auto it4 = PeriodTable::organicsubset.find(idx);
	if(it4!=PeriodTable::organicsubset.end())
	{
		return true;
	}
	return false;
}
int PeriodTable::getIdx(char str[], bool one)  //not secure , must be in str[0] :Upper str[1]: Lower, must with length larger than 1 or 2
{
	if(one)
	{
		return element1[str[0]-'A'];
	}
	else 
	{
		return element2[str[0]-'A'][str[1]-'a'];
	}
}
const char* PeriodTable::idx2element(int idx)
{
	return vElement[idx];
}
PeriodTable* PeriodTable::p = NULL;
void PeriodTable::PeriodTable::ini()
{
	if(!p)
		p = new PeriodTable;
}
PeriodTable* PeriodTable::instance()
{
	return p;
}
const int PeriodTable::idx2order(int idx)
{
	return oElement[idx]; 
}

class Graph
{
public:
	vector<int> index2atomidx;    //node idx to atom idx
	map<int,char> index2atomcharge;   //node idx to charge
	map<int,bool> index2atomchiral;    //node idx to chirality
	map<int,int> index2hydrogencount;  //node idx to hydrogen count
	map<int,int> index2isotopemass;  //node idx to isotope mass
	set<int> index2squarebracket;  //node idx to square bracket
	map<int,int> index2ezcarbons;  //node idx to those ez carbons with format     x(=,/a,\b) //or x(/a,\b,=) or x(\b,=,/a)
	                               //if encounter '/' , label next atom as potential center   (idx, false) , with slash num 1, and continue   //false = -1*slashnum, true=1*slashnum
								   //after iterate over its childs, if there is double bond, change it to (idx,true) and rearrange its childs
								   //also consider the atom after '=', if pre is '=' and it has child that is already center(we know that already since it has a child with '=')
								   //then we mark this atom as center as well
	
	vector<vector<int> > adj;    //only deal with tetrahedral type, if @(true) then 1 2 3 elif @@(false) then 3 2 1
	                                 //array of fixed arrays   for ex  C: 4 , N:3 , O:2
									 //double bond: -2, triple bond:-3, as nodes
	Graph(char smiles[]);
	void addEdge(int v, int w);
	void printadj();
	void printezcarbons();
	string idx2str(int idx, int parent);
	void DFS(int s);
	int BFSheight(int root);
	int checkcenter();
	int fastcenter();
};

Graph::Graph(char smiles[])
{
	char c;   //current char
	int idx = 0;   //current idx
	int pre = ELEMENT_NOT_FOUND;       //last node idx
	int atomidx=ELEMENT_NOT_FOUND;    //current atom idx
	stack<int> round_pre;   // record the index of the element before round '(', if encounter ')' put top element to be the pre;
	int ring_idx2node_idx[RNG_SIZE];    //ring number to node idx
	int ring_idx2child_idx[RNG_SIZE];   //, the n-th child 
	memset(ring_idx2node_idx,ELEMENT_NOT_FOUND,sizeof(ring_idx2node_idx));  //initialize with -1
	
	//int cnt;
	bool squarebracket = false;
	int squaretop;    // [XAB]C we know that X is connected to C
	
	bool isotope = false;
	int isomass;
	
	bool chiralH = false;
	bool slashnext = false;
	int slashnum = 0;
	
	//fprintf(stderr,"%s\n",smiles);
	
	while((c=smiles[idx])!='\n')
	{
		//fprintf(stderr,"%c %d %d %d\n",c,idx,pre,atomidx);
		if(isalpha(c))
		{
			if(islower(smiles[idx+1]))
			{
				atomidx = PeriodTable::instance()->getIdx(smiles+idx,false);
				if(atomidx == ELEMENT_NOT_FOUND)
				{
					atomidx = PeriodTable::instance()->getIdx(smiles+idx,true);
					if(atomidx == ELEMENT_NOT_FOUND)
						fprintf(stderr,"error at idx %d\n",idx);
					idx++;
				}
				else idx+=2;
			}
			else if(c=='H' && pre!=ELEMENT_NOT_FOUND && !chiralH && !squarebracket)
			{
				if(isdigit(smiles[idx+1]))
				{
					index2hydrogencount[pre] = smiles[idx+1]-'0';
					idx+=2;
				}
				else
				{
					index2hydrogencount[pre] = 1;
					idx++;
				}
				continue;
			}
			else
			{
				atomidx = PeriodTable::instance()->getIdx(smiles+idx,true);
				if(atomidx == ELEMENT_NOT_FOUND)
					fprintf(stderr,"error at idx %d\n",idx);
				idx++;
			}
			
			index2atomidx.push_back(atomidx);
			int tpre = index2atomidx.size()-1;
			
			adj.push_back(vector<int>());
			
			if(pre!=ELEMENT_NOT_FOUND)
			{
				addEdge(pre,tpre);
			}
			
			if(index2atomidx[pre]==-2) // if previous one is "="
			{
				auto it = index2ezcarbons.find(pre);
				if(it!=index2ezcarbons.end() )
				{
					index2ezcarbons[tpre] = 0; // this atom is also center
				}
			}
			
			
			pre = tpre;
			if(squarebracket)
			{
				squaretop = pre;
				index2squarebracket.insert(pre);
				squarebracket = false;
			}
			if(isotope)
			{
				index2isotopemass[pre] = isomass;
				isotope = false;
				//fprintf(stderr,"%d\n",isomass);
			}
			if(slashnext)
			{
				index2ezcarbons[pre] = - slashnum;
				slashnext = false;
			}
			
			
			chiralH = false;
		}
		else if(c=='(')
		{
			round_pre.push(pre);
			idx++;
		}
		else if(c=='[')
		{
			squarebracket = true;
			idx++;
		}
		else if(isdigit(c))    //the charge and hydrogen condition are prejudged, so only isotope and rings consider here
		{
			if(squarebracket)
			{
				char d ;
				isotope = true;
				isomass = 0;
				while(isdigit((d=smiles[idx])))
				{
					isomass = (isomass<<3) + (isomass<<1) + (d-'0');
					idx++;
				}
				//fprintf(stderr,"%d\n",isomass);
				continue;
				
			}
				
			if(ring_idx2node_idx[c-'0']==ELEMENT_NOT_FOUND)
			{
				ring_idx2node_idx[c-'0'] = pre;
				adj[pre].push_back(-1);
				ring_idx2child_idx[c-'0'] = adj[pre].size()-1;
				//fprintf(stderr,"ring first encounter at pre=%d\n",pre);
			}
			else
			{
				int rnum = c-'0';
				int ringpre = ring_idx2node_idx[rnum];
				adj[pre].push_back(ringpre);
				adj[ringpre][ring_idx2child_idx[rnum]] = pre;
				ring_idx2node_idx[rnum] = ELEMENT_NOT_FOUND;
			}
			idx++;
		}
		else if(c=='=')
		{
			atomidx = -2;
			index2atomidx.push_back(atomidx);
			adj.push_back(vector<int>());
			addEdge(pre,index2atomidx.size()-1);
			auto it = index2ezcarbons.find(pre);
			int tpre =index2atomidx.size()-1;
			if(it!=index2ezcarbons.end())
			{
				(*it).second = -(it->second);  // this is a true center
				index2ezcarbons[tpre]  = 0 ;// add "=" to the map with zero val
				if(adj[pre].size()==2)
				{
					if(it->second == 1)  //(/a, =, \b) -> ( = , /a, \b)
					{
						adj[pre][0]^=adj[pre][1];
						adj[pre][1]^=adj[pre][0];
						adj[pre][0]^=adj[pre][1];
					}
				}
				else
				{
					if(it->second == 2)             //  (\b,/a, =)-> (/a, \b, =)
					{
						adj[pre][0]^=adj[pre][1];
						adj[pre][1]^=adj[pre][0];
						adj[pre][0]^=adj[pre][1];
					}
					
				}
			}
			pre = tpre;
			idx++;
		}
		else if(c=='#')
		{
			atomidx = -3;
			index2atomidx.push_back(atomidx);
			adj.push_back(vector<int>());
			addEdge(pre,index2atomidx.size()-1);
			pre = index2atomidx.size()-1;
			idx++;
		}
		else if(c=='+' || c=='-')
		{
			char nextc = smiles[idx+1];
			int charge=1;
			if(isdigit(nextc))
			{
				charge = nextc-'0';
				idx+=2;
			}
			else idx++;
			if(c=='+')
				index2atomcharge[pre] = charge;
			else
				index2atomcharge[pre] = -charge;
		}
		else if(c==']')
		{
			pre = squaretop;
			idx++;
		}
		else if(c==')')
		{
			pre = round_pre.top();
			round_pre.pop();
			idx++;
		}
		else if(c=='@')
		{
			if(smiles[idx+1]=='@')
			{
				index2atomchiral[pre] = false;
				idx+=2;
			}
			else
			{
				index2atomchiral[pre] = true;
				idx++;
			}
			chiralH = true;
		}
		else if(c=='.')
		{
			pre = ELEMENT_NOT_FOUND; 
			idx++;
		}
		else if(c=='/')    //SMILES support only cis and trans
		{
			if(index2ezcarbons.find(pre)!=index2ezcarbons.end() && adj[pre].size()==2)   //previous atom is center
			{
				adj[pre][0]^=adj[pre][1];
				adj[pre][1]^=adj[pre][0];
				adj[pre][0]^=adj[pre][1];                   //(=,\b, /a ) -> (\b, =, /a)
			}
			slashnext = true;
			slashnum = 1;
			idx++;
		}
		else if(c=='\\')
		{
			if(index2ezcarbons.find(pre)!=index2ezcarbons.end() && adj[pre].size()==1)   //previous atom is center
			{
				adj[pre][0]^=adj[pre][1];
				adj[pre][1]^=adj[pre][0];
				adj[pre][0]^=adj[pre][1];                   //(=,\b,/a ) -> (\b, =, /a)
			}
			slashnext = true;
			slashnum = 2;
			idx++;
		}
		else 
		{
			fprintf(stderr,"Not support yet: %c\n",c);
			exit(EXIT_FAILURE);
		}
			
			
		
	}
}

void Graph::addEdge(int v,int w)
{
	adj[v].push_back(w);
	adj[w].push_back(v);
}

void Graph::printadj()
{
	for(int i=0;i<adj.size();i++)
	{
		fprintf(stderr,"%d ",i);
		for(int j=0;j<adj[i].size();j++)
		{
			fprintf(stderr,"%d ",adj[i][j]);
		}
		fprintf(stderr,"\n");
	}
		
}

void Graph::printezcarbons()
{
	fprintf(stderr,"EZcarbons:\n");
	for(auto it=index2ezcarbons.begin();it!=index2ezcarbons.end();++it)
	{
		fprintf(stderr,"%d %d\n",it->first,it->second);
	}
}
string Graph::idx2str(int idx, int parent)
{
	int atomidx = index2atomidx[idx];
	if(atomidx==-2)
		return "=";
	else if(atomidx==-3)
		return "#";
	
	string res = PeriodTable::idx2element(atomidx);
	bool bracket = false;
	
	auto it3 = index2hydrogencount.find(idx);
	if(it3!=index2hydrogencount.end())
	{
		if(it3->second>1)
			res+="H"+to_string(it3->second);
		else
			res+="H";
		bracket = true;
	}
	auto it=index2atomcharge.find(idx);
	
	if(it!=index2atomcharge.end())
	{
		if(it->second>0)
		{
			if(it->second>1)
				res+="+"+to_string(it->second);
			else
				res+="+";
		}
		else
		{
			if(-it->second>1)
				res+="-"+to_string(-it->second);
			else
				res+="-";
		}
		bracket = true;
	}
	auto it2=index2atomchiral.find(idx);
	if(it2!=index2atomchiral.end())
	{
		if(it2->second)
		{
			res+="@";
		}
		else
		{
			res+="@@";
		}
		bracket = true;
	}
	
	if(!PeriodTable::isorganic(atomidx))
		bracket = true;
	
	auto it4=index2isotopemass.find(idx);
	if(it4!=index2isotopemass.end())
	{
		res = to_string(it4->second)+res;
		bracket = true;
	}
	
	
	
	if(!bracket)
	{
		if(index2squarebracket.find(idx)!=index2squarebracket.end())
		{
			bracket = true;
		}
	}
	if(bracket)
	{
		res = "[" + res + "]";
	}
	
	auto it5 = index2ezcarbons.find(idx);
	if(it5!=index2ezcarbons.end()&& atomidx!=-2 && it5->second>=0)
	{
		if(index2atomidx[parent]==-2)
		{
			int d;
			for(int i=0;i<adj[idx].size();i++)
			{
				if(adj[idx][i]==parent)
				{
					d = i;
					break;
				}
			}
			//fprintf(stderr,"d:%d\n",d);
			if(((d+1)%3)==0 || d==0)
			{
				res += "/";
			}
			else
			{
				res+= "\\";
			}
		}
		else
		{
			int p,d;
			for(int i=0;i<adj[idx].size();i++)
			{
				if(adj[idx][i]==parent)
				{
					p = i;
				}
				else if(index2atomidx[adj[idx][i]]==-2)
				{
					d = i;
				}
			}
			//fprintf(stderr,"d:%d p:%d\n",d,p);
			if( p == ((d+1)%3))
			{
				res = "/"+res;
			}
			else
			{
				res = "\\"+res;
			}
		}
		
	}
	
	//fprintf(stderr,"%s\n",res.c_str());
	return res;
}

int BFSheight(bool* color,int root, int paintnum)
{
	
	int* height = new bool[adj.size()-1]();
	queue<int> q;
	visited[root] = paintnum;
	q.push(root);
	height[root]=0;
	int child;
	
	while(!q.empty())
	{
		root = q.front();
		q.pop();
		for(int i=0;i<adj[root].size();++i)
		{
			child = adj[root][i];
			if(!visited[child])
			{
				visited[child] = paintnum;
				height[child] = height[root]+1;
				q.push(child);
			}
		}
	}
	int maxheight = -1;
	for(int i=0;i<adj.size();++i)
	{
		maxheight = height[i]>maxheight?height[i]:maxheight;
	}
	delete [] height;
	return maxheight;
	
}
int checkcenter()  //need to consider disconnected component in the future
{
	int* color = new int[adj.size()-1]();  //color 1 means first component, color 2 means second component...
	int paintnum = 0;
	vector<int> minheight;
	int t;
	for(int i=0;i<adj.size();++i)
	{
		if(!color[i])
		{
			paintnum++;
			minheight.push_back(INT_MAX);
		}
		t = BFSheight(color,i,paintnum);
		if(t<minheight[paintnum-1] )
			minheight[paintnum-1] = t;
		
	}
	delete [] color;
	return minheight[0];
}
class Smiles
{
	Graph* g;
	string smiles;
	map<unsigned long long,int> tocyclenum;    //pair of parent & child will be substitute to cycle num later
	int cyclecnt;
	//bool* cyclenumused;
public:
	Smiles(Graph* gin);
	string smilesutil(int v, bool visited[], int parent);
	void print(FILE* f);
};
Smiles::Smiles(Graph* gin) 
{ 
    g = gin;
	int V = g->adj.size();
    // Mark all the vertices as not visited 
    bool *visited = new bool[V]; 
    for (int i = 0; i < V; i++) 
        visited[i] = false; 
	
	cyclecnt=0;
	//cyclenumused = new bool[9]();
	srand(time(NULL));
	int rd;
	assert(V==g->index2atomidx.size());
	assert(V>0);
	while(g->index2atomidx[(rd=rand()%V)]<0 || (g->index2ezcarbons.find(rd)!=g->index2ezcarbons.end() && g->index2ezcarbons[rd]>=0));
	smiles = smilesutil(rd, visited, -1);
	//fprintf(stderr,"%s\n",smiles.c_str());
	for(int i=0;i<V;i++)
	{
		if(!visited[i])
			smiles+="."+smilesutil(i, visited, -1); 
	}
	delete [] visited;
	//delete [] cyclenumused;
} 
string Smiles::smilesutil(int v, bool visited[], int parent) 
{ 
    visited[v] = true; 
	int child;
	string res = g->idx2str(v,parent);
	int numofchild = g->adj[v].size();
	bool inverse = false;
	if(g->index2atomchiral.find(v)!=g->index2atomchiral.end() && (g->adj[v][1]==parent || g->adj[v][3]==parent))
	{
		inverse = true;
	}
	int i;
    for (int cnt = 0; cnt <numofchild; ++cnt) 
	{
		i = inverse? numofchild-cnt-1:cnt;
		child = g->adj[v][i];
		if (!visited[child]) 
			if(cnt!=numofchild-1)
				res+="("+smilesutil(child, visited,v)+")"; 
			else
				res+=smilesutil(child, visited,v);
		else if(child!=parent)
		{
			auto it = tocyclenum.find(((unsigned long long)child<<32 | v));
			if(it!=tocyclenum.end())
			{
				string mbond="";
				if(g->index2atomidx[child]<0)
				{
					if(g->index2atomidx[child]==-2)
						mbond = "=";
					else if(g->index2atomidx[child]==-3)
						mbond = "#";
				}
				if(it->second>=10)
					res+=mbond+"%"+to_string(it->second);
				else
					res+=mbond+to_string(it->second);
				//cyclenumused[it->second-1] = false;
			}
			else
			{
				/*if(cyclecnt = 9)
				{
					int j;
					for(j=0;j<9;j++)
					{
						if(!cyclenumused[j])
						{
							cyclecnt = j;
							break;
						}
					}
					if(j==9)
					{
						fprintf(stderr,"Too many ring number\n");
						exit(EXIT_FAILURE);
					}
				}*/
				tocyclenum[(unsigned long long)v<<32 | child] = ++cyclecnt;
				if(cyclecnt>=10)
					res+="%"+to_string(cyclecnt);
				else
					res+=to_string(cyclecnt);
				//cyclenumused[cyclecnt-1] = true;
			}
		}
	}
    return res;
} 
  


void Smiles::print(FILE* f=stdout)
{
      fprintf(f,"%s\n",smiles.c_str());
}
/*void Graph::DFS(int s) 
{ 
    // Initially mark all verices as not visited 
    vector<bool> visited(V, false); 
	int parent=-1;
	map<unsigned long long,int> tocyclenum;    //pair of parent & child will be substitute to cycle num later
	int cyclecnt=0;
    // Create a stack for DFS 
    stack<pair<int,int> > stack; 
  
    // Push the current source node. 
    stack.push(make_pair(s,parent)); 
	pair<int,int> spair;
	string smilestr = "";
  
    while (!stack.empty()) 
    { 
        // Pop a vertex from stack and print it 
        spair = stack.top(); 
        stack.pop(); 
		
  
        // Stack may contain same vertex twice. So 
        // we need to print the popped item only 
        // if it is not visited. 
		if(spair.first<0)
		{
			smilestr+=to_string(-spair.first);
			continue;
		}
        if (!visited[spair.first]) 
        { 
            smilestr+= "("+idxstr(spair.first);
            visited[s] = true; 
        } 
  
        // Get all adjacent vertices of the popped vertex s 
        // If a adjacent has not been visited, then push it 
        // to the stack. 
        for (int i=0; i != adj[spair.first].size(); ++i) 
		{
			int child = adj[spair.first][i];
			if (!visited[child]) 
			{
                stack.push(make_pair(child,spair.first)); 
			}
			else
			{
				auto it = tocyclenum.find(((unsigned long long)child<<32 | parent));
				if(it!=tocyclenum.end())
				{
					stack.push(make_pair(-it->second,spair.first));
				}
				else
				{
					tocyclenum[(unsigned long long)parent<<32 | child] = cyclecnt++;
				}
			}
		}
            
    } 
} */
void testGraph(char smiles[], FILE* fout)
{
	Graph *g = new Graph(smiles);
	//g.printadj();
	//g.printezcarbons();
	Smiles *s = new Smiles(g);
	s->print(fout);
	delete s;
	delete g;
}


void parseFile(FILE* fin, FILE* fout)
{
	char buf[BUF_SZ];
	//int limit = 3;
	while(fgets(buf,BUF_SZ,fin)!=NULL )//&& limit--)
	{
		//smile2adj(buf);
		testGraph(buf,fout);
	}
	fprintf(stderr,"finished\n");
}

void testPeroidTable()   //OK
{
	PeriodTable::ini();
	char t[] = "SClCOsPQQ";
	fprintf(stderr,"Construction complete\n");
	fprintf(stderr,"%d\n",PeriodTable::instance()->getIdx(t,true));
	fprintf(stderr,"%d\n",PeriodTable::instance()->getIdx(t+1,false));
	fprintf(stderr,"%d\n",PeriodTable::instance()->getIdx(t+3,true));
	fprintf(stderr,"%d\n",PeriodTable::instance()->getIdx(t+4,false));
	fprintf(stderr,"%d\n",PeriodTable::instance()->getIdx(t+6,true));
	if(PeriodTable::instance()->getIdx(t+7,true)==ELEMENT_NOT_FOUND)printf("Not found: %c\n",t[7]);
	fprintf(stderr,"Id: %d is element %s\n",16,PeriodTable::idx2element(16));
}


int main(int args, char** argv)
{
	if(args!=3)
	{
		fprintf(stderr,"Usage: ./smile2adj file.smi out.txt\n");
		return 1;
	}
	PeriodTable::ini();
	char* fname = argv[1];
	char* outfile = argv[2];
	FILE* fin = fopen(fname,"r");
	FILE* fout = fopen(outfile,"w");
	parseFile(fin,fout);
	fclose(fin);
	fclose(fout);
	//testPeroidTable();
	
	
}