# Library Management System

A comprehensive Library Management System built in C++ that allows management of books and user accounts.

## Features

### For Librarians:
- Add new books to the library
- Remove books from the library
- View all books in the library
- Add new users (Students, Faculty, Librarians)
- Remove existing users

### For Students:
- Borrow books
- Return books
- View borrowed books
- View borrowing history
- Pay fines

### For Faculty:
- Borrow books
- Return books
- View borrowed books
- View borrowing history

## System Requirements

- C++17 or later
- Windows operating system
- g++ compiler (for building)

## Getting Started

1. Open terminal and navigate to the project directory
2. Build and run the project:
```bash
g++ LMS.cpp -o LMS.exe
./LMS.exe
```

## User Roles

The system supports three types of users:
1. Student - Can borrow and return books
2. Faculty - Can borrow and return books
3. Librarian - Full administrative access

## Default Librarian Account

For initial login:
- UserId: 100
- Password: password

## File Structure

```
LMS/
├── Users/             # User data
│   ├── Student/       # Student user data
│   ├── Faculty/       # Faculty user data
│   └── Librarian/     # Librarian user data
├── Books/             # Book data
└── LMS.cpp           # Main source code
```

## Security Features

- Password encryption
- User authentication
- Role-based access control
- Fine management for overdue books
