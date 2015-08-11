# JsonObject

A very lightweight wrapper to make working with the [json-c](https://github.com/json-c/json-c) library slightly more straightforward.

Instead of relying on json-c's `json_object_object_foreach()` and storing values as you loop through them, this wrapper will give you easy access to the values.

## Example Usage

**Sample JSON**

```json
{
  "aBool": true
}
```

**Sample C++**

```c++
#include <json/json.h>

JsonObject root;

json_object *config = json_tokener_parse(json.c_str());

JsonObject::buildObject(root, config);

bool myValue = root.getChild("aBool").getBool(); // true
```

## License

MIT
