#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

class RuntimeStringCmp
{
public:
    enum cmp_mode{normal, nocase};

private:
    const cmp_mode mode;
    static bool nocase_compare(char c1, char c2)
    {
        return toupper(c1) < toupper(c2);
    }

public:
    RuntimeStringCmp(cmp_mode m = normal):mode(m){}

    bool operator()(const string & s1, const string & s2)const
    {
        if (mode == normal)
        {
            return s1 < s2;
        }
        else
        {
            return lexicographical_compare(s1.begin(), s1.end(),
                                           s2.begin(), s2.end(),
                                           nocase_compare);
        }
    }
};

typedef map<string, string, RuntimeStringCmp> StringStringMap;

void fillAndprint(StringStringMap & coll);

int main()
{
    StringStringMap coll1;
    fillAndprint(coll1);

    //create an object for case-insensitive comparisons
    RuntimeStringCmp ignorecase(RuntimeStringCmp::nocase);

    //create a container with the case-insensitive
    //comparisons criterion
    StringStringMap coll2(ignorecase);
    fillAndprint(coll2);
}

void fillAndprint(StringStringMap & coll)
{
    coll["Deutschland"] = "Germany";
    coll["deutsch"] = "German";
    coll["Haken"] = "snag";
    coll["arbeiten"] = "work";
    coll["Hund"] = "dog";
    coll["gehen"] = "go";
    coll["Unternehmen"] = "enterprise";
    coll["unternehmen"] = "undertake";
    coll["gehen"] = "walk";
    coll["Bestatter"] = "undertaker";

    StringStringMap::iterator pos;
    cout.setf(ios::left, ios::adjustfield);
    for (pos = coll.begin();pos != coll.end();++pos)
    {
        cout << setw(15) << pos->first.c_str() << " "
        << pos->second << endl;
    }
    cout << endl;
}
