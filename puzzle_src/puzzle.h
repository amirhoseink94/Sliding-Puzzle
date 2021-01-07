class puzzle
{
	public:
		int**a;
		int*t;
		char*s;
		int n;
		puzzle(int);
	private:
		void fillrandom(int **,const int);
		void print(int**,const int);
		int* search(int**,const int,const int);
		void movezero(const int,int**,int*,int*);
		void moveup(int**,const int,int*);
		void movedown(int**,const int,int*);
		void moveright(int**,const int,int*);
		void moveleft(int**,const int,int*);
		void gotoposition(int**,const int,const int,const int);
		void specialpositoin(int**,const int,const int,const int);
		void specialpositoin2(int**,const int,const int,const int);
		void veryspecialmovement(int**,const int,const int);
		bool inreng(const int,int);
		bool equality(int*,int*);
		bool everythingisok(int**,const int);
		void solve(int**,const int,const int);
		int ishope(int**,const int);
		void rollingzero(int**,const int ,const int );
		void upload(int**,const int);
};
