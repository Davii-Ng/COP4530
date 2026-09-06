# COP 4530 - C++ Basics Programming Assessment

## Section 1
**1. (3 pts) Explain the purpose of `main()` function in C++:**
- It is the designated entry point for program execution

**2.  (4 pts) List four fundamentals data types in C++:**
- int: stores positive and negative whole numbers, size: 4 bytes
- char: stores a single character or ASCII encoded value enclosed in single quotes, size: 1 byte
- bool: Stores logic, true or false, size: 1 byte
- float: Stores decimal numbers, size: 4 bytes

**3. (4 pts) Write a C++ program that:**

- Declares an integer variable count initialized to 10

- Declares a double variable price initialized to 25.75

- Prints both values to the console

Read Here: [Code](./Section1/main.cpp)

**4. (4 pts) Explain the difference between float and double. Include one situation where double is preferred.**

- The main difference between a float and a double is its memory. A float uses 4 bytes of storage whereas a double uses 8 bytes of storage. 

- Float is better for memory efficiency, such as large arrays in computer graphics, where slight precision errors do not matter
- Double is better for accurate calculations, for example pi.

## Section 2

**1. (5 pts) Write a C++ program using a for loop to print all even numbers between 1 and 20.**

[Code](./Section2/loop.cpp)

**2. (5 pts) Explain the difference between a while loop and a do‑while loop. Include a short code snippet for each.**

- A while loop checks the condition before the code blocks run whereas a do-while loop checks for the condition after the code block.
- Example:

```C++
// This is a while loop
int main(){
    int count = 5;
    
    while(count < 3){
        cout << "This should not be printed"<< endl;
        count++;
    }
    return 0;
}
```

```cpp
int main(){

    int count = 5;
    do{
        cout << "This should be printed" << endl;
        count++;
    }while(count < 3);
    
    return 0;
}
```

**3.(5 pts) Write a C++ program that:**
- Takes an integer input from the user
- Uses an if‑else statement to determine whether the number is positive, negative, or zero

[Click me for Code](./Section2/integer-check.cpp)

**4. (5 pts) Write a C++ program using a switch statement to display the day of the week based on a number (1 = Monday, 2 = Tuesday, …, 7 = Sunday).**

[Click me for Code](./Section2/switchcase.cpp)


## Section 3
**1.(4 pts) Write a function declaration and definition for a function calculateArea that takes two double parameters (length and width) and returns the area.**

[Click me for Code](./Section3/area.cpp)

**2. (4 pts) Explain function overloading in C++. Provide a small example with at least two overloaded functions.**

- Function overloading is a feature that allows multiple functions to share the same name within the same scope.

[Click me for Code](./Section3/function-overloading.cpp)

**3. (4 pts) Explain the difference between pass‑by‑value and pass‑by‑reference. When should pass‑by‑reference be used?**

- The difference is whether the function receives a copy of the argument or a direct alias to the original variable. Pass-by-value copies the argument, so changes inside the function do not affect the caller's variable. Pass-by-reference binds to the original variable, so changes inside the function do affect the caller's variable.
- Pass-by-reference should be used when we want the function to modify the original data, or when we want to avoid copying large objects. If we only want to avoid the copy but not modify the data, use a `const` reference.

**4. (4 pts) What are default arguments in C++? Write a function example that uses a default argument.**

- A default argument is a fallback value specified in the function declaration that the compiler automatically applies if the caller omits that argument
- Example: [Here](./Section3/default-argument.cpp)


**5. (4 pts) Write a complete C++ program that swaps two integers using a function swapInts and pass‑by‑reference. The program should print values before and after swapping.**

- Example: [Here](./Section3/swapint.cpp)

## Section 4

**1. (6 pts) Define a class Rectangle with:**
- Private data members: length and width
- Public member functions: setValues(), getArea(), and getPerimeter()
- Write a main() function that creates an object of Rectangle and displays the area and perimeter.

[Click here for code](./Section4/rectangle.cpp)

**2. (4 pts) Explain encapsulation in C++. How is it implemented in a class?**
- Encapsulation is a concept of OOP that hides attributes and methods inside a class to restrict access to data, it is done by using classes and access specifiers.

**3. (4 pts) Explain the difference between public, private, and protected access specifiers.**

- Public: Members that are public are accessible anywhere in the program
- Protected: Members that cannot be accessed from outside the class hierarchy, but can be accessed by child classes which inherit from this class
- Private: Members are hidden from everything outside the class, even child classes.


**4. (6 pts) Explain inheritance in C++. Write a simple example where a class Square inherits from Rectangle.**

- Inheritance is a concept in OOP that allows a class to acquire the properties and behavior of another class.

[Click me to see code](./Section4/square.cpp)


## Section 5

**1. (5 pts) Write a C++ program that dynamically allocates an integer array of size 5 using new, assigns values, prints them, and properly deallocates the memory using delete[].**


[Click me for code](./Section5/dynamic-allocation.cpp)

**2. (5 pts) What is a memory leak? Explain two ways to prevent memory leaks in C++.**

- A memory leak occurs when dynamically allocated heap memory is never released back to the heap after it is no longer needed, so the program keeps holding memory it cannot use again.
- Two ways to prevent memory leaks:
  1. Match every allocation with the matching deallocation: every `new` with a `delete`, and every `new[]` with a `delete[]`, on every path out of the function, including error paths.
  2. Use smart pointers such as `std::unique_ptr` and `std::shared_ptr`, or standard containers such as `std::vector` and `std::string`. They own the memory and free it automatically in their destructor (RAII), so no manual `delete` is needed.


**3. (5 pts) Write a C++ program that:**
- Declares a pointer to an integer
- Assigns it the address of a variable
- Prints the value using the pointer
- Explain the difference between * and & in this context

- `&` is the address-of operator. In `int *ptr = &x;` it produces the memory address of `x`, which is the value stored in the pointer. In a declaration such as `int &ref = x;` the same symbol means "reference", not address-of.
- `*` has two roles. In the declaration `int *ptr` it marks the variable as a pointer to an int. In an expression such as `*ptr` it is the dereference operator, which reads the value stored at the address the pointer holds, so `*ptr` gives `5` while `ptr` gives the address of `x`.

[Click me for code](./Section5/pointer.cpp)


## Section 6
**1. (5 pts) Explain exception handling in C++. Write a simple try‑catch example that handles division by zero.**

- Exception handling is a mechanism that allows programs to handle runtime errors without having to crash. Code that may fail goes in a `try` block, the error is signalled with `throw`, and a matching `catch` block handles it.

[Click me for code](./Section6/divide-by-zero.cpp)


**2. (5 pts) Explain the purpose of the const keyword.**

- `const` marks something as read-only. The compiler rejects any attempt to modify it, so a value that should never change cannot be changed by accident.
- On a variable it creates a named constant that must be initialized when it is declared.
- On a function parameter, especially a `const` reference, it lets the function read the argument without copying it while promising not to modify the caller's data.

Write a short C++ program demonstrating:
- A constant variable
- A function parameter declared as const

[Click me for code](./Section6/const.cpp)