# Coding Norme

## Header

Use only ifndef define to be cross plateform
```c++
#define __MYCLASS_H__
#ifndef __MYCLASS_H__

...

#endif // __MYCLASS_H__
```

## Includes in .h

```c++
#include <iostream>
#include <...>

#include "MyHeader.h"
#include "..."

// Forward declaration
class MyClass1;
namespace MyNamespace
{
    class MyClass2;
}

typedef MyNamespace::MyClass2 MyClass2;
```

## Include in .cpp

```c++
#include "MyHeader.h"

#include <iostream>
#include <...>

#include "MyClass.h"
#include "..."
```

## Namespace

Use PascalCase
```c++
namespace MyNamespace
{
    // write your code here
}
```

## Enum

Always use enum class and start with E prefix
```c++
/**
 * Tiny description of what the class is used for
 */
enum class EMyEnum
{
    DEFAULT,
    VAR1,
    VAR2,
    COUNT
}
```

## Class

```c++
/**
 * Tiny description of what the class is used for
 */
class MyClass
{
private:
#pragma region Internal Classes

    struct      myStruct ...;
    enum class  myEnum ...;

#pragma endregion

#pragma region Attributes

    int     _myVar1;
    float   _myVar2;

#pragma endregion

#pragma region Constructors

    // if Contstructors are defined
    MyClass();
    MyClass(const MyClass& class);
    MyClass(MyClass&& class);

    ~MyClass();

    // if Constructors aren't defined;
    MyClass() = default;
    MyClass(const MyClass& class) = default;
    MyClass(MyClass&& class) = default;

    ~MyClass() = default;

#pragma endregion

#pragma region Operators

    MyClass& operator=(const MyClass& class);

#pragma endregion

#pragma region Functions

    // Order from A to Z
    void    AMyMethod();
    float   BMyMethod();
    void    CMyMethod();

#pragma endregion

protected:
    (Same as private)

public:

#pragma region Attributes

    int myVar3;

#pragma endregion

    (Same as private)

#pragma region Accessors
    inline int  MyVar1() const { return _myVar1; }
    inline int& MyVar1()       { return _myVar1; }
#pragma endregion
}
```

## Function

Use reference type when parameter is bigger than 8 bytes
```c++
void MyFunction(const long long& arg1, int arg2);
```

If you return multiple values use out prefix on the returned parameter
```c++
void MyFunction(int& outArg1, MyClass& outArg2);
```

For function with a lot of arguments cut the line approximately at 80 characters
```c++
void MyFunction(const long long& arg1, int arg2, float arg3, double arg4,
    const MyClass& arg5, const MyBigNamedClass& arg6,
    MyVeryBigNameClassThatYouDontWantToWrite& outArg7);
```

If your function do not throw exception use noexcept suffix
```c++
void MyNotThrowFunction(const long long& arg1, int arg2) noexcept;
```

Document your function in javadoc
```c++
/**
 * Tiny description of what the function do
 * @parm paramName descrition of what the param is used for
 * @return description of the return
 * @throw what is throw
 */
 void Function(int paramName);
```

## If else statement

If the condition needs *one line* of execution  do not use the {}
```c++
if (condition)
    Action();

if (condition1)
    Action1();
else if (condition2)
    Action2();
else
    Action3();
```

If *one of the condition needs more than one line* use {}
```c++
if (condition)
    Action1();
else
{
    Action2();
    Action3();
}

if (condition1)
{
    Action1();
    Action2();
}
else
    Action3();
```

To check if pointer exist uss this
```c++
if (my_pointer1 || !my_pointer2)
{
    ...
}
```

If you have a lot of check cut the line before && or || and always use {}
```c++
if (condition1 && MyHugeFunctionForCheckARandomCondition()
    || AnOtherFunctionToCheckSomeThings())
{
    ...
}
```

## For and Foreach statement

Use the = to set iterator value
```c++
for (uint i = 0; i < size; ++i)
{

}
```

If more than *one line*
```c++
for (uint i = 0; i < size; ++i)
{
    Action1(i);
    Action2(i);
}

for (uint i = 0; i < size; ++i)
{
    if (condition1)
        Action(i);
}
```

In foreach loop use const & for types bigger than 8 bytes
```c++
for (const MyClass& my_class : myClasses)
{
    ...
}
```

## Switch statement

```c++
switch (...)
{
    // If very short line
    case 0: Action(); break;

    // If one line case
    case 1:
        MyActionThatIMustDoInThisCase();
    break;

    // If more than one line
    case 1:
    {
        Action1();
        Action2();
    }
    break;

    default:
    break;
}
```

## Variables

Use _ to separate variables name for local variables
```c++
int     my_var1;
float*  my_var2;
```

Use {} to init variable and be excplicit with types

```c++
// Do this
float   my_float { 5.f };

// Not this
float   my_float { 5 };
```