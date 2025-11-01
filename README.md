# 🔁 Arithmetic Notation Converter using Deque

This project implements a **Deque (Double-Ended Queue)** to convert mathematical expressions between **infix**, **prefix**, and **postfix** notations.  
It demonstrates strong understanding of **data structures**, **expression parsing**, and **algorithm design**.

---

## 🚀 Features
- **Full Notation Conversion Support**
  - Infix → Postfix / Prefix  
  - Postfix → Infix / Prefix  
  - Prefix → Infix / Postfix  
- **Deque-Based Implementation:** Utilizes a double-ended queue for efficient front and back access.  
- **Operator Precedence Handling:** Ensures accurate conversions using correct order of operations.  
- **Expression Validation:** Handles nested parentheses, multiple operators, and invalid input cases gracefully.  

---

## 🧠 Learning Objectives
- Apply the **Deque data structure** for bidirectional expression management.  
- Reinforce concepts of **stack-based expression parsing**.  
- Understand **prefix, infix, and postfix notation rules** and operator precedence.  
- Strengthen problem-solving in **algorithmic logic** and **data manipulation**.

---

## ⚙️ Implementation Details
- The project defines a `Deque` class supporting:
  - Insertion/removal from both ends.
  - Peek and empty checks.
- The converter class uses:
  - **Stacks** for operator precedence.
  - **Deques** for storing and reversing sequences efficiently.
- Conversion algorithms are based on classical **Shunting Yard Algorithm** and **stack-based evaluation** logic.

---

## 🧩 Example Usage
```cpp
ExpressionConverter converter;
string infix = "A - B + C";
string postfix = converter.infixToPostfix(infix);   // Output: "A B - C +"
string prefix  = converter.infixToPrefix(infix);    // Output: "+ - A B C"

