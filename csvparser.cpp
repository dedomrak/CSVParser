#include "csvparser.h"

CSVParser::CSVParser()
{
    m_colList = std::vector<ColumnVal>();
}

int CSVParser::Parse(FILE  *fp)
{
    if(!fp)
        return 2;

    int size = 1024;
    int pos = 0;
    int ch;
    char *line = (char *)malloc(size);

    do { // read all lines in file
        pos = 0;
        do{ // read one line
            ch = fgetc(fp);
            if(ch != EOF)  line[pos++] = (char)ch;
            if(pos >= size - 1) {
                // increase buffer length - leave room for 0
                size *=2;
                line = (char*)realloc(line, size);
            }
        }while(ch != EOF && ch != '\n');

        line[pos] = 0;
        if(strlen(line)==1 && ch=='\n') {
            line[0] ='\0';
            continue;
        }
        char * lineT = trimWhiteSpace(line);
        if(lineT[0] == '\0')
            continue;
        // Process this line
        char ch =' ';
        char *key = &ch;
        if(startsWith("Column",lineT) ) {
            std::vector<char *> splitVector;
            m_headerName = splitString(line,key);
            for(int i=0;i<m_headerName.size(); i++) {
                ColumnVal col;
                col._name = m_headerName[i];
                col._maxValue = 0;
                col._sumValues = 0;
                m_colList.push_back(col);
            }
        }
        else {
            std::vector<char *> splitVector;
            splitVector = splitString(line,key);
            int columnNumber = 0;
            unsigned int rowSum = 0;
            for(int i=0;i<splitVector.size(); i++) {
                unsigned int number = atoi(splitVector[i]);
                m_values.push_back(number);
                if (m_colList[columnNumber]._maxValue < number)
                    m_colList[columnNumber]._maxValue = number;
                m_colList[columnNumber]._sumValues+=number;
                rowSum +=number;
                columnNumber++;
            }
            m_rowSum.push_back(rowSum);
        }
    }  while(ch != EOF);
    fclose(fp);
    if(line!=NULL)
        free(line);
    return 0;
}

int CSVParser::PrintColumns()
{
    for(int i=0;i<m_headerName.size(); i++)
        printf("  %s  ",m_headerName[i]);
    printf("\n");
    int breakNum =1;
    char * oneTab = "\t";
    char *twoTab ="\t\t";
    for(int i=0;i<m_values.size(); i++) {
        printf("  %d%s",m_values[i],(i%2)? oneTab:twoTab);
        if(breakNum ==m_headerName.size()) {
            printf("\n");
            breakNum =0;
        }
        breakNum++;
    }

    return  0;
}

int CSVParser::PrintColumnSum()
{
    for(int i=0;i<m_headerName.size(); i++)
        printf("  %s  ",m_headerName[i]);
    printf("\n");
    int breakNum =1;
    char * oneTab = "\t";
    char *twoTab ="\t\t";
    for(int i=0;i<m_colList.size(); i++) {
        printf("  %d%s",m_colList[i]._sumValues,(i%2)? oneTab:twoTab);
        if(breakNum ==m_headerName.size()) {
            printf("\n");
            breakNum =0;
        }
        breakNum++;
    }
    return  0;
}

int CSVParser::PrintColumnMax()
{

    for(int i=0;i<m_headerName.size(); i++)
        printf("  %s  ",m_headerName[i]);
    printf("\n");
    int breakNum =1;
    char * oneTab = "\t";
    char *twoTab ="\t\t";
    for(int i=0;i<m_colList.size(); i++) {
        printf("  %d%s",m_colList[i]._maxValue,(i%2)? oneTab:twoTab);
        if(breakNum ==m_headerName.size()) {
            printf("\n");
            breakNum =0;
        }
        breakNum++;
    }
    return  0;
}

int CSVParser::PrintRowSum()
{
    printf("  Column Row Sum\n");
    for(int i=0;i<m_rowSum.size(); i++)
        printf("  %d\t\n",m_rowSum[i]);
    return  0;
}
