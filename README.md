# Debug scripts

This repo contains a bunch of scripts I use frequently for debugging purposes.

## Contents

+ [kvm-ftrace-windows-reboot](#kvm-ftrace-windows-reboot)

## kvm-ftrace-windows-reboot

This directory contains:
+ monitor_ftrace.sh
+ winrm_exec.py
+ reboot.ps1

monitor_ftrace.sh enables ftrace tracing, reboots a windows VM, and when the VM is back, dumps the ring buffer and stops the trace. This process is repeated until the machine crashes.

winrm_exec.py is used by monitor_ftrace.sh to run ps1 scripts in a remote windows machine (requires [pywinrm](https://github.com/diyan/pywinrm))
