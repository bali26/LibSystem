//rewind�������õ�ͬ�� (void)fseek(stream, 0L, SEEK_SET);
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
			break;
		case 1: //admin
			passwd = checkPasswd();
			while (passwd) {

				system("cls");

				switch (adminmenu()) {

				case 0:  //exit
					goto menu;

				case 1:  //add

				case 2:  //record
				case 3:  //get
					book_get(load());
				case 4:  //sort
				case 5:  //change
				case 6:  //delete
				case 7:  //edit

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
	while (!feof(fp)) {
		p1 = (struct admin*) malloc(sizeof(struct admin)); //change
		fscanf(fp, "%s %s\n", p1->account, p1->password);
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
	gets(account); //����ȡ���з� ��ת����\0   ��char *str�� ָ������
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
	if ((fp = fopen("book.txt", "r")) == NULL) {
		printf("File open error! \n");
		exit(0);
	}
	if (fgetc(fp) == EOF) {
		printf("File context isn't exist");
		exit(0);
	}
	rewind(fp); //warning
	while (!feof(fp)) {  //feof(fp)!=NULL �������� !feof(fp)   �ļ����� ��0   δ���� 0   NULL����ָ��Ͷ���0������ֵ  int feof( FILE *stream );
		p1 = (struct book*) malloc(sizeof(struct book));
		fscanf(fp, "%d %s %s %s %s %d %d %d %f", &p1->num,&p1->bname,&p1->wname,&p1->press,&p1->sort,&p1->time.year,&p1->time.month,&p1->time.day,&p1->price);
		//fscanf(fp, "%d %s %s %s %s %d %d %d %f", p1->num,p1->bname,p1->wname,p1->press,p1->sort,p1->time.year,p1->time.month,p1->time.day,p1->price);
		//fscanf(fp, "%d%s%s%s%s%d%d%d%f\n", p1->num, p1->bname, p1->wname, p1->press,p1->sort, p1->time.year, p1->time.month, p1->time.day, p1->price);
		
		if (head == NULL) {
			head = p1; //ͷ�����Ա��ʼ��
			/*printf("\t\t %-6d%-17s%-10s%-17s%-9s%-d.%2d.%-5d%-.2f\n", head->num, head->bname, head->wname,
				head->press, head->sort, head->time.year, head->time.month, head->time.day, head->price);
			*/
			//head = (tail = p1); 
		}
		else {
			tail->next = p1; //����ͷ�� n>1ʱ�� [β][ͷ]��һ��ָ���·����p1
		}
		tail = p1; //ֻ��һ����Ա ͷβ��ͬ
	}
	tail->next = NULL; //����ѭ�� ���һ�������Աָ��NEXTΪNULL
	fclose(fp);
	return head;

}
void book_add() {
	
	struct book* head = NULL;
	char a;
	head = load();
	if (head == NULL) {
		printf("File context is null");
		getchar();
	}
	else {
	}



}

void book_get(struct book *head) {
	struct book* ptr;
	
	if (head == NULL) {
		printf("No Information");
		return;
	}

	printf(" ͼ����Ϣ��");
	printf("��� ͼ���� ������ ������ ��� ����ʱ�� �۸�\n");

	while (head->next != NULL) {
		printf("%d %s %s %s %s %d %d %d %f\n", head->num, head->bname, head->wname, head->press, head->sort, head->time.year, head->time.month, head->time.day, head->price);
		head = head->next;
	
	}
	getchar();

}