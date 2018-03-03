#include <iostream>
#include "Resizable_deque.h"

/*
template <typename T>
std::ostream &operator<<( std::ostream &out, Resizable_deque<T> const &line ) {
    int i = 0;
    int val;

    for (int i = 0; i < line.capacity(); i++) {
        val = line.array[i];

        //If front is also end and two digit value use '!' to represent '*' + '.'
        if (i == line.iback && i == line.ifront){
            if (val < 10 && val > 0){
                out << '*' << val << '.';
            }else if(val == 0){
                out << '*' << '_' << '.';
            }else{
                out << '!' <<val;
            }
        }
            //Mark array end w/ '.'
        else if (i == line.iback){
            if (val < 10 && val > 0){
                out << ' ' << val;
            }else if(val == 0){
                out << '_' << ' ';
            }else{
                out << val;
            }
            out << '.';
        }
            //Mark array front w/ '*'
        else if( i == line.ifront){
            out << '*';
            if (val < 10 && val > 0){
                out << val << ' ';
            }else if(val == 0){
                out << '_' << ' ';
            }else{
                out << val;
            }
        }
            //Stored values
        else if (val != 0){//should be empty/not empty nodes
            if (val < 10){
                out << ' ' << val << ' ';
            }else{
                out << ' ' << val;
            }
        }
            //Blanks
        else{
            out << " _ ";
        }

    }
    return out << std::endl;
}
*/

int main() {

    //Create deque
    Resizable_deque<int>* test_line = new Resizable_deque<int>(14);
    std::cout << std::endl << "Printing test_line..." << std::endl << std::endl;

    //Print header
    std::cout << std::endl << "         front = '*'          back = '.'" << std::endl;
    //Print underline
    for (int i = 0; i< 16*3; i++){
        std::cout << '-';
    }
    //Print header index
    std::cout << std::endl;
    for (int i = 0; i < test_line->capacity(); i++){
        if (i < 10){
            std::cout << ' ' << i << ' ';
        }else{
            std::cout << i << ' ';
        }
    }
    std::cout << std::endl;

    //Print underline
    for (int i = 0; i< 16*3; i++){
        std::cout << '-';
    }
    std::cout << std::endl;
/*                      Test Code                          */
/*---------------------------------------------------------*/

    //Empty array (no back)
    std::cout << *test_line;
    //Fill deque from 1 - 16
    for (int i = 0; i < 15; i++) {
    test_line->push_back(test_line->size()+1);
    std::cout << *test_line;
    }

    //Check circular push_front
    test_line->push_front(test_line->size()+1);
    std::cout << *test_line;

    std::cout << std::endl;

    //Resize array and wrap front of line to back of array
    std::cout << std::endl << "Upsizing..." << std::endl << std::endl;

    test_line->push_front(test_line->size()+1);
	std::cout << *test_line;

    //Fill remaining spots
    std::cout << std::endl;
    for (int i = 0; i < 4; i++) {
        test_line->push_front(test_line->size()+1);
        std::cout << *test_line;
    }

    //Middle fill

    //Resize array and wrap ifront to back of array
    for (int i = 0; i < 5; i++) {
        test_line->push_front(test_line->size()+1);
        std::cout << *test_line;
    }

    for (int i = 0; i < 6; i++) {
        test_line->push_back(test_line->size()+1);
        std::cout << *test_line;
    }

    std::cout << std::endl;

    //Test move and copy
    Resizable_deque<int> mv;
    {
        std::cout << std::endl;
        Resizable_deque<int> cp = Resizable_deque<int>(*test_line);
        std::cout << "Copied  : " << cp;
        mv = Resizable_deque<int>(std::move(cp));   //move contents of cp to mv
    }   //kill cp

    //Print lines
    std::cout << "Original: " << *test_line;
    std::cout << "Moved   : " << mv << std::endl;
    //Erase until downsize; iback wraps to back of array before downsize (ifront < iback)
    for (int i = 0; i < 24; i++) {
        test_line->pop_back();
        std::cout << *test_line;
    }

    //Cleared original test_line
    test_line->clear();
    std::cout << *test_line;


    //Print underline
    for (int i = 0; i< 16*3; i++){
        std::cout << '-';
    }

    //Print header index
    std::cout << std::endl;
    for (int i = 0; i < test_line->capacity(); i++){
        if (i < 10){
            std::cout << ' ' << i << ' ';
        }else{
            std::cout << i << ' ';
        }
    }
    std::cout << std::endl;

    //Print underline
    for (int i = 0; i< 16*3; i++) {
        std::cout << '-';
    }

    //Print stats
    std::cout << std::endl;
    std::cout << "Deque Size:" << ' '<< test_line->size() << '\t' << '\t' << '\t' << '\t';
    std::cout << "Deque Capacity: " << ' ' << test_line->capacity() << std::endl << std::endl;

    //Restore moved copy
    std::cout << std::endl << "Printing mv..." << std::endl << std::endl;

    for (int i = 0; i < 19; i++) {
        mv.pop_back();
        std::cout << mv;
    }

    //Force downsize and rewrite array with iback < ifront
    for (int i = 0; i < 6; i++) {
        mv.pop_front();
        std::cout << mv;
    }

    //Print footer (mv)

    //Print underline
    for (int i = 0; i< 16*3; i++){
        std::cout << '-';
    }

    //Print header index
    std::cout << std::endl;
    for (int i = 0; i < test_line->capacity(); i++){
        if (i < 10){
            std::cout << ' ' << i << ' ';
        }else{
            std::cout << i << ' ';
        }
    }
    std::cout << std::endl;

    //Print underline
    for (int i = 0; i< 16*3; i++){
        std::cout << '-';
    }
    std::cout << std::endl;

    //Print stats
    std::cout << "Deque Size (mv):" << ' '<< mv.size() << '\t' << '\t' << '\t' << '\t';
    std::cout << "Deque Capacity (mv): " << ' ' << mv.capacity() << std::endl << std::endl;

    delete test_line;
	return 0;
}