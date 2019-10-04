//rewind函数作用等同于 (void)fseek(stream, 0L, SEEK_SET);
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

int mainmenu();
int adminmenu();
int usermenu();
int checkPasswd();
void book_add(); //link
void book_del(); //link
void book_get();
void book_change();

void fprint(struct book *head);
struct book* load();
struct book {
	int num;
	char bname[50];
	char wname[50];
	char press[50];
	char sort[50];
	struct date {
		int year;
		int month;
		int day;

	}time;
	float price;
	struct book* next;
};

struct student {
	int num[15]; //student id
	char name[20]; //student name
	int numbook; //book id
	struct student* next;

};

struct admin {
	char account[15];
	char password[15];
	struct admin* next;

};

int main() {
	int n, y = 1;
	int passwd;

	while (1) {
		system("cls");
		menu: 
		n = mainmenu();
		switch (n) { //1.Admin 2.
		case 3: //exit
			y = 0;
			exit(0);
			break;
		case 1: //admin
			passwd = checkPasswd();
			while (passwd) {

				system("cls");

				switch (adminmenu()) {

				case 0:  //exit
					goto menu;

				case 1:  //add
					book_add();
					break;
				case 2:  //record
					break;
				case 3:  //get
					book_get();
					break;
				case 4:  
		
				
					//sort
					break;
				case 5:  //change
					book_change();
					break;
				case 6:  //delete
					book_del();
					break;
				case 7:  //edit
					break;
					;
				}


			}
		case 2: //user

			;
		}
	}


}


int mainmenu() {
	system("cls");
	int x;
	printf("\n\n\n\n\n\n\n");
	printf("\t\t\t\tWELCOME \n");
	printf("\t\t\t\t1.Admin \n");
	printf("\t\t\t\t2.User \n");
	printf("\t\t\t\t3.Exit \n");
	printf("\t\t\t\tEnter your choice: ");

	scanf("%d", &x);
	getchar();
	return x;

}

int adminmenu() {
	system("cls");
	int x;
	printf("\t\t\t\t----------------------------------------------------------\n");
	printf("\t\t\t\tBook Information System\n");
	printf("\t\t\t\t----------------------------------------------------------\n");
	printf("\t\t\t\t**********************************************************\n");
	printf("\t\t\t\tWELCOME, BackGround System.\n");
	printf("\t\t\t\t1.Add Book Information       2.Record Book Information\n");
	printf("\t\t\t\t3.Get Book Information       4.Sort Book Information\n");
	printf("\t\t\t\t5.Change Book Information    6.delete Book Information\n");
	printf("\t\t\t\t7.Edit Account               0.Exit\n");
	printf("\t\t\t\t**********************************************************\n");
	printf("\t\t\t\tEnter id: ");
	scanf("%d",&x);
	getchar();
	return x;
}

int usermenu() {

}

int checkPasswd() {

	FILE* fp;
	char account[15], password[15];
	struct admin* p1, * head = NULL, * tail = NULL;
	if ((fp = fopen("admin.txt", "r")) == NULL) {
		printf("File open error! \n");
		exit(0);
	}
	if (fgetc(fp) == EOF) {
		return 1; //no passwd
	}
	rewind(fp);
	while (!feof(fp)) { //文件结束非0 未结束0  !=0的时候 feof到文件尾  feof(fp)==0
		p1 = (struct admin*) malloc(sizeof(struct admin)); //change
		fscanf(fp, "%s %s\n", p1->account, p1->password);  //%s -> 字符数组 因此不用&
		//printf("%s", p1->account);
		//printf("%s", p1->password);
		if (head == NULL) {
			head = p1;
		}
		else {
			tail->next = p1;
		}
		tail = p1;
	
}
	tail->next = NULL;
	fclose(fp);
	p1 = head;
	fclose(fp);

	p1 = head;
	printf("\t\t\t\tyour user name: ");
	gets(account); //不读取换行符 会转换成\0   （char *str） 指针数组
//	printf(account);

	int isAccount = 0;

	while (p1!=NULL) {

		if (strcmp(p1->account, account)==0) {
			isAccount = 1;
			break;
		}
		p1 = NULL; //p1 = p1->next;
	}

	if (p1 == NULL) {
		printf("\t\t\t\tthis account isn't exist!\n");
		getchar();
		return 0;
	}

	if (isAccount) {
		printf("\t\t\t\tyour user password: ");
		gets(password);

		if (strcmp(p1->password, password) == 0) {

			printf("\t\t\t\t%s - password verification - [passed]\n", account);
			printf("\t\t\t\t[Enter] into background" );
			getchar();
			system("cls");
			return 1;
		}
		else {
			printf("\t\t\t\t%s - password verification - [failed]", account);
			getchar();
			system("cls");
			return 0;
		}
	}
	
}

struct book *load() { //form link
	FILE *fp;
	//struct book *head = NULL,*tail = NULL,*p1 = NULL;
	struct book* head, * tail, * p1;
	head = tail = NULL;
	if ((fp = fopen("book.txt", "a+")) == NULL) {
		printf("File open error! \n");
		exit(0);
	}
	if (fgetc(fp) == EOF) {
		printf("File context isn't exist");
		//exit(0);
		fclose(fp);
		return NULL;
	}
	rewind(fp); //warning
	while (!feof(fp)) {  //feof(fp)!=NULL 并不等于 !feof(fp)   文件结束 非0   未结束 0   NULL用于指针和对象，0用于数值  int feof( FILE *stream );
		p1 = (struct book*) malloc(sizeof(struct book));
		fscanf(fp, "%d %s %s %s %s %d %d %d %f\n", &p1->num,p1->bname,p1->wname,p1->press,p1->sort,&p1->time.year,&p1->time.month,&p1->time.day,&p1->price);
		if (head == NULL) {
			head = p1; //头链表成员初始化
			//head = (tail = p1); 
		}
		else {
			tail->next = p1; //存在头部 n>1时候 [尾][头]下一个指向新分配的p1  旧p1->新p1
		}
		tail = p1; //只有一个成员 头尾相同 第一次
	}
	tail->next = NULL; //结束循环 最后一个链表成员指向NEXT为NULL
	fclose(fp);
	return head;

}
struct book* create_book() {
	struct book* p;
	p = (struct book*)malloc(sizeof(struct book)); //define new p
	printf("Num: \n");
	scanf("%d", &p->num);
	getchar();
	printf("BookName: \n");
	scanf("%s", p->bname);
	getchar();
	printf("WriterName: \n");
	scanf("%s", p->wname);
	getchar();
	printf("Press: \n");
	scanf("%s", p->press);
	getchar();
	printf("Sort: \n");
	scanf("%s", p->sort);
	getchar();
	printf("PressTime - Year: \n");
	scanf("%d", &p->time.year);
	getchar();
	printf("PressTime - Month: \n");
	scanf("%d", &p->time.month);
	getchar();
	printf("PressTime - Day: \n");
	scanf("%d", &p->time.day);
	getchar();
	printf("Price: \n");
	scanf("%f", &p->price);
	getchar();

	p->next = NULL;
	return p;
}
void book_add() {

	struct book* head, * p, * newbook;
	p = newbook = NULL;
	newbook = create_book();
	FILE* fp;
	if (newbook == NULL) {
		printf("Input Book Information - [failed]");
		exit(0);
	}

	char a;
	p = load(); // *struct book *head;
	head = p;
	if (p == NULL) {
		/*printf("File context is null");
		getchar();*/
		/*if((fp = fopen("book.txt", "w"))==NULL){
			printf("File open error!\n");
			exit(0);
		}*/
		fprint(newbook);
		head = newbook;
	}
	else {
		printf("exist");

		//while (p != NULL) {
		while (p->next != NULL){
			printf("p num: %d \n", p->num);
		p = p->next;

	}
	p->next = newbook;
	//p = newbook;
	struct book* q;

	//q = newbook;
	//p = q;
	//p->next = NULL;

	fprint(head);

	//insert link struct

}
	book_get();
}
void book_del() {
	int num = 0;
	struct book *head = NULL;
	struct book *p = NULL;
	printf("Enter delete num:");
	scanf("%d",&num);

	head = load();
	printf("输出头书名: %s", head->bname);

	p = head;

	if (head == NULL) {
		printf("File no context");
		exit(0);
	}
	//for (p;p!=NULL;p=p->next) {
	struct book* q = NULL;
	
	if (head != NULL && head->num == num)
	{
		q = head;
		head = q->next; //head = head->next;
		free(q);
		fprint(head);
		return;
	}
	//p = head = load();
	q = p->next; //p为A q为B p->next 下一个   q->next为C 下下个 A->B->C 目前要删除B
	while(q!=NULL){ //第二个开始
		if (q->num==num) {
		printf("符合");
		p->next = q->next; //第二个开始指向
		free(q);//释放B
		q = NULL;//避免野指针
		fprint(head);
		break;
		}
		else {
			p = p->next;
			q = q->next;
		}

	}



}

void book_get() {

	struct book* head = NULL;
	head = load();
	if (head == NULL) {
		printf("No Information \n");
		getchar();
		return;
	}

	printf(" 图书信息：");
	printf("编号 图书名 作者名 出版社 类别 出版时间 价格\n");
	
	while (head != NULL) {
		printf("%d %s %s %s %s %d %d %d %f\n", head->num, head->bname, head->wname, head->press, head->sort, head->time.year, head->time.month, head->time.day, head->price);
		head = head->next;
	}
	getchar();

}
void book_change() {
	int num;
	struct book* head=NULL,*p=NULL;
	head = load();

	if (head == NULL) {
		printf("File content error!\n");
		exit(0);
	}
	printf("Enter Book Num: \n");
	scanf("%d",&num);
	p = head;
	while (p != NULL) {
		if (p->num == num) {
			
			printf("==========================================\n");
			printf("The content of the book to be revised\n");
			printf("==========================================\n");
			printf("序号 书名 作者名 出版社 类型 年 月 日 金额\n");
			printf("%d %s %s %s %s %d %d %d %f \n", p->num, p->bname, p->wname, p->press, p->sort, p->time.year, p->time.month, p->time.day, p->price);
			printf("==========================================\n");
			printf("What you want to modify:\n");
			printf("1.Num           2.BookName\n");
			printf("3.WriteName     4.pressName\n");
			printf("5.Sort          6.Year\n");
			printf("7.Month         8.Day\n");
			printf("9.Price	        0.Exit\n");
			printf("==========================================\n");
			int x=0;
			scanf("%d",&x);
			switch (x) {
			case 0: //exit
				exit(0);
				break;
			case 1:
				scanf("%d", &p->num);
				break; 
			case 2:
				printf("\t\t\t请输入新图书名:");
				gets(p->bname);
				printf("\t\t\t修改成功!\n");
				break;
			case 3:
				gets(p->wname);
				break;
			case 4:
				gets(p->press);
				break;
			case 5:
				gets(p->sort);
				break;
			case 6:
				scanf("%d", &p->time.year);
				break;
			case 7:
				scanf("%d", &p->time.month);
				break;
			case 8:
				scanf("%d", &p->time.day);
				break;
			case 9:
				scanf("%f", &p->price);
				break;


			}
		}
		p = p->next;
	}
	fprint(head);


}
void fprint(struct book* head) {

	FILE *fp;
	struct book* p1 = NULL;
	if ((fp = fopen("book.txt", "w+")) == NULL) {
	
		printf("book.txt File open error! \n");
		exit(0);//OS
	}
	printf("1");
	system("pause");
	p1 = head;
	while(p1!=NULL){
	//for (p1 = head; p1; p1 = p1->next) { // !=NULL
		printf("2");
		fprintf(fp,"%d %s %s %s %s %d %d %d %f\n", p1->num, p1->bname, p1->wname, p1->press,
			p1->sort, p1->time.year, p1->time.month, p1->time.day, p1->price); //输出到fp 不用取地址
		
		system("pause");
	
		p1 = p1->next;
	}
	printf("3");
	system("pause");
	fclose(fp);
}