# LC3_VM

Virtual machine for the  [LC3 architecture](https://en.wikipedia.org/wiki/Little_Computer_3).
LC3_VM is a simple virtual machine written following this [tutorial](https://justinmeiners.github.io/lc3-vm/) to get a better understanding how virtual machines work.

I added tests for all instructions. Each instruction has a test written in LC3 Assembly which is converted to an .obj file using lc3as provided by http://highered.mheducation.com/sites/0072467509/student_view0/lc-3_simulator.html.

This project will also be used to test my [LC3_ASM](https://github.com/feelqah/LC3_ASM).

## Installation


## Usage
For building the lc3_vm:
```bash
make 
```
lc3_vm program is located in the bin dir.

example usage:
./lc3_vm assembly_examples/obj/2048.obj


For building tests:
```bash
make test
```
run_tests program is located in root dir.

example usage:
./run_tests tests/add/add.obj


## Contributing

## License

[CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/)
