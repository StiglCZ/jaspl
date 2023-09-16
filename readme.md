# JASPL
## Just another stigl programming lang

JASPL compiles to nasm assembly.

### Syntax:
```
$ This is a comment

$ This defines a function with
$ name example, return type number
$ and 1 argument, number
func example(int , number) {
    int variable = 10;
    $ Example of recursion
    if(variable = 10){
        call example(variable);
    }
    $ Returns a value
    return 10;
}
```
Entrypoint is main
You can also create pointers using \variable

You can use syscalls and interupts using set function
set eax_v ebx_v ecx_v edx_v interupt

