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

#include <json/json.h>
#include <map>
#include <string>
#include <vector>

#include "JsonObject.h"

JsonObject::JsonObject (int val)
{
    objType  = INT;
    intValue = val;
}

JsonObject::JsonObject (bool val)
{
    objType   = BOOL;
    boolValue = val;
}

JsonObject::JsonObject (const char* val)
{
    objType  = STRING;
    strValue = val;
}

JsonObject::JsonObject (std::vector<JsonObject> val)
{
    objType  = OBJECT_ARRAY;
    objArray = val;
}

JsonObject::JsonObject (std::vector<std::string> val)
{
    objType  = STR_ARRAY;
    strArray = val;
}

JsonObject::JsonObject (std::vector<bool> val)
{
    objType   = BOOL_ARRAY;
    boolArray = val;
}

JsonObject::JsonObject (std::vector<int> val)
{
    objType  = INT_ARRAY;
    intArray = val;
}

JsonObject::JsonObject ()
{
    objType = OBJECT;
}

JsonObject JsonObject::getChild (std::string key)
{
    return children[key];
}

std::map<std::string, JsonObject> JsonObject::getChildren ()
{
    return children;
}

std::vector<std::string> JsonObject::getStringArray ()
{
    return strArray;
}

std::vector<JsonObject> JsonObject::getObjectArray ()
{
    return objArray;
}

std::vector<bool> JsonObject::getBoolArray ()
{
    return boolArray;
}

std::vector<int> JsonObject::getIntArray ()
{
    return intArray;
}

bool JsonObject::getBoolAt (unsigned int i)
{
    return boolArray.at(i);
}

int JsonObject::getIntAt (unsigned int i)
{
    return intArray.at(i);
}

std::string JsonObject::getStringAt (unsigned int i)
{
    return strArray.at(i);
}

JsonObjectType JsonObject::getType ()
{
    return objType;
}

bool JsonObject::hasChildren ()
{
    return !children.empty();
}

JsonObject JsonObject::push_back (std::string key, JsonObject val)
{
    objType  = OBJECT;
    children[key] = val;

    return *this;
}

std::string JsonObject::toString ()
{
    switch (objType)
    {
        case STRING:
            return strValue;

        case BOOL:
            return (boolValue) ? "true" : "false";

        case INT:
            return std::to_string(intValue);

        default:
            return "JsonObject";
    }
}

void JsonObject::buildObject(JsonObject &parent, json_object *obj)
{
    enum json_type type;

    json_object_object_foreach(obj, key, val)
    {
        type = json_object_get_type(val);

        switch (type)
        {
            case json_type_object:
            {
                JsonObject child;

                JsonObject::buildObject(child, val);

                parent.push_back(key, child);
            }
            break;

            case json_type_array:
            {
                json_object *jArray = val;

                std::vector<JsonObject>  objArray;
                std::vector<std::string> strArray;
                std::vector<bool>        boolArray;
                std::vector<int>         intArray;

                int arraylen = json_object_array_length(jArray);
                json_object *jValue;

                for (int i = 0; i < arraylen; i++)
                {
                    jValue = json_object_array_get_idx(jArray, i);
                    type = json_object_get_type(jValue);

                    switch (type)
                    {
                        case json_type_string:
                        {
                            std::string value = json_object_get_string(jValue);
                            strArray.push_back(value);
                        }
                        break;

                        case json_type_boolean:
                        {
                            bool value = (bool)json_object_get_boolean(jValue);

                            boolArray.push_back(value);
                        }
                        break;

                        case json_type_int:
                        {
                            int value = json_object_get_int(jValue);

                            intArray.push_back(value);
                        }
                        break;
                            
                        case json_type_object:
                        {
                            JsonObject child;
                            
                            JsonObject::buildObject(child, jValue);
                            
                            objArray.push_back(child);
                        }
                        break;

                        default:break;
                    }
                }

                JsonObject child;

                if (!strArray.empty())
                {
                    child = JsonObject(strArray);
                }
                else if (!boolArray.empty())
                {
                    child = JsonObject(boolArray);
                }
                else if (!intArray.empty())
                {
                    child = JsonObject(intArray);
                }
                else if (!objArray.empty())
                {
                    child = JsonObject(objArray);
                }

                parent.push_back(key, child);
            }
            break;

            case json_type_boolean:
            {
                bool value = (bool)json_object_get_boolean(val);

                parent.push_back(key, value);
            }
            break;

            case json_type_int:
            {
                int value = json_object_get_int(val);

                parent.push_back(key, value);
            }
            break;

            case json_type_string:
            {
                std::string value = json_object_get_string(val);

                parent.push_back(key, value.c_str());
            }
            break;

            default: break;
        };
    }
}

std::string JsonObject::getString ()
{
    return strValue;
}

bool JsonObject::getBool ()
{
    return boolValue;
}

int JsonObject::getInt ()
{
    return intValue;
}
