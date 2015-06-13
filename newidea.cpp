//Author : pakhandi
// Correct
using namespace std;

#include<bits/stdc++.h>

#define wl(n) while(n--)
#define fl(i,a,b) for(i=a; i<b; i++)
#define rev(i,a,b) for(i=a; i>=b; i--)
#define scan(n) scanf("%d", &n)
#define scans(s) scanf("%s", s)
#define scanc(c) scanf("%c", &c)
#define scanp(f) scanf("%f", &f)
#define print(n) printf("%d\n", n)
#define prints(s) printf("%s\n", s)
#define printc(c) printf("%c\n", c)
#define printp(f) printf("%f\n", f)
#define nline printf("\n")
#define mclr(strn) strn.clear()
#define ignr cin.ignore()
#define MOD 1000000007
#define ll long long int
#define u64 unsigned long long int

#define PB push_back
#define SZ size
#define MP make_pair
#define fi first
#define sec second

int n;
std::vector<string> mat;

int thisopx, thisopy;	//to store the this move of oponent;

//Moves for x & y
int dx1[]={+1,+1,0,-1,-1,-1,0,+1};
int dy1[]={0,+1,+1,+1,0,-1,-1,-1};

int dx2[]={-1,-1,0,+1,+1,+1,0,-1};
int dy2[]={0,-1,-1,-1,0,+1,+1,+1};

int dx[]={-1,-1,-1,0,0,+1,+1,+1};
int dy[]={-1,0,+1,-1,+1,-1,0,+1};

void baptize(int &x)
{
	x;
}

int isonboard(int x, int y)
{	
	if(x>=n || y>=n || x<0 || y<0 )
		return 0;
	return 1;
}

int isvalid(std::vector<string> curr_mat, int x, int y)	//a valid cell to move into
{
	if(x>=n || y>=n || x<0 || y<0 || curr_mat[x][y]!='0')
		return 0;
	return 1;
}

int issafe(std::vector<string> curr_mat, int myx, int myy, int opx, int opy)	//not gonna get killed in next move
{
	if(!isvalid(curr_mat,myx,myy))
		return 0;
	int i;
	fl(i,0,8)
	{
		if(isonboard(myx+dx[i],myy+dy[i]) && opx==myx+dx[i] && opy==myy+dy[i])
			return 0;
	}
	return 1;
}

int dfs(int level, std::vector<string> curr_mat, int myx, int myy, int opx, int opy)
{
	
	//std::vector<string> th = curr_mat;
	//cout<<level;nline;

	int ret;
	int j, i;
	/*cout<<"*********************";
	cout<<level<<" : ";
	nline;
	fl(i,0,n)
	{
		cout<<curr_mat[i];
		nline;
	}
	cout<<"*********************";*/
	if(level>10)
		return level;
	if(level%2==0)
	{
		int i;
		int f=0;
		fl(i,0,8)
		{
			if(isonboard(myx+dx[i],myy+dy[i]) && myx+dx[i]==opx && myy+dy[i]==opy)
				return level;
		}

		fl(i,0,n)
		{
			int caprow=1;
			fl(j,0,n)
			{
				if(mat[i][j]=='0' )
				{
					caprow=0;
					break;
				}
			}
			if(caprow==1)
			{
				if(myx>=0 && myx<caprow && caprow<n-1-caprow )
				{
					return level;
				}
				if(myx>caprow && myx<n && n-1-caprow<caprow)
					return level;
			}
		}

		fl(i,0,n)
		{
			int capcol=1;
			fl(j,0,n)
			{
				if(mat[j][i]=='0')
				{
					capcol=0;
					break;
				}
			}
			if(capcol==1)
			{
				if(myy>=0 && myy<capcol && capcol<n-1-capcol )
				{
					return level;
				}
				if(myy>capcol && myy<n && n-1-capcol<capcol)
					return level;
			}
		}

		fl(i,0,8)
		{
			if(issafe(curr_mat,myx+dx[i],myy+dy[i],opx,opy))
				f=1;
		}
		if(f==0)
			return level;

		std::vector<string> th=curr_mat;

		ret = 0;

		fl(i,0,8)
		{
			if(issafe(curr_mat,myx+dx[i],myy+dy[i],opx,opy))
			{	
				th[myx+dx[i]][myy+dy[i]]='1';
				ret=max(ret,dfs(level+1,th,myx+dx[i],myy+dy[i],opx,opy) );
				th[myx+dx[i]][myy+dy[i]]='0';
			}
		}

		return ret;
	}

	else
	{
		int i;
		int f=0;
		fl(i,0,8)
		{
			if(isonboard(opx+dx[i],opy+dy[i]) && opx+dx[i]==myx && opy+dy[i]==myy)
				return level;
		}

		fl(i,0,n)
		{
			int caprow=1;
			fl(j,0,n)
			{
				if(mat[i][j]=='0')
				{
					caprow=0;
					break;
				}
			}
			if(caprow==1)
			{
				if(opx>=0 && opx<caprow && caprow<n-1-caprow )
				{
					return level;
				}
				if(opx>caprow && opx<n && n-1-caprow<caprow)
					return level;
			}
		}

		fl(i,0,n)
		{
			int capcol=1;
			fl(j,0,n)
			{
				if(mat[j][i]=='0')
				{
					capcol=0;
					break;
				}
			}
			if(capcol==1)
			{
				if(opy>=0 && opy<capcol && capcol<n-1-capcol )
				{
					return level;
				}
				if(opy>capcol && opy<n && n-1-capcol<capcol)
					return level;
			}
		}

		fl(i,0,8)
		{
			if(issafe(curr_mat,opx+dx[i],opy+dy[i],myx,myy))
				f=1;
		}
		if(f==0)
			return level;

		ret=100000;

		std::vector<string> th=curr_mat;

		fl(i,0,8)
		{
			if(issafe(curr_mat,opx+dx[i],opy+dy[i],myx,myy))
			{	
				th[opx+dx[i]][opy+dy[i]]='2';
				ret=min(ret, dfs(level+1,th,myx,myy,opx+dx[i],opy+dy[i]) );
				th[opx+dx[i]][opy+dy[i]]='0';
			}
		}

		return ret;
	}
}

int rec(int level, std::vector<string> curr_mat, int myx, int myy, int opx, int opy)
{
	
	//std::vector<string> th = curr_mat;
	//cout<<level;nline;

	int ret;
	int j, i;
	/*cout<<"*********************";
	cout<<level<<" : ";
	nline;
	fl(i,0,n)
	{
		cout<<curr_mat[i];
		nline;
	}
	cout<<"*********************";*/
	if(level>10)
		return 0;
	if(level%2==0)
	{
		int i;
		int f=0;
		fl(i,0,8)
		{
			if(isonboard(myx+dx[i],myy+dy[i]) && myx+dx[i]==opx && myy+dy[i]==opy)
				return 1;
		}

		fl(i,0,n)
		{
			int caprow=1;
			fl(j,0,n)
			{
				if(mat[i][j]=='0' )
				{
					caprow=0;
					break;
				}
			}
			if(caprow==1)
			{
				if(myx>=0 && myx<caprow && caprow<n-1-caprow )
				{
					return 0;
				}
				if(myx>caprow && myx<n && n-1-caprow<caprow)
					return 0;
			}
		}

		fl(i,0,n)
		{
			int capcol=1;
			fl(j,0,n)
			{
				if(mat[j][i]=='0')
				{
					capcol=0;
					break;
				}
			}
			if(capcol==1)
			{
				if(myy>=0 && myy<capcol && capcol<n-1-capcol )
				{
					return 0;
				}
				if(myy>capcol && myy<n && n-1-capcol<capcol)
					return 0;
			}
		}

		fl(i,0,8)
		{
			if(issafe(curr_mat,myx+dx[i],myy+dy[i],opx,opy))
				f=1;
		}
		if(f==0)
			return 0;

		std::vector<string> th=curr_mat;

		fl(i,0,8)
		{
			if(issafe(curr_mat,myx+dx[i],myy+dy[i],opx,opy))
			{	
				th[myx+dx[i]][myy+dy[i]]='1';
				ret=rec(level+1,th,myx+dx[i],myy+dy[i],opx,opy);
				if(ret==1)
					return 1;
				th[myx+dx[i]][myy+dy[i]]='0';
			}
		}

		return 0;
	}

	else
	{
		int i;
		int f=0;
		fl(i,0,8)
		{
			if(isonboard(opx+dx[i],opy+dy[i]) && opx+dx[i]==myx && opy+dy[i]==myy)
				return 0;
		}

		fl(i,0,n)
		{
			int caprow=1;
			fl(j,0,n)
			{
				if(mat[i][j]=='0')
				{
					caprow=0;
					break;
				}
			}
			if(caprow==1)
			{
				if(opx>=0 && opx<caprow && caprow<n-1-caprow )
				{
					return 1;
				}
				if(opx>caprow && opx<n && n-1-caprow<caprow)
					return 1;
			}
		}

		fl(i,0,n)
		{
			int capcol=1;
			fl(j,0,n)
			{
				if(mat[j][i]=='0')
				{
					capcol=0;
					break;
				}
			}
			if(capcol==1)
			{
				if(opy>=0 && opy<capcol && capcol<n-1-capcol )
				{
					return 1;
				}
				if(opy>capcol && opy<n && n-1-capcol<capcol)
					return 1;
			}
		}

		fl(i,0,8)
		{
			if(issafe(curr_mat,opx+dx[i],opy+dy[i],myx,myy))
				f=1;
		}
		if(f==0)
			return 1;

		std::vector<string> th=curr_mat;

		fl(i,0,8)
		{
			if(issafe(curr_mat,opx+dx[i],opy+dy[i],myx,myy))
			{	
				th[opx+dx[i]][opy+dy[i]]='2';
				ret=rec(level+1,th,myx,myy,opx+dx[i],opy+dy[i]);
				if(ret==0)
					return 0;
				th[opx+dx[i]][opy+dy[i]]='0';
			}
		}

		return 1;
	}
}

int main(int argc, char *argv[])
{
	int i, j;

	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);

	string whattodo=argv[1];

	if(whattodo=="start")	//Initializing the board
	{
		int myx, myy, opx, opy;
		
		myx=atoi(argv[2]);
		myy=atoi(argv[3]);
		opx=atoi(argv[4]);
		opy=atoi(argv[5]);
		n=atoi(argv[6]);

		/*myx--;
		myy--;
		opx--;
		opy--;
		*/

		opy--;
		myy--;

		//baptize(myx);
		//baptize(opx);

		myx--;
		opx--;

		freopen("out.txt","w",stdout);

		cout<<n;
		nline;

		fl(i,0,n)
		{
			fl(j,0,n)
			{
				if(i==myx && j==myy)
				{
					cout<<"1";
				}
				else if(i==opx && j==opy)
				{
					cout<<"2";
				}
				else
				{
					cout<<"0";
				}
			}
			nline;
		}

		cout<<myx<<" "<<myy;nline;
		cout<<1;nline;

		return 0;

	}

	freopen("out.txt","r",stdin);



	//freopen("move.txt","w",stdout);

	scan(n);

	fl(i,0,n)
	{
		string str1;
		cin>>str1;
		mat.PB(str1);
	}

	if(mat[0][0]=='1')
	{
		fl(i,0,8)
		{
			dx[i]=dx1[i];
			dy[i]=dy1[i];
		}
	}
	if(mat[n-1][n-1]=='1')
	{
		fl(i,0,8)
		{
			dx[i]=dx2[i];
			dy[i]=dy2[i];
		}
	}

	int opx=atoi(argv[2]);
	int opy=atoi(argv[3]);

	
	opy--;

	//baptize(opx);
	opx--;

	int myx, myy;

	scan(myx); scan(myy);

	int flag;

	scan(flag);


	thisopx=opx;
	thisopy=opy;

	int savex=-1, savey=-1;

	mat[opx][opy]='2';

	fl(i,0,8)
	{
		if(isonboard(myx+dx[i],myy+dy[i]) && myx+dx[i]==opx && myy+dy[i]==opy)
		{
			//freopen("move.txt","w",stdout);
			myx=myx+dx[i];
			//baptize(myx);
			myx++;
			myy++;
			cout<<myx<<" "<<myy+dy[i];
			nline;
			return 0;
		}
	}

	std::vector<string> th=mat;

	if(min(abs(myx-opx) , abs(myy-opy) ) <=2 )
	{
		flag=0;
	}

	if(flag==1)
	{
		if(mat[0][0]=='1')
		{
			if(mat[0][1]!='1')
			{
				mat[0][1]='1';
				myx=0;
				myy=1;
			}
			else
			{
				if(mat[myx][myy-1]=='1')
				{
					myx=myx+1;
				}
				else
				{
					myy=myy+1;
				}
			}
		}
		else if(mat[n-1][n-1]=='1')
		{
			if(mat[n-1][n-2]!='1')
			{
				mat[n-1][n-2]='1';
				myx=n-1;
				myy=n-2;
			}
			else
			{
				if(mat[myx][myy+1]=='1')
				{
					myx--;
				}
				else
				{
					myy--;
				}
			}
		}

	}

	if(mat[0][0]=='1' && flag==1)
	{
		if(myx==2 && myy==2)
			flag=0;
		mat[myx][myy]='1';
		int savex=myx;
		int savey=myy;
		//baptize(myx);
		myx++;
		myy++;
		cout<<myx<<" "<<myy;
		freopen("out.txt","w",stdout);
		cout<<n;
		nline;
		fl(i,0,n)
		{
			fl(j,0,n)
			{
				cout<<mat[i][j];
			}
			nline;
		}
		cout<<savex<<" "<<savey;nline;
		cout<<flag;
		nline;
		return 0;
	}

	if(mat[n-1][n-1]=='1' && flag==1)
	{
		if(myx==n-3 && myy==n-3)
			flag=0;
		mat[myx][myy]='1';
		int savex=myx;
		int savey=myy;
		//baptize(myx);
		myx++;
		myy++;
		cout<<myx<<" "<<myy;
		freopen("out.txt","w",stdout);
		cout<<n;
		nline;
		fl(i,0,n)
		{
			fl(j,0,n)
			{
				cout<<mat[i][j];
			}
			nline;
		}
		cout<<savex<<" "<<savey;nline;
		cout<<flag;
		nline;
		return 0;
	}

	fl(i,0,8)
	{
		if(issafe(mat,myx+dx[i],myy+dy[i],opx,opy))
		{
			th[myx+dx[i]][myy+dy[i]]='1';
			if(rec(1,th,myx+dx[i],myy+dy[i],opx,opy)==1)
			{
				//freopen("move.txt","w",stdout);
				savex=myx+dx[i]; savey=myy+dy[i];
				myx=myx+dx[i];
				//baptize(myx);
				myx++;
				
				cout<<myx<<" "<<myy+dy[i]+1;
				break;
			}
			th[myx+dx[i]][myy+dy[i]]='0';
		}
	}

	int curr=-1;
	int sv;

	if(savex==-1 && savey==-1)
	{
		fl(i,0,8)
		{
			//cout<<dx[i]<<" "<<dy[i];nline;
			if(issafe(mat,myx+dx[i],myy+dy[i],opx,opy))
			{
				th[myx+dx[i]][myy+dy[i]]='1';
				if((sv=dfs(1,th,myx+dx[i],myy+dy[i],opx,opy))>curr)
				{
					//freopen("move.txt","w",stdout);
					savex=myx+dx[i]; 
					savey=myy+dy[i];
					curr=sv;
				}
				th[myx+dx[i]][myy+dy[i]]='0';
			}
		}
	}

	freopen("out.txt","w",stdout);
	mat[savex][savey]='1';
	cout<<n;
	nline;
	fl(i,0,n)
	{
		fl(j,0,n)
		{
			cout<<mat[i][j];
		}
		nline;
	}

	cout<<savex<<" "<<savey; nline;
	cout<<flag;nline;

	//rec(0,mat);

	return 0;
}

/*
	Powered by Buggy plugin
*/