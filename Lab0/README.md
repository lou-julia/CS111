# A Kernel Seedling
Create a /proc/count file that shows the current number of running processes (or
tasks) running.

## Building
```shell
make
```

## Running
```shell
sudo insmod proc_count.ko
cat /proc/count
```
Will report a single integer that represents the number of processes. 

Example from my my result: 
136

## Cleaning Up
```shell
sudo rmmod proc_count
```

## Testing
```python
python -m unittest
```
Will output that it ran 3 tests in a certain amount of seconds.
Will output "OK".

Example from my result: 
Ran 3 tests in 10.285s

OK

Report which kernel release version you tested your module on
(hint: use `uname`, check for options with `man uname`).
It should match release numbers as seen on https://www.kernel.org/.

```shell
uname -r -s -v
```
Kernel release version is 5.14.8-arch1-1 from Linux virtual machine.
