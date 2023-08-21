#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Tminterm
{
public:
	char tvalue[100];
	Tminterm* next;
	int coverd = 0;
	int check = 0;
};
class Tlist
{
public:
	Tminterm* tlisthead = NULL;
	Tminterm* tlisttail = NULL;
	Tminterm* tlistcur = NULL;
	Tminterm* tlistnewtmin = NULL;
	void addtlist(char arr[])
	{
		tlistnewtmin = new Tminterm;
		strcpy_s(tlistnewtmin->tvalue, arr);
		if (tlisthead == NULL)
		{
			tlisthead = tlistnewtmin;
			tlisttail = tlistnewtmin;
		}
		else
		{
			tlisttail->next = tlistnewtmin;
			tlisttail = tlistnewtmin;
		}
	}
	bool countchecked()
	{
		tlistcur = tlisthead;
		while (tlistcur != NULL)
		{
			if (tlistcur->check == 0)
			{
				return true;
			}
				
			tlistcur = tlistcur->next;
		}
		return false;
	}
};
class Minterm
{
public:
	int dorm = -1;//dontcare 0 minterm 1
	int check = 0;//선택됬었는지 아닌지
	char value[100] = "";//값
	int countcover = 0;
	Tminterm* head = NULL;
	Tminterm* tail = NULL;
	Tminterm* cur = NULL;
	Tminterm* newtmin = NULL;
	Minterm* next = NULL;
	void addtmin(char arr[])
	{
		newtmin = new Tminterm;
		strcpy_s(newtmin->tvalue, arr);
		if (head == NULL)
		{
			head = newtmin;
			tail = newtmin;
		}
		else
		{
			tail->next = newtmin;
			tail = newtmin;
		}
	}
	int isthere(char arr[100])
	{
		cur = head;
		while (cur != NULL)
		{
			if (strcmp(cur->tvalue, arr) == 0)
			{
				return 0;
			}
			cur = cur->next;
		}
		return 1;
	}
	void checker(char arr[100])
	{
		Tminterm* cur1;
		cur1 = head;
		while (cur1 != NULL)
		{
			if (strcmp(cur1->tvalue, arr) == 0)
			{
				cur1->check = 1;
			}
			
			cur1 = cur1->next;
		}
	}
	int covercounter()
	{
		int covercount = 0;
		cur = head;
		while (cur != NULL)
		{
			if (cur->check == 0)
			{
				covercount++;
			}
			cur = cur->next;
		}
		return covercount;
	}
};

int main()
{
	Minterm* head = NULL;
	Minterm* tail = NULL;
	Minterm* cur = NULL;
	Minterm* newminterm = NULL;
	Minterm* cutline = NULL;
	Minterm* column1line = NULL;
	Minterm* plshead = NULL;
	Minterm* plscur = NULL;
	Minterm* plstail = NULL;
	Minterm* plsprecur = NULL;
	Minterm* essentialhead = NULL;
	Minterm* essentialcur = NULL;
	Minterm* essentialtail = NULL;

	int bitnum;
	ifstream input;//읽을 파일 선언
	int i = 0;
	input.open("input_minterm.txt");//파일 열기
	if (input.is_open())//열였을 경우
	{
		newminterm = new Minterm;
		head = newminterm;//첫 노드는 bitnum
		tail = newminterm;
		newminterm->next = NULL;
		input.getline(newminterm->value, 100);//한줄씩 받기

		while (!input.eof())//파일을 끝까지 읽기
		{
			newminterm = new Minterm;
			input.getline(newminterm->value, 100);//한줄씩 받기
			tail->next = newminterm;
			tail = newminterm;
			cutline = tail;
			column1line = tail;
		}
	}

	else//안열렸을 경우
	{
		cout << "file is not open";
		return 0;
	}
	bitnum = atoi(head->value);

	cur = head;
	while (cur != NULL)//임시 결과값 출력
	{
		cout << cur->value << endl;
		cur = cur->next;
	}
	cur = head;
	while (cur != NULL)// d 랑 m 구별해서 dorm값 수정 해주기
	{
		if (cur->value[0] == 'd')
		{
			cur->dorm = 0;
		}
		else if (cur->value[0] == 'm')
		{
			cur->dorm = 1;
		}
		// d 랑 m을 뺸 순수 value값으로 수정 해주기
		char temp[100];
		int t = 0;
		for (int i = 2; i < bitnum + 2; i++)
		{
			temp[t] = cur->value[i];
			cur->value[t] = temp[t];
			t++;
		}
		cur->value[bitnum] = '\0';
		cur = cur->next;
	}

	cur = head;
	while (cur != NULL)//임시 결과값 출력
	{
		cout << cur->value << endl;
		cur = cur->next;
	}
	cout << "------------------------------------pls" << endl;

	Minterm* standard = head->next;
	while (standard != NULL)
	{
		cur = standard->next;
		while (cur != cutline->next)//standard랑 비교하기
		{
			int countcheck = 0;
			int differentpoint = 0;

			for (int i = 0; i < bitnum; i++)//각자리비교해보기
			{
				if (cur->value[i] == standard->value[i])
				{
					countcheck++;
				}
				else
				{
					differentpoint = i;
				}
			}
			if (countcheck == bitnum - 1)//한 bit만 다른 경우
			{
				standard->check = 1;
				cur->check = 1;
				newminterm = new Minterm;
				strcpy_s(newminterm->value, standard->value);
				newminterm->value[differentpoint] = '-';
				tail->next = newminterm;//cutline의 next부터가 연산과정의 민텀들인것임.
				tail = newminterm;
			}
			cur = cur->next;
		}
		standard = standard->next;
		if (standard == cutline)
		{
			standard = standard->next;
			cutline = tail;
		}
	}
	Minterm* pcur = head->next;
	while (pcur != NULL)
	{
		if (pcur->check == 0)
		{
			newminterm = new Minterm;
			strcpy_s(newminterm->value, pcur->value);
			if (plshead == NULL)
			{
				plshead = newminterm;
				plstail = newminterm;
			}
			else
			{
				plstail->next = newminterm;
				plstail = newminterm;
			}
		}
		pcur = pcur->next;
	}

	standard = plshead;//중복 pls삭제
	Minterm* mintermkiller;
	while (standard != NULL)
	{
		plscur = standard->next;
		plsprecur = standard;
		while (plscur != NULL)
		{
			if (strcmp(standard->value, plscur->value) == 0)
			{
				if (plscur == standard->next)
				{
					mintermkiller = plscur;
					standard->next = plscur->next;
					delete(mintermkiller);
					plscur = standard->next;
				}
				else if (plscur == plstail)
				{
					plsprecur->next = NULL;
					mintermkiller = plscur;
					delete(mintermkiller);
					plstail = plsprecur;
					break;
				}
				else
				{
					plsprecur->next = plscur->next;
					mintermkiller = plscur;
					plscur = plscur->next;
					delete(mintermkiller);

				}
			}
			else
			{
				plsprecur = plscur;
				plscur = plscur->next;
			}

		}
		standard = standard->next;
	}

	plscur = plshead;//pls임시출력
	while (plscur != NULL)
	{
		cout << plscur->value << endl;
		plscur = plscur->next;
	}
	cout << "--------------------------essential pls" << endl;
	Tlist tlist;
	cur = head;//tlist에 true민텀들 넣기
	while (1)
	{
		if (cur->dorm == 1)
		{
			tlist.addtlist(cur->value);
		}
		if (cur == column1line)
		{
			break;
		}
		cur = cur->next;
	}

	tlist.tlistcur = tlist.tlisthead;
	while (tlist.tlistcur != NULL)//pls가 커버하는 수 체크
	{
		plscur = plshead;
		while (plscur != NULL)
		{
			for (int i = 0; i < bitnum; i++)
			{
				if ((plscur->value[i] == '-') || (plscur->value[i] == tlist.tlistcur->tvalue[i]))
				{
					if (i == bitnum - 1)
					{
						tlist.tlistcur->coverd++;
						plscur->addtmin(tlist.tlistcur->tvalue);//pls에 cover하는 minterm넣어주기
						plscur->countcover++;
					}
				}
				else
				{
					break;
				}
			}

			plscur = plscur->next;
		}
		tlist.tlistcur = tlist.tlistcur->next;
	}
	char deletemin[100];
	Tminterm* listcur2;
	Tminterm* prevlistcur2;
	Tminterm* plscur2;
	Tminterm* prevplscur2;
	Minterm* plscur3;
	tlist.tlistcur = tlist.tlisthead;
	while (tlist.tlistcur != NULL)//하나만 커버되는 경우가 있다면 그 pls essentialpls
	{
		if (tlist.tlistcur->coverd == 1)//하나만 커버되는 거 찾고
		{
			plscur = plshead;
			while (plscur != NULL)
			{
				if (tlist.tlisthead == NULL)//만약 essential pl로 trueminterm들이 전부 커버되면 끝
				{
					goto finish;
				}
				int find=plscur->isthere(tlist.tlistcur->tvalue);
				if (find == 0)
				{
					newminterm = new Minterm;
					strcpy_s(newminterm->value,plscur->value);
					if (essentialhead == NULL)
					{
						essentialhead = newminterm;
						essentialtail = newminterm;
					}
					else
					{
						essentialtail->next = newminterm;
						essentialtail = newminterm;
					}
					plscur->cur = plscur->head;
					while (plscur->cur != NULL)//essential pls가 cover하는 minterm들 체크
					{
						listcur2 = tlist.tlisthead;
						while (listcur2 != NULL)
						{
							if (strcmp(listcur2->tvalue, plscur->cur->tvalue) == 0)
							{
								listcur2->check = 1;
							}
							listcur2 = listcur2->next;
						}
						

						//pls에서 커버된 minterm들 체크해주기
						strcpy_s(deletemin, plscur->cur->tvalue);
						plscur3=plshead;
						while (plscur3 != NULL)
						{
							plscur3->checker(deletemin);
							plscur3 = plscur3->next;
						}
						plscur->cur = plscur->cur->next;
					}
				}
				plscur = plscur->next;
			}
		}

		tlist.tlistcur = tlist.tlistcur->next;
	}

	Minterm* bigpls;
	while (tlist.countchecked())//minterm 들이 전부 체크될 때까지
	{
		bigpls = plshead;
		plscur = plshead;
		while (plscur != NULL)//남은 minterm들중 가장 많이 커버하는 pls 선택
		{
			if (plscur->covercounter() > bigpls->covercounter())
			{
				bigpls = plscur;
			}
			plscur = plscur->next;
		}
		newminterm = new Minterm;//가장 커버 많이 하는 pls 에센셜로 보내기
		strcpy_s(newminterm->value, bigpls->value);
		if (essentialhead == NULL)
		{
			essentialhead = newminterm;
			essentialtail = newminterm;
		}
		else
		{
			essentialtail->next = newminterm;
			essentialtail = newminterm;
		}
		bigpls->cur = bigpls->head;
		while (bigpls->cur != NULL)
		{
			tlist.tlistcur = tlist.tlisthead;//trueminterm들 커버된 minterm체크해주기
			while (tlist.tlistcur != NULL)
			{
				if (strcmp(bigpls->cur->tvalue, tlist.tlistcur->tvalue)==0)
				{
					tlist.tlistcur->check = 1;
					bigpls->countcover--;
				}
				tlist.tlistcur = tlist.tlistcur->next;
			}
			//pls에서 커버된 minterm들 체크해주기
			strcpy_s(deletemin, bigpls->cur->tvalue);
			plscur3 = plshead;
			while (plscur3 != NULL)
			{
				plscur3->checker(deletemin);
				plscur3 = plscur3->next;
			}
			bigpls->cur = bigpls->cur->next;
		}
	}
	

finish:
	Minterm* essentialprecur;
	//essential 중복 삭제
	standard = essentialhead;//중복 pls삭제
	Minterm* essentialmintermkiller;
	while (standard != NULL)
	{
		essentialcur = standard->next;
		essentialprecur = standard;
		while (essentialcur != NULL)
		{
			if (strcmp(standard->value, essentialcur->value) == 0)
			{
				if (essentialcur == standard->next)
				{
					essentialmintermkiller = essentialcur;
					standard->next = essentialcur->next;
					delete(essentialmintermkiller);
					essentialcur = standard->next;
				}
				else if (essentialcur == essentialtail)
				{
					essentialprecur->next = NULL;
					essentialmintermkiller = essentialcur;
					delete(essentialmintermkiller);
					essentialtail = essentialprecur;
					break;
				}
				else
				{
					essentialprecur->next = essentialcur->next;
					essentialmintermkiller = essentialcur;
					essentialcur = essentialcur->next;
					delete(essentialmintermkiller);

				}
			}
			else
			{
				essentialprecur = essentialcur;
				essentialcur = essentialcur->next;
			}

		}
		standard = standard->next;
	}

	essentialcur = essentialhead;//essentialpls임시출력
	while (essentialcur != NULL)
	{
		cout << essentialcur->value << endl;
		essentialcur = essentialcur->next;
	}

	
	int countor = 0;//count plus gate
	int countand = 0;//count and gate
	int countandinput = 0;
	int countnot = 0;//count not gate
	int checknot[100] = { 0, };
	int cost = 0;
	essentialcur = essentialhead;
	while (essentialcur != NULL)
	{
		countandinput = 0;
		for (int i = 0; i < bitnum; i++)
		{
			if (essentialcur->value[i] == '0')
			{
				checknot[i] = 1;
			}
			if ((essentialcur->value[i] == '0') || (essentialcur->value[i] == '1'))
			{
				countandinput++;
			}
		}
		if (countandinput > 1)
		{
			countand += countandinput * 2 + 2;//n-input and gate = 2n+2 
		}

		countor++;
		essentialcur = essentialcur->next;
	}
	if (countor > 1)//하나인 경우 or gate는 없다.
	{
		countor = countor * 2 + 2;//n-input or gate = 2n+2
	}
	int j = 0;

	for (int i = 0; i < bitnum; i++)
	{
		if (checknot[i] == 1)
		{
			countnot++;
		}
	}
	countnot = 2 * countnot;//not gate = 2n
	cost = countnot + countand + countor;
	cout << "Cost (# of transistors): " << cost << endl;
	//result.txt 저장하기
	ofstream fout("result.txt");
	essentialcur = essentialhead;//essentialpls임시출력
	while (essentialcur != NULL)
	{
		fout << essentialcur->value << endl;
		essentialcur = essentialcur->next;
	}
	fout << endl;
	fout << "Cost (# of transistors): " << cost << endl;

	//동적할당 해제
	Tminterm* nextdeltminterm;
	Tminterm* deltminterm;
	deltminterm = tlist.tlisthead;
	while (deltminterm != NULL)
	{
		nextdeltminterm = deltminterm->next;
		delete(deltminterm);
		deltminterm = nextdeltminterm;
	}

	Minterm* nextdelminterm=NULL;
	Minterm* delminterm=head;
	while (delminterm != NULL)
	{
		nextdelminterm = delminterm->next;
		delete(delminterm);
		delminterm = nextdelminterm;
	}

	plscur = plshead;
	while (plscur != NULL)
	{
		nextdeltminterm=NULL;
		deltminterm = plscur->head;
		while (delminterm != NULL)
		{
			nextdeltminterm = deltminterm->next;
			delete(deltminterm);
			deltminterm = nextdeltminterm;
		}
		plscur = plscur->next;
	}
	
	nextdelminterm = NULL;
	delminterm = plshead;
	while (delminterm != NULL)
	{
		nextdelminterm = delminterm->next;
		delete(delminterm);
		delminterm = nextdelminterm;
	}

	nextdelminterm = NULL;
	delminterm = essentialhead;
	while (delminterm != NULL)
	{
		nextdelminterm = delminterm->next;
		delete(delminterm);
		delminterm = nextdelminterm;
	}
	
}
