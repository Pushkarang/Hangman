#define MAX_LEVEL 3
#define DEF "/home/wolfie/Hangman/Hangman/cities.txt"
#define city "/home/wolfie/Hangman/Hangman/cities.txt"
#define word "/home/wolfie/Hangman/Hangman/words.txt"
#define animal "/home/wolfie/Hangman/Hangman/animals.txt"
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
       else if(strcmp(argv[1],"-word")==0)
            level=2;
       else if(strcmp(argv[1],"-animal")==0)
            level=3;
//CHANGE3
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
        case 2:
            c = strcat(cmd,word);
           break;
        case 3:
            c = strcat(cmd,animal);
           break;
//SWITCH3
	default:
	    c = strcat(cmd,DEF);
	    break;
    }
    return c;
}
