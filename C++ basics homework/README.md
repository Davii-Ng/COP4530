# COP 4530 - C++ Basics Programming Assesment

## Section 1
**1. (3 pts) Explain the purpose of `main()` function in C++:**
- It is the designated entry point for program execution

**2.  (4 pts) List four fundamentals data types in C++:**
- int: stores postive and negative whole numbers, size: 4 bytes
- char: stores a single character or ASCII encoded value enclosed in single quotes, size: 1 byte
- bool: Stores logic, true or false, size: 1 byte
- float: Stores decimals numbers, size: 4 to 8

**3. (4 pts) Write a C++ program that:**

- Declares an integer variable count initialized to 10

- Declares a double variable price initialized to 25.75
Prints both values to the console

Read Here: [Code](./Section1/main.cpp)

**4. (4 pts) Explain the difference between float and double. Include one situation where double is preferred.**

- The main difference between a float and a double is its memory. A float uses 4 bytes of storage whereas a double uses 8 bytes of storage. 

- Float is better for memory efficiency, such as large arrays of computer graphics, where slight precision errors does not matter
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
        cout++;
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
