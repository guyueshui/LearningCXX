#ifndef _UNIT_H_
#define _UNIT_H_

#include<string>

class Unit {
private:
    using pos = unsigned int; // type alias
    pos rowIdx;
    pos colIdx;
    bool isRC; // is the type `R23C55`
    void getIdx_RC(std::string); // build index for type 'R23C55'
    void getIdx_NRC(std::string); // for type 'BC23'

public:
    // constructor1
    Unit(pos _r, pos _c) : rowIdx(_r), colIdx(_c) { }
    // constructor2
    Unit(std::string);

    // selectors
    pos getRow() { return rowIdx; }
    pos getCol() { return colIdx; }

    // modifiers
    void setRow(pos _r) { rowIdx = _r; }
    void setCol(pos _c) { colIdx = _c; }

    // utilties
    void printer(void);
    void convertor(void);
};
#endif
