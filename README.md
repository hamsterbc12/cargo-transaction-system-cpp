# cargo-transaction-system-cpp
C++ transaction and systems modeling project
# Cargo Transport Transaction System (C++)

## Overview
This project is a C++ console-based transaction system that simulates a real-world cargo shipping workflow. Users can enter multiple containers with physical dimensions, select delivery methods, process payments, and receive an itemized receipt with estimated delivery dates.

The project emphasizes modular design, structured data handling, input validation, and reproducible computation.

## Features
- Structured container modeling using C++ `struct`
- Support for multiple containers per transaction
- Rule-based pricing and delivery eligibility constraints
- Input validation for dimensions, delivery methods, and identification
- Automated cost calculation, sales tax computation, and receipt formatting
- Estimated delivery date computation using C++ time libraries

## Technical Highlights
- Modular function design for volume calculation, payment processing, validation, and delivery estimation
- Use of STL containers (`vector`) for dynamic data storage
- Date and time manipulation using `tm`, `mktime`, and `strftime`
- Console-based user interaction with formatted output

## Skills Demonstrated
- C++ programming
- Systems modeling
- Data validation
- Control flow and logic design
- Reproducible computation
- Problem decomposition

## Future Improvements
- File I/O for saving receipts
- Unit testing for validation functions
- Refactoring into separate header and implementation files
- Command-line argument support

## Author
Bea Calma
