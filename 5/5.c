#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define false 0;
#define true 1;

FILE *file;
FILE *fout;
int  numberOfStates = 0;
int  flag = 0;
int  states[20];
int start_states[10];
int final_states[20];
int inFinal[130];
int no_of_final = 0;
int no_of_inputs = 0;
int no_of_starts = 0;
int *FINAL_STATES[10];
int NO_OF_FINAL = 0;
int inputs[10];

char a[150];

int  transitions[10][5][5];
int transitionPresent = 0;
int Q[10][5];
int j = 0;
int i = 0;
int k = 0;
int n = 0;
int ex = 0;
int indx = 0;
int map[10];


void LookUp(int *set,int input)
{
	transitionPresent = 0;

	fprintf(fout,"({");
	for(i = 0; set[i] != -1; i++){
		int initial = set[i];
		for(j = 0; j < 5; j++){
			ex = transitions[initial+1][input+1][j];
			if(ex != 232){
				map[ex] = 1;
				transitionPresent = 1;
			}
		}
		if(set[i+1] != -1)
			fprintf(fout,"q%d,",set[i]);
		else
			fprintf(fout,"q%d",set[i]);
	}
	fprintf(fout,"}");
	fprintf(fout,",%d) = ",input);
	for(i = 0; i < 10; i++)
		if(map[i] != 0)
			fprintf(fout,"q%d ",i);
	
	fprintf(fout,"\n");
}

void Read()
{
	file = fopen("input.txt","r");  
	fout = fopen("output.txt","w"); 
	int i = 0;     
	if (file == NULL ) {
		perror("fopen");
	
	}
	else if (fout == NULL ) {
		perror("fopen");
		
	}
	printf("Reading...\n");

	while(!feof(file))
	{
		fscanf(file,"%s",a);
		if(strcmp("//states",a) == 0)
			flag = 1;
		else if(strcmp("//input_symbols",a) == 0)
		{	
			fscanf(file,"%s",a);
			while(a[0] != '/')
			{	
				inputs[no_of_inputs++] = a[0] - '0';
				fscanf(file,"%s",a);
			}
			flag = 0;
		}
		if(strcmp("//start_state",a) == 0)
		{	
			fscanf(file,"%s",a);
			while(a[0] != '/')
			{	
				if(a[1] >= '0' && a[1] <= '9'){					
					start_states[no_of_starts++] = a[1] - '0';
				}
				else{
					start_states[no_of_starts++] = a[1];		
				}
				fscanf(file,"%s",a);
			}
			flag = 0;
		}
		if(strcmp("//final_state",a) == 0)
		{
			fscanf(file,"%s",a);
			while(a[0] != '/')
			{
				if(a[1] >= '0' && a[1] <= '9'){					
					final_states[no_of_final++] = a[1] - '0';
					inFinal[a[1] - '0'] = 1;
				}
				else{
					final_states[no_of_final++] = a[1];			
					inFinal[a[1] - '0'] = 1;
				}
				fscanf(file,"%s",a);
			}
			break;
		}
		if (flag == 1 && a[0] != '/')
		{
			if(a[1] >= '0' && a[1] <= '9')     			
				states[i++] = a[1] - '0';
			else							
				states[i++] = a[1];
		}
		numberOfStates = i;	
	}
	
	
	printf("\nStates : \n");
	for(i = 0; i < numberOfStates; i++)
	{	
		if(states[i] < 97)
			printf("q%d\n",states[i]);
		else
			printf("q%c\n",states[i]);
	}
	
    for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 5; j++)
		{ 
			for(int k = 0; k < 5; k++)
			transitions[i][j][k] = 232;
		}
	}
	for(i = 1; i <= no_of_inputs; i++)   				
		transitions[0][i][0] = inputs[i-1];
	
	while(!feof(file))
	{
		fgets(a,100,file);
        	n = 1;
        	for(i = 5; i < 50; i++){   					
            		if(a[i] == ',')
                	n++;
        	}
		if(a[0] == 'q')
		{	
			for(j = 1; j <= no_of_inputs; j++)  			
			{	
				if(transitions[0][j][0] ==  a[3] - '0')
					break;
			}
           	 	i = 0;
           	 	while(n > 0){
				transitions[(a[1] - '0') + 1][j][i] = a[6 + (i * 3)] - '0';
                		i++;
				n--;
            		}
           	 	transitions[(a[1] - '0') + 1][0][0] = a[1] - '0'; 	
		}
	}
	
	for(i = 0; i < numberOfStates; i++ )  					
	{	
		if(transitions[i][0][0] == 232)
			transitions[i][0][0] = states[i-1];
	}
	printf("\nTransitions read\n");
}

void ClearMap()
{
	for(i = 0; i < 10; i++)
		map[i] = 0;
}

int EqualTo(int *map2)
{
	for(i = 0; i < 10; i++){
		if(map[i] != map2[i])
			return false;
	}
	return true;
}

int InQ_()
{
	int map2[10] = {0,0,0,0,0,0,0,0,0,0};
	
	for(int i = 0; Q[i][0] != -1; i++){
		for(int j = 0; j < 5; j++){
			if(Q[i][j] != -1)
				map2[Q[i][j]] = 1;
		}
		if(EqualTo(map2)){      			
			return true;
		}
		for(int k = 0; k < 10; k++) 			
			map2[k] = 0;
	}
	return false;
}

int Update(int *set)   
{
		for(k = 0; k < no_of_inputs; k++)
		{	
			int i,j,temp;

			ClearMap();
			LookUp(set,inputs[k]);
			if(!InQ_() && transitionPresent){  			
				for(i = 0; Q[i][0] != -1; i++){;}     		
				indx = 0;
				for(j = 0; j < 10; j++){
					if(map[j] == 1){
						Q[i][indx] = j;
						indx++;
					}
				}
				temp = k;        
				Update(Q[i]);
				k = temp;      
			}
		}
		return 0;
}

#define FindFinal {									\
	int i,j,k;									\
	for(i = 0; i < 10; i++){							\
		for(j = 0; Q[i][j] != -1; j++){						\
			for(k = 0; k < no_of_final; k++){				\
				if(Q[i][j] == final_states[k])				\
				{							\
					FINAL_STATES[i] = Q[i];				\
					NO_OF_FINAL++;					\
				}							\
			}								\
		}									\
	}										\
	fprintf(fout,"\nFinal States : ");						\
	k = i = 0;									\
	while(k >= 0){									\
		if(FINAL_STATES[i] != NULL)						\
		{									\
			fprintf(fout,"{");						\
			for(j = 0; FINAL_STATES[i][j] != -1; j++){			\
				if(FINAL_STATES[i][j+1] != -1)				\
					fprintf(fout,"q%d,",FINAL_STATES[i][j]);	\
				else							\
					fprintf(fout,"q%d",FINAL_STATES[i][j]);		\
			}								\
			fprintf(fout,"}");						\
			k++;								\
		}									\
		i++;									\
		if(k == NO_OF_FINAL) break;						\
	}										\
}

#define FindStart {								\
		fprintf(fout,"Start states:");					\
		for(i = 0; i < no_of_starts; i++){				\
			Q[i][0] = start_states[i];				\
			fprintf(fout,"{q%d}",Q[i][0]);				\
		}								\
		fprintf(fout,"\n\n");						\
	}

int main()
{

	for(i = 0; i < 10; i++){
		for(j = 0; j < 5; j++){
			Q[i][j] = -1;
		}
	}

	Read();   

	FindStart
	
	int complete = Update(Q[0]);             
	if(complete == 0) printf("\nDFA READY\n");
	else printf("\nUnexpected Error!\n");


	fprintf(fout,"\nStates : ");
	for(i = 0; i < 10; i++){
		fprintf(fout,"{");
		for(j = 0; Q[i][j] != -1; j++){
			if(Q[i][j+1] != -1)
				fprintf(fout,"q%d,",Q[i][j]);
			else
				fprintf(fout,"q%d",Q[i][j]);
		}
		fprintf(fout,"}");
		if(Q[i+1][0] == -1) break;
	}

	FindFinal
	
	return 0;
}
