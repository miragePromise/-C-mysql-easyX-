#include "book.h"

void reader_login(MYSQL *sock) {
	while (1) {
		char id[70], pass[70], real_pass[70];
		char sqlbuf[200] = "SELECT reader_pass FROM reader where reader_id = '";

		cout << "�����û�id:" << endl;
		cin >> id;
		cout << "�����û�����:" << endl;
		cin >> pass;

		getMD5(sock, pass);
		strcpy_s(pass, global_str);

		strcat_s(sqlbuf, id);
		strcat_s(sqlbuf, "'");

		cout << "sqlbuf = " << sqlbuf << endl;
		cout << "pass = " << pass << endl;

		if (mysql_query(sock, sqlbuf)) {
			printf("���ݻ�ȡʧ��!%s", mysql_error(sock));
			return;
		}

		MYSQL_RES *result;
		MYSQL_ROW row;

		if (!(result = mysql_store_result(sock))) {
			printf("�����ȡʧ��!:%s", mysql_error(sock));
			return;
		}

		if (!mysql_num_rows(result)) {
			printf("���û�id������\n");
			return;
		}

		row = mysql_fetch_row(result);


		strcpy_s(real_pass, (char*)row[0]);

		mysql_free_result(result);
		if (!strcmp(real_pass, pass)) {
			cout << "�û��ɹ���¼��" << endl;
			user_operate(sock,id);
			break;
		}
		else {
			cout << "������������ԣ�" << endl;
			continue;
		}

	}
}