#define MAX_LEVEL 1
//DEFINE
int selectlevel(int argc,char *argv[]){
    int level;
    if(argc>2){
    	printf("Syntax Error!\n Hangman [level]\n");
	exit(1);
    }
    else if(argc>1){
	if(strcmp(argv[1],"-city")==0)
	    level =1;
//CHANGE1
	else
	    level=100;
    }
    else
	level=1;
    return level;

}

int change_level(int level){
    if(level<MAX_LEVEL){
	return (level+1);
    }
    else 
	return level;
}

char* getcmd(char *cmd,int level){
    char *c;
    switch(level){
	case 1:
	    c= strcat(cmd,city);
	    break;
//SWITCH1
	default:
	    c = strcat(cmd,DEF);
	    break;
    }
    return c;
}
