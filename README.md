# JsonObject

A very lightweight wrapper to make working with the [json-c](https://github.com/json-c/json-c) library slightly more straightforward.

## Example

```c++
#include <json/json.h>

JsonObject root;

json_object *config = json_tokener_parse(json.c_str());

JsonObject::buildObject(root, config);
```

## License

MIT