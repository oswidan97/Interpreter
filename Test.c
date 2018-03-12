/*
 ============================================================================
 Name        : Test.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<strings.h>
#include<string.h>
#include <ctype.h>
#define maxSize 50
typedef struct Node {
    char key[20];
    double value;
    struct Node *next;


} Node;
typedef struct List {
    Node *head;
    Node *tail;
} List;
typedef struct
{
    int items[maxSize];
    int top;
} stack;


int precedence(char c)
{
    switch (c)
    {
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        case '(':
            return 0;
    }

}
Node *CreateNode(char key[], double value);

void InitializeList(List *list);

void AddHead(List *list, char key[], double value);

void DisplayList(List *list);
double Search(List *list, char key[]);
int IsOperator(char c);
void Push(stack *s,int x);
int pop(stack *s);
int top(stack *s);
int IsEmpty(stack *s);
int evaluatePosFix(char post[]);
void infixTopostfix(char infix[], char postfix[]);
void SecExpTokinizer(char x[], char z[], double arr1[]);
void InfixPosFixConvertor(char infix[],char postFix[]);




int main() {
    char x[50], z[20];
    //double arr1[20];
    scanf("%s",x);
    //SecExpTokinizer(x,z,arr1);
    InfixPosFixConvertor(x,z);


    return 0;
}

void InitializeList(List *list) {
    list->head = NULL;
    list->tail = NULL;
}

Node *CreateNode(char key[], double value) {

    Node *NewNode = (Node *) malloc(sizeof(Node));
    strcpy(NewNode->key, key);
    NewNode->value = value;
    NewNode->next = NULL;
    return NewNode;

}

void AddHead(List *list, char key[], double value) {

    Node *NewNode = CreateNode(key, value);
    NewNode->next = list->head;
    list->head = NewNode;
    if (list->tail == NULL)
        list->tail = NewNode;

}

void DisplayList(List *list) {
    Node *temp = list->head;
    while (temp) {
        printf("%s : %lf", temp->key, temp->value);
        temp = temp->next;

    }


}

double Search(List *list, char key[]) {
    Node *temp = list->head;
    while (temp) {
        if (strcmp(temp->key, key) == 0) {

            return temp->value;
        }
        temp = temp->next;
    }
    return 0;

}

int ValFirstExp(char exp[]) {
    int i = 0;

    if (isdigit(exp[0]))
        return 0;
    while (exp[i] != '\0') {
        if (exp[i] == '+' || exp[i] == '*' || exp[i] == '-' || exp[i] == '/') {

            return 0;
        }
        i++;
    }
    return 1;

}

int ValSecondExp(double Arr1[], char Arr2[]) {


}

int IsOperator(char c) {
    if (c == '+' || c == '*' || c == '-' || c == '/' || c == '(' || c == ')')
        return 1;
    return 0;


}
void Initialize(stack *s)
{

    s->top=0;
}
void Push(stack *s,int x)
{
    s->items[s->top]=x;
    s->top++;

}
int pop(stack *s)
{
    s->top--;
    return s->items[s->top];
}
int top(stack *s)
{
    return s->items[s->top-1];
}
int IsEmpty(stack *s)
{
    if(s->top==0)
        return 1;
    return 0;

}
int evaluatePosFix(char post[])
{

    stack s;
    Initialize(&s);
    int i;
    int x,y;
    int r=0;


    for(i=0;i<strlen(post);i++)
    {

        if(isdigit(post[i]))
            Push(&s,post[i]-'0');
        else
        {
            x=pop(&s);
            y=pop(&s);

            switch (post[i])
            {

                case '+':
                    r=y+x;
                    break;

                case '-':
                    r=y-x;
                    break;

                case '*':
                    r=y*x;
                    break;
                case '/':
                    r=y/x;
                    break;


            }
            Push(&s,r);

        }

    }
    return r;



}
void infixTopostfix(char infix[], char postfix[])
{
    stack s;
    Initialize(&s);
    int i=0,j=0;
    while(infix[i]!='\0')
    {


        if(isdigit(infix[i]))
        {
            postfix[j]=infix[i];
            j++;
        }

        else if(IsEmpty(&s)||infix[i]=='(')
        {Push(&s,infix[i]-'0');
        }
        else if(infix[i]==')')
        {
            while(top(&s)!='('-'0')
            {


                postfix[j]=pop(&s)+'0';
                j++;

            }
            pop(&s);
        }
        else if(precedence(infix[i])>=precedence(top(&s)+'0'))
        {
            Push(&s,infix[i]-'0');
        }
        else
        {
            while(!IsEmpty(&s))
            {
                postfix[j]=pop(&s)+'0';
                j++;
            }
            Push(&s,infix[i]-'0');
        }
        i++;
    }
    while(!IsEmpty(&s))
    {
        if(top(&s)+'0'=='(')
            pop(&s);
        else postfix[j]=pop(&s)+'0';
        j++;
    }
}
void SecExpTokinizer(char x[], char z[], double arr1[]) {
    int i = 0, j = 0, k = 0, l;
    int index = 0;


    char y[200];
    while (x[i] != '\0') {   //y=(char*)malloc(200);
        j = 0;
        if (IsOperator(x[i])) {
            z[k] = x[i];
            //  printf("%c\n",z[k]);
            k++;
        } else {
            while (!IsOperator(x[i])) {
                y[j] = x[i];
                i++;
                j++;
            }
            y[j] = '\0';
            arr1[index] = atof(y);

            /* for(l=0;l<200;l++)
                 y[l]='\0';*/
            //free(y);
            index++;
            continue;
        }
        i++;


    }
    z[k] = '\0';

    printf("%s", z);
    for (i = 0; i < 5; i++)
        printf("\n%lf", arr1[i]);

}
void InfixPosFixConvertor(char infix[],char postFix[])
{
	stack s;
	Initialize(&s);
	int i=0,j=0;
	 while(infix[i]!='\0')
	 {
		 if(!IsOperator(infix[i])){
			 while(!IsOperator(infix[i]))
			 	 {
				 	 printf("%c",infix[i]);
				 	 i++;

			 	 }
			 printf(" ");

		 }

		 else if(IsEmpty(&s)||infix[i]=='(')
		         {
			 	 	 Push(&s,infix[i]-'0');
		         }
		 else if(infix[i]==')')
		         {
		             while(top(&s)!='('-'0')
		             {

		            	 printf("%c",pop(&s)+'0');
		                 //postfix[j]=pop(&s)+'0';
		                // j++;

		             }
		             pop(&s);
		         }
		 else if(precedence(infix[i])>=precedence(top(&s)+'0'))
		         {
		             Push(&s,infix[i]-'0');
		         }
		         else
		         {
		             while(!IsEmpty(&s))
		             {
		                 //postfix[j]=pop(&s)+'0';
		                // j++;
		            	 printf("%c",pop(&s)+'0');
		             }
		             Push(&s,infix[i]-'0');
		         }
		         i++;
		     }

	 while(!IsEmpty(&s))
	     {
	         if(top(&s)+'0'=='(')
	             pop(&s);
	         else {

	        	 printf("%c",pop(&s)+'0');
	        	// postfix[j]=pop(&s)+'0';
	        	 //j++;
	         }
	     }


}








