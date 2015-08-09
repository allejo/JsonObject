/*
Copyright (C) 2015 Vladimir Jimenez

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef __JsonObject_H_
#define __JsonObject_H_

#include <json/json.h>
#include <string>
#include <vector>
#include <map>

enum JsonObjectType {
    INT,
    BOOL,
    OBJECT,
    STRING,
    INT_ARRAY,
    STR_ARRAY,
    BOOL_ARRAY,
    LAST_OBJECT_TYPE
};

class JsonObject
{
public:
    JsonObject (int val);
    JsonObject (bool val);
    JsonObject (const char* val);
    JsonObject (std::vector<std::string> val);
    JsonObject (std::vector<bool> val);
    JsonObject (std::vector<int> val);
    JsonObject ();

    JsonObject getChild (std::string key);

    std::map<std::string, JsonObject> getChildren ();

    std::vector<std::string> &getStringArray ();
    std::vector<bool> &getBoolArray ();
    std::vector<int> &getIntArray ();

    std::string getStringAt (unsigned int i);
    std::string getString ();
    std::string toString ();

    bool hasChildren ();
    bool getBoolAt (unsigned int i);
    bool getBool ();
    int getIntAt (unsigned int i);
    int getInt ();

    JsonObjectType getType ();
    JsonObject push_back (std::string key, JsonObject val);

    static void buildObject (JsonObject &parent, json_object *obj);

private:
    JsonObjectType objType;

    std::map<std::string, JsonObject> children;

    std::vector<std::string> strArray;
    std::vector<bool>        boolArray;
    std::vector<int>         intArray;
    std::string strValue;
    bool        boolValue;
    int         intValue;
};

#endif
