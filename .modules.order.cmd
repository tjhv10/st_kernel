cmd_/home/vboxuser/develop/kernel/st_kernel/modules.order := {   echo /home/vboxuser/develop/kernel/st_kernel/st_kernel.ko; :; } | awk '!x[$$0]++' - > /home/vboxuser/develop/kernel/st_kernel/modules.order