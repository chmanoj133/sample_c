 #include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <map>

void main_menu(struct node **data, char * error_msg, char *filename);
struct node * add_node_to_BST(struct node *root, int inorder_type, char *name, int *marks, int no_of_subjects);
struct node** add_node_to_all_BSTs(struct node **data, char *name, int *marks, int no_of_subjects);
void admin_main_menu(struct node**data, char *filename, char *error_msg);
void listings_main_menu(struct node **data, char *filename, char *error_msg);
char **subject_names(char *filename);
int string_length(char* str);
bool check_condition(struct node *root, int index, int num, int op);

struct node
{
	char *name;
	int *scores;
	struct node* left;
	struct node* right;
};

typedef std::map <int, struct node* > dict;

int total_marks(int *arr, int N)
{
	int i, ans = 0;
	for (i = 0; i < N; i++)
		ans = ans + arr[i];
	return ans;
}

bool string_compare(char *str1, char *str2)	
{
	int i;
	int len = string_length(str1);
	if (len != string_length(str2))
		return false;

	for (i = 0; i < len; i++)
	{
		if (str1[i] != str2[i])
			return false;
	}
	return true;
}

char *toLower(char *str)
{
	int i;
	for (i = 0; str[i] != '\0'; i++)
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] - 'A' + 'a';
	return str;
}

char *captilize(char *str)
{
	int i;

	if (str[0] >= 'a' && str[0] <= 'z')
		str[0] = str[0] - 'a' + 'A';

	for (i = 1; str[i + 1] != '\0'; i++)
	{
		if (str[i] == ' ' && str[i + 1] >= 'a' && str[i + 1] <= 'z')
			str[i + 1] = str[i + 1] - 'a' + 'A';
	}

	return str;
}

int string_length(char* str)
{
	int i;
	for (i = 0; str[i] != '\0'; i++);
	return i;
}

void save_data(struct node *root, FILE *p, int no_of_subjects)
{
	int i;
	if (root != NULL)
	{
		fprintf(p, "%s\n", root->name);
		if (total_marks(root->scores, no_of_subjects) != -no_of_subjects)
		{
			for (i = 0; i < no_of_subjects - 1; i++)
				fprintf(p, "%d,", root->scores[i]);
			fprintf(p, "%d\n", root->scores[i]);
		}
		save_data(root->left, p, no_of_subjects);
		save_data(root->right, p, no_of_subjects);
	}
}

void exit_prog(struct node **data, char *filename, int no_of_subjects)
{
	char **subjects = subject_names(filename);
	FILE *p1 = fopen(filename, "w");
	int i;

	fprintf(p1, "%d\n", no_of_subjects);
	for (i = 0; i < no_of_subjects - 1; i++)
		fprintf(p1, "%s,", subjects[i]);
	fprintf(p1, "%s\n", subjects[i]);

	system("cls");
	printf("Please wait while we save your changes...\n\n\n");
	save_data(data[0], p1, no_of_subjects);
	fclose(p1);
	system("pause");
}

// "Inorder_type" variable used to specify the inorder traversal of a BST:
// -2	->	Alphabetical wise
// -1	->	Total Marks wise
//	N 	->	Nth indexed subject -> marks wise  (0 <= N < No. of subjects)
struct node *find_student(struct node *bst, char *name, int inorder_type, int key, int no_of_subjects)
{
	int flag, i, total;
	FILE *p1;
	if (bst == NULL)
		return NULL;

	switch (inorder_type)
	{
	case -2:
		for (i = 0; bst->name[i] == name[i] && name[i] != '\0' && bst->name[i] != '\0'; i++);
		if (bst->name[i] == '\0' && name[i] == '\0')
			return bst;
		else
		{
			if (name[i] < bst->name[i])
				return find_student(bst->left, name, inorder_type, key, no_of_subjects);
			else if (name[i] > bst->name[i])
				return find_student(bst->right, name, inorder_type, key, no_of_subjects);
		}
		break;
	case -1:
		total = total_marks(bst->scores, no_of_subjects);
		if (total == key)
			return bst;
		else
		{
			if (key <= total)
				return find_student(bst->left, name, inorder_type, key, no_of_subjects);
			else if (key > total)
				return find_student(bst->right, name, inorder_type, key, no_of_subjects);
		}
		break;
	default:
		if (inorder_type >= no_of_subjects)
			return NULL;
		if (key == bst->scores[inorder_type])
			return bst;
		else
		{
			if (key <= bst->scores[inorder_type])
				return find_student(bst->left, name, inorder_type, key, no_of_subjects);
			else if (key > bst->scores[inorder_type])
				return find_student(bst->right, name, inorder_type, key, no_of_subjects);
		}
		break;
	}
	return NULL;
}

char **subject_names(char *filename)
{
	FILE *p1 = fopen(filename, "r"), *p2;
	char c, **subs;
	int no_of_subjects, i = 0, index = 0;

	fscanf(p1, "%d", &no_of_subjects);
	subs = (char**)calloc(no_of_subjects, sizeof(char*));
	c = fgetc(p1);
	if (c != '\n')
		for (; c != '\n'; c = fgetc(p1));
	subs[index] = (char*)calloc(i, sizeof(char));
	while (1)
	{
		c = fgetc(p1);
		if (c == ',')
		{
			subs[index][i] = '\0';
			index++;
			i = 0;
			subs[index] = (char*)calloc(25, sizeof(char));
			c = fgetc(p1);
			if (c == ' ')
				c = fgetc(p1);
		}
		if (c == '\n')
			break;
		subs[index][i] = c;
		i++;
	}

	return subs;
}

// "Inorder_type" variable used to specify the inorder traversal of a BST:
// -2	->	Alphabetical wise
// -1	->	Total Marks wise
//	N 	->	Nth indexed subject marks wise  (0 <= N < No. of subjects)
struct node *delete_node_BST(struct node *root, char *name, int *marks, int inorder_type, int no_of_subjects)
{
	int i, total, key;
	struct node *temp;

	if (root == NULL)
		return NULL;
	switch (inorder_type)
	{
	case -2:
		for (i = 0; name[i] == root->name[i] && name[i] != '\0' && root->name[i] != '\0'; i++);
		if (!(name[i] == '\0' && root->name[i] == '\0'))
		{
			if (name[i] < root->name[i])
				root->left = delete_node_BST(root->left, name, marks, inorder_type, no_of_subjects);
			else if (name[i] > root->name[i])
				root->right = delete_node_BST(root->right, name, marks, inorder_type, no_of_subjects);
		}
		else
		{
			if (root->left == NULL)
				return root->right;
			else if (root->right == NULL)
				return root->left;

			temp = root->right;
			while (temp->left != NULL)
				temp = temp->left;
			root->name = temp->name;
			root->scores = temp->scores;
			root->right = delete_node_BST(root->right, temp->name, temp->scores, inorder_type, no_of_subjects);
		}
		return root;
		break;
	case -1:
		key = total_marks(marks, no_of_subjects);
		total = total_marks(root->scores, no_of_subjects);
		for (i = 0; name[i] == root->name[i] && name[i] != '\0' && root->name[i] != '\0'; i++);
		if (!(name[i] == '\0' && root->name[i] == '\0' && total == key))
		{
			if (key <= total)
				root->left = delete_node_BST(root->left, name, marks, inorder_type, no_of_subjects);
			else if (name[i] > root->name[i])
				root->right = delete_node_BST(root->right, name, marks, inorder_type, no_of_subjects);
		}
		else
		{
			if (root->left == NULL)
				return root->right;
			else if (root->right == NULL)
				return root->left;

			temp = root->right;
			while (temp->left != NULL)
				temp = temp->left;
			root->name = temp->name;
			root->scores = temp->scores;
			root->right = delete_node_BST(root->right, temp->name, temp->scores, inorder_type, no_of_subjects);
		}
		return root;
		break;
	default:
		for (i = 0; name[i] == root->name[i] && name[i] != '\0' && root->name[i] != '\0'; i++);
		if (!(name[i] == '\0' && root->name[i] == '\0' && marks[inorder_type] == root->scores[inorder_type]))
		{
			if (marks[inorder_type] <= root->scores[inorder_type])
				root->left = delete_node_BST(root->left, name, marks, inorder_type, no_of_subjects);
			else if (marks[inorder_type] > root->scores[inorder_type])
				root->right = delete_node_BST(root->right, name, marks, inorder_type, no_of_subjects);
		}
		else
		{
			if (root->left == NULL)
				return root->right;
			else if (root->right == NULL)
				return root->left;

			temp = root->right;
			while (temp->left != NULL)
				temp = temp->left;
			root->name = temp->name;
			root->scores = temp->scores;
			root->right = delete_node_BST(root->right, temp->name, temp->scores, inorder_type, no_of_subjects);
		}
		return root;
		break;
	}
}

void student_main_menu(struct node **data, struct node *student_node, char *error_msg, char *filename)
{
	int option, i, no_of_subjects, choice, max = -2, index = 0, *marks;
	float avg = 0;
	char **subjects = subject_names(filename), *new_name, *name, c;
	FILE *p1 = fopen(filename, "r");
	fscanf(p1, "%d", &no_of_subjects);
	fclose(p1);
	system("cls");
	printf("Welcome %s\n\n", captilize(student_node->name));
	toLower(student_node->name);
	if (error_msg != NULL)
		printf("Error: %s", error_msg);
	printf("\n\n");
	printf("[1] View your marks\n");
	printf("[2] View my maximum marks and its subject\n");
	printf("[3] View marks of a particular subject\n");
	printf("[4] View my average\n");
	printf("[5] Change Profile info(At present, you have access to change only name)\n\n");
	printf("[9] <-- Go back (log out)\n");
	printf("[0] Exit\n\n");
	printf("Enter your choice: ");
	scanf("%d", &option);

	switch (option)
	{
	case 1:
		system("cls");
		printf("Welcome %s\n\nYour marks :\n\n", captilize(student_node->name));
		toLower(student_node->name);
		for (i = 0; i < no_of_subjects; i++)
		{
			if (student_node->scores[i] == -1)
				printf("%s marks are not enrolled\n", subjects[i]);
			else
				printf("%s  : %d\n", subjects[i], student_node->scores[i]);
		}
		printf("\n\n[1] <-- Go Back\n[0] Exit\n\nEnter your choice: ");
		scanf("%d", &choice);
		if (choice == 1)
			student_main_menu(data, student_node, NULL, filename);
		else if (choice == 0)
			exit_prog(data, filename, no_of_subjects);
		else
			student_main_menu(data, student_node, "Wrong choice", filename);
		break;
	case 2:
		for (i = 0; i < no_of_subjects; i++)
			if (max < student_node->scores[i])
			{
				max = student_node->scores[i];
				index = i;
			}
		system("cls");
		if (max == -1)
			student_main_menu(data, student_node, "\b\b\b\b\b\b\bNo subject marks are enrolled", filename);
		else
		{
			printf("You have got maximum of %d in %s Subject !! Congratulations", max, subjects[index]);
			printf("\n\n[1] <-- Go Back\n[0] Exit\n\nEnter your choice: ");
			scanf("%d", &choice);
			if (choice == 1)
				student_main_menu(data, student_node, NULL, filename);
			else if (choice == 0)
				exit_prog(data, filename, no_of_subjects);
			else
				student_main_menu(data, student_node, "Wrong choice", filename);
		}
		break;
	case 3:
		system("cls");
		printf("Welcome %s ! Select a subject to view its marks\n\n", student_node->name);
		for (i = 1; i <= no_of_subjects; i++)
			printf("[%d] %s\n", i, subjects[i - 1]);
		printf("[0] Exit\n[-1] <-- Go Back\n\nEnter Your Choice: ");
		scanf("%d", &choice);
		if (choice >= 1 && choice <= no_of_subjects)
		{
			system("cls");
			if (student_node->scores[choice - 1] == -1)
				printf("This Subject marks are not enrolled.\n\n");
			else
				printf("You have got %d marks in %s subject\n\n", student_node->scores[choice - 1], subjects[choice - 1]);
			printf("[0] Exit\n[1] Go to Student menu\n\nEnter your choice: ");
			scanf("%d", &choice);
			if (choice == 0)
				exit_prog(data, filename, no_of_subjects);
			else if (choice == 1)
				student_main_menu(data, student_node, NULL, filename);
			else
				student_main_menu(data, student_node, "Wrong Option", filename);
		}
		else if (choice == 0)
			exit_prog(data, filename, no_of_subjects);
		else if (choice == -1)
			student_main_menu(data, student_node, NULL, filename);
		else
			student_main_menu(data, student_node, "Wrong Option", filename);
		break;
	case 4:
		avg = total_marks(student_node->scores, no_of_subjects);
		avg = avg / no_of_subjects;
		if (avg < 0)
			student_main_menu(data, student_node, "Your marks are not enrolled", filename);
		else
		{
			system("cls");
			printf("You have an average of %f", avg);
			printf("\n\n[1] <-- Go Back\n[0] Exit\n\nEnter your choice: ");
			scanf("%d", &choice);
			if (choice == 1)
				student_main_menu(data, student_node, NULL, filename);
			else if (choice == 0)
				exit_prog(data, filename, no_of_subjects);
			else
				student_main_menu(data, student_node, "Wrong choice", filename);
		}
		break;
	case 5:
		system("cls");
		printf("Are you Sure ? [y/n]: ");
		c = _getch();
		if (c == 'y' || c == 'Y')
		{
			system("cls");
			printf("Enter your new name (max 25 chars): ");
			new_name = (char*)calloc(25, sizeof(char));
			fflush(stdin);
			scanf("%[^\n]s", new_name);
			new_name = toLower(new_name);
			if (find_student(data[0], new_name, -2, NULL, no_of_subjects) != NULL)
			{
				student_main_menu(data, student_node, "Already Such name exists. Try by adding Surname", filename);
				return;
			}
			for (i = 0; new_name[i] != '\0'; i++)
				student_node->name[i] = new_name[i];
			student_node->name[i] = '\0';
			name = student_node->name;
			marks = student_node->scores;
			data[0] = delete_node_BST(data[0], name, marks, -2, no_of_subjects);
			data[0] = add_node_to_BST(data[0], -2, name, marks, no_of_subjects);
			student_node = find_student(data[0], name, -2, NULL, no_of_subjects);
			student_main_menu(data, student_node, "\b\b\b\b\b\b\bYour name is Successfully changed", filename);
		}
		else if (c == 'n' || c == 'N')
			student_main_menu(data, student_node, NULL, filename);
		else
			student_main_menu(data, student_node, "Wrong key was pressed ! Please try again", filename);
		break;
	case 9:
		main_menu(data, NULL, filename);
		break;
	case 0:
		exit_prog(data, filename, no_of_subjects);
		break;
	default:
		student_main_menu(data, student_node, "You have choosen Wrong Option", filename);
		break;
	}
}

void student_login(struct node ** data, char *filename)
{
	char *name = (char*)calloc(25, sizeof(char));
	struct node *student_data_node;
	int no_of_subjects;
	FILE *p1 = fopen(filename, "r");

	fscanf(p1, "%d", &no_of_subjects);
	fclose(p1);
	printf("\n\nEnter student name: ");
	fflush(stdin);
	scanf("%[^\n]s", name);
	name = toLower(name);
	student_data_node = find_student(data[0], name, -2, NULL, no_of_subjects);

	if (student_data_node == NULL)
		main_menu(data, "Student not found", filename);
	else
		student_main_menu(data, student_data_node, NULL, filename);
}

void edit_student_data_menu(struct node **data, struct node *student_node, char *error_msg, int no_of_subjects,char* filename)
{
	int option, *marks, i, choice, new_score;
	char *new_name, *name, **subjects = subject_names(filename);
	system("cls");
	printf("Welcome to profile of %s\n\n", captilize(student_node->name));
	student_node->name = toLower(student_node->name);
	if (error_msg != NULL)
		printf("%s", error_msg);
	printf("\n\n[1] Change student name\n");
	printf("[2] Change a particular subject marks\n");
	printf("[3] Change all subject marks\n");
	printf("[9] Go back\n[0] Exit\n\nEnter a option: ");
	scanf("%d", &option);
	switch (option)
	{
	case 1:
		system("cls");
		printf("Enter new name (max 25 chars): ");
		new_name = (char*)calloc(25, sizeof(char));
		scanf("%s", new_name);
		new_name = toLower(new_name);
		if (find_student(data[0], new_name, -2, NULL, no_of_subjects) != NULL)
		{
			edit_student_data_menu(data, student_node, "Error: Already Such name exists. Try by adding Surname", no_of_subjects, filename);
			return;
		}
		for (i = 0; new_name[i] != '\0'; i++)
			student_node->name[i] = new_name[i];
		student_node->name[i] = '\0';
		name = student_node->name;
		marks = student_node->scores;
		data[0] = delete_node_BST(data[0], name, marks, -2, no_of_subjects);
		data[0] = add_node_to_BST(data[0], -2, name, marks, no_of_subjects);
		student_node = find_student(data[0], name, -2, NULL, no_of_subjects);
		edit_student_data_menu(data, student_node, "Successfully Changed", no_of_subjects, filename);
		break;
	case 2:
		system("cls");
		printf("Select a subject\n\n");
		for (i = 0; i < no_of_subjects; i++)
			printf("[%d] %s\n", i + 1, subjects[i]);
		printf("\n[9] Go Back\n[0] Exit\n\nEnter your Choice: ");
		scanf("%d", &choice);
		if (choice > 0 && choice <= no_of_subjects)
		{
			system("cls");
			printf("If you dont want to change, enter -1\n\n");
			printf("Enter new Score of %s(previous score is %d): ", subjects[choice - 1], student_node->scores[choice - 1]);
			scanf("%d", &new_score);
			if (new_score >= 0 && new_score <= 100){
				student_node->scores[choice - 1] = new_score;
				data[no_of_subjects + 2] = delete_node_BST(data[no_of_subjects + 2], student_node->name, student_node->scores, -2, no_of_subjects);
				data[choice + 1] = delete_node_BST(data[choice + 1], student_node->name, student_node->scores, choice - 1, no_of_subjects);
				data[choice + 1] = add_node_to_BST(data[choice + 1], choice - 1, student_node->name, student_node->scores, no_of_subjects);
				edit_student_data_menu(data, student_node, "Successfully Changes are done", no_of_subjects, filename);
			}
			else if (new_score == -1)
				edit_student_data_menu(data, student_node, "No changes were done", no_of_subjects, filename);
			else
				edit_student_data_menu(data, student_node, "Error: Marks must lie between 0 & 100", no_of_subjects, filename);
		}
		else if (choice == 9)
			edit_student_data_menu(data, student_node, NULL, no_of_subjects, filename);
		else if (choice == 0)
			exit_prog(data, filename, no_of_subjects);
		else
			edit_student_data_menu(data, student_node, "Error: Wrong key pressed. Try again", no_of_subjects, filename);
		break;
	case 3:
		system("cls");
		printf("\n\nPress -1 if you dont want to change that subject\n\n");
		for (i = 0; i < no_of_subjects; i++)
		{
			printf("Enter new score of %s (previous score is %d) : ", subjects[i], student_node->scores[i]);
			scanf("%d", &new_score);
			if (new_score >= 0 && new_score <= 100)
			{
				student_node->scores[i] = new_score;
				data[i + 2] = delete_node_BST(data[i + 2], student_node->name, student_node->scores, i, no_of_subjects);
				data[i + 2] = add_node_to_BST(data[i + 2], i, student_node->name, student_node->scores, no_of_subjects);
			}
			else if (new_score != -1)
			{
				admin_main_menu(data, filename, "Marks must lie between 0 and 100");
				return;
			}
			printf("\n\n");
		}
		data[no_of_subjects + 2] = delete_node_BST(data[no_of_subjects + 2], student_node->name, student_node->scores, -2, no_of_subjects);
		edit_student_data_menu(data, student_node, "Succesfully Changes were done", no_of_subjects, filename);
		break;
	case 9:
		admin_main_menu(data, filename, NULL);
		break;
	case 0:
		exit_prog(data, filename, no_of_subjects);
		break;
	}
}

dict students_with_missed_data(struct node *root, int *i, dict select_student)
{
	if (root != NULL)
	{
		select_student = students_with_missed_data(root->left, i, select_student);
		select_student[*i] = root;
		*i = *i + 1;
		select_student = students_with_missed_data(root->right, i, select_student);
	}
	return select_student;
}

void admin_main_menu(struct node**data, char *filename, char *error_msg)
{
	int option, *marks, no_of_subjects, score, i, j, stop = 0, index, selection = -1;
	char *name, **subjects = subject_names(filename), choice;
	struct node* student_node = NULL;
	FILE *p1 = fopen(filename, "r");
	dict student_at_index;
	fscanf(p1, "%d", &no_of_subjects);
	fclose(p1);
	system("cls");
	printf("Welcome Admin !! \n\n");
	if (error_msg != NULL)
		printf("Error: %s", error_msg);
	printf("\n\n");
	printf("[1] Add a student\n");
	printf("[2] Edit a student name and his marks\n");
	printf("[3] Remove a student\n");
	printf("[4] View List of students whose data is missing and enroll their marks\n");
	printf("[9] Log out\n");
	printf("[0] Exit\n\n");
	printf("Enter your option: ");
	scanf("%d", &option);

	switch (option)
	{
	case 1:
		system("cls");
		printf("Enter student name(max 25 chars allowed): ");
		name = (char*)calloc(25, sizeof(char));
		scanf("%s", name);
		student_node = find_student(data[0], name, -2, NULL, no_of_subjects);
		if (student_node != NULL)
		{
			printf("\n\nFound a Student with same name. Would you like to edit his marks ? [y/n] : ");
			choice = _getch();
			if (choice == 'y' || choice == 'Y')
			{
				printf("\n\nPress -1 if you dont want to change that subject\n\n");
				for (i = 0; i < no_of_subjects; i++)
				{
					printf("Enter new score of %s (previous score is %d) : ", subjects[i], student_node->scores[i]);
					scanf("%d", &score);
					if (score >= 0 && score <= 100)
					{
						student_node->scores[i] = score;
						data[i + 2] = delete_node_BST(data[i + 2], student_node->name, student_node->scores, i, no_of_subjects);
						data[i + 2] = add_node_to_BST(data[i + 2], i, student_node->name, student_node->scores, no_of_subjects);
					}
					else if (score != -1)
					{
						admin_main_menu(data, filename, "Marks must lie between 0 and 100");
						return;
					}
					printf("\n\n");
				}
				admin_main_menu(data, filename, "\b\b\b\b\b\b\bSuccesfully changed his details");
			}
			else if (choice == 'n' || choice == 'N')
				admin_main_menu(data, filename, NULL);
			else
				admin_main_menu(data, filename, "Wrong Key was pressed. Please try again");
		}
		else
		{
			printf("\n\nPress -1 if you dont want to enter that subject\n\n");
			marks = (int*)calloc(no_of_subjects, sizeof(int));
			for (i = 0; i < no_of_subjects; i++)
			{
				printf("Enter the score of %s subject: ", subjects[i]);
				scanf("%d", &score);
				if (score >= 0 && score <= 100)
					marks[i] = score;
				else if (score != -1)
				{
					admin_main_menu(data, filename, "Marks must lie between 0 and 100. Retry again. Student data enrolling failed");
					return;
				}
				printf("\n\n");
			}
			data = add_node_to_all_BSTs(data, name, marks, no_of_subjects);
			admin_main_menu(data, filename, "\b\b\b\b\b\b\bSuccesfully Added a student");
		}
		break;
	case 2:
		system("cls");
		printf("Enter student's name: ");
		name = (char*)calloc(25, sizeof(char));
		scanf("%s", name);
		student_node = find_student(data[0], name, -2, NULL, no_of_subjects);
		if (student_node == NULL)
			admin_main_menu(data, filename, "Student Not found with that name. Try adding a surname");
		else
			edit_student_data_menu(data, student_node, NULL, no_of_subjects, filename);
		break;
	case 3:
		system("cls");
		printf("Enter student's name: ");
		name = (char*)calloc(25, sizeof(char));
		scanf("%s", name);
		student_node = find_student(data[0], name, -2, NULL, no_of_subjects);
		if (student_node != NULL)
		{
			marks = student_node->scores;
			data[0] = delete_node_BST(data[0], name, marks, -2, no_of_subjects);
			data[1] = delete_node_BST(data[1], name, marks, -1, no_of_subjects);
			for (i = 0; i < no_of_subjects; i++)
				data[2 + i] = delete_node_BST(data[2 + i], name, marks, i, no_of_subjects);
			admin_main_menu(data, filename, "\b\b\b\b\b\b\bSuccesfully Removed a student");
		}
		else
			admin_main_menu(data, filename, "No such student found");
		break;
	case 4: 
		i = 1, j = 0;
		system("cls");
		printf("Please be patient while we are fetching the missed data students . . .");
		student_at_index = students_with_missed_data(data[no_of_subjects + 2], &i, student_at_index);
		system("cls");
		printf("Viewing first 200 members at a time. Scroll Down for options\n\n");
		i = 1;
		for (dict::iterator it = student_at_index.begin(); it != student_at_index.end(); it++, i++)
		{
			printf("[%d] %s\n", i, captilize(student_at_index[i]->name));
			student_at_index[i]->name = toLower(student_at_index[i]->name);
			if (i >= (200*j + 200))
			{
				j++;
				printf("\n\nYour options:\n");
				printf("\n[1] Select a student from the above list to edit his marks\n[2] View next 200\n[9] Go back\n[0] Exit\n\n");
				printf("Your choice: ");
				scanf("%d", &selection);
				if (selection != 2)
					break;
				system("cls");
				printf("Viewing next 200 results\n\n");
			}
		}
		if (selection == 2 || selection == -1)
		{
			j++;
			printf("\n\nYour options:\n");
			printf("\n[1] Select a student from the above list to edit his marks\n[9] Go back\n[0] Exit\n\n");
			printf("Your choice: ");
			scanf("%d", &selection);
		}
		if (selection == 1)
		{
			printf("\n\nEnter the index of student printed above (scroll up and see): ");
			scanf("%d", &index);
			if (index >= (j - 1) * 200 && index <= ((j - 1) * 200 + 200))
				edit_student_data_menu(data, student_at_index[index], NULL, no_of_subjects, filename);
			else
				admin_main_menu(data, filename, "You have choosen index which is not shown above");
		}
		else if (selection == 9)
			admin_main_menu(data, filename, NULL);
		else if (selection == 0)
			exit_prog(data, filename, no_of_subjects);
		else 
			admin_main_menu(data, filename, "You have choosen a Wrong option");
		break;
	case 9:
		main_menu(data, NULL, filename);
		break;
	case 0:
		exit_prog(data, filename, no_of_subjects);
		break;
	default:
		admin_main_menu(data, filename, "You have choosen wrong option. Try again");
		break;
	}
}

void admin_login(struct node **data, char *filename, char *error_msg, int tries)
{
	int i = 0;
	bool correct = true;
	char *pin = "1234", c;
	system("cls");
	if (error_msg != NULL)
		printf("%s\n\n", error_msg);
	printf("Enter 4 Digit Pin(backspace disabled): ");
	if (tries <= 0)
	{
		main_menu(data, "3 wrong PIN's ! Try again after sometime", filename);
		return;
	}
	while (i < 4)
	{
		c = _getch();
		if (c == '\n')
		{
			admin_login(data, filename, "No Need to press Enter. Try again", tries - 1);
			return;
		}
		if (c != pin[i])
			correct = false;
		printf("*");
		i++;
	}

	if (!correct)
		admin_login(data, filename, "Wrong PIN try again", tries - 1);
	else
		admin_main_menu(data, filename, NULL);
}

void list_alphabetical(struct node** data, struct node *root, char *filename, int *i, int *j, int *stop, int no_of_subjects)
{
	int option, k;
	if (root != NULL && *stop == 0)
	{
		list_alphabetical(data, root->left, filename, i, j, stop, no_of_subjects);
		printf("[%d] %s\t\t\t", *i, captilize(root->name));
		root->name = toLower(root->name);
		for (k = 1; k < no_of_subjects + 1; k++)
			printf("subject[%d]: %d\t", k, root->scores[k - 1]);
		printf("\n");
		*i = *i + 1;
		if (*i > (200 * (*j) + 200))
		{
			*j = *j + 1;
			printf("\n\nSelect an option\n\n[1] View next 200\n[2] Enter a student name to edit his details\n[3] Go back\n[0] Exit\n\nEnter an option: ");
			scanf("%d", &option);
			if (option == 0)
			{
				*stop = 1;
				exit_prog(data, filename, no_of_subjects);
			}
			else if (option == 2)
			{
				*stop = 1;
				student_login(data, filename);
			}
			else if (option == 3)
			{
				*stop = 1;
				listings_main_menu(data, filename, NULL);
			}
			else if (option != 1)
			{
				*stop = 1;
				system("cls");
				printf("\nYou have choosen a wrong option !!\n\n");
				system("pause");
				exit_prog(data, filename, no_of_subjects);
			}
			else if (option == 1)
			{
				system("cls");
				printf("Viewing next 200 results\n\n");
			}
		}
		list_alphabetical(data, root->right, filename, i, j, stop, no_of_subjects);
	}
}

void list_total_marks(struct node **data, struct node *root, char *filename, int *i, int *j, int* stop, int no_of_subjects)
{
	int option;
	if (root != NULL && *stop == 0)
	{
		list_total_marks(data, root->right, filename, i, j, stop, no_of_subjects);
		printf("[%d] %s\t\t\t---> %d\n", *i, captilize(root->name), total_marks(root->scores, no_of_subjects));
		root->name = toLower(root->name);
		*i = *i + 1;
		if (*i > (200 * (*j) + 200))
		{
			*j = *j + 1;
			printf("\n\nSelect an option\n\n[1] View next 200\n[2] Enter a student name to edit his details\n[3] Go back\n[0] Exit\n\nEnter an option: ");
			scanf("%d", &option);
			if (option == 0)
			{
				*stop = 1;
				exit_prog(data, filename, no_of_subjects);
			}
			else if (option == 2)
			{
				*stop = 1;
				student_login(data, filename);
			}
			else if (option == 3)
			{
				*stop = 1;
				listings_main_menu(data, filename, NULL);
			}
			else if (option != 1)
			{
				*stop = 1;
				system("cls");
				printf("\nYou have choosen a wrong option !!\n\n");
				system("pause");
				exit_prog(data, filename, no_of_subjects);
			}
			else if (option == 1)
			{
				system("cls");
				printf("Viewing next 200 results\n\n");
			}
		}
		list_total_marks(data, root->left, filename, i, j, stop, no_of_subjects);
	}
}

void list_particular_subject(struct node **data, struct node *root, char *filename, int *i, int *j, int *stop, int no_of_subjects, int index)
{
	int option;
	if (root != NULL && *stop != 1)
	{
		list_particular_subject(data, root->right, filename, i, j, stop, no_of_subjects, index);
		printf("[%d] %s\t\t\t ---> %d\n", *i, root->name, root->scores[index]);
		*i = *i + 1;
		if (*i > (200 * (*j) + 200))
		{
			*j = *j + 1;
			printf("\n\nSelect an option\n\n[1] View next 200\n[2] Enter a student name to edit his details\n[3] Go back\n[0] Exit\n\nEnter an option: ");
			scanf("%d", &option);
			if (option == 0)
			{
				*stop = 1;
				exit_prog(data, filename, no_of_subjects);
			}
			else if (option == 2)
			{
				*stop = 1;
				student_login(data, filename);
			}
			else if (option == 3)
			{
				*stop = 1;
				listings_main_menu(data, filename, NULL);
			}
			else if (option != 1)
			{
				*stop = 1;
				system("cls");
				printf("\nYou have choosen a wrong option !!\n\n");
				system("pause");
				exit_prog(data, filename, no_of_subjects);
			}
			else if (option == 1)
			{
				system("cls");
				printf("Viewing next 200 results\n\n");
			}
		}
		list_particular_subject(data, root->left, filename, i, j, stop, no_of_subjects, index);
	}
}

char *remove_spaces(char *str)
{
	char *new_str = (char*)calloc(50, sizeof(char));
	int i, j;
	for (i = 0, j = 0; str[i] != '\0'; i++)
		if (str[i] != ' ')
		{
			new_str[j] = str[i];
			j++;
		}
	new_str[j] = '\0';
	return new_str;
}

void list_one_condition(struct node **data, struct node *root, char *filename, int *i, int *j, int *stop, int no_of_subjects, int index, int op, int num)
{
	int option, total;
	if (root != NULL && *stop != 1)
	{
		list_one_condition(data, root->right, filename, i, j, stop, no_of_subjects, index, op, num);
		switch (op)
		{
		case 0:
			if (root->scores[index - 2] == num && index != 1)
			{
				printf("[%d] %s\t\t\t ---> %d\n", *i, root->name, root->scores[index - 2]);
				*i = *i + 1;
			}
			else if (index == 1)
			{
				total = total_marks(root->scores, no_of_subjects);
				if (total == num)
				{
					printf("[%d] %s\t\t\t ---> %d\n", *i, root->name, total);
					*i = *i + 1;
				}
			}
			break;
		case 1:
			if (root->scores[index - 2] < num && index != 1)
			{
				printf("[%d] %s\t\t\t ---> %d\n", *i, root->name, root->scores[index - 2]);
				*i = *i + 1;
			}
			else if (index == 1)
			{
				total = total_marks(root->scores, no_of_subjects);
				if (total < num)
				{
					printf("[%d] %s\t\t\t ---> %d\n", *i, root->name, total);
					*i = *i + 1;
				}
			}
			break;
		case 2:
			if (root->scores[index - 2] > num && index != 1)
			{
				printf("[%d] %s\t\t\t ---> %d\n", *i, root->name, root->scores[index - 2]);
				*i = *i + 1;
			}
			else if (index == 1)
			{
				total = total_marks(root->scores, no_of_subjects);
				if (total > num)
				{
					printf("[%d] %s\t\t\t ---> %d\n", *i, root->name, total);
					*i = *i + 1;
				}
			}
			break;
		}
		if (*i > (200 * (*j) + 200))
		{
			*j = *j + 1;
			printf("\n\nSelect an option\n\n[1] View next 200\n[2] Enter a student name to edit his details\n[3] Go back\n[0] Exit\n\nEnter an option: ");
			scanf("%d", &option);
			if (option == 0)
			{
				*stop = 1;
				exit_prog(data, filename, no_of_subjects);
			}
			else if (option == 2)
			{
				*stop = 1;
				student_login(data, filename);
			}
			else if (option == 3)
			{
				*stop = 1;
				listings_main_menu(data, filename, NULL);
			}
			else if (option != 1)
			{
				*stop = 1;
				system("cls");
				printf("\nYou have choosen a wrong option !!\n\n");
				system("pause");
				exit_prog(data, filename, no_of_subjects);
			}
			else if (option == 1)
			{
				system("cls");
				printf("Viewing next 200 results\n\n");
			}
		}
		list_one_condition(data, root->left, filename, i, j, stop, no_of_subjects, index, op, num);
	}
}

void one_condition_leaderboard(struct node  **data, char *filename, int no_of_subjects)
{
	char **subjects = subject_names(filename);
	char *str = (char*)calloc(100, sizeof(char));
	char *sub = (char*)calloc(25, sizeof(char));
	int i, symbol, num = 0, index = 0, j = 0, stop = 0, choice;
	system("cls");
	printf("Enter query(e.g: physics > 60): ");
	fflush(stdin);
	scanf("%[^\n]s", str);
	printf("\n\n");
	str = remove_spaces(str);
	str = toLower(str);
	for (i = 0; i < no_of_subjects; i++)
		subjects[i] = toLower(remove_spaces(subjects[i]));
	for (i = 0; str[i] != '\0' && str[i] != '<' && str[i] != '>' && str[i] != '='; i++)
		sub[i] = str[i];

	if (str[i] == '<')
		symbol = 1;
	else if (str[i] == '>')
		symbol = 2;
	else if (str[i] == '=')
		symbol = 0;
	else symbol = -1;
	i++;
	if (symbol != -1)
		for (; str[i] != '\0'; i++)
			num = num * 10 + (str[i] - '0');
	else
	{
		listings_main_menu(data, filename, "Wrong operator used");
		return;
	}

	if (string_compare(sub, "total"))
		index = 1;
	else
	{
		for (i = 0; i < no_of_subjects; i++)
			if (string_compare(sub, subjects[i]))
				break;
		if (i == no_of_subjects)
			return listings_main_menu(data, filename, "We are unable to understand subject name");
		index = 2 + i;
	}
	i = 1;

	list_one_condition(data, data[index], filename, &i, &j, &stop, no_of_subjects, index, symbol, num);
	if (stop == 0)
	{
		printf("\n\nSelect an option\n\n[1] Enter a student name to view his details\n[2] Go back\n[0] Exit\n\nEnter an option: ");
		scanf("%d", &choice);
		if (choice == 1)
			student_login(data, filename);
		else if (choice == 0)
			exit_prog(data, filename, no_of_subjects);
		else if (choice == 2)
			listings_main_menu(data, filename, NULL);
		else
			listings_main_menu(data, filename, "Wrong option was choosen");
	}
}

void list_two_conditions(struct node **data, struct node *root, char *filename, int *i, int *j, int *stop, int no_of_subjects,  int *index, int *op, int *num, int is_and)
{
	int option;
	if (root != NULL && *stop != 1)
	{
		list_two_conditions(data, root->right, filename, i, j, stop, no_of_subjects, index, op, num, is_and);
		switch (is_and)
		{
		case 1:
			if (check_condition(root, index[0], num[0], op[0]) && check_condition(root, index[1], num[1], op[1]))
			{
				printf("[%d] %s\t\t\t%d\t%d\n", *i, root->name, root->scores[index[0]], root->scores[index[1]]);
				*i = *i + 1;
			}
			break;
		case 0:
			if (check_condition(root, index[0], num[0], op[0]) || check_condition(root, index[1], num[1], op[1]))
			{
				printf("[%d] %s\t\t\t%d\t%d\n", *i, root->name, root->scores[index[0]], root->scores[index[1]]);
				*i = *i + 1;
			}
			break;
		}
		if (*i > (200 * (*j) + 200))
		{
			*j = *j + 1;
			printf("\n\nSelect an option\n\n[1] View next 200\n[2] Enter a student name to edit his details\n[3] Go back\n[0] Exit\n\nEnter an option: ");
			scanf("%d", &option);
			if (option == 0)
			{
				*stop = 1;
				exit_prog(data, filename, no_of_subjects);
			}
			else if (option == 2)
			{
				*stop = 1;
				student_login(data, filename);
			}
			else if (option == 3)
			{
				*stop = 1;
				listings_main_menu(data, filename, NULL);
			}
			else if (option != 1)
			{
				*stop = 1;
				system("cls");
				printf("\nYou have choosen a wrong option !!\n\n");
				system("pause");
				exit_prog(data, filename, no_of_subjects);
			}
			else if (option == 1)
			{
				system("cls");
				printf("Viewing next 200 results\n\n");
			}
		}

		list_two_conditions(data, root->left, filename, i, j, stop, no_of_subjects, index, op, num, is_and);
	}
}

bool check_condition(struct node *root, int index, int num, int op)
{
	switch (op)
	{
	case 0:
		if (root->scores[index] == num)
			return true;
		else
			return false;
		break;
	case 1:
		if (root->scores[index] < num)
			return true;
		else
			return false;
		break;
	case 2:
		if (root->scores[index] > num)
			return true;
		else
			return false;
		break;
	}
}

void two_condition_leaderboard(struct node  **data, char *filename, int no_of_subjects)
{
	char **subjects = subject_names(filename);
	char *str = (char*)calloc(100, sizeof(char));
	char **sub = (char**)calloc(2, sizeof(char*));
	int i, symbol[2], num[2] = { 0, 0 }, index[2] = { 0, 0 }, j = 0, stop = 0, choice, q = 0, is_and = -1;
	system("cls");
	printf("Enter query(e.g: physics > 60 and chemistry < 100): ");
	fflush(stdin);
	scanf("%[^\n]s", str);
	printf("\n\n");
	str = remove_spaces(str);
	str = toLower(str);
	for (i = 0; i < no_of_subjects; i++)
		subjects[i] = toLower(remove_spaces(subjects[i]));
	sub[q] = (char*)calloc(25, sizeof(char));

	for (i = 0; str[i] != '\0' && str[i] != '<' && str[i] != '>' && str[i] != '='; i++)
		sub[q][i] = str[i];

	if (str[i] == '<')
		symbol[q] = 1;
	else if (str[i] == '>')
		symbol[q] = 2;
	else if (str[i] == '=')
		symbol[q] = 0;
	else 
		symbol[q] = -1;
	i++;
	if (symbol[q] != -1)
		for (; str[i] != 'a' && str[i] != 'o'; i++)
			num[q] = num[q] * 10 + (str[i] - '0');
	else
	{
		listings_main_menu(data, filename, "Wrong operator used");
		return;
	}

	if (str[i] == 'a' && str[i + 1] == 'n' && str[i + 2] == 'd')
	{
		is_and = 1;
		i += 3;
	}
	else if (str[i] == 'o' && str[i + 1] == 'r')
	{
		is_and = 0;
		i += 2;
	}
	else
		listings_main_menu(data, filename, "AND , OR not found");
	q++;
	sub[q] = (char*)calloc(25, sizeof(char));
	for (j = 0; str[i] != '\0' && str[i] != '<' && str[i] != '>' && str[i] != '='; i++, j++)
		sub[q][j] = str[i];

	if (str[i] == '<')
		symbol[q] = 1;
	else if (str[i] == '>')
		symbol[q] = 2;
	else if (str[i] == '=')
		symbol[q] = 0;
	else
		symbol[q] = -1;
	i++;
	if (symbol[q] != -1)
		for (; str[i] != '\0'; i++)
			num[q] = num[q] * 10 + (str[i] - '0');
	else
	{
		listings_main_menu(data, filename, "Wrong operator used");
		return;
	}

	for (i = 0; i < no_of_subjects; i++)
		if (string_compare(sub[0], subjects[i]))
		{
			index[0] = i;
			break;
		}
	if (i == no_of_subjects)
		return listings_main_menu(data, filename, "Subject not found");
	
	for (i = 0; i < no_of_subjects; i++)
		if (string_compare(sub[1], subjects[i]))
		{
			index[1] = i;
			break;
		}
	if (i == no_of_subjects)
		return listings_main_menu(data, filename, "Subject not found");

	i = 1, j = 0;

	list_two_conditions(data, data[1], filename, &i, &j, &stop, no_of_subjects, index, symbol, num, is_and);
	if (stop == 0)
	{
		printf("\n\nList came to end\n\nSelect an option\n\n[1] Enter a student name to view his details\n[2] Go back\n[0] Exit\n\nEnter an option: ");
		scanf("%d", &choice);
		if (choice == 1)
			student_login(data, filename);
		else if (choice == 0)
			exit_prog(data, filename, no_of_subjects);
		else if (choice == 2)
			listings_main_menu(data, filename, NULL);
		else
			listings_main_menu(data, filename, "Wrong option was choosen");
	}
}

void listings_main_menu(struct node **data, char *filename, char *error_msg)
{
	int option, i = 1, j = 0, stop = 0, choice, no_of_subjects;
	char **subjects = subject_names(filename);
	FILE *p1 = fopen(filename, "r");
	fscanf(p1, "%d", &no_of_subjects);
	fclose(p1);
	system("cls");
	printf("Here you can view list of students on the following criteria\n\n");
	if (error_msg != NULL)
		printf("Error: %s", error_msg);
	printf("\n\n[1] View all students and his marks in alphabetical order\n");
	printf("[2] View leaderboard according to their total\n");
	printf("[3] View leaderboard according to a particular subject\n");
	printf("[4] View listings on one condition(e.g Physics > 60)\n");
	printf("[5] View listings on two conditions (e.g Physics < 60 and Maths < 50\n\n");
	printf("[9] Go back\n[0] Exit\n\nEnter your option: ");
	scanf("%d", &option);

	switch (option)
	{
	case 1:
		system("cls");
		printf("Viewing first 200 results at a time\n\n");
		for (i = 0; i < no_of_subjects; i++)
			printf("Subject-%d: %s\n", i + 1, subjects[i]);
		printf("\n\n");
		i = 1;
		list_alphabetical(data, data[0], filename, &i, &j, &stop, no_of_subjects);
		if (stop == 0)
		{
			printf("\n\nSelect an option\n\n[1] Enter a student name to view his details\n[2] Go back\n[0] Exit\n\nEnter an option: ");
			scanf("%d", &choice);
			if (choice == 1)
				student_login(data, filename);
			else if (choice == 0)
				exit_prog(data, filename, no_of_subjects);
			else if (choice == 2)
				listings_main_menu(data, filename, NULL);
			else
				listings_main_menu(data, filename, "Wrong option was choosen");
		}
		break;
	case 2:
		system("cls");
		printf("Viewing first 200 results at a time\n\n");
		list_total_marks(data, data[1], filename, &i, &j, &stop, no_of_subjects);
		if (stop == 0)
		{
			printf("\n\nSelect an option\n\n[1] Enter a student name to view his details\n[2] Go back\n[0] Exit\n\nEnter an option: ");
			scanf("%d", &choice);
			if (choice == 1)
				student_login(data, filename);
			else if (choice == 0)
				exit_prog(data, filename, no_of_subjects);
			else if (choice == 2)
				listings_main_menu(data, filename, NULL);
			else
				listings_main_menu(data, filename, "Wrong option was choosen");
		}
		break;
	case 3:
		system("cls");
		printf("Select a subject to view its leaderboard\n\n");
		for (i = 0; i < no_of_subjects; i++)
			printf("[%d] %s\n", i + 1, subjects[i]);
		printf("\n[0] Exit\n[-1] Go back\n\nEnter your option: ");
		scanf("%d", &option);
		switch (option)
		{
		case 0:
			exit_prog(data, filename, no_of_subjects);
			break;
		case -1:
			listings_main_menu(data, filename, NULL);
			break;
		default:
			if (option >= 1 && option <= no_of_subjects)
			{
				system("cls");
				printf("Viewing first 200 results\n\n");
				i = 1, j = 0;
				list_particular_subject(data, data[1 + option], filename, &i, &j, &stop, no_of_subjects, option - 1);
				if (stop == 0)
				{
					printf("\n\nSelect an option\n\n[1] Enter a student name to view his details\n[2] Go back\n[0] Exit\n\nEnter an option: ");
					scanf("%d", &choice);
					if (choice == 1)
						student_login(data, filename);
					else if (choice == 0)
						exit_prog(data, filename, no_of_subjects);
					else if (choice == 2)
						listings_main_menu(data, filename, NULL);
					else
						listings_main_menu(data, filename, "Wrong option was choosen");
				}
			}
			else
				listings_main_menu(data, filename, "Wrong option was choosen");
			break;
		}
		break;
	case 4:
		one_condition_leaderboard(data, filename,  no_of_subjects);
		break;
	case 5:
		two_condition_leaderboard(data, filename, no_of_subjects);
		break;
	case 9:
		main_menu(data, NULL, filename);
		break;
	case 0:
		exit_prog(data, filename, no_of_subjects);
		break;
	default:
		listings_main_menu(data, filename, "You have entered a Wrong option");
		break;
	}

}

void main_menu(struct node **data, char * error_msg, char *filename)
{
	int option, no_of_subjects;
	FILE *p1 = fopen(filename, "r");
	fscanf(p1, "%d", &no_of_subjects);
	fclose(p1);
	system("cls");
	printf("WELCOME TO STUDENT DATABASE\n\n");
	if (error_msg != NULL)
		printf("Error: %s\n\n", error_msg);
	else
		printf("\n\n");
	printf("[1] Student login\n[2] Administrator login\n[3] View Specific listings/Leaderboards/Conditional View\n[0] Exit\n\n");
	printf("Enter your option: ");
	scanf("%d", &option);
	switch (option)
	{
	case 0:
		exit_prog(data, filename, no_of_subjects);
		break;
	case 1:
		student_login(data, filename);
		break;
	case 2:
		admin_login(data, filename, NULL, 3);
		break;
	case 3:
		listings_main_menu(data, filename, NULL);
		break;
	default:
		main_menu(data, "You have Entered Wrong option. Please try again", filename);
		break;

	}
}

struct node * add_node_to_BST(struct node *root, int inorder_type, char *name, int *marks, int no_of_subjects)
{
	int i = 0, total, root_total;

	if (root == NULL)
	{
		struct node *temp = (struct node *)malloc(sizeof(struct node));
		temp->name = name;
		temp->scores = marks;
		temp->left = NULL;
		temp->right = NULL;
		return temp;
	}

	switch (inorder_type)
	{
	case -2:
		for (i = 0; name[i] == root->name[i]; i++);
		if (name[i] < root->name[i])
			root->left = add_node_to_BST(root->left, inorder_type, name, marks, no_of_subjects);
		else if (name[i] > root->name[i])
			root->right = add_node_to_BST(root->right, inorder_type, name, marks, no_of_subjects);
		break;

	case -1:
		total = total_marks(marks, no_of_subjects);
		root_total = total_marks(root->scores, no_of_subjects);
		if (total <= root_total)
			root->left = add_node_to_BST(root->left, inorder_type, name, marks, no_of_subjects);
		else if (total > root_total)
			root->right = add_node_to_BST(root->right, inorder_type, name, marks, no_of_subjects);
		break;

	default:
		if (inorder_type >= no_of_subjects)
			return NULL;
		if (marks[inorder_type] <= root->scores[inorder_type])
			root->left = add_node_to_BST(root->left, inorder_type, name, marks, no_of_subjects);
		else if (marks[inorder_type] > root->scores[inorder_type])
			root->right = add_node_to_BST(root->right, inorder_type, name, marks, no_of_subjects);
		break;
	}

	return root;
}

struct node** add_node_to_all_BSTs(struct node **data, char *name, int *marks, int no_of_subjects)
{
	int i;

	data[0] = add_node_to_BST(data[0], -2, name, marks, no_of_subjects);
	data[1] = add_node_to_BST(data[1], -1, name, marks, no_of_subjects);
	for (i = 0; i < no_of_subjects; i++)
		data[i + 2] = add_node_to_BST(data[i + 2], i, name, marks, no_of_subjects);

	return data;
}

struct node **retrieve_student_data(char * file_name)
{
	FILE *p1 = fopen(file_name, "r");
	int no_of_subjects, *marks;
	int i = 0, num = 0;
	struct node **data = NULL;
	char c, *name;

	printf("Loading Please wait...(Retrieveing data)");
	fscanf(p1, "%d", &no_of_subjects);
	data = (struct node **)calloc(no_of_subjects + 3, sizeof(struct node*));
	c = fgetc(p1);
	if (c != '\n')
		for (; c != '\n'; c = fgetc(p1));
	c = fgetc(p1);
	if (c != '\n')
		for (; c != '\n'; c = fgetc(p1));

	while (!feof(p1))
	{
		name = (char*)calloc(25, sizeof(char));
		fgets(name, 25, p1);
		name[string_length(name) - 1] = '\0';
		name = toLower(name);
		marks = (int*)calloc(no_of_subjects, sizeof(int));
		c = fgetc(p1);
		if (c >= '0' && c <= '9')
		{
			fseek(p1, -1, SEEK_CUR);
			for (i = 0; i < no_of_subjects - 1; i++)
				fscanf(p1, "%d,", &marks[i]);
			fscanf(p1, "%d", &marks[i]);
			c = fgetc(p1);
			data = add_node_to_all_BSTs(data, name, marks, no_of_subjects);
		}
		else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			fseek(p1, -1, SEEK_CUR);
			for (i = 0; i < no_of_subjects; i++)
				marks[i] = -1;
			data = add_node_to_all_BSTs(data, name, marks, no_of_subjects);
			data[no_of_subjects + 2] = add_node_to_BST(data[no_of_subjects + 2], -2, name, marks, no_of_subjects);
		}		
		num++;
	}
	fclose(p1);
	return data;
}

int main()
{
	char *filename = "student_data1.txt";
	struct node **data = retrieve_student_data(filename);
	main_menu(data, NULL, filename);
}
