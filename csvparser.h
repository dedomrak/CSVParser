#ifndef CSVPARSER_H
#define CSVPARSER_H

#include "support_funcs.h"

struct ColumnVal {
    ColumnVal ():_name(NULL), _maxValue(0),_sumValues(0) {}
    char * _name;
    unsigned int _maxValue;
    unsigned int _sumValues;
};

class CSVParser
{
public:
    CSVParser();
    int Parse(FILE *fp);
    int PrintColumns();
    int PrintColumnSum();
    int PrintColumnMax();
    int PrintRowSum();
private:
    std::vector<char *> m_headerName;
    std::vector<int> m_values;
    std::vector<ColumnVal> m_colList;
    std::vector<unsigned int> m_rowSum;
};

#endif // CSVPARSER_H
