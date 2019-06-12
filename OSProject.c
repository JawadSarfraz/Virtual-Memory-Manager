
#include<stdio.h>
#include<stdlib.h>

#define frameSize 256
#define Frames 256
#define pageSize 256
#define pages 256

int tlb[16],indexOfTlb = 0;
int frameNo=0;
int offset=0;
int page_number=0;
int page_table[256][2];
int physical_memory[pages][pageSize];
int logical_memory[pages][pageSize];

//print Tlb entries
void Tlb(){
	int i;
	for(i =0;i<16;i++){
		printf("At index %d the page is : %d",i,tlb[i]);
	}
}
//Writes entry in tlb
int writeTlb(int frameNo){
	if(indexOfTlb == 15){
		indexOfTlb=0;
	}
	tlb[indexOfTlb] = frameNo;
	indexOfTlb++;
	return tlb[indexOfTlb];
}

//assigning physical memory
void assigningMemory()
{
   int total_physical_memory[Frames][frameSize];
   int total_logical_memory[pages][pageSize];
   int page_table[pages][pageSize];

int i,j=0;
int k=1;
for(i=0;i<pages;i++)
	{
		for(j=0;j<pageSize;j++){
			total_logical_memory[i][j]=k;
              		k++;				
	}
}
for(i=0;i<pages;i++)
	{
		for(j=0;j<pageSize;j++)
			{
				printf("byte no: %d page_number: %d offset: %d \n",total_logical_memory[i][j],i,j);
			}
	}					
}

//mapping of logical to physical memory
int Mapping(int logicalAdressByte)
{
	   int checkForEntries = 256;
           frameNo = logicalAdressByte/checkForEntries;
           int offset = logicalAdressByte % checkForEntries;
           printf("logical adress mapped to frame number  %d\n",frameNo);
           printf("and offset is %d\n",offset);
	   writeTlb(logicalAdressByte);
	   int storeTlbIndex = indexOfTlb-1;
	   printf("Entry in tlb %d at index : %d",tlb[storeTlbIndex],storeTlbIndex);

}

//mapping from file
int MappingFromFile()
{
	int i,indexOf2ndEntery,l,m,p,indexOfStoring,pageMapping,pageTable,totalNoOfPages = 255;
	for(i=0;i<totalNoOfPages;i++)
	{
		for(indexOf2ndEntery=0;indexOf2ndEntery<totalNoOfPages;indexOf2ndEntery++)
			physical_memory[i][indexOf2ndEntery]=indexOf2ndEntery;
	}

	static const char fileName[] = "File.txt";
	FILE *file = fopen ( fileName, "r" );
	if ( file != NULL )
	{
		char lineNumber [6]; /* or other suitable maximum line size */
		int input_number=1;
		printf("logical Address\t page number\t offset\t page table block\t physical memory block\n");
		while ( fgets ( lineNumber, sizeof lineNumber, file ) != NULL ) /* read a line */
		{          			
   				printf("%d) ",input_number);
          			printf(" ");
           			page_number = atoi(lineNumber)/(totalNoOfPages+1);
           			offset = atoi(lineNumber) % (totalNoOfPages+1);
				for(l=0;l<1;l++)
				{ 
					for(m=0;m<1;m++)
					{
						page_table[l][m]=page_number;
                                                	
						pageTable=page_table[l][m];	
						input_number++;
					}						
				}	
				for(indexOfStoring=0;indexOfStoring<totalNoOfPages;indexOfStoring++)
				{
					for(p=0;p<totalNoOfPages;p++)
					{
						pageMapping=offset+page_table[indexOfStoring][p+1];
				}
			}

				printf("\t\t%d\t\t %d \t\t%d \t\t%d \t\t\t%d\n",atoi(lineNumber),page_number,offset,pageTable,pageMapping);
			}
		fclose(file);
	}
}
int main()
{

	int choice = 0;
	while(choice!=5){
	printf("\n Choose the option\n 1 For mapping the entire file \n 2 Map logical addresses to physical\n");
	printf(" 3 Map logical to physical addresses from file\n 4 For check Tlb table\n 5 To Exit \n");

	scanf("%d",&choice);
	int logical_address;
	if(choice==1)
		assigningMemory();
	if(choice==2){
		printf("enter logical address\n");
		scanf("%d",&logical_address);
		Mapping(logical_address);
	}
	if(choice==3){
		MappingFromFile();
	}
	if(choice==4){
		Tlb();
	}
} 
	return 0;
}
