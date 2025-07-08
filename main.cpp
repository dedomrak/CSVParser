
#include "csvparser.h"
#include <iostream>

int main(int argc, char *argv[])
{
    char *fileName=NULL;

    if(argc==1)
    {
        printf("Usage:\n    CSV parser  <input CSV file> \n");
        printf("\tp.....Prints file contents \n");
        printf("\t+..... Sum of file's columns\n");
        printf("\tm.....Max of columns values\n");
        printf("\ta.....Add each row of columns values\n");
        printf("\tq.....Quit\n");
    }
    fileName = (argc==2) ? (argv[1]): NULL ;

    if(!fileName) {
        printf("Input file is missing!\n") ;
        return 1 ;
    }

    FILE *fp =fopen(fileName,"r");
    if (!fp) {
        printf("Could't open file!\n");
        return 1;
    }
    int retVal = 0;
    CSVParser csv;
    retVal = csv.Parse(fp);

    char num ;
    printf(" Parse\n %s \n file!\n",fileName);
    printf( " Expect input option: p,+,m,a or q!\n") ;
    while ( num != 113 ) {
        std::cin>>num;
       // printf( "%d\n", num ) ;
        if(112==num)
            csv.PrintColumns();
        else if(43==num)
            csv.PrintColumnSum();
        else if(109==num)
            csv.PrintColumnMax();
        else if(97==num)
            csv.PrintRowSum();
    }

    return 0;
}
