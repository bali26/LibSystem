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
void book_change();
void book_sort();
void book_get();
void admin_edit();
void admin_fprint(struct admin* head);
void fprint(struct book* head);

struct admin* admin_init();
struct admin* admin_add(struct admin* link);
struct admin* admin_del(struct admin* link);
struct admin* admin_change(struct admin* link);
void admin_see(struct admin* link);
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

				case 2:  //del
					book_del();
					break;
				case 3:
					//change
					book_change();
					break;
				case 4:  //sort

					break;
				case 5:  //get
					book_get();
					break;
				case 6:  //edit
					admin_edit();
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
	printf("\t\t\t\t1.Add Book Information                 2.Delete Book Information\n");
	printf("\t\t\t\t3.Change Book Information              4.Sort Book Information\n");
	printf("\t\t\t\t5.Get Book Information                 6.Edit Account\n");
	printf("\t\t\t\t                                       0.Exit\n");
	printf("\t\t\t\t**********************************************************\n");
	printf("\t\t\t\tEnter id: ");
	scanf("%d", &x);
	getchar();
	return x;
}

int usermenu() {

}

int checkPasswd() {

	FILE* fp;
	char account[15], password[15];
	struct admin* p1, * head = NULL, * tail = NULL;
	if ((fp = fopen("admin.txt", "a+")) == NULL) {
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
	printf("\t\t\t\tyour user name: ");
	gets(account); //不读取换行符 会转换成\0   （char *str） 指针数组

	int isAccount = 0;
	/*if (p1 == NULL) {
		printf("\t\t\t\tthis account isn't exist!\n");
		getchar();
		return 0;
	}*/

	while (p1 != NULL) {

		if (strcmp(p1->account, account) == 0) {
			isAccount = 1;
			break;
		}
		p1 = p1->next;
	}

	if (isAccount) {
		printf("\t\t\t\tyour user password: ");
		gets(password);

		if (strcmp(p1->password, password) == 0) {

			printf("\t\t\t\t%s - password verification - [passed]\n", account);
			printf("\t\t\t\t[Enter] into background");
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
	else {
		printf("\t\t\t\tthis account isn't exist!\n");
		getchar();
		return 0;
	}

}

struct book* load() { //form link
	FILE* fp;
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
		fscanf(fp, "%d %s %s %s %s %d %d %d %f\n", &p1->num, p1->bname, p1->wname, p1->press, p1->sort, &p1->time.year, &p1->time.month, &p1->time.day, &p1->price);
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
		while (p->next != NULL) {
			printf("p num: %d \n", p->num);
			p = p->next;

		}
		p->next = newbook;
		//p = newbook;
		//struct book* q;

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
	struct book* head = NULL;
	struct book* p = NULL;
	printf("Enter delete num:");
	scanf("%d", &num);

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
	while (q != NULL) { //第二个开始
		if (q->num == num) {
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

	printf("Book Information：\n");
	//printf("编号 图书名 作者名 出版社 类别 出版时间 价格\n");
	printf("num        book         writer         press         sort         year         month         day         price\n");

	while (head != NULL) {
		//printf("%d %s %s %s %s %d %d %d %f\n", head->num, head->bname, head->wname, head->press, head->sort, head->time.year, head->time.month, head->time.day, head->price);
		printf("%d %10s %12s %14s %15s %10d %12d %13d %19f \n", head->num, head->bname, head->wname, head->press, head->sort, head->time.year, head->time.month, head->time.day, head->price);
		head = head->next;
	}
	getchar();

}
void book_change() {
	int num;
	struct book* head = NULL, * p = NULL;
	head = load();

	if (head == NULL) {
		printf("File content error!\n");
		exit(0);
	}
	printf("Enter Book Num: ");
	scanf("%d", &num);
	p = head;
	while (p != NULL) {
		if (p->num == num) {

			printf("==========================================\n");
			printf("The content of the book to be revised\n");
			printf("==========================================\n");
			printf("num        book         writer         press         sort         year         month         day         price\n");
			printf("%d %10s %12s %14s %15s %10d %12d %13d %19f \n", p->num, p->bname, p->wname, p->press, p->sort, p->time.year, p->time.month, p->time.day, p->price);
			printf("==========================================\n");
			printf("What you want to modify:\n");
			printf("1.Num           2.BookName\n");
			printf("3.WriteName     4.pressName\n");
			printf("5.Sort          6.Year\n");
			printf("7.Month         8.Day\n");
			printf("9.Price	        0.Exit\n");
			printf("==========================================\n");
			int x = 0;
			scanf("%d", &x);
			switch (x) {
			case 0: //exit
				exit(0);
				break;
			case 1:
				printf("Enter new number:");
				scanf("%d", &p->num);
				printf("modify successfully!\n");
				break;
			case 2:
				printf("Enter new book name:");
				scanf("%s", p->bname);
				printf("modify successfully!\n");
				break;
			case 3:
				printf("Enter new writer name:");
				scanf("%s", p->wname);
				printf("modify successfully!\n");
				break;
			case 4:
				printf("Enter new press:");
				scanf("%s", p->press);
				printf("modify successfully!\n");
				break;
			case 5:
				printf("Enter new sort:");
				scanf("%s", p->sort);
				printf("modify successfully!\n");
				break;
			case 6:
				printf("Enter new year:");
				scanf("%d", &p->time.year);
				printf("modify successfully!\n");
				break;
			case 7:
				printf("Enter new month:");
				scanf("%d", &p->time.month);
				printf("modify successfully!\n");
				break;
			case 8:
				printf("Enter new day:");
				scanf("%d", &p->time.day);
				printf("modify successfully!\n");
				break;
			case 9:
				printf("Enter new price:");
				scanf("%f", &p->price);
				printf("modify successfully!\n");
				break;


			}
		}
		p = p->next;
	}
	fprint(head);

}

void admin_edit() {

	FILE* fp;
	int ret;
	struct admin* ad = NULL;
	if ((fp = fopen("admin.txt", "a+")) == NULL) {
		printf("File open failed");
		exit(0);
	}
	char* account = (char*)malloc(sizeof(char));
	char* password = (char*)malloc(sizeof(char));
	struct admin* head = NULL, * p = NULL, * tail = NULL, * n = NULL;

	p = (struct admin*)malloc(sizeof(struct admin));


	printf("=====================\n");
	printf("Account Edit\n");
	printf("=====================\n");
	printf("1.Register 2.Remove\n");
	printf("3.Edit     0.exit\n");
	printf("=====================\n");

	int num;
	printf("Please enter your number:");
	scanf("%d", &num);


	/*	while (fscanf(fp, "%s %s", p->account, p->password) != EOF) { //fscanf 格式化读取每行 且不等于EOF

			printf("out0: %s %s\n", p->account, p->password);
			p = p->next;
		}*/


	struct admin* link = admin_init();

	while (1) {
		ret = (fscanf(fp, "%s %s", p->account, p->password));
		if (ret == EOF) break;
		if (ret == 2) {
			admin_add(link, p->account, p->password);
		}
		else {
			printf("%d\n", ret);
			perror("fscanf:");
			break;
		}
	}
	admin_see(link);
	fclose(fp);
	switch (num) {
	case 0: //exit"
		exit(0);
		break;
	case 1: //register
		printf("ENTER");
		printf("Please enter your account:");
		scanf("%s", account);
		printf("Please enter your password:");
		scanf("%s", password);
		admin_add(link, account, password);
		system("pause");
		admin_see(link);
		admin_fprint(link);

		break;
	case 2: //remove
		printf("Please enter your account:");
		scanf("%s", account);
		admin_del(link, account);
		admin_fprint(link);
		break;
	case 3: //edit
		printf("Please enter your account:");
		scanf("%s", account);
		admin_change(link, account);
		system("pause");
		admin_see(link);
		admin_fprint(link);

		break;

	}

}
void fprint(struct book* head) {

	FILE* fp;
	struct book* p1 = NULL;
	if ((fp = fopen("book.txt", "w+")) == NULL) {

		printf("book.txt File open error! \n");
		exit(0);//OS
	}
	printf("1");
	system("pause");
	p1 = head;
	while (p1 != NULL) {
		//for (p1 = head; p1; p1 = p1->next) { // !=NULL
		printf("2");
		fprintf(fp, "%d %s %s %s %s %d %d %d %f\n", p1->num, p1->bname, p1->wname, p1->press,
			p1->sort, p1->time.year, p1->time.month, p1->time.day, p1->price); //输出到fp 不用取地址


		system("pause");

		p1 = p1->next;
	}
	printf("3");
	system("pause");
	fclose(fp);
}

void admin_fprint(struct admin* head) {
	FILE* fp;
	struct admin* tail = NULL, * p = NULL;
	if ((fp = fopen("admin.txt", "w+")) == NULL) {
		printf("File open error!\n");
		exit(0);
	}
	//p = head;
	//p = (struct admin*)malloc(sizeof(struct admin));
	while (head->next != NULL) {
		head = head->next;
	//	printf("out3: %s\n", head->account);
	//	printf("out3: %s\n", head->password);
		fprintf(fp, "%s %s\n", head->account, head->password);

	}
	getchar();
	system("pause");
	fclose(fp);
	//	head = head->next;
	//}

	/*	for (p = head; p; p = p->next)
		{
			fprintf(fp, "%s %s\n", p->account, p->password);
		}*/
}


struct admin* admin_init() {
	printf("admin_init\n");
	struct admin* head = NULL;

	head = (struct admin*)malloc(sizeof(struct admin));

	head->next = NULL;

	return head;

}

struct admin* admin_add(struct admin* link, char* account, char* password) {
	printf("admin_add\n");
	struct admin* head, * node;
	head = link;
	node = (struct admin*) malloc(sizeof(struct admin));
	while (link->next != NULL) {
		link = link->next;
	}
	strcpy(node->account, account);
	strcpy(node->password, password);
	node->next = NULL;
	link->next = node;

	return head;
}
struct admin* admin_del(struct admin* link, char* account) {
	//printf("admin_del-account: %s \n",account);
	struct admin* head = NULL, *p,* p2 = NULL;
	p = link;
	if (p == NULL) {
		printf("admin.txt is null");
		exit(0);
	}
	else {
		//printf("Multiple elements");
		 //Multiple elements
		while (p->next != NULL) {
			p2 = p->next;
			if ((strcmp(p2->account, account)) == 0) {
			p->next = p2->next;
			free(p2);
			return 0;
			}
			p = p->next;
		}
	}
	return link;
}

struct admin* admin_change(struct admin* link,char * account) {
	struct admin * p=NULL,*p2=NULL;

	if (link == NULL) {
		printf("admin.txt is null");
		exit(0);
	}
	p = link;
	p2 = p->next;
	//single
	/*if (p2->next == NULL) {
		if (strcmp(p2->account, account) == 0) {
			printf("enter you want to change password: \n");
			char* password = (char*)malloc(sizeof(char));
			scanf("%d", password);
			strcpy(p2->password, password);
			printf("Change password Successfully!");

		}
	}*/
	//multiple elements
	while (p2 != NULL) {
		if (strcmp(p2->account, account) == 0) {
			char* password = (char*)malloc(sizeof(char));
			printf("enter you want to change password: \n");
			scanf("%s", password);
			strcpy(p2->password, password);
			printf("Change password Successfully!");
			break;
		}
		p2 = p2->next;
	}
	return link;
	
}
void admin_see(struct admin* link) {
	//printf("admin_see\n");
	while (link->next != NULL) {
		link = link->next;
		printf("out_admin_see_account: %s \n", link->account);
		printf("out_admin_see_password: %s \n", link->password);

	}
}
