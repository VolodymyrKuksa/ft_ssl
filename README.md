# ft_ssl
ft_ssl is a school42/UNIT Factory project. The goal of the project is to implement md5 and sha356 algorithms and pack them into an executable program.  
Made and tested only for MacOS.

# Installation
Clone the repository and run `make`. This will compile the executable named `ft_ssl` and the libraries upon which it depends: `libft.a` and `clp.a`.

# Usage
`./ft_ssl [command] [flags] [parameters]`  
### Available commands:
`md5` - execute MD5 hashing algorithm  
`sha256` - execute SHA256 hashing algorithm
### Available flags:
`-p` - echo STDIN to STDOUT and append the checksum to STDOUT  
`-q` - quiet mode  
`-r` - reverse the format of the output  
`-s` - print the sum of the given string (the string should be provided right after this flag)  
# The task
The PDF detailing the task can be found [here](resources/ft_ssl_md5.en.pdf).
