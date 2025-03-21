# Image Strip Linker DLL

This project is an implementation of a doubly-linked list (DLL) to manipulate blocks of pixels from an image. The task involves unscrambling an image that has been divided into vertical strips (blocks) and then reassembling them based on minimizing the difference between adjacent blocks.

## Overview

The goal of this assignment was to:
- Implement a doubly-linked list (DLL) to hold and manipulate image blocks.
- Implement functions for inserting, swapping, and unscrambling the blocks in the chain.
- Work with dynamic memory management, including copy constructors, destructors, and assignment operators.

## Features

- **Block Class**: Handles image blocks (vertical strips of the image).
  - `Width()` and `Height()` methods to return the dimensions of the block.
  - `Build()` to grab a vertical strip from the image.
  - `Render()` to draw the block onto the image.
  
- **Chain Class**: Implements the doubly-linked list to hold the blocks.
  - `InsertAfter()` to insert a new node after a given node in the chain.
  - `Swap()` to swap two nodes in the list.
  - `Unscramble()` to rearrange the blocks into their original order.
  - Destructor and helper functions for memory management.

## Project Structure

- `block.cpp`: Implements the `Block` class, which holds data about an image block.
- `chain.cpp`: Implements the `Chain` class, which is a doubly-linked list used to store and manage the blocks.
- `main.cpp`: The main program to demonstrate the functionality.
  
## Functions

### Block Class

- `int Width() const`: Returns the width of the current block.
- `int Height() const`: Returns the height of the current block.
- `void Build(PNG &im, int x, int width)`: Grabs a vertical strip from the image `im`.
- `void Render(PNG &im, int x) const`: Draws the current block at position `(x, 0)` in the image.

### Chain Class

- `void Clear()`: Helper function for deallocating dynamic memory associated with the chain.
- `void Copy(const Chain &other)`: Helper function for the copy constructor and assignment operator.
- `~Chain()`: Destructor.
- `Node* InsertAfter(Node *p, const Block &ndata)`: Inserts a new node after node `p`.
- `PNG Render()`: Renders the pixel data of the chain to a PNG image.
- `void Swap(Node *p, Node *q)`: Swaps two nodes in the chain.
- `void Unscramble()`: Rearranges the chain into its original order by minimizing the difference between adjacent blocks.

📂 Image-Strip-Linker-DLL  
 ├── 📜 README.md  # Project documentation  
 ├── 📜 main.cpp  # Main driver code  
 ├── 📜 DLL.h / DLL.cpp  # Doubly Linked List implementation  
 ├── 📜 ImageProcessor.h / ImageProcessor.cpp  # Image processing functions  
 ├── 📂 images/  # Sample images for testing  
 ├── 📂 bin/  # Compiled binaries  
 └── 📂 docs/  # Additional documentation  

## Memory Management

The Chain class is responsible for dynamic memory management, including:
- Proper allocation and deallocation of memory for nodes in the doubly-linked list.
- Copy constructor and assignment operator to handle deep copying of the list.
  
The Block class does not require a destructor, copy constructor, or assignment operator because the memory it uses is handled by the Chain class.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- The project is based on the concept of a doubly-linked list and dynamic memory management.
- Thanks to the course materials and instructors for providing the initial framework for this assignment.
