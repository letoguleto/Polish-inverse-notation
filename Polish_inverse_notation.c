#include"stdio.h"
#include"stdlib.h"
char* changeBuffer( char*,int);
int findSize(char*);
int prior(char);
int main(int argc,char* argv[]){
    char *startStr = argv[1];
    //startStr = changeBuffer(startStr,atoi(argv[2]));
    char polishList[255];
    char *polish = polishList;int j = 0;
    char stack[255];char *s = stack;int k = 0;
    for(int i = 0;startStr[i] != '\0';i++){
        k = findSize(stack);
        if ((int)startStr[i] >= 48 && (int)startStr[i] <= 58) {
            polish[j] = startStr[i];j++;
            continue;
        }
        else
        {stack[k] = startStr[i];}
        //printf("k %d\n",k);

        while (k>=1){
            if ((char)stack[k] == '(' || (char)stack[k-1] == '(') { break;}
            if ((char)stack[k] == ')'){
                //printf("scobe %s\n",stack);
                changeBuffer(stack,k+1);
                //printf("scobe end %s\n",stack);
                k--;
                while((char)stack[k] != '('){
                    polish[j] = stack[k];
                    //printf("polish %s   %s\n",polish,stack);
                    j++;
                    changeBuffer(stack,k+1);k--;
                }
                //printf("stack start %s\n",stack);
                if ((char)stack[k] == '(') changeBuffer(stack,k+1);
                //printf("stack end %s\n",stack);
            }
            //printf("priority %c   %c\n",stack[k-1],stack[k]);
            else if ((prior(stack[k-1])>=prior(stack[k]))){
                polish[j] = stack[k-1];j++;
                //printf("%d %c %c\n",k,stack[k-1],stack[k]);
                //printf("%s\n",stack);
                changeBuffer(stack,k);k--;
                //printf("%s\n",stack);
            }
            else break;
        }
    }
    k = findSize(stack);
    if ( k > 0){
        for(int i = k-1;i >= 0;i--){
            if (stack[i] != 40 && stack[i] != 41) {
                polish[j] = stack[i];
                j++;
            }
        }
    }
    printf("%s   %s\n",polish,stack);
    return 0;
}

char* changeBuffer( char* str,int rm){
    int size = findSize(str);
    if (size < rm) return 0;
    if (size == 1)  {str[0] = '\0';return str;}
    char temp[size];
    for(int i = 0;str[i] != '\0';i++ ){
        temp[i] = str[i];
        //printf("%c\n",temp[i]);
    }
    int j = 0;
    for(int i = 0;i < size-1;i++){
        //if(i == size-1){str[i] = '\0';break;}
        if (i == rm - 1) j++;
        str[i] = temp[j];
        str[i+1] = '\0';
        j++;
    }
    return str;
}

int findSize(char* str){
    int i = 0;
    while ((char)str[i] != '\0'){
        i++;
    }
    return i;
}
int prior(char x){
    if (x == '+' || x == '-') return 0;
    else if (x == '*' || x == '/') return 1;
    else if (x == '(' || x == ')') return -1;
}