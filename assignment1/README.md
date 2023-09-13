# carManagementSystem

This is a C++ demo project as the car management system for an assumed car rental company, as assignment 1 of Professional Software Engineering course. This project including 4 parts: user management, car management, rental booking and rental management. 

这是一个 C++ 演示项目，作为假设的汽车租赁公司的汽车管理系统，作为专业软件工程课程的作业 1。 该项目包括4个部分：用户管理、车辆管理、租车预订和租赁管理。

For chinese students who have learned basic syntax of C++ and want to build a whole object-oriented management system, reference [1] could be helpful for you, as a step-to-step guide video courses.

对于已经学习了C++基本语法并想要构建一个完整的面向对象管理系统的中国学生，参考文献[1]可能会对您有所帮助，作为逐步指导的视频课程。

## Dependencies
```bash

```

## Start the program
- Open the project folder with microsoft visual studio, and directly start the project. 
- admin login page: { username: 'admin', password: '123456'}
- user login page: different usernames and passwords are stored in users.csv.

## UserManual
- There is also a user manual as a reference. Admin and users' steps of using the system and how to modify demo csv databases are listed in the usermanual.

## Usage

```C++
// entrance main function
main.cpp

// admin menu, user menu, admin login process, user login process
systemPage.h

// including add, remove, update, query cars and car-retal options 
carManage.h

// encapsulate file operate functions, such as from vector<Car> to .csv file.
tools.h

// object Car
car.h

## Reference
[1] [book management system](https://www.bilibili.com/video/BV1Sv4y1Y74E/)
