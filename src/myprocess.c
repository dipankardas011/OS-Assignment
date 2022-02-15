#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char **argv){

	int i,a[2]={0};

	printf(1, "Parent: %d %d\n",getpid(),getpid());
	for(i=0;i<2;i++){
		a[i]=fork();
		if(a[i]==0){
				printf(1, "Child: %d %d\n",a[i],getpid());
			break;
		}else{
			printf(1, "parent: %d %d\n",a[i],getpid());
		}
	}
	int c = waitpid(a[1]);
	printf(1, "WAIT : %d %d\n",c,getpid());
	exit();

}

