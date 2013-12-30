R_TTS
=================

R_TTS is a small Text To Speech project that implements Google TTS API, using cURL library for managing protocols.

Usage
-------------
```C
#include "TTS.c"

int main()
{
	speakFromString("hello");
	return 0;
}
```

```BASH
$ gcc -lcurl main.c -o main
$ ./main
```

License
--------

This code is under the BSD license.
