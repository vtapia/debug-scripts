# KVM + Ftrace Windows reboot debugging

Set of scripts to capture the kernel work (vhost/kvm/virtio...) during a Windows VM reboot.

## How to set the environment

1. Guest: Enable WinRM

From a powershell interface, run the following commands:

```
Set-ExecutionPolicy -ExecutionPolicy Bypass -Force
Enable-PSRemoting -force
Set-Item WSMan:\localhost\Client\TrustedHosts * -force
winrm set winrm/config/service/auth '@{Basic="true"}'
winrm set winrm/config/service '@{AllowUnencrypted="true"}'
restart-Service winrm
```

2. Hypervisor: Kernel with debugfs enabled to use ftrace

Make sure debugfs/tracefs is mounted:

```
$ mount | grep debug
debugfs on /sys/kernel/debug type debugfs (rw,relatime)
tracefs on /sys/kernel/debug/tracing type tracefs (rw,relatime)
```

Mount if not, as root:

```
mount -t debugfs nodev /sys/kernel/debug
mount -t tracefs nodev /sys/kernel/debug/tracing
```

3. Hypervisor: install PyWinRM (and its requirements) to run remote commands to the Windows guest

Install python-pip:

```
sudo apt install python-pip
```

Install virtualenv using pip:

```
sudo pip install virtualenv
```

As the ubuntu user, create the virtual environment in ~/reproducer:

```
cd ; virtualenv reproducer
```

Activate the virtual environment:

```
cd ~/reproducer ; source bin/activate
```

NOTE: To exit the virtual environment, just run "deactivate"

Create a directory to for the scripts:

```
mkdir ~/reproducer/scripts
```

Install pywinrm using pip:

```
pip install pywinrm
```

4. Download the scripts from this repo and run

```
cd /tmp ; git clone https://github.com/vtapia/debug-scripts.git
cp debug-scripts/kvm-ftrace-windows-reboot/* ~/reproducer/scripts
```

Determine the instance name according to virsh (e.g. instance-00000004) and its IP. Then run:

```
source ~/reproducer/bin/activate
cd ~/reproducer/scripts
./monitor_ftrace.sh $INSTANCE $IP      # e.g. ./monitor_ftrace.sh instance-00000004 10.230.63.192
```

This will create a txt file at /home/ubuntu/${INSTANCE}.txt containing the output from ftrace. This file will always hold the information of the last run.
