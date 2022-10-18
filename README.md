# Netcal
It is a small program written in C++ as a tool for my use, and as a systems engineering student I also wanted to learn how to create my own tools.

# Usage
```bash
$ netcal 196.250.110.1/24
+-------------+------------------+-------------------------------------+
|   Address   | 196.250.110.1    | 11000100.11111010.01101110.00000001 |
+-------------+------------------+-------------------------------------+
|   Netmask   | 255.255.255.0    | 11111111.11111111.11111111.00000000 |
+-------------+------------------+-------------------------------------+
|   Network   | 196.250.110.0/24 | 11000100.11111010.01101110.00000000 |
+-------------+------------------+-------------------------------------+
|  Broadcast  | 196.250.110.255  | 11000100.11111010.01101110.11111111 |
+-------------+------------------+-------------------------------------+
| Start range | 196.250.110.1    | 11000100.11111010.01101110.00000001 |
+-------------+------------------+-------------------------------------+
|  End range  | 196.250.110.255  | 11000100.11111010.01101110.11111111 |
+-------------+------------------+-------------------------------------+
|    Hosts    | 254              |                                     |
+-------------+------------------+-------------------------------------+
```

```
$ netcal -h
Usage: netcal [-h] address

Utility that calculates network address, netmask, network, broadcast, etc by given IP Address with CIRD Notation.

Positional arguments:
  address      	ip address with cird notation, example: 192.168.100.1/24 

Optional arguments:
  -h, --help   	shows help message and exits 
  -v, --version	prints version information and exits 

Written by Rosmer Lopez
```

# Librarys
This program makes use of the following third party libraries.
- [Argparse](https://github.com/p-ranav/argparse)
- [Asio](https://github.com/chriskohlhoff/asio)
- [Tabulate](https://github.com/p-ranav/tabulate)
