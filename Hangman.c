#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#include<ctype.h>
#include "Select.h"

//MAXXX
#define clear() printf("\033[H\033[J")

char original_word[1000],dashed_word[1000],entered[1000],max_name[1000],user_name[1000];
int entered_count =-1,ps=0,max=0,maxx=0;
void checkmax(int score,int st){
	if(st==2){
    	FILE *max_file ;
	max_file = fopen(MAX_FILE,"r");
	char charscore[1000];
	fgets(max_name,sizeof(max_name),max_file);
	fgets(charscore,sizeof(charscore),max_file);
	maxx = atoi(charscore);
	}
	if(score>maxx && st==1){
	    FILE *p = fopen(MAX_FILE,"w");
	    fprintf(p,"%s\n%d",user_name,score);
	    fclose(p);
	    system("figlet New Highscore");
	    return;
	}
	else if (score>maxx && st!=1){
	    max = score;
	    strcpy(max_name,user_name);
	    strcat(max_name,"\n");
	    return;
	}
	else
	    max = maxx;
	
	return;



}
void displayman(int chance,int score){
	switch(chance){
		case 1:
		    printf("\n\n");
		    printf("\n         +-------+                                                     Highscore  %d by %s",max,max_name);
		    printf("         |       |");
		    printf("\n         |        ");
		    printf("\n         |        ");
		    printf("\n         |");
		    printf("\n         |");
		    printf("\n        /|\\\n\n");
		    break;
		case 2:
		    printf("\n\n");
		    printf("\n         +-------+                                                     Highscore  %d by %s",max,max_name);
		    printf("         |       |");
		    printf("\n         |       O");
		    printf("\n         |       |");
		    printf("\n         |");
		    printf("\n         |");
		    printf("\n        /|\\\n\n");
		    break;
		case 3:
		    printf("\n\n");
		    printf("\n         +-------+                                                     Highscore  %d by %s",max,max_name);
		    printf("         |       |");
		    printf("\n         |       O");
		    printf("\n         |      /|");
		    printf("\n         |        ");
		    printf("\n         |        ");
		    printf("\n        /|\\\n\n");
		    break;
		case 4:
		    printf("\n\n");
		    printf("\n         +-------+                                                     Highscore  %d by %s",max,max_name);
		    printf("         |       |");
		    printf("\n         |       O");
		    printf("\n         |      /|\\");
		    printf("\n         |        ");
		    printf("\n         |        ");
		    printf("\n        /|\\\n\n");
		    break;
		case 5:
		    printf("\n\n");
		    printf("\n         +-------+                                                     Highscore  %d by %s",max,max_name);
		    printf("         |       |");
		    printf("\n         |       O");
		    printf("\n         |      /|\\");
		    printf("\n         |       |");
		    printf("\n         |      /");
		    printf("\n         |        ");
		    printf("\n        /|\\\n\n");
		    break;
		case 6:
		    printf("\n\n");
		    printf("\n         +-------+                                                     Highscore  %d by %s",max,max_name);
		    printf("         |       |");
		    printf("\n         |       O");
		    printf("\n         |      /|\\");
		    printf("\n         |       |");
		    printf("\n         |      / \\");
		    printf("\n         |        ");
		    printf("\n        /|\\\n\n");
		    printf("\n\n\t You are hanged!!!\n");
		    printf("The word is %s\n",original_word);
	            checkmax(score,1);
		    exit(1);
		    break;
	
	
	}
}

void displaydash(){
	printf("\n\n");
	printf("Guess the word which looks like this\n");
	int ii = strlen(dashed_word)-1,i;
	for(i=0;i<=ii;i++)
	    printf("%c ",dashed_word[i]);
	printf("\n\n");
}

void displayinfo(int level,int score,int chance){
	printf("\nLevel:%d\n",level);
	printf("Total Score:%d\n",score);
	printf("You have %d chance left to guess\n",6-chance);
	
	
}

void displayenterd(){
	int i;
	printf("You already entered { ");
	for(i=0;i<=entered_count;i++){
	    printf("%c,",entered[i]);
	}
	printf(" } \n");
}
//select level based on cmd args
//return true if word is guessed
bool isguessed(){
	int i;
	for(i=0;i<strlen(dashed_word);i++)
	    if(dashed_word[i]=='_')
		return false;
	return true;
}
//clear screen and print greetings on terminal
void printgreetings(){
	clear();
	printf("Welcome to Hangman 2.0 \n");
}
void createdashedword(char orig_word[],int level){
	int len = strlen(orig_word) -1;
	int i;
	for(i =0;i<=len;i++)
	    dashed_word[i] = '_';
	dashed_word[i]='\0';
	
}
//select random word depending on level
void selectword(int level){
	FILE *pipe;
	char cmd[1000],*comd;
	strcpy(cmd,"shuf -n 1 ");
	comd = getcmd(cmd,level);
	
	pipe = popen(comd,"r");
	if(pipe==NULL){
	    printf("Error running shuf command \n");
	    exit(1);
	}
	else{
	    fscanf(pipe,"%[^\n]", original_word);//assign random word selected to original word
	    createdashedword(original_word,level);//initialize dashed word
	}
}
int notentered(char c){
	int i;
	for(i=0;i<=entered_count;i++)
	    if(entered[i]==c)
		return 0;
	return 1;
}
int update_dashed_word(char c,int chance){
	int len=strlen(original_word)-1,i,j=0;
	for(i=0;i<=len;i++){
		if(dashed_word[i]=='_' && original_word[i]==c && notentered(c)){
		    dashed_word[i]= c;
		    j=1;
		}

	}
	if(j)
	    return chance;
	else {
	    if(notentered(c))
	    	chance = chance+1;
	    return chance;
	}
}
//startgame recursively depending on score
void startgame(int level,int score,int chance){
	if(chance==-1){
		selectword(level);
		startgame(level,score,1);
		return;
	}
	else if(chance>0 && chance<7 ){
	    if(!isguessed()){
	   	char enterd_char;
		printgreetings();
		//printf("%s\n",original_word);//to hack
		displayman(chance,score);
		displayinfo(level,score,chance);
		displayenterd();
		displaydash();
		printf("Enter a character :  ");
	    	scanf(" %c",&enterd_char);
		enterd_char = toupper(enterd_char);
		chance = update_dashed_word(enterd_char,chance);
		if(notentered(enterd_char))
		    entered[++entered_count] = enterd_char;
	        printf("%d\t%s\n",chance,dashed_word);
		clear();
	    	startgame(level,score,chance);
		return;
	    }
	    else{
		clear();
		
		printf("Word is %s\n" , original_word);
		system("figlet You Have Won");
		system("sleep 1");
		entered_count =-1;
		if(score > ps+20){
		    ps = score;
		    score = score+10;
		    checkmax(score,0);
		    startgame(change_level(level),(score),-1);
		}
		chance = -1;
		score=score+10;
		checkmax(score,0);
		startgame(level,score,chance);
	    }
	}
}
int main(int argc,char *argv[]){
    int level,score =0;
    printf("Enter your name :");
    scanf("%s",user_name);
    checkmax(score,2);
    level = selectlevel(argc,argv);
    startgame(level,score,-1);
    return 0;
    
}

