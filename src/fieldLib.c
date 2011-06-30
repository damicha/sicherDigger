/* fieldLib.cpp */

// FIXME: merge anchor and object because the object has an fixed position in the field
// FIXME: fill prev and next
// FIXME: traverse through the array elements (print pos, prev, next pos)
// FIXME: split files

#include <stdio.h>
#include <deque>
using namespace std;


class baseObj;
class baseObjAnchor;
class baseObjField;


class baseObjAnchor
{
public:
    baseObj *obj;
    int pos_x;

    baseObjAnchor() : pos_x(-1), obj(NULL) {};
    
};


class baseObjField
{
public:
    int size_x;
    deque<baseObjAnchor> anchor;

    baseObjField(int size) {
        size_x = size;
        
        baseObjAnchor defaultAnchor;
        anchor.resize(size, defaultAnchor);
        
        initAnchors();
    };

    int initAnchors() {
        for (int i = 0; i < anchor.size(); i++)
        {
            anchor[i].pos_x = i;
        }
    
    };

};



/*
 * baseObj
 */
class baseObj
{
public:
    // root
    baseObjAnchor *root;
    // neighbours
    baseObj *x_prev, *x_next;
};



/*
 * main
 */
int main(void)
{
    baseObjField field(10);

    for(int x = 0; x < field.anchor.size(); x++) {
        printf("position: (x: %d, %d)\n", x, field.anchor[x].pos_x);
    }
    return 0;

/* error handling */
out:
    return -1;
}

