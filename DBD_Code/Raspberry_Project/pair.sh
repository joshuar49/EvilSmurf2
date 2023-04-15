#!/usr/bin/expect -f

set bt_addr [lindex $argv 0]
set file_name [lindex $argv 1]
set timeout [lindex $argv 2]

log_file "$file_name"

spawn sudo bluetoothctl
expect -re ".*#"

send "agent on\r"
expect "Agent registered"

send "discoverable on\r"
expect "Changing discoverable on succeeded" 

send "pairable on\r"
expect "Changing pairable on succeeded" 

send "scan on\r"
expect -re "Device $file_name"

send "pair $bt_addr\r"
expect -re "Confirm passkey"

send "yes\r"
expect "Pairing successful"

send "exit\r"
expect eof

