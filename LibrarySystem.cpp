//rewind函数作用等同于 (void)fseek(stream, 0L, SEEK_SET);
#include <stdio.h>
#include <Windows.h>

int mainmenu();
int adminmenu();
int usermenu();
int checkPasswd();

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


				case 1:  //add
				case 2:  //record
				case 3:  //get
				case 4:  //sort
				case 5:  //change
				case 6:  //delete
				case 7:  //edit

				}


			}
		case 2: //user

		}
	}


}


int mainmenu() {
	int x;
	printf("\n\n\n\n\n\n\n");
	printf("WELCOME \n");
	printf("1.Admin \n");
	printf("2.User \n");
	printf("3.Exit \n");
	printf("Enter your choice: \n");

	scanf("%d", &x);
	printf("\n");
	getchar();
	return x;

}

int adminmenu() {
	int x;
	printf("----------------------------------------------------------");
	printf("Book Information System");
	printf("----------------------------------------------------------");
	printf("**********************************************************");
	printf("\n\n\n\n\n\n\n");
	printf("WELCOME, BackGround System.\n");
	printf("1.Add Book Information       2.Record Book Information");
	printf("3.Get Book Information       4.Sort Book Information");
	printf("5.Change Book Information    6.delete Book Information");
	printf("7.Edit Account               0.Exit");
	printf("**********************************************************");
	printf("Enter id: ");
	scanf("%d",&x);
	getchar();
	return x;
}

int usermenu() {

}

int checkPasswd() {

	FILE* fp;
	char account[15], password[15];
	struct admin* p1, * head = NULL, * tail;
	if ((fp) = fopen("admin.txt", "r") == NULL) {
		printf("File open error! \n");
		exit(0);
	}
	if (fgetc(fp) == EOF) {
		return 1; //no passwd
	}
	rewind(fp);
	while (!feof(fp)) {
		p1 = (struct admin*) malloc(sizeof(struct admin)); //change
		fscanf(fp, "%s%s\n", p1->account, p1->password);
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
	printf("\t\tPlease Enter your user name: ");
	gets(account); //不读取换行符 会转换成\0   （char *str） 指针数组
	if (p1 == NULL) {
		printf("\t\t该账号不存在!\n");
		getchar();
		return 0;
	}
	bool isAccount = false;
	while (1) {

		if (strcmp(p1->account, account)) {
			isAccount = true;
			break;
		}
	}

	if (isAccount) {
		printf("\t\t请输入你的密码: \n");
		gets(password);

		if (strcmp(p1->password, password) == 0) {

			printf("\t\t%s密码验证 - [通过]", account);
			printf("\t\t请输入 [Enter] 进入后台" );
			getchar();
			system("cls");
			return 1;
		}
		else {
			printf("\t\t%s密码验证 - [失败]", account);
			getchar();
			system("cls");
			return 0;
		}
	}

}
