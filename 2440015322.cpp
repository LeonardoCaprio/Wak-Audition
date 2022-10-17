#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct tree{
	char name[100];
	char gender[100];
	int age;
	char song[100];
	int height;
	tree* left;
	tree* right;
};

tree* createRoot(char name[100], char gender[100], int age, char song[100]){
	tree* newRoot = (tree*) malloc (sizeof(tree));
	strcpy(newRoot->name, name);
	strcpy(newRoot->gender,gender);
	newRoot->age = age;
	strcpy(newRoot->song,song);
	newRoot->left = newRoot->right= NULL;
	newRoot->height = 1;
	return newRoot;
}

int max(int a, int b){
	return a > b ? a : b;
}

int getHeight(tree* root){
	if(root == NULL){  
		return 0;
	}
	return root->height;
}

int getBalanceFactor(tree* root){
	return getHeight(root->left) - getHeight(root->right);
}

void update(tree* root){
	root->height = max(getHeight(root->left), getHeight(root->right))+1;
}

tree *rotateRight(tree *root){
	tree *x = root->left;
	tree *t2 = x->right;
	
	x->right = root ;
	root->left = t2;
	
	update(root);
	update(x);
	
	return x;	
}

tree *rotateLeft(tree *root){
	tree *y = root->right;
	tree *t2 = y->left;
	
	y->left = root ;
	root->right = t2;
	
	update(root);
	update(y);
	return y;
}

tree* rebalance(tree* root){
	int bf = getBalanceFactor(root);
	
	if(bf < -1){
		if(getBalanceFactor(root->right) > 0){
			root->right = rotateRight(root->right);
		}
		root = rotateLeft(root);
	}
	else if(bf > 1){
		if(getBalanceFactor(root->left) < 0){
			root->left = rotateLeft(root->left);
		}
		root = rotateRight(root);
	}
	return root;
}

tree* search(tree* root, char name[100]){
	if(!root){
		return NULL;
	} 
	
	if(strcmp(name, root->name) < 0){
		return search(root->left, name);
	}
	else if(strcmp(name, root->name) > 0){
		return search(root->right, name);
	}
	else{
		return root;
	}
}


tree* push(tree* root,char name[100], char gender[100], int age, char song[100]){
	if(root == NULL){
		return createRoot(name, gender, age, song);
	} 
	
	if(strcmp(name, root->name) < 0){
		root->left = push(root->left, name, gender, age, song);
	}
	else if(strcmp(name, name) > 0){
		root->right = push(root->right, name, gender, age, song);
	}
	update(root);
	return rebalance(root);
}

bool validname(tree* root, char name[100]){
	if(strlen(name) < 2){
 		return false;
	}
	for (int i=0; i<strlen(name); i++){
		if(islower(name[i]) || isupper(name[i])){
			return true;	
		}
 	}
 	
	if(search(root, name)){
		return true;
	} 
	return false;
}

tree* registered(tree* root){
	char name[100];
	char gender[100];
	int age;
	char song[100];
	
	do{
		printf("Input Product Name (Must 2 Word(6-20)): ");
		scanf("%[^\n]", name);
		getchar();
	}while(!validname(root, name));
	
	do{
		printf("Input Your Gender (Female||Male): ");
		scanf("%s", gender);
		getchar();
	}while(strcmp(gender,"Female")!=0 && strcmp(gender,"Male")!=0);
	
	do{
		printf("Input Your Age (6-59): ");
		scanf("%s", age);
		getchar();
	}while(age <= 6 || age >= 59);
	
	do{
		printf("Input Song: ");
		scanf("%[^\n]", song);
		getchar();	
	}while(strlen(song)<0);

	root = push(root, name,gender,age,song);
	printf("Insert Success");
	return root;
}

void inOrder(tree* root){
	if(root == NULL){
		return;
	}
	
	inOrder(root->left);
	printf("%s - %s - %d - %d\n", root->name, root->gender, root->age, root->song);
	inOrder(root->right);
}

void preOrder(tree* root){
	if(root == NULL){
		return;
	}
	printf("%s - %s - %d - %s\n", root->name, root->gender, root->age, root->song);
	preOrder(root->left);
	preOrder(root->right);
}

void postOrder(tree* root){
	if(root == NULL){
		return ;
	}
	postOrder(root->left);
	postOrder(root->right);
	printf("%s - %s - %d - %s\n", root->name, root->gender, root->age, root->song);
}

void viewAudition(tree* root){
	if(root == NULL){
		puts("There is no Contestant\n");
		return ;
	}
	
	char pilih[10];
	do{
		puts("Choose Oder [Pre|In|Post]: ");
		scanf("%s",&pilih);
		getchar();
		if(strcmp(pilih,"Pre")){
			preOrder(root);
		}
		else if(strcmp(pilih,"In")){
			inOrder(root);
		}
		else if(strcmp(pilih,"Post")){
			postOrder(root);
		}
	}while(strcmp(pilih,"Pre")!=0 && strcmp(pilih,"In")!=0 && strcmp(pilih,"Post")!=0);
}

tree* findkey(tree* root){
	while(root->right){
		root = root->right;
 	}
 	return root;
}

tree* pop(tree* root, char name[100]){
	if(root == NULL){
		return NULL;
	}
	
	if(strcmp(name, root->name) < 0){
		root->left = pop(root->left, name);
	}
	else if(strcmp(name, root->name) > 0){
		root->right = pop(root->right, name);
	}
	else{
		if(!root->left && !root->right){
			root = NULL;
			free(root);
			return NULL;
		}
		else if(!root->left){
			tree* child = root->right;
			root = NULL;
			free(root);
			return child;
		}
		else if(!root->right){
			tree* child = root->left;
			root = NULL;
			free(root);
			return child;
		}
		else{
			tree* find = findkey(root);
			strcpy(root->name, find->name);
			strcpy(root->gender, find->gender);
			root->age = find->age;
			strcpy(root->song, find->song);
			
			root->left = pop(root->left, find->name);			
		}
	}
}

tree* call(tree* root){
	if(root==NULL){
		printf("There is no contestant\n");
		return NULL;
	}
 	
	char name[100];
	tree* find = NULL;
 
 	viewAudition(root);
 
 	do{
  		printf("Enter Contestant Name : ");
  		scanf("%[^\n]", name);
  		getchar();
  		find = search(root, name);
 	}while(!find);
 	return pop(root, name);
}

int main(){
int choose = 0;
	tree* root = NULL;
	do{
		puts("  WAK-Audition");
		puts("1. View Contestant");
		puts("2. Register Contestant");
		puts("3. Call Contestant");
		puts("4. End Audition");
		printf(">> ");
		scanf("%d", &choose);
		getchar();
		switch(choose){
			case 1:{
				system("cls");
				viewAudition(root);
				break;
			}
			case 2:{
				system("cls");
				root = registered(root);
				break;
			}
			case 3:{
				system("cls");
				root = call(root);
				break;
			}
			
		}
	}while(choose!=4);
	return 0;
}
