# Banking-System

Second practice for advanced programming course at Bu-Ali Sina University.

In this program we want to design a simple banking system.    

## Installation

use build system [cmake](https://cmake.org/download/)

## Usage

This program can create new account,deposit and withdraw money,renewal account,get_loan,pay_loan and add profit for customers.

We take the username and IP from the customer and create an account for her or him

IP must be like: 1.2.3.4 , 22.36.45.87 , 120.36.7.5

example:

```bash
create john:1.1.1.1
deposit john:1.1.1.1:200
withdraw john:1.1.1.1:20
transfer john:1.1.1.1:henry:100
renewal john:1.1.1.1
get_loan john:1.1.1.1:60
pay_loan john:30
add_profits john
```
If the user enters the username or IP, we display the account information

```bash
1.1.1.1
```

output:
```bash
usernam:john
IP:1.1.1.1
.....
```
