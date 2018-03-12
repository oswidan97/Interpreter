
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<strings.h>
#include<string.h>
#include <ctype.h>
#include <regex.h>

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
typedef struct {
    char items[maxSize];
    int top;
} stack;
typedef struct {
    double items[maxSize];
    int top;
} DoubleStack;


int precedence(char c) {
    switch (c) {
        case '*':
        case '/':
        case '%':
            return 2;
        case '+':
        case '-':
            return 1;
        case '(':
            //case ')':
            return 0;
    }

}


Node *CreateNode(char key[], double value);

void InitializeList(List *list);

void AddHead(List *list, char key[], double value);

void DisplayList(List *list);

Node* Search(List *list, char key[]);

int IsOperator(char c);

void Initialize(stack *s);

void Push(stack *s, char x);

char pop(stack *s);

char top(stack *s);

int IsEmpty(stack *s);


void InitializeDoubleStack(DoubleStack *s);

void DoubleStackPush(DoubleStack *s, double x);

double DoubleStackPop(DoubleStack *s);

double DoubleStackTop(DoubleStack *s);

int IsDoubleStackEmpty(DoubleStack *s);


int evaluatePosFix(char post[]);

void infixTopostfix(char infix[], char postfix[]);

void SecExpTokinizer(char x[], char z[], double arr1[]);

void infixTopostfix(char infix[], char postfix[]);

double PostFixEvaluation(char postfix[],List *l);
int ValFirstExp(char exp[]);
int Tokinizer(char exp[],char key[],char infix[]);
int secExpValidator(char x[]);
int main() {

    char *infix, postfix[200] = {0};
    char *key,exp[100];
    List l;
    InitializeList(&l);
    regex_t regex;
    regcomp(&regex,"[a-z]*=\.",0);
    while (1) {
        //double arr1[20];
        fflush(stdout);
        printf("Enter an Expression or \"end\" to exit->  ");
        scanf("%s",exp);
       if (!strcmp(exp,"end"))
            break;
        getc(stdin);
       int reti= regexec(&regex, exp, 0, NULL, 0);
        if( reti ){
            printf("not valid\n");
            continue;
        }
        key=strtok(exp,"=");
        infix=strtok(NULL,"\0");
        if (!ValFirstExp(key))
        {
            printf("not valid\n");
            continue;
        }
        if (!secExpValidator(infix))
            continue;

        /*printf("%s\n",infix);
        printf("%s\n",key);*/
        infixTopostfix(infix, postfix);
       // printf("%s",postfix);
        double hamada = PostFixEvaluation(postfix, &l);
        printf("exp= %lf\n", hamada);

        Node*  node=Search(&l,key);
        if(node!=NULL)
        {
            node->value=hamada;
        }
        else {

            AddHead(&l, key, hamada);
        }
        //DisplayList(&l);
    }
    return 0;
}
int Tokinizer(char exp[],char key[],char infix[]){
   int i=0;
    //printf("%s",exp);
    while (exp[i]!='=')
        i++;

    strncpy(key,exp,i);

   // key[i]='\0';

    i++;
    while (i<strlen(exp))
    {

        infix[i]=exp[i];
        //printf("%c",infix[i]);
        i++;
    }


    //infix[i]='\0';

    printf("%s\t%s",key,infix);
    return 1;

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
        printf("%s : %lf\t", temp->key, temp->value);
        temp = temp->next;

    }


}

Node * Search(List *list, char string[]) {
    Node *temp = list->head;
    while (temp) {
        if (strcmp(temp->key, string) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;

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


            for (l = 0; l < 200; l++)
                y[l] = '\0';

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

int IsOperator(char c) {
    if (c == '+' || c == '*' || c == '-' || c == '/' || c == '(' || c == ')')
        return 1;
    return 0;


}

void Initialize(stack *s) {

    s->top = 0;
}

void Push(stack *s, char x) {
    s->items[s->top] = x;
    (s->top)++;

}

char pop(stack *s) {


    (s->top)--;
    return s->items[s->top];
}

char top(stack *s) {
    return s->items[s->top - 1];
}

int IsEmpty(stack *s) {
    if (s->top == 0)
        return 1;
    return 0;

}

int evaluatePosFix(char post[]) {

    stack s;
    Initialize(&s);
    int i;
    int x, y;
    int r = 0;


    for (i = 0; i < strlen(post); i++) {

        if (isdigit(post[i]))
            Push(&s, post[i] - '0');
        else {
            x = pop(&s);
            y = pop(&s);

            switch (post[i]) {

                case '+':
                    r = y + x;
                    break;

                case '-':
                    r = y - x;
                    break;

                case '*':
                    r = y * x;
                    break;
                case '/':
                    r = y / x;
                    break;


            }
            Push(&s, r);

        }

    }
    return r;


}

void infixTopostfix(char infix[], char postfix[]) {
    stack s;
    Initialize(&s);
    int i = 0, j = 0;

    while (infix[i] != '\0') {


        if (infix[i] != '+' && infix[i] != '*' && infix[i] != '-' && infix[i] != '/' && infix[i] != '%' &&
            infix[i] != '(' && infix[i] != ')') {
            while (infix[i] != '\0' && infix[i] != '+' && infix[i] != '*' && infix[i] != '-' && infix[i] != '/' &&
                   infix[i] != '%' && infix[i] != '(' && infix[i] != ')') {

                postfix[j] = infix[i];
                j++;
                i++;

            }
            postfix[j] = ' ';
            j++;
        } else if (IsEmpty(&s) || infix[i] == '(') {
            Push(&s, infix[i]);
            i++;
        } else if (infix[i] == ')') {
            while (top(&s) != '(') {

                // printf("%c",pop(&s));
                postfix[j] = pop(&s);
                j++;

            }
            pop(&s);
            i++;
        } else if (precedence(infix[i]) >precedence(top(&s))) {
            Push(&s, infix[i]);
            i++;
        } else {
            while (!IsEmpty(&s)) {
                /*if(precedence(infix[i])>=precedence(top(&s)))
                    break;*/
                //printf("%c",pop(&s));
                postfix[j] = pop(&s);
                j++;
            }
            Push(&s, infix[i]);
            i++;
        }

    }


    while (!IsEmpty(&s)) {
        char c=top(&s);
        int x=s.top;
        printf("%c\n",top(&s));
        if(top(&s)=='(')
             pop(&s);
        else
             postfix[j] = pop(&s);
        j++;

    }
    postfix[j] = '\0';

}

void InitializeDoubleStack(DoubleStack *s) {

    s->top = 0;
}

void DoubleStackPush(DoubleStack *s, double x) {
    s->items[s->top] = x;
    s->top++;

}

double DoubleStackPop(DoubleStack *s) {

    s->top--;
    return s->items[s->top];
}

double DoubleStackTop(DoubleStack *s) {
    return s->items[s->top - 1];
}

int IsDoubleStackEmpty(DoubleStack *s) {
    if (s->top == 0)
        return 1;
    return 0;

}


double PostFixEvaluation(char postfix[],List *l) {

    DoubleStack s;
    InitializeDoubleStack(&s);
    double x, y, sum = 0;
    int i = 0, j;
    char temp[50] = {'\0'};
    while (postfix[i] != '\0') {
        j = 0;
        if (postfix[i] != '+' && postfix[i] != '*' && postfix[i] != '-' && postfix[i] != '/' && postfix[i] != '%') {

            while (postfix[i] != ' ' && postfix[i] != '\0') {

                temp[j] = postfix[i];
                i++;
                j++;

            }
            temp[j] = '\0';
            i++;
            if (!isdigit(temp[0])) {
                Node* m=Search(l, temp);
               // printf("temp=%lf",m);
                if(m!=NULL)
                    DoubleStackPush(&s,m->value);
                else {
                    printf("syntax error\n");
                    break;
                }

            }
           else {
                int k=1;
                int flag=1;
                while(temp[k]!='\0')
                {
                    if(!isdigit(temp[k])&&temp[k]!='.')
                    {
                        printf("syntax error\n");
                        flag=0;
                        break;
                    }
                    k++;

                }
                if(!flag)
                    break;
                DoubleStackPush(&s, atof(temp));


            }
        } else {
            x = DoubleStackPop(&s);
            y = DoubleStackPop(&s);

            switch (postfix[i]) {

                case '+':
                    sum = y + x;
                    break;

                case '-':
                    sum = y - x;
                    break;

                case '*':
                    sum = y * x;
                    break;
                case '/':
                    sum = y / x;
                    break;


            }
            DoubleStackPush(&s, sum);
            i++;

        }


    }


    return DoubleStackPop(&s);

}

int secExpValidator(char x[])
{
    int i=0;
    int count=0;
    if(strlen(x)==0)
    {
        printf("Syntax error1");
        return 0;
    }
    if(x[0]=='/'||x[0]=='*')
    {
        printf("Syntax error2");
        return 0;
    }
    while(x[i]!='\0'&&count>=0)
    {
        if(i>0)
        {
            if(x[i]=='('&&!IsOperator(x[i-1]))
            {
                printf("Syntax error3");
                return 0;
            }
            else if(x[i]=='*'&&x[i-1]=='*')
            {
                printf("Syntax error4");
                return 0;
            }
            else if(x[i]=='/'&&x[i-1]=='/')
            {
                printf("Syntax error5");
                return 0;
            }
        }

        if(x[i]=='=')
        {
            printf("Syntax error");
            return 0;
        }
        if(x[i]=='(')
            count++;
        else if(x[i]==')')
            count--;
        i++;
    }
    if(count!=0)
    {
        printf("Syntax error");
        return 0;

    }
    return 1;
}





