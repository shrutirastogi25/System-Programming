#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char pseudo[6][6]={"DB","DW","DD","RESB","RESW","RESD"}; //opcodes
int pseudo_size[6]={1,2,4,1,2,4};
char mnemonics[9][6]={"STOP","ADD","SUB","MUL","MOVER","MOVEM","INC","STORE","CMP"}; //mnemonics
int mnemonics_size[9]={1,1,1,1,5,5,1,5,5};
 
/*Pass1*/
struct assemb_section
{
          	char name[20];
          	int size;
}section[5]; 	
 	
struct symb
{  
          	char name[20];
          	char type[20];
          	int location; //address of symbol
          	int size;
          	int section_id;
}sym[20];
 
int main()
{
          	char wordcount[10];
          	int lc=0,initial=0,length,nsymb=0,nsec=0,i,check=0;
          	FILE *fin;
          	fin=fopen("input.asm","r"); //assembler input
          	fscanf(fin,"%s",wordcount); //read input
        	if(!strcmp(wordcount,"START")) //if start copy address(lc)
          	{
                       	fscanf(fin,"%d",&initial);
                       	lc=initial;
          	}
          	while(!feof(fin))
          	{
                       	fscanf(fin,"%s",wordcount); //read next
                       	//check if it is present in mnemonics table
                       	for(i=0;i<9;i++)
                       	{
                                     	if(!strcmp(wordcount,mnemonics[i]))
                                     	{
                                     		lc+=mnemonics_size[i];
                                                   	check=1;
                                                   	break;
                                     	}
                       	}
                       	if(check==0)
                       	{
                                     	if(!strcmp(wordcount,"section"))          	                       	//check if it is a section
                                     	{
          	                                     	fscanf(fin,"%s",wordcount);
                                     	          	strcpy(section[nsec].name,wordcount);
                                                   	if(nsec==0)
                                                                 	nsec++;
                                                   	else
                                                   	{
                                                                 	section[nsec-1].size=lc-initial;
                                                                 	nsec++;
                                                   	}
                                                   	lc=initial;
                                     	}
                                     	else
                                     	{
                                                   	length=strlen(wordcount);
                                                   	if(wordcount[length-1]==':')                	//check if it is a label
                                                   	{                                   	
                                                                 	          	for(i=0;wordcount[i]!=':';i++)
                                                                              		sym[nsymb].name[i]=wordcount[i];
                                                                 	          	sym[nsymb].name[i]='\0';	
                                                                 	          	strcpy(sym[nsymb].type,"Lbl");       	
                                                                 	          	sym[nsymb].location=lc;
                                                                 	          	sym[nsymb].size=0;
                                                                 	          	sym[nsymb].section_id=nsec;
                                                   	}                      	
                                                   	else                               	//check if it is a variable
                                                   	{
                                                                 	          	if(!strcmp(wordcount,"END"))
                                                                                            	break;
                                                                 	          	strcpy(sym[nsymb].name,wordcount);
                                     	                                     	fscanf(fin,"%s",wordcount); //read next
                                                                             	for(i=0;i<6;i++)
                                                                              	{
                                                                              	          	if(!strcmp(wordcount,pseudo[i]))
                                                                                            	{
                                                                                            	          	strcpy(sym[nsymb].type,"Var");
                                                                                            	          	sym[nsymb].location=lc;
                                                                                            	          	sym[nsymb].size=pseudo_size[i];
                                                                                            	          	sym[nsymb].section_id=nsec;
                                                                                            	          	lc+=pseudo_size[i];
                                                                                            	          	break;
                                                                                            	}
                                                                              	}
                                                   	}        	 
                                                   	nsymb++;
                                     	}
                       	}
                       	check=0;
                       	fgets(wordcount,50,fin); //read until '\n' character
          	}
          	section[nsec-1].size=lc-initial;
          	
          	printf("\n\n1) SYMBOL TABLE:\n----------------\n\nSequence\tSymbol\t Type\tAddress\tSize\tSection_ID");
          	for(i=0;i<nsymb;i++)
                       	printf("\n %d \t\t %s \t %s \t %d \t %d\t   %d",i+1,sym[i].name,sym[i].type,sym[i].location,sym[i].size,sym[i].section_id);
          	printf("\n\n\n\n1) SECTION TABLE:\n-----------------\n\nSequence\t Section\tSize");
          	for(i=0;i<nsec;i++)
                       	printf("\n %d \t\t %s \t\t %d",i+1,section[i].name,section[i].size);
 
          	fclose(fin); //close files opened
          	
/* PASS 2 */
          	int size=0;  //offset
          	FILE *fop;
          	int character1=1,j,character2=1,character3=1;
          	fop=fopen("output.txt","w");
          	fin=fopen("input.asm","r"); //assembler input
          	fscanf(fin,"%s",wordcount);
          	if(!strcmp(wordcount,"START")) //if start copy address(start)
                       	fscanf(fin,"%d",&size);
          	while(!feof(fin))
          	{
                       	
                       	bool character=true;
                       	fscanf(fin,"%s",wordcount); //read next
                       	if(!strcmp(wordcount,"END"))
                                     	break;
                       	for(i=0;i<9;i++)                               	//check if it is present in mnemonics table
                       	{
                                     	if(!strcmp(wordcount,mnemonics[i]))
                                     	{
                                                   	fprintf(fop,"\n%08x\t",size);
                                     		size=size+mnemonics_size[i];
                                     		fprintf(fop,"%08x",i+1);
                                                   	check=1;
                                                   	fscanf(fin,"%s",wordcount);
                                                   	if(i!=6&&i!=7)              	//if it is a two operand instruction
                                                   	{
                                                                 	fscanf(fin,"%s",wordcount);
                                                                 	for(j=0;j<nsymb;j++)                	//if operand is a symbol
                                     	    	{
                                                                 	          	if((!strcmp(wordcount,sym[j].name)) && (!strcmp(sym[j].type,"Var")))
                                                                              	{
                                                                              	          	fprintf(fop,"%08x",sym[j].location);
                                                                              	          	character2=0;
                                                                              	}
                                                                 	}
                                                                 	if(character2==1)          	//if operand is a constant
                                                                 	{
                                                                              	fprintf(fop,"%08x",atoi(wordcount));
                                                                 	}
                                                                 	character2=1;
                                                   	}
                                                   	else                     	//for STORE,INC
                                     	          	{                                   	          	
                                                                 	for(j=0;j<nsymb;j++)   	//if operand is a symbol
                                     	    	{
                                                                 	          	if((!strcmp(wordcount,sym[j].name)) && (!strcmp(sym[j].type,"Var")))
                                                                              	{
                                                                              	          	fprintf(fop,"%08x",sym[j].location);
                                                                              	          	character3=0;
                                                                              	}
                                                                 	}
                                                                 	if(character3==1)         	//if operand is a constant
                                                                 	{
                                                                              	fprintf(fop,"%08x",atoi(wordcount));
                                                                 	}
                                                                 	character3=1;  	                       	
                                                   	}
                                                   	break;
                                     	}
                       	}
                       	if(check==0)                  	//if not a mnemonic         	
                       	{
                                     	for(j=0;j<nsymb;j++)                	//if it is a symbol
                                     	{
                                     	          	if((!strcmp(wordcount,sym[j].name)) && (!strcmp(sym[j].type,"Var")))
                                                   	{
                                                                 	
                                                                 	fprintf(fop,"\n%08x\t",size);
                                                                 	size=size+sym[j].size;
                                                                 	fscanf(fin,"%s",wordcount);
                                                                 	fscanf(fin,"%s",wordcount);
                                                                 	fprintf(fop,"%08x",atoi(wordcount));
                                                                 	character=false;
          	                                                   	break;
                                                   	}
                                                   	else if((!strcmp(wordcount,sym[j].name)) && (!strcmp(sym[j].type,"Lbl")))
                                                   	{
                                                                 	character=false;
                                                                 	break;
                                                   	}
                                     	}
                                     	if(character==true)     	//if it is a section                                     	
                                     	   	for(int k=0;k<nsec;k++)
                                                                 	          	if(!strcmp(wordcount,section[k].name))
                                                   	         	break;
          	          	character=true;
                       	}
                       	check=0;
          	}
          	fclose(fin);
          	fclose(fop);
          	fop=fopen("output.txt","r");
          	
          	printf("\n\nOutput:");
          	printf("\n-------------------------------------");
          	char str[50];
          	while(!feof(fop))
          	{        	
                       	fgets(str,50,fop);
                       	printf("%s\n",str);
          	}
          	printf("\n");
          	//system("pause");
          	return 0;
}
